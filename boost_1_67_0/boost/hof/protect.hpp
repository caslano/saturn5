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