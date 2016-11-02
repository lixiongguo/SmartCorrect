/*************************************************************************
	> File Name: server.c
	> Author: Comst
	> Mail:750145240@qq.com 
	> Created Time: Sat 26 Jul 2014 10:22:59 AM CST
 ************************************************************************/

#include"net.h"

int init_listenfd()
{
	int fd_server;
	int reuse = 1;
	struct sockaddr_in server_addr;
	int addrlen = sizeof(server_addr);
	if((fd_server = socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket");
		return -1;
	}
	if(0 != setsockopt(fd_server,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int)))
	{
		perror("setsockopt");
		close(fd_server);
		return -1;
	}
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8888);
	server_addr.sin_addr.s_addr = inet_addr("192.168.1.100");
	if(-1 == bind(fd_server,(struct sockaddr*)&server_addr,sizeof(server_addr)))
	{
		perror("bind");
		close(fd_server);
		return -1;
	}
	if(-1 == listen(fd_server,5))
	{
		perror("listen");
		close(fd_server);
		return -1;
	}
	return fd_server;
}

	
int client_connect()
{
	int fd_client = socket(AF_INET,SOCK_STREAM, 0);
	if(fd_client == -1)
		perror("socket");
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8888);
	server_addr.sin_addr.s_addr = inet_addr("192.168.1.100");
	if(connect(fd_client,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
	{
		perror("connect");
		close(fd_client);
		exit(-1);
	}
	return fd_client;
}
