#include "Async_Stream.h"

Async_Stream::Async_Stream()
{
	completion_handler_ = NULL;
	handle_ = NULL;
	proactor_ = NULL;
}

void Async_Stream::open(Completion_Handler * handler, SOCKET handle, Proactor * proactor)
{
	completion_handler_ = handler;
	handle_ = handle;
	proactor_ = proactor;
	proactor->register_handle(handle);// Associate handle with <proactor>'s completion port, as shown in implementation activity 4.
}

void Async_Stream::async_read(void * buf, u_long n_bytes)
{
	u_long bytes_read;
	OVERLAPPED *act = new Async_Stream_Read_Result(completion_handler_);
	ReadFile((HANDLE)handle_, buf, n_bytes, &bytes_read, act);
}

void Async_Stream::async_write(const void * buf, u_long n_bytes)
{
	u_long bytes_read;
	OVERLAPPED *act = new Async_Stream_Write_Result(completion_handler_);
	WriteFile((HANDLE)handle_, buf, n_bytes, &bytes_read, act);
}
