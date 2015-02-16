#ifndef ___SV_CONST_H___
#define ___SV_CONST_H___

typedef enum FatalError{normally = 0, error};

typedef enum clActive { clFalse = 0, clTrue };		// 対象のクライアントがアクティブかどうかを表す（アクセプトされるとTrue, UnConnectが完了するとFalseになる）
typedef enum clCommStatus { GoodNess, CommCheck, ReConnect, UnConnect };	// 通信相手の現在の通信状態を表す
typedef enum SOCKETTYPE{ TCP, UDP };				// ソケットのタイプを表す


#ifdef __SERVER_MANAGER_CPP__
/********* チェック用文字列 *********/
const char* CHECK_MSG = "CheckingActive";
const char* ACTIVE_MSG = "ReturnActive";
const char* MULTICAST_ADDR = "239.1.2.37";	// マルチキャストで使用するアドレス
/************************************/
#else
/********* チェック用文字列 *********/
extern const char* CHECK_MSG;
extern const char* ACTIVE_MSG;
extern const char* MULTICAST_ADDR;	// マルチキャストで使用するアドレス
/************************************/
#endif

const int MAX_CLIENT = 5;					// このクラス群が管理出来るクライアントの最大人数（この値を変えれば任意に人数を変更できるが、大人数になった時の処理は保証できない）
const int ACTIVE_CNT = 10;					// クライアントが正常に接続されていると認識する基準値（相手との通信がタイムアウトになるたびに１減算する）
const int MAX_PORTNO = 65535;				// ポート番号を設定するときに入力できる値の最大値
const int MIN_PORTNO = 0;					// ポート番号を設定するときに入力できる値の最小値
const int CLIENT_PORTNO = 20250;			// クライアントアプリが使用しているポート番号


#endif