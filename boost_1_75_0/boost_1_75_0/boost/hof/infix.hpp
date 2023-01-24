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
9B5G86s887L02rO8D6GAKNnwPttet3kS6XRYDj5ZMUogUEoECL3w9ppwtFczbn82Qcs+ywA2V/6/kvh8HdU/QPyV6N+8fdgDQuYv0S+8/RCCQ0Yv/IW3R+lVDNX+SyX+PFWVjB6aBW6VXNkbfB7+rUfvUPtQlU8BZGaYveR/McS3x7PHb6Z2lCuTdqX1xTvCJ8XzpuKl4aU+/myb1mh4/hvTXGBqCdWMQ4pFiuw78QuTn94qCSspXoxwbakSOQ/PaUcyXgym7DVfAiBD5PBP5QTDXT9shh5De+5GPggjYj0/kc10NK7XrTvfMvS2Q6Z69z4tuGrdZW72/7W/dujxpSzOPS5vSCkW9KUIki8lNx5zxOVwPzzdJwviI5mJ/SZZOfHLQtald2bb+EGfpcxBh6bk7kPMDZSLlnuDj8bAsdUQkyHh4a9zMQf4laVs/AkkvW/kFAXOoGrEz7LKZw3ji65gsQfXiC/YhX/RGcfCVA+wqt5/xY11uFlWVbrr+bArck6VtIPLJb7TR5NeI2J8xF1VdxqDSVrfuqv19MDEhq+qG2RQpIY7ZleCEucDrRd0X6+VQX27/LULEmloclX1V1dUpbk72G4AlcXgL93CWZJI1/aIxuC+a3rWsZj7WF/eKuwrvr5Db4M+c7Gym8O5Kbucn3w8lp1/HPQu4rL9r/0/P8bWOE8W4kMKnWt0f6pCiOSqhpksqfBn5a01
*/