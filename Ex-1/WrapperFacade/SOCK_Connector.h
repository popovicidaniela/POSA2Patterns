#pragma once
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#include "../WrapperFacade/INET_Addr.h"
#include "../WrapperFacade/SOCK_Stream.h"
namespace WrapperFacade {
	class SOCK_Connector
	{
	public:
		SOCK_Connector();
		SOCK_Connector(const INET_Addr &addr, SOCK_Stream &s);
		void connectt(SOCK_Stream &s, const INET_Addr &addr);
		SOCKET get_handle() const;
	private:
		SOCKET handle_;
	};
}