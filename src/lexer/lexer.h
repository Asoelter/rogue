#ifndef LEXER_H
#define LEXER_H

#include <memory>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

#include "namespace.h"
#include "regex.h"
#include "token_generator.h"

LEXER_NAMESPACE_BEGIN

class Token;

class Lexer
{
public:
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

    Lexer() = default;

    void addRule(Rule&& rule);

    std::vector<std::unique_ptr<Token>> lex(const std::string& fileName);

private:
    void resetActiveRules();
    void updateActiveRules(char c);
    void updateLineAndColumn(char c, size_t& line, size_t& column);

private:
    std::vector<Rule> rules_;
    std::unordered_set<Rule*> activeRules_;
    std::stack<Rule*> rejectedRules_;
};

LEXER_NAMESPACE_END

#endif //LEXER_H
