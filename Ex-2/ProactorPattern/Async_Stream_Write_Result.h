#pragma once
#include"Completion_Handler.h"
class Async_Stream_Write_Result : public Async_Result
{
public:
	Async_Stream_Write_Result(Completion_Handler *completion_handler) : completion_handler_(completion_handler) { }// Constructor caches the completion handler.
	virtual void complete()// Adapter that dispatches the <handle_event> hook method on cached completion handler.
	{
		completion_handler_->handle_event(completion_handler_->get_handle(), ReactorPattern::WRITE_EVENT, *this);
	}
private:
	Completion_Handler *completion_handler_;// Cache a pointer to a completion handler.
};