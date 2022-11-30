//
// Copyright (c) 2016-2019 Damian Jarek (damian dot jarek93 at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_TUPLE_HPP
#define BOOST_BEAST_DETAIL_TUPLE_HPP

#include <boost/mp11/integer_sequence.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/copy_cv.hpp>
#include <cstdlib>
#include <utility>

namespace boost {
namespace beast {
namespace detail {

template<std::size_t I, class T>
struct tuple_element_impl
{
    T t;

    tuple_element_impl(T const& t_)
        : t(t_)
    {
    }

    tuple_element_impl(T&& t_)
        : t(std::move(t_))
    {
    }
};

template<std::size_t I, class T>
struct tuple_element_impl<I, T&>
{
    T& t;

    tuple_element_impl(T& t_)
        : t(t_)
    {
    }
};

template<class... Ts>
struct tuple_impl;

template<class... Ts, std::size_t... Is>
struct tuple_impl<
    boost::mp11::index_sequence<Is...>, Ts...>
  : tuple_element_impl<Is, Ts>...
{
    template<class... Us>
    explicit tuple_impl(Us&&... us)
        : tuple_element_impl<Is, Ts>(
            std::forward<Us>(us))...
    {
    }
};

template<class... Ts>
struct tuple : tuple_impl<
    boost::mp11::index_sequence_for<Ts...>, Ts...>
{
    template<class... Us>
    explicit tuple(Us&&... us)
      : tuple_impl<
            boost::mp11::index_sequence_for<Ts...>, Ts...>{
          std::forward<Us>(us)...}
    {
    }
};

template<std::size_t I, class T>
T&
get(tuple_element_impl<I, T>& te)
{
    return te.t;
}

template<std::size_t I, class T>
T const&
get(tuple_element_impl<I, T> const& te)
{
    return te.t;
}

template<std::size_t I, class T>
T&&
get(tuple_element_impl<I, T>&& te)
{
    return std::move(te.t);
}

template<std::size_t I, class T>
T&
get(tuple_element_impl<I, T&>&& te)
{
    return te.t;
}

template <std::size_t I, class T>
using tuple_element = typename boost::copy_cv<
    mp11::mp_at_c<typename remove_cv<T>::type, I>, T>::type;

} // detail
} // beast
} // boost

#endif

/* tuple.hpp
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
*/