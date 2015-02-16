#ifndef ___SV_COMMONSTRUCU_H___
#define ___SV_COMMONSTRUCU_H___

using namespace std;

#include <WinSock2.h>
#include <vector>
#include "SV_Const.h"
#include "C_Stack.h"

typedef struct {
	SOCKET			socket;
	sockaddr_in		addr;
	int				addrLen;
	FD_SET			fds;				// fdsのオリジナル　タイムアウトにこの変数は直接使用しない
}Sock_Info;
typedef struct{
	clActive		clActive;			// アクティブフラグ
	clCommStatus	clCommStatus;		// 通信の状態	
}ClientStatus;

/***** スレッド用構造体 *****/
typedef struct{
	HANDLE	TH;
	UINT	ID;
}Thread_Handle;
typedef struct{
	void* p_Server;
	int target;
}Thread_Data;

typedef struct{
	Thread_Handle	hd;
	Thread_Data		thData;
}Thread_Info;
/***************************/

typedef struct{
	Sock_Info		tcpSockInfo;		// ソケット情報
	Sock_Info		udpSockInfo;		// ソケット情報
	ClientStatus	clStatus;			// クライアントのステータス
	int				commActiveCnt;		// アクティブ許容値	(初期値10で、タイムアウト1回につき-1　０でアクティブチェックを行う)
	ULONG			sequenceNo;			// サーバーに到着した最新のシーケンス値
	char*			lastGameData;		// プレイヤーから受信したデータの最新データ
	int				pingTime;			// アクセプト時に計測した通信時間
}Client_Info;

#endif