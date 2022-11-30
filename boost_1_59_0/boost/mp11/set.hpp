#ifndef BOOST_MP11_SET_HPP_INCLUDED
#define BOOST_MP11_SET_HPP_INCLUDED

// Copyright 2015, 2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/utility.hpp>
#include <boost/mp11/function.hpp>
#include <boost/mp11/detail/mp_list.hpp>
#include <boost/mp11/detail/mp_append.hpp>
#include <boost/mp11/detail/mp_copy_if.hpp>
#include <boost/mp11/detail/mp_remove_if.hpp>
#include <boost/mp11/detail/mp_is_list.hpp>
#include <type_traits>

namespace boost
{
namespace mp11
{

// mp_set_contains<S, V>
namespace detail
{

template<class S, class V> struct mp_set_contains_impl
{
};

template<template<class...> class L, class... T, class V> struct mp_set_contains_impl<L<T...>, V>
{
    using type = mp_to_bool<std::is_base_of<mp_identity<V>, mp_inherit<mp_identity<T>...> > >;
};

} // namespace detail

template<class S, class V> using mp_set_contains = typename detail::mp_set_contains_impl<S, V>::type;

// mp_set_push_back<S, T...>
namespace detail
{

template<class S, class... T> struct mp_set_push_back_impl
{
};

template<template<class...> class L, class... U> struct mp_set_push_back_impl<L<U...>>
{
    using type = L<U...>;
};

template<template<class...> class L, class... U, class T1, class... T> struct mp_set_push_back_impl<L<U...>, T1, T...>
{
    using S = mp_if<mp_set_contains<L<U...>, T1>, L<U...>, L<U..., T1>>;
    using type = typename mp_set_push_back_impl<S, T...>::type;
};

} // namespace detail

template<class S, class... T> using mp_set_push_back = typename detail::mp_set_push_back_impl<S, T...>::type;

// mp_set_push_front<S, T...>
namespace detail
{

template<class S, class... T> struct mp_set_push_front_impl
{
};

template<template<class...> class L, class... U> struct mp_set_push_front_impl<L<U...>>
{
    using type = L<U...>;
};

template<template<class...> class L, class... U, class T1> struct mp_set_push_front_impl<L<U...>, T1>
{
    using type = mp_if<mp_set_contains<L<U...>, T1>, L<U...>, L<T1, U...>>;
};

template<template<class...> class L, class... U, class T1, class... T> struct mp_set_push_front_impl<L<U...>, T1, T...>
{
    using S = typename mp_set_push_front_impl<L<U...>, T...>::type;
    using type = typename mp_set_push_front_impl<S, T1>::type;
};

} // namespace detail

template<class S, class... T> using mp_set_push_front = typename detail::mp_set_push_front_impl<S, T...>::type;

// mp_is_set<S>
namespace detail
{

template<class S> struct mp_is_set_impl
{
    using type = mp_false;
};

template<template<class...> class L, class... T> struct mp_is_set_impl<L<T...>>
{
    using type = mp_to_bool<std::is_same<mp_list<T...>, mp_set_push_back<mp_list<>, T...> > >;
};

} // namespace detail

template<class S> using mp_is_set = typename detail::mp_is_set_impl<S>::type;

// mp_set_union<L...>
namespace detail
{

template<class... L> struct mp_set_union_impl
{
};

template<> struct mp_set_union_impl<>
{
    using type = mp_list<>;
};

template<template<class...> class L, class... T> struct mp_set_union_impl<L<T...>>
{
    using type = L<T...>;
};

template<template<class...> class L1, class... T1, template<class...> class L2, class... T2> struct mp_set_union_impl<L1<T1...>, L2<T2...>>
{
    using type = mp_set_push_back<L1<T1...>, T2...>;
};

template<class L1, class... L> using mp_set_union_ = typename mp_set_union_impl<L1, mp_append<mp_list<>, L...>>::type;

template<class L1, class L2, class L3, class... L> struct mp_set_union_impl<L1, L2, L3, L...>: mp_defer<mp_set_union_, L1, L2, L3, L...>
{
};

} // namespace detail

template<class... L> using mp_set_union = typename detail::mp_set_union_impl<L...>::type;

// mp_set_intersection<S...>
namespace detail
{

template<class... S> struct in_all_sets
{
    template<class T> using fn = mp_all< mp_set_contains<S, T>... >;
};

template<class L, class... S> using mp_set_intersection_ = mp_if< mp_all<mp_is_list<S>...>, mp_copy_if_q<L, detail::in_all_sets<S...>> >;

template<class... S> struct mp_set_intersection_impl
{
};

template<> struct mp_set_intersection_impl<>
{
    using type = mp_list<>;
};

template<class L, class... S> struct mp_set_intersection_impl<L, S...>: mp_defer<mp_set_intersection_, L, S...>
{
};

} // namespace detail

template<class... S> using mp_set_intersection = typename detail::mp_set_intersection_impl<S...>::type;

// mp_set_difference<L, S...>
namespace detail
{

template<class... S> struct in_any_set
{
    template<class T> using fn = mp_any< mp_set_contains<S, T>... >;
};

} // namespace detail

template<class L, class... S> using mp_set_difference = mp_if< mp_all<mp_is_list<S>...>, mp_remove_if_q<L, detail::in_any_set<S...>> >;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_SET_HPP_INCLUDED

/* set.hpp
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
*/