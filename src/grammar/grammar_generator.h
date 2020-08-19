#ifndef GRAMMAR_GENERATOR_H
#define GRAMMAR_GENERATOR_H

#include <string>
#include <unordered_map>

#include <lexer/lexer.h>

#include <util/type_id.hpp>

class GrammarGenerator
{
public: 
    GrammarGenerator();

    template<typename T>
    GrammarGenerator& addAlias(const std::string& alias)
    {
        ids_[alias] = TypeId<T>;
        return *this;
    }


    void readSpec(const std::string& specFileName);
private:
    LEXER_NAMESPACE::Lexer lexer_;
    std::unordered_map<std::string, type_id> ids_;
};

#endif //GRAMMAR_GENERATOR_H
