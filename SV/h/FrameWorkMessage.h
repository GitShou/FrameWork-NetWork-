#ifndef ___FRAMEWORKMESSAGE_H___
#define ___FRAMEWORKMESSAGE_H___

// メッセージヘッダー
struct	_MSGHEADER{
	short	type;	// メッセージタイプ 0:初回　1:通常　2:終了
};

// メッセージボディ（メッセージタイプ０）
struct	_MSGBODY0{
	int rndNo;
};

// メッセージボディ（メッセージタイプ１）
struct	_MSGBODY1{
	unsigned int sequenceNo;
};


// メッセージの構造
struct	_MESSAGE{
	struct	_MSGHEADER	Header;
	union{
		struct	_MSGBODY0	Body0;		// 初回
		struct	_MSGBODY1	Body1;		// 通常

	};
};

// 送受信メッセージ構造体
struct	FrameWorkMsg{
	union{
		struct	_MESSAGE  Msg;
		char	data[sizeof(_MESSAGE)];
	};
};

#endif