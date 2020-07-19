#include "lexer.h"

LEXER_NAMESPACE_BEGIN

void Lexer::addRule(std::string&& rule)
{
    rules_.emplace_back(rule);
}

LEXER_NAMESPACE_END