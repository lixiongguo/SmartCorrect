#include "Rio.h"

Rio::Rio(int fd)
	:fd_(fd),bufptr_(buffer_),left_(0)
{}

size_t Rio::rio_read(char *buf, int n)
{
	size_t  nread;
	while(left_<= 0)
	{
		nread = read(fd_, buffer_, sizeof(buffer_));
		bufptr_ = buffer_;
		if(nread==-1)
		{
			if(errno == EINTR)
				continue;
			else 
				return -1;
		}
		else if(nread == 0) 
			return 0;
		left_ += nread;
	}
	int cnt = n;
	if(left_ < cnt) cnt = left_;
	memcpy(buf, bufptr_,cnt);
	left_-= cnt;
	bufptr_ += cnt;
	return cnt;
}

ssize_t Rio::readn(char *usrbuf, size_t n)
{
	ssize_t nread;
	char *bufp = usrbuf;
	ssize_t nleft = n;
	while( nleft > 0)
	{
		nread = rio_read(bufp, n);
		if(nread == -1)
			return -1;
		if(nread == 0)
			break;
		nleft -= nread;
		bufp += nread;
	}
	return n-nleft;
}


ssize_t Rio::readline(char *usrbuf, size_t maxlen)
{
	char *bufp = usrbuf;
	char c;
	int i;
	int nread;
	for(i=0; i<maxlen-1; ++i)
	{
		if((nread = readn(&c, 1)) == -1)
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

ssize_t Rio :: writen(const char *usrbuf, size_t n)
{
	size_t nleft = n;
	ssize_t nwrite;

	const char *bufp = usrbuf;
	while(nleft > 0)
	{
		if((nwrite=(write(fd_, bufp, nleft)))== -1)
		{
			if(errno == EINTR)
			{
				nwrite =0;
			}
			else 
			  return -1;
		}
		nleft -= nwrite;
		bufp += nwrite;
	}
	return n;
}



