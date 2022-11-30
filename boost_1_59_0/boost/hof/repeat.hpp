/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    repeat.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_REPEAT_H
#define BOOST_HOF_GUARD_REPEAT_H

/// repeat
/// ======
/// 
/// Description
/// -----------
/// 
/// The `repeat` function decorator will repeatedly apply a function a given
/// number of times.
/// 
/// 
/// Synopsis
/// --------
/// 
///     template<class Integral>
///     constexpr auto repeat(Integral);
/// 
/// Semantics
/// ---------
/// 
///     assert(repeat(std::integral_constant<int, 0>{})(f)(xs...) == f(xs...));
///     assert(repeat(std::integral_constant<int, 1>{})(f)(xs...) == f(f(xs...)));
///     assert(repeat(0)(f)(xs...) == f(xs...));
///     assert(repeat(1)(f)(xs...) == f(f(xs...)));
/// 
/// Requirements
/// ------------
/// 
/// Integral must be:
/// 
/// * Integral
/// 
/// Or:
/// 
/// * IntegralConstant
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
///         constexpr T operator()(T x) const
///         {
///             return x + 1;
///         }
///     };
/// 
///     int main() {
///         auto increment_by_5 = boost::hof::repeat(std::integral_constant<int, 5>())(increment());
///         assert(increment_by_5(1) == 6);
///     }
/// 

#include <boost/hof/always.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/result_of.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/decorate.hpp>
#include <boost/hof/first_of.hpp>
#include <boost/hof/detail/recursive_constexpr_depth.hpp>

namespace boost { namespace hof { namespace detail {

template<int N>
struct repeater
{
    template<class F, class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(repeater<N-1>, id_<const F&>, result_of<const F&, id_<Ts>...>) 
    operator()(const F& f, Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        repeater<N-1>()(f, f(BOOST_HOF_FORWARD(Ts)(xs)...))
    );
};

template<>
struct repeater<0>
{
    template<class F, class T>
    constexpr T operator()(const F&, T&& x) const
    BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT(T(x))
    {
        return x;
    }
};

struct repeat_constant_decorator
{
    template<class Integral, class F, class... Ts>
    constexpr auto operator()(Integral, const F& f, Ts&&... xs) const BOOST_HOF_RETURNS
    (
        detail::repeater<Integral::type::value>()
        (
            f, 
            BOOST_HOF_FORWARD(Ts)(xs)...
        )
    );
};

template<int Depth>
struct repeat_integral_decorator
{
    template<class Integral, class F, class T, class... Ts, class Self=repeat_integral_decorator<Depth-1>>
    constexpr auto operator()(Integral n, const F& f, T&& x, Ts&&... xs) const BOOST_HOF_RETURNS
    (
        (n) ? 
            Self()(n-1, f, f(BOOST_HOF_FORWARD(T)(x), BOOST_HOF_FORWARD(Ts)(xs)...)) :
            BOOST_HOF_FORWARD(T)(x)
    );
};

template<>
struct repeat_integral_decorator<0>
{
    template<class Integral, class F, class T, class Self=repeat_integral_decorator<0>>
#if BOOST_HOF_HAS_RELAXED_CONSTEXPR
    constexpr
#endif
    auto operator()(Integral n, const F& f, T x) const 
    BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT((n--, f(BOOST_HOF_FORWARD(T)(x))))
    -> decltype(f(BOOST_HOF_FORWARD(T)(x)))
    {
        while(n > 0)
        {
            n--;
            x = f(BOOST_HOF_FORWARD(T)(x));
        }
        return x;
    }
    // TODO: Add overload for lvalue
};

}

#if BOOST_HOF_HAS_RELAXED_CONSTEXPR
#define BOOST_HOF_REPEAT_CONSTEXPR_DEPTH 1
#else
#define BOOST_HOF_REPEAT_CONSTEXPR_DEPTH BOOST_HOF_RECURSIVE_CONSTEXPR_DEPTH
#endif

BOOST_HOF_DECLARE_STATIC_VAR(repeat, decorate_adaptor<
    boost::hof::first_of_adaptor<
    detail::repeat_constant_decorator, 
    detail::repeat_integral_decorator<BOOST_HOF_REPEAT_CONSTEXPR_DEPTH>
>>);

}} // namespace boost::hof

#endif

/* repeat.hpp
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
*/