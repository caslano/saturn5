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
976pcPxgQUVxEpHwfZRLwqIjekg6TQ50CfSZIrAf9aWBM2QMVN1LsTRF9RaJl0EvNn121LVIWB8K1aHmmcUlTtU+Onb9M2x4sAGkswHuWu26x/N0rG82QYQDancn6n1P16TT9s13FrnAWEuhTQK77EgWauGLIi4o2WBXG9tcklVUMVKX3wz58R4HdfDRhL1y3sZNycWdjcreslvznZilLmzWrTT3O0GGRekSOai3/P5zoH0Q5csRIQTehFIW+rDH9Wm7i+wS8HleA+oQY6YedaqLRe6A/9fLzRlus842YJhBwMLYPQ70qZGgpRvL1swsZuccqSRaOrmBzQgAUTMK9qCsfKPtDzt0iXX+zwEnRHIfWGjSZGUQLQ9N8hqw1xlDMh1gJPa/K/jSbOaJaY0ddRThI1GFoSQqSdaqV8H8unD2k4R7pcHSVxhXSXPXq5PhZcsFEKp3i0qcXLdewPkU8qlbIyqzYSnwNPbQK1c3cw02Zra/RrbOA1Uw24FnjjcpT4TZZIqsg4pOi4NU9+KRvwYVP729EMowu4QzqMq6UPl7AI/F89nWGi+AFw==
*/