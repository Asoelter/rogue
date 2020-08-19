#ifndef CONTAINER_TRAITS_H
#define CONTAINER_TRAITS_H

#include <type_traits>

template<typename ...Args>
struct TypeList
{
    static constexpr auto size = sizeof...(Args);
};

//----------------------IsList-----------------------

template<typename List>
struct IsListT : std::false_type {};

template<typename ...Args>
struct IsListT<TypeList<Args...>> : std::true_type {};

template<typename List>
constexpr auto IsList = IsListT<List>::type::value;

//----------------------Tail-----------------------

template<typename List>
struct TailT;

template<typename Head, typename ...Tail>
struct TailT<TypeList<Head, Tail...>>
{
    using type = TypeList<Tail...>;
};

template<typename List>
using Tail = typename TailT<List>::type;

//----------------------Head-----------------------

template<typename List>
struct HeadT;

template<typename Head, typename ...Tail>
struct HeadT<TypeList<Head, Tail...>>
{
    using type = Head;
};

template<typename List>
using Head = typename HeadT<List>::type;

//-------------------AreSimilar--------------------

template<typename LhsList, typename RhsList>
struct AreSimilarT;


template<>
struct AreSimilarT<TypeList<>, TypeList<>>
{
    static constexpr bool value = true;
};

template<typename T>
struct AreSimilarT<TypeList<>, TypeList<T>>
{
    static constexpr bool value = false;
};

template<typename T>
struct AreSimilarT<TypeList<T>, TypeList<>>
{
    static constexpr bool value = false;
};

template<typename T, typename U>
struct AreSimilarT<TypeList<T>, TypeList<U>>
{
    static constexpr bool value = std::is_convertible_v<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;
};

template<typename LhsList, typename RhsList>
struct AreSimilarT
{
    static_assert(IsListT<LhsList>::value && IsListT<RhsList>::value);

    static constexpr bool value = std::is_convertible_v<
        std::remove_cvref_t<Head<RhsList>>, 
        std::remove_cvref_t<Head<LhsList>>
    > && AreSimilarT<Tail<LhsList>, Tail<RhsList>>::value;
};

template<typename LhsList, typename RhsList>
constexpr auto AreSimilar = AreSimilarT<LhsList, RhsList>::value;

//-------------------Contains--------------------

template<typename List, typename T>
struct ContainsT;

template<typename T>
struct ContainsT<TypeList<>, T>
{
    static constexpr bool value = false;
};

template<typename List, typename T>
struct ContainsT
{
    static_assert(IsListT<List>::value);

    static constexpr bool value = std::is_same_v<std::remove_cvref_t<Head<List>>, std::remove_cvref_t<T>>
        || ContainsT<Tail<List>, T>::value;
};

template<typename List, typename T>
constexpr auto Contains = ContainsT<List, T>::value;

//-------------------NthElement--------------------

template<size_t N, typename List>
struct NthElementT
{
    static_assert(IsListT<List>::value, "NthElement called on non-TypeList");
    using type = std::conditional_t <N == 0, Head<List>, NthElementT<N - 1, Tail<List>>>;
};

template<size_t N, typename List>
using NthElement = typename NthElementT<N, List>::type;

#endif //CONTAINER_TRAITS_H