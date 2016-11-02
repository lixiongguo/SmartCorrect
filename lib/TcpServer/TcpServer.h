#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include "NonCopyable.h"
#include "InetAddress.h"
#include "TcpConnection.h"
#include "Socket.h"
#include "Thread.h"
#include "PollPoller.h"
#include "ThreadPool.h"
#include <memory>

class TcpServer :private NonCopyable
{
	public :
		typedef TcpConnection::TcpConnectionCallback TcpCallback;
		typedef ThreadPool::Task ThreadTask;
		explicit TcpServer(const InetAddress &addr);

		void setConnectionCallback(const TcpCallback &cb)
		{onConnectionCallback_ = cb ;}
		void setMessageCallback(const TcpCallback &cb)
		{onMessageCallback_ = cb;}
		void setCloseCallback(const TcpCallback &cb)
		{onCloseCallback_ = cb;}

		void start();

	void poolAddTask(const ThreadTask &);

	private :
		std::unique_ptr<Socket>sock_;
		std::unique_ptr<PollPoller>poller_;
		std::unique_ptr<ThreadPool>pool_;

		TcpCallback onConnectionCallback_;
		TcpCallback onMessageCallback_;
		TcpCallback onCloseCallback_;
};

#endif
