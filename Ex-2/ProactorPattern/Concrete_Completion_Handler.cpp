#include "Concrete_Completion_Handler.h"
void Concrete_Completion_Handler::open()
{
	sock_ = peer();
	stream_.open(this, sock_.get_handle(), proactor_);// Initialize <Async_Stream>. This completion handler.
	stream_.async_read(request_, sizeof(request_));// Start asynchronous read operation on socket.
}

void Concrete_Completion_Handler::handle_event(SOCKET s, ReactorPattern::Event_Type event_type, const Async_Result & async_result)
{
	if (event_type == ReactorPattern::READ_EVENT)
	{
		int i = 0;
		while (request_[i] != '$')
		{
			cout << request_[i];
			i++;
		}
		cout << endl;
		//if (async_result.bytes_transferred()) stream_.async_read(request_, sizeof(request_));
		// Didn't get entire request, so start a new asynchronous read operation.
		//else parse_request();
	}
	else if (event_type == ReactorPattern::WRITE_EVENT)
	{
		//if (!file_.done(async_result.bytes_transferred())) stream_.async_write(file_.buffer(), file_.buffer_size());
		// Didn't send entire data, so start another asynchronous write.
		//else// Success, so free up resources...
	}
}
SOCKET Concrete_Completion_Handler::get_handle() const
{
	return sock_.get_handle();
}