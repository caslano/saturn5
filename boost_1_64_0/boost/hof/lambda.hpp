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
GgxibQsR8pdgBp0xXOFeKFf0L8GVprm4Oa4uZd2vEvgv59j2xNiaDbQ5EgwzE4zRvmmW0KxK2D8sIU0suCy2bpnY+jZPVPTTGO1RM0mLSvLlxCR8UwBTcgauVrnGK+Uz/TE/bcq1+SStzcwlpHKpV7kspWygucZNY5Wum5zNyslrxRJmpfH5Y4mV2i+EJJAjWd8nriKd/Xt9fJD83ygx/R3s3zCG479Wavp3U+nIHBVlvae1oubPVEgOBb5MDJ+imMh5i7xouI6vR6EHD8b8lM2ed8yY90uziNEujgiDIb/wiS9NMnTw0A0F8dAE1RTzMecWnUphdF2pHp3/Qg7XHD0yul589CfOA+OZVDrUopysk9SQmErntFVQWzxBsZe+Q+gRy8tQ0giKGE7vQqgL7acWtZwGvYObkzHmkbGcTHvfHCYV3PK/GUo3bi7KMmT3GjiFdpfZRdeoLto1NHE83WFms5lDb1Wh/wzFn/+mn8Fbra4ktFjP4rOd1ZV8W62aUOWQ0OZGGFDwignArBzosrBk7yLxJ7u6+rXe21m9iLzFA+j3yPqmzmovOXFlqpdYdYT62y1Zycc9KlLryTCocf7rwZj2gMPoA5/4Gs8CV2IOPcnPelPcq1Lc2nHkVRtT3ItS3I7U8uIo+vzMBPzZk7xs4XHOX0qOI+9bmeJemeJekeJeliTv29TVDSSfGL44Vd74hOWHpbs8xT0vxe0+lrxydq2ppCYnsrxJkrC54RlgRnZWZbOMUtU8+cmRnxr58crPCvlZLD/L5Gel/Gjys0p+VstPQH4WyU8jf66l9UH+a1H/MizMfsfBczVYopV6Nd03B5PVE+0PsWGZGlqKXURZYwoROusVrsqLZnVW5Z01zWJ450jvXPLO3d+oYrukt5u83SuCyjtPeueTd/7O85W3R3oXkHcBlSy986V3IXkX7pynYhdI72LyLu6erbwLpXcJeZccWKK8i6V3GXmXVVcpuEukdzl5lzvmWFxiMCYkWMMY6300R29YS7nWaB+Iy3vFM9kKi+dF7aEa1wBtmzbIJZaA6UsaEMVdHJ7NHONhSB09W69yhRpzLUEPHXhPG4t4Yv0ZKhOnVzwFL32BixaLitxaH3BJU2+F+OOqxrSC3ia2126QDMG3BxhnuYGDvNj84/WG/bN+2pcUwmNNx2LqSarVRmpfccQrul1WNGPAcZTGyfNlY4J94pxNarK1evH8yYYQCGkVXmvmu4HF0+j+iyu+FYXlsEKOzTfWRmFLYCZGVzYjcbQdnSXjoCBSAd5PX22PGo7AROwC+iWUFzHLa1TllSaURyDzEKxxhTa4IQcX3oBc4C7n4QL36tyGT6k2p4dforx4dkeSe1tzz/oOaDiPwLhGZB6dVViUEvanrIuhIqezIm/nWpers6LMhVnfkVqeo8PMT66i68CnP1ldtYYyBy8yPQa89o5kN9YAtZ96k+W45L7BK1VHgSHVO80Zg5Jn4RivDzyWfP2KlPKwppjryWPYJB6d36E0+flZWIvfaMPBKYpEUvSNII8VeSnyM2wWwkj/ak5K+mPdP8jtMMt3iAtG9nDg0jaP+f/DEvWd1SCTRXLfv4y13F1h1516vSP08dDgpEjFe6FDmesHX6zPdEQCnokXI0ZBqKtPZPZfo6eTyubzUXwNRDc/ZCGveR2Rir+GDvVZ/7qMXyijZ7Ndr786N9ky9l/s/Dlo3dpWW9mSwNyy0wJVZRMCM0Mf2pzXu20Qfs6EvsTQHtu2Kmtory3UZQtMbJ42MTh+5pyi3ZAvBqk8qnV485HCpqHNR6ZuHlg+cw5kyJpE1AHR18JCJMF3CaI5W57DFKKoS6Bf70OYB33CSjK+XXc=
*/