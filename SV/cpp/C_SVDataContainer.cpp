#include "C_SVDataContainer.h"


void C_SVDataContainer::InitDataContainer(void){
	this->m_fatalError = error;
	clInfo.resize(MAX_CLIENT);

	this->m_fatalError = normally;
}

C_SVDataContainer::~C_SVDataContainer(void){
	for(int i = 0; i < MAX_CLIENT; i++){
		delete clInfo[i].lastGameData;
	}
}


bool C_SVDataContainer::AddClient(Sock_Info* tcpSock, Sock_Info* udpSock, int pingTime){
	int i;

	for(i = 0; i < MAX_CLIENT; ++i){
		if(!this->clInfo[i].clStatus.clActive){
			this->clInfo[i].clStatus.clActive = clTrue;							// �A�N�e�B�u��Ԃɐݒ�
			this->clInfo[i].clStatus.clCommStatus = GoodNess;					// �ʐM�󋵂�ǍD�ɐݒ�
			this->clInfo[i].commActiveCnt = ACTIVE_CNT;							// �A�N�e�B�u�J�E���g��ݒ�
			this->clInfo[i].sequenceNo = 0;										// �V�[�P���X�i���o�[��������
			memcpy(&this->clInfo[i].tcpSockInfo, tcpSock, sizeof(Sock_Info));	// �\�P�b�g��ݒ�
			memcpy(&this->clInfo[i].udpSockInfo, udpSock, sizeof(Sock_Info));	// �\�P�b�g��ݒ�
			this->clInfo[i].pingTime = pingTime;								// �v�������s���^�C����ݒ�

			printf("�V�K�N���C�A���g��%d�Ԃɒǉ�����܂���\n", i);
			return true;
		}
	}
	return false;
}
void C_SVDataContainer::DeleteClient(int target){
	memset(&this->clInfo[target], 0, sizeof(Client_Info));
}

bool C_SVDataContainer::SetClientLastData(int target, char* data){
	memcpy(this->clInfo[target].lastGameData, data, this->maxDataSize);
	return true;
}

/**************** �Q�b�^�[ ****************/
// �\�P�b�g���擾
const SOCKET* C_SVDataContainer::GetClientSocket(int target, SOCKETTYPE sockType){
	if (target >= MAX_CLIENT){
		printf("GetSock�ُ���� Target %d \n", target);
		while (true){ Sleep(100); }
	}
	switch (sockType){
	case SOCKETTYPE::TCP:
		return &this->clInfo[target].tcpSockInfo.socket;
	case SOCKETTYPE::UDP:
		return &this->clInfo[target].udpSockInfo.socket;

	default:
		printf("GetSock�ُ���� sockType %d \n", sockType);
		while (true){ Sleep(100); }
	}

}

// �A�h���X���擾
const sockaddr_in* C_SVDataContainer::GetClientAddr(int target, SOCKETTYPE sockType){
	if (target >= MAX_CLIENT){
		printf("GetAddr�ُ���� Target %d \n", target);
		while (true){ Sleep(100); }
	}
	switch (sockType){
	case SOCKETTYPE::TCP:
		return &this->clInfo[target].tcpSockInfo.addr;
	case SOCKETTYPE::UDP:
		return &this->clInfo[target].udpSockInfo.addr;

	default:
		printf("GetAddr�ُ���� %d \n", sockType);
		while (true){ Sleep(100); }
	}
}

// FDS���擾
const FD_SET* C_SVDataContainer::GetClientFds(int target, SOCKETTYPE sockType){

	switch (sockType){
	case SOCKETTYPE::TCP:
		return &this->clInfo[target].tcpSockInfo.fds;
	case SOCKETTYPE::UDP:
		return &this->clInfo[target].udpSockInfo.fds;

	default:
		printf("GetAddr�ُ���� %d \n", sockType);
		while (true){ Sleep(100); }
	}
}

// �N���C�A���g�̒ʐM�󋵎擾
const ClientStatus* C_SVDataContainer::GetClientStatus( int target ){
	if (target >= MAX_CLIENT){
		printf("GetStatus�ُ���� Target %d \n", target);
		while (true){ Sleep(100); }
	}
	return &this->clInfo[target].clStatus;
}

// �A�N�e�B�u�J�E���g���擾
const int C_SVDataContainer::GetClientActiveCnt( int target ){
	if (target >= MAX_CLIENT){
		printf("GetActiveCnt�ُ���� Target %d \n", target);
		while (true){ Sleep(100); }
	}
	return this->clInfo[target].commActiveCnt;
}

// �N���C�A���g�̃V�[�P���X�i���o�[���擾
const ULONG C_SVDataContainer::GetClientSequenceNo( int target ){
	if (target >= MAX_CLIENT){
		printf("GetSewuenceNo�ُ���� Target %d \n", target);
		while (true){ Sleep(100); }
	}
	return this->clInfo[target].sequenceNo;
}

// �s���̃^�C�����擾
const int C_SVDataContainer::GetClientPingTime( int target )
{
	if (target >= MAX_CLIENT){
		printf("GetPingTime�ُ���� Target %d \n", target);
		while (true){ Sleep(100); }
	}
	return this->clInfo[target].pingTime;
}

// �Q�[���f�[�^���擾
const char* C_SVDataContainer::GetClientGameData( int target ){
	if (target >= MAX_CLIENT){
		printf("GetGameData�ُ���� Target %d \n", target);
		while (true){ Sleep(100); }
	}
	return this->clInfo[target].lastGameData;
}

// ���p���Ă���Q�[���f�[�^�̍ő�T�C�Y���擾
const int C_SVDataContainer::GetDataSize(){
	return this->maxDataSize;
}


// �T�[�o�[�̃V�[�P���X�i���o�[���擾
//const UINT	C_SVDataContainer::GetSVSequenceNo(void){
//	return this->m_svSequenceNo;
//}

const FatalError	C_SVDataContainer::GetFatalError(void){
	return this->m_fatalError;
}
