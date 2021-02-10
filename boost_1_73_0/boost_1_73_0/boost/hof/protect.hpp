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
PO80LtBZ97JZE9dnIPKz+KIss9V5YmmYPjm21tl5u4tOXmIJKYJWuXCBnCwIMieKnBOOE8eJhuQLimxVW78elYW7pRChm1Ir5bE0vCWLoYJlcqfrhlHK6ba+crqqYKVviUgC9ZyUdrOfnm4cEe64OaNCshnKlZxu4l1tFmE81wOhJiheQGeBmNN592Z1tTMsKcFqXDrt7of64u2y1/rY2QiRYlwEKcPZGSVFsD1OR7pbzpuddZU0fWk4liKxxJ7xl4W64fCacAGNdnp8PYuVf0CWm7jrijY0wWblwXCubssO3tzjr8ZLq1oC5py+vr7G/myhgdIVyuMiz9JK351X2dqSX9mSJQBZHFebTqbV/f8RIBN55+kER4edOh8lKi3QD3mfrFbUbmvpCLCzYTOyQ4KzxksZs9aopQIW7zuBMN6h+JaZPid8J+GIvnJJd2j4sCzcEShDcgmEezcgW373A1p0uzjIdEaD1TDcWdTyeLWkF/ZgHeFxf9leFfEG4Xr9SqYvp281zbTT09X9A2iPQ4Y/MUMWVlUm6F+ZrbLZpo8JaCu5m2r0/1N3fVMGbn1zoc9yiGR6iTmyVYKYLZaG98I7uBX/Rzi7TVT6zMR5nljGj8Z4a5CalxjcZt8UFwn8P8xzLcd/eQdj8QW/
*/