#ifndef BOOST_MP11_LIST_HPP_INCLUDED
#define BOOST_MP11_LIST_HPP_INCLUDED

//  Copyright 2015-2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integral.hpp>
#include <boost/mp11/detail/mp_list.hpp>
#include <boost/mp11/detail/mp_is_list.hpp>
#include <boost/mp11/detail/mp_append.hpp>
#include <boost/mp11/detail/config.hpp>
#include <type_traits>

namespace boost
{
namespace mp11
{

// mp_list_c<T, I...>
template<class T, T... I> using mp_list_c = mp_list<std::integral_constant<T, I>...>;

// mp_is_list<L>
//   in detail/mp_is_list.hpp

// mp_size<L>
namespace detail
{

template<class L> struct mp_size_impl
{
// An error "no type named 'type'" here means that the argument to mp_size is not a list
};

template<template<class...> class L, class... T> struct mp_size_impl<L<T...>>
{
    using type = mp_size_t<sizeof...(T)>;
};

} // namespace detail

template<class L> using mp_size = typename detail::mp_size_impl<L>::type;

// mp_empty<L>
template<class L> using mp_empty = mp_bool< mp_size<L>::value == 0 >;

// mp_assign<L1, L2>
namespace detail
{

template<class L1, class L2> struct mp_assign_impl;

template<template<class...> class L1, class... T, template<class...> class L2, class... U> struct mp_assign_impl<L1<T...>, L2<U...>>
{
    using type = L1<U...>;
};

} // namespace detail

template<class L1, class L2> using mp_assign = typename detail::mp_assign_impl<L1, L2>::type;

// mp_clear<L>
template<class L> using mp_clear = mp_assign<L, mp_list<>>;

// mp_front<L>
namespace detail
{

template<class L> struct mp_front_impl
{
// An error "no type named 'type'" here means that the argument to mp_front
// is either not a list, or is an empty list
};

template<template<class...> class L, class T1, class... T> struct mp_front_impl<L<T1, T...>>
{
    using type = T1;
};

} // namespace detail

template<class L> using mp_front = typename detail::mp_front_impl<L>::type;

// mp_pop_front<L>
namespace detail
{

template<class L> struct mp_pop_front_impl
{
// An error "no type named 'type'" here means that the argument to mp_pop_front
// is either not a list, or is an empty list
};

template<template<class...> class L, class T1, class... T> struct mp_pop_front_impl<L<T1, T...>>
{
    using type = L<T...>;
};

} // namespace detail

template<class L> using mp_pop_front = typename detail::mp_pop_front_impl<L>::type;

// mp_first<L>
template<class L> using mp_first = mp_front<L>;

// mp_rest<L>
template<class L> using mp_rest = mp_pop_front<L>;

// mp_second<L>
namespace detail
{

template<class L> struct mp_second_impl
{
// An error "no type named 'type'" here means that the argument to mp_second
// is either not a list, or has fewer than two elements
};

template<template<class...> class L, class T1, class T2, class... T> struct mp_second_impl<L<T1, T2, T...>>
{
    using type = T2;
};

} // namespace detail

template<class L> using mp_second = typename detail::mp_second_impl<L>::type;

// mp_third<L>
namespace detail
{

template<class L> struct mp_third_impl
{
// An error "no type named 'type'" here means that the argument to mp_third
// is either not a list, or has fewer than three elements
};

template<template<class...> class L, class T1, class T2, class T3, class... T> struct mp_third_impl<L<T1, T2, T3, T...>>
{
    using type = T3;
};

} // namespace detail

template<class L> using mp_third = typename detail::mp_third_impl<L>::type;

// mp_push_front<L, T...>
namespace detail
{

template<class L, class... T> struct mp_push_front_impl
{
// An error "no type named 'type'" here means that the first argument to mp_push_front is not a list
};

template<template<class...> class L, class... U, class... T> struct mp_push_front_impl<L<U...>, T...>
{
    using type = L<T..., U...>;
};

} // namespace detail

template<class L, class... T> using mp_push_front = typename detail::mp_push_front_impl<L, T...>::type;

// mp_push_back<L, T...>
namespace detail
{

template<class L, class... T> struct mp_push_back_impl
{
// An error "no type named 'type'" here means that the first argument to mp_push_back is not a list
};

template<template<class...> class L, class... U, class... T> struct mp_push_back_impl<L<U...>, T...>
{
    using type = L<U..., T...>;
};

} // namespace detail

template<class L, class... T> using mp_push_back = typename detail::mp_push_back_impl<L, T...>::type;

// mp_rename<L, B>
namespace detail
{

template<class A, template<class...> class B> struct mp_rename_impl
{
// An error "no type named 'type'" here means that the first argument to mp_rename is not a list
};

template<template<class...> class A, class... T, template<class...> class B> struct mp_rename_impl<A<T...>, B>
{
    using type = B<T...>;
};

} // namespace detail

template<class A, template<class...> class B> using mp_rename = typename detail::mp_rename_impl<A, B>::type;

template<template<class...> class F, class L> using mp_apply = typename detail::mp_rename_impl<L, F>::type;

template<class Q, class L> using mp_apply_q = typename detail::mp_rename_impl<L, Q::template fn>::type;

// mp_replace_front<L, T>
namespace detail
{

template<class L, class T> struct mp_replace_front_impl
{
// An error "no type named 'type'" here means that the first argument to mp_replace_front
// is either not a list, or is an empty list
};

template<template<class...> class L, class U1, class... U, class T> struct mp_replace_front_impl<L<U1, U...>, T>
{
    using type = L<T, U...>;
};

} // namespace detail

template<class L, class T> using mp_replace_front = typename detail::mp_replace_front_impl<L, T>::type;

// mp_replace_first<L, T>
template<class L, class T> using mp_replace_first = typename detail::mp_replace_front_impl<L, T>::type;

// mp_replace_second<L, T>
namespace detail
{

template<class L, class T> struct mp_replace_second_impl
{
// An error "no type named 'type'" here means that the first argument to mp_replace_second
// is either not a list, or has fewer than two elements
};

template<template<class...> class L, class U1, class U2, class... U, class T> struct mp_replace_second_impl<L<U1, U2, U...>, T>
{
    using type = L<U1, T, U...>;
};

} // namespace detail

template<class L, class T> using mp_replace_second = typename detail::mp_replace_second_impl<L, T>::type;

// mp_replace_third<L, T>
namespace detail
{

template<class L, class T> struct mp_replace_third_impl
{
// An error "no type named 'type'" here means that the first argument to mp_replace_third
// is either not a list, or has fewer than three elements
};

template<template<class...> class L, class U1, class U2, class U3, class... U, class T> struct mp_replace_third_impl<L<U1, U2, U3, U...>, T>
{
    using type = L<U1, U2, T, U...>;
};

} // namespace detail

template<class L, class T> using mp_replace_third = typename detail::mp_replace_third_impl<L, T>::type;

// mp_transform_front<L, F>
namespace detail
{

template<class L, template<class...> class F> struct mp_transform_front_impl
{
// An error "no type named 'type'" here means that the first argument to mp_transform_front
// is either not a list, or is an empty list
};

template<template<class...> class L, class U1, class... U, template<class...> class F> struct mp_transform_front_impl<L<U1, U...>, F>
{
    using type = L<F<U1>, U...>;
};

} // namespace detail

template<class L, template<class...> class F> using mp_transform_front = typename detail::mp_transform_front_impl<L, F>::type;
template<class L, class Q> using mp_transform_front_q = mp_transform_front<L, Q::template fn>;

// mp_transform_first<L, F>
template<class L, template<class...> class F> using mp_transform_first = typename detail::mp_transform_front_impl<L, F>::type;
template<class L, class Q> using mp_transform_first_q = mp_transform_first<L, Q::template fn>;

// mp_transform_second<L, F>
namespace detail
{

template<class L, template<class...> class F> struct mp_transform_second_impl
{
// An error "no type named 'type'" here means that the first argument to mp_transform_second
// is either not a list, or has fewer than two elements
};

template<template<class...> class L, class U1, class U2, class... U, template<class...> class F> struct mp_transform_second_impl<L<U1, U2, U...>, F>
{
    using type = L<U1, F<U2>, U...>;
};

} // namespace detail

template<class L, template<class...> class F> using mp_transform_second = typename detail::mp_transform_second_impl<L, F>::type;
template<class L, class Q> using mp_transform_second_q = mp_transform_second<L, Q::template fn>;

// mp_transform_third<L, F>
namespace detail
{

template<class L, template<class...> class F> struct mp_transform_third_impl
{
// An error "no type named 'type'" here means that the first argument to mp_transform_third
// is either not a list, or has fewer than three elements
};

template<template<class...> class L, class U1, class U2, class U3, class... U, template<class...> class F> struct mp_transform_third_impl<L<U1, U2, U3, U...>, F>
{
    using type = L<U1, U2, F<U3>, U...>;
};

} // namespace detail

template<class L, template<class...> class F> using mp_transform_third = typename detail::mp_transform_third_impl<L, F>::type;
template<class L, class Q> using mp_transform_third_q = mp_transform_third<L, Q::template fn>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_LIST_HPP_INCLUDED

/* list.hpp
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
*/