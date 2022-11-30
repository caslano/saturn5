/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    rotate.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_ROTATE_H
#define BOOST_HOF_GUARD_ROTATE_H

/// rotate
/// ====
/// 
/// Description
/// -----------
/// 
/// The `rotate` function adaptor moves the first parameter to the last
/// parameter.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     rotate_adaptor<F> rotate(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(rotate(f)(x, xs...) == f(xs..., x));
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
/// 
///     int main() {
///         int r = boost::hof::rotate(boost::hof::_ - boost::hof::_)(2, 5);
///         assert(r == 3);
///     }
/// 

#include <boost/hof/detail/result_of.hpp>
#include <boost/hof/reveal.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {

template<class F>
struct rotate_adaptor : detail::callable_base<F>
{
    typedef rotate_adaptor fit_rewritable1_tag;
    BOOST_HOF_INHERIT_CONSTRUCTOR(rotate_adaptor, detail::callable_base<F>);

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    struct rotate_failure
    {
        template<class Failure>
        struct apply
        {
            template<class T, class... Ts>
            struct of
            : Failure::template of<Ts..., T>
            {};
        };
    };

    struct failure
    : failure_map<rotate_failure, detail::callable_base<F>>
    {};

    BOOST_HOF_RETURNS_CLASS(rotate_adaptor);

    template<class T, class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(const detail::callable_base<F>&, id_<Ts>..., id_<T>) 
    operator()(T&& x, Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        (BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(xs...)))
            (BOOST_HOF_FORWARD(Ts)(xs)..., BOOST_HOF_FORWARD(T)(x))
    );
};

BOOST_HOF_DECLARE_STATIC_VAR(rotate, detail::make<rotate_adaptor>);

}} // namespace boost::hof

#endif

/* rotate.hpp
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
*/