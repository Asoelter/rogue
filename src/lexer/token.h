#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <util/type_id_generator.hpp>

#include "namespace.h"

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

    size_t line() const;
    size_t column() const;
private:
    size_t line_;
    size_t column_;
};

template<typename T>
class DerivedToken : public Token
{
public:
    DerivedToken(size_t line, size_t column, const T & value);
    DerivedToken(const DerivedToken& rhs) = default;
    DerivedToken(DerivedToken&& rhs) = default;

    virtual ~DerivedToken() = default;

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

using IntLitToken = DerivedToken<int>;
using StringLitToken = DerivedToken<std::string>;
using IdentifierToken = DerivedToken<std::string>;

LEXER_NAMESPACE_END

#include "token.hpp"

#endif //TOKEN_H
