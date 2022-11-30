/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    partial.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_PARTIAL_H
#define BOOST_HOF_GUARD_FUNCTION_PARTIAL_H

/// partial
/// ========
/// 
/// Description
/// -----------
/// 
/// The `partial` function adaptor allows partial application of the function.
/// If the function can not be called with all the parameters, it will return
/// another function. It will repeatedly do this until the function can
/// finally be called. By default, `partial` captures all of its variables by
/// value, just like bind. As such all parameters must be `MoveConstructible`
/// when the function is aprtial application. `std::ref` can be used to
/// capture references instead.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     constexpr partial_adaptor<F> partial(F f);
/// 
/// Semantics
/// ---------
/// 
///     assert(partial(f)(xs...)(ys...) == f(xs..., ys...));
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
///         assert(3 == partial(sum())(1)(2));
///     }
/// 
/// References
/// ----------
/// 
/// * [Partial application](https://en.wikipedia.org/wiki/Partial_application)
/// * [Currying](https://en.wikipedia.org/wiki/Currying)
/// 

#include <boost/hof/first_of.hpp>
#include <boost/hof/static.hpp>
#include <boost/hof/pipable.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>


namespace boost { namespace hof { 

// TODO: Get rid of sequence parameter
// Forward declare partial_adaptor, since it will be used below
template<class F, class Pack=void >
struct partial_adaptor;

BOOST_HOF_DECLARE_STATIC_VAR(partial, detail::make<partial_adaptor>);

namespace detail {

template<class Derived, class F, class Pack>
struct partial_adaptor_invoke
{
    template<class... Ts>
    constexpr const F& get_function(Ts&&...) const noexcept
    {
        return static_cast<const F&>(static_cast<const Derived&>(*this));
    }

    template<class... Ts>
    constexpr const Pack& get_pack(Ts&&...) const noexcept
    {
        return static_cast<const Pack&>(static_cast<const Derived&>(*this));
    }

    BOOST_HOF_RETURNS_CLASS(partial_adaptor_invoke);

    template<class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT
    (
        typename result_of<decltype(boost::hof::pack_join), 
            id_<const Pack&>, 
            result_of<decltype(boost::hof::pack_forward), id_<Ts>...> 
        >::type,
        id_<F&&>
    ) 
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        boost::hof::pack_join
        (
            BOOST_HOF_MANGLE_CAST(const Pack&)(BOOST_HOF_CONST_THIS->get_pack(xs...)), 
            boost::hof::pack_forward(BOOST_HOF_FORWARD(Ts)(xs)...)
        )
        (BOOST_HOF_RETURNS_C_CAST(F&&)(BOOST_HOF_CONST_THIS->get_function(xs...)))
    );
};

#ifdef _MSC_VER
#define BOOST_HOF_PARTIAL_RETURNS(...) -> decltype(__VA_ARGS__) { return (__VA_ARGS__); }
#else
#define BOOST_HOF_PARTIAL_RETURNS BOOST_HOF_SFINAE_RETURNS
#endif

template<class Derived, class F, class Pack>
struct partial_adaptor_join
{
    template<class... Ts>
    constexpr const F& get_function(Ts&&...) const noexcept
    {
        return static_cast<const F&>(static_cast<const Derived&>(*this));
    }

    template<class... Ts>
    constexpr const Pack& get_pack(Ts&&...) const noexcept
    {
        return static_cast<const Pack&>(static_cast<const Derived&>(*this));
    }

    BOOST_HOF_RETURNS_CLASS(partial_adaptor_join);

    template<class... Ts, class=typename std::enable_if<
        ((sizeof...(Ts) + Pack::fit_function_param_limit::value) < function_param_limit<F>::value)
    >::type>
    constexpr auto operator()(Ts&&... xs) const 
#ifdef _MSC_VER
    // Workaround ICE on MSVC
    noexcept(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(F, F&&) && noexcept(boost::hof::pack_join(std::declval<const Pack&>(), boost::hof::pack(BOOST_HOF_FORWARD(Ts)(xs)...))))
#endif
    BOOST_HOF_PARTIAL_RETURNS
    (
        boost::hof::partial
        (
            BOOST_HOF_RETURNS_C_CAST(F&&)(BOOST_HOF_CONST_THIS->get_function(xs...)), 
            boost::hof::pack_join(BOOST_HOF_MANGLE_CAST(const Pack&)(BOOST_HOF_CONST_THIS->get_pack(xs...)), boost::hof::pack(BOOST_HOF_FORWARD(Ts)(xs)...))
        )
    );
};

template<class Derived, class F>
struct partial_adaptor_pack
{

    constexpr partial_adaptor_pack() noexcept
    {}
    
    template<class... Ts>
    constexpr const F& get_function(Ts&&...) const noexcept
    {
        return static_cast<const F&>(static_cast<const Derived&>(*this));
    }

    BOOST_HOF_RETURNS_CLASS(partial_adaptor_pack);

    template<class... Ts, class=typename std::enable_if<
        (sizeof...(Ts) < function_param_limit<F>::value)
    >::type>
    constexpr auto operator()(Ts&&... xs) const 
#ifdef _MSC_VER
    // Workaround ICE on MSVC
    noexcept(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(F, F&&) && noexcept(boost::hof::pack(BOOST_HOF_FORWARD(Ts)(xs)...)))
#endif
    BOOST_HOF_PARTIAL_RETURNS
    (
        boost::hof::partial
        (
            BOOST_HOF_RETURNS_C_CAST(F&&)(BOOST_HOF_CONST_THIS->get_function(xs...)), 
            boost::hof::pack(BOOST_HOF_FORWARD(Ts)(xs)...)
        )
    );
};
template<class F, class Pack>
struct partial_adaptor_base 
{
    typedef basic_first_of_adaptor
    <
        partial_adaptor_invoke<partial_adaptor<F, Pack>, F, Pack>,
        partial_adaptor_join<partial_adaptor<F, Pack>, F, Pack> 
    > type;
};

template<class Derived, class F>
struct partial_adaptor_pack_base
{
    typedef basic_first_of_adaptor
    <
        F,
        partial_adaptor_pack<Derived, F> 
    > type;
};

}

template<class F, class Pack>
struct partial_adaptor : detail::partial_adaptor_base<F, Pack>::type, F, Pack
{
    typedef typename detail::partial_adaptor_base<F, Pack>::type base;

    typedef partial_adaptor fit_rewritable1_tag;
    
    template<class... Ts>
    constexpr const F& base_function(Ts&&...) const noexcept
    {
        return *this;
    }

    constexpr const Pack& get_pack() const noexcept
    {
        return *this;
    }

    using base::operator();

    BOOST_HOF_INHERIT_DEFAULT(partial_adaptor, base, F, Pack);

    template<class X, class S>
    constexpr partial_adaptor(X&& x, S&& seq) 
    BOOST_HOF_NOEXCEPT(BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(F, X&&) && BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(Pack, S&&))
    : F(BOOST_HOF_FORWARD(X)(x)), Pack(BOOST_HOF_FORWARD(S)(seq))
    {}
};

template<class F>
struct partial_adaptor<F, void> : detail::partial_adaptor_pack_base<partial_adaptor<F, void>, detail::callable_base<F>>::type
{
    typedef typename detail::partial_adaptor_pack_base<partial_adaptor<F, void>, detail::callable_base<F>>::type base;

    typedef partial_adaptor fit_rewritable1_tag;
    
    template<class... Ts>
    constexpr const detail::callable_base<F>& base_function(Ts&&...) const noexcept
    {
        return *this;
    }

    using base::operator();

    BOOST_HOF_INHERIT_CONSTRUCTOR(partial_adaptor, base);

};

// Make partial_adaptor work with pipable_adaptor by removing its pipableness
template<class F>
struct partial_adaptor<pipable_adaptor<F>, void>
: partial_adaptor<F, void>
{
    typedef partial_adaptor<F, void> base;

    typedef partial_adaptor fit_rewritable1_tag;
    BOOST_HOF_INHERIT_CONSTRUCTOR(partial_adaptor, base);
};

template<class F>
struct partial_adaptor<static_<pipable_adaptor<F>>, void>
: partial_adaptor<F, void>
{
    typedef partial_adaptor<F, void> base;

    typedef partial_adaptor fit_rewritable1_tag;

    BOOST_HOF_INHERIT_CONSTRUCTOR(partial_adaptor, base);
};
}} // namespace boost::hof

#endif

/* partial.hpp
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
*/