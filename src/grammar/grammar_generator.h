#ifndef GRAMMAR_GENERATOR_H
#define GRAMMAR_GENERATOR_H

#include <string>
#include <unordered_map>

#include <lexer/lexer.h>

#include <util/type_id.hpp>

class ProductionRule
{
public:
    ProductionRule() = default;

    void addToSequence(type_id id)
    {
        typeSequence_.push_back(id);
    }

    template<typename T>
    void addToSequence()
    {
        typeSequence_.push_back(TypeId<T>);
    }

private:
    std::vector<type_id> typeSequence_;
};

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
