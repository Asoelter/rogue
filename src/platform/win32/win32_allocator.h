#ifndef WIN32_ALLOCATOR_H
#define WIN32_ALLOCATOR_H

#include "win32.h"

class GlobalAllocator
{
public:
    ~GlobalAllocator();

    static void* allocate(size_t bytes);
    static void deallocate(void* ptr);

    template<typename T>
    static T* allocate(size_t bytes)
    {
        return reinterpret_cast<T*>(allocate(bytes));
    }

    template<typename T>
    static void deallocate(T* ptr)
    {
        deallocate(reinterpret_cast<void*>(ptr));
    }

private:
    GlobalAllocator();
    static HANDLE heapHandle_;
};

class LocalStackAllocator
{
public:
    LocalStackAllocator();

    void* allocate(size_t bytes);
    void deallocate(void* ptr);

    template<typename T>
    T* allocate(size_t amount)
    {
        return static_cast<T*>(allocate(amount * sizeof(T)));
    }

    template<typename T>
    void deallocate(T* ptr)
    {
        deallocate(reinterpret_cast<void*>(ptr));
    }

private:
    using Byte = unsigned char;
    static constexpr auto chunkSize = 4000;

    Byte* buffer_;
    Byte* frontier_;
};

#endif //WIN32_ALLOCATOR_H
