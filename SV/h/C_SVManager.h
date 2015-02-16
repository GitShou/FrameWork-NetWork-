#ifndef ___C_SVManager_H___
#define ___C_SVManager_H___


//#include <mmsystem.h> // winmm.lib �������N����̂�Y�ꂸ��
#include "SV_IncludeHeader.h"
#include "Manager_PrivateStruct.h"
#include "Manager_PrivateConst.h"
#include "C_SVDataContainer.h"
#include "C_CommCheck.h"
#include "C_SVRecv.h"
#include "C_SVSend.h"

// �T�[�o�[��GUID
static const GUID FrameWorkGUID_Server = { 0x59574e5f, 0xd0a, 0x4012, { 0x83, 0x82, 0xf4, 0xe2, 0x76, 0xfd, 0xc5, 0xa8 } };
//
// �N���C�A���g��GUID�i�R�l�N�V�����𒣂��Ă����N���C�A���g���A�Ή������t���[�����[�N���g�p���Ă��邩���m�F���邽�߂ɗ��p����j
static const GUID FrameWorkGUID_Client = { 0xc39e4436, 0xff6e, 0x4209, { 0x94, 0x94, 0x64, 0x52, 0x90, 0x5d, 0x7a, 0x2 } };


const int TIMEOUT_PING_CHECK_SEC = 0;		// �s���`�F�b�N���̃^�C���A�E�g(�b�P��)
const int TIMEOUT_PING_CHECK_USEC = 32000;	// �s���`�F�b�N���̃^�C���A�E�g(�i�m�b�P��)
class C_SVManager
{
private: // const
	const int m_maxDataSize;				// ���̃}�l�[�W���[���g�p���鎞�̃Q�[���f�[�^�̍ő�T�C�Y(�}�l�[�W���[�̃C���X�^���X�𐶐�����ۂɈ����Ƃ��ēn���ꂽ�l)

private: // Class
	shared_ptr<C_SVRecv>			p_recvClass;		// ��M��S�����Ă���N���X
	shared_ptr<C_SVSend>			p_sendClass;		// ���M��S�����Ă���N���X
	shared_ptr<C_CommCheck>			p_checkClass;		// ���̃N���X�Q�Ŕ�������ʐM�ُ̈퓙���`�F�b�N����N���X
	shared_ptr<C_SVDataContainer>	p_dataContainer;	// �ʐM�Ŏ�舵���Ă���f�[�^��~�ς��邽�߂̃N���X

private: // Variable
	svOperatingNormally		svOperatingNormally;	// �}�l�[�W���[�̐���ғ�
	Sock_Info						m_svSockInfo;			// �T�[�o�[�̎�t�\�P�b�g
	
	Thread_Info					m_acceptInfo;			// �A�N�Z�v�g�v�X���b�h�̏��

	NEW_CLIENT					m_newClient;			// �V�K�N���C�A���g�v���[�N�X�y�[�X

	UINT								m_svSequenceNo;			// �T�[�o�[�̃V�[�P���X�i���o�[

private: // function

	//********** �R���X�g���N�^���s���̂ݎg�p���鏉�����֐� **********//
	void m_InitManager();													// �}�l�[�W���[�̏������֐��i�R���X�g���N�^������������1�x�����Ăяo�����j
	bool m_InitWinsock(WSADATA* m_wd, WORD requiredversion);				// winsock�̏�����					(m_InitManager��1�x�����Ă΂��)
	bool m_InitSock();														// ������accept�p�̊֐��𐶐�		(m_InitManager��1�x�����Ă΂��)
	bool m_CheckingVersion(WSADATA* m_wd, WORD requiredversion);			// winsock�̃o�[�W�����`�F�b�N		(m_InitManager��1�x�����Ă΂��)
	bool m_BindingSocket(SOCKET* sock, sockaddr_in* addr);					// accept�p�̃\�P�b�g���o�C���h����	(m_InitManager��1�x�����Ă΂��)
	//****************************************+***********************//

	bool Connection(SOCKET* sock, sockaddr_in* addr);		// �w�肵���\�P�b�g��connect()���s���܂�
	bool MakeSocket(SOCKET* sock, SOCKETTYPE type);			// �w�肵���^�C�v�̃\�P�b�g�𐶐�����
	
	bool CheckingNewClient();								// �V�K�N���C�A���g����t���A���̑��肪����ȃN���C�A���g�����`�F�b�N����

	void StartAccept();										// �A�N�Z�v�g�v�X���b�h�𗧂��グ��֐�
	static UINT WINAPI  Accept(void* data);					// �A�N�Z�v�g�����Ă���X���b�h

public:
	C_SVManager(int dataSize) : m_maxDataSize(dataSize){m_InitManager();};		// �C�j�V�����C�U�𗘗p���āA���p����ő�f�[�^�T�C�Y��������(���ۂ̏�������m_InitManager())
	~C_SVManager(void);
	bool UnConnectClient(int target);											// �N���C�A���g�̐ؒf
	void UpdateManager(void);													// �e��Ԃ��ŐV�̏�ԂɍX�V����i�T�[�o�[�̃v���O���������ň�ԍŏ��ɌĂяo���j
	bool SendMultiCast(char* data, int dataSize);								// �N���C�A���g�ɃQ�[���f�[�^���M(�}���`�L���X�g)
	bool SendUniCast(int target, SOCKETTYPE type, char* data, int dataSize);	// �N���C�A���g�ɃQ�[���f�[�^���M(���j�L���X�g)
};

#endif