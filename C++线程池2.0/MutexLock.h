#ifndef MUTEXLOCK_H_
#define MUTEXLOCK_H_

#include<pthread.h>
#include"NonCopyable.h"

class MutexLock : NonCopyable
{
	public :
		MutexLock();
		~MutexLock();
		void lock();
		void unlock();

		pthread_mutex_t *getMutexPtr(){return &mutex_;}
		bool isLocked()const {return isLocked_;}
	private :
		pthread_mutex_t mutex_;
		bool isLocked_;
};
inline MutexLock::MutexLock()
{
	pthread_mutex_init(&mutex_, NULL);
}

inline MutexLock::~MutexLock()
{
	pthread_mutex_destroy(&mutex_);
}

inline void MutexLock::lock()
{
	pthread_mutex_lock(&mutex_);
}

inline void MutexLock::unlock()
{
	pthread_mutex_unlock(&mutex_);
}

class MutexLockGuard
{
	public :
		MutexLockGuard(MutexLock &mutex);
		~MutexLockGuard();
	private :
		MutexLock &mutex_;
};

inline MutexLockGuard::MutexLockGuard(MutexLock &mutex)
		:mutex_(mutex)
{
	mutex_.lock();
}

inline MutexLockGuard::~MutexLockGuard()
{
	mutex_.unlock();
}

#define MutexLockGuard(m)"ERROR"
#endif
