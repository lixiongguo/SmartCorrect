#ifndef PTR_VECTOR_H_
#define PTR_VECTOR_H_

#include"NonCopyable.h"
#include<vector>

template <typename T>
class PtrVector : public std::vector<T*>,
				  private NonCopyable
{
	public :
		~PtrVector()
		{
			clear();
		}
		void push_back(T *val)
		{
			std::vector<T*>::push_back(val);
		}
		void clear()
		{
			typename std::vector<T*>::iterator it;
			for(it = std::vector<T*>::begin(); it != std::vector<T*>::end(); ++it)
			{
				delete *it;
			}
			std::vector<T*>::clear();
		}
};
#endif

