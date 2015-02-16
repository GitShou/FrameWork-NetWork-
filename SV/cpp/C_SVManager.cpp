#define __SERVER_MANAGER_CPP__
#include "C_SVManager.h"
#include <time.h>


C_SVManager::~C_SVManager(void){
	this->svOperatingNormally = svFalse;

}

void C_SVManager::StartAccept(){

	// �ڑ��̎�t�J�n
	listen(this->m_svSockInfo.socket, MAX_CLIENT);

	//// �A�N�Z�v�g�J�n�O�Ɏg�p����ϐ��̏�����
	memset(&this->m_newClient, 0, sizeof(NEW_CLIENT));
	this->m_newClient.tcpSock.addrLen = sizeof(sockaddr);
	this->m_newClient.udpSock.addrLen = sizeof(sockaddr);

	this->MakeSocket(&m_newClient.tcpSock.socket, SOCKETTYPE::TCP);
	this->MakeSocket(&m_newClient.udpSock.socket, SOCKETTYPE::UDP);

	// �A�N�Z�v�g�p�̃X���b�h���N��
	this->m_acceptInfo.hd.TH = (HANDLE)_beginthreadex(NULL, 0, Accept, this, 0, &this->m_acceptInfo.hd.ID);
}

UINT WINAPI  C_SVManager::Accept(void* data){
	C_SVManager*	svManager = (C_SVManager*) data;

	while(svManager->svOperatingNormally){
		printf("�N���C�A���g��t��...\n\n");
		svManager->m_newClient.tcpSock.socket = accept( svManager->m_svSockInfo.socket, 
														(struct sockaddr *) &svManager->m_newClient.tcpSock.addr, 
														&svManager->m_newClient.tcpSock.addrLen);

		if (!svManager->p_checkClass->CheckCommError(svManager->m_newClient.tcpSock.socket)) {	 // �G���[�`�F�b�N
			printf("%s �ƃR�l�N�V�������󂯕t���܂���\n", inet_ntoa(svManager->m_newClient.tcpSock.addr.sin_addr));
			if (svManager->CheckingNewClient()){
				printf("�N���C�A���g���^�C���A�E�g���܂���\n");
			}
		}
	}
	return 0;
}

bool C_SVManager::CheckingNewClient(void){
	FrameWorkMsg		buf;				// �ʐM�p�o�b�t�@
	int					sts;
	int					rndNo;				// �����i�[�p
	DWORD				oTime, nTime;		// ping���Ԍv���p
	fd_set				workFds;
	timeval				timeOut;

	srand((unsigned)time(NULL));

	timeOut.tv_sec = TIMEOUT_PING_CHECK_SEC;
	timeOut.tv_usec = TIMEOUT_PING_CHECK_USEC;

	// TCP�\�P�b�g�Ɏ󂯂�connect�̏����g���AUDP�̃\�P�b�g��connect����
	//this->Connection(&this->m_newClient.udpSock.socket, &this->m_newClient.tcpSock.addr);

	FD_SET(this->m_newClient.tcpSock.socket, &this->m_newClient.tcpSock.fds);


	printf("�N���C�A���g�̒ʐM���x���v�����܂�\n");
	oTime = timeGetTime();
	
	// �����_���l�𐶐����A�N���C�A���g�ɑ��M�i�N���C�A���g�͋K��̌v�Z���@���g���l��ύX�����̒l���T�[�o�[��UDP�\�P�b�g�ɑ΂����M����j
	rndNo = rand() % 100;
	//buf.Msg.Body0.rndNo = rndNo;
	//send(m_newClient.udpSock.socket, buf.data, sizeof(FrameWorkMsg), 0);

	memcpy(&workFds, &this->m_newClient.udpSock.fds, sizeof(fd_set));

	// ��莞�ԃN���C�A���g����̕ԐM���Ȃ��ꍇ�I��
	sts = select(0, &workFds, NULL, NULL, &timeOut);
	if (sts != NULL) {
		// ��M�����f�[�^���`�F�b�N���A�����Ȓl�������ꍇ�V�K�N���C�A���g�Ƃ��Ď󂯓����(�`�F�b�N���̓}�N���Œ�`���Ă���)
		if (FD_ISSET(this->m_newClient.udpSock.socket, &workFds)){
			recv(m_newClient.udpSock.socket, buf.data, sizeof(FrameWorkMsg), 0);
			nTime = timeGetTime();

			if (ATTESTATION_NO == buf.Msg.Body0.rndNo){
				printf("���K�N���C�A���g�ł�\n");

				if ((nTime - oTime) <= LIMIT_PINGTIME){
					printf("�N���C�A���g�Ƃ̒ʐM���x�����e�͈͓�\n");
					printf("�N���C�A���g��ǉ����܂�\n");
					this->p_dataContainer->AddClient(&m_newClient.tcpSock, &m_newClient.udpSock, (nTime - oTime));
				}
				else{
					printf("�N���C�A���g�Ƃ̒ʐM���x�����e�͈͊O\n");
					printf("�N���C�A���g�̃Q�[���Q�������ۂ��܂�\n");
				}
			}
			else{
				printf("�񐳋K�̃N���C�A���g�ł�\n");
				printf("�N���C�A���g�̐ڑ������ۂ��܂�\n");
			}
		}
	}else{
		return true;
	}

	return false;
}


void C_SVManager::UpdateManager(void){
	++this->m_svSequenceNo;

}
bool C_SVManager::Connection(SOCKET* sock, sockaddr_in* addr){
	int sts;
	int	addrLen = sizeof(sockaddr);

	sts = connect(*sock, (struct sockaddr *) addr, addrLen);
	if (this->p_checkClass->CheckCommError(sts)){
		return true;	// �����ŃR���X�g���N�^�������I��
	}
	return false;
}
bool C_SVManager::MakeSocket(SOCKET* sock, SOCKETTYPE type){

	switch (type){
	case SOCKETTYPE::TCP:
		// SOCKETTYPE::UDP�ʐM�p�̃\�P�b�g�𐶐�����
		*sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (this->p_checkClass->CheckCommError(sock)){
			printf("TCP�\�P�b�g�������s\n");
			_getch();
			//�R���\�[���폜
			FreeConsole();
			return true;
		}
		break;
	case SOCKETTYPE::UDP:
		// SOCKETTYPE::UDP�ʐM�p�̃\�P�b�g�𐶐�����
		*sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (this->p_checkClass->CheckCommError(sock)){
			printf("UDP�\�P�b�g�������s\n");
			_getch();
			//�R���\�[���폜
			FreeConsole();
			return true;
		}
		break;
	}
	return false;
}

bool C_SVManager::SendMultiCast(char* data, int dataSize){
	if (this->p_sendClass->MultiCast(data, dataSize)){
		return true;
	}
	return false;
}
bool C_SVManager::SendUniCast(int target, SOCKETTYPE type, char* data, int dataSize){
	if (this->p_sendClass->UniCast(target, type, data, dataSize)){
		return true;
	}
	return false;
}
