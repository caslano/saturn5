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