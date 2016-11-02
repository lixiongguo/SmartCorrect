#include"../include/tThread.h"

tThread::tThread(const ThreadFunc &callback)
    :tid_(0),isStarted_(false),callback_(callback)
{}

tThread::~tThread()
{
    if(isStarted_)
        pthread_detach(tid_);
}

void tThread::setCallback(const ThreadFunc& cb)
{
   callback_ = cb;
}

void *tThread::threadFunc(void *arg)
{
    tThread *pt = static_cast<tThread *>(arg);
    pt->callback_();
}
void tThread::start()
{
    pthread_create(&tid_,NULL,threadFunc,this);
}
void tThread::join()
{
    pthread_join(tid_,NULL);
}
