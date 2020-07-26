#ifndef LEXER_H
#define LEXER_H

#include <memory>
#include <regex>
#include <string>
#include <vector>

#include "namespace.h"
#include "token_generator.h"

LEXER_NAMESPACE_BEGIN

class Token;

class Lexer
{
public:
    struct Rule
    {
        Rule(const char * p, std::unique_ptr<TokenGenerator>&& g)
            : pattern(p)
            , generator(std::move(g))
        {
            
        }

        std::regex pattern;
        std::unique_ptr<TokenGenerator> generator;
    };

    Lexer() = default;

    void addRule(Rule&& rule);

    std::vector<std::unique_ptr<Token>> lex(const std::string& fileName);
private:
    std::vector<Rule> rules_;
};

LEXER_NAMESPACE_END

#endif //LEXER_H
