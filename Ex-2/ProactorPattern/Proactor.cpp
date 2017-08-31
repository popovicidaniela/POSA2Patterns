#include "Proactor.h"

void Proactor::register_handle(SOCKET handle)
{
	proactor_impl_->register_handle(handle);
}

void Proactor::handle_events(timeval * wait_time)
{
	proactor_impl_->handle_events(wait_time);
}
Proactor * Proactor::pointerInstance;
Proactor * Proactor::instance()
{
	if (!pointerInstance)
	{
		pointerInstance = new Proactor;
		pointerInstance->setProactorImplementation(new Win32_Proactor_Implementation);
	}
	return pointerInstance;
}

void Proactor::setProactorImplementation(Proactor_Implementation * proactor_impl)
{
	proactor_impl_ = proactor_impl;
}
