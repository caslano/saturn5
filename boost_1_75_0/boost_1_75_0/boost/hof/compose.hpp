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
VlzGjp4yduDXcjbNQEnzmTCvUNv3ra1HO4pz8sLS28Iz/G5zhMcMFW3LCviH8tqF9G1YIkPEsUxZ07nHnLYfd9iFxD72ijakwIVx8Xoi+D4CIm44kHo5EAgpJ4AENdtvhNG1tzs44C/+fCgiE0WkCANt+fyOInhEFz7sgGueZoO9E41BnSLcpgVz+eO/IBiGAyX0oXZgfTAKhAwiAkH0f/uC3okIewMoQIbhnfdMbgO30y5RIOWH5CVgdUMJyCMK7lXEMFjS5bA1VrL558VL7G0U4DMQ/JYognfI2/XTQHJZLH0Al2hOmstQosshMhFAlH13Xtui3ffb6zJNZjezwQsJ0uG7kxaLGXVZ9Sud5ChGJS4eAh9v+QG8u7EIYMftIHt9xo5GY52WLsBeY4Ex68fZCN09nr0Jj3fo1FYeJyaUMpebtyDeXgOzy9CC1P9U1H76hyNtmTDAnWneGa6aKS0l4g/9wpcHZux9rekN0+LSLcToaKFq/y+nSvslTPc37iC888/nZC5iGyWplUA8lVth0sXnF2ObS+XLtyF+Y94TDQkXYiiUD88Rs9ttBYnOq73FNyVSm5tTrVOd6eywwOCxMwOr25apyR4jvalm9qSg4ZsLGbA4JQyTuUFkiaBBovgK0PuYfPGHGIfRS3zIpXgLBNZeJHJZj+z/5+vfvN8sxwE/BIM9JS+NyvajGnSu2ZlDYC7vA2UujTYb
*/