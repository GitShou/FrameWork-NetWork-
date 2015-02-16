#ifndef ___Stack_DATA_H___
#define ___Stack_DATA_H___

// キューのデータ用クラス
template<typename T>
class C_StackData {
private:
	T* data;
	C_StackData* next; // 次のアドレス
public:
	// コンストラクタ
	C_StackData<T>(const T data, C_StackData *next, int size);
	~C_StackData<T>();

	T*				getData(); // データを返す
	C_StackData<T>*	getNext() const; // 次のアドレスを返す
	void			setNext(C_StackData *next); // アドレスを設定
};
// コンストラクタ
template<typename T>
C_StackData<T>::C_StackData(const T data, C_StackData *next, int size){ 
	this->data = new T[size];
	this->next = next;
}

template<typename T>
C_StackData<T>::~C_StackData(){ 
	delete data;	
}

// データを返す
template<typename T>
T* C_StackData<T>::getData() { 
	return &data; 
}

// 次のアドレスを返す
template<typename T>
C_StackData<T>* C_StackData<T>::getNext() const { 
	return next; 
}

// アドレスを設定
template<typename T>
void C_StackData<T>::setNext(C_StackData *next) {
	this->next = next; 
}

#endif