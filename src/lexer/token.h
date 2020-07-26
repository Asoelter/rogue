#ifndef TOKEN_H
#define TOKEN_H

#include <string>

#include <util/type_id_generator.hpp>

#include "keyword.h"
#include "namespace.h"
#include "symbol.h"

LEXER_NAMESPACE_BEGIN

class Token
{
public:
    Token(size_t line, size_t column);
    Token(const Token& rhs) = default;
    Token(Token&& rhs) = default;

    virtual ~Token() = default;

    Token& operator=(const Token& rhs) = default;
    Token& operator=(Token&& rhs) = default;

    [[nodiscard]]
    virtual type_id type() const = 0;

    [[nodiscard]]
    virtual std::string toString() const = 0;

    [[nodiscard]]
    size_t line() const;

    [[nodiscard]]
    size_t column() const;
private:
    size_t line_;
    size_t column_;
};

template<typename T, typename ForIdGen = T>
class DerivedToken : public Token
{
public:
    DerivedToken(size_t line, size_t column, const T & value);
    DerivedToken(const DerivedToken& rhs) = default;
    DerivedToken(DerivedToken&& rhs) = default;

    ~DerivedToken() override = default;

    DerivedToken& operator=(const DerivedToken& rhs) = default;
    DerivedToken& operator=(DerivedToken&& rhs) = default;

    [[nodiscard]]
    type_id type() const override;

    [[nodiscard]]
    std::string toString() const override;

    const T& value() const;

private:
    T value_;
};

struct __IdentifierIdType{};

template<Symbol>
struct __SymbolIdType {};

template<typename T, T V>
class EnumeratedToken : public Token
{
public:
    EnumeratedToken(size_t line, size_t column);
    EnumeratedToken(const EnumeratedToken& rhs) = default;
    EnumeratedToken(EnumeratedToken&& rhs) = default;

    ~EnumeratedToken() override = default;

    EnumeratedToken& operator=(const EnumeratedToken& rhs) = default;
    EnumeratedToken& operator=(EnumeratedToken&& rhs) = default;

    [[nodiscard]]
    type_id type() const override;

    [[nodiscard]]
    std::string toString() const override;

    const T value() const;
};

using IntLitToken = DerivedToken<int>;
using StringLitToken = DerivedToken<std::string>;
using IdentifierToken = DerivedToken<std::string, __IdentifierIdType>;

template<Symbol S>
using SymbolToken = EnumeratedToken<Symbol, S>;

using LParenToken    = SymbolToken<Symbol::LParen>;
using RParenToken    = SymbolToken<Symbol::RParen>;
using LCurlyToken    = SymbolToken<Symbol::LCurly>;
using RCurlyToken    = SymbolToken<Symbol::RCurly>;
using CommaToken     = SymbolToken<Symbol::Comma>;
using DotToken       = SymbolToken<Symbol::Dot>;
using SemiColonToken = SymbolToken<Symbol::SemiColon>;
using PlusToken      = SymbolToken<Symbol::Plus>;
using MinusToken     = SymbolToken<Symbol::Minus>;
using EqualsToken    = SymbolToken<Symbol::Equals>;

template<Keyword K>
using KeywordToken = EnumeratedToken<Keyword, K>;

using IfToken    = KeywordToken<Keyword::If>;
using ElseToken  = KeywordToken<Keyword::Else>;
using WhileToken = KeywordToken<Keyword::While>;
using ForToken   = KeywordToken<Keyword::For>;
using IntToken   = KeywordToken<Keyword::Int>;
using CharToken  = KeywordToken<Keyword::Char>;
using BoolToken  = KeywordToken<Keyword::Bool>;
using TrueToken  = KeywordToken<Keyword::True>;
using FalseToken = KeywordToken<Keyword::False>;

LEXER_NAMESPACE_END

#include "token.hpp"

#endif //TOKEN_H
