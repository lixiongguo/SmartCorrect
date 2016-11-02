#ifndef QUERY_H_
#define QUERY_H_
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<fstream>
#include<sstream>
#include<string.h>

struct Data{    
        bool operator<(const Data& data2)const{
         return freq_ > data2.freq_;
        }
        bool operator==(const Data& data2)const{
            return word_ == data2.word_;
        }
        bool operator!=(const Data& data2)const{
            return word_ != data2.word_;
        }
        std::string word_;
        int freq_;
};
void vecdo(std::vector<Data>&vec);
void  query(std::string query,std::string& result1,std::string& result2);
#endif
