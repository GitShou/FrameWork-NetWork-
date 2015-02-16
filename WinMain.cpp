
#include "C_SVManager.h"

//------------------------------------
// マクロ
//------------------------------------
#define		NAME		"TCP_Server"
#define		TITLE		"TCP_Server"
#define		RECT_WIDTH	100
#define		RECT_HEIGHT	50

const char* SERVERIP = "127.0.0.1";
const int	PORTNO = 20250;

#define		USERNAME	"萩森 省吾"

//------------------------------------
// ライブラリ
//------------------------------------
#pragma	comment(lib, "ws2_32.lib")

//------------------------------------
// プロトタイプ
//------------------------------------
LRESULT CALLBACK WndProc(	HWND hWnd,			// ウインドウメッセージ関数 
							UINT message, 
							WPARAM wParam, 
							LPARAM lParam);

//------------------------------------
// グローバル変数
//------------------------------------
bool mainModule;
C_SVManager sv(100);
//------------------------------------
// WinMain関数
//------------------------------------
int APIENTRY WinMain(HINSTANCE 	hInstance, 		// アプリケーションインスタンス値
					 HINSTANCE 	hPrevInstance,	// 意味なし
					 LPSTR 		lpszArgs, 		// 起動時の引数文字列
					 int 		nWinMode)		// ウインドウ表示モード
{
	HWND			hwnd;						// ウインドウハンドル
	WNDCLASSEX		wcex;						// ウインドウクラス構造体

	// ウインドウクラス情報のセット
	wcex.hInstance		= hInstance;			// インスタンス値のセット
	wcex.lpszClassName	= NAME;					// クラス名
	wcex.lpfnWndProc	= (WNDPROC)WndProc;		// ウインドウメッセージ関数
	wcex.style			= 0;					// ウインドウスタイル
	wcex.cbSize 		= sizeof(WNDCLASSEX);	// 構造体のサイズ
	wcex.hIcon			= LoadIcon((HINSTANCE)NULL, IDI_APPLICATION);	// ラージアイコン
	wcex.hIconSm		= LoadIcon((HINSTANCE)NULL, IDI_WINLOGO);		// スモールアイコン
	wcex.hCursor		= LoadCursor((HINSTANCE)NULL, IDC_ARROW);		// カーソルスタイル
	wcex.lpszMenuName	= 0; 					// メニューなし
	wcex.cbClsExtra		= 0;					// エキストラなし
	wcex.cbWndExtra		= 0;					
	wcex.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);		// 背景色白

	if (!RegisterClassEx(&wcex)) return FALSE;	// ウインドウクラスの登録

	hwnd = CreateWindow(NAME, 				// ウインドウクラスの名前
				TITLE, 							// タイトル
				WS_CAPTION | WS_SYSMENU,		// ウインドウスタイル
				100,100,						// X座標,Y座標
				640,480,						// ウインドウサイズ
				HWND_DESKTOP, 					// 親ウインドウなし
				(HMENU)NULL, 					// メニューなし
				hInstance, 						// インスタンスハンドル
				(LPVOID)NULL);					// 追加引数なし

	if (!hwnd) return FALSE;


	while (1){ Sleep(100); }


	// ウインドウを表示する
	ShowWindow(hwnd, nWinMode);
	UpdateWindow(hwnd);

	return 0;
}
//------------------------------------
// ウインドウプロシージャ
//------------------------------------
LRESULT WINAPI WndProc(HWND hwnd, 				// ウインドウハンドル値
						UINT message,			// メッセージ識別子
						WPARAM wParam,			// 付帯情報１
						LPARAM lParam)			// 付帯情報２
{
	switch (message){
		case WM_KEYDOWN:
			switch(wParam)
			{
				case VK_ESCAPE:
					break;

			}
		break;

		case WM_DESTROY:
			break;

		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
