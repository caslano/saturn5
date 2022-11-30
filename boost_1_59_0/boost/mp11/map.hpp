#ifndef BOOST_MP11_MAP_HPP_INCLUDED
#define BOOST_MP11_MAP_HPP_INCLUDED

//  Copyright 2015-2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/mp_map_find.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/function.hpp>
#include <boost/mp11/set.hpp>
#include <type_traits>

namespace boost
{
namespace mp11
{

// mp_map_contains<M, K>
template<class M, class K> using mp_map_contains = mp_not<std::is_same<mp_map_find<M, K>, void>>;

// mp_map_insert<M, T>
template<class M, class T> using mp_map_insert = mp_if< mp_map_contains<M, mp_first<T>>, M, mp_push_back<M, T> >;

// mp_map_replace<M, T>
namespace detail
{

template<class M, class T> struct mp_map_replace_impl;

template<template<class...> class M, class... U, class T> struct mp_map_replace_impl<M<U...>, T>
{
    using K = mp_first<T>;

    // mp_replace_if is inlined here using a struct _f because of msvc-14.0

    template<class V> struct _f { using type = mp_if< std::is_same<mp_first<V>, K>, T, V >; };

    using type = mp_if< mp_map_contains<M<U...>, K>, M<typename _f<U>::type...>, M<U..., T> >;
};

} // namespace detail

template<class M, class T> using mp_map_replace = typename detail::mp_map_replace_impl<M, T>::type;

// mp_map_update<M, T, F>
namespace detail
{

template<class M, class T, template<class...> class F> struct mp_map_update_impl
{
    template<class U> using _f = std::is_same<mp_first<T>, mp_first<U>>;

    // _f3<L<X, Y...>> -> L<X, F<X, Y...>>
    template<class L> using _f3 = mp_assign<L, mp_list<mp_first<L>, mp_rename<L, F> > >;

    using type = mp_if< mp_map_contains<M, mp_first<T>>, mp_transform_if<_f, _f3, M>, mp_push_back<M, T> >;
};

} // namespace detail

template<class M, class T, template<class...> class F> using mp_map_update = typename detail::mp_map_update_impl<M, T, F>::type;
template<class M, class T, class Q> using mp_map_update_q = mp_map_update<M, T, Q::template fn>;

// mp_map_erase<M, K>
namespace detail
{

template<class M, class K> struct mp_map_erase_impl
{
    template<class T> using _f = std::is_same<mp_first<T>, K>;
    using type = mp_remove_if<M, _f>;
};

} // namespace detail

template<class M, class K> using mp_map_erase = typename detail::mp_map_erase_impl<M, K>::type;

// mp_map_keys<M>
template<class M> using mp_map_keys = mp_transform<mp_first, M>;

// mp_is_map<M>
namespace detail
{

template<class L> struct mp_is_map_element: mp_false
{
};

template<template<class...> class L, class T1, class... T> struct mp_is_map_element<L<T1, T...>>: mp_true
{
};

template<class M> using mp_keys_are_set = mp_is_set<mp_map_keys<M>>;

template<class M> struct mp_is_map_impl
{
    using type = mp_false;
};

template<template<class...> class M, class... T> struct mp_is_map_impl<M<T...>>
{
    using type = mp_eval_if<mp_not<mp_all<mp_is_map_element<T>...>>, mp_false, mp_keys_are_set, M<T...>>;
};

} // namespace detail

template<class M> using mp_is_map = typename detail::mp_is_map_impl<M>::type;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_MAP_HPP_INCLUDED

/* map.hpp
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
*/