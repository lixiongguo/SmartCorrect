/*************************************************************************
	> File Name: server.h
	> Author: Comst
	> Mail:750145240@qq.com 
	> Created Time: Sat 26 Jul 2014 10:22:59 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>


int init_listenfd();

int client_connect();

