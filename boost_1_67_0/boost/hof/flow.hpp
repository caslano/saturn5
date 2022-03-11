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