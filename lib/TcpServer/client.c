#include"net.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
int main(void)
{
	int peerfd = client_connect();
	char sndbuf[1024]="";
	char rcvbuf[1024]="";
	char hellobuf[128]="";
	recv(peerfd, hellobuf, sizeof(hellobuf),0);
	printf("%s",hellobuf);
	while(fgets(sndbuf,sizeof(sndbuf),stdin) != NULL)
	{
		send(peerfd, sndbuf, strlen(sndbuf),0);
		recv(peerfd, rcvbuf, sizeof(rcvbuf),0);
		printf("%s",rcvbuf);
		memset(sndbuf,0,sizeof(sndbuf));
		memset(rcvbuf,0,sizeof(rcvbuf));
	}
}
