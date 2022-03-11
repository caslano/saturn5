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