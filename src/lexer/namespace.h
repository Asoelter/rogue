#ifndef LEXER_NAMESPACE_H
#define LEXER_NAMESPACE_H

#ifndef LEXER_NAMESPACE
#   define LEXER_NAMESPACE lexer
#endif 

#ifndef LEXER_NAMESPACE_BEGIN
#   define LEXER_NAMESPACE_BEGIN namespace LEXER_NAMESPACE{
#endif 

#ifndef LEXER_NAMESPACE_END
#   define LEXER_NAMESPACE_END }
#endif 

#ifndef USE_LEXER_NAMESPACE
#   define USE_LEXER_NAMESPACE using namespace LEXER_NAMESPACE;
#endif

#ifndef LEXER_FORWARD_DECLARE
#   define LEXER_FORWARD_DECLARE(name) \
    LEXER_NAMESPACE_BEGIN              \
    class name;                        \
    LEXER_NAMESPACE_END
#endif

#endif //LEXER_NAMESPACE_H
