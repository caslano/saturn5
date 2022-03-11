/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    infix.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_INFIX_H
#define BOOST_HOF_GUARD_FUNCTION_INFIX_H

/// infix
/// =====
/// 
/// Description
/// -----------
/// 
/// The `infix` function adaptor allows the function to be used as an infix
/// operator. The operator must be placed inside the angle brackets(ie `<`
/// and `>`).
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     constexpr infix_adaptor<F> infix(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(x <infix(f)> y == f(x, y));
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [BinaryInvocable](BinaryInvocable)
/// * MoveConstructible
/// 
/// Operator precedence
/// -------------------
/// 
/// Infix operators have the precedence of relational operators. This means
/// operators such as `+` or `*` have higher precedence:
/// 
///     assert((x + y <infix(f)> z) == ((x + y) <infix(f)> z));
///     assert((x * y <infix(f)> z) == ((x * y) <infix(f)> z));
/// 
/// However, operators such as `|` or `==` have lower precedence::
/// 
///     assert((x | y <infix(f)> z) == (x | (y <infix(f)> z)));
///     assert((x == y <infix(f)> z) == (x == (y <infix(f)> z)));
/// 
/// Also, infix operators have left-to-right associativity:
/// 
///     assert(x <infix(f)> y <infix(g)> z == ((x <infix(f)> y) <infix(g)> z));
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     using namespace boost::hof;
/// 
///     struct plus_f
///     {
///         template<class T, class U>
///         T operator()(T x, U y) const
///         {
///             return x+y;
///         }
///     };
///     
///     int main() {
///         constexpr infix_adaptor<plus_f> plus = {};
///         int r = 3 <plus> 2;
///         assert(r == 5);
///     }
/// 

#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/always.hpp>
#include <boost/hof/reveal.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {
 
namespace detail{
template<class T, class F>
struct postfix_adaptor : F
{
    T x;

    template<class X, class XF>
    constexpr postfix_adaptor(X&& xp, XF&& fp)
    BOOST_HOF_NOEXCEPT(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(F, XF&&) && BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(T, X&&)) 
    : F(BOOST_HOF_FORWARD(XF)(fp)), x(BOOST_HOF_FORWARD(X)(xp))
    {}

    template<class... Ts>
    constexpr const F& base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    BOOST_HOF_RETURNS_CLASS(postfix_adaptor);

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(const F&, id_<T&&>, id_<Ts>...)
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        (BOOST_HOF_MANGLE_CAST(const F&)(BOOST_HOF_CONST_THIS->base_function(xs...)))(BOOST_HOF_RETURNS_C_CAST(T&&)(BOOST_HOF_CONST_THIS->x), BOOST_HOF_FORWARD(Ts)(xs)...)
    );

    template<class A>
    constexpr BOOST_HOF_SFINAE_RESULT(const F&, id_<T&&>, id_<A>)
    operator>(A&& a) const BOOST_HOF_SFINAE_RETURNS
    (
        (BOOST_HOF_MANGLE_CAST(const F&)(BOOST_HOF_CONST_THIS->base_function(a)))(BOOST_HOF_RETURNS_C_CAST(T&&)(BOOST_HOF_CONST_THIS->x), BOOST_HOF_FORWARD(A)(a))
    );
};

template<class T, class F>
constexpr postfix_adaptor<T, F> make_postfix_adaptor(T&& x, F f)
BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(postfix_adaptor<T, F>, T&&, F&&)
{
    return postfix_adaptor<T, F>(BOOST_HOF_FORWARD(T)(x), static_cast<F&&>(f));
}
}

template<class F>
struct infix_adaptor : detail::callable_base<F>
{
    typedef infix_adaptor fit_rewritable1_tag;
    BOOST_HOF_INHERIT_CONSTRUCTOR(infix_adaptor, detail::callable_base<F>);

    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    template<class... Ts>
    constexpr const detail::callable_base<F>& infix_base_function(Ts&&... xs) const noexcept
    {
        return boost::hof::always_ref(*this)(xs...);
    }

    BOOST_HOF_RETURNS_CLASS(infix_adaptor);

    template<class... Ts>
    constexpr auto operator()(Ts&&... xs) const BOOST_HOF_RETURNS
    (
        (BOOST_HOF_MANGLE_CAST(const detail::callable_base<F>&)(BOOST_HOF_CONST_THIS->base_function(xs...)))(BOOST_HOF_FORWARD(Ts)(xs)...)
    );
};

template<class T, class F>
constexpr auto operator<(T&& x, const infix_adaptor<F>& i) BOOST_HOF_RETURNS
(detail::make_postfix_adaptor(BOOST_HOF_FORWARD(T)(x), boost::hof::move(i.base_function(x))));

// TODO: Operators for static_

namespace detail {

template<class F>
struct static_function_wrapper;

// Operators for static_function_wrapper adaptor
template<class T, class F>
auto operator<(T&& x, const boost::hof::detail::static_function_wrapper<F>& f) BOOST_HOF_RETURNS
(
    detail::make_postfix_adaptor(BOOST_HOF_FORWARD(T)(x), boost::hof::move(f.base_function().infix_base_function()))
);

template<class F>
struct static_default_function;

// Operators for static_default_function adaptor
template<class T, class F>
auto operator<(T&& x, const boost::hof::detail::static_default_function<F>&) BOOST_HOF_RETURNS
(
    detail::make_postfix_adaptor(BOOST_HOF_FORWARD(T)(x), boost::hof::move(F().infix_base_function()))
);
}
// This overload is needed for gcc
template<class T, class F>
constexpr auto operator<(T&& x, const boost::hof::reveal_adaptor<F>& f) BOOST_HOF_RETURNS
(
    detail::make_postfix_adaptor(BOOST_HOF_FORWARD(T)(x), f.infix_base_function())
);

BOOST_HOF_DECLARE_STATIC_VAR(infix, detail::make<infix_adaptor>);

}} // namespace boost::hof

#endif

/* infix.hpp
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
*/