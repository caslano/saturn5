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
avbg7zWfQ7oh88RM+f2SpqryxZcVHmqSAWLq8EGIScX/z6m18sBjI6HolquvHMBuM7MRRxMPWEknvEcvTHYJBtY3LFlzxs7NSS+UevPbHMKAYZ2shNyoaRTMs9Fi98CXZ2BV70IfBkmXt+r/fkGV/eQBXYQMByA5nMLRxOEDJs1s3FgUnvtIfqPS5yKhuZRPUtcdOO+ebVmpoGt/+km5EWkTqXq4NCzOhDHfW6KviDc07IvCWM8oiCUmVaGpZbzQKS1CV6+e44LRY8/TF4C5osSW/pm31abYJ8Yj1vXaNujwuD2H9J8Equ/XhP89+VzkGAy47rpL8a7c+duuDDctqhdM9oV+SyNR7UlfNc/b2GyG2R8M5dVxwKX6q0DnO7kRWgFnYAXeNKYwHi5RajgtZJx3lPBctfQUICrnVT3d1VHxUFpKN5yw8R1gjCDUG4peBpMCwiXwYEgog3PXHAPiPOv04FTq6VY9JQGUKM2/+/bjSCRSlmWkm+PCQgDoR/IiEIJtri3PswwCXrQddvfZgOTBmYblpXJauCByWUj5Nww+k/HCvbGudnU93w==
*/