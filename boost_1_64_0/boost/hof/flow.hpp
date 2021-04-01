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
b4RI5H+fwOgiwy1GyR7RMlm6jmCIbPM+TH/UAIJePAyK1y9Vd/WJ4Y43zkzIUiw7QcCyIKJS4c+rBlgpXl5OCc3vYKWOzX7in4sW4uktQwwatMBW/7To1lI97dHGYLyAgVyC9Hd1Rl7XJcETX8RsJXQA+I0z7jhZDeaBFYgVYt7kqw5HhzBR33MEXKfQg9oRuVzFGScd6KuUOt81r6+bW/WKN1JOsIUV4FgyZBW267QiYQPiC9+D0+qiEuZLcD+WKkINqNsI/dKLSBTn7ZcXet5Dzq4Npbem/2Wx7BFkLC2hz7sYoc1lSrC8w3Uxsy7pUNXJXRFoPoUbZA3iFHjtlj2nP7sUv7stAWlwxMMJ82l3zx1yXWKCr7GGIDGRf3p4igg7khZg16AD5wBPR3ezaT6si/5ADpML5Dg8YNstza/mXqGV8ksPUtvbHliquz3vlkyFK0cIVh0H5iaSEzbM415+MeyfXnA8GlPiV74hpSXrtG/m9DGwG5pnYTGD1Bt6p11uL95D9ZFMlbUDVHmSXHrR+Lph0Z0KkUBPrUHS2ILAoBx/xoYa4Dyj4Q==
*/