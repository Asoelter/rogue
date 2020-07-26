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

template<typename T, T V>
class EnumeratedTokenGenerator : public TokenGenerator
{
public:
    std::unique_ptr<Token> generate(size_t line, size_t column, const std::string&) override
    {
        return std::make_unique<EnumeratedToken<T, V>>(line, column);
    }
};

template<Symbol S>
using SymbolTokenGenerator = EnumeratedTokenGenerator<Symbol, S>;

using LParenTokenGenerator    = SymbolTokenGenerator<Symbol::LParen>;
using RParenTokenGenerator    = SymbolTokenGenerator<Symbol::RParen>;
using LCurlyTokenGenerator    = SymbolTokenGenerator<Symbol::LCurly>;
using RCurlyTokenGenerator    = SymbolTokenGenerator<Symbol::RCurly>;
using CommaTokenGenerator     = SymbolTokenGenerator<Symbol::Comma>;
using DotTokenGenerator       = SymbolTokenGenerator<Symbol::Dot>;
using SemiColonTokenGenerator = SymbolTokenGenerator<Symbol::SemiColon>;
using PlusTokenGenerator      = SymbolTokenGenerator<Symbol::Plus>;
using MinusTokenGenerator     = SymbolTokenGenerator<Symbol::Minus>;
using EqualsTokenGenerator    = SymbolTokenGenerator<Symbol::Equals>;

template<Keyword K>
using KeywordTokenGenerator = EnumeratedTokenGenerator<Keyword, K>;

using IfTokenGenerator    = KeywordTokenGenerator<Keyword::If>;
using ElseTokenGenerator  = KeywordTokenGenerator<Keyword::Else>;
using WhileTokenGenerator = KeywordTokenGenerator<Keyword::While>;
using ForTokenGenerator   = KeywordTokenGenerator<Keyword::For>;
using IntTokenGenerator   = KeywordTokenGenerator<Keyword::Int>;
using CharTokenGenerator  = KeywordTokenGenerator<Keyword::Char>;
using BoolTokenGenerator  = KeywordTokenGenerator<Keyword::Bool>;
using TrueTokenGenerator  = KeywordTokenGenerator<Keyword::True>;
using FalseTokenGenerator = KeywordTokenGenerator<Keyword::False>;

LEXER_NAMESPACE_END

#endif //TOKEN_GENERATOR_H
