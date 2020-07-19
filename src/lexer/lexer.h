#ifndef LEXER_H
#define LEXER_H

#include <memory>
#include <regex>
#include <string>
#include <vector>

#include "namespace.h"

LEXER_NAMESPACE_BEGIN

class Token;

class Lexer
{
public:
    Lexer() = default;

    void addRule(std::string&& rule);

    //std::vector<std::unique_ptr<Token>> lex(const std::string& fileName);
private:
    std::vector<std::regex> rules_;
};

LEXER_NAMESPACE_END

#endif //LEXER_H
