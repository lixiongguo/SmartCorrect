#ifndef T_THREAD_H_
#define T_THREAD_H_

#include<pthread.h>
#include<functional>

class tThread 
{
    public :
        typedef std::function<void ()>ThreadFunc;
        tThread(){}
        explicit tThread(const ThreadFunc &callback);
        ~tThread();

        void setCallback(const ThreadFunc &cb);
        void start();
        void join();
    
    private:
        static void *threadFunc(void *);

        pthread_t tid_;
        ThreadFunc callback_;
        bool isStarted_;
};
#endif
