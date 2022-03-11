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