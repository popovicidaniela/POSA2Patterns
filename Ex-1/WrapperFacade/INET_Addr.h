#pragma once
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
namespace WrapperFacade {
	class INET_Addr
	{
	public:
		INET_Addr(u_short port, char* addr);
		u_short get_port() const;
		u_long get_ip_addr() const;
		sockaddr *addr() const;
		size_t size() const;
		static void get_ip_address(SOCKET s);
	private:
		mutable sockaddr_in addr_;
	};
}