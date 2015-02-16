#ifndef ___SV_COMMONSTRUCU_H___
#define ___SV_COMMONSTRUCU_H___

using namespace std;

#include <WinSock2.h>
#include <vector>
#include "SV_Const.h"
#include "C_Stack.h"

typedef struct {
	SOCKET			socket;
	sockaddr_in		addr;
	int				addrLen;
	FD_SET			fds;				// fds�̃I���W�i���@�^�C���A�E�g�ɂ��̕ϐ��͒��ڎg�p���Ȃ�
}Sock_Info;
typedef struct{
	clActive		clActive;			// �A�N�e�B�u�t���O
	clCommStatus	clCommStatus;		// �ʐM�̏��	
}ClientStatus;

/***** �X���b�h�p�\���� *****/
typedef struct{
	HANDLE	TH;
	UINT	ID;
}Thread_Handle;
typedef struct{
	void* p_Server;
	int target;
}Thread_Data;

typedef struct{
	Thread_Handle	hd;
	Thread_Data		thData;
}Thread_Info;
/***************************/

typedef struct{
	Sock_Info		tcpSockInfo;		// �\�P�b�g���
	Sock_Info		udpSockInfo;		// �\�P�b�g���
	ClientStatus	clStatus;			// �N���C�A���g�̃X�e�[�^�X
	int				commActiveCnt;		// �A�N�e�B�u���e�l	(�����l10�ŁA�^�C���A�E�g1��ɂ�-1�@�O�ŃA�N�e�B�u�`�F�b�N���s��)
	ULONG			sequenceNo;			// �T�[�o�[�ɓ��������ŐV�̃V�[�P���X�l
	char*			lastGameData;		// �v���C���[�����M�����f�[�^�̍ŐV�f�[�^
	int				pingTime;			// �A�N�Z�v�g���Ɍv�������ʐM����
}Client_Info;

#endif