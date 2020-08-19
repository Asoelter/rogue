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
    PlusEq,
    Minus,
    MinusEq,
    Times,
    TimesEq,
    Div,
    DivEq,
    Equals,
    Less,
    LessEq,
    Greater,
    GreaterEq,
    Pipe,
    Ampersand,
    Or,
    And,
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
    case Symbol::PlusEq:    return "PlusEq";
    case Symbol::Minus:     return "Minus";
    case Symbol::MinusEq:   return "MinusEq";
    case Symbol::Times:     return "Times";
    case Symbol::TimesEq:   return "TimesEq";
    case Symbol::Div:       return "Div";
    case Symbol::DivEq:     return "DivEq";
    case Symbol::Equals:    return "Equals";
    case Symbol::Less:      return "Less";
    case Symbol::LessEq:    return "LessEq";
    case Symbol::Greater:   return "Greater";
    case Symbol::GreaterEq: return "GreaterEq";
    case Symbol::Pipe:      return "Pipe";
    case Symbol::Ampersand: return "Ampersand";
    case Symbol::Or:        return "Or";
    case Symbol::And:       return "And";
    default:                return "Unkown";
    }
}

LEXER_NAMESPACE_END

#endif //SYMBOLS_H
