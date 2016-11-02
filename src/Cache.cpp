#include "../include/Cache.h"
using namespace std;

Cache::Cache()
{}
Cache::Cache(const string& cache_a,const string& cache_b)
			:cache_a_(cache_a),cache_b_(cache_b)
{

}
void Cache::setCache_a(const string& cache_a)
{
    cache_a_ = cache_a;
}
void Cache::setCache_b(const string& cache_b)
{
    cache_b_ = cache_b;
}
void Cache::setCacheSize(const int size)
{
    Cache_Size_ = size;
}
void Cache::insertCache(const string& linea,const string& lineb)
{ 
       list_.push_back(linea);
       list<string>::iterator it = list_.end();
       it--;
      cache_[linea]=make_pair(lineb,it);
      if(cache_.size() > Cache_Size_)
      {
          string s = *list_.begin();
          list_.pop_front();    
          cache_.erase(s);
       }
}

bool Cache::queryCache(const string& query,string& result){
    string lineb;
    bool flag = false;
    if(cache_.count(query))
    {
       lineb = cache_[query].first;
       result = process(lineb);

       list_.erase(cache_[query].second);
       list_.push_back(query);
       list<string>::iterator it = list_.end();
       it--;
       cache_[query] = make_pair(lineb,it);
       flag =true;
    }
    return flag;
}

void Cache:: writeDisk()
{
            cout << "Begin to write to disk cache file"<< endl;
             ofstream ofsa_,ofsb_;
             ofsa_.open(cache_a_.c_str());
             ofsb_.open(cache_b_.c_str());
            if(!ofsa_ || !ofsb_)printf("open failed");
            list<string>::iterator it = list_.begin();
            while(it != list_.end())
            {
                string s = *it;
                cout << "cache go "<< s << endl;
                ofsa_ << s << endl;
                ofsb_ << cache_[s].first << endl;
                it++;
            }
            ofsa_.close();
            ofsb_.close();
}



void  Cache::readDisk()
{
        cout <<"Begin to read disk cache file" << endl;
          ifstream ifsa_,ifsb_;
          ifsa_.open(cache_a_.c_str());
          ifsb_.open(cache_b_.c_str());
          //ifsa_.open("../dat/cache_a.txt");
          //ifsb_.open("../dat/cache_b.txt");
          if(!ifsa_ || !ifsb_)cout << "open cache file fail"<<endl;
          string linea;
          string lineb;
            while(getline(ifsa_,linea) && getline(ifsb_,lineb))
            {
                cout << "Read " << " " << linea << endl;
                list_.push_back(linea);
                list<string>::iterator it = list_.end();
                it--;
                cache_[linea]=make_pair(lineb,it);
            }
            ifsa_.close();
            ifsb_.close();
}


string  Cache::process(string lineb)
{
     char str[128] = "";
     string::size_type ix=0;
    while(ix != lineb.size())
    {
        if(lineb[ix]==' ')
            str[ix] = '\n';
        else str[ix] = lineb[ix];
        ix++;
    }
    str[ix] = '\n';
    string nlineb(str);
    return nlineb ;
}
