#include"../include/CacheManager.h"
#include<stdlib.h>

using namespace std;

CacheManager::CacheManager(const string& cache_a,const string& cache_b)
{
   for(int i=0; i<Cache_Num; i++)
   {
        cacheFree_[i] = true;
        caches_[i].setCache_a(cache_a);
        caches_[i].setCache_b(cache_b);
        caches_[i].readDisk();
        caches_[i].setCacheSize(100);
   }
   srand(10086);
}

void CacheManager::writeToDisk()
{
    int cache_index = getCache();
    cout << "cache "<< cache_index<< " " << "write to disk" << endl;
   caches_[cache_index].writeDisk();
   putCache(cache_index);
}

int CacheManager::getCache()
{
    cache_manager_lock_.lock();
    int ix;
    int start = rand()%Cache_Num;
    int end = start + Cache_Num;
    for(ix=start; ix != end; ix++)
    {
          ix = ix%Cache_Num;
          if(cacheFree_[ix])
        {
           cacheFree_[ix]=false;
           break;
        }
    }
    cache_manager_lock_.unlock();
    return ix;
}

bool CacheManager::query(const string& s, string& result)
{
    int cache_index = getCache();
   if(caches_[cache_index].queryCache(s,result))
   {       
    cout << "query from cache "<<" "<< cache_index << endl;
    putCache(cache_index);
    return true;
   }
   else{
       putCache(cache_index);
    return false;
   }
}


void CacheManager::insert(const string& linea,const string& lineb)
{ 
   int cache_index = getCache();
    cout << "insert into cache "<<" "<< cache_index << endl;
   caches_[cache_index].insertCache(linea,lineb); 
   putCache(cache_index);
}

void CacheManager::putCache(int i)
{
    cache_manager_lock_.lock();
    cacheFree_[i]=true;
    cache_manager_lock_.unlock();
}

