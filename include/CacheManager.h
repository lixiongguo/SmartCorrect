#include "../include/Cache.h"
#include <libServer/MutexLock.h>
#define Cache_Num 3
class CacheManager{
    public :
       CacheManager(const std::string&, const std::string&);
       void writeToDisk();
       int getCache();
       void putCache(int i);
       void insert(const std::string&, const std::string&);
       bool query(const std::string&, std::string& );
        Cache caches_[Cache_Num];
    private:
     MutexLock cache_manager_lock_;
     bool cacheFree_[Cache_Num];
};
