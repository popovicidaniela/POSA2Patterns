#pragma once
#include "Completion_Handler.h"
#include "Async_Stream_Read_Result.h"
#include "Async_Stream_Write_Result.h"
#include "Proactor.h"
class Async_Stream
{
public:
	Async_Stream();// Constructor 'zeros out' the data members.
	void open(Completion_Handler *handler, SOCKET handle, Proactor *proactor);// Initialization method.
	void async_read(void *buf, u_long n_bytes);// Invoke an asynchronous read operation.
	void async_write(const void *buf, u_long n_bytes);// Invoke an asynchronous write operation.
private:// Cache parameters passed in <open>.
	Completion_Handler *completion_handler_;
	SOCKET handle_;
	Proactor *proactor_;
};