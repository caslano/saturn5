/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    lift.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_LIFT_H
#define BOOST_HOF_GUARD_FUNCTION_LIFT_H

/// BOOST_HOF_LIFT
/// ========
/// 
/// Description
/// -----------
/// 
/// The macros `BOOST_HOF_LIFT` and `BOOST_HOF_LIFT_CLASS` provide a lift operator that
/// will wrap a template function in a function object so it can be passed to
/// higher-order functions. The `BOOST_HOF_LIFT` macro will wrap the function using
/// a generic lambda. As such, it will not preserve `constexpr`. The
/// `BOOST_HOF_LIFT_CLASS` can be used to declare a class that will wrap function.
/// This will preserve `constexpr` and it can be used on older compilers that
/// don't support generic lambdas yet.
/// 
/// Limitation
/// ----------
/// 
/// In C++14, `BOOST_HOF_LIFT` doesn't support `constexpr` due to using a generic
/// lambda. Instead, `BOOST_HOF_LIFT_CLASS` can be used. In C++17, there is no such
/// limitation.
/// 
/// Synopsis
/// --------
/// 
///     // Wrap the function in a generic lambda
///     #define BOOST_HOF_LIFT(...)
/// 
///     // Declare a class named `name` that will forward to the function
///     #define BOOST_HOF_LIFT_CLASS(name, ...)
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     #include <algorithm>
/// 
///     // Declare the class `max_f`
///     BOOST_HOF_LIFT_CLASS(max_f, std::max);
/// 
///     int main() {
///         auto my_max = BOOST_HOF_LIFT(std::max);
///         assert(my_max(3, 4) == std::max(3, 4));
///         assert(max_f()(3, 4) == std::max(3, 4));
///     }
/// 

#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/returns.hpp>
#include <boost/hof/lambda.hpp>
#include <boost/hof/detail/forward.hpp>

namespace boost { namespace hof { namespace detail {

template<class F, class NoExcept>
struct lift_noexcept : F
{
    BOOST_HOF_INHERIT_CONSTRUCTOR(lift_noexcept, F);

    template<class... Ts>
    constexpr auto operator()(Ts&&... xs) const
    noexcept(decltype(std::declval<NoExcept>()(BOOST_HOF_FORWARD(Ts)(xs)...)){})
    -> decltype(std::declval<F>()(BOOST_HOF_FORWARD(Ts)(xs)...))
    { return F(*this)(BOOST_HOF_FORWARD(Ts)(xs)...);}
};

template<class F, class NoExcept>
constexpr lift_noexcept<F, NoExcept> make_lift_noexcept(F f, NoExcept)
{
    return {f};
}

}

}} // namespace boost::hof

#define BOOST_HOF_LIFT_IS_NOEXCEPT(...) std::integral_constant<bool, noexcept(decltype(__VA_ARGS__)(__VA_ARGS__))>{}

#if defined (_MSC_VER)
#define BOOST_HOF_LIFT(...) (BOOST_HOF_STATIC_LAMBDA { BOOST_HOF_LIFT_CLASS(fit_local_lift_t, __VA_ARGS__); return fit_local_lift_t(); }())
#elif defined (__clang__)
#define BOOST_HOF_LIFT(...) (boost::hof::detail::make_lift_noexcept( \
    BOOST_HOF_STATIC_LAMBDA(auto&&... xs) \
    -> decltype((__VA_ARGS__)(BOOST_HOF_FORWARD(decltype(xs))(xs)...)) \
    { return (__VA_ARGS__)(BOOST_HOF_FORWARD(decltype(xs))(xs)...); }, \
    BOOST_HOF_STATIC_LAMBDA(auto&&... xs) { return BOOST_HOF_LIFT_IS_NOEXCEPT((__VA_ARGS__)(BOOST_HOF_FORWARD(decltype(xs))(xs)...)); } \
))
#else
#define BOOST_HOF_LIFT(...) (BOOST_HOF_STATIC_LAMBDA(auto&&... xs) BOOST_HOF_RETURNS((__VA_ARGS__)(BOOST_HOF_FORWARD(decltype(xs))(xs)...)))
#endif

#define BOOST_HOF_LIFT_CLASS(name, ...) \
struct name \
{ \
    template<class... Ts> \
    constexpr auto operator()(Ts&&... xs) const \
    BOOST_HOF_RETURNS((__VA_ARGS__)(BOOST_HOF_FORWARD(Ts)(xs)...)) \
}

#endif

/* lift.hpp
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
*/