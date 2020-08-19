#include "production.h"

PARSER_NAMESPACE_BEGIN

/*friend*/ Production operator|(Production::RulePtr&& lhs, Production&& rhs)
{
    rhs.addRule(std::move(lhs));

    return std::move(rhs);
}

/*friend*/ Production operator|(Production&& lhs, Production::RulePtr&& rhs)
{
    return operator|(std::move(rhs), std::move(lhs));
}

Production Production::operator|(Production&& rhs) &&
{
    Production result;

    for(auto && rule : rules_)
    {
        result.addRule(std::move(rule));
    }

    for(auto && rule : rhs.rules_)
    {
        result.addRule(std::move(rule));
    }

    return result;
}

void Production::addRule(RulePtr&& rule)
{
    rules_.push_back(std::move(rule));
}

PARSER_NAMESPACE_END
