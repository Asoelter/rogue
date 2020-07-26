#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <string>

#include "namespace.h"

LEXER_NAMESPACE_BEGIN

enum class Symbol
{
    LParen, 
    RParen, 
    LCurly, 
    RCurly, 
    Comma, 
    Dot, 
    SemiColon, 
    Plus,
    Minus,
    Equals
};

inline std::string toString(Symbol s)
{
    switch (s)
    {
    case Symbol::LParen:    return "LParen";
    case Symbol::RParen:    return "RParen";
    case Symbol::LCurly:    return "LCurly";
    case Symbol::RCurly:    return "RCurly";
    case Symbol::Comma:     return "Comma";
    case Symbol::Dot:       return "Dot";
    case Symbol::SemiColon: return "SemiColon";
    case Symbol::Plus:      return "Plus";
    case Symbol::Minus:     return "Minus";
    case Symbol::Equals:    return "Equals";
    default:                return "Unkown";
    }
}

LEXER_NAMESPACE_END

#endif //SYMBOLS_H
