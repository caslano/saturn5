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
lDNF7IbIzQpFwKmT4dlMiInn+8rReFBB4P4ZM9BdBZaK0AoObLocekyV8GYGrOY/PV6NxqOlUgI0YY8uLACE8e4ZCLxzL10OEgwObA4WXOcY3BcCjiq9fTzKUGNXNw/4LsfLCKwCwi/Bv+Qg5vFXV5nL7k6pzbKGBdWz/A4OS9b3+SiL39aua8+3TfOlNrKWvJ0kCB2MrcyVvnE1GkyU/K7Rts9cLGC3I24M4s3cvjGdqWgSeDtPP2pcYrrgqWdkH9+oclLBftIG+oWrs8TBWacRtwm7t5EENT4r2jQ7Dd+SQ2kxRMe+NjBtQxKFTL88IiRzk3hwUyfTT7bjJH4Rp2ffTjSv8c/mfXgW3XKpnMH5ogT6tgNCSoJXVEw0RwVRCsH7nTO3EQx2vDDItuNDDgOsNqSIA4HwXYL7QVuqiMml41zoXvxf+eCg1z+XahGZyNe6uqDdRacV49wq5DQmGEMDvO9jUH5R7Y7EHaI2CY7YZeweK7zefdi3R/GAIcpTtxAIod2MuhYhb0rFPH7cJwTPafp99abjIZD+x5q/HAzxuBtQve1xjxYLlYAYEn2UROgnBeQWgQb9IRcucWgKcB9CbCGPDQR+1hwCTPNRCdGAAwyHI978faPgqCkre+F/bhQw/He/u5S5h53lPxfZfeycTgzQXVOGUoPF2nETBEOjsK268/uoPF3R8eQ9uD8kffqJhHfpWwRLHKSY
*/