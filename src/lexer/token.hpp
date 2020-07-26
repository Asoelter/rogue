#include <stdexcept>

LEXER_NAMESPACE_BEGIN

inline Token::Token(size_t line, size_t column)
    : line_(line)
    , column_(column)
{
    
}

inline size_t Token::line() const
{
    return line_;
}

inline size_t Token::column() const
{
    return column_;
}

template<typename T, typename ForIdGen>
DerivedToken<T, ForIdGen>::DerivedToken(size_t line, size_t column, const T & value)
    : Token(line, column)
    , value_(value)
{
    
}

template<typename T, typename ForIdGen>
type_id DerivedToken<T, ForIdGen>::type() const 
{
    return TypeIdGenerator<DerivedToken<T, ForIdGen>>::generate();
}

template<typename T, typename ForIdGen>
std::string DerivedToken<T, ForIdGen>::toString() const 
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

template<typename T, typename ForIdGen>
const T& DerivedToken<T, ForIdGen>::value() const
{
    return value_;
}

template<typename T, T V>
EnumeratedToken<T, V>::EnumeratedToken(size_t line, size_t column)
    : Token(line, column)
{

}

template<typename T, T V>
type_id EnumeratedToken<T, V>::type() const
{
    return TypeIdGenerator<EnumeratedToken<T, V>>::generate();
}

template<typename T, T V>
std::string EnumeratedToken<T, V>::toString() const
{
    return lexer::toString(V);
}

template<typename T, T V>
const T EnumeratedToken<T, V>::value() const
{
    return V;
}

LEXER_NAMESPACE_END
