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
Djp01GbFQebMYnJF0DugMOcfYsP907XnbXXHac+GyqPaszPThvdRbVpbK9v0pqnJbVpzttGmT50Sb9PzEtp0I4o5NCu5TddNP7pNZ5ye0Kbjhsbb9KI42JzZg7P+SW0q6Xvinesbca6+DoORVh6JMEZfvIPkX+oYW5QudgQ24hio1qcQwWvxvd9Ji+J7P194uUOfRbui/ua+z+7PjRaGL3dBvY1DrCpTZHpWAwvPdBxzszodhJ1xHe7TE++GvI9UnYQmJ0XtOHaoxBIiVlSrS68Oi/OGJ/nqWoOjFsuKi1faS+pMgSScKi7z0XkudHM7jLo6TKhdcaiPWZO1RPnQfUrRX2adR0fB+5oeWF4rJoAZo80eYnHRWPkrgiPV5d56v108OQ6J1meLaUDANGZ+sRIRn7MY46NejGIyq+DvESJJ3Z+Up57fZKe4C1LPd451XgR3YYo7L8Vd1pHI3yrvOgAqPjHckxLfneIuTnGXpLhdKe6cJDfRBsHqHs4jtJtUU/vnidKFCRoLr6OAHZkulzgsbw+Eq2jQ13RmMlFShXkS5tEwWVyaR/8JT5zKarvRrRVTFOoYKi6YScE1+N+3s6qSUtMCQzI6s9EQRPD2Gy3V5/bCV3vQYlK9Y4qliuZPL5h+FL8vW8ydlJ4fSCaHYdelI9mdn+LOTXEXprjzUtzo85Ty350Zpzs7ksbDm4DsaHjzZx0LXk9Kee4Ud3GKuyQVHiyp6fNX4csbjlW+KyX/nI7E8VY5vufzscg8jhPaXbmQzk8en2kQIZuJZVO0G/jKbnXelZ7B2PVabor+wtoU/QcLU+QHJye770lJvzkl/SJvinxiSvq3FiS7m1Pym5XifvqcZPe7KW6RUt7pKeVdlVLeC+cmu+9LSX/wzCS3VOXtIuJb76MX6u0TMoOnhrrA3qGXjWahPbbGLjTJWjLdN1Ww+7jTrm2Rlex/VyfKc3il/uplrOz+Tv4S+5eEOlbhP1EgxfQa3kBiLPr1SMBiFtVzSZiCMuyISKmObGSjyeR50WERafg30b+FDUvV8apXK94dTiQIEyCNl+J+wud9tZ1ZrDo/aBVXL1DSXuf4YOxivqESFiw6LIHBUmLSDSIm3RimjrHHqpsK6ihbubaUKzadK5ZVBfl9lV3TI8tRBaqk/sPzG+ige/Mcrsc/Rf9vGwl1iN/NTmzvZots6B0WqTCcW6noHdLVQffM0e7SBC2um4ISO1N8vx81E4JcpKionbQ27aOkYt4gUy/fg/CFHsmnKWCbO8pH1j+2MVE6aes7YO6fb/dP1izFJDzQNJFRvU8rhrM2NnixVKS7t3JUzNL1ABLFpixQapeLXg1j8wXQ3OKteaaQyxhEMvinkKW/7mwDvsJY0CI6R6iFZIBXWIeoq+e5dHaJcFJWTto2HlzKzKB5iEqhkPw520r6gzNmkeQDqjLhl3rJlhg09YMW+h0Nw0b7CF1zQP9051ichDdv6FUT2vdReVAreom1g5PFwmcBLJl3K4TewXyGryRnPKif9tCBjM7KlkIaWxWlLzR16YitI66OuH33orJlFNR3T/Ak/C+hiuNbbHwL6RvNU7HIx2rEML4l9C16tugllJvHpYWaWgotkLGxj59ZlrfGXrZpXUZoTwaVfYCMTETsw/U/h9ptGfvCcG35UFaT7cNxNweG46K8t074B5g9/KyFezjaH0KGHiMuptlee+HpVayNOKMbFN2NNvItzvgrm/jYmzm9CtSTvtgBwOYTvajvMYErgfAsijkQOrR8fa9t/auip+jtF3dmLmtsP2QP/d4ZOgBZ1Oa3saxvq7I5H9si/2VASm1m6S+avqdjdJLao72ZlllhfDEOnp1rCg0=
*/