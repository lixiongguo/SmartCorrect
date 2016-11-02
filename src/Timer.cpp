#include"../include/Timer.h"
#include"../include/NonCopyable.h"
#include<poll.h>
#include<unistd.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

Timer::Timer()
{
    timerfd_ = ::timerfd_create(CLOCK_REALTIME,0);
    if(timerfd_ == -1)
        perror("timerfd_create");
   memset(&howlong_,0,sizeof howlong_);
}

Timer::~Timer()
{
    ::close(timerfd_);
}

void Timer::setTimer(int val, int interval)
{
    howlong_.it_value.tv_sec = val;
    howlong_.it_interval.tv_sec =interval;
}

void Timer::setTimeCallback(const TimeCallback& cb){
    timeCallback_ = cb;
}

void Timer::runTimer()
{
    struct pollfd event[1];
    event[0].fd = timerfd_;
    event[0].events = POLLIN;
   int nready;
   char buf[1024];
   if(timerfd_settime(timerfd_,0,&howlong_,NULL) == -1)
       perror("timer_settime");
    while(isStarted_)
    {
        nready = poll(event,1,10000);
        if(nready == -1)
        {perror("poll");}
        else if(nready == 0)
        { printf("time out\n");}
        else
        {
            if(read(timerfd_,buf,sizeof buf)==-1)
               perror("read");
            timeCallback_();
        }
    }
}

void Timer::cancelTimer()
{
    memset(&howlong_,0,sizeof howlong_);
    if(timerfd_settime(timerfd_,0,&howlong_,NULL)==-1)
        perror("timerfd_settime");
    isStarted_ = false;
}
