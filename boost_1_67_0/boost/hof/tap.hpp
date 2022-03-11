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