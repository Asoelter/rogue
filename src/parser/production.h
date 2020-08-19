#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <memory>
#include <vector>


#include "production_rule.h"

PARSER_NAMESPACE_BEGIN

class Production
{
public:
    using RulePtr = std::unique_ptr<parser::ProductionRule> ;

    Production() = default;
    Production(const Production&) = default;
    Production(Production&&) = default;
    ~Production() = default;

    Production& operator=(const Production&) = default;
    Production& operator=(Production&&) = default;

    friend Production operator|(RulePtr&& lhs, Production&& rhs);
    friend Production operator|(Production&& lhs, RulePtr&& rhs);
    Production operator|(Production&& rhs) &&;

    void addRule(RulePtr&& rule);

private:
    std::vector<RulePtr> rules_;
};

inline Production operator|(std::unique_ptr<ProductionRule>&& lhs, std::unique_ptr<ProductionRule>&& rhs)
{
    Production result;

    result.addRule(std::move(lhs));
    result.addRule(std::move(rhs));

    return result;
}

PARSER_NAMESPACE_END

#endif //PRODUCTION_H
