/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    eval.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_EVAL_H
#define BOOST_HOF_GUARD_EVAL_H

/// eval
/// ====
/// 
/// Description
/// -----------
/// 
/// The `eval` function will evaluate a "thunk". This can be either a nullary
/// function or it can be a unary function that takes the identity function as
/// the first parameter(which is helpful to delay compile-time checking).
/// Also, additional parameters can be passed to `eval` to delay
/// compiliation(so that result can depend on template parameters).
/// 
/// Synopsis
/// --------
/// 
///     template<class F, class... Ts>
///     constexpr auto eval(F&& f, Ts&&...);
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [EvaluatableFunctionObject](EvaluatableFunctionObject)
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     int main() {
///         assert(boost::hof::eval([]{ return 3; }) == 3);
///     }
/// 
/// References
/// ----------
/// 
/// * [POO51](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0051r2.pdf) - Proposal for C++
///   Proposal for C++ generic overload function
/// * [static_if](static_if)
/// * [Ordering evaluation of arguments](<Ordering evaluation of arguments>)
/// 

#include <boost/hof/always.hpp>
#include <boost/hof/identity.hpp>
#include <boost/hof/first_of.hpp>
#include <boost/hof/detail/result_of.hpp>

namespace boost { namespace hof {

namespace detail {

struct simple_eval
{
    template<class F, class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(F) 
    operator()(F&& f, Ts&&...xs) const BOOST_HOF_SFINAE_RETURNS
    (boost::hof::always_ref(f)(xs...)());
};

struct id_eval
{
    template<class F, class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(F, id_<decltype(boost::hof::identity)>) 
    operator()(F&& f, Ts&&...xs) const BOOST_HOF_SFINAE_RETURNS
    (boost::hof::always_ref(f)(xs...)(boost::hof::identity));
};

}

BOOST_HOF_DECLARE_STATIC_VAR(eval, boost::hof::first_of_adaptor<detail::simple_eval, detail::id_eval>);

}} // namespace boost::hof

#endif

/* eval.hpp
7fY5eF5H2zfArFX4W5UYHCzgWcegXzlJ45NBE/iP040AuwxXH7ePyLvxkn3Qs1yvPmags/VqWzGeVFpT2JjeijEvPtRe3L88PJTNFxq9FzHskfqQsCxNixCfmiPxGE7n4ebgTqhqQbRcFFTgab1pRgVKVOxhOf1YOl9RRyB6XP/6sFiGJfpLHYGXKNw8l799MGx+PRNPqrEZfTqfgwYcbcVhZtLyS8nrfAR2fM1l++x59Xmz3q5n6+UBr0J/2ViVEfAivFratdZZ6a/EJ9puXmZbLeU2OhSfHrOukjdVYW5TBQbI9RXPRUrcCXW85AmS6xmqt3S1cJg6nvEEpU89Ayhx/lOYCOSxlCBrEH8OnzHWKza9CfNGqXDDUxRwRkepgiXPzvyLJRQ3aOFOqoR3x+JhLhuiknaQmN2VWbtGP0+XLxU9rzcGMXrA+loKnm4a+JvfS19u1jP2teLCW8TUEhARm80SpSgFhL9q59/nBGD98JAZ/+JCwtfx+CdHGv99+8KDYDXZWm7IyE/mfNnKETiX5DUHi9XDet+5tGOxdvqxckqAJ1OthP6cXuUStZGnnl6l3EJFuDi3Pa6jZnZrGB0P4XT7sglxU1KwYqJskJunIwcOPHn1zcZycf+/Fb2p15nUiCsx0EngyT92
*/