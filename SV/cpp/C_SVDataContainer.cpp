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
			this->clInfo[i].clStatus.clActive = clTrue;							// アクティブ状態に設定
			this->clInfo[i].clStatus.clCommStatus = GoodNess;					// 通信状況を良好に設定
			this->clInfo[i].commActiveCnt = ACTIVE_CNT;							// アクティブカウントを設定
			this->clInfo[i].sequenceNo = 0;										// シーケンスナンバーを初期化
			memcpy(&this->clInfo[i].tcpSockInfo, tcpSock, sizeof(Sock_Info));	// ソケットを設定
			memcpy(&this->clInfo[i].udpSockInfo, udpSock, sizeof(Sock_Info));	// ソケットを設定
			this->clInfo[i].pingTime = pingTime;								// 計測したピンタイムを設定

			printf("新規クライアントが%d番に追加されました\n", i);
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

/**************** ゲッター ****************/
// ソケットを取得
const SOCKET* C_SVDataContainer::GetClientSocket(int target, SOCKETTYPE sockType){
	if (target >= MAX_CLIENT){
		printf("GetSock異常引数 Target %d \n", target);
		while (true){ Sleep(100); }
	}
	switch (sockType){
	case SOCKETTYPE::TCP:
		return &this->clInfo[target].tcpSockInfo.socket;
	case SOCKETTYPE::UDP:
		return &this->clInfo[target].udpSockInfo.socket;

	default:
		printf("GetSock異常引数 sockType %d \n", sockType);
		while (true){ Sleep(100); }
	}

}

// アドレスを取得
const sockaddr_in* C_SVDataContainer::GetClientAddr(int target, SOCKETTYPE sockType){
	if (target >= MAX_CLIENT){
		printf("GetAddr異常引数 Target %d \n", target);
		while (true){ Sleep(100); }
	}
	switch (sockType){
	case SOCKETTYPE::TCP:
		return &this->clInfo[target].tcpSockInfo.addr;
	case SOCKETTYPE::UDP:
		return &this->clInfo[target].udpSockInfo.addr;

	default:
		printf("GetAddr異常引数 %d \n", sockType);
		while (true){ Sleep(100); }
	}
}

// FDSを取得
const FD_SET* C_SVDataContainer::GetClientFds(int target, SOCKETTYPE sockType){

	switch (sockType){
	case SOCKETTYPE::TCP:
		return &this->clInfo[target].tcpSockInfo.fds;
	case SOCKETTYPE::UDP:
		return &this->clInfo[target].udpSockInfo.fds;

	default:
		printf("GetAddr異常引数 %d \n", sockType);
		while (true){ Sleep(100); }
	}
}

// クライアントの通信状況取得
const ClientStatus* C_SVDataContainer::GetClientStatus( int target ){
	if (target >= MAX_CLIENT){
		printf("GetStatus異常引数 Target %d \n", target);
		while (true){ Sleep(100); }
	}
	return &this->clInfo[target].clStatus;
}

// アクティブカウントを取得
const int C_SVDataContainer::GetClientActiveCnt( int target ){
	if (target >= MAX_CLIENT){
		printf("GetActiveCnt異常引数 Target %d \n", target);
		while (true){ Sleep(100); }
	}
	return this->clInfo[target].commActiveCnt;
}

// クライアントのシーケンスナンバーを取得
const ULONG C_SVDataContainer::GetClientSequenceNo( int target ){
	if (target >= MAX_CLIENT){
		printf("GetSewuenceNo異常引数 Target %d \n", target);
		while (true){ Sleep(100); }
	}
	return this->clInfo[target].sequenceNo;
}

// ピンのタイムを取得
const int C_SVDataContainer::GetClientPingTime( int target )
{
	if (target >= MAX_CLIENT){
		printf("GetPingTime異常引数 Target %d \n", target);
		while (true){ Sleep(100); }
	}
	return this->clInfo[target].pingTime;
}

// ゲームデータを取得
const char* C_SVDataContainer::GetClientGameData( int target ){
	if (target >= MAX_CLIENT){
		printf("GetGameData異常引数 Target %d \n", target);
		while (true){ Sleep(100); }
	}
	return this->clInfo[target].lastGameData;
}

// 利用しているゲームデータの最大サイズを取得
const int C_SVDataContainer::GetDataSize(){
	return this->maxDataSize;
}


// サーバーのシーケンスナンバーを取得
//const UINT	C_SVDataContainer::GetSVSequenceNo(void){
//	return this->m_svSequenceNo;
//}

const FatalError	C_SVDataContainer::GetFatalError(void){
	return this->m_fatalError;
}
