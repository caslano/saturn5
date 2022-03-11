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