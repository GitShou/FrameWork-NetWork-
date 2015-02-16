#ifndef ___C_SVDATABASE_H___
#define ___C_SVDATABASE_H___
using namespace std;

#include <stdio.h>
#include <vector>
#include "SV_ShareStruct.h"
#include "SV_Const.h"

// ���̃N���X�����Ȕ��f�Ńf�[�^�������������肷�邱�Ƃ͂Ȃ�

class C_SVDataContainer 
{
	friend class C_SVManager;		// �}�l�[�W���[�͎��R�ɃA�N�Z�X�\

private: // const
	const int maxDataSize;

private:// Variable
	vector<Client_Info> clInfo;
	FatalError	m_fatalError;

private:// Function
	void InitDataContainer(void);

	// �N���C�A���g�̒ǉ��폜�̓t�����h�w�肵�Ă���Manager�N���X�������s�ł��Ȃ�
	bool AddClient(Sock_Info* tcpSock, Sock_Info* udpSock, int pingTime);
	void DeleteClient(int target);

public:	// Initialize
	C_SVDataContainer(int dataSize) : maxDataSize(dataSize){ InitDataContainer(); };
	~C_SVDataContainer(void);

public: // Setter
	bool SetClientLastData (int target, char* data);

public: // Getter
	/****************** �N���C�A���g���̃Q�b�^�[ *******************/
	const SOCKET*			GetClientSocket(int target, SOCKETTYPE sockType);		// �\�P�b�g���擾
	const FD_SET*			GetClientFds(int target, SOCKETTYPE sockType);			// FDS���擾
	const sockaddr_in*		GetClientAddr(int target, SOCKETTYPE sockType);			// �A�h���X���擾
	const ClientStatus*		GetClientStatus(int target);							// �X�e�[�^�X�擾
	const int				GetClientActiveCnt(int target);							// �A�N�e�B�u�J�E���g�擾
	const ULONG				GetClientSequenceNo(int target);						// �ŐV�V�[�P���X�i���o�[�擾
	const int				GetClientPingTime(int target);							// �s���`�F�b�N�ł����������Ԃ��擾
	const char*				GetClientGameData(int target);							// �ŐV�̃Q�[���f�[�^�擾
	/*****************************************************************/

	const UINT				GetSVSequenceNo(void);
	const int				GetDataSize(void);

	const FatalError		GetFatalError(void);

};

#endif
