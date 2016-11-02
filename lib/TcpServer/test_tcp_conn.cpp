#include "net.h"
#include "TcpConnection.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
	int listenfd = init_listenfd();
	if(listenfd == -1)
		perror("listenfd");
	int peerfd =accept(listenfd, NULL, NULL);
	if(peerfd == -1)
		perror("accept");

	TcpConnectionPtr conn(new TcpConnection(peerfd));
	char buf[1024]="";
	while(1)
	{
		int ret = conn->readline(buf,1024);
		if(ret == 0)
		{
			conn->shutdown();
			cout << "close" << endl;
			break;
		}
		cout << "recv data:" << buf;
		conn -> sendString(buf);
		memset(buf,0,sizeof(buf));
	}
}
