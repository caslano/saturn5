/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    compose.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_COMPOSE_H
#define BOOST_HOF_GUARD_FUNCTION_COMPOSE_H

/// compose
/// =======
/// 
/// Description
/// -----------
/// 
/// The `compose` function adaptor provides function composition. It produces
/// a function object that composes a set of functions, ie the output of one
/// function becomes the input of the second function. So, `compose(f, g)(0)`
/// is equivalent to `f(g(0))`.
/// 
/// 
/// Synopsis
/// --------
/// 
///     template<class... Fs>
///     constexpr compose_adaptor<Fs...> compose(Fs... fs);
/// 
/// Semantics
/// ---------
/// 
///     assert(compose(f, g)(xs...) == f(g(xs...)));
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
///         int r = compose(increment(), decrement(), increment())(3);
///         assert(r == 4);
///     }
/// 
/// References
/// ----------
/// 
/// * [Function composition](https://en.wikipedia.org/wiki/Function_composition)
/// 
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
struct compose_kernel : detail::compressed_pair<F1, F2>, compose_function_result_type<F1, F2>
{
    typedef detail::compressed_pair<F1, F2> base_type;

    BOOST_HOF_INHERIT_CONSTRUCTOR(compose_kernel, base_type)

    BOOST_HOF_RETURNS_CLASS(compose_kernel);

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(const F1&, result_of<const F2&, id_<Ts>...>) 
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        BOOST_HOF_MANGLE_CAST(const F1&)(BOOST_HOF_CONST_THIS->first(xs...))(
            BOOST_HOF_MANGLE_CAST(const F2&)(BOOST_HOF_CONST_THIS->second(xs...))(BOOST_HOF_FORWARD(Ts)(xs)...)
        )
    );
};
}

template<class F, class... Fs>
struct compose_adaptor 
: detail::compose_kernel<detail::callable_base<F>, BOOST_HOF_JOIN(compose_adaptor, detail::callable_base<Fs>...)>
{
    typedef compose_adaptor fit_rewritable_tag;
    typedef BOOST_HOF_JOIN(compose_adaptor, detail::callable_base<Fs>...) tail;
    typedef detail::compose_kernel<detail::callable_base<F>, tail> base_type;

    BOOST_HOF_INHERIT_DEFAULT(compose_adaptor, base_type)

    template<class X, class... Xs, 
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(detail::callable_base<F>, X), 
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(tail, Xs...)
    >
    constexpr compose_adaptor(X&& f1, Xs&& ... fs)
    BOOST_HOF_NOEXCEPT(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(base_type, X&&, tail) && BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(tail, Xs&&...))
    : base_type(BOOST_HOF_FORWARD(X)(f1), tail(BOOST_HOF_FORWARD(Xs)(fs)...))
    {}

    template<class X,
        BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(detail::callable_base<F>, X)
    >
    constexpr compose_adaptor(X&& f1) 
    BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(base_type, X&&)
    : base_type(BOOST_HOF_FORWARD(X)(f1))
    {}
};

template<class F>
struct compose_adaptor<F> : detail::callable_base<F>
{
    typedef compose_adaptor fit_rewritable_tag;

    BOOST_HOF_INHERIT_DEFAULT(compose_adaptor, detail::callable_base<F>)

    template<class X, BOOST_HOF_ENABLE_IF_CONVERTIBLE(X, detail::callable_base<F>)>
    constexpr compose_adaptor(X&& f1) 
    BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(detail::callable_base<F>, X&&)
    : detail::callable_base<F>(BOOST_HOF_FORWARD(X)(f1))
    {}

};

template<class F1, class F2>
struct compose_adaptor<F1, F2>
: detail::compose_kernel<detail::callable_base<F1>, detail::callable_base<F2>>
{
    typedef compose_adaptor fit_rewritable_tag;
    typedef detail::compose_kernel<detail::callable_base<F1>, detail::callable_base<F2>> base_type;

    BOOST_HOF_INHERIT_CONSTRUCTOR(compose_adaptor, base_type)
};

BOOST_HOF_DECLARE_STATIC_VAR(compose, detail::make<compose_adaptor>);

}} // namespace boost::hof

#endif

/* compose.hpp
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
*/