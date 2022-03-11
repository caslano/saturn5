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