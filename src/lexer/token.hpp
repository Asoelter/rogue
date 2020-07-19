#include <stdexcept>

LEXER_NAMESPACE_BEGIN

Token::Token(size_t line, size_t column)
    : line_(line)
    , column_(column)
{
    
}

size_t Token::line() const
{
    return line_;
}

size_t Token::column() const
{
    return column_;
}

template<typename T>
DerivedToken<T>::DerivedToken(size_t line, size_t column, const T & value)
    : Token(line, column)
    , value_(value)
{
    
}

template<typename T>
type_id DerivedToken<T>::type() const 
{
    return TypeIdGenerator<DerivedToken<T>>::generate();
}

template<typename T>
std::string DerivedToken<T>::toString() const 
{
    if constexpr (std::is_arithmetic_v<T>)
    {
        return std::to_string(value_);
    }
    else if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, const char *>)
    {
        return value_;
    }
    else
    {
        throw std::invalid_argument("Unknown type used as token parameter");
    }
}

template<typename T>
const T& DerivedToken<T>::value() const
{
    return value_;
}

LEXER_NAMESPACE_END
