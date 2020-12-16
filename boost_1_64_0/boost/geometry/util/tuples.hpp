// Boost.Geometry Index
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019, 2020.
// Modifications copyright (c) 2019-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_TUPLES_HPP
#define BOOST_GEOMETRY_UTIL_TUPLES_HPP

#include <boost/geometry/core/config.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_same.hpp>

#include <utility>

#ifdef BOOST_GEOMETRY_CXX11_TUPLE

#include <tuple>

#endif // BOOST_GEOMETRY_CXX11_TUPLE

namespace boost { namespace geometry { namespace tuples {


using boost::tuples::null_type;


template <int I, typename Tuple>
struct element
    : boost::tuples::element<I, Tuple>
{};

template <typename Tuple>
struct size
    : boost::tuples::length<Tuple>
{};

template <int I, typename HT, typename TT>
inline typename boost::tuples::access_traits
    <
        typename boost::tuples::element<I, boost::tuples::cons<HT, TT> >::type
    >::non_const_type
get(boost::tuples::cons<HT, TT> & tup)
{
    return boost::tuples::get<I>(tup);
}

template <int I, typename HT, typename TT>
inline typename boost::tuples::access_traits
    <
        typename boost::tuples::element<I, boost::tuples::cons<HT, TT> >::type
    >::const_type
get(boost::tuples::cons<HT, TT> const& tup)
{
    return boost::tuples::get<I>(tup);
}


template <int I, typename F, typename S>
struct element<I, std::pair<F, S> >
{};

template <typename F, typename S>
struct element<0, std::pair<F, S> >
{
    typedef F type;
};

template <typename F, typename S>
struct element<1, std::pair<F, S> >
{
    typedef S type;
};

template <typename F, typename S>
struct size<std::pair<F, S> >
    : boost::integral_constant<int, 2>
{};

template <int I, typename Pair>
struct get_pair;

template <typename F, typename S>
struct get_pair<0, std::pair<F, S> >
{
    typedef F type;

    static inline F& apply(std::pair<F, S> & p)
    {
        return p.first;
    }

    static inline F const& apply(std::pair<F, S> const& p)
    {
        return p.first;
    }
};

template <typename F, typename S>
struct get_pair<1, std::pair<F, S> >
{
    typedef S type;

    static inline S& apply(std::pair<F, S> & p)
    {
        return p.second;
    }

    static inline S const& apply(std::pair<F, S> const& p)
    {
        return p.second;
    }
};

template <int I, typename F, typename S>
inline typename get_pair<I, std::pair<F, S> >::type&
get(std::pair<F, S> & p)
{
    return get_pair<I, std::pair<F, S> >::apply(p);
}

template <int I, typename F, typename S>
inline typename get_pair<I, std::pair<F, S> >::type const&
get(std::pair<F, S> const& p)
{
    return get_pair<I, std::pair<F, S> >::apply(p);
}

#ifdef BOOST_GEOMETRY_CXX11_TUPLE

template <int I, typename ...Ts>
struct element<I, std::tuple<Ts...> >
    : std::tuple_element<I, std::tuple<Ts...> >
{};

template <typename ...Ts>
struct size<std::tuple<Ts...> >
    : std::tuple_size<std::tuple<Ts...> >
{};

template <int I, typename ...Ts>
inline typename std::tuple_element<I, std::tuple<Ts...> >::type&
get(std::tuple<Ts...> & tup)
{
    return std::get<I>(tup);
}

template <int I, typename ...Ts>
inline typename std::tuple_element<I, std::tuple<Ts...> >::type const&
get(std::tuple<Ts...> const& tup)
{
    return std::get<I>(tup);
}

#endif // BOOST_GEOMETRY_CXX11_TUPLE


// find_index_if
// Searches for the index of an element for which UnaryPredicate returns true
// If such element is not found the result is N

template
<
    typename Tuple,
    template <typename> class UnaryPred,
    int I = 0,
    int N = size<Tuple>::value
>
struct find_index_if
    : boost::mpl::if_c
        <
            UnaryPred<typename element<I, Tuple>::type>::value,
            boost::integral_constant<int, I>,
            typename find_index_if<Tuple, UnaryPred, I+1, N>::type
        >::type
{};

template
<
    typename Tuple,
    template <typename> class UnaryPred,
    int N
>
struct find_index_if<Tuple, UnaryPred, N, N>
    : boost::integral_constant<int, N>
{};


// find_if
// Searches for an element for which UnaryPredicate returns true
// If such element is not found the result is boost::tuples::null_type

template
<
    typename Tuple,
    template <typename> class UnaryPred,
    int I = 0,
    int N = size<Tuple>::value
>
struct find_if
    : boost::mpl::if_c
        <
            UnaryPred<typename element<I, Tuple>::type>::value,
            element<I, Tuple>,
            find_if<Tuple, UnaryPred, I+1, N>
        >::type
{};

template
<
    typename Tuple,
    template <typename> class UnaryPred,
    int N
>
struct find_if<Tuple, UnaryPred, N, N>
{
    typedef boost::tuples::null_type type;
};


// is_found
// Returns true if a type T (the result of find_if) was found.

template <typename T>
struct is_found
    : boost::mpl::not_<boost::is_same<T, boost::tuples::null_type> >
{};


// is_not_found
// Returns true if a type T (the result of find_if) was not found.

template <typename T>
struct is_not_found
    : boost::is_same<T, boost::tuples::null_type>
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
          size_t I = 0,
          size_t N = size<Tuple>::value>
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

template <typename Tuple, typename T, size_t N>
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
#ifdef BOOST_GEOMETRY_CXX11_TUPLE
    typedef std::tuple<F, S, T> type;
#else
    typedef boost::tuple<F, S, T> type;
#endif // BOOST_GEOMETRY_CXX11_TUPLE

    static type apply(std::pair<F, S> const& p, T const& t)
    {
        return type(p.first, p.second, t);
    }

#ifdef BOOST_GEOMETRY_CXX11_TUPLE
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    static type apply(std::pair<F, S> && p, T const& t)
    {
        return type(std::move(p.first), std::move(p.second), t);
    }

    static type apply(std::pair<F, S> && p, T && t)
    {
        return type(std::move(p.first), std::move(p.second), std::move(t));
    }

#endif
#endif // BOOST_GEOMETRY_CXX11_TUPLE

};

#ifdef BOOST_GEOMETRY_CXX11_TUPLE

// NOTE: In C++14 std::integer_sequence and std::make_integer_sequence could be used

template <int... Is>
struct int_sequence {};

template <int N, int ...Is>
struct make_int_sequence
{
    typedef typename make_int_sequence<N - 1, N - 1, Is...>::type type;
};

template <int ...Is>
struct make_int_sequence<0, Is...>
{
    typedef int_sequence<Is...> type;
};

template <typename Is, typename Tuple, typename T>
struct push_back_st;

template <int ...Is, typename ...Ts, typename T>
struct push_back_st<int_sequence<Is...>, std::tuple<Ts...>, T>
{
    typedef std::tuple<Ts..., T> type;

    static type apply(std::tuple<Ts...> const& tup, T const& t)
    {
        return type(std::get<Is>(tup)..., t);
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    static type apply(std::tuple<Ts...> && tup, T const& t)
    {
        return type(std::move(std::get<Is>(tup))..., t);
    }

    static type apply(std::tuple<Ts...> && tup, T && t)
    {
        return type(std::move(std::get<Is>(tup))..., std::move(t));
    }

#endif
};

template <typename ...Ts, typename T>
struct push_back<std::tuple<Ts...>, T>
    : push_back_st
        <
            typename make_int_sequence<sizeof...(Ts)>::type,
            std::tuple<Ts...>,
            T
        >
{};

#endif // BOOST_GEOMETRY_CXX11_TUPLE


}}} // namespace boost::geometry::tuples

#endif // BOOST_GEOMETRY_UTIL_TUPLES_HPP

/* tuples.hpp
KAfVoAN0Aa9kjAEIAMEgEsSBJJAOnKAYlIEKsAfsB/WgEbSAi8DyAHQHQSAMTAYxIBHYQBbIB6WgCtSAOtAM2kAnuAJ8HkQfQCAIBREgClhBBsgFJaAcVIJacAQ0gVbQAbqAVwr6BQJAMIgEcSAJpAMnKATFoAxUgD1gP6gH7cB/EfoDwsBkEAOyQBEoBdtBDagDDaAZtIFOcAX4PIR+gFAQAVJABsgFLlACKkEtOAKaQCvwSoXeIBiEg0gQB5KAM9XS8+n59Hx6Pj2fnk/P57/4DLTc5ueJtG6cvF8wLXZO6pLUFSuyLKMpb+yWL3M8nro4b8kSR45kSE17dNkyR1quBZ8hzFsx/sa8UoslZwSf2Sbc8EyvYNko5gkLZx4+dxakrnCsWJH56LLUzHRsEYYxn+/EG/OtyMjLTX/08WWWTHdbgU/K86jEuHmpaVmZjmW5qdmO3IxH0/Eoc4i7re483Q8d7vKR3c/Qfs5jjpwbyrt1tXbneWxc6nijnRt0der5utty11OqPzfby3XrVH1jPr21dHefAr99Q56szBW5jmXdY9N4Y3kWdNfdeeMzXYN0d57Sa++TR8+dm5r1qD09dd68uNQVuTmZy5ausKS7+2q59jczc6zRs+Vx5rLM3GtOsKzbrjt64bk1Oj41x8E65kXPmxc7Z7Zc4bOfep7FmY9q+brtEfiyO9/jOZm5Di2Tu64KPc/XKnPrbd3fG/nmzbWmTrdnpaVOTXXac+zZltRuv7z2rqGUnB5rjYmem5ruWJGWk+nMhWda8Bnm7t8EI9+SzGXpcAF3PS7z+VJHbqo9LzcjdZn49/XxuEk+KJ+74gb/s4XfJE9apjMDYye1ufO13ixfeuZSx4pcyXfdBhNvki/zuo84b/b8kXzUIXnY1s3yLLNnO/DMrY/vfTfJA4dbQVt2t2fmy1yRaodH4NGyscxTdz3PnHhrqj09HUEj25nDmNE9ibp9ZpKWHy2HudXLdNcZ+bU8N6lzxfUxd349v4xljvu5y3xOi7jba9Sfr4BON21wlDt/0fX8s2ekTk9MQjRw2HNSl2TZMRdTR7jtvM7MJ96YuSIDr8S6dWtd//U8OQ5Hd9/qnjafS/B2jyU+xeZz0X9cKpRfkpkv84ft3DQfNbbcoPOGm+aTGLKiey5u/E95UtNy0eYQtz9v0vKlZadbVrj7ZdtsPku15yx97Hq/nv3a88fsWXmO1NwCp+MGfW0HejOfqIH4cd2Ezu64/fbN8khsvJ4n7O8eN+QRN2aAnz61ex22HvG+eZ60vBW5j2an4v/iy7z4HDXyMqjfmLd7Tvyw19fyrlCTcUX3uOz0vCFPmj0ra7E97RHYOyer22alep4MBzI4czIfsyPuPuIoQHvM9yPmu8F1H70WSVd0+11Y2o06YZ+wJHMpxJnd8VGvI1dig2OZfXGWI717vYt8Rc8DVVO715jdNz5Lty9zaHPI0t3vn5r52Iz8c7rucfl6nmxxE/FKCz7dbX4tnzYH0He2+W/Ozge+yqoMwHcwdNhI0KGzUCeOGjVs6MCRo2aNwho1atQs+jVi4MgBQ4eNnDVq1KhZs0YNgxo6bNS0WVNnDRs1bNbMkUNnzRo1bNTIkbNGjuy5fc8luE374+/3eL77fec7f97zvu95z9m9nG+fks/qaP7JcpJ2nSIbXt94Y1FkxMLlnOx/+2nlhHXyX/2vuOeUZ4EbXLnqhtI1q9esZLjCbbaMcfKVFq+/7sNo0Q3kO+n3/y1fMIPyaP1Jm/pOdJ6IeoS1I3RSd7P+LR/dW7mR+XsTeovgSlecbF9BdN5/diPSun/FLhXR+ZwoEdiqSL0V2GBUnogNhkOp8Fj+y77umDg=
*/