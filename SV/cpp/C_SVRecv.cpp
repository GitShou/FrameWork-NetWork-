#include "C_SVRecv.h"


C_SVRecv::C_SVRecv(shared_ptr<C_SVDataContainer> p_dataContainer, shared_ptr<C_CommCheck> commCheck){

	this->m_fatalError = error;

	this->p_dataContainer = p_dataContainer;
	this->p_checkClass = commCheck;

	this->MakeRecvThread();		// ��M�X���b�h���N������

	this->workBuf = new char[p_dataContainer->GetDataSize() + sizeof(FrameWorkMsg)];	// ��M�p���[�N�o�b�t�@�𐶐�

	/*** ��M�f�[�^�~�ϗp�̃X�^�b�N������������ ***/
	for (int i = 0; i < MAX_CLIENT; i++){
		this->m_dataStack[i] = new C_Stack<char>(p_dataContainer->GetDataSize() + sizeof(FrameWorkMsg));
	}

	this->m_fatalError = normally;
}
C_SVRecv::~C_SVRecv(void){
	delete this->workBuf;
}


/************************************************************************/
/*		MakeRecvThread
/*			�����F�Ȃ�
/*			�߂�l�F�Ȃ�
/*		�T�v�F���V�[�u�p�̃X���b�h���N��������
/*		�쐬��2013/11/11
/************************************************************************/
void C_SVRecv::MakeRecvThread(){
	this->runRecvThread = true;
	this->m_recvInfo.hd.TH = (HANDLE)_beginthreadex(NULL, 0, RecvThread, this, 0, &this->m_recvInfo.hd.ID);
}


/************************************************************************/
/*		RecvThread
/*			�����Fp_Server(vouid*) �F �����̃A�h���X
/*			�߂�l�F�Ȃ�
/*		�T�v�F�A�N�e�B�u�ȃN���C�A���g����f�[�^���󂯎��i���C���Ƃ͕ʃX���b�h�ŁA��Ɏ�M����Ă���j
/*		�쐬��2013/11/11
/************************************************************************/
UINT WINAPI C_SVRecv::RecvThread(void* p_recv){
	C_SVRecv*			p_recvClass = (C_SVRecv*)p_recv;
	int					sts;

	const FrameWorkMsg*	workFWMsg;
	const FrameWorkMsg* stackData;

	fd_set				workFds;
	timeval				timeOut;
	timeOut.tv_sec = RECV_TIME_OUT_SEC;
	timeOut.tv_usec = RECV_TIME_OUT_USEC;

	while (p_recvClass->runRecvThread){
		for (int i = 0; i < MAX_CLIENT; i++){

			if (p_recvClass->p_dataContainer->GetClientStatus(i)->clActive){
				// �ǂݍ��ݗpworkFds�̏�����
				memcpy(&workFds, p_recvClass->p_dataContainer->GetClientFds(i, SOCKETTYPE::UDP), sizeof(fd_set));

				sts = select(0, &workFds, NULL, NULL, &timeOut);	// select( ���݂͎g�p����Ă��Ȃ��̂łO�ł���, ��M�`�F�b�N�Ȃ炱����workFds, ���M�Ȃ炱��, ???, �ҋ@���� )
				if (p_recvClass->p_checkClass->CheckCommError(sts, i)) {
					continue;
				}
				if (FD_ISSET(p_recvClass->p_dataContainer->GetClientSocket(i, SOCKETTYPE::UDP), &workFds)){
					// �w�肵���\�P�b�g�Ɏ�M��������
					memset(p_recvClass->workBuf, 0, p_recvClass->p_dataContainer->GetDataSize());	// ��M�o�b�t�@�̏�����
					sts = recv(*p_recvClass->p_dataContainer->GetClientSocket(i,SOCKETTYPE::UDP),
								p_recvClass->workBuf,
								p_recvClass->p_dataContainer->GetDataSize(),
								0);

					if (p_recvClass->p_checkClass->CheckCommError(sts)){
						// �G���[����
					}
					else if (sts == 0){
						printf("�N���C�A���g���\�P�b�g����܂���\n");
						// �I���ʒm
						
					}
					else{
						// ��M����
						workFWMsg = (FrameWorkMsg*)&p_recvClass->workBuf;
						if (p_recvClass->m_dataStack[i]->Empty()){	// �X�^�b�N�ɂȂɂ��Ȃ��Ƃ��͂Ƃ肠�����擾
							p_recvClass->m_dataStack[i]->EnStack(p_recvClass->workBuf);
						}
						else{
							stackData = (FrameWorkMsg*)p_recvClass->m_dataStack[i]->GetLastDataPtr();
							if (p_recvClass->p_checkClass->CheckSequenceNo(workFWMsg->Msg.Body1.sequenceNo, stackData->Msg.Body1.sequenceNo)){	// Stack�̍ŐV�f�[�^���A�V�����f�[�^���𔻒�
								p_recvClass->m_dataStack[i]->EnStack(p_recvClass->workBuf);
							}
						}
					}
				}
			}
		}
		Sleep(16);
	}
	return 0;
}

const FatalError	C_SVRecv::GetFatalError(void){
	return this->m_fatalError;
}
