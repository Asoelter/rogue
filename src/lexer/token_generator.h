#ifndef TOKEN_GENERATOR_H
#define TOKEN_GENERATOR_H

#include <memory>
#include <string>

#include "token.h"

LEXER_NAMESPACE_BEGIN

class TokenGenerator
{
public:
    virtual ~TokenGenerator() = default;

    virtual std::unique_ptr<Token> generate(size_t line, size_t column, const std::string & value) = 0;
};

class IntLitTokenGenerator : public TokenGenerator
{
public:
    std::unique_ptr<Token> generate(size_t line, size_t column, const std::string& value) override;
};

class StringLitTokenGenerator : public TokenGenerator
{
public:
    std::unique_ptr<Token> generate(size_t line, size_t column, const std::string& value) override;
};

class IdTokenGenerator : public TokenGenerator
{
public:
    std::unique_ptr<Token> generate(size_t line, size_t column, const std::string& value) override;
};

LEXER_NAMESPACE_END

#endif //TOKEN_GENERATOR_H
