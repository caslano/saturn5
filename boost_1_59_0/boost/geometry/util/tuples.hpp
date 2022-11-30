// Boost.Geometry Index
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019-2020.
// Modifications copyright (c) 2019-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_TUPLES_HPP
#define BOOST_GEOMETRY_UTIL_TUPLES_HPP

#include <tuple>
#include <type_traits>
#include <utility>

#include <boost/geometry/core/config.hpp>

#include <boost/tuple/tuple.hpp>

namespace boost { namespace geometry { namespace tuples
{

template <typename T>
struct is_tuple
    : std::integral_constant<bool, false>
{};

template <typename ...Ts>
struct is_tuple<std::tuple<Ts...>>
    : std::integral_constant<bool, true>
{};

template <typename F, typename S>
struct is_tuple<std::pair<F, S>>
    : std::integral_constant<bool, true>
{};

template <typename ...Ts>
struct is_tuple<boost::tuples::tuple<Ts...>>
    : std::integral_constant<bool, true>
{};

template <typename HT, typename TT>
struct is_tuple<boost::tuples::cons<HT, TT>>
    : std::integral_constant<bool, true>
{};


template <std::size_t I, typename Tuple>
struct element;

template <std::size_t I, typename ...Ts>
struct element<I, std::tuple<Ts...>>
    : std::tuple_element<I, std::tuple<Ts...>>
{};

template <std::size_t I, typename HT, typename TT>
struct element<I, std::pair<HT, TT>>
    : std::tuple_element<I, std::pair<HT, TT>>
{};

template <std::size_t I, typename ...Ts>
struct element<I, boost::tuples::tuple<Ts...>>
{
    typedef typename boost::tuples::element
        <
            I, boost::tuples::tuple<Ts...>
        >::type type;
};

template <std::size_t I, typename HT, typename TT>
struct element<I, boost::tuples::cons<HT, TT>>
{
    typedef typename boost::tuples::element
        <
            I, boost::tuples::cons<HT, TT>
        >::type type;
};


template <typename Tuple>
struct size;

template <typename ...Ts>
struct size<std::tuple<Ts...>>
    : std::tuple_size<std::tuple<Ts...>>
{};

template <typename HT, typename TT>
struct size<std::pair<HT, TT>>
    : std::tuple_size<std::pair<HT, TT>>
{};

template <typename ...Ts>
struct size<boost::tuples::tuple<Ts...>>
    : std::integral_constant
        <
            std::size_t,
            boost::tuples::length<boost::tuples::tuple<Ts...>>::value
        >
{};

template <typename HT, typename TT>
struct size<boost::tuples::cons<HT, TT>>
    : std::integral_constant
        <
            std::size_t,
            boost::tuples::length<boost::tuples::cons<HT, TT>>::value
        >
{};


template <std::size_t I, typename ...Ts>
constexpr inline typename std::tuple_element<I, std::tuple<Ts...>>::type&
get(std::tuple<Ts...> & t)
{
    return std::get<I>(t);
}

template <std::size_t I, typename ...Ts>
constexpr inline typename std::tuple_element<I, std::tuple<Ts...>>::type const&
get(std::tuple<Ts...> const& t)
{
    return std::get<I>(t);
}

template <std::size_t I, typename HT, typename TT>
constexpr inline typename std::tuple_element<I, std::pair<HT, TT>>::type&
get(std::pair<HT, TT> & t)
{
    return std::get<I>(t);
}

template <std::size_t I, typename HT, typename TT>
constexpr inline typename std::tuple_element<I, std::pair<HT, TT>>::type const&
get(std::pair<HT, TT> const& t)
{
    return std::get<I>(t);
}

template <std::size_t I, typename ...Ts>
inline typename boost::tuples::access_traits
    <
        typename boost::tuples::element<I, boost::tuples::tuple<Ts...>>::type
    >::non_const_type
get(boost::tuples::tuple<Ts...> & t)
{
    return boost::tuples::get<I>(t);
}

template <std::size_t I, typename ...Ts>
inline typename boost::tuples::access_traits
    <
        typename boost::tuples::element<I, boost::tuples::tuple<Ts...>>::type
    >::const_type
get(boost::tuples::tuple<Ts...> const& t)
{
    return boost::tuples::get<I>(t);
}


template <std::size_t I, typename HT, typename TT>
inline typename boost::tuples::access_traits
    <
        typename boost::tuples::element<I, boost::tuples::cons<HT, TT> >::type
    >::non_const_type
get(boost::tuples::cons<HT, TT> & tup)
{
    return boost::tuples::get<I>(tup);
}

template <std::size_t I, typename HT, typename TT>
inline typename boost::tuples::access_traits
    <
        typename boost::tuples::element<I, boost::tuples::cons<HT, TT> >::type
    >::const_type
get(boost::tuples::cons<HT, TT> const& tup)
{
    return boost::tuples::get<I>(tup);
}



// find_index_if
// Searches for the index of an element for which UnaryPredicate returns true
// If such element is not found the result is N

template
<
    typename Tuple,
    template <typename> class UnaryPred,
    std::size_t I = 0,
    std::size_t N = size<Tuple>::value
>
struct find_index_if
    : std::conditional_t
        <
            UnaryPred<typename element<I, Tuple>::type>::value,
            std::integral_constant<std::size_t, I>,
            typename find_index_if<Tuple, UnaryPred, I+1, N>::type
        >
{};

template
<
    typename Tuple,
    template <typename> class UnaryPred,
    std::size_t N
>
struct find_index_if<Tuple, UnaryPred, N, N>
    : std::integral_constant<std::size_t, N>
{};


// find_if
// Searches for an element for which UnaryPredicate returns true
// If such element is not found the result is detail::null_type

namespace detail
{

struct null_type {};

} // detail

template
<
    typename Tuple,
    template <typename> class UnaryPred,
    std::size_t I = 0,
    std::size_t N = size<Tuple>::value
>
struct find_if
    : std::conditional_t
        <
            UnaryPred<typename element<I, Tuple>::type>::value,
            element<I, Tuple>,
            find_if<Tuple, UnaryPred, I+1, N>
        >
{};

template
<
    typename Tuple,
    template <typename> class UnaryPred,
    std::size_t N
>
struct find_if<Tuple, UnaryPred, N, N>
{
    typedef detail::null_type type;
};


// is_found
// Returns true if a type T (the result of find_if) was found.

template <typename T>
struct is_found
    : std::integral_constant
        <
            bool,
            ! std::is_same<T, detail::null_type>::value
        >
{};


// is_not_found
// Returns true if a type T (the result of find_if) was not found.

template <typename T>
struct is_not_found
    : std::is_same<T, detail::null_type>
{};


// exists_if
// Returns true if search for element meeting UnaryPred can be found.

template <typename Tuple, template <typename> class UnaryPred>
struct exists_if
    : is_found<typename find_if<Tuple, UnaryPred>::type>
{};


// push_back
// A utility used to create a type/object of a Tuple containing
//   all types/objects stored in another Tuple plus additional one.

template <typename Tuple,
          typename T,
          std::size_t I = 0,
          std::size_t N = size<Tuple>::value>
struct push_back_bt
{
    typedef
    boost::tuples::cons<
        typename element<I, Tuple>::type,
        typename push_back_bt<Tuple, T, I+1, N>::type
    > type;

    static type apply(Tuple const& tup, T const& t)
    {
        return
        type(
            geometry::tuples::get<I>(tup),
            push_back_bt<Tuple, T, I+1, N>::apply(tup, t)
        );
    }
};

template <typename Tuple, typename T, std::size_t N>
struct push_back_bt<Tuple, T, N, N>
{
    typedef boost::tuples::cons<T, boost::tuples::null_type> type;

    static type apply(Tuple const&, T const& t)
    {
        return type(t, boost::tuples::null_type());
    }
};

template <typename Tuple, typename T>
struct push_back
    : push_back_bt<Tuple, T>
{};

template <typename F, typename S, typename T>
struct push_back<std::pair<F, S>, T>
{
    typedef std::tuple<F, S, T> type;

    static type apply(std::pair<F, S> const& p, T const& t)
    {
        return type(p.first, p.second, t);
    }

    static type apply(std::pair<F, S> && p, T const& t)
    {
        return type(std::move(p.first), std::move(p.second), t);
    }

    static type apply(std::pair<F, S> && p, T && t)
    {
        return type(std::move(p.first), std::move(p.second), std::move(t));
    }
};

template <typename Is, typename Tuple, typename T>
struct push_back_st;

template <std::size_t ...Is, typename ...Ts, typename T>
struct push_back_st<std::index_sequence<Is...>, std::tuple<Ts...>, T>
{
    typedef std::tuple<Ts..., T> type;

    static type apply(std::tuple<Ts...> const& tup, T const& t)
    {
        return type(std::get<Is>(tup)..., t);
    }

    static type apply(std::tuple<Ts...> && tup, T const& t)
    {
        return type(std::move(std::get<Is>(tup))..., t);
    }

    static type apply(std::tuple<Ts...> && tup, T && t)
    {
        return type(std::move(std::get<Is>(tup))..., std::move(t));
    }
};

template <typename ...Ts, typename T>
struct push_back<std::tuple<Ts...>, T>
    : push_back_st
        <
            std::make_index_sequence<sizeof...(Ts)>,
            std::tuple<Ts...>,
            T
        >
{};


}}} // namespace boost::geometry::tuples

#endif // BOOST_GEOMETRY_UTIL_TUPLES_HPP

/* tuples.hpp
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
*/