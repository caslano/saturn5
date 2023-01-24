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
DoJyLODPFXHZ2OV1Jzn+jeC9Vro+cjssj4xQ+8L3jvC3seGjbeKwdaVerKm9Jvm8xalIH9KW7ED61Pvh94xg/f4EwmEYZ5I9+N3Y/Jy7fI5OS/KrND3h9rA5fIM+1pqKyWGOnoKYcuQ7hOTz7T1EHxc/6+NV+yeZSVx2UyBcmGTvfJ+nLAfHAm0uOgOPKJf3AdN93ivV9Zv6JL6/+FoIKygJ6tqJ9pEm+iaGdN5z2qettyeC987XJ/E9as9B+ArGco5x3XuglhKw3xV4V4D/ZVtym/dDefvPd/48v6BdiVL9iyNivzYcc1RX2HbNmR2WrjueQXeSpr7lvsGaa4q2iWiXXUTnhWJcgTwjymOKsSOdvUSMt197VFvkzohW9SyTqZdJ9BpP14w0uk4k99vLkdT4S/FTd46hl2naOk2YLNzvRllEaKn/fbq0ry/fPye/CZQrepimym8CkXuxxu027w3U+y603R1qvVbM/9PYdFaI6Oe7A+P/aoz/t8nn7+m/Jt14d3BY57uDO++vd2g03iTKPCdZE9VzIw7R18XPjMxQzwCY5H2UNjnmmWi/lJ/xsOTqiaYQkwih++OHQEfQx/fpZvztvD+MnjHIi1J7uAc7Z7bF9L+H95oj8yJEJOZOkRuC/6dnJ03QKWOcUs/0zcWYUnDUM337kfYN9F2fbyB0JFP5y8+8We/VtEyRqsnnYOi9rAeD+4XYkdz/
*/