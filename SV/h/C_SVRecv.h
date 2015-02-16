#ifndef ___C_SVRecv_H___
#define ___C_SVRecv_H___

#include "SV_IncludeHeader.h"

const int RECV_TIME_OUT_SEC = 0;		// recv()���̃^�C���A�E�g���ԁi�b�P�ʁj
const int RECV_TIME_OUT_USEC = 1000;	// recv()���̃^�C���A�E�g���ԁi�i�m�b�P�ʁj

class C_SVRecv
{
private:	// Class
	shared_ptr<C_CommCheck>			p_checkClass;				// ���̃N���X�Q�Ŕ�������ʐM�ُ̈퓙���`�F�b�N����N���X
	shared_ptr<C_SVDataContainer>	p_dataContainer;			// �ʐM�Ŏ�舵���Ă���f�[�^��~�ς��邽�߂̃N���X
	C_Stack<char>*					m_dataStack[MAX_CLIENT];	// �ʐM���肩���M�����f�[�^��~�ς���

private:	// Variable
	Thread_Info			m_recvInfo;					// ���V�[�u�p�̃X���b�h���
	bool				runRecvThread;				// ���V�[�u�X���b�h���N�����Ă����邩�ǂ�����\��

	char*				workBuf;					// �f�[�^��M���Ɏ󂯂Ƃ�ꏊ

	FatalError			m_fatalError;				// ���V�[�u�̏����������t���O(True:����)


private:	// Function
	static UINT WINAPI	RecvThread(void* thData);	// ���V�[�u�p�̃X���b�h

public:
	C_SVRecv(shared_ptr<C_SVDataContainer> p_dataContainer, shared_ptr<C_CommCheck> commCheck);
	~C_SVRecv(void);

	void				MakeRecvThread(void);		// ���V�[�u�X���b�h���N�����邽�߂̊֐�

	bool				SetNewData(void);			// �R���e�i�Ɏ�M�����ŐV�f�[�^���Z�b�g����
	const FatalError	GetFatalError(void);		// m_fatalError���

};


#endif