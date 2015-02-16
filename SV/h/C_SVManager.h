#ifndef ___C_SVManager_H___
#define ___C_SVManager_H___


//#include <mmsystem.h> // winmm.lib をリンクするのを忘れずに
#include "SV_IncludeHeader.h"
#include "Manager_PrivateStruct.h"
#include "Manager_PrivateConst.h"
#include "C_SVDataContainer.h"
#include "C_CommCheck.h"
#include "C_SVRecv.h"
#include "C_SVSend.h"

// サーバーのGUID
static const GUID FrameWorkGUID_Server = { 0x59574e5f, 0xd0a, 0x4012, { 0x83, 0x82, 0xf4, 0xe2, 0x76, 0xfd, 0xc5, 0xa8 } };
//
// クライアントのGUID（コネクションを張ってきたクライアントが、対応したフレームワークを使用しているかを確認するために利用する）
static const GUID FrameWorkGUID_Client = { 0xc39e4436, 0xff6e, 0x4209, { 0x94, 0x94, 0x64, 0x52, 0x90, 0x5d, 0x7a, 0x2 } };


const int TIMEOUT_PING_CHECK_SEC = 0;		// ピンチェック時のタイムアウト(秒単位)
const int TIMEOUT_PING_CHECK_USEC = 32000;	// ピンチェック時のタイムアウト(ナノ秒単位)
class C_SVManager
{
private: // const
	const int m_maxDataSize;				// このマネージャーを使用する時のゲームデータの最大サイズ(マネージャーのインスタンスを生成する際に引数として渡された値)

private: // Class
	shared_ptr<C_SVRecv>			p_recvClass;		// 受信を担当しているクラス
	shared_ptr<C_SVSend>			p_sendClass;		// 送信を担当しているクラス
	shared_ptr<C_CommCheck>			p_checkClass;		// このクラス群で発生する通信の異常等をチェックするクラス
	shared_ptr<C_SVDataContainer>	p_dataContainer;	// 通信で取り扱っているデータを蓄積するためのクラス

private: // Variable
	svOperatingNormally		svOperatingNormally;	// マネージャーの正常稼働
	Sock_Info						m_svSockInfo;			// サーバーの受付ソケット
	
	Thread_Info					m_acceptInfo;			// アクセプト要スレッドの情報

	NEW_CLIENT					m_newClient;			// 新規クライアント要ワークスペース

	UINT								m_svSequenceNo;			// サーバーのシーケンスナンバー

private: // function

	//********** コンストラクタ実行時のみ使用する初期化関数 **********//
	void m_InitManager();													// マネージャーの初期化関数（コンストラクタが走った時に1度だけ呼び出される）
	bool m_InitWinsock(WSADATA* m_wd, WORD requiredversion);				// winsockの初期化					(m_InitManagerで1度だけ呼ばれる)
	bool m_InitSock();														// 自分のaccept用の関数を生成		(m_InitManagerで1度だけ呼ばれる)
	bool m_CheckingVersion(WSADATA* m_wd, WORD requiredversion);			// winsockのバージョンチェック		(m_InitManagerで1度だけ呼ばれる)
	bool m_BindingSocket(SOCKET* sock, sockaddr_in* addr);					// accept用のソケットをバインドする	(m_InitManagerで1度だけ呼ばれる)
	//****************************************+***********************//

	bool Connection(SOCKET* sock, sockaddr_in* addr);		// 指定したソケットにconnect()を行います
	bool MakeSocket(SOCKET* sock, SOCKETTYPE type);			// 指定したタイプのソケットを生成する
	
	bool CheckingNewClient();								// 新規クライアントを受付時、その相手が正常なクライアントかをチェックする

	void StartAccept();										// アクセプト要スレッドを立ち上げる関数
	static UINT WINAPI  Accept(void* data);					// アクセプトをしているスレッド

public:
	C_SVManager(int dataSize) : m_maxDataSize(dataSize){m_InitManager();};		// イニシャライザを利用して、利用する最大データサイズを初期化(実際の初期化はm_InitManager())
	~C_SVManager(void);
	bool UnConnectClient(int target);											// クライアントの切断
	void UpdateManager(void);													// 各状態を最新の状態に更新する（サーバーのプログラム部分で一番最初に呼び出す）
	bool SendMultiCast(char* data, int dataSize);								// クライアントにゲームデータ送信(マルチキャスト)
	bool SendUniCast(int target, SOCKETTYPE type, char* data, int dataSize);	// クライアントにゲームデータ送信(ユニキャスト)
};

#endif