#define __SERVER_MANAGER_CPP__
#include "C_SVManager.h"
#include <time.h>


C_SVManager::~C_SVManager(void){
	this->svOperatingNormally = svFalse;

}

void C_SVManager::StartAccept(){

	// 接続の受付開始
	listen(this->m_svSockInfo.socket, MAX_CLIENT);

	//// アクセプト開始前に使用する変数の初期化
	memset(&this->m_newClient, 0, sizeof(NEW_CLIENT));
	this->m_newClient.tcpSock.addrLen = sizeof(sockaddr);
	this->m_newClient.udpSock.addrLen = sizeof(sockaddr);

	this->MakeSocket(&m_newClient.tcpSock.socket, SOCKETTYPE::TCP);
	this->MakeSocket(&m_newClient.udpSock.socket, SOCKETTYPE::UDP);

	// アクセプト用のスレッドを起動
	this->m_acceptInfo.hd.TH = (HANDLE)_beginthreadex(NULL, 0, Accept, this, 0, &this->m_acceptInfo.hd.ID);
}

UINT WINAPI  C_SVManager::Accept(void* data){
	C_SVManager*	svManager = (C_SVManager*) data;

	while(svManager->svOperatingNormally){
		printf("クライアント受付中...\n\n");
		svManager->m_newClient.tcpSock.socket = accept( svManager->m_svSockInfo.socket, 
														(struct sockaddr *) &svManager->m_newClient.tcpSock.addr, 
														&svManager->m_newClient.tcpSock.addrLen);

		if (!svManager->p_checkClass->CheckCommError(svManager->m_newClient.tcpSock.socket)) {	 // エラーチェック
			printf("%s とコネクションを受け付けました\n", inet_ntoa(svManager->m_newClient.tcpSock.addr.sin_addr));
			if (svManager->CheckingNewClient()){
				printf("クライアントがタイムアウトしました\n");
			}
		}
	}
	return 0;
}

bool C_SVManager::CheckingNewClient(void){
	FrameWorkMsg		buf;				// 通信用バッファ
	int					sts;
	int					rndNo;				// 乱数格納用
	DWORD				oTime, nTime;		// ping時間計測用
	fd_set				workFds;
	timeval				timeOut;

	srand((unsigned)time(NULL));

	timeOut.tv_sec = TIMEOUT_PING_CHECK_SEC;
	timeOut.tv_usec = TIMEOUT_PING_CHECK_USEC;

	// TCPソケットに受けたconnectの情報を使い、UDPのソケットをconnectする
	//this->Connection(&this->m_newClient.udpSock.socket, &this->m_newClient.tcpSock.addr);

	FD_SET(this->m_newClient.tcpSock.socket, &this->m_newClient.tcpSock.fds);


	printf("クライアントの通信速度を計測します\n");
	oTime = timeGetTime();
	
	// ランダム値を生成し、クライアントに送信（クライアントは規定の計算方法を使い値を変更しその値をサーバーのUDPソケットに対し送信する）
	rndNo = rand() % 100;
	//buf.Msg.Body0.rndNo = rndNo;
	//send(m_newClient.udpSock.socket, buf.data, sizeof(FrameWorkMsg), 0);

	memcpy(&workFds, &this->m_newClient.udpSock.fds, sizeof(fd_set));

	// 一定時間クライアントからの返信がない場合終了
	sts = select(0, &workFds, NULL, NULL, &timeOut);
	if (sts != NULL) {
		// 受信したデータをチェックし、正当な値だった場合新規クライアントとして受け入れる(チェック式はマクロで定義している)
		if (FD_ISSET(this->m_newClient.udpSock.socket, &workFds)){
			recv(m_newClient.udpSock.socket, buf.data, sizeof(FrameWorkMsg), 0);
			nTime = timeGetTime();

			if (ATTESTATION_NO == buf.Msg.Body0.rndNo){
				printf("正規クライアントです\n");

				if ((nTime - oTime) <= LIMIT_PINGTIME){
					printf("クライアントとの通信速度も許容範囲内\n");
					printf("クライアントを追加します\n");
					this->p_dataContainer->AddClient(&m_newClient.tcpSock, &m_newClient.udpSock, (nTime - oTime));
				}
				else{
					printf("クライアントとの通信速度が許容範囲外\n");
					printf("クライアントのゲーム参加を拒否します\n");
				}
			}
			else{
				printf("非正規のクライアントです\n");
				printf("クライアントの接続を拒否します\n");
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
		return true;	// ここでコンストラクタを強制終了
	}
	return false;
}
bool C_SVManager::MakeSocket(SOCKET* sock, SOCKETTYPE type){

	switch (type){
	case SOCKETTYPE::TCP:
		// SOCKETTYPE::UDP通信用のソケットを生成する
		*sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (this->p_checkClass->CheckCommError(sock)){
			printf("TCPソケット生成失敗\n");
			_getch();
			//コンソール削除
			FreeConsole();
			return true;
		}
		break;
	case SOCKETTYPE::UDP:
		// SOCKETTYPE::UDP通信用のソケットを生成する
		*sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (this->p_checkClass->CheckCommError(sock)){
			printf("UDPソケット生成失敗\n");
			_getch();
			//コンソール削除
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
