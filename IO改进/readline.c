/*************************************************************************
	> File Name: test2.c
	> Author: Comst
	> Mail:750145240@qq.com 
	> Created Time: Thu 24 Jul 2014 10:58:20 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>

ssize_t readline(int fd, void *usrbuf, size_t maxlen)
{
	char *bufp = usrbuf;
	size_t nread;
	size_t nleft = maxlen - 1;
	char c;
	while(nleft > 0)
	{
		if((nread = read(fd, &c ,1)) == -1)
		{
			if(errno == EINTR)
				continue;
			return -1;
		}else if(nread == 0)
		{
			break;
		}
		if(c == '\n')
		{
			*bufp = c;
			bufp++;
			nleft --;
			break;
		}
		*bufp = c;
		bufp ++;
		nleft --;
	}
	*bufp = '\0';
	return (maxlen - nleft -1);
}

int main(int argc, char * argv[])
{
	int fd = open("test.txt", O_RDONLY);
	if(fd == -1)
		perror("open");
	int ret;
	char buf[1024];}
	while((ret = readline(0, ret, buf)))
	{
		printf("ret=%d, buf=%s\n",ret,buf);
	}
	return 0;
