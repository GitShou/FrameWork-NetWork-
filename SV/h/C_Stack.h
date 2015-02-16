#ifndef ___Stack_CLASS_H___
#define ___Stack_CLASS_H___

#include "C_StackData.h"

#define MAX_Stack 10

//【C_Stackクラス】
// キューの管理用クラス
template<typename T>
class C_Stack{
private:
	C_StackData<T>* pf; // 単連結リストの先頭
	C_StackData<T>* pe; // 単連結リストの末尾

	const int dataSize; // データ1つのデータサイズ
	int length;			// 現在管理しているデータの長さ

private:
	void Init_Stack();

public:
	C_Stack<T>(int size) : dataSize(size){Init_Stack();}; // コンストラクタ
	~C_Stack<T>(); // デストラクタ

	void		EnStack(const T* data); // データの追加
	void		DeStack(); // 先頭要素の削除

	const T*	GetLastDataPtr(); // 先頭要素の取得
	int			Size() const; // データ長を返す
	bool		Empty() const; // キューが空のときのみ true
	
	int			GetDataSize(){ return this->dataSize; };
};

// コンストラクタ
template<typename T>
void C_Stack<T>::Init_Stack(){ 
	this->pf = pe = NULL;
	this->length = 0;
}; 
// デストラクタ
template<typename T>
C_Stack<T>::~C_Stack(){ 
	// キューにたまっているデータを全て解放
	while(!this->Empty()){
		this->DeStack();
	}
}

// キューの追加
template<typename T>
void C_Stack<T>::EnStack(const T* data){
	C_StackData<T>* C_NewData;
	C_NewData = new C_StackData<T>(*data, NULL, this->dataSize);

	if(this->Empty()){ // リストに何もない時
		this->pf = C_NewData;
		this->pe = C_NewData;
		this->length += dataSize;

	}else if(MAX_Stack <= length / this->dataSize ){ // リストに存在するデータの個数が最大
		this->DeStack();	//先頭のデータを削除
		this->pe->setNext(C_NewData);
		this->pe = C_NewData;

	}else{
		this->pe->setNext(C_NewData);
		this->pe = C_NewData;
		this->length += dataSize;
	}
}

// キューの最後尾を取得
template<typename T>
const T* C_Stack<T>::GetLastDataPtr(){
	return (char*)this->pe;
}

// 先頭を削除
template<typename T>
void C_Stack<T>::DeStack(){
	C_StackData<T>* work = this->pf;
	this->pf = this->pf->getNext();
	delete(work);
	length -= sizeof(C_StackData<T>);
}

// キューのサイズを取得
template<typename T>
int C_Stack<T>::Size()const{
	return length;
}

// キューにデータが存在するかチェック
template<typename T>
bool C_Stack<T>::Empty()const{

	if (this->length <= 0 && this->pf != NULL){
		while (1){
			MessageBox(NULL, "lengthが0以下ですが、pfがNULLではありません。", "スタック異常の検出", MB_OK);
			Sleep(1000);
		}
	}

	if(this->length <= 0){
		return true;
	}
	return false;
}

#endif