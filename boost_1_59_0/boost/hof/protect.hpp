/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    protect.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_PROTECT_H
#define BOOST_HOF_GUARD_FUNCTION_PROTECT_H

/// protect
/// =======
/// 
/// Description
/// -----------
/// 
/// The `protect` function adaptor can be used to make a bind expression be
/// treated as a normal function instead. Both `bind` and
/// [`lazy`](/include/boost/hof/lazy) eargerly evaluates nested bind expressions.
/// The `protect` adaptor masks the type so `bind` or
/// [`lazy`](/include/boost/hof/lazy) no longer recognizes the function as bind
/// expression and evaluates it.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     constexpr protect_adaptor<F> protect(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(lazy(f)(protect(lazy(g)(_1)))() == f(lazy(g)(_1)))
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [ConstInvocable](ConstInvocable)
/// * MoveConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     using namespace boost::hof;
/// 
///     int main() {
///         auto lazy_id = lazy(identity)(_1);
///         auto lazy_apply = lazy(apply)(protect(lazy_id), _1);
///         assert(lazy_apply(3) == 3);
///     }
/// 
/// See Also
/// --------
/// 
/// * [lazy](lazy)
/// 

#include <utility>
#include <boost/hof/reveal.hpp>
#include <boost/hof/detail/forward.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {

template<class F>
struct protect_adaptor : detail::callable_base<F>
{
    typedef protect_adaptor fit_rewritable1_tag;
    BOOST_HOF_INHERIT_CONSTRUCTOR(protect_adaptor, detail::callable_base<F>)
};

BOOST_HOF_DECLARE_STATIC_VAR(protect, detail::make<protect_adaptor>);

}} // namespace boost::hof
#endif

/* protect.hpp
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
*/