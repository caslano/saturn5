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
qGZy+riRnsxDFgodVjVIJcURGXGvrMGVRg1kGtQDlbhC1eCIpQZxyTR1khxcI66jBB5GaWmqtjx91X6ftmorWqzan9JW7deyBtcYnHQrkEci4H+1wv+wBf/jCn+GwHXjWnFRS1Q7k8/tHLgez5dV42oyCrpEQVaNq8nBP1bBxzlYseWfZbCsGleTSZ62goh4UNZEM2oyz2yJa+GsHFK1OSRrY5ZISRcylMOqhlwXE0pkCX+k1PUus66pdfxJ+jr+/MQ6MvUVGFkNWSWyR0dkB8TrcLwuk6/+CCDL1ysiaGv5eiXqOPvf7F0LfJPVFU/S0AYoJECBAAWKBixSsdgKhRZsobQFAYOlKQJSdOg+IypCAkULFFOU9DOIj6lzbuJ0m69t6pirzgelG0XnJuoebu7B5mO3Rke3+UBQs/8597tfHqSA7r3f8vt935f7Pvd17rnnnnuOLnEZfG+Rvsuw3O6S8uJNYTSb9F2Bv3fyXzQLypd/Nfy9V/5dFUZLyr/5yIFGPrDGPOdDz7nauwgyj/Oxv8CnDD7u9jft7V1u52PP0YR9mpvuMa7ZLR5aqI02eMQq65RnNhj7GkjgXWqYLocKO8JhxjzJRZEq4DAHGAPQjWLV0ICvgYtdgMnBeT1HMKtWRQSjVctVZjwWeA2hek56kpeDSbu4CZEJZS+r+iwvOS8xcv04jpAeRZVUFVCxtPCruqkqAKTylGrkpq1GTrwaCFRtmVwTl9EhiKNGFQJtMrAyfTWL9k5q4iWDqmaCjKphiNOOWS0XR7iGFldCR+Ql1qIyoRaqlmkr4k7qj/Kj+yMnXgujmsmVUTV1m6MsZUjVpK8pl/kials8KeDxcnUV/NyTR+KI7dFYYofkoSBZyZqUuuQmdgq3Qkpd3KouqrKpFck5VkVcaeYGuNI9jFesLqjYYpRm9qabETfqdjiO5h79xKwBQCowuiqpU2qO7pRcVZF4TR9RK4+qKVfEjFCCanAENYANsB9Ry5usIgpVAeYiapQi6ybriZqtoK7QA1zTZQzvn9xIDXQjoS5gfMN1fIzKTKyBqmVib9Qc3Ru5qZUoS+kRd9oeyekJVbnSoirOPbX/PFQj1FJDXlRRVHKlRKolBDUjVZdCqpz9rVSxxPXfrCTGCNVCjZVk4oGrmUppcN1ULRLoGVU9VQtFJpjVUw2i6A0ZME/5JnSgXHhopBIaRvVW0cG3Me5kA7yAYl5CYTQdXzCIBsTBdOT1GfXlFlS1pmaiypYYlS1JrCyPcNUkBpaSGD0st2xU+4T2z02pPfYaqllU7XmTB12GtO+TLYGdimoi1RLIXUgumpe2imgYjmcQYvtl+W/LGIvMfAvg2S09F6PVOAkPj5f1O3n9KXoPMagq+k8QZ5lu7iFLYIMWQYdk4hW0f4XzI+lcCdLHhQX7p+T8BW1zEWaxcpiGsHKEvUJhLyPMgzC7DFuFsByE/Vou9IW0bUaog0JbJAFh1AWIAPGMfW8+K/tRO1zm2cK15ZOaPAz662FJIAa4mcf4ELMHQg/xZr9c94miF/UFb09yFWFQTaqx615HUZ1Fr8ku+kXRfHvoh+VhePwoXJOt+w4VeV36go+KanKKaN91PS9SYa8rXJMDvoDXDZtMRTW5CCsuItLI66YTS5+jyJunL8guqvEgZFERkUdeHGJ6dJ+ryJuvL8gpqilAyDKErFB8BW9+qLM8XFOg+9xF3kJ9QW5RTTHirCwi0shbGK4p1n3I1BPaW17kLSmqKUPgKgC0i2vGuiCtYW9JuKZMsTpkrcOyDZxbXQdjLPsJFsx/gqqd///+//v/73/s1/YQ6z96MJGffJ/EzW18SgKFwoyx6p/ZSSe7FOacfYg=
*/