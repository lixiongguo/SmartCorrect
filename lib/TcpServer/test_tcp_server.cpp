#include "TcpConnection.h"
#include "PollPoller.h"
#include "net.h"
#include "InetAddress.h"
#include "TcpServer.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void onConnection(const TcpConnectionPtr &conn)
{
	cout << "New Client" << conn->getPeerAddr().toIp()<<" Port " << conn->getPeerAddr().toPort()
<< endl;
	string s("Hello from server\n");
	conn->sendString(s);
}

void onMessage(const TcpConnectionPtr &conn)
{
	string s(conn->receiveString());
	cout << "receive a string from"<<
		conn->getPeerAddr().toIp()<<":"<<conn->getPeerAddr().toPort()
		<< "   :"<< s ;
	conn->sendString(s);
}

void onClose(const TcpConnectionPtr &conn)
{
	cout << "Close conn" << endl;
	conn->shutdown();
}

int main(int argc, char *argv[])
{
	int listenfd = init_listenfd();
	if(listenfd == -1)
		perror("listenfd");

	InetAddress addr(8888);
	TcpServer server(addr);

	server.setConnectionCallback(onConnection);
	server.setMessageCallback(onMessage);
	server.setCloseCallback(onClose);
	server.start();
	return 0;
}
