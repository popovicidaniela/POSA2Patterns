#pragma once
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
namespace WrapperFacade {
	class SOCK_Stream
	{
	public:
		SOCK_Stream();
		SOCK_Stream(SOCKET h);
		~SOCK_Stream();
		void set_handle(SOCKET h);
		SOCKET get_handle() const;
		uintptr_t recv(char *buf, size_t len, int flags);
		uintptr_t send(const char *buf, size_t len, int flags);
	private:
		SOCKET handle_;
	};
}
