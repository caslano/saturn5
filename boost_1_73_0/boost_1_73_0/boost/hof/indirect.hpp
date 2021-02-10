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
rQ/79cOqpIcVYH90j3YZTUkE+XOiR1r8b6m7ZzjdpeW+XeoR+4C4OXeM8ocePdJanoXUdhdYPW+khN/j1IHqYiYWZ0DN+Ld1aek4gkfv7Biy5gPaH3sAU9coCmzqJBH9nZRX8+N5GS088zEvo0s6lMXwjkX2TwURxSAe8YmfnhzEGT9xPScjcRdq3ajTBOTfpMcELzpwEsqhIfUdqVfKTz+4MVZiNZbYNkrC6gIxwMO/lA+WhKWdhRiPyn4TqMcoHGGtsKHAZjfnHTzhZ3SNd2Q0+Am++gqL/DiJfGgVaGQXBx9/+qQeH20+5tyHQZxTlgFlrLz1o/SyiR/4rk0891c6C0m8BP5RUHwsuYp0jqABwp5nVIfQnrPAS2JaGBoEoPMGma7jaX0VBj71eZtqZ8pNm6BdeXNNqfUco6JRhe/BcOiN4Seel1FieeYLTzyRtHlDiJtePlDdquLjhZv3ysYn2S1uNav9usfB8LZAj79w/2k50wKV6ogO0sfROhtVPS9BLjA4XAFHXaop1tlshqlLT9tchQ5X9ih9hsWMstE4tRGP0gbmGL2BIXqbT10lkP9sKEgBxqUydkW+B6CxX1zRmFM/ZINO/dprJGovA9CMUv2mdcw/2ob/8m7ZbBU4iUdBfs1ES44FSWSn
*/