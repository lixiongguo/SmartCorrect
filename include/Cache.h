#ifndef CACHE_H_
#define CACHE_H_

#include <unordered_map>
#include <map>
#include <list>
#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>
#include <fstream>

class Cache
{
    public:
        Cache();
        Cache(const std::string&,const std::string&);
void setCache_a(const std::string& );
void setCache_b(const std::string& );
void setCacheSize(const int );
        void readDisk();
        void writeDisk();
        bool queryCache(const std::string& , std::string& );
       void insertCache(const std::string& ,const std::string&);

    private:
        std::string process(std::string lineb);
       
        struct hash_str{
            size_t operator()(const std::string& s)const
            {
                char str1[128]="";
                ::strcpy(str1,s.c_str());
                char *str=str1;
                unsigned int hash= 131542311;
                while(*str)
                {
                    hash^=((hash<<5)+(*str++)+(hash>>2));
                }

                return (hash & 0x7FFFFFFF);
            }
        };
        struct equal_str{
            bool operator()(const std::string&a, const std::string&b)const
            {
                return a==b;
            }
};        
      std::unordered_map<std::string,std::pair<std::string,std::list<std::string>::iterator> ,hash_str,equal_str>cache_;
      std::list<std::string>list_;

      std::string cache_a_;
      std::string cache_b_;
      int Cache_Size_;
};
#endif
