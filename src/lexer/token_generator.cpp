#include "token_generator.h"

LEXER_NAMESPACE_BEGIN


std::unique_ptr<Token> IntLitTokenGenerator::generate(size_t line, size_t column, const std::string& value)
{
    return std::make_unique<IntLitToken>(line, column, std::stoi(value));
}

std::unique_ptr<Token> IntLitTokenGenerator::generate(size_t line, size_t column, std::string&& value)
{
    return std::make_unique<IntLitToken>(line, column, std::stoi(value));
}

std::unique_ptr<Token> StringLitTokenGenerator::generate(size_t line, size_t column, const std::string& value)
{
    auto copy = value;
    return generate(line, column, std::move(copy));
}

std::unique_ptr<Token> StringLitTokenGenerator::generate(size_t line, size_t column, std::string&& value)
{
    return std::make_unique<StringLitToken>(line, column, std::move(value));
}

std::unique_ptr<Token> IdTokenGenerator::generate(size_t line, size_t column, const std::string& value)
{
    auto copy = value;
    return generate(line, column, std::move(copy));
}

std::unique_ptr<Token> IdTokenGenerator::generate(size_t line, size_t column, std::string&& value)
{
    return std::make_unique<IdentifierToken>(line, column, std::move(value));
}

LEXER_NAMESPACE_END