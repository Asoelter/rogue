#ifndef TYPE_ID_HPP
#define TYPE_ID_HPP

#include "id_generator.hpp"

using type_id = size_t;

template<typename T>
struct TypeIdGenerator
{
    static size_t generate()
    {
        static const auto id = IdGenerator::generate();
        return id;
    }
};

template<typename T>
const auto TypeId = TypeIdGenerator<T>::generate();

#endif //TYPE_ID_HPP
