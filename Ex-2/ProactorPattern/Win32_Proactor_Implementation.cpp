#include "Win32_Proactor_Implementation.h"

Win32_Proactor_Implementation::Win32_Proactor_Implementation()
{
	completion_port_ = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
}

void Win32_Proactor_Implementation::register_handle(SOCKET h)
{
	HANDLE acceptSocket = (HANDLE)h;
	CreateIoCompletionPort(acceptSocket, completion_port_, 0, 0);
}

void Win32_Proactor_Implementation::handle_events(timeval * wait_time)
{
	u_long num_bytes;
	OVERLAPPED *act;
	BOOL status = GetQueuedCompletionStatus(completion_port_, &num_bytes, 0, &act, wait_time == 0 ? 0 : wait_time->tv_usec/1000);//asynchronous event demultiplexer
	Async_Result *async_result = static_cast <Async_Result *> (act);
	async_result->status(status);
	if (!status) async_result->error(GetLastError());
	else async_result->bytes_transferred(num_bytes);
	async_result->complete();
	delete async_result;
}
