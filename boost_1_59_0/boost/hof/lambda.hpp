/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    lambda.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_LAMBDA_H
#define BOOST_HOF_GUARD_FUNCTION_LAMBDA_H

/// BOOST_HOF_STATIC_LAMBDA
/// =================
/// 
/// Description
/// -----------
/// 
/// The `BOOST_HOF_STATIC_LAMBDA` macro allows initializing non-capturing lambdas at
/// compile-time in a `constexpr` expression.
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     const constexpr auto add_one = BOOST_HOF_STATIC_LAMBDA(int x)
///     {
///         return x + 1;
///     };
/// 
///     int main() {
///         assert(3 == add_one(2));
///     }
/// 
/// BOOST_HOF_STATIC_LAMBDA_FUNCTION
/// ==========================
/// 
/// Description
/// -----------
/// 
/// The `BOOST_HOF_STATIC_LAMBDA_FUNCTION` macro allows initializing a global
/// function object that contains non-capturing lambdas. It also ensures that
/// the global function object has a unique address across translation units.
/// This helps prevent possible ODR-violations.
///
/// By default, all functions defined with `BOOST_HOF_STATIC_LAMBDA_FUNCTION` use
/// the `boost::hof::reveal` adaptor to improve error messages.
/// 
/// Note: due to compiler limitations, a global function declared with
/// `BOOST_HOF_STATIC_LAMBDA_FUNCTION` is not guaranteed to have a unique 
/// address across translation units when compiled with pre-C++17 MSVC.
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     BOOST_HOF_STATIC_LAMBDA_FUNCTION(add_one) = [](int x)
///     {
///         return x + 1;
///     };
///     int main() {
///         assert(3 == add_one(2));
///     }
/// 

#include <boost/hof/config.hpp>

// TODO: Move this to a detail header
#if !BOOST_HOF_HAS_CONSTEXPR_LAMBDA || !BOOST_HOF_HAS_INLINE_LAMBDAS

#include <type_traits>
#include <utility>
#include <boost/hof/detail/result_of.hpp>
#include <boost/hof/reveal.hpp>
#include <boost/hof/detail/constexpr_deduce.hpp>
#include <boost/hof/function.hpp>


#ifndef BOOST_HOF_REWRITE_STATIC_LAMBDA
#ifdef _MSC_VER
#define BOOST_HOF_REWRITE_STATIC_LAMBDA 1
#else
#define BOOST_HOF_REWRITE_STATIC_LAMBDA 0
#endif
#endif

namespace boost { namespace hof {

namespace detail {

template<class F>
struct static_function_wrapper
{
    // Default constructor necessary for MSVC
    constexpr static_function_wrapper()
    {}

    static_assert(BOOST_HOF_IS_EMPTY(F), "Function or lambda expression must be empty");

    struct failure
    : failure_for<F>
    {};

    template<class... Ts>
    const F& base_function(Ts&&...) const
    {
        return reinterpret_cast<const F&>(*this);
    }

    BOOST_HOF_RETURNS_CLASS(static_function_wrapper);

    template<class... Ts>
    BOOST_HOF_SFINAE_RESULT(const F&, id_<Ts>...) 
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        BOOST_HOF_RETURNS_REINTERPRET_CAST(const F&)(*BOOST_HOF_CONST_THIS)(BOOST_HOF_FORWARD(Ts)(xs)...)
    );
};

struct static_function_wrapper_factor
{
    constexpr static_function_wrapper_factor()
    {}
    template<class F>
    constexpr static_function_wrapper<F> operator= (const F&) const
    {
        // static_assert(std::is_literal_type<static_function_wrapper<F>>::value, "Function wrapper not a literal type");
        return {};
    }
};

#if BOOST_HOF_REWRITE_STATIC_LAMBDA
template<class T, class=void>
struct is_rewritable
: std::false_type
{};

template<class T>
struct is_rewritable<T, typename detail::holder<
    typename T::fit_rewritable_tag
>::type>
: std::is_same<typename T::fit_rewritable_tag, T>
{};

template<class T, class=void>
struct is_rewritable1
: std::false_type
{};

template<class T>
struct is_rewritable1<T, typename detail::holder<
    typename T::fit_rewritable1_tag
>::type>
: std::is_same<typename T::fit_rewritable1_tag, T>
{};


template<class T, class=void>
struct rewrite_lambda;

template<template<class...> class Adaptor, class... Ts>
struct rewrite_lambda<Adaptor<Ts...>, typename std::enable_if<
    is_rewritable<Adaptor<Ts...>>::value
>::type>
{
    typedef Adaptor<typename rewrite_lambda<Ts>::type...> type;
};

template<template<class...> class Adaptor, class T, class... Ts>
struct rewrite_lambda<Adaptor<T, Ts...>, typename std::enable_if<
    is_rewritable1<Adaptor<T, Ts...>>::value
>::type>
{
    typedef Adaptor<typename rewrite_lambda<T>::type, Ts...> type;
};

template<class T>
struct rewrite_lambda<T, typename std::enable_if<
    std::is_empty<T>::value && 
    !is_rewritable<T>::value && 
    !is_rewritable1<T>::value
>::type>
{
    typedef static_function_wrapper<T> type;
};

template<class T>
struct rewrite_lambda<T, typename std::enable_if<
    !std::is_empty<T>::value && 
    !is_rewritable<T>::value && 
    !is_rewritable1<T>::value
>::type>
{
    typedef T type;
};

#endif

template<class T>
struct reveal_static_lambda_function_wrapper_factor
{
    constexpr reveal_static_lambda_function_wrapper_factor()
    {}
#if BOOST_HOF_REWRITE_STATIC_LAMBDA
    template<class F>
    constexpr reveal_adaptor<typename rewrite_lambda<F>::type> 
    operator=(const F&) const
    {
        return reveal_adaptor<typename rewrite_lambda<F>::type>();
    }
#elif BOOST_HOF_HAS_CONST_FOLD
    template<class F>
    constexpr const reveal_adaptor<F>& operator=(const F&) const
    {
        return reinterpret_cast<const reveal_adaptor<F>&>(static_const_var<T>());
    }
#else
    template<class F>
    constexpr reveal_adaptor<static_function_wrapper<F>> operator=(const F&) const
    {
        return {};
    }
#endif
};

}}} // namespace boost::hof

#endif

#if BOOST_HOF_HAS_CONSTEXPR_LAMBDA
#define BOOST_HOF_STATIC_LAMBDA []
#else
#define BOOST_HOF_DETAIL_MAKE_STATIC BOOST_HOF_DETAIL_CONSTEXPR_DEDUCE boost::hof::detail::static_function_wrapper_factor()
#define BOOST_HOF_STATIC_LAMBDA BOOST_HOF_DETAIL_MAKE_STATIC = []
#endif

#if BOOST_HOF_HAS_INLINE_LAMBDAS
#define BOOST_HOF_STATIC_LAMBDA_FUNCTION BOOST_HOF_STATIC_FUNCTION
#else
#define BOOST_HOF_DETAIL_MAKE_REVEAL_STATIC(T) BOOST_HOF_DETAIL_CONSTEXPR_DEDUCE_UNIQUE(T) boost::hof::detail::reveal_static_lambda_function_wrapper_factor<T>()
#define BOOST_HOF_STATIC_LAMBDA_FUNCTION(name) \
struct fit_private_static_function_ ## name {}; \
BOOST_HOF_STATIC_AUTO_REF name = BOOST_HOF_DETAIL_MAKE_REVEAL_STATIC(fit_private_static_function_ ## name)
#endif

#endif

/* lambda.hpp
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
*/