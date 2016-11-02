#include "TcpServer.h"
#include "NonCopyable.h"
#include <iostream>
#include <string>

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
void func()
{
	conn->sendString("ACk\n");
}
void onMessage(const TcpConnectionPtr &conn)
{
/**	string s(conn->receiveString());
	cout << "receive a string from   "<<
		conn->getPeerAddr().toIp()<<":"<<conn->getPeerAddr().toPort()
		<< "   says:"<< s ;
	conn->sendString(s);**/
	server_.pool_addaTask(bind(&TestTcpServer::func,this));
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
