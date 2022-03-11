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
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
*/