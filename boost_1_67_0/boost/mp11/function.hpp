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

#elif defined( BOOST_MP11_HAS_FOLD_EXPRESSIONS )

template<class... T> using mp_all = mp_bool<(static_cast<bool>(T::value) && ...)>;

#else

template<class... T> using mp_all = mp_and<mp_to_bool<T>...>;

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
#if defined( BOOST_MP11_HAS_FOLD_EXPRESSIONS ) && !BOOST_MP11_WORKAROUND( BOOST_MP11_GCC, != 0 ) && !BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 )

template<class... T> using mp_any = mp_bool<(static_cast<bool>(T::value) || ...)>;

#else

template<class... T> using mp_any = mp_bool< mp_count_if< mp_list<T...>, mp_to_bool >::value != 0 >;

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
    using type = mp_all<std::is_same<T1, T>...>;
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