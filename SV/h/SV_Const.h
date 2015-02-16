#ifndef ___SV_CONST_H___
#define ___SV_CONST_H___

typedef enum FatalError{normally = 0, error};

typedef enum clActive { clFalse = 0, clTrue };		// �Ώۂ̃N���C�A���g���A�N�e�B�u���ǂ�����\���i�A�N�Z�v�g������True, UnConnect�����������False�ɂȂ�j
typedef enum clCommStatus { GoodNess, CommCheck, ReConnect, UnConnect };	// �ʐM����̌��݂̒ʐM��Ԃ�\��
typedef enum SOCKETTYPE{ TCP, UDP };				// �\�P�b�g�̃^�C�v��\��


#ifdef __SERVER_MANAGER_CPP__
/********* �`�F�b�N�p������ *********/
const char* CHECK_MSG = "CheckingActive";
const char* ACTIVE_MSG = "ReturnActive";
const char* MULTICAST_ADDR = "239.1.2.37";	// �}���`�L���X�g�Ŏg�p����A�h���X
/************************************/
#else
/********* �`�F�b�N�p������ *********/
extern const char* CHECK_MSG;
extern const char* ACTIVE_MSG;
extern const char* MULTICAST_ADDR;	// �}���`�L���X�g�Ŏg�p����A�h���X
/************************************/
#endif

const int MAX_CLIENT = 5;					// ���̃N���X�Q���Ǘ��o����N���C�A���g�̍ő�l���i���̒l��ς���ΔC�ӂɐl����ύX�ł��邪�A��l���ɂȂ������̏����͕ۏ؂ł��Ȃ��j
const int ACTIVE_CNT = 10;					// �N���C�A���g������ɐڑ�����Ă���ƔF�������l�i����Ƃ̒ʐM���^�C���A�E�g�ɂȂ邽�тɂP���Z����j
const int MAX_PORTNO = 65535;				// �|�[�g�ԍ���ݒ肷��Ƃ��ɓ��͂ł���l�̍ő�l
const int MIN_PORTNO = 0;					// �|�[�g�ԍ���ݒ肷��Ƃ��ɓ��͂ł���l�̍ŏ��l
const int CLIENT_PORTNO = 20250;			// �N���C�A���g�A�v�����g�p���Ă���|�[�g�ԍ�


#endif