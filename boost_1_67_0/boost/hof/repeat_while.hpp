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