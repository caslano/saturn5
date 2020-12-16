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
OempfklZ6grW5qk7uHldHz1M1E0z+7HNWISiHgURp05EY82qidEWGG001nzoYTTWTFO1aTvnFyAnAgtHDNUxygiuV99WxwgnQHoTjaewxg9vF9aYvwtr/Mh2xRrDd2aNV20X1pg+Mmv8xHZhjfmZWWN1zUWMikWpxhjfBdHysLoFgi6OaaKpFZju0mDq0WC6V4OpR2B6QIOpR2D6pgbTNwUmeopiAbnbseVevsGW4LhLXW67hK9wMciLOQSrmaQV64KL1Nk+rBH+3l+KAT36EfWK7Xx5iEuOwQa6oQFE6obceoT/zrWevsSt6Fu8gNqkfcfiTSPUR82vTGOZGNXVX5S6+Brt8GYIMlsw0KyHU+XzMiHtwPqtZU+oLv2jAHlnrE/Xw7UTC5fZrhhkeGbGM0Njjv9WtmC2hmtpSy2/yN5SKzDdzgXPSg8HL6iHozVNax2WNcID0GNupYejN9HDvfW4gvX0AlsPB1icjZTF69O64wtqPmHTyndtBHAH4rnIxdepCrdDsitLdCXPJzTBUxujWQXLoovcZsqrb3bP5w8C5Jkr+5WXQj8grJVfVPP5pQDOZ6vMpyqfK0Bm3e9cfwfV9+wPVJfKySQY69MFSvd84iCzQEkPPAOVK3k+Ceut/YI9n8t5vtWdxHe1MP5bzvMp8Cp47NlfTv9Rs5ultTdcg3WhmATrBMhyiFLceVrrPK3hJ33VWzMWowXtkj6qf+pVamzH+XEsgCawXJiCB1R24n/RmIQf1uG/cNa63ocTAXCQXa3eqT7qFNfP9+/B2dtj2uEllbSomiWvAHDcBCtHp1/vHGZSuCmCorxlvXv4Jf8IyV8/wjVJyW7OF12Jw8EDxciQ+mHZe9OZ3IRrcrHUgiNjVK4T1oTlTCwbqtxTL1JsCWbi7U4Pycea18Wle9IH8s2wvlCf270l1L0lrW5sIfkPr1fdUziFu8f5+Joomn3unpov7p5dznLhojXcvZVx7N6WKP2Xs1aTimtNneoeJrKoHefu8ezVncvwV9KCqz8tBzVjDhGY3avCOvr7ajk86lrGm+wnewzrzubxY4jrT83BhwT8uzHeYu4196oWP+pkHCB3C4nxaCzM9WkFCVn95BbNWFhQFvMi9SV2fmvIKsU1nXAeP1NWFtk7Vn4isn/y+9j/HPnwzdvZ/1IslTd+jZY0WRv1fE5cJYl/eEles2CsoaIRPEhFDY4zMG6F0mIuxQQJKDCEE2hvXQtZ7WgCFMCPniAXV/F8rYRlQPtCvrOLLwNkdQC7Rr7BsZpsy2iodAxk4G18/+0uH0fp252f+5f5ODr+iy0gy7WEs8rtUKTYN2KEmcTvtLSmGY0QzkVR8Yraq0BUfG8RZcgvtB22N4/sH26T+SPrTOmq7wE1jaPOETstmsYh8pqhnNvOtl8tymzJazdlfk1e45T5RXnNUuafyGsXWoDBlFf57Pi3Rdammnd3qGAWYvV1kI8U3mEL4rVdTdNUy+ElY/wWixg8v79uUQtpG8eKJ6sda52W8BYmhNN2IAJYPSLBpLmSb5wpHO/xLVWtc6yqhziOaYDjIrRWW4+SZt3g2UrjN16EVUs1Rz0v2fTvgB+puTw8gEDPlzxFoXBXVVt//ZbUDKuwJbIKnAa5ZvHQxW9s1No9xyqoUaRwb+xDJE3u/BlSz8RBb8gqQAuzs/199aUKoD8426WPE++8RMm8L3IizliVRTumj+MwbOuOhnsTx6CcAVbrDWNw2J3t+ehXVQ1L2TQXluwSYecjFDoUxvYgZMBowk48Q7ZpKSSyCd++y9XOCyfHqj2Q5WgX276sCOyk5Jiaz/ucLVAT4yBr6YU0NLhsUtEI2fjVj6QlZVATp8Y=
*/