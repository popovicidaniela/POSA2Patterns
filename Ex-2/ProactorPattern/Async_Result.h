#pragma once
#include<WinSock2.h>
class Async_Result : public OVERLAPPED
{
public:
	virtual void complete() = 0;//Dispatch to completion handler hook method.
	void bytes_transferred(u_long);//Set/get number of bytes transferred by an asynchronous operation.
	u_long bytes_transferred() const;
	void status(u_long);//Set/get the status of the asynchronous operation,// i.e., whether it succeeded or failed.
	u_long status() const;
	void error(u_long);// Set/get error value if the asynchronous operation failed or was canceled by the initiator.
	u_long error() const;
private:
	u_long bytes_transferred_ = 0;
	u_long status_ = 0;
	u_long error_ = 0;
};