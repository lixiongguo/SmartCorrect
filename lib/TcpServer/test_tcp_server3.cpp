#include "TcpServer.h"
#include "NonCopyable.h"
#include "Thread.h"
#include "ThreadPool.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <pthread.h>

using namespace std;
using namespace std::placeholders;

class TestTcpServer:NonCopyable
{
	public :
		TestTcpServer(const InetAddress &addr)
			:server_(addr)
		{
			server_.setConnectionCallback(bind(&TestTcpServer::onConnection,this,_1));
			server_.setMessageCallback(bind(&TestTcpServer::onMessage,this,_1));
			server_.setCloseCallback(bind(&TestTcpServer::onClose,this,_1));
		}
		void start()
		{server_.start();}
	private :
void onConnection(const TcpConnectionPtr &conn)
{
	cout << "New Client" << conn->getPeerAddr().toIp()<<" Port " << conn->getPeerAddr().toPort()
<< endl;
	string s("Hello from server\n");
	conn->sendString(s);
}
void func(const TcpConnectionPtr &conn,const string &s)
{
	::printf("\n%u get task!\n",pthread_self());
	conn->sendString(s);
}
void onMessage(const TcpConnectionPtr &conn)
{
	string s(conn->receiveString());
	cout << "receive a string from   "<<
		conn->getPeerAddr().toIp()<<":"<<conn->getPeerAddr().toPort()
		<< "   says:"<< s ;
	server_.poolAddTask(bind(&TestTcpServer::func,this,conn,s));
}

void onClose(const TcpConnectionPtr &conn)
{
	cout << "Close conn" << endl;
	conn->shutdown();
}

TcpServer server_;
};

int main(int argc,const char *argv[])
{
	InetAddress addr(8888);
	TestTcpServer server(addr);
	server.start();
	return 0;
}
