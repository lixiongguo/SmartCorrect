#ifndef TIMER_H_
#define TIMER_H_

#include"../include/NonCopyable.h"
#include<functional>
#include<sys/timerfd.h>

class Timer
{
    public :
        typedef std::function<void()>TimeCallback;
        Timer();
        ~Timer();

        void setTimer(int val, int interval);
        void setTimeCallback(const TimeCallback &);
        void runTimer();
        void cancelTimer();
    private :
        int timerfd_;
        struct itimerspec howlong_;
        TimeCallback timeCallback_;
        bool isStarted_;
};
#endif
