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