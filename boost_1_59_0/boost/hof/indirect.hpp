/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    indirect.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_INDIRECT_H
#define BOOST_HOF_GUARD_FUNCTION_INDIRECT_H

/// indirect
/// ========
/// 
/// Description
/// -----------
/// 
/// The `indirect` function adaptor dereferences the object before calling it.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     constexpr indirect_adaptor<F> indirect(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(indirect(f)(xs...) == (*f)(xs...));
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * MoveConstructible
/// * Dereferenceable
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     #include <memory>
///     using namespace boost::hof;
/// 
///     struct sum
///     {
///         template<class T, class U>
///         T operator()(T x, U y) const
///         {
///             return x+y;
///         }
///     };
/// 
///     int main() {
///         int r = indirect(std::make_unique<sum>())(3,2);
///         assert(r == 5);
///     }
/// 

#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/result_of.hpp>
#include <boost/hof/reveal.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {
// TODO: Support non-classes as well
template<class F>
struct indirect_adaptor : F
{
    typedef indirect_adaptor fit_rewritable1_tag;
    BOOST_HOF_INHERIT_CONSTRUCTOR(indirect_adaptor, F);

    template<class... Ts>
    constexpr const F& base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    struct failure
    : failure_for<decltype(*std::declval<F>())>
    {};

    BOOST_HOF_RETURNS_CLASS(indirect_adaptor);

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(decltype(*std::declval<F>()), id_<Ts>...) 
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        (*BOOST_HOF_MANGLE_CAST(const F&)(BOOST_HOF_CONST_THIS->base_function(xs...)))(BOOST_HOF_FORWARD(Ts)(xs)...)
    );
};

template<class F>
struct indirect_adaptor<F*>
{
    typedef indirect_adaptor fit_rewritable1_tag;
    F* f;
    constexpr indirect_adaptor() noexcept
    {}

    constexpr indirect_adaptor(F* x) noexcept
    : f(x)
    {}

    template<class... Ts>
    constexpr F& base_function(Ts&&...) const noexcept
    {
        return *f;
    }

    struct failure
    : failure_for<F>
    {};

    BOOST_HOF_RETURNS_CLASS(indirect_adaptor);

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(F, id_<Ts>...) 
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        (BOOST_HOF_MANGLE_CAST(F&)(BOOST_HOF_CONST_THIS->base_function(xs...)))(BOOST_HOF_FORWARD(Ts)(xs)...)
    );
};

BOOST_HOF_DECLARE_STATIC_VAR(indirect, detail::make<indirect_adaptor>);

}} // namespace boost::hof

#endif

/* indirect.hpp
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
*/