/*************************************************************************
	> File Name: test3.c
	> Author: Comst
	> Mail:750145240@qq.com 
	> Created Time: Thu 24 Jul 2014 11:39:39 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>

typedef struct tag
{
	int fd_;
	int left_;
	char *bufptr_;
	char buffer_[1024];
}rio_t;

void rio_init(rio_t *rp,int fd)
{
	rp->left_=0;
	rp->fd_ = fd;
	rp->bufptr_= rp->buffer_;
}

size_t rio_read(rio_t *rp, char *buf, int n)
{
	size_t  nread;
	while(rp->left_<= 0)
	{
		nread = read(rp->fd_, rp->buffer_, sizeof(rp->buffer_));
		rp->bufptr_ = rp->buffer_;
		if(nread==-1)
		{
			if(errno == EINTR)
				continue;
			else 
				return -1;
		}
		else if(nread == 0) 
			return 0;
		rp->left_ += nread;
	}
	int cnt = n;
	if(rp->left_ < cnt) cnt = rp->left_;
	memcpy(buf, rp->bufptr_,cnt);
	rp->left_-= cnt;
	rp->bufptr_ += cnt;
	return cnt;
}

ssize_t rio_readn(rio_t *rp, void *usrbuf, size_t n)
{
	ssize_t nread;
	char *bufp = usrbuf;
	ssize_t nleft = n;
	while( nleft > 0)
	{
		nread = rio_read(rp, bufp, n);
		if(nread == -1)
			return -1;
		if(nread == 0)
			break;
		nleft -= nread;
		bufp += nread;
	}
	return n-nleft;
}

ssize_t rio_readline(rio_t *rp, void *usrbuf, size_t maxlen)
{
	char *bufp = usrbuf;
	char c;
	int i;
	int nread;
	for(i=0; i<maxlen-1; ++i)
	{
		if((nread = rio_readn(rp, &c, 1)) == -1)
			return -1;
		else if(nread == 0)
		{
			if(i==0)
				return 0;
		}
		*bufp++ = c;
		if(c == '\n')
			break;
	}
	*bufp = '\0';
	return i;
}
ssize_t writen(rio_t *rp, size_t n)
{
    size_t nleft = n;
    ssize_t nwrite;

    char *bufp = rp->usrbuf;

    while(nleft > 0)
    {
        //nwrite == 0也属于错误
        if((nwrite = write(fd_, bufp, nleft)) <= 0)
        {
            if(errno == EINTR)
                nwrite = 0;
            else
                return -1; // -1 和 0
        }

        nleft -= nwrite;
        bufp += nwrite;
    }
    return n;  //这里不是 n- nleft 必须是n
}
int main(int argc, char * argv[])
{
	char buf[512]="";
	rio_t rio;
	int fd = open("test.txt",O_RDONLY);
	rio_init(&rio,fd);

//	rio_readn(&rio,buf,10);
//	puts(buf);
	while(rio_readline(&rio, buf, 1024)>0)
	{
		printf("%s",buf);
		printf("---------------\n");
	}
}
