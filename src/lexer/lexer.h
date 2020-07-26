#ifndef LEXER_H
#define LEXER_H

#include <memory>
#include <regex>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

#include "namespace.h"
#include "token_generator.h"

#define USE_CUSTOM_REGEX

#ifdef USE_CUSTOM_REGEX
#   include "regex.h"
#endif

LEXER_NAMESPACE_BEGIN

class Token;

class Lexer
{
public:
#ifdef USE_CUSTOM_REGEX
    struct Rule
    {
        Rule(std::unique_ptr<Regex> p, std::unique_ptr<TokenGenerator>&& g)
            : pattern(std::move(p))
            , generator(std::move(g))
        {
            
        }

        std::unique_ptr<Regex> pattern;
        std::unique_ptr<TokenGenerator> generator;
    };
#else
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
#endif

    Lexer() = default;

    void addRule(Rule&& rule);

    std::vector<std::unique_ptr<Token>> lex(const std::string& fileName);
private:
#ifdef USE_CUSTOM_REGEX
    std::vector<Rule> rules_;
    std::unordered_set<Rule*> activeRules_;
    std::stack<Rule*> rejectedRules_;
#else
    std::vector<Rule> rules_;
    std::vector<Rule*> matches_;
#endif
};

LEXER_NAMESPACE_END

#endif //LEXER_H
