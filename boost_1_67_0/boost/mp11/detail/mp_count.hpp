#ifndef BOOST_MP11_DETAIL_MP_COUNT_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_COUNT_HPP_INCLUDED

//  Copyright 2015, 2016 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integral.hpp>
#include <boost/mp11/detail/mp_plus.hpp>
#include <boost/mp11/detail/config.hpp>

namespace boost
{
namespace mp11
{

// mp_count<L, V>
namespace detail
{

template<class L, class V> struct mp_count_impl;

#if defined( BOOST_MP11_HAS_FOLD_EXPRESSIONS )

template<template<class...> class L, class... T, class V> struct mp_count_impl<L<T...>, V>
{
    using type = mp_size_t<(std::is_same<T, V>::value + ... + 0)>;
};

#elif !defined( BOOST_MP11_NO_CONSTEXPR )

constexpr std::size_t cx_plus()
{
    return 0;
}

template<class T1, class... T> constexpr std::size_t cx_plus(T1 t1, T... t)
{
    return static_cast<std::size_t>(t1) + cx_plus(t...);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class... T>
constexpr std::size_t cx_plus(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9, T10 t10, T... t)
{
    return static_cast<std::size_t>(t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8 + t9 + t10) + cx_plus(t...);
}

template<template<class...> class L, class... T, class V> struct mp_count_impl<L<T...>, V>
{
    using type = mp_size_t<cx_plus(std::is_same<T, V>::value...)>;
};

#else

template<template<class...> class L, class... T, class V> struct mp_count_impl<L<T...>, V>
{
    using type = mp_size_t<mp_plus<std::is_same<T, V>...>::value>;
};

#endif

} // namespace detail

template<class L, class V> using mp_count = typename detail::mp_count_impl<L, V>::type;

// mp_count_if<L, P>
namespace detail
{

template<class L, template<class...> class P> struct mp_count_if_impl;

#if defined( BOOST_MP11_HAS_FOLD_EXPRESSIONS ) && !BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 )

template<template<class...> class L, class... T, template<class...> class P> struct mp_count_if_impl<L<T...>, P>
{
    using type = mp_size_t<(mp_to_bool<P<T>>::value + ... + 0)>;
};

#elif !defined( BOOST_MP11_NO_CONSTEXPR )

template<template<class...> class L, class... T, template<class...> class P> struct mp_count_if_impl<L<T...>, P>
{
    using type = mp_size_t<cx_plus(mp_to_bool<P<T>>::value...)>;
};

#else

template<template<class...> class L, class... T, template<class...> class P> struct mp_count_if_impl<L<T...>, P>
{
#if BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 )

    template<class T> struct _f { using type = mp_to_bool<P<T>>; };
    using type = mp_size_t<mp_plus<typename _f<T>::type...>::value>;

#else

    using type = mp_size_t<mp_plus<mp_to_bool<P<T>>...>::value>;

#endif
};

#endif

} // namespace detail

template<class L, template<class...> class P> using mp_count_if = typename detail::mp_count_if_impl<L, P>::type;
template<class L, class Q> using mp_count_if_q = mp_count_if<L, Q::template fn>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_COUNT_HPP_INCLUDED

/* mp_count.hpp
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
*/