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