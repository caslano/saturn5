/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    pipable.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_PIPABLE_H
#define BOOST_HOF_GUARD_FUNCTION_PIPABLE_H

/// pipable
/// =======
/// 
/// Description
/// -----------
/// 
/// The `pipable` function adaptor provides an extension method. The first
/// parameter of the function can be piped into the function using the pipe
/// `|` operator. This can be especially convenient when there are a lot of
/// nested function calls. Functions that are made pipable can still be called
/// the traditional way without piping in the first parameter.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     constexpr pipable_adaptor<F> pipable(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(x | pipable(f)(ys...) == f(x, ys...));
/// 
/// Requirements
/// ------------
/// 
/// F must be:
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
///     struct sum
///     {
///         template<class T, class U>
///         T operator()(T x, U y) const
///         {
///             return x+y;
///         }
///     };
/// 
///     int main() {
///         assert(3 == (1 | pipable(sum())(2)));
///         assert(3 == pipable(sum())(1, 2));
///     }
/// 
/// References
/// ----------
/// 
/// * [Extension methods](<Extension methods>)
/// 

#include <boost/hof/first_of.hpp>
#include <boost/hof/pack.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/limit.hpp>

namespace boost { namespace hof { 
 
template<class F>
struct pipable_adaptor;

namespace detail {

template<class F, class Pack>
struct pipe_closure : F, Pack
{
    
    template<class X, class P>
    constexpr pipe_closure(X&& fp, P&& packp) 
    BOOST_HOF_NOEXCEPT(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(F, X&&) && BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(Pack, P&&))
    : F(BOOST_HOF_FORWARD(X)(fp)), Pack(BOOST_HOF_FORWARD(P)(packp))
    {}

    template<class... Ts>
    constexpr const F& base_function(Ts&&...) const noexcept
    {
        return *this;
    }

    template<class... Ts>
    constexpr const Pack& get_pack(Ts&&...) const noexcept
    {
        return *this;
    }

    template<class A>
    struct invoke
    {
        A a;
        const pipe_closure * self;
        template<class X>
        constexpr invoke(X&& xp, const pipe_closure * selfp) 
        BOOST_HOF_NOEXCEPT(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(A, X&&))
        : a(BOOST_HOF_FORWARD(X)(xp)), self(selfp)
        {}

        BOOST_HOF_RETURNS_CLASS(invoke);

        template<class... Ts>
        constexpr BOOST_HOF_SFINAE_RESULT(const F&, id_<A>, id_<Ts>...) 
        operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
        (BOOST_HOF_RETURNS_STATIC_CAST(const F&)(*BOOST_HOF_CONST_THIS->self)(BOOST_HOF_FORWARD(A)(a), BOOST_HOF_FORWARD(Ts)(xs)...));
    };

    BOOST_HOF_RETURNS_CLASS(pipe_closure);

    template<class A>
    constexpr BOOST_HOF_SFINAE_RESULT(const Pack&, id_<invoke<A&&>>) 
    operator()(A&& a) const BOOST_HOF_SFINAE_RETURNS
    (BOOST_HOF_MANGLE_CAST(const Pack&)(BOOST_HOF_CONST_THIS->get_pack(a))(invoke<A&&>(BOOST_HOF_FORWARD(A)(a), BOOST_HOF_CONST_THIS)));
};

template<class F, class Pack>
constexpr auto make_pipe_closure(F f, Pack&& p) BOOST_HOF_RETURNS
(
    pipe_closure<F, typename std::remove_reference<Pack>::type>(BOOST_HOF_RETURNS_STATIC_CAST(F&&)(f), BOOST_HOF_FORWARD(Pack)(p))
);


template<class Derived, class F>
struct pipe_pack
{
    template<class... Ts>
    constexpr const F& get_function(Ts&&...) const noexcept
    {
        return static_cast<const F&>(static_cast<const Derived&>(*this));
    }

    BOOST_HOF_RETURNS_CLASS(pipe_pack);

    template<class... Ts, class=typename std::enable_if<
        (sizeof...(Ts) < function_param_limit<F>::value)
    >::type>
    constexpr auto operator()(Ts&&... xs) const BOOST_HOF_RETURNS
    (make_pipe_closure(BOOST_HOF_RETURNS_C_CAST(F&&)(BOOST_HOF_CONST_THIS->get_function(xs...)), boost::hof::pack_forward(BOOST_HOF_FORWARD(Ts)(xs)...)));
};
    
template<class A, class F, class Pack>
constexpr auto operator|(A&& a, const pipe_closure<F, Pack>& p) BOOST_HOF_RETURNS
(p(BOOST_HOF_FORWARD(A)(a)));

}

template<class F>
struct pipable_adaptor 
: detail::basic_first_of_adaptor<detail::callable_base<F>, detail::pipe_pack<pipable_adaptor<F>, detail::callable_base<F>> >
{
    typedef detail::basic_first_of_adaptor<detail::callable_base<F>, detail::pipe_pack<pipable_adaptor<F>, detail::callable_base<F>> > base;
    typedef pipable_adaptor fit_rewritable_tag;

    BOOST_HOF_INHERIT_CONSTRUCTOR(pipable_adaptor, base);

    constexpr const detail::callable_base<F>& base_function() const noexcept
    {
        return *this;
    }
};

template<class A, class F>
constexpr auto operator|(A&& a, const pipable_adaptor<F>& p) BOOST_HOF_RETURNS
(p(BOOST_HOF_FORWARD(A)(a)));

BOOST_HOF_DECLARE_STATIC_VAR(pipable, detail::make<pipable_adaptor>);

namespace detail {

template<class F>
struct static_function_wrapper;

// Operators for static_function_wrapper adaptor
template<class A, class F>
auto operator|(A&& a, const boost::hof::detail::static_function_wrapper<F>& f) BOOST_HOF_RETURNS
(f(BOOST_HOF_FORWARD(A)(a)));

template<class F>
struct static_default_function;

// Operators for static_default_function adaptor
template<class A, class F>
auto operator|(A&& a, const boost::hof::detail::static_default_function<F>& f) BOOST_HOF_RETURNS
(f(BOOST_HOF_FORWARD(A)(a)));

}

template<class F>
struct static_;

// Operators for static_ adaptor
template<class A, class F>
auto operator|(A&& a, static_<F> f) BOOST_HOF_RETURNS
(f.base_function().base_function()(BOOST_HOF_FORWARD(A)(a)));

}} // namespace boost::hof

#endif

/* pipable.hpp
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
*/