/*************************************************************************
	> File Name: test1.c
	> Author: Comst
	> Mail:750145240@qq.com 
	> Created Time: Thu 24 Jul 2014 09:56:58 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
ssize_t readn(int fd , char *buf, int n); 
ssize_t writen(int fd , char *buf, int n); 
int main(int argc, char *argv[])
{
	int fd = open("test.txt",O_RDONLY);
	int nread;
	if(fd == -1)
		perror("open");
	char buf[128]="";
	
	while((nread = readn(fd, buf, 5))>0)
	{
		//printf("%d\n",nread);
		writen(1, buf,nread);
	}
}
ssize_t readn(int fd, char *buf, int n) 
{
	size_t nleft=n;
	size_t nread;

	char *bufp=buf;

	while(nleft > 0)
	{
		nread = read( fd, bufp, nleft );
		if(nread == -1)
		{
			if(errno == EINTR)
			continue;
			else 
				return -1;
		}
		else if(nread == 0)
				break;
		nleft -= nread;
		bufp += nread;
	}
	return (n - nleft);
}

ssize_t writen(int fd , char *buf, int n)
{
	size_t nleft = n;
	size_t nwrite;
	char *bufp = buf;
	while(nleft > 0)
	{
		nwrite = write(fd, bufp, nleft);
		if(nwrite <= 0)
		{
			if(errno == EINTR)
			continue;
			else 
				return -1;

		}
			nleft -= nwrite;
			bufp += nwrite;
	}
	return n;
}
