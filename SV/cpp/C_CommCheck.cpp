#include "C_CommCheck.h"

C_CommCheck::C_CommCheck(){


	this->errData[0] = { WSANOTINITIALISED, "A successful WSAStartup must occur before using this function." };
	this->errData[1] = { WSAENETDOWN, "The Windows Sockets implementation has detected that the network " "subsystem has failed." };
	this->errData[2] = { WSAENOTCONN, "The socket is not connected." };
	this->errData[3] = { WSAEINTR, "The (blocking) call was canceled using WSACancelBlockingCall." };
	this->errData[4] = { WSAEINPROGRESS, "A blocking Windows Sockets operation is in progress." };
	this->errData[5] = { WSAENOTSOCK, "The descriptor is not a socket." };
	this->errData[6] = { WSAEOPNOTSUPP, "MSG_OOB was specified, but the socket is not of type SOCK_STREAM." };
	this->errData[7] = { WSAESHUTDOWN, "The socket has been shut down; it is not possible to recv on a socket" " after shutdown has been invoked with how set to 0 or 2." };
	this->errData[8] = { WSAEWOULDBLOCK, "The socket is marked as nonblocking and the receive operation would block." };
	this->errData[9] = { WSAEMSGSIZE, "The datagram was too large to fit into the specified buffer and was truncated." };
	this->errData[10] = { WSAEINVAL, "The socket has not been bound with bind." };
	this->errData[11] = { WSAECONNABORTED, "The virtual circuit was aborted due to timeout or other failure." };
	this->errData[12] = { WSAECONNRESET, "The virtual circuit was reset by the remote side." };
	this->errData[13] = { WSANOTINITIALISED, "A successful WSAStartup must occur before using this function." };
	this->errData[14] = { WSAENETDOWN, "The Windows Sockets implementation has detected that the network"	" subsystem has failed." };
	this->errData[15] = { WSAEAFNOSUPPORT, "The specified address family is not supported." };
	this->errData[16] = { WSAEINPROGRESS, "A blocking Windows Sockets operation is in progress." };
	this->errData[17] = { WSAEMFILE, "No more file descriptors are available." };
	this->errData[18] = { WSAENOBUFS, "No buffer space is available. The socket cannot be created." };
	this->errData[19] = { WSAEPROTONOSUPPORT, "The specified protocol is not supported." };
	this->errData[20] = { WSAEPROTOTYPE, "The specified protocol is the wrong type for this socket." };
	this->errData[21] = { WSAESOCKTNOSUPPORT, "The specified socket type is not supported in this address family." };
	this->errData[22] = { WSANOTINITIALISED, "A successful WSAStartup must occur before using this function." };
	this->errData[23] = { WSAENETDOWN, "The Windows Sockets implementation has detected that the " "network subsystem has failed." };
	this->errData[24] = { WSAEADDRINUSE, "The specified address is already in use. (See the SO_REUSEADDR" " socket option under setsockopt.)" };
	this->errData[25] = { WSAEFAULT, "The namelen argument is too small (less than the size of a struct sockaddr)." };
	this->errData[26] = { WSAEINPROGRESS, "A blocking Windows Sockets call is in progress." };
	this->errData[27] = { WSAEAFNOSUPPORT, "The specified address family is not supported by this protocol." };
	this->errData[28] = { WSAEINVAL, "The socket is already bound to an address." };
	this->errData[29] = { WSAENOBUFS, "Not enough buffers available, too many connections." };
	this->errData[30] = { WSAENOTSOCK, "The descriptor is not a socket." };
	this->errData[31] = { WSANOTINITIALISED, "A successful WSAStartup must occur before using this function." };
	this->errData[32] = { WSAENETDOWN, "The Windows Sockets implementation has detected that " "the network subsystem has failed." };
	this->errData[33] = { WSAEINVAL, "Indicates that one of the specified parameters was invalid." };
	this->errData[34] = { WSAEINPROGRESS, "A blocking Windows Sockets operation is in progress." };
	this->errData[35] = { WSAEADDRINUSE, "The specified address is already in use." };
	this->errData[36] = { WSAEADDRNOTAVAIL, "The specified address is not available from the local computer." };
	this->errData[37] = { WSAEAFNOSUPPORT, "Addresses in the specified family cannot be used with this socket." };
	this->errData[38] = { WSAECONNREFUSED, "The attempt to connect was forcefully rejected." };
	this->errData[39] = { WSAEDESTADDRREQ, "A destination address is required." };
	this->errData[40] = { WSAEFAULT, "The namelen argument is incorrect." };
	this->errData[41] = { WSAEINVAL, "The socket is already bound to an address." };
	this->errData[42] = { WSAEISCONN, "The socket is already connected." };
	this->errData[43] = { WSAEMFILE, "No more file descriptors are available." };
	this->errData[44] = { WSAENETUNREACH, "The network can't be reached from this host at this time." };
	this->errData[45] = { WSAENOBUFS, "No buffer space is available. The socket cannot be connected." };
	this->errData[46] = { WSAENOTCONN, "The socket is not connected." };
	this->errData[47] = { WSAENOTSOCK, "The descriptor is a file, not a socket." };
	this->errData[48] = { WSAETIMEDOUT, "Attempt to connect timed out without establishing a connection" };
	this->errData[49] = { WSAENETDOWN, "The Windows Sockets implementation has detected that the network" " subsystem has failed." };
	this->errData[50] = { WSAECONNRESET, "The connection was reset by the remote side." };
	this->errData[51] = { WSAECONNABORTED, "The connection was aborted due to timeout or other failure." };
	this->errData[52] = { WSAENETDOWN, "The Windows Sockets implementation has detected that "  "the network subsystem has failed." };
	this->errData[53] = { WSANOTINITIALISED, "A successful WSAStartup must occur before using this function." };
	this->errData[54] = { WSAENETDOWN, "The Windows Sockets implementation has detected " "that the network subsystem has failed." };
	this->errData[55] = { WSAEACCES, "The requested address is a broadcast address, but the appropriate flag was not set." };
	this->errData[56] = { WSAEINTR, "The (blocking) call was canceled using WSACancelBlockingCall." };
	this->errData[57] = { WSAEINPROGRESS, "A blocking Windows Sockets operation is in progress." };
	this->errData[58] = { WSAEFAULT, "The buf or to parameters are not part of the user address space, " "or the to argument is too small (less than the size of a socket address structure)." };
	this->errData[59] = { WSAENETRESET, "The connection must be reset because the Windows Sockets implementation dropped it." };
	this->errData[60] = { WSAENOBUFS, "The Windows Sockets implementation reports a buffer deadlock." };
	this->errData[61] = { WSAENOTCONN, "The socket is not connected (SOCK_STREAM only)." };
	this->errData[62] = { WSAENOTSOCK, "The descriptor is not a socket." };
	this->errData[63] = { WSAEOPNOTSUPP, "MSG_OOB was specified, but the socket is not of type SOCK_STREAM." };
	this->errData[64] = { WSAESHUTDOWN, "The socket has been shut down; it is not possible to sendto on a socket" " after shutdown has been invoked with how set to 1 or 2." };
	this->errData[65] = { WSAEWOULDBLOCK, "The socket is marked as nonblocking and the requested operation would block." };
	this->errData[66] = { WSAEMSGSIZE, "The socket is of type SOCK_DGRAM, and the datagram is larger " "than the maximum supported by the Windows Sockets implementation." };
	this->errData[67] = { WSAECONNABORTED, "The virtual circuit was aborted due to timeout or other failure." };
	this->errData[68] = { WSAECONNRESET, "The virtual circuit was reset by the remote side." };
	this->errData[69] = { WSAEADDRNOTAVAIL, "The specified address is not available from the local computer." };
	this->errData[70] = { WSAEAFNOSUPPORT, "Addresses in the specified family cannot be used with this socket." };
	this->errData[71] = { WSAEDESTADDRREQ, "A destination address is required." };
	this->errData[72] = { WSAENETUNREACH, "The network can't be reached from this host at this time." };
	this->errData[73] = { WSANOTINITIALISED, "A successful WSAStartup must occur before using this function." };
	this->errData[74] = { WSAENETDOWN, "The Windows Sockets implementation has detected that the network" " subsystem has failed." };
	this->errData[75] = { WSAENOTSOCK, "The descriptor is not a socket." };
	this->errData[76] = { WSAEINPROGRESS, "A blocking Windows Sockets call is in progress." };
	this->errData[77] = { WSAEINTR, "The (blocking) call was canceled using WSACancelBlockingCall." };
	this->errData[78] = { WSAEWOULDBLOCK, "The socket is marked as nonblocking and SO_LINGER is set to a nonzero timeout value." };
	this->errData[79] = { WSANOTINITIALISED, "A successful WSAStartup must occur before using this function." };
	this->errData[80] = { WSAENETDOWN, "The Windows Sockets implementation has detected that the network" " subsystem has failed." };
	this->errData[81] = { WSAEINPROGRESS, "A blocking Windows Sockets operation is in progress." };
	this->errData[82] = { WSANOTINITIALISED, "A successful WSAStartup must occur before using this function." };
	this->errData[83] = { WSAENETDOWN, "The Windows Sockets implementation has detected that the network" " subsystem has failed." };
	this->errData[84] = { WSAENOTCONN, "The socket is not connected." };
	this->errData[85] = { WSAEINTR, "The (blocking) call was canceled using WSACancelBlockingCall." };
	this->errData[86] = { WSAEINPROGRESS, "A blocking Windows Sockets operation is in progress." };
	this->errData[87] = { WSAENOTSOCK, "The descriptor is not a socket."};
	this->errData[88] = { WSAEOPNOTSUPP, "MSG_OOB was specified, but the socket is not of type SOCK_STREAM." };
	this->errData[89] = { WSAESHUTDOWN, "The socket has been shut down; it is not possible to recv on a socket" " after shutdown has been invoked with how set to 0 or 2." };
	this->errData[90] = { WSAEWOULDBLOCK, "The socket is marked as nonblocking and the receive operation would block." };
	this->errData[91] = { WSAEMSGSIZE, "The datagram was too large to fit into the specified buffer and was truncated."};
	this->errData[92] = { WSAEINVAL, "The socket has not been bound with bind." };
	this->errData[93] = { WSAECONNABORTED, "The virtual circuit was aborted due to timeout or other failure." };
	this->errData[94] = { WSAECONNRESET, "The virtual circuit was reset by the remote side." };

}


/************************************************************************/
/*		MakeTimeOutThread
/*			引数：なし
/*			戻り値：なし
/*		概要：通信状態を確認するためのスレッドを起動する
/*		作成日2013/11/14
/************************************************************************/
//void C_CommCheck::MakeTimeOutThread(int target){
//	//this->thData.target = target;
//	//this->checkInfo.TH = (HANDLE)_beginthreadex(NULL, 0, CheckingActive, &this->thData, 0,	&this->checkInfo.ID);
//}
/************************************************************************/
/*		CheckingActive
/*			引数：target(int) : ソケットを閉じる対象
/*			戻り値：なし
/*		概要：指定したクライアントとの通信状態を確認　正常な通信をしていないと判断した場合ソケットを閉じる
/*		作成日2013/11/14
/************************************************************************/
// クライアントの生存確認
//UINT WINAPI C_CommCheck::CheckingActive( void* data )
//{
	//Thread_Data* useData = (Thread_Data*) data;
	//C_CommCheck*	sv = (C_CommCheck*) useData->p_Server;
	//fd_set fds;

	//FrameWorkMsg buf;
	//int  sts;

	//timeval	timeOut;
	//timeOut.tv_sec = 3;		// 秒
	//timeOut.tv_usec = 0;	// ナノ秒
	//memcpy(&fds, &sv->clientInfo[useData->target].fds, sizeof(fd_set));
	//sv->clientInfo[useData->target].status = CHECK_ACTIVE;
	//
	//printf("%d番との通信確認を開始\n", useData->target);
	//// ヘルスチェック用データ送信
	//for(int i=0; i<5; ++i){
	//	sv->MakeSendData(&useData->workMsg, MSG_CHECK);
	//	sv->SendData( useData->target, useData->workMsg.data, sizeof(FrameWorkMsg));
	//}

	//for(int i=10; i>0; --i){
	//	memcpy(&fds, &sv->clientInfo[useData->target].fds, sizeof(fd_set));
	//	// タイムアウト処理
	//	sts = select(sv->clientInfo[useData->target].destSock, &fds, NULL, NULL, &timeOut);	// select( 現在使用しているソケットの最大の番号+1の値, 受信チェックならここにfds, 送信ならここ, ???, 待機時間 )
	//	if (sts == 0) {
	//		printf("No.%d CheckAlive : TimeOut\n残り%d\n", useData->target, i);
	//		continue;
	//	}else if(sv->CheckingError(sts)){
	//		sv->CloseClientSock(useData->target);				//通信できないのでソケットを閉じる
	//	}
	//	if(FD_ISSET(sv->clientInfo[useData->target].destSock, &fds)){
	//	// 指定したソケットに受信があった
	//		memset(buf.data, 0, sizeof(FrameWorkMsg));
	//		sts = recv(sv->clientInfo[useData->target].destSock, buf.data, sizeof(FrameWorkMsg), 0);
	//		// エラーチェック
	//		if( sv->CheckingError(sts) ){
	//			sv->CloseClientSock(useData->target);				//通信できないのでソケットを閉じる
	//		}else{
	//			if(strcmp(buf.msg.check.checkMsg, ACTIVE_MSG) == 0 && 
	//			   buf.msg.header.type == MSG_RESPONSE ){
	//				//一致	通信確認成功
	//				printf("クライアントのアクティブを確認\n");
	//				sv->clientInfo[useData->target].status = ACTIVE;
	//				sv->clientInfo[useData->target].activeCnt = 10;
	//				return 0;
	//			}
	//		}
	//	}	
	//}
	//// 通信確認失敗	
	//printf("%d番との通信を確認できず\n", useData->target);
	//sv->CloseClientSock(useData->target);

//	return 0;
//}

bool C_CommCheck::CheckCommError(int sts){
	int errcode;

	if( sts == SOCKET_ERROR ){
		errcode = WSAGetLastError();
		this->errcom( errcode );
		return true;
	}
	return false;
}
bool C_CommCheck::CheckCommError(SOCKET* sock){
	int errcode;

	if(*sock == INVALID_SOCKET){
		errcode = WSAGetLastError();
		this->errcom(errcode);
		return true;
	}
	return false;
}

bool C_CommCheck::CheckCommError( int sts, int target ){
	if (sts == 0) {
		printf("No.%d Receve : TimeOut\n", target);
		return true;
	}
	return false;
}

bool C_CommCheck::CheckSequenceNo(UINT targetSqNo, UINT nowSqNo){
	if (nowSqNo - targetSqNo >= SQNO_OVERFLOW_BASELINE){		// シーケンス番号がオーバーフローした可能性が高い
		return true;
	}
	else if (nowSqNo - targetSqNo < 0){
		return true;
	}
	else{
		while (1){
			MessageBox(NULL, "シーケンスナンバーチェック例外", "要検証", MB_OK);
			Sleep(1000);
		}
	}
	return false;
}


void C_CommCheck::errcom(int errcode){
	int	i;
	for (i = 0; i<sizeof(this->errData) / sizeof(this->errData[0]); i++){
		if (errcode == this->errData[i].errNo){
			::MessageBox(NULL, this->errData[i].errMsg, "Server WINSOCK ERROR!", MB_OK);
			break;
		}
	}
}