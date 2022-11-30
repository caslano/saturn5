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
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
*/