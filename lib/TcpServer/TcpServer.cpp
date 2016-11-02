#include "TcpServer.h"
#include "Socket.h"
#include "PollPoller.h"
#include <functional>
#include <iostream>

using namespace std;
using namespace std::placeholders;


TcpServer::TcpServer(const InetAddress &addr)
{
	int sockfd = ::socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	perror("socket");
	sock_.reset(new Socket(sockfd));
	sock_->setReusePort();
	sock_->bindAddress(addr);
	sock_->listen();

	pool_.reset(new ThreadPool(5,4));
}

void TcpServer::start()
{
	poller_.reset(new PollPoller(sock_->fd()));
	poller_->setConnectionCallback(onConnectionCallback_);
	poller_->setMessageCallback(onMessageCallback_);
	poller_->setCloseCallback(onCloseCallback_);

	pool_->start();
	while(1)
	{
		poller_->poll();
		poller_->handleAccept();
		poller_->handleData();
	}
}
void TcpServer::poolAddTask(const ThreadTask &task)
{
	pool_->addTask(task);
}
