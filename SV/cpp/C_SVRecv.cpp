#include "C_SVRecv.h"


C_SVRecv::C_SVRecv(shared_ptr<C_SVDataContainer> p_dataContainer, shared_ptr<C_CommCheck> commCheck){

	this->m_fatalError = error;

	this->p_dataContainer = p_dataContainer;
	this->p_checkClass = commCheck;

	this->MakeRecvThread();		// 受信スレッドを起動する

	this->workBuf = new char[p_dataContainer->GetDataSize() + sizeof(FrameWorkMsg)];	// 受信用ワークバッファを生成

	/*** 受信データ蓄積用のスタックを初期化する ***/
	for (int i = 0; i < MAX_CLIENT; i++){
		this->m_dataStack[i] = new C_Stack<char>(p_dataContainer->GetDataSize() + sizeof(FrameWorkMsg));
	}

	this->m_fatalError = normally;
}
C_SVRecv::~C_SVRecv(void){
	delete this->workBuf;
}


/************************************************************************/
/*		MakeRecvThread
/*			引数：なし
/*			戻り値：なし
/*		概要：レシーブ用のスレッドを起動させる
/*		作成日2013/11/11
/************************************************************************/
void C_SVRecv::MakeRecvThread(){
	this->runRecvThread = true;
	this->m_recvInfo.hd.TH = (HANDLE)_beginthreadex(NULL, 0, RecvThread, this, 0, &this->m_recvInfo.hd.ID);
}


/************************************************************************/
/*		RecvThread
/*			引数：p_Server(vouid*) ： 自分のアドレス
/*			戻り値：なし
/*		概要：アクティブなクライアントからデータを受け取る（メインとは別スレッドで、常に受信されている）
/*		作成日2013/11/11
/************************************************************************/
UINT WINAPI C_SVRecv::RecvThread(void* p_recv){
	C_SVRecv*			p_recvClass = (C_SVRecv*)p_recv;
	int					sts;

	const FrameWorkMsg*	workFWMsg;
	const FrameWorkMsg* stackData;

	fd_set				workFds;
	timeval				timeOut;
	timeOut.tv_sec = RECV_TIME_OUT_SEC;
	timeOut.tv_usec = RECV_TIME_OUT_USEC;

	while (p_recvClass->runRecvThread){
		for (int i = 0; i < MAX_CLIENT; i++){

			if (p_recvClass->p_dataContainer->GetClientStatus(i)->clActive){
				// 読み込み用workFdsの初期化
				memcpy(&workFds, p_recvClass->p_dataContainer->GetClientFds(i, SOCKETTYPE::UDP), sizeof(fd_set));

				sts = select(0, &workFds, NULL, NULL, &timeOut);	// select( 現在は使用されていないので０でいい, 受信チェックならここにworkFds, 送信ならここ, ???, 待機時間 )
				if (p_recvClass->p_checkClass->CheckCommError(sts, i)) {
					continue;
				}
				if (FD_ISSET(p_recvClass->p_dataContainer->GetClientSocket(i, SOCKETTYPE::UDP), &workFds)){
					// 指定したソケットに受信があった
					memset(p_recvClass->workBuf, 0, p_recvClass->p_dataContainer->GetDataSize());	// 受信バッファの初期化
					sts = recv(*p_recvClass->p_dataContainer->GetClientSocket(i,SOCKETTYPE::UDP),
								p_recvClass->workBuf,
								p_recvClass->p_dataContainer->GetDataSize(),
								0);

					if (p_recvClass->p_checkClass->CheckCommError(sts)){
						// エラー処理
					}
					else if (sts == 0){
						printf("クライアントがソケットを閉じました\n");
						// 終了通知
						
					}
					else{
						// 受信成功
						workFWMsg = (FrameWorkMsg*)&p_recvClass->workBuf;
						if (p_recvClass->m_dataStack[i]->Empty()){	// スタックになにもないときはとりあえず取得
							p_recvClass->m_dataStack[i]->EnStack(p_recvClass->workBuf);
						}
						else{
							stackData = (FrameWorkMsg*)p_recvClass->m_dataStack[i]->GetLastDataPtr();
							if (p_recvClass->p_checkClass->CheckSequenceNo(workFWMsg->Msg.Body1.sequenceNo, stackData->Msg.Body1.sequenceNo)){	// Stackの最新データより、新しいデータかを判定
								p_recvClass->m_dataStack[i]->EnStack(p_recvClass->workBuf);
							}
						}
					}
				}
			}
		}
		Sleep(16);
	}
	return 0;
}

const FatalError	C_SVRecv::GetFatalError(void){
	return this->m_fatalError;
}
