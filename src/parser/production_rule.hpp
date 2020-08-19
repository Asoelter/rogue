
PARSER_NAMESPACE_BEGIN

template<typename ...Args>
Rule<Args...>::Rule()
{
    types_ = gatherTypeIds<Args...>();
}

template<typename ...Args>
std::unordered_set<type_id> Rule<Args...>::firstSet() const
{
    std::unordered_set<type_id> result;

    for(const auto type : types_)
    {
        result.insert(type);

        if(type != TypeId<Epsilon>)
        {
            break;
        }
    }

    return result;
}

template<typename ...Args>
template<typename T>
CappedVector<type_id, 1> Rule<Args...>::gatherTypeIdsImpl()
{
    CappedVector<type_id, 1> result;

    auto const id = TypeId<T>;

    result.push_back(id);

    return result;
}

template<typename ...Args>
template<typename HeadType, typename TailList>
CappedVector<type_id, 1 + TailList::size> Rule<Args...>::gatherTypeIdsImpl()
{
    CappedVector<type_id, 1 + TailList::size> result;

    auto headId = TypeId<HeadType>;
    result.push_back(headId);

    if constexpr (TailList::size > 0)
    {
        auto tailIds = gatherTypeIdsImpl< Head<TailList>, Tail<TailList>>();
        result.append(tailIds.begin(), tailIds.end());
    }

    return result;
}

template<typename ...Args>
template<typename ... Ts>
typename Rule<Args...>::SequenceList Rule<Args...>::gatherTypeIds()
{
    if constexpr (sizeof...(Ts) == 1)
    {
        return gatherTypeIdsImpl<Head<TypeList<Ts...>>>();
    }
    return gatherTypeIdsImpl<Head<TypeList<Ts...>>, Tail<TypeList<Ts...>>>();
}

PARSER_NAMESPACE_END
