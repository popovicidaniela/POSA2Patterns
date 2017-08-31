#pragma once
#include "Async_Result.h"
#include "Proactor.h"
#include "../Reactor/Event_Handler.h"
class Completion_Handler
{
public:
	Completion_Handler() : proactor_(Proactor::instance()) {}
	Completion_Handler(Proactor *proactor) : proactor_(proactor) { }// Cache the <proactor> so that hook methods can invoke asynchronous operations on <proactor>.
	virtual ~Completion_Handler() { }// Virtual destruction.
	virtual void handle_event(SOCKET handle, ReactorPattern::Event_Type et, const Async_Result &result) = 0;// Hook method dispatched by cached<proactor_> to handle completion events of a particulartype that occur on the <handle>. <Async_Result>reports the results of the completed asynchronous operation.
	virtual SOCKET get_handle() const = 0;// Returns underlying I/O <HANDLE>.
private:
	Proactor *proactor_;
};