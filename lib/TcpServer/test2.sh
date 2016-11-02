#########################################################################
# File Name: test1.sh
# Author: Comst
# mail: 750145240@qq.com
# Created Time: Wed 06 Aug 2014 08:44:38 PM CST
#########################################################################
#!/bin/bash
g++ -o test2 test_tcp_server.cpp TcpServer.cpp PollPoller.cpp Socket.cpp InetAddress.cpp Rio.cpp TcpConnection.cpp net.c -std=c++0x

