#ifndef TYPE_ID_GENERATOR_HPP
#define TYPE_ID_GENERATOR_HPP

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

#endif //TYPE_ID_GENERATOR_HPP
