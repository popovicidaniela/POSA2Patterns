#include "SOCK_Connector.h"

WrapperFacade::SOCK_Connector::SOCK_Connector()
{
	handle_ = socket(PF_INET, SOCK_STREAM, 0);
}

WrapperFacade::SOCK_Connector::SOCK_Connector(const INET_Addr & addr, SOCK_Stream &s)
{
	handle_ = socket(PF_INET, SOCK_STREAM, 0);
	connect(handle_, addr.addr(), addr.size());
	s.set_handle(handle_);
}

void WrapperFacade::SOCK_Connector::connectt(SOCK_Stream & s, const INET_Addr & addr)
{
	//handle_ = socket(PF_INET, SOCK_STREAM, 0);
	connect(handle_, addr.addr(), addr.size());
	s.set_handle(handle_);
}

SOCKET WrapperFacade::SOCK_Connector::get_handle() const
{
	return handle_;
}
