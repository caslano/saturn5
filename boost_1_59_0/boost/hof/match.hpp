/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    match.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_OVERLOAD_H
#define BOOST_HOF_GUARD_FUNCTION_OVERLOAD_H

/// match
/// =====
/// 
/// Description
/// -----------
/// 
/// The `match` function adaptor combines several functions together and
/// resolves which one should be called by using C++ overload resolution. This
/// is different than the [`first_of`](/include/boost/hof/conditional) adaptor which resolves
/// them based on order.
/// 
/// Synopsis
/// --------
/// 
///     template<class... Fs>
///     constexpr match_adaptor<Fs...> match(Fs...fs);
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
///     using namespace boost::hof;
/// 
///     struct int_class
///     {
///         int operator()(int) const
///         {
///             return 1;
///         }
///     };
/// 
///     struct foo
///     {};
/// 
///     struct foo_class
///     {
///         foo operator()(foo) const
///         {
///             return foo();
///         }
///     };
/// 
///     typedef match_adaptor<int_class, foo_class> fun;
/// 
///     static_assert(std::is_same<int, decltype(fun()(1))>::value, "Failed match");
///     static_assert(std::is_same<foo, decltype(fun()(foo()))>::value, "Failed match");
/// 
///     int main() {}
/// 
/// References
/// ----------
/// 
/// * [POO51](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0051r2.pdf) - Proposal for C++
///   Proposal for C++ generic overload function
/// 

#include <boost/hof/reveal.hpp>
#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {

template<class...Fs> struct match_adaptor;
 
template<class F, class...Fs>
struct match_adaptor<F, Fs...> : detail::callable_base<F>, match_adaptor<Fs...>
{
    typedef match_adaptor<Fs...> base;
    typedef match_adaptor fit_rewritable_tag;

    struct failure
    : failure_for<detail::callable_base<F>, Fs...>
    {};

    BOOST_HOF_INHERIT_DEFAULT(match_adaptor, detail::callable_base<F>, base);

    template<class X, class... Xs, BOOST_HOF_ENABLE_IF_CONVERTIBLE(X, detail::callable_base<F>), BOOST_HOF_ENABLE_IF_CONSTRUCTIBLE(base, Xs...)>
    constexpr match_adaptor(X&& f1, Xs&& ... fs) 
    : detail::callable_base<F>(BOOST_HOF_FORWARD(X)(f1)), base(BOOST_HOF_FORWARD(Xs)(fs)...)
    {}

    using F::operator();
    using base::operator();
};

template<class F>
struct match_adaptor<F> : detail::callable_base<F>
{
    typedef detail::callable_base<F> base;
    typedef match_adaptor fit_rewritable_tag;
    using F::operator();

    BOOST_HOF_INHERIT_CONSTRUCTOR(match_adaptor, detail::callable_base<F>);
};

BOOST_HOF_DECLARE_STATIC_VAR(match, detail::make<match_adaptor>);

}} // namespace boost::hof

#endif

/* match.hpp
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
*/