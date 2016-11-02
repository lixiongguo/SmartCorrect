#include"TcpConnection.h"

using namespace std;

TcpConnection::TcpConnection(int sockfd,const InetAddress &localAddr,const InetAddress &peerAddr)
	:sockfd_(sockfd),
	buffer_(sockfd),
	localAddr_(localAddr),
	peerAddr_(peerAddr)
{
}

TcpConnection::~TcpConnection()
{
	shutdown();
}

ssize_t TcpConnection::readn(char *usrbuf, size_t n)
{
	int nread = buffer_.readn(usrbuf,n);
	if(nread == -1)
		perror("readn");
	return nread;
}

ssize_t TcpConnection::readline(char *usrbuf, size_t n)
{
	int nread = buffer_.readline(usrbuf,n);
	if(nread == -1)
		perror("readline");
	return nread;
}


ssize_t TcpConnection::writen(const char *usrbuf, size_t n)
{
	int nwrite = buffer_.writen(usrbuf, n);
	if(nwrite == -1)
		perror("writen");
	return nwrite;
}

void TcpConnection::sendString(const std::string &s)
{
	writen(s.c_str(),s.size());
}

std::string TcpConnection::receiveString()
{
	char buf[1024];
	readline(buf,1024);
	return std::string(buf);
}

void TcpConnection::shutdown()
{
	sockfd_.shutdownWrite();
}

