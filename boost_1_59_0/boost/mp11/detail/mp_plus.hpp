#ifndef BOOST_MP11_DETAIL_MP_PLUS_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_PLUS_HPP_INCLUDED

//  Copyright 2015 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/config.hpp>
#include <type_traits>

namespace boost
{
namespace mp11
{

// mp_plus
namespace detail
{

#if defined( BOOST_MP11_HAS_FOLD_EXPRESSIONS ) && !BOOST_MP11_WORKAROUND( BOOST_MP11_MSVC, < 1920 )

template<class... T> struct mp_plus_impl
{
    static const auto _v = (T::value + ... + 0);
    using type = std::integral_constant<typename std::remove_const<decltype(_v)>::type, _v>;
};

#else

template<class... T> struct mp_plus_impl;

template<> struct mp_plus_impl<>
{
    using type = std::integral_constant<int, 0>;
};

#if BOOST_MP11_WORKAROUND( BOOST_MP11_GCC, < 40800 )

template<class T1, class... T> struct mp_plus_impl<T1, T...>
{
    static const decltype(T1::value + mp_plus_impl<T...>::type::value) _v = T1::value + mp_plus_impl<T...>::type::value;
    using type = std::integral_constant<typename std::remove_const<decltype(_v)>::type, _v>;
};

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class... T> struct mp_plus_impl<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T...>
{
    static const
        decltype(T1::value + T2::value + T3::value + T4::value + T5::value + T6::value + T7::value + T8::value + T9::value + T10::value + mp_plus_impl<T...>::type::value)
        _v = T1::value + T2::value + T3::value + T4::value + T5::value + T6::value + T7::value + T8::value + T9::value + T10::value + mp_plus_impl<T...>::type::value;
    using type = std::integral_constant<typename std::remove_const<decltype(_v)>::type, _v>;
};

#else

template<class T1, class... T> struct mp_plus_impl<T1, T...>
{
    static const auto _v = T1::value + mp_plus_impl<T...>::type::value;
    using type = std::integral_constant<typename std::remove_const<decltype(_v)>::type, _v>;
};

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10, class... T> struct mp_plus_impl<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T...>
{
    static const auto _v = T1::value + T2::value + T3::value + T4::value + T5::value + T6::value + T7::value + T8::value + T9::value + T10::value + mp_plus_impl<T...>::type::value;
    using type = std::integral_constant<typename std::remove_const<decltype(_v)>::type, _v>;
};

#endif

#endif

} // namespace detail

template<class... T> using mp_plus = typename detail::mp_plus_impl<T...>::type;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_PLUS_HPP_INCLUDED

/* mp_plus.hpp
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
*/