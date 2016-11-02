#########################################################################
# File Name: test1.sh
# Author: Comst
# mail: 750145240@qq.com
# Created Time: Wed 06 Aug 2014 08:44:38 PM CST
#########################################################################
#!/bin/bash
g++ -o test4 test_tcp_server3.cpp TcpServer.cpp PollPoller.cpp Socket.cpp InetAddress.cpp Rio.cpp TcpConnection.cpp net.c ThreadPool.cpp Thread.cpp Condition.cpp -lpthread -std=c++0x

