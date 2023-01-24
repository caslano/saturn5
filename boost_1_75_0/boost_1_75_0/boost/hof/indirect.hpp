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
O3Fqw9Q+j9R6s/ICbAMmbkuRAXcEODylXAhjzmY4IC6h7EnC5/7jWKnIxuaFS4MjavZYjCO20pZptN/9fPpQVqGvqIsgiACk8qoLy0IMhN57x4m8JeqvcI0LeLWJpk/1/D51BriZEJyIekh8IQ8a1i023Sm6jsZSAA2HMSLQbgAMMEQ8JbKZfXCoL+QWkQ1/We2p0FaHIiT+HuxBqG1toX8P9pz/N3jPLfRfwXtSdEcjuZuJFoHm7Q+qW3viwTlzCqQiFzXkIjUeiwFes4NRZB2qMx8FIbfxz7M3cOs7l3cMBF0FKBh8CoqaONbWCaSfCokIRunymTWEkOW/4lEhv9VNECSN+0pVXDwWwHPls5B9U1/yhpnr5x3ig8t6wMu/eUBDA6IDon99hSvxIttISL79hN+ZxRwipO+k/EaN8CtJIdyeOdU9SxOhVlt5rYaMsuAUZSRH/MLbK+Ep4o/i7dGk0I5LZ8TXvTIv+Dtvr5CqB2IrPUEcAkTI37xrQGFGpvp+RoK13/6dafYladyJLg30EV75Pl4VimTEVsJv5ScotyXMBuZARo1t+e/ecobqb3feFRCU/rWQxKW+u9vdCgOeLZm54fGFxoNBKp1mtLqg5fjEZeXUCWsicHLJjoIx5hb5JDHzcgFPy/X+zKltc+UQQM/pAEcBI1RDow9hZ2sB9Hi3wPUrJsSt/kG+BdGTAJUodHQT4s5W5+b9
*/