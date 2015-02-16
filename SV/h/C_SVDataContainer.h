#ifndef ___C_SVDATABASE_H___
#define ___C_SVDATABASE_H___
using namespace std;

#include <stdio.h>
#include <vector>
#include "SV_ShareStruct.h"
#include "SV_Const.h"

// このクラスが自己判断でデータを書き換えたりすることはない

class C_SVDataContainer 
{
	friend class C_SVManager;		// マネージャーは自由にアクセス可能

private: // const
	const int maxDataSize;

private:// Variable
	vector<Client_Info> clInfo;
	FatalError	m_fatalError;

private:// Function
	void InitDataContainer(void);

	// クライアントの追加削除はフレンド指定しているManagerクラスしか実行できない
	bool AddClient(Sock_Info* tcpSock, Sock_Info* udpSock, int pingTime);
	void DeleteClient(int target);

public:	// Initialize
	C_SVDataContainer(int dataSize) : maxDataSize(dataSize){ InitDataContainer(); };
	~C_SVDataContainer(void);

public: // Setter
	bool SetClientLastData (int target, char* data);

public: // Getter
	/****************** クライアント情報のゲッター *******************/
	const SOCKET*			GetClientSocket(int target, SOCKETTYPE sockType);		// ソケットを取得
	const FD_SET*			GetClientFds(int target, SOCKETTYPE sockType);			// FDSを取得
	const sockaddr_in*		GetClientAddr(int target, SOCKETTYPE sockType);			// アドレスを取得
	const ClientStatus*		GetClientStatus(int target);							// ステータス取得
	const int				GetClientActiveCnt(int target);							// アクティブカウント取得
	const ULONG				GetClientSequenceNo(int target);						// 最新シーケンスナンバー取得
	const int				GetClientPingTime(int target);							// ピンチェックでかかった時間を取得
	const char*				GetClientGameData(int target);							// 最新のゲームデータ取得
	/*****************************************************************/

	const UINT				GetSVSequenceNo(void);
	const int				GetDataSize(void);

	const FatalError		GetFatalError(void);

};

#endif
