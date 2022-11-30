/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    flow.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_FLOW_H
#define BOOST_HOF_GUARD_FUNCTION_FLOW_H

/// flow
/// ====
/// 
/// Description
/// -----------
/// 
/// The `flow` function adaptor provides function composition. It is useful as
/// an alternative to using the pipe operator `|` when chaining functions. It is
/// similiar to [`compose`](compose.md) except the evaluation order is
/// reversed. So, `flow(f, g)(0)` is equivalent to `g(f(0))`.
/// 
/// 
/// Synopsis
/// --------
/// 
///     template<class... Fs>
///     constexpr flow_adaptor<Fs...> flow(Fs... fs);
/// 
/// Semantics
/// ---------
/// 
///     assert(flow(f, g)(xs...) == g(f(xs...)));
/// 
/// Requirements
/// ------------
/// 
/// Fs must be:
/// 
/// * [ConstInvocable](ConstInvocable)
/// * MoveConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     using namespace boost::hof;
/// 
///     struct increment
///     {
///         template<class T>
///         T operator()(T x) const
///         {
///             return x + 1;
///         }
///     };
/// 
///     struct decrement
///     {
///         template<class T>
///         T operator()(T x) const
///         {
///             return x - 1;
///         }
///     };
/// 
///     int main() {
///         int r = flow(increment(), decrement(), increment())(3);
///         assert(r == 4);
///     }
/// 
/// References
/// ----------
/// 
/// * [Function composition](https://en.wikipedia.org/wiki/Function_composition)
/// 

#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/compressed_pair.hpp>
#include <boost/hof/detail/join.hpp>
#include <tuple>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/result_type.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof { namespace detail {

template<class F1, class F2>
struct flow_kernel : detail::compressed_pair<detail::callable_base<F1>, detail::callable_base<F2>>, compose_function_result_type<F2, F1>
{
    typedef detail::compressed_pair<detail::callable_base<F1>, detail::callable_base<F2>> base_type;

    BOOST_HOF_INHERIT_CONSTRUCTOR(flow_kernel, base_type)

    BOOST_HOF_RETURNS_CLASS(flow_kernel);

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(const detail::callable_base<F2>&, result_of<const detail::callable_base<F1>&, id_<Ts>...>) 
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        BOOST_HOF_MANGLE_CAST(const detail::callable_base<F2>&)(BOOST_HOF_CONST_THIS->second(xs...))(
            BOOST_HOF_MANGLE_CAST(const detail::callable_base<F1>&)(BOOST_HOF_CONST_THIS->first(xs...))(BOOST_HOF_FORWARD(Ts)(xs)...)
        )
    );
};
}

template<class F, class... Fs>
struct flow_adaptor : detail::flow_kernel<F, BOOST_HOF_JOIN(flow_adaptor, Fs...)>
{
    typedef flow_adaptor fit_rewritable_tag;
    typedef BOOST_HOF_JOIN(flow_adaptor, Fs...) tail;
    typedef detail::flow_kernel<F, tail> base_type;

    BOOST_HOF_INHERIT_DEFAULT(flow_adaptor, base_type)

    template<class X, class... Xs, 
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(detail::callable_base<F>, X), 
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(tail, Xs...)
    >
    constexpr flow_adaptor(X&& f1, Xs&& ... fs) 
    BOOST_HOF_NOEXCEPT(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(base_type, X&&, tail) && BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(tail, Xs&&...))
    : base_type(BOOST_HOF_FORWARD(X)(f1), tail(BOOST_HOF_FORWARD(Xs)(fs)...))
    {}

    template<class X,
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(detail::callable_base<F>, X)
    >
    constexpr flow_adaptor(X&& f1) 
    BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(base_type, X&&)
    : base_type(BOOST_HOF_FORWARD(X)(f1))
    {}
};

template<class F>
struct flow_adaptor<F> : detail::callable_base<F>
{
    typedef flow_adaptor fit_rewritable_tag;
    BOOST_HOF_INHERIT_DEFAULT(flow_adaptor, detail::callable_base<F>)

    template<class X, BOOST_HOF_ENABLE_IF_CONVERTIBLE(X, detail::callable_base<F>)>
    constexpr flow_adaptor(X&& f1) 
    BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(detail::callable_base<F>, X&&)
    : detail::callable_base<F>(BOOST_HOF_FORWARD(X)(f1))
    {}

};

template<class F1, class F2>
struct flow_adaptor<F1, F2>
: detail::flow_kernel<detail::callable_base<F1>, detail::callable_base<F2>>
{
    typedef flow_adaptor fit_rewritable_tag;
    typedef detail::flow_kernel<detail::callable_base<F1>, detail::callable_base<F2>> base_type;

    BOOST_HOF_INHERIT_CONSTRUCTOR(flow_adaptor, base_type)
};

BOOST_HOF_DECLARE_STATIC_VAR(flow, detail::make<flow_adaptor>);

}} // namespace boost::hof

#endif

/* flow.hpp
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
*/