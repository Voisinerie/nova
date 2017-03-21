#ifndef NON_COPYABLE_H
#define NON_COPYABLE_H

class NonCopyable
{
public:
    NonCopyable() {}
    ~NonCopyable() {}

    NonCopyable(const NonCopyable& rhs) = delete;
    NonCopyable& operator=(const NonCopyable& rhs) = delete;
};

#endif
