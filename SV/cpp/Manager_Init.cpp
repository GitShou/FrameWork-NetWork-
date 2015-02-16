#include "C_SVManager.h"

#pragma warning(disable : 4996)

void C_SVManager::m_InitManager(){
	WSADATA		m_wd;								// �v�r�`�r�s�`�q�s�t�o�p
	WORD		requiredversion = MAKEWORD(2,2);	// ���̃v���O�������v������o�[�W����

	this->svOperatingNormally = svFalse;
	this->m_svSequenceNo = 0;

	// ���\���p�R���\�[���E�C���h�E�\��
	AllocConsole();
	freopen( "CON", "r", stdin  );  // �W�����͂����蓖�Ă�
	freopen( "CON", "w", stdout );  // �W���o�͂����蓖�Ă�

	// �}�l�[�W���[�̏��������s��
	this->p_checkClass.reset(new C_CommCheck());

	if( this->m_InitWinsock(&m_wd, requiredversion) ){
		exit(1);
	}
	if( this->m_CheckingVersion(&m_wd, requiredversion) ){
		exit(1);
	}
	if( this->m_InitSock() ){
		exit(1);
	}
	printf("��t�p�\�P�b�g�̃o�C���h�J�n\n");
	if (this->m_BindingSocket(&this->m_svSockInfo.socket, &this->m_svSockInfo.addr)){
		exit(1);
	}

	// �g�p���邻�̑��N���X�̏�����
	this->p_dataContainer.reset(new C_SVDataContainer(this->m_maxDataSize));
	if (this->p_dataContainer->GetFatalError()){
		printf("�R���e�i���������s\n");
	}
	this->p_recvClass.reset(new C_SVRecv(this->p_dataContainer, this->p_checkClass));
	if (this->p_recvClass->GetFatalError()){
		printf("���V�[�o�[���������s\n");
	}
	this->p_sendClass.reset(new C_SVSend(this->p_dataContainer, this->p_checkClass));
	if (this->p_sendClass->GetFatalError()){
		printf("�Z���_�[���������s\n");
	}

	printf("�}�l�[�W���[�y�сA�e�N���X�̏���������\n");
	this->svOperatingNormally = svTrue;		// �}�l�[�W���[�����������ł������Ƃ��L��

	this->StartAccept();


}

bool C_SVManager::m_InitWinsock(WSADATA* m_wd, WORD requiredversion){
	int sts;
	printf("WinSock�������J�n\n");

	// Windows �̏ꍇ
	sts = WSAStartup(requiredversion, m_wd);
	if( this->p_checkClass->CheckCommError(sts) )
	{
		printf( "WINSOCK���������s\n");
		getch();
		//�R���\�[���폜
		FreeConsole();
		return true;
	}
	return false;
}
bool C_SVManager::m_CheckingVersion(WSADATA* m_wd, WORD requiredversion){
	printf("�o�[�W�����`�F�b�N\n");
	// �o�[�W�����`�F�b�N
	if(m_wd->wVersion != requiredversion)
	{
		printf("�o�[�W�����G���[");
		getch();
		//�R���\�[���폜
		FreeConsole();
		return true;	// �����ŃR���X�g���N�^�������I��
	}
	return false;
}
bool C_SVManager::m_InitSock(){
	int flg = true;
	int	portNo;

	printf("�\�P�b�g�̏������J�n\n");

	// �\�P�b�g�̐����iSOCKETTYPE::TCP�j
	this->MakeSocket(&this->m_svSockInfo.socket, SOCKETTYPE::TCP);

	// �T�[�o�[�̎g�p����|�[�g�ԍ���ݒ肷��i���K�l�����͂����܂Ń��[�v�j
	this->m_svSockInfo.addrLen = sizeof(this->m_svSockInfo.addr);
	printf("�}�l�[�W���[�̎�t�p�\�P�b�g�𐶐����܂���\n");
	// �T�[�o�[�������
	printf("���񂱂̃T�[�o�[�Ŏg�p����|�[�g�ԍ�����͂��Ă��������B\n(�����ԍ��F49152�`65535)");
	while (flg){
		scanf_s("%d", &portNo);
		if (portNo > MAX_PORTNO || portNo < MIN_PORTNO){
			printf("�l���s���ł��B\n�ēx���͂��Ă��������B");
		}
		else{
			flg = false;
		}
	}	
	// �����̃A�h���X��ݒ�
	memset(&this->m_svSockInfo.addr, 0, sizeof(sockaddr_in));
	this->m_svSockInfo.addr.sin_port = htons(portNo);
	this->m_svSockInfo.addr.sin_family = AF_INET;
	this->m_svSockInfo.addr.sin_addr.s_addr = htonl(INADDR_ANY);
	this->m_svSockInfo.addrLen = sizeof(sockaddr_in);


	return false;
}
bool C_SVManager::m_BindingSocket(SOCKET* sock, sockaddr_in* addr){
	int sts;
	int addrLen = sizeof(sockaddr_in);

	// �\�P�b�g�̃o�C���h
	sts = bind(*sock, (struct sockaddr *) addr, addrLen);
	if (this->p_checkClass->CheckCommError(sts)){
		printf("�o�C���h���s\n");
		getch();
		FreeConsole();	//�R���\�[���폜
		return true;
	}
	return false;
}