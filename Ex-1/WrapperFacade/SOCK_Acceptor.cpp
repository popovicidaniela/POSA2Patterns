#include "SOCK_Acceptor.h"

WrapperFacade::SOCK_Acceptor::SOCK_Acceptor()
{
}

WrapperFacade::SOCK_Acceptor::SOCK_Acceptor(const INET_Addr & addr)
{
	handle_ = socket(PF_INET, SOCK_STREAM, 0);
	bind(handle_, addr.addr(), addr.size());
	listen(handle_, 2);
}

void WrapperFacade::SOCK_Acceptor::open(const INET_Addr & sock_addr)
{
	handle_ = socket(PF_INET, SOCK_STREAM, 0);
	bind(handle_, sock_addr.addr(), sock_addr.size());
	listen(handle_, 2);
}

void WrapperFacade::SOCK_Acceptor::accept(SOCK_Stream &s)
{
	SOCKET socket = _WINSOCKAPI_::accept(handle_, 0, 0);
	s.set_handle(socket);
}

SOCKET WrapperFacade::SOCK_Acceptor::get_handle() const
{
	return handle_;
}
