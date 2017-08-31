#pragma once
#include"../Reactor/Event_Handler.h"
#include<WinSock2.h>
template <class IPC_STREAM>
class Service_Handler : public ReactorPattern::Event_Handler {
public:
	virtual void open() { }
	IPC_STREAM &peer() { return ipc_stream_; }
	void set_handle(SOCKET handle) { return ipc_stream_.set_handle(handle); }
	virtual void handle_event(SOCKET s, ReactorPattern::Event_Type et) { }
	virtual SOCKET get_handle() const { return ipc_stream_.get_handle(); }
private:
	IPC_STREAM ipc_stream_;
};