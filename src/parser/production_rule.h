#ifndef PRODUCTION_RULE_H
#define PRODUCTION_RULE_H

#include <unordered_set>

#include <containers/capped_vector.h>
#include <containers/typelist.h>

#include <util/type_id.hpp>

#include "namespace.h"

PARSER_NAMESPACE_BEGIN

class Epsilon {};

class ProductionRule
{
public:
    ProductionRule() = default;
    ProductionRule(const ProductionRule&) = default;
    ProductionRule(ProductionRule&&) = default;
    virtual ~ProductionRule() = default;

    ProductionRule& operator=(const ProductionRule&) = default;
    ProductionRule& operator=(ProductionRule&&) = default;

    [[nodiscard]]
    virtual std::unordered_set<type_id> firstSet() const = 0;
};

template<typename ... Args>
class Rule final : public ProductionRule
{
public:
    Rule();
    Rule(const Rule&) = default;
    Rule(Rule&&) = default;
    ~Rule() = default;

    Rule& operator=(const Rule&) = default;
    Rule& operator=(Rule&&) = default;

    [[nodiscard]]
    std::unordered_set<type_id> firstSet() const override;

private:
    static constexpr auto size = sizeof...(Args);
    using SequenceList = CappedVector<type_id, size>;

    template<typename T>
    static CappedVector<type_id, 1> gatherTypeIdsImpl();

    template<typename HeadType, typename TailList>
    static CappedVector<type_id, 1 + TailList::size> gatherTypeIdsImpl();

    template<typename ... Ts>
    static SequenceList gatherTypeIds();

private:
    CappedVector <type_id, size> types_;
};

template<typename ... Args>
std::unique_ptr<ProductionRule> makeRule()
{
    return std::make_unique<Rule<Args...>>();
}

PARSER_NAMESPACE_END

#include "production_rule.hpp"

#endif //PRODUCTION_RULE_H
