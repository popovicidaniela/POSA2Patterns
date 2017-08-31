#include "SOCK_Stream.h"

WrapperFacade::SOCK_Stream::SOCK_Stream() : handle_(INVALID_SOCKET) { }

WrapperFacade::SOCK_Stream::SOCK_Stream(SOCKET h) : handle_(h) { handle_ = h; }

WrapperFacade::SOCK_Stream::~SOCK_Stream()
{
	//closesocket(handle_);
}

void WrapperFacade::SOCK_Stream::set_handle(SOCKET h)
{
	handle_ = h;
}

SOCKET WrapperFacade::SOCK_Stream::get_handle() const
{
	return handle_;
}

uintptr_t WrapperFacade::SOCK_Stream::recv(char * buf, size_t len, int flags)
{
	return _WINSOCKAPI_::recv(handle_, buf, len, flags);;
}

uintptr_t WrapperFacade::SOCK_Stream::send(const char * buf, size_t len, int flags)
{ 
	return _WINSOCKAPI_::send(handle_, buf, len, flags);
}
