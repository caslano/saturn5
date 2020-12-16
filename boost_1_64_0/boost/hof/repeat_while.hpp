/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    repeat_while.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_REPEAT_WHILE_H
#define BOOST_HOF_GUARD_REPEAT_WHILE_H

/// repeat_while
/// ======
/// 
/// Description
/// -----------
/// 
/// The `repeat_while` function decorator will repeatedly apply a function while
/// the predicate returns a boolean that is true. If the predicate returns an
/// `IntergralConstant` then the predicate is only evaluated at compile-time.
/// 
/// 
/// Synopsis
/// --------
/// 
///     template<class Predicate>
///     constexpr auto repeat_while(Predicate predicate);
/// 
/// Requirements
/// ------------
/// 
/// Predicate must be:
/// 
/// * [ConstFunctionObject](ConstFunctionObject)
/// * MoveConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     struct increment
///     {
///         template<class T>
///         constexpr std::integral_constant<int, T::value + 1> operator()(T) const
///         {
///             return std::integral_constant<int, T::value + 1>();
///         }
///     };
/// 
///     struct not_6
///     {
///         template<class T>
///         constexpr std::integral_constant<bool, (T::value != 6)> 
///         operator()(T) const
///         {
///             return std::integral_constant<bool, (T::value != 6)>();
///         }
///     };
/// 
///     typedef std::integral_constant<int, 1> one;
///     typedef std::integral_constant<int, 6> six;
/// 
///     int main() {
///         auto increment_until_6 = boost::hof::repeat_while(not_6())(increment());
///         static_assert(std::is_same<six, decltype(increment_until_6(one()))>::value, "Error");
///     }
/// 

#include <boost/hof/always.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/result_of.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/decorate.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/first_of.hpp>
#include <boost/hof/detail/recursive_constexpr_depth.hpp>

namespace boost { namespace hof { namespace detail {

template<class P, class... Ts>
struct compute_predicate
{
    typedef decltype(std::declval<P>()(std::declval<Ts>()...)) type;
};

template<bool B>
struct while_repeater
{
    template<class F, class P, class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(while_repeater<
        compute_predicate<P, typename result_of<const F&, id_<Ts>...>::type>::type::value
    >, id_<const F&>, id_<const P&>, result_of<const F&, id_<Ts>...>) 
    operator()(const F& f, const P& p, Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        while_repeater<
            compute_predicate<P, decltype(f(BOOST_HOF_FORWARD(Ts)(xs)...))>::type::value
        >()(f, p, f(BOOST_HOF_FORWARD(Ts)(xs)...))
    );
};

template<>
struct while_repeater<false>
{
    template<class F, class P, class T>
    constexpr T operator()(const F&, const P&, T&& x) const 
    BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT(x)
    {
        return x;
    }
};

struct repeat_while_constant_decorator
{
    template<class P, class F, class... Ts>
    constexpr auto operator()(const P& p, const F& f, Ts&&... xs) const BOOST_HOF_RETURNS
    (
        detail::while_repeater<
            detail::compute_predicate<P, decltype(std::declval<F>()(BOOST_HOF_FORWARD(Ts)(xs)...))>::type::value
        >()
        (
            f, 
            p, 
            BOOST_HOF_FORWARD(Ts)(xs)...
        )
    );
};

template<int Depth>
struct repeat_while_integral_decorator
{
    template<class P, class F, class T, class... Ts, class Self=repeat_while_integral_decorator<Depth-1>>
    constexpr auto operator()(const P& p, const F& f, T&& x, Ts&&... xs) const BOOST_HOF_RETURNS
    (
        (p(x, BOOST_HOF_FORWARD(Ts)(xs)...)) ? 
            Self()(
                p, 
                f, 
                f(x, BOOST_HOF_FORWARD(Ts)(xs)...)
            ) : 
            BOOST_HOF_FORWARD(T)(x)
    );
};

template<>
struct repeat_while_integral_decorator<0>
{
    template<class P, class F, class T, class Self=repeat_while_integral_decorator<0>>
#if BOOST_HOF_HAS_RELAXED_CONSTEXPR
    constexpr
#endif
    auto operator()(const P& p, const F& f, T x) const 
    BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT((p(x), f(x)))
    -> decltype(f(x))
    {
        while(p(x))
        {
            // TODO: Should move?
            x = f(x);
        }
        return x;
    }
};
}

#if BOOST_HOF_HAS_RELAXED_CONSTEXPR
#define BOOST_HOF_REPEAT_WHILE_CONSTEXPR_DEPTH 1
#else
#define BOOST_HOF_REPEAT_WHILE_CONSTEXPR_DEPTH BOOST_HOF_RECURSIVE_CONSTEXPR_DEPTH
#endif

BOOST_HOF_DECLARE_STATIC_VAR(repeat_while, decorate_adaptor<
    boost::hof::first_of_adaptor<
        detail::repeat_while_constant_decorator,
        detail::repeat_while_integral_decorator<BOOST_HOF_REPEAT_WHILE_CONSTEXPR_DEPTH>
    >
>);

}} // namespace boost::hof

#endif

/* repeat_while.hpp
V+tknq0xHDlHkP+hXmLvClDZHRDy4OL0Yp/QQ9KJJGPLCN9FX0GAYf/E1+gV50u700E6z7WxuoCBAOB/s7mdlHfsFhYyQ2eRWxxNtfVQiWsAYs5ejlbgZBCHK/8J5qQoMcPUZ9dGk/vsTKPPToa5DPXZKwvU8W5/xYTolHX2NN3EpeuHtYa9oF4XFCJ8ET0dvJtmIfCR2s+Rrv0cx95+Dtl+r16d1H6OI7efe80R2s9B7XftNGo/R3L7OcSQqV+l/Zj0ONHsAZAsL7Ib4kTDz4PNwvQerfwQWX6keHlZYnFLutLKvmrsSsqKo8DkPOb9j6mphqxObqrXZI1HfHuUNK9/QbX+KXjC+rf6MPnVuTz5vER83+RfLfn8SMVD0cP4ddZqT7E8+tBSddLR9ACe/fv2wVb4WzIxWsXptLDWiiaVMRwgf48wfC9cIkMHkw770quYQ7Hxw3eIAV5QLf0k/J2CsvUg9lMaHd0+nMMCra9UvqdDJ3NCpN4IvVxbIQYvVRbwd/xWnkK09yXlRmR3bGX1QgvmfXsGXkTkngeh+b6JFpwqt6MIL0mNA/3n5VlchPRPnEYnsLrUorUeywJ05I+K/7+Q99+5GB0cU8zOG29eACYa79hdj8DH6f+UhwNHDcln+AeDWHHGeLwovxYQWJbi4efUVZsxQryi6gJW4tYdth9j/x9gcTLOUXFs7JNrOJ4RBy+mBTQwEyjYAmbI1Ur2y5KgmuZqe3RMmzWGTy3FTW/2O5qrXXCA1lZpoUQJil5LKPVzDP+N6Cwvh4B74uy4f9/e7F7MuaodOdvHaN1QSY+xyxAH789IQECrX6GUflqyUx59sW76znjyL5EcsLCwGrjAK+adrbSkuTrqdXwOLdcvJh8YKIii/YtY/JjLeX1THI+/PQO0iv4Gqh6MKjSpvS/KffBd7iMuB1/Sqsx7XOatUYZErUr1a8+VLqT+ZtGJpmsfPFJrREuY7lYd71f3X5hUovKbG4td+cj7ABgC7OMttmUrvsXGS+kg4iU0k57wL/auBDyq6grPTCbJAAMzgSABgkSMGg1CNEGzIAQSkggIE8PMsActxWeqCDqDQRGwEyrDM4W6tNpqtdZata3aailYi2CUxQ0EFxQX3G+MBhSEsMj0P+e++2ZhMVjp8n2d75uZ9+6+nnvuWV+XsFvneZ36bfZfCdDeWG8n31jMgoHabYHkTxDwsB6TGaPYPnbzQdwB4tBRx6XZHoyHb20J77+8JkH+c1j8+/xA/PuKhPyRiQn+f2R5ifvxAtqDty9gCLUnBXLpWsFYC+MNl0khfMN2rVP48V7XW/ucd+lvvEwcOuqQ8njUKKcOqexQlh2Md/WIc6+Su8lOjgcQCthXl8/l1oFjMjsqvNZP7J9jHMnBzLpCo+rTUXWN+GA+L3VJLsayzbDQfY6AGCxWJYen2ls66anAYCE0JlHGznollEUU+GwvGTk6flfNSeD/J4x/Yfx7lB/hkQ5SNwfISWqS/kzThdW0Op6cfeTVkZi/Jn9b0XgS23LdTuPXCbreTEGxJ209+gFwTHuVR2CPJMQ7jqy/wdwx3if1nUqG2W9IWbPdnmRVyNtR63fG1Q/PQbaAnULJ/OvR2gv5j9kJ8h+zou8mPWEHNrzEBPjE8ut/oo3uM1UC7pltYgNfUQQcl91sBv30KQSBv503iyAgHbGBUgYXfMi7GlYjGleKWg60G4F/4ECvGHmp6WEmOEIfQWjSRN0S2u72RM4Hx+Xy6Cq+BLE+jGmoSwrWH3kZnO5Xts/Bb+13vpQzKA51saINtNPKVXzgNLVccQCU+cSmWaZoRDlgnKKSaL841SIdFDw+W57fyC2pGPRCyZDaRDY=
*/