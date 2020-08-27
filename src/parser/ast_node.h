#ifndef AST_NODE_H
#define AST_NODE_H

#include "namespace.h"

PARSER_NAMESPACE_BEGIN

class TypeNode
{
public:
    enum class Type
    {
        Int,
        Bool,
        Char,
        UserDefined
    };

    explicit TypeNode(const Type type) : type_(type) {}

    Type type() const noexcept { return type_; }
private:

    Type type_;
};

template<TypeNode::Type NodeType>
struct TypeNodeTemplate final : TypeNode
{
    TypeNodeTemplate() : TypeNode(NodeType) {}
};

using IntTypeNode = TypeNodeTemplate<TypeNode::Type::Int>;
using BoolTypeNode = TypeNodeTemplate<TypeNode::Type::Bool>;
using CharTypeNode = TypeNodeTemplate<TypeNode::Type::Char>;

PARSER_NAMESPACE_END

#endif //AST_NODE_H
