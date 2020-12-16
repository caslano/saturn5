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
03h6KIM1pfp44uMrHk9jr5wSmqBzyZHipT9yVcSjKU38sg9T2T4fT0XiPjyRUnZqLcjCu4snpLAPHOGB/kEO1aCl1KDNb/OsqfVG3v5SvDrMiOON7iXR9Nr1VmkHSVOk3UYvTcFqp/GICGaTinhSFH8w4W7oLbtzJLqzHj8pur4P35p7CvnNv45U7dWR3Tb41SGrIomJBUPuundz1HnOlTS5ywwyFxKZ7/6FyWyujDErXaBfT4RJHVm40cBraCRXUR44j+k3AnTwiCQFkB9a8N/34hbJo6KvfmrMG7rvzu13Zyd6iZz9uKfIbtvQwd0G0qvRbx50nBcEz9I6xB+dhDyXmgiDYii9Bt4uHGrvS03ypbYHTASNMAqRZ+mAYdVPPo/F2mu4ll7Yifs/NHX44xbu8Pbh6HI3caFh/hpHcpbbLQaP0RliBr6pK+iYjcfSnjdpIfKIDf10r3UlCPTfOIqOsruFTgMjzO2szLEF+3rFrUy/jejH7iSUXVI3JQQ1oHhjKHc9upggAh1Tjf7iHyd9FmPkE3XkNkIeLmqu4L6IuueIfVgEEpe1Afqy5lLDFxRUESu09lPTaQwI6kbuyPMsDYmo1ptQlZtRYSbXETVb+qoAPyiNkoQgdLyoNZXvay4vik05+plzxKnBOrP8eJFhKpBxGMp9ruQcOeYcypKSHr7pdfj/n/+ND8uffN0RK2xnWY4rVHCwqpri7waHGCOjIEHgy2SrD2INelSQduOqYyEJ1lC52UP2+q0ZLOIZKAbGUQSfOAZtHNMn7eO349RRc/OqJHrDFBnl0+SnmTbFaSiDJ0LwX1pgaeyuV1tTi6iFtPV7AY+a4HXwld66oy5cDF5QI64wSmuXFtCrrXo/PDPyReZjmSjicU7fL774QweMQYiv2B66HGzPeRcMbEIjo+E5OOvF5bd2B+Nd1vsw8bkioSkuBDPMwfpQcmh5KfjZNOggZDOfzohCfRjJOYo4iSNaNx9oJiag6VdV8oXzumJwPPjP1N8Sv4qP3T7nyB+13xqWpeTn3OK9KoY82cfjcJwIXuXgG/B1fnr1K+dH6xZG64JkzW/DuOpZN7e5wso+xXzrNHeQr7u7i2rpRBFqj5wZ0pdc+0D2jch/vOLpAnQVOLi+CJLenng++N3lmnskSuihO51NpAZHF5yE5Jp4OgIJuEfVUoLa3X8nEssI5lAqDeYEwPm807wER9c14iL8BYnsFUr5HaLb3Rx8rfe4xhXk9n4M2r09x+hfEvz1ehnTUMY0EH+Rop8taW3/Ie+HW11s/21T/ZXvUxKzeh3qr2E8h23YNfwuRruGSHiJJdgXOQr0nLlZ+G4fSFJ4dU7L/qzIW1YIUAVadS6+crF1eVkKxutqCN21PXn2cFikznLwlFMOVi1knpKvRvCcaJgG8fFqEFOnfp9FMdQp89tS5C9MzH8+h0Of7pK074x8EQsWYc0egm3QORhhJeijhh6SreUHZ0EwbB8K0HSgOZHeZpACjQMoOAagUQBhBlJ1ZOymtbU7+H229EiexAYFO+UwpEDk/WtrPDCGuA7Sjm4DQTcaaHpj8xc+u7NqYT40EK7QGVqVn+y5Ty5DcGYRNr/goIRZfQUV0KYvbK60drbkOyufIeHwYAs3zCit6nJCc0LJi+E8E46TEnCcovkunwBfGsDUnslu2SogCOU5r6uB4VTCAu+ScZ7p1797SH6tD5/9MmvVwnPEJegYjbiMrRrMshZcNK+5ysrCdoZd55kAlNbXEcdpZcD+7iQQksdN4gbSzGQv7fXy0HTDE1a6HXoAxQZ0YSPZLUVon1mxMCOY11kRzAgNMGb8CQkN/myne+GKBFhRAuzngNnhRXk=
*/