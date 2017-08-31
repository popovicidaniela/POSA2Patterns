#include "Async_Result.h"

void Async_Result::bytes_transferred(u_long bt)
{
	bytes_transferred_ = bt;
}

u_long Async_Result::bytes_transferred() const
{
	return bytes_transferred_;
}

void Async_Result::status(u_long s)
{
	status_ = s;
}

u_long Async_Result::status() const
{
	return status_;
}

void Async_Result::error(u_long e)
{
	error_ = e;
}

u_long Async_Result::error() const
{
	return error_;
}
