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