#include "capped_vector.h"

#include <stdexcept>

template<typename T, size_t Cap>
CappedVector<T, Cap>::CappedVector(const std::initializer_list<T>& values)
    : size_(values.size())
{
    if(size() > capacity())
    {
       //TODO(asoelter): throw exception (std or home brew?)
       throw std::runtime_error("cannot push back on a full vector");
    }

    std::copy(values.begin(), values.end(), values_.begin());
}

template<typename T, size_t Cap>
template<typename ... Args>
void CappedVector<T, Cap>::emplace_back(const Args&... args)
{
   if(full())
   {
       //TODO(asoelter): std or home brew?
       throw std::runtime_error("cannot push back on a full vector");
   }

    values_[size_++] = T(std::forward(args...));
}

template<typename T, size_t Cap>
void CappedVector<T, Cap>::push_back(const T& value)
{
   if(full())
   {
       //TODO(asoelter): std or home brew?
       throw std::runtime_error("cannot push back on a full vector");
   }

   values_[size_++] = value;
}

template<typename T, size_t Cap>
void CappedVector<T, Cap>::pop_back()
{
    if(empty())
    {
        throw std::runtime_error("cannot pop_back from an empty vector");
    }

    --size_;
}

template<typename T, size_t Cap>
template<typename InputIterator>
void CappedVector<T, Cap>::append(InputIterator begin, InputIterator end)
{
    while(begin != end)
    {
        push_back(*begin);
        ++begin;
    }
}

template<typename T, size_t Cap>
typename CappedVector<T, Cap>::const_reference CappedVector<T, Cap>::operator[](size_t index) const
{
    return values_[index];
}

template<typename T, size_t Cap>
typename CappedVector<T, Cap>::reference CappedVector<T, Cap>::operator[](size_t index)
{
    return values_[index];
}

template<typename T, size_t Cap>
typename CappedVector<T, Cap>::iterator CappedVector<T, Cap>::begin()
{
    return &values_[0];
}

template<typename T, size_t Cap>
typename CappedVector<T, Cap>::iterator CappedVector<T, Cap>::end()
{
    return &values_[size_];
}

template<typename T, size_t Cap>
typename CappedVector<T, Cap>::const_iterator CappedVector<T, Cap>::begin() const
{
    return &values_[0];
}

template<typename T, size_t Cap>
typename CappedVector<T, Cap>::const_iterator CappedVector<T, Cap>::end() const
{
    return &values_[size_];
}

template<typename T, size_t Cap>
size_t CappedVector<T, Cap>::capacity()
{
    return Cap;
}

template<typename T, size_t Cap>
size_t CappedVector<T, Cap>::size() const noexcept
{
    return size_;
}

template<typename T, size_t Cap>
bool CappedVector<T, Cap>::empty() const noexcept
{
    return size_ == 0;
}

template<typename T, size_t Cap>
bool CappedVector<T, Cap>::full() const noexcept
{
    return size_ == Cap;
}

