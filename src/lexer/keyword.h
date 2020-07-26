#ifndef KEYWORD_H
#define KEYWORD_H

#include <string>

#include "namespace.h"

LEXER_NAMESPACE_BEGIN

enum class Keyword
{
    If, 
    Else, 
    While, 
    For,
    Int, 
    Char, 
    Bool, 
    True,
    False
};

inline std::string toString(Keyword k)
{
    switch (k)
    {
    case Keyword::If:    return "If";
    case Keyword::Else:  return "Else";
    case Keyword::While: return "While";
    case Keyword::For:   return "For";
    case Keyword::Int:   return "Int";
    case Keyword::Char:  return "Char";
    case Keyword::Bool:  return "Bool";
    case Keyword::True:  return "True";
    case Keyword::False: return "False";
    default:             return "Unkown";
    }
}

LEXER_NAMESPACE_END

#endif //KEYWORD_H
