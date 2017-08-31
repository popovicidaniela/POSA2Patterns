#pragma once
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#include "../WrapperFacade/INET_Addr.h"
#include "../WrapperFacade/SOCK_Stream.h"
namespace WrapperFacade {
	class SOCK_Acceptor
	{
	public:
		SOCK_Acceptor();
		SOCK_Acceptor(const INET_Addr &addr);
		void open(const INET_Addr &sock_addr);
		void accept(SOCK_Stream &s);
		SOCKET get_handle() const;
	private:
		SOCKET handle_;
	};
}