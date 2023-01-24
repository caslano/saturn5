/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    tap.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_TAP_H
#define BOOST_HOF_GUARD_FUNCTION_TAP_H

/// tap
/// ===
/// 
/// Description
/// -----------
/// 
/// The `tap` function invokes a function on the first argument passed in and
/// then returns the first argument. This is useful in a chain of pipable
/// function to perform operations on intermediate results. As a result, this
/// function is [`pipable`](/include/boost/hof/pipable).
/// 
/// Synopsis
/// --------
/// 
///     template<class T, class F>
///     pipable constexpr T tap(T&& x, const F& f);
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [UnaryInvocable](UnaryInvocable)
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     #include <iostream>
///     using namespace boost::hof;
/// 
///     struct sum_f
///     {
///         template<class T, class U>
///         T operator()(T x, U y) const
///         {
///             return x+y;
///         }
///     };
/// 
///     const pipable_adaptor<sum_f> sum = {};
///     int main() {
///         // Prints 3
///         int r = 1 | sum(2) | tap([](int i) { std::cout << i; }) | sum(2);
///         assert(r == 5);
///     }
/// 

#include <boost/hof/pipable.hpp>
#include <boost/hof/apply.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof { namespace detail {

struct tap_f
{
    template<class T, class F>
    constexpr T operator()(T&& x, const F& f) const
    BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT((boost::hof::apply(f, x), BOOST_HOF_FORWARD(T)(x)))
    {
        return boost::hof::apply(f, x), BOOST_HOF_FORWARD(T)(x);
    }
};

}

BOOST_HOF_DECLARE_STATIC_VAR(tap, pipable_adaptor<detail::tap_f>);


}} // namespace boost::hof

#endif

/* tap.hpp
2qWDoysJMMiYRSIcvj9K49iPkA5QOjkuvzuHzKXiDrRj1ERPnD0dsvX909gBjAnhlF3H3Y9Jnatgvjmt74Bx/c+WHcCYsgZasCpJnS+Fk3b7/BJfiDxk1ECLYjmHbMfNW1hHOtTrQuuiueXMIYkvyKcZNS5dW9QnzCb6Rg44gjn8khRo2wGqA//En7Rqod+1MAKMLgK0XwELrubFEEawUoDlyY0hCH6r78QDby6wtPW52j/fgnq1gCvzAOAxPRELNPzB3EuURBAZIRANERhLCe4RoAcYumoOANwAOAH8+f0+AB4AXAB4MSJ2eGqARkqAuQTg8k8EqKUYim9JWlWzBlhdVAagDeDpsdsnmABAsRHAuyQAPwDOwERWAGNAFHIA/tTDBsACN6FwhEDKEH+hBYwyA1qqgV4UsI5zAN08GJHUmXittbMVwze4FmNbkLADnv3PWywRm66xc3qt90od2nsFNJCrAwA+GwEPskCA8kMEs3tSwJdnAL4C4AJQAEAV+JnHSeyPAe8uxKgo6bAfNL1+liB82AlRJXtEddEZyRGIrpgDz7j8O4IQe5dXBia6nBGRE4Gkbaetfrqrah07G9pCVJv+5BL5vcoFp/wr+odeb6eLgiKWPZOGFqx2QrSsIM7O0ZULNEuNX0ZeqFoC/sa/+JCeoJR3eJez/pyTDnTiXgIGHDCa/xxlCoyi+XxGf6QIxMcBAKaBfzVC
*/