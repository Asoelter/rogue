#include "rogue_string.h"

#include <cassert>
#include <cstring>

#include <util/allocator.h>

String::String()
    : representation_{}
{
    
}

String::String(const char* text)
    : representation_{}
{
    const auto textSize = strlen(text);

    if(textSize < smallStringCapacity_)
    {
        memcpy(representation_.smallRep.buffer, text, textSize);
        representation_.smallRep.size = static_cast<unsigned char>(textSize);
    }
    else
    {
        reserve(textSize);
        memcpy(representation_.largeRep.buffer, text, textSize);
    }
}

String::String(const String& rhs)
    : representation_{}
{
    
}

String::String(String&& rhs) noexcept
    : representation_{}
{
    if(rhs.isSmall())
    {
        memcpy(representation_.smallRep.buffer, rhs.representation_.smallRep.buffer, rhs.size());
        representation_.smallRep.size = static_cast<unsigned char>(rhs.size());
    }
    else
    {
        representation_.largeRep.buffer = rhs.representation_.largeRep.buffer;
        rhs.representation_.largeRep.buffer = nullptr;
        representation_.largeRep.capacity = rhs.representation_.largeRep.capacity;
    }
}

String& String::operator=(const char* text)
{
    
    return *this;
}

String& String::operator=(const String& rhs)
{
    
    return *this;
}

String& String::operator=(String&& rhs)
{
    return *this;
}

char String::operator[](size_t index) const
{
   if(isSmall())
   {
       return representation_.smallRep.buffer[index];
   }

   return representation_.largeRep.buffer[index];
}

char& String::operator[](size_t index)
{
   if(isSmall())
   {
       return representation_.smallRep.buffer[index];
   }

   return representation_.largeRep.buffer[index];
}

void String::push_back(char c)
{
    if(full())
    {
        reserve(2 * size());
    }

    this->operator[](size()) = c;
    increaseSize();
}

void String::pop_back()
{
    assert(size() > 0);
    decreaseSize();
}

size_t String::size() const noexcept
{
    return representation_.smallRep.size;
}

bool String::empty() const noexcept
{
    return size() == 0;
}

bool String::full() const noexcept
{
    if(isSmall())
    {
        return size() >= smallStringCapacity_ - 1;
    }

    return size() >= representation_.largeRep.capacity - 1;
}

const char* String::c_str()
{
    if(isSmall())
    {
        return representation_.smallRep.buffer;
    }

    return representation_.largeRep.buffer;
}

bool String::isSmall() const noexcept
{
    assert(representation_.largeRep.size == representation_.smallRep.size);
    return representation_.smallRep.size < smallStringCapacity_;
}

void String::reserve(size_t size)
{
    if(size < this->size() || size < smallStringCapacity_)
    {
        return;
    }

    representation_.largeRep.buffer = GlobalAllocator::allocate<char>(size);
    representation_.largeRep.size = size;
    representation_.largeRep.capacity = 2 * size;
}

void String::increaseSize()
{
    if(isSmall())
    {
        ++representation_.smallRep.size;
        return;
    }

    ++representation_.largeRep.size;
}

void String::decreaseSize()
{
    if(isSmall())
    {
        --representation_.smallRep.size;
        return;
    }

    --representation_.largeRep.size;
}
