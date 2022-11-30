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
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
*/