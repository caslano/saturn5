/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    apply_eval.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_APPLY_EVAL_H
#define BOOST_HOF_GUARD_APPLY_EVAL_H

/// apply_eval
/// ==========
/// 
/// Description
/// -----------
/// 
/// The `apply_eval` function work like [`apply`](/include/boost/hof/apply), except it calls
/// [`eval`](/include/boost/hof/eval) on each of its arguments. Each [`eval`](/include/boost/hof/eval) call is
/// always ordered from left-to-right.
/// 
/// Synopsis
/// --------
/// 
///     template<class F, class... Ts>
///     constexpr auto apply_eval(F&& f, Ts&&... xs);
/// 
/// Semantics
/// ---------
/// 
///     assert(apply_eval(f)(xs...) == f(eval(xs)...));
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [ConstInvocable](ConstInvocable)
/// 
/// Ts must be:
/// 
/// * [EvaluatableFunctionObject](EvaluatableFunctionObject)
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     struct sum_f
///     {
///         template<class T, class U>
///         T operator()(T x, U y) const
///         {
///             return x+y;
///         }
///     };
/// 
///     int main() {
///         assert(boost::hof::apply_eval(sum_f(), []{ return 1; }, []{ return 2; }) == 3);
///     }
/// 

#include <boost/hof/config.hpp>
#include <boost/hof/returns.hpp>
#include <boost/hof/detail/forward.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/apply.hpp>
#include <boost/hof/eval.hpp>

#if BOOST_HOF_NO_ORDERED_BRACE_INIT
#include <boost/hof/pack.hpp>
#include <boost/hof/capture.hpp>
#endif

namespace boost { namespace hof {

namespace detail {

#if BOOST_HOF_NO_ORDERED_BRACE_INIT
template<class R, class F, class Pack>
constexpr R eval_ordered(const F& f, Pack&& p)
{
    return p(f);
}

template<class R, class F, class Pack, class T, class... Ts>
constexpr R eval_ordered(const F& f, Pack&& p, T&& x, Ts&&... xs)
{
    return boost::hof::detail::eval_ordered<R>(f, boost::hof::pack_join(BOOST_HOF_FORWARD(Pack)(p), boost::hof::pack_forward(boost::hof::eval(x))), BOOST_HOF_FORWARD(Ts)(xs)...);
}
#else
template<class R>
struct eval_helper
{
    R result;

    template<class F, class... Ts>
    constexpr eval_helper(const F& f, Ts&&... xs) : result(boost::hof::apply(f, BOOST_HOF_FORWARD(Ts)(xs)...))
    {}
};

template<>
struct eval_helper<void>
{
    int x;
    template<class F, class... Ts>
    constexpr eval_helper(const F& f, Ts&&... xs) : x((boost::hof::apply(f, BOOST_HOF_FORWARD(Ts)(xs)...), 0))
    {}
};
#endif

struct apply_eval_f
{
    template<class F, class... Ts, class R=decltype(
        boost::hof::apply(std::declval<const F&>(), boost::hof::eval(std::declval<Ts>())...)
    ),
    class=typename std::enable_if<(!std::is_void<R>::value)>::type 
    >
    constexpr R operator()(const F& f, Ts&&... xs) const BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT(boost::hof::apply(f, boost::hof::eval(BOOST_HOF_FORWARD(Ts)(xs))...))
    {
        return
#if BOOST_HOF_NO_ORDERED_BRACE_INIT
        boost::hof::detail::eval_ordered<R>
            (f, boost::hof::pack(), BOOST_HOF_FORWARD(Ts)(xs)...);
#else
        boost::hof::detail::eval_helper<R>
            {f, boost::hof::eval(BOOST_HOF_FORWARD(Ts)(xs))...}.result;
#endif
    }

    template<class F, class... Ts, class R=decltype(
        boost::hof::apply(std::declval<const F&>(), boost::hof::eval(std::declval<Ts>())...)
    ),
    class=typename std::enable_if<(std::is_void<R>::value)>::type 
    >
    constexpr typename detail::holder<Ts...>::type 
    operator()(const F& f, Ts&&... xs) const BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT(boost::hof::apply(f, boost::hof::eval(BOOST_HOF_FORWARD(Ts)(xs))...))
    {
        return (typename detail::holder<Ts...>::type)
#if BOOST_HOF_NO_ORDERED_BRACE_INIT
        boost::hof::detail::eval_ordered<R>
            (f, boost::hof::pack(), BOOST_HOF_FORWARD(Ts)(xs)...);
#else
        boost::hof::detail::eval_helper<R>
            {f, boost::hof::eval(BOOST_HOF_FORWARD(Ts)(xs))...};
#endif
    }
};

}

BOOST_HOF_DECLARE_STATIC_VAR(apply_eval, detail::apply_eval_f);

}} // namespace boost::hof

#endif

/* apply_eval.hpp
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
*/