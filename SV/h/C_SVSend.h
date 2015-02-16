#ifndef ___C_SVSEND_H___
#define ___C_SVSEND_H___

#include "SV_ShareStruct.h"
#include "C_SVDataContainer.h"
#include "C_CommCheck.h"
#include "SV_IncludeHeader.h"

class C_SVSend
{
private: // ClassPtr
	shared_ptr<C_CommCheck>			p_checkClass;				// ���̃N���X�Q�Ŕ�������ʐM�ُ̈퓙���`�F�b�N����N���X
	shared_ptr<C_SVDataContainer>	p_dataContainer;			// �ʐM�Ŏ�舵���Ă���f�[�^��~�ς��邽�߂̃N���X

private: // Function
	void InitSender();

private: // Variable
	SOCKET		m_multicastSocket;
	char*		sendBuf;
	FatalError	m_fatalError;

public:
	C_SVSend(shared_ptr<C_SVDataContainer> container, shared_ptr<C_CommCheck> commCheck) : p_dataContainer(container), p_checkClass(commCheck){ InitSender(); };
	~C_SVSend(void);

	bool UniCast(int target, SOCKETTYPE type, char* data, const int dataSize);
	bool MultiCast(char* data, const int dataSize);

	const FatalError	GetFatalError(void);

};

#endif