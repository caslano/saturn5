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