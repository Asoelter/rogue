#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <vector>

#include <lexer/namespace.h>

#include "namespace.h"

class Statement {};

LEXER_FORWARD_DECLARE(Token);

PARSER_NAMESPACE_BEGIN

class Parser
{
public:
    using TokenStream = std::vector<std::unique_ptr<LEXER_NAMESPACE::Token>>;
    using StatementPtr = std::unique_ptr<Statement>;
    using Statements = std::vector<StatementPtr>;

    Parser() = default;

    Statements parse(const TokenStream& tokens);

};

PARSER_NAMESPACE_END

#endif //PARSER_H
