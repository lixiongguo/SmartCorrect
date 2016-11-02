#########################################################################
# File Name: test1.sh
# Author: Comst
# mail: 750145240@qq.com
# Created Time: Wed 06 Aug 2014 08:44:38 PM CST
#########################################################################
#!/bin/bash
g++ -o test1 test_tcp_conn.cpp Socket.cpp Rio.cpp TcpConnection.cpp net.c -std=c++0x
