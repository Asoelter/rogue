#ifndef TOKEN_GENERATOR_H
#define TOKEN_GENERATOR_H

#include <memory>
#include <string>

#include "token.h"

LEXER_NAMESPACE_BEGIN

class TokenGenerator
{
public:
    using Ptr = std::unique_ptr<TokenGenerator>;

    virtual ~TokenGenerator() = default;

    virtual std::unique_ptr<Token> generate(size_t line, size_t column, const std::string& value) = 0;
    virtual std::unique_ptr<Token> generate(size_t line, size_t column, std::string&& value) = 0;
};

class IntLitTokenGenerator : public TokenGenerator
{
public:
    std::unique_ptr<Token> generate(size_t line, size_t column, const std::string& value) override;
    std::unique_ptr<Token> generate(size_t line, size_t column, std::string&& value) override;
};

class StringLitTokenGenerator : public TokenGenerator
{
public:
    std::unique_ptr<Token> generate(size_t line, size_t column, const std::string& value) override;
    std::unique_ptr<Token> generate(size_t line, size_t column, std::string&& value) override;
};

class IdTokenGenerator : public TokenGenerator
{
public:
    std::unique_ptr<Token> generate(size_t line, size_t column, const std::string& value) override;
    std::unique_ptr<Token> generate(size_t line, size_t column, std::string&& value) override;
};

template<typename T, T V>
class EnumeratedTokenGenerator : public TokenGenerator
{
public:
    std::unique_ptr<Token> generate(size_t line, size_t column, const std::string&) override
    {
        return std::make_unique<EnumeratedToken<T, V>>(line, column);
    }

    std::unique_ptr<Token> generate(size_t line, size_t column, std::string&&) override
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
using PlusEqTokenGenerator    = SymbolTokenGenerator<Symbol::PlusEq>;
using MinusTokenGenerator     = SymbolTokenGenerator<Symbol::Minus>;
using MinusEqTokenGenerator   = SymbolTokenGenerator<Symbol::MinusEq>;
using TimesTokenGenerator     = SymbolTokenGenerator<Symbol::Times>;
using TimesEqTokenGenerator   = SymbolTokenGenerator<Symbol::TimesEq>;
using DivTokenGenerator       = SymbolTokenGenerator<Symbol::Div>;
using DivEqTokenGenerator     = SymbolTokenGenerator<Symbol::DivEq>;
using EqualsTokenGenerator    = SymbolTokenGenerator<Symbol::Equals>;
using LessTokenGenerator      = SymbolTokenGenerator<Symbol::Less>;
using LessEqTokenGenerator    = SymbolTokenGenerator<Symbol::LessEq>;
using GreaterTokenGenerator   = SymbolTokenGenerator<Symbol::Greater>;
using GreaterEqTokenGenerator = SymbolTokenGenerator<Symbol::GreaterEq>;
using PipeTokenGenerator      = SymbolTokenGenerator<Symbol::Pipe>;
using AmpersandTokenGenerator = SymbolTokenGenerator<Symbol::Ampersand>;
using OrTokenGenerator        = SymbolTokenGenerator<Symbol::Or>;
using AndTokenGenerator       = SymbolTokenGenerator<Symbol::And>;

template<Keyword K>
using KeywordTokenGenerator = EnumeratedTokenGenerator<Keyword, K>;

using IfTokenGenerator     = KeywordTokenGenerator<Keyword::If>;
using ElseTokenGenerator   = KeywordTokenGenerator<Keyword::Else>;
using WhileTokenGenerator  = KeywordTokenGenerator<Keyword::While>;
using ForTokenGenerator    = KeywordTokenGenerator<Keyword::For>;
using IntTokenGenerator    = KeywordTokenGenerator<Keyword::Int>;
using CharTokenGenerator   = KeywordTokenGenerator<Keyword::Char>;
using BoolTokenGenerator   = KeywordTokenGenerator<Keyword::Bool>;
using TrueTokenGenerator   = KeywordTokenGenerator<Keyword::True>;
using FalseTokenGenerator  = KeywordTokenGenerator<Keyword::False>;
using ReturnTokenGenerator = KeywordTokenGenerator<Keyword::Return>;

LEXER_NAMESPACE_END

#endif //TOKEN_GENERATOR_H
