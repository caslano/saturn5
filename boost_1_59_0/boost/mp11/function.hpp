#ifndef BOOST_MP11_FUNCTION_HPP_INCLUDED
#define BOOST_MP11_FUNCTION_HPP_INCLUDED

// Copyright 2015-2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integral.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/mp11/detail/mp_list.hpp>
#include <boost/mp11/detail/mp_count.hpp>
#include <boost/mp11/detail/mp_plus.hpp>
#include <boost/mp11/detail/mp_min_element.hpp>
#include <boost/mp11/detail/mp_void.hpp>
#include <boost/mp11/detail/config.hpp>
#include <type_traits>

namespace boost
{
namespace mp11
{

// mp_void<T...>
//   in detail/mp_void.hpp

// mp_and<T...>
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1910 )

namespace detail
{

template<class... T> struct mp_and_impl;

} // namespace detail

template<class... T> using mp_and = mp_to_bool< typename detail::mp_and_impl<T...>::type >;

namespace detail
{

template<> struct mp_and_impl<>
{
    using type = mp_true;
};

template<class T> struct mp_and_impl<T>
{
    using type = T;
};

template<class T1, class... T> struct mp_and_impl<T1, T...>
{
    using type = mp_eval_if< mp_not<T1>, T1, mp_and, T... >;
};

} // namespace detail

#else

namespace detail
{

template<class L, class E = void> struct mp_and_impl
{
    using type = mp_false;
};

template<class... T> struct mp_and_impl< mp_list<T...>, mp_void<mp_if<T, void>...> >
{
    using type = mp_true;
};

} // namespace detail

template<class... T> using mp_and = typename detail::mp_and_impl<mp_list<T...>>::type;

#endif

// mp_all<T...>
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=86355
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 ) || BOOST_MP11_WORKAROUND( BOOST_MP11_GCC, != 0 )

template<class... T> using mp_all = mp_bool< mp_count_if< mp_list<T...>, mp_not >::value == 0 >;

#else

template<class... T> using mp_all = mp_bool< mp_count< mp_list<mp_to_bool<T>...>, mp_false >::value == 0 >;

#endif

// mp_or<T...>
namespace detail
{

template<class... T> struct mp_or_impl;

} // namespace detail

template<class... T> using mp_or = mp_to_bool< typename detail::mp_or_impl<T...>::type >;

namespace detail
{

template<> struct mp_or_impl<>
{
    using type = mp_false;
};

template<class T> struct mp_or_impl<T>
{
    using type = T;
};

template<class T1, class... T> struct mp_or_impl<T1, T...>
{
    using type = mp_eval_if< T1, T1, mp_or, T... >;
};

} // namespace detail

// mp_any<T...>
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=86356
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 ) || BOOST_MP11_WORKAROUND( BOOST_MP11_GCC, != 0 )

template<class... T> using mp_any = mp_bool< mp_count_if< mp_list<T...>, mp_to_bool >::value != 0 >;

#else

template<class... T> using mp_any = mp_bool< mp_count< mp_list<mp_to_bool<T>...>, mp_true >::value != 0 >;

#endif

// mp_same<T...>
namespace detail
{

template<class... T> struct mp_same_impl;

template<> struct mp_same_impl<>
{
    using type = mp_true;
};

template<class T1, class... T> struct mp_same_impl<T1, T...>
{
    using type = mp_bool< mp_count<mp_list<T...>, T1>::value == sizeof...(T) >;
};

} // namespace detail

template<class... T> using mp_same = typename detail::mp_same_impl<T...>::type;

// mp_similar<T...>
namespace detail
{

template<class... T> struct mp_similar_impl;

template<> struct mp_similar_impl<>
{
    using type = mp_true;
};

template<class T> struct mp_similar_impl<T>
{
    using type = mp_true;
};

template<class T> struct mp_similar_impl<T, T>
{
    using type = mp_true;
};

template<class T1, class T2> struct mp_similar_impl<T1, T2>
{
    using type = mp_false;
};

template<template<class...> class L, class... T1, class... T2> struct mp_similar_impl<L<T1...>, L<T2...>>
{
    using type = mp_true;
};

template<template<class...> class L, class... T> struct mp_similar_impl<L<T...>, L<T...>>
{
    using type = mp_true;
};

template<class T1, class T2, class T3, class... T> struct mp_similar_impl<T1, T2, T3, T...>
{
    using type = mp_all< typename mp_similar_impl<T1, T2>::type, typename mp_similar_impl<T1, T3>::type, typename mp_similar_impl<T1, T>::type... >;
};

} // namespace detail

template<class... T> using mp_similar = typename detail::mp_similar_impl<T...>::type;

#if BOOST_MP11_GCC
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wsign-compare"
#endif

// mp_less<T1, T2>
template<class T1, class T2> using mp_less = mp_bool<(T1::value < 0 && T2::value >= 0) || ((T1::value < T2::value) && !(T1::value >= 0 && T2::value < 0))>;

#if BOOST_MP11_GCC
# pragma GCC diagnostic pop
#endif

// mp_min<T...>
template<class T1, class... T> using mp_min = mp_min_element<mp_list<T1, T...>, mp_less>;

// mp_max<T...>
template<class T1, class... T> using mp_max = mp_max_element<mp_list<T1, T...>, mp_less>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_FUNCTION_HPP_INCLUDED

/* function.hpp
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
*/