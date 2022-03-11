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