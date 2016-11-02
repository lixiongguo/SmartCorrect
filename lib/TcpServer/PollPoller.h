#ifndef POLL_POLLER_H_
#define POLL_POLLER_H_

#include "NonCopyable.h"
#include "TcpConnection.h"
#include "InetAddress.h"

#include <map>
#include <functional>
#include <poll.h>

class PollPoller : private NonCopyable
{
	public :
		typedef TcpConnection::TcpConnectionCallback PollerCallback;
		explicit PollPoller(int listenfd);

		void poll();
		void handleAccept();
		void handleData();

		void handleConnectionEvent(int peerfd);
		void handleMessageEvent(int peerfd);
		void handleCloseEvent(int peerfd);


		void setConnectionCallback(const PollerCallback &cb)
		{onConnectionCallback_ = cb;}
		void setMessageCallback(const PollerCallback &cb)
		{onMessageCallback_ = cb;}
		void setCloseCallback(const PollerCallback &cb)
		{onCloseCallback_ = cb;}
	
	private :
		struct pollfd event_[2048];
		int listenfd_;
		int maxi_;
		int nready_;
		std::map<int, TcpConnectionPtr>lists_;
		typedef std::map<int, TcpConnectionPtr>::iterator TcpIterator;
		PollerCallback onConnectionCallback_;
		PollerCallback onMessageCallback_;
		PollerCallback onCloseCallback_;
};

#endif
