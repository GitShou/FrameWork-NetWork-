#ifndef ___Stack_CLASS_H___
#define ___Stack_CLASS_H___

#include "C_StackData.h"

#define MAX_Stack 10

//�yC_Stack�N���X�z
// �L���[�̊Ǘ��p�N���X
template<typename T>
class C_Stack{
private:
	C_StackData<T>* pf; // �P�A�����X�g�̐擪
	C_StackData<T>* pe; // �P�A�����X�g�̖���

	const int dataSize; // �f�[�^1�̃f�[�^�T�C�Y
	int length;			// ���݊Ǘ����Ă���f�[�^�̒���

private:
	void Init_Stack();

public:
	C_Stack<T>(int size) : dataSize(size){Init_Stack();}; // �R���X�g���N�^
	~C_Stack<T>(); // �f�X�g���N�^

	void		EnStack(const T* data); // �f�[�^�̒ǉ�
	void		DeStack(); // �擪�v�f�̍폜

	const T*	GetLastDataPtr(); // �擪�v�f�̎擾
	int			Size() const; // �f�[�^����Ԃ�
	bool		Empty() const; // �L���[����̂Ƃ��̂� true
	
	int			GetDataSize(){ return this->dataSize; };
};

// �R���X�g���N�^
template<typename T>
void C_Stack<T>::Init_Stack(){ 
	this->pf = pe = NULL;
	this->length = 0;
}; 
// �f�X�g���N�^
template<typename T>
C_Stack<T>::~C_Stack(){ 
	// �L���[�ɂ��܂��Ă���f�[�^��S�ĉ��
	while(!this->Empty()){
		this->DeStack();
	}
}

// �L���[�̒ǉ�
template<typename T>
void C_Stack<T>::EnStack(const T* data){
	C_StackData<T>* C_NewData;
	C_NewData = new C_StackData<T>(*data, NULL, this->dataSize);

	if(this->Empty()){ // ���X�g�ɉ����Ȃ���
		this->pf = C_NewData;
		this->pe = C_NewData;
		this->length += dataSize;

	}else if(MAX_Stack <= length / this->dataSize ){ // ���X�g�ɑ��݂���f�[�^�̌����ő�
		this->DeStack();	//�擪�̃f�[�^���폜
		this->pe->setNext(C_NewData);
		this->pe = C_NewData;

	}else{
		this->pe->setNext(C_NewData);
		this->pe = C_NewData;
		this->length += dataSize;
	}
}

// �L���[�̍Ō�����擾
template<typename T>
const T* C_Stack<T>::GetLastDataPtr(){
	return (char*)this->pe;
}

// �擪���폜
template<typename T>
void C_Stack<T>::DeStack(){
	C_StackData<T>* work = this->pf;
	this->pf = this->pf->getNext();
	delete(work);
	length -= sizeof(C_StackData<T>);
}

// �L���[�̃T�C�Y���擾
template<typename T>
int C_Stack<T>::Size()const{
	return length;
}

// �L���[�Ƀf�[�^�����݂��邩�`�F�b�N
template<typename T>
bool C_Stack<T>::Empty()const{

	if (this->length <= 0 && this->pf != NULL){
		while (1){
			MessageBox(NULL, "length��0�ȉ��ł����Apf��NULL�ł͂���܂���B", "�X�^�b�N�ُ�̌��o", MB_OK);
			Sleep(1000);
		}
	}

	if(this->length <= 0){
		return true;
	}
	return false;
}

#endif