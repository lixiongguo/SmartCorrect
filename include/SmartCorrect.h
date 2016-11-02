#ifndef SMARTCORRECT_H_
#define SMARTCORRECT_H_

#include <libServer/TcpServer.h>
#include <libServer/NonCopyable.h>
#include <libServer/Thread.h>
#include <libServer/ThreadPool.h>
#include <libServer/MutexLock.h>

#include <unordered_map>
#include <algorithm>

#include <iostream>
#include <string>
#include <string.h>

#include <pthread.h>

#include "../include/query.h"
#include "../include/Edist.h"
#include "../include/TimerThread.h"
#include "../include/CacheManager.h"

class SmartCorrect:NonCopyable{
    public:
        SmartCorrect(const InetAddress &addr,const std::string& , const std::string&);      
        void start();
    private :
        void onConnection(const TcpConnectionPtr &conn);
        void func(const TcpConnectionPtr &conn, const std::string &s);
        void onMessage(const TcpConnectionPtr &conn);
        void onClose(const TcpConnectionPtr &conn);

        
       TcpServer server_;

       TimerThread cache_writer_;
        
       CacheManager cache_manager_;
};

#endif
