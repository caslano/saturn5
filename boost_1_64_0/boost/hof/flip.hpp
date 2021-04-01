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
5WK7NoRycDZ/9I3mIOr9GdFUgMsDodjSDiOyx20YCefSx5+jk7zYbzalD25b33Oor2c+dJ0aiSsS/ROrBCysfrp92t/+zKPXr/149nSXyd5N/MLVX//Ei0+hwOyjVMY47wNQevoUm3mZY7Xiq6FG7/vNDnazVPvEFACh3FUyLBOgHgDs8Dy1/h3DWrNasrWhnH2A/mmXmhUK7J4XERifHmgIvgqeMpYloMU83edtMI7TPkT1PhpmMWmGYqHRiSjCYKpATrwSEuh5OdjoMRk8JFVAiXDLwFzvODU/TSQB8yqc6KhJ1ag/PvZ1L7nEJNaBJeXIsN7pT47mM9tYo1F6XoGgf2p4nbJmf8d+YKmHqFaeMVBGccS4SFIDo4ISp1USZaC5+G4UxN1UYdBMh9Fl/4gVuCtnZDaMan5YLORcqdw1SOSLt/OjxF8HIATymbXnluJ/KZtRkMZYUgNfiUuphmfBJFD4I6Oa85tP+hTWEYub7Kd+AMsuLQcvqWqVvJqvk6B0Bb08aVKsiXFmsJ/BTwyd1DvePbbwq2raD0Mjq4zEHEPqkm4KEfnFCQ==
*/