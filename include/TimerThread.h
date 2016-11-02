#ifndef TIMERTHREAD_H_
#define TIMERTHREAD_H_ 
#include "../include/tThread.h"
#include "../include/Timer.h"
#include <functional>

class TimerThread
{
    public :
        typedef std::function<void ()>TimerCallback;        void setTimer(int value,int interval);
       void setTimerCallback(const TimerCallback &);
        void startTimerThread();
        void cancelTimerThread();
    private :
        Timer timer_;
        tThread thread_;
};

#endif  /*TIMERTHREAD_H_*/
