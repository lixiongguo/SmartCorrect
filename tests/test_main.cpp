#include "../include/SmartCorrect.h"
#include<stdlib.h>
using namespace std;

void Read_Config(int *p_port, string &cache_a , string &cache_b)
{

    string config_file="../config/config.txt";
    ifstream config_ifs;
    config_ifs.open(config_file.c_str());

    string line;
    string::size_type pos;
    string option;

    
    while(getline(config_ifs,line))
    {
        pos = line.find('=');
        option = line.substr(0,pos);
        if(option == "CACHE_A")   
        {
            cache_a = line.substr(pos+1,line.size());
        }
        else if(option == "CACHE_B")   
        {
            cache_b = line.substr(pos+1,line.size());
        }
        else if(option == "PORT")
        {
            *p_port=::atoi(line.substr(pos+1,line.size()).c_str());
        }
    }
}

int main(int argc,const char *argv[])
{

    string cache_a;
    string cache_b;
    int port;
    Read_Config(&port,cache_a,cache_b);
	InetAddress addr(port);
    SmartCorrect correct(addr,cache_a,cache_b);
	correct.start();
	return 0;
}
