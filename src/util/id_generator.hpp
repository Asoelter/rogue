#ifndef ID_GENERATOR_H
#define ID_GENERATOR_H

#include <stddef.h>

using id_type = size_t;

class IdGenerator
{
public:
    IdGenerator() = default;

    static size_t generate() 
    {
        static size_t currentId = 0;
        return ++currentId;
    }
};

#endif //ID_GENERATOR_H
