#include "../include/SmartCorrect.h"
#include "../include/TimerThread.h"
#include <fstream>
using namespace std;
using namespace std::placeholders;

SmartCorrect::SmartCorrect(const InetAddress &addr,const string& cache_a,const string& cache_b)
			:server_(addr),
            cache_manager_(cache_a,cache_b)
		{
			server_.setConnectionCallback(bind(&SmartCorrect ::onConnection,this,_1));
			server_.setMessageCallback(bind(&SmartCorrect ::onMessage,this,_1));
			server_.setCloseCallback(bind(&SmartCorrect ::onClose,this,_1));
            
            
            cache_writer_.setTimer(60,60);
            cache_writer_.setTimerCallback(bind(&CacheManager::writeToDisk,&cache_manager_));

        }

void SmartCorrect::start()
		{
           cache_writer_.startTimerThread();
           server_.start();
        }

void SmartCorrect::onConnection(const TcpConnectionPtr &conn)
{
	cout << "New Client" << conn->getPeerAddr().toIp()<<" Port " << conn->getPeerAddr().toPort()
<< endl;
	string s("Hello from server\r\n");
	conn->sendString(s);
}


void SmartCorrect::func(const TcpConnectionPtr &conn, const string &s)
{
	::printf("\n%lx get task!\n",pthread_self());
    string result1;
    string result2;
    string result;
    if(cache_manager_.query(s,result))
    {     
    }
    else
    {
        string s1=s;
        query(s1,result1,result2);
     cout << "through computation" << endl;
    
        cache_manager_.insert(s,result2);
        /**最简单得cache共享方法:多写几次**/
        cache_manager_.insert(s,result2);
        cache_manager_.insert(s,result2);

        result = result1 + "\n";
    }
    
	conn->sendString(result);
}


void SmartCorrect::onMessage(const TcpConnectionPtr &conn)
{
	string s0(conn->receiveString());
    char str[128]="";
    string ::size_type ix;
    for(ix=0; s0[ix] != '\r'; ix++)
        str[ix] = s0[ix];
    str[ix] = '\0';
    string s(str);

	cout << "receive a string from   "<<
		conn->getPeerAddr().toIp()<<":"<<conn->getPeerAddr().toPort()
		<< "   says:"<< s <<endl;
    if(s=="write==")
        cache_manager_.writeToDisk();
	server_.poolAddTask(bind(&SmartCorrect ::func,this,conn,s));
}

void SmartCorrect::onClose(const TcpConnectionPtr &conn)
{
	cout << "Close conn" << endl;
	conn->shutdown();
}




