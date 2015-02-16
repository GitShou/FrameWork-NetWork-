#include "C_SVManager.h"

#pragma warning(disable : 4996)

void C_SVManager::m_InitManager(){
	WSADATA		m_wd;								// ＷＳＡＳＴＡＲＴＵＰ用
	WORD		requiredversion = MAKEWORD(2,2);	// このプログラムが要求するバージョン

	this->svOperatingNormally = svFalse;
	this->m_svSequenceNo = 0;

	// 情報表示用コンソールウインドウ表示
	AllocConsole();
	freopen( "CON", "r", stdin  );  // 標準入力を割り当てる
	freopen( "CON", "w", stdout );  // 標準出力を割り当てる

	// マネージャーの初期化を行う
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
	printf("受付用ソケットのバインド開始\n");
	if (this->m_BindingSocket(&this->m_svSockInfo.socket, &this->m_svSockInfo.addr)){
		exit(1);
	}

	// 使用するその他クラスの初期化
	this->p_dataContainer.reset(new C_SVDataContainer(this->m_maxDataSize));
	if (this->p_dataContainer->GetFatalError()){
		printf("コンテナ初期化失敗\n");
	}
	this->p_recvClass.reset(new C_SVRecv(this->p_dataContainer, this->p_checkClass));
	if (this->p_recvClass->GetFatalError()){
		printf("レシーバー初期化失敗\n");
	}
	this->p_sendClass.reset(new C_SVSend(this->p_dataContainer, this->p_checkClass));
	if (this->p_sendClass->GetFatalError()){
		printf("センダー初期化失敗\n");
	}

	printf("マネージャー及び、各クラスの初期化成功\n");
	this->svOperatingNormally = svTrue;		// マネージャーが無事生成できたことを記す

	this->StartAccept();


}

bool C_SVManager::m_InitWinsock(WSADATA* m_wd, WORD requiredversion){
	int sts;
	printf("WinSock初期化開始\n");

	// Windows の場合
	sts = WSAStartup(requiredversion, m_wd);
	if( this->p_checkClass->CheckCommError(sts) )
	{
		printf( "WINSOCK初期化失敗\n");
		getch();
		//コンソール削除
		FreeConsole();
		return true;
	}
	return false;
}
bool C_SVManager::m_CheckingVersion(WSADATA* m_wd, WORD requiredversion){
	printf("バージョンチェック\n");
	// バージョンチェック
	if(m_wd->wVersion != requiredversion)
	{
		printf("バージョンエラー");
		getch();
		//コンソール削除
		FreeConsole();
		return true;	// ここでコンストラクタを強制終了
	}
	return false;
}
bool C_SVManager::m_InitSock(){
	int flg = true;
	int	portNo;

	printf("ソケットの初期化開始\n");

	// ソケットの生成（SOCKETTYPE::TCP）
	this->MakeSocket(&this->m_svSockInfo.socket, SOCKETTYPE::TCP);

	// サーバーの使用するポート番号を設定する（正規値が入力されるまでループ）
	this->m_svSockInfo.addrLen = sizeof(this->m_svSockInfo.addr);
	printf("マネージャーの受付用ソケットを生成しました\n");
	// サーバー情報を入力
	printf("今回このサーバーで使用するポート番号を入力してください。\n(推奨番号：49152～65535)");
	while (flg){
		scanf_s("%d", &portNo);
		if (portNo > MAX_PORTNO || portNo < MIN_PORTNO){
			printf("値が不正です。\n再度入力してください。");
		}
		else{
			flg = false;
		}
	}	
	// 自分のアドレスを設定
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

	// ソケットのバインド
	sts = bind(*sock, (struct sockaddr *) addr, addrLen);
	if (this->p_checkClass->CheckCommError(sts)){
		printf("バインド失敗\n");
		getch();
		FreeConsole();	//コンソール削除
		return true;
	}
	return false;
}