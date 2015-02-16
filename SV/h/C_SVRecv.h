#ifndef ___C_SVRecv_H___
#define ___C_SVRecv_H___

#include "SV_IncludeHeader.h"

const int RECV_TIME_OUT_SEC = 0;		// recv()時のタイムアウト時間（秒単位）
const int RECV_TIME_OUT_USEC = 1000;	// recv()時のタイムアウト時間（ナノ秒単位）

class C_SVRecv
{
private:	// Class
	shared_ptr<C_CommCheck>			p_checkClass;				// このクラス群で発生する通信の異常等をチェックするクラス
	shared_ptr<C_SVDataContainer>	p_dataContainer;			// 通信で取り扱っているデータを蓄積するためのクラス
	C_Stack<char>*					m_dataStack[MAX_CLIENT];	// 通信相手から受信したデータを蓄積する

private:	// Variable
	Thread_Info			m_recvInfo;					// レシーブ用のスレッド情報
	bool				runRecvThread;				// レシーブスレッドが起動していうるかどうかを表す

	char*				workBuf;					// データ受信時に受けとる場所

	FatalError			m_fatalError;				// レシーブの初期化成功フラグ(True:成功)


private:	// Function
	static UINT WINAPI	RecvThread(void* thData);	// レシーブ用のスレッド

public:
	C_SVRecv(shared_ptr<C_SVDataContainer> p_dataContainer, shared_ptr<C_CommCheck> commCheck);
	~C_SVRecv(void);

	void				MakeRecvThread(void);		// レシーブスレッドを起動するための関数

	bool				SetNewData(void);			// コンテナに受信した最新データをセットする
	const FatalError	GetFatalError(void);		// m_fatalErrorを提供

};


#endif