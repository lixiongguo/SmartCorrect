#ifndef RIO_H_
#define RIO_H_

#include"NonCopyable.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>

#define  MAXLINE 1024
#define  RIO_BUFFER 8192

class Rio : private NonCopyable
{
	public :
	explicit Rio(int fd);
	ssize_t readn( char *usrbuf, size_t n);
	ssize_t readline(char *usrbuf, size_t maxlen);
	ssize_t writen(const char *usrbuf, size_t n);

	private :
		size_t rio_read(char *buf, int n);

		int fd_;
		int left_;
		char *bufptr_;
		char buffer_[RIO_BUFFER];
};

#endif
