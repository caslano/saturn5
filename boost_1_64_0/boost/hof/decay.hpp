/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    decay.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_DECAY_H
#define BOOST_HOF_GUARD_DECAY_H

/// decay
/// =====
/// 
/// Description
/// -----------
/// 
/// The `decay` function is a unary function object that returns whats given to it after decaying its type.
/// 
/// Synopsis
/// --------
/// 
///     struct
///     {
///         template<class T>
///         constexpr typename decay<T>::type operator()(T&& x) const
///         {
///             return boost::hof::forward<T>(x);
///         }
///     } decay;
/// 
/// References
/// ----------
/// 
/// * [n3255](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2011/n3255.html) - Proposal for `decay_copy`
/// 

#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/unwrap.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/detail/forward.hpp>

namespace boost { namespace hof { namespace detail {

template<class T>
struct decay_mf
: unwrap_reference<typename std::decay<T>::type>
{};

struct decay_f
{
    template<
        class T, 
        class Result=typename unwrap_reference<typename std::decay<T>::type>::type, 
        class=typename std::enable_if<(BOOST_HOF_IS_CONSTRUCTIBLE(Result, T))>::type
    >
    constexpr Result operator()(T&& x) const BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(Result, T&&)
    {
        return BOOST_HOF_FORWARD(T)(x);
    }
};

}

BOOST_HOF_DECLARE_STATIC_VAR(decay, detail::decay_f);

}} // namespace boost::hof

#endif

/* decay.hpp
EFprDHChDVFkCcQuMVCKSQCzSBqDMfSCK578jkWYtQQ9Hivq0LneNKE5jeJs+4d/5kgBzDmkTwDY4cmr4DMddvvCak9vOm2WtttrxbIchyrCfxK6mviyEH29O8Uj/6ogqJ1b6UG+Oh+LledVMiBgS8VXZDaFVzQfrD3sw43dEojtyA4q3OZsxolZiK1zYnPCJoZP4o6yTy5LU1dApJMk4zIpxShLBHTXqmVwYrEcMSuYJQLGPHqiBDy457mgNL3OddOioLvorXA0BfPsQsYxXwmV0/En42haG4uepQM1JDJThisrTpgKiGOdx2zus5dJlpEUex0/Qmfl7ko+uuZjxJlQgUuKPkLlKdxLktBZoRJfuj8Xl48fdN2/+rEw9HC1/7yxGUfkO8YYa189VLZ3j9W77WhCnM6/y9GfRFcRVwyk06AAjFss8HYPqm18iS2OPWNrUOd4/bkTPOPFu/8RRgv2vbMNKnTHPNrnSMu62PR0BjpjI5EGb93o6u+WwOLwL2e1N+aDL6p12hINL7WhFzX2ZY8Bhv6E0e0BTuMbJrJRX89ERLejXKXu1A==
*/