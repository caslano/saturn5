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

#if !defined( BOOST_MP11_NO_CONSTEXPR )

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

#endif

template<class L, class V> struct mp_count_impl;

#if defined( BOOST_MP11_HAS_CXX14_CONSTEXPR )

template<class V, class... T> constexpr std::size_t cx_count()
{
    constexpr bool a[] = { false, std::is_same<T, V>::value... };

    std::size_t r = 0;

    for( std::size_t i = 1; i < sizeof...(T) + 1; ++i )
    {
        r += a[ i ];
    }

    return r;
}

template<template<class...> class L, class... T, class V> struct mp_count_impl<L<T...>, V>
{
    using type = mp_size_t<cx_count<V, T...>()>;
};

#elif !defined( BOOST_MP11_NO_CONSTEXPR )

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

#if defined( BOOST_MP11_HAS_CXX14_CONSTEXPR ) && !BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1930 )

template<template<class...> class P, class... T> constexpr std::size_t cx_count_if()
{
    constexpr bool a[] = { false, static_cast<bool>( P<T>::value )... };

    std::size_t r = 0;

    for( std::size_t i = 1; i < sizeof...(T) + 1; ++i )
    {
        r += a[ i ];
    }

    return r;
}

template<template<class...> class L, class... T, template<class...> class P> struct mp_count_if_impl<L<T...>, P>
{
    using type = mp_size_t<cx_count_if<P, T...>()>;
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