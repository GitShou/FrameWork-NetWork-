#ifndef ___Stack_DATA_H___
#define ___Stack_DATA_H___

// �L���[�̃f�[�^�p�N���X
template<typename T>
class C_StackData {
private:
	T* data;
	C_StackData* next; // ���̃A�h���X
public:
	// �R���X�g���N�^
	C_StackData<T>(const T data, C_StackData *next, int size);
	~C_StackData<T>();

	T*				getData(); // �f�[�^��Ԃ�
	C_StackData<T>*	getNext() const; // ���̃A�h���X��Ԃ�
	void			setNext(C_StackData *next); // �A�h���X��ݒ�
};
// �R���X�g���N�^
template<typename T>
C_StackData<T>::C_StackData(const T data, C_StackData *next, int size){ 
	this->data = new T[size];
	this->next = next;
}

template<typename T>
C_StackData<T>::~C_StackData(){ 
	delete data;	
}

// �f�[�^��Ԃ�
template<typename T>
T* C_StackData<T>::getData() { 
	return &data; 
}

// ���̃A�h���X��Ԃ�
template<typename T>
C_StackData<T>* C_StackData<T>::getNext() const { 
	return next; 
}

// �A�h���X��ݒ�
template<typename T>
void C_StackData<T>::setNext(C_StackData *next) {
	this->next = next; 
}

#endif