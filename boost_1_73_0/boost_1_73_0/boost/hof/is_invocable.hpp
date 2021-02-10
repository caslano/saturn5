/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    is_invocable.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_IS_CALLABLE_H
#define BOOST_HOF_GUARD_IS_CALLABLE_H

/// is_invocable
/// ===========
/// 
/// Description
/// -----------
/// 
/// The `is_invocable` metafunction checks if the function is callable with
/// certain parameters.
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [Invocable](Invocable)
/// 
/// Synopsis
/// --------
/// 
///     template<class F, class... Ts>
///     struct is_invocable;
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     using namespace boost::hof;
/// 
///     struct is_invocable_class
///     {
///         void operator()(int) const
///         {
///         }
///     };
///     static_assert(is_invocable<is_invocable_class, int>(), "Not callable");
/// 
///     int main() {}
/// 


#include <boost/hof/detail/can_be_called.hpp>
#include <boost/hof/apply.hpp>

namespace boost { namespace hof {

template<class F, class... Ts>
struct is_invocable 
: detail::can_be_called<detail::apply_f, F, Ts...>
{};

template<class F, class... Ts, class... Us>
struct is_invocable<F(Ts...), Us...>
{
    static_assert(!std::is_same<F, F>::value, 
        "The is_invocable<F(Args...)> form is not supported because it is problematic."
        "Please use is_invocable<F, Args...> instead."
    );
};

}} // namespace boost::hof

#endif

/* is_invocable.hpp
nGRtQlzrJyegtbBA2cnhW+jFjmBRiGLq3sBPu0WfMcVWe2zfLEUuzFeS2FrvWSHV8+aemt6ij8purxzDm33MssOMZPJmL1nazeaE6e0+0u7Ls9dm7w1Sig46J8vour1TcyATxd/X8PLCPO+ag7NZesT6X9exgJreruEVZniO+1beibV99WXWtGy6C6uX9U/V1GKlH5hTATzkO5KuljPUy3HZHcNwDylbThOt4HBRGvJ4EXCCBcBGhdPlr7VWPJp2Xx6r84rIp+LVIW/V8l8Y4p35sSh4durp7AhxAlU/WBH/2sNdvqvlHAtT9ULzaL3VIrjn2u0exBFUyeGvhxhL2odvZ+XNz0chqXefzJhibWsYj4Uq742kr0uxmOTtGPxS17TOX5lOj43qzini/8YqorXSMDqPQvvt9sW9UvRz/mc4wptFUYOFkEdsXqypBrzrLwJ08vQndWb8j1I2XT21isaMH7a6Rz8YIuAXh9bG9fZabupUjiQbWiV48kGK+jgk3gQrReIPPgdJNM7KkMSDz0EaXPTLcHC4YK97kbLeXBEnG9yy+q4XvVDb7Ps0aKGT/BdQSwMECgAAAAgALWdKUqxozEf4BAAAjwsAACoACQBjdXJsLW1hc3Rlci9wYWNrYWdlcy9PUzQwMC9t
*/