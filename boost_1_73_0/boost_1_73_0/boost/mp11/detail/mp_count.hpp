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
VihTUjuaKKmLWq2Bs3MOZ53MFVzhktoXF2fqgoC3tGsO7nshrOikWXKT4G0cY+mEDxj0D98i6NJSLMWGasvimx/9diUKlxNH8K6FFPvuwre68emd3sh25wjGWimSttYqxa3WOoII7mIQn1zwPYbVBxfcJj8raskIj//Bd6NBXlgAMbydKcWKREEteqbg0HdsA2JZkdx8Gc6fhfxRwBdZ/gdk1IPsCXLWOzdYetzUpGxvaRkOLsQEkhlU1u5cwvGIXIktZaefEL7WtjoSROqZolDF6bJvKETqvcXxwjgZ1ukgl3q7deFdpZSx4XS2zJ/m6dCXmM8WOUvuknsc/cJGr5kfyvgL19Mp0237tsNAz9TW5SEMjqK0rrStCL0tsRIGV0QKB6bSdgD8JcQ6iV2rrZa6ycBP1dU8Oi2CqTY2xXetRfDXgRk9rl1x55p927Dh82SxfJr9ieBRStq562t27f3C2bkELx0R9AQeBm+mGnwZe19wkx/Agz/yc9vz3+4/UEsDBAoAAAAIAC1nSlLrNMwQQQMAADwJAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTQxOFVUBQABtkgkYNVWTY/bNhC9C/B/mFWxlyCKJMufqmxgu1kkRpK1EbvZQ9EDTVEW
*/