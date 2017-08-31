#pragma once
#include "Proactor.h"
#include "Async_Stream.h"
#include "../AcceptorConnectorPattern/Service_Handler.h"
#include "../../Ex-1/WrapperFacade/SOCK_Stream.h"
#include <iostream>
using namespace std;
using namespace WrapperFacade;
typedef Service_Handler<SOCK_Stream> Some_Handler;
class Concrete_Completion_Handler : public Completion_Handler, public Some_Handler
{
public:
	Concrete_Completion_Handler() : proactor_(Proactor::instance()) { }
	Concrete_Completion_Handler(Proactor * p) : proactor_(p) { }
	virtual void open();
	virtual void handle_event(SOCKET s, ReactorPattern::Event_Type event_type, const Async_Result &async_result);
	virtual SOCKET get_handle() const;
private:
	Proactor *proactor_;// Cached <Proactor>.
	char * request_;// Hold the HTTP Request while its being processed.// Hold the HTTP Request while its being processed.
	Async_Stream stream_;// Read/write asynchronous socket I/O.
	SOCK_Stream sock_;
};