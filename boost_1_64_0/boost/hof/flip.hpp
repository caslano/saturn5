/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    flip.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FLIP_H
#define BOOST_HOF_GUARD_FLIP_H

/// flip
/// ====
/// 
/// Description
/// -----------
/// 
/// The `flip` function adaptor swaps the first two parameters.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     flip_adaptor<F> flip(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(flip(f)(x, y, xs...) == f(y, x, xs...));
/// 
/// Requirements
/// ------------
/// 
/// F must be at least:
/// 
/// * [BinaryInvocable](BinaryInvocable)
/// 
/// Or:
/// 
/// * [Invocable](Invocable) with more than two argurments
/// 
/// And:
/// 
/// * MoveConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     int main() {
///         int r = boost::hof::flip(boost::hof::_ - boost::hof::_)(2, 5);
///         assert(r == 3);
///     }
/// 

#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/reveal.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {

template<class F>
struct flip_adaptor : detail::callable_base<F>
{
    typedef flip_adaptor fit_rewritable1_tag;
    BOOST_HOF_INHERIT_CONSTRUCTOR(flip_adaptor, detail::callable_base<F>);

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    struct flip_failure
    {
        template<class Failure>
        struct apply
        {
            template<class T, class U, class... Ts>
            struct of
            : Failure::template of<U, T, Ts...>
            {};
        };
    };

    struct failure
    : failure_map<flip_failure, detail::callable_base<F>>
    {};

    BOOST_HOF_RETURNS_CLASS(flip_adaptor);

    template<class T, class U, class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(const detail::callable_base<F>&, id_<U>, id_<T>, id_<Ts>...) 
    operator()(T&& x, U&& y, Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        (BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(xs...)))
            (BOOST_HOF_FORWARD(U)(y), BOOST_HOF_FORWARD(T)(x), BOOST_HOF_FORWARD(Ts)(xs)...)
    );
};

BOOST_HOF_DECLARE_STATIC_VAR(flip, detail::make<flip_adaptor>);

}} // namespace boost::hof

#endif

/* flip.hpp
g0zGNhCs4YGipBlr+GKqmS3Ud801BGAz9iLuX3stXk1i5OMnteAW8+8+cor5a+IjiuZQ+xSiRsEe1Ftt1BhOeovdhDcHvQl6y6C3HIrtSG959OaiVixsmew1smRthe7i4uWLcy0BVV+OtTbLV8ZagDW/Oq4Vli/XWgLPINcC/ElPZwe9aeVY/GtT0v6RbPb39+CHnYKf9Xrx6tvPWzbpYNKsENEUT2TEfJIDI2kgecQ7mPL1BVnB3vMN9iZHouIR1AahXic0wVtEfpWc/UQ2YaC3yfRwhEcBQfzT1pHI6b4ZXB+E94S86S2OSNcSuuC3Hlu1kRelcoEHkYxW8ecgAe2ugyp/S8Gs8LPlHiTqVNuXXnvjtUNt1/UdeH3hLo6aGEHizA0X2xwoOPwicvu2TJ0KdxFO4iAQrBgH4wBYSACnak3HqAOvWkkQaUuKvsk1+SCi8xCtUUHwxLyP5WvzLMqscPyKcWTPUhNHz+I6R+9OtV3w06dDbYdN5Y7eHRini4ECMCJbJgLzbM0D4iOoM9KiBJMBBQopPfh0n+/raCdOAqJt4Agaz7+jgl4yg/y8AagD8pN2J3W6zsXrvIVoyFDPTbDVdpWZRC3AGP53lIevxAiIGzCPt+y0/8beNSFq4S1xmj6V70Xbd6PLV9Rw8ZOXmBRrqLGRou58JDin+AJmjn6qf5/AHEZye12WuAmaBYHnRvGL3vfSVm5mThRrLr1c08i7aRAaFZv/GPsfboY4A09DDp9/HbXOZ51Vel9qcMgOajf22qe1KEgKf/wtqUmei+8catodslk/Uu5XZAAGkUrkHhI+cVidhnuuDDupzLA+PD+nVjdy8a5G+J+Hj9gXZM/gTQi4QnulcfDUlewOD12E/x8cEDraR4+RCrp//jCs/eTbQnmIcctk+fw/3OXb/Y73WegxJOsYEO+8Jj1SYgEx9gF+hUl7/0zX5E2n7MDc4Mgg+bfRKv/AXST/SCA9Q+/gMSd+auLrvB5iPMTRb8mLrikv+nmb+lTRtIoqgg+PwZwL7mHmzMcHYb6J9nlteok4kyC2GUsY8FLwtQPfscCXt5axhK6f6oms8m4mUTjVibeX6O0K7+yAfmjQYWzV8iDZoDciz3o3IALxz+LH9N9awp++XYY/E849n5O5L/O4nlMU6axPKnJEJjv0Hr6evikOXRWQt51+7sp7Gz/YZRc+Ulq3GeUQNs8f7M/LuAX4duIbr5Pw6pCvXh3Ela+j8XrUxq/5eD0oX4vwGpOvg/H6hXzNw6uQrxPx+ql89eB1t3wtx+v78jUXrzvlayleCcXIOqYIiVL4x5R757iemuRdtPFjh+up7ca1ouTq9oeDGGV8Dx3C//rPj9L7fcfwv+upu7y0QR/pfQ8d5uDjHLwVeVepiCMcEeeIzQhB3INE1odkQTa3LOgXKv0xDrYbwb9Rwcc5OIODqWvNl1gS0hs/QXyc4zMR77vQN8NBeX9Ijfg44a4/Q8ConMeoEr71x1LwREScIzINuD9SwYc5OFGv1SriCEcY9UIE8YjEifB57ChHq9qtVbmOcbCq3R9U8HEO5tqhBW5Bu5CnHfjyUZlCv5Ob4A5Kh9Yq1O/k8u/IMAq620h2BQxFKw9xFEGCCJvveuo1ArEyzqGqfj9FBg4+bJar38WVU+mPcERcRjzAEVs4QkJWNXtYFXSMg1EzSr+MsAcyrqfeoArNRQpipGcOmtSPwFGQm0WRA8m+D/yHc2GSHqp2P1MwVOMxjMUWZJMb71cqvWo8WYfUyqHxOOKR1Mqh2ThihazFcNQClAyhBkgGxP1IqupCGfQfc7aVNqMet3NRqBUjK3G6U+GESjFOMvh+C/kQjAoy+Sw=
*/