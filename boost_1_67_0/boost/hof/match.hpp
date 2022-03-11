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