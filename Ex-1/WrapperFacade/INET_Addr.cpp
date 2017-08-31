#include "INET_Addr.h"
#include <iostream>
using namespace std;

namespace WrapperFacade
{
	INET_Addr::INET_Addr(u_short port, char* addr)
	{
		memset(&addr_, 0, sizeof addr_);
		addr_.sin_family = AF_INET;
		addr_.sin_port = htons(port);
		addr_.sin_addr.s_addr = inet_pton(AF_INET, addr, &(addr_.sin_addr));;
		if (inet_pton(AF_INET, addr, &(addr_.sin_addr)) == INVALID_SOCKET) {	// For some reason this makes the server setup not fail!?
			cout<<L"socket failed with error: %ld\n"<< WSAGetLastError();		// Cannot explain why	
			WSACleanup();
		}
	}

	u_short INET_Addr::get_port() const
	{
		return addr_.sin_port;
	}

	u_long INET_Addr::get_ip_addr() const
	{
		return addr_.sin_addr.s_addr;
	}

	sockaddr * INET_Addr::addr() const
	{
		return reinterpret_cast <sockaddr *> (&addr_);
	}

	size_t INET_Addr::size() const
	{
		return sizeof(addr_);
	}

	void INET_Addr::get_ip_address(SOCKET s)
	{
		socklen_t len;
		struct sockaddr_storage addr;
		char ipstr[INET6_ADDRSTRLEN];
		int port;

		len = sizeof addr;
		getpeername(s, (struct sockaddr*)&addr, &len);

		// deal with both IPv4 and IPv6:
		if (addr.ss_family == AF_INET) {
			struct sockaddr_in *s = (struct sockaddr_in *)&addr;
			port = ntohs(s->sin_port);
			inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
		}
		else { // AF_INET6
			struct sockaddr_in6 *s = (struct sockaddr_in6 *)&addr;
			port = ntohs(s->sin6_port);
			inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof ipstr);
		}
		cout << ipstr;
	}

}