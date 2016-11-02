#ifndef NONCOPYABLE_H_
#define NONCOPYABLE_H_
class NonCopyable
{
    public :
        NonCopyable();
        ~NonCopyable();
    private :
        NonCopyable(const NonCopyable &);
        void operator=(const NonCopyable &);
};
#endif
