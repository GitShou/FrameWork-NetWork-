#include "C_SVSend.h"


void C_SVSend::InitSender(){
	sockaddr_in		multicastAddr;
	int				sts;
	int	addrLen = sizeof(sockaddr);

	this->m_fatalError = error;

	this->sendBuf = new char[this->p_dataContainer->GetDataSize()];
	this->m_multicastSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (this->p_checkClass->CheckCommError(this->m_multicastSocket)){
		printf("マルチキャスト用ソケット設定失敗");
		exit(0);
	}

	multicastAddr.sin_family = AF_INET;
	multicastAddr.sin_port = htons(CLIENT_PORTNO);
	multicastAddr.sin_addr.s_addr = inet_addr(MULTICAST_ADDR);

	sts = connect(this->m_multicastSocket, (struct sockaddr*) &multicastAddr, addrLen);
	if (this->p_checkClass->CheckCommError(sts)){
		printf("マルチキャスト用ソケットのconnect失敗");
		exit(0);	// ここでコンストラクタを強制終了
	}

	this->m_fatalError = normally;

}


C_SVSend::~C_SVSend(void)
{
	delete this->sendBuf;
}

bool C_SVSend::UniCast(int target, SOCKETTYPE type, char* data, const int dataSize){
	int sts;

	sts = send(*this->p_dataContainer->GetClientSocket(target, type), data, dataSize, 0);
	if (this->p_checkClass->CheckCommError(sts)){
		return true;
	}
	return false;
}

bool C_SVSend::MultiCast(char* data, const int dataSize){
	int sts;
	sts = send(this->m_multicastSocket, data, dataSize, 0);

	if (this->p_checkClass->CheckCommError(sts)){
		return true;
	}
	return false;
}


const FatalError	C_SVSend::GetFatalError(void){
	return this->m_fatalError;
}
