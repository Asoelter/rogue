#ifndef CAPPED_VECTOR_H
#define CAPPED_VECTOR_H

#include <stddef.h>
#include <initializer_list>

template<typename T, size_t Cap>
class CappedVector
{
public:
    using iterator = T*;
    using const_iterator = T const*;
    using reference = T&;
    using const_reference = const T&;

    CappedVector() = default;
    CappedVector(const std::initializer_list<T>& values);
    CappedVector(const CappedVector& rhs) = default;
    CappedVector(CappedVector&& rhs) = default;
    ~CappedVector() = default;

    CappedVector& operator=(const CappedVector& rhs) = default;
    CappedVector& operator=(CappedVector&& rhs) = default;

    template<typename ... Args>
    void emplace_back(const Args&... args);

    void push_back(const T& value);
    void pop_back();

    template<typename InputIterator>
    void append(InputIterator begin, InputIterator end);

    const_reference operator[](size_t index) const;
    reference operator[](size_t index);

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    [[nodiscard]] static size_t capacity();
    [[nodiscard]] size_t size() const noexcept;
    [[nodiscard]] bool empty() const noexcept;
    [[nodiscard]] bool full() const noexcept;

private:
    size_t size_ = 0;
    T values_[Cap];
};

#include "capped_vector.hpp"

#endif //CAPPED_VECTOR_H
