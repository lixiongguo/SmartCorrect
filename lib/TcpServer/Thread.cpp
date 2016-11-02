#include"Thread.h"

Thread::Thread(ThreadFunc callback)
	:tid_(0),
	isStarted_(false),
	callback_(callback)
{}

Thread::~Thread()
{
	if(isStarted_)
		pthread_detach(tid_);
}

void *Thread::threadFunc(void *arg)
{
	Thread *pt = static_cast<Thread *>(arg);
	pt->callback_();
}

void Thread::start()
{
	pthread_create(&tid_,NULL,threadFunc,this);
}

void Thread::join()
{
	pthread_join(tid_,NULL);
}
