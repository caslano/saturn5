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
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
*/