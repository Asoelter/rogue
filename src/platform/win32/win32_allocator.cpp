#include "allocator.h"

#include <new>
#include <stdexcept>

HANDLE GlobalAllocator::heapHandle_ = HeapCreate(0, 0, 0);

GlobalAllocator::GlobalAllocator()
{
    if(!heapHandle_)
    {
        throw std::bad_alloc();
    }
}

GlobalAllocator::~GlobalAllocator()
{
    HeapDestroy(heapHandle_);
}

void* GlobalAllocator::allocate(size_t bytes)
{
    return HeapAlloc(heapHandle_, 0, bytes);
}

void GlobalAllocator::deallocate(void* ptr)
{
    HeapFree(heapHandle_, 0, ptr);
}

LocalStackAllocator::LocalStackAllocator()
    : buffer_(GlobalAllocator::allocate<Byte>(chunkSize))
    , frontier_(buffer_)
{
    
}

void* LocalStackAllocator::allocate(size_t bytes)
{
    const auto rval = frontier_;
    frontier_ += bytes;
    return rval;
}

void LocalStackAllocator::deallocate(void* ptr)
{
#ifdef DEBUG
    if(ptr < buffer_ || ptr > buffer_ + chunkSize)
    {
        throw std::invalid_argument("failed to deallocate the pointer");
    }
#endif

    frontier_ = static_cast<Byte*>(ptr);
}
