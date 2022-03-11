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
IzsodUFHe5mcXjB/y7SUu2qxkwlTNr+YLOvF1LstGp+cgWYvho0pI+R5oV3ViPfydct7sJRjLzJXxiajVYIBtuUbENd/M0YWIXGi75m5fPFSj2CX3NUAqX79tHCG7rXYEpCn5cys8p4U+Znq5i7j2W1mA2FtWHkxcBhhwm1TOTzPjJa1ATVuNJAIHfBPB6yOgYX/Ka1UjpKzHngReJifRbbPjEz9q40/4HObvlBdlPl0B9oymvnIIXIbfGrfu0TcuNfO0qr5mJxXJGfz8RGJZZD9YhRJB3u7R6rpZpHChjFbEotznAB5HBdsMEp7yAtCQikY3oUx5m/r8/7r3xm77QXhM6uycIZP+SCKV5Odc4RbzDiC2eqTpfJ5SrDErcbJHXMyAxTqxkhO+XF3/gXiYEQtt7QYCkTnpyRUSTIItvXkeRBhzNcoABWY14YSDjNtwSaT7jJ7FDFJcrwPP8o0Q8ULifAuFgeRnXYwEEesMT/Um3mS2jLdacYhj8LvkZE3V0d/EV82SPEyKnyM2AUgDrkTCmznNBM2ZGHIMuSNEcknETehytPrKtk5jBQ0YyrKVqzglkUrD1uWOEnGE84uGNgY/Zmvxm2LnIoMzc9WwX+mq2UmrLcFqqnIKorgXAP7qov7qQuQJGdTbkiRV8RDpopjMpC+aZACN0VFqKuSFq8zt/1d9o/jVIc/fUH0Csl4Umr0tyLL2hPpkp77xpqTkXwG9TAARD0ozXxtBJMz/6Pt4QAFqEs6ehRHaUVqudMbaj/Z6z6HLXG3WfX0fef+wbIr1AnjO2WP1i5JGaSo73VFg6c/XfkqtuMS3rpV2X9Z2dH/3kTb3FWbgpkEWR8KjoJyY9JOWkeuY+UQXz00ynFA054GlzVyp1iOb4m7An20i1ql/SYY6yrgcEEkXeKA/YpPbNSi9+BobcjQWqfjHaVnLrJibo/8sM9c0T3jxrd5TqsbQ9Zicg2TNSglLEFG7DNEi2XqXKFQRyht0d0W+yQprozAYZehDt4W3fVTcafRp21ZGQ7oWzOC/MA05EdGRPVKjHVQrFoO9RkUWRGLEMhJ+Z9KTNzwhib4wz1CqB9GEiEVfZimqqNg0WNxq9m1kAYtCuJadwCsq6AzSFDeXEhr6qeGl7QCf/jgpg6gbLCP39a6QzH5xlTCtFpPMVeERM10KJFcZ11b1jJ69pdiEqxXWo+okjg0uJRb64b9WDpoKS6s48qqE9aVI1oGK9tZVGl8SJnzF/0w4I7ICmL+u5eaZ+7Qe03jPnXldciqN0GY0dPNi87rZiAj1GpxC2iogA3mBxZYjvRLZB1PruRuvhJkIiB+IuJciGn27jw15b0Sxof1OohcJIJOHUTQPcWf/eig6I3gEWDG7bekro1CjpmvsyAaUsO6IaIXOEkiCpGokp5TSI8pGevTFiAw2JdbHijDKM0rodwt46GhBwrouyjstSh2F2mIFcZgvWw2ChGPbdNkeLv3vauLmEr/RwZXYx8ddOyRt2juzELdFqRSeKWj0UkaSWITh0HbklaRo9zqH5bdt2VLxiUEXWPbUukbRUevXuKyEoyHodhLvn6UdLqWX0+I2mD+PWYgWl/w4Y1a/kkq0t6T10Bkka41z+OQWApYFMNOVA+P1KaUvjXtBLXX2kSgKk+Os0AnGt2QGinvJOzQoEzRi5Gypz/RD6QdlEANRC5F9fH3XnBmEAUjSnk55Y0aNjeYsssDV3rHRMRv53PRavdQMg/q5UMpiddyOVMciPkP2Iu/ER+1r51QyakO6aJYrCBB2wSO+2Ca3vYtHqGrpV1zUSoVtCSZUALTQpJs70XgTlFe1UkVwIQEi1Ao1RzmK/WhpAmD3zWRND8gJznn7xx/r/Fdd25oOPLClUEduey81jcBc158De4ZI7dOk5BirPGuVuZ0fWCEmqkDJGrIGXHbghjvokBl34C9oiYaV78COV0MhJI9q3ZRvO6Z9pIE37bxFdQVvcbLJX/v69bpbIcJ4LO+wu53g4CRWOqUWy4ObTxbsv7E9oHk3izc2tmDohUWJAoWA0JuT2pL3kvsI8o8e4BlNEigv1Mgu5gj9kXa6e5r5ZEojByBCyB/6tIgJvXp5zDijYa7OMq13cBgYaUJwm+oI02V1c2sXtPx2I1FpUcwshLIJMGVY52RRFnXoXugjsH9l00RUwHca4mJuMyjpmVBP91vg6ATFdGEVT4vYSdnG8uzDTQDYc1yCyaOdhT/FDhY02Zp/fYX/2SvUywQIpqs0CGWn93rv3PbSPIIVLwWpV397klH2nBFbw5j0bECxdDD8cGNcNpvGuisf0/yT5Xax9p2XC3D5g8HRxwe6xkcFKHIL61Scjpe3WJs/jLTQ2urnr88o1MG0SGgEHXiN9bnXIyAVWt2Sc4mpq+DT1CpUsXH+k13ZcmOlArCuXWX0Cb+N3i7IOpB1rtx5fenq2Cd7xXunpBeVdgodAtzFPnoY+amLD1/0e+cQgpfXklM7xbQPO2ug++kOr9HoBNbcD8NIawEGBydDYApcr0DwRqA6XszVDva+4kF09RwEIzDp2/bpGuQu2dZwAj+76Slok46+nylOio/xhFfvB999zqcph9z3OGxlB1n2oQeYd9pOWUHp5+MrvsbNtrvK0W+yuFBy/witjkXai7onIdXEX8dZv9vXy8/EThGyWjbY9rC4ZFTrhyN7eJeZuXSXjTmffCsD1lJ7KFd6O9A3g/dWanflt8KE3UMLpGdUjTfaWRLEmhDTZW6cOqkB/wF8DcRuRqtyND7SBqQlN0VFgQQAa5nM/I7owYj3jP+xguLk47FI4RDpdm7Mfqig9D7V3XuNd2U2D0cDUrftK13G3Bc9Ijq2L5/vUNaWCTH1DZO/FxHrmx+c6G38S0H1z6qzb2GTHVKA6WR86tvCt+I7A/kdVBdO2g1ggsUbrof3lALKOKQIRpUtaYUw0MxUIJABUuXlnOrlWhKgylAXUr7xsoljVSqefjkFLJW493llEd3w+yZg5a43qEm3bPCJjECfrzgUrWNqbupfBasqvvOpIgMAag/iiz62LWoXdSEuK6Ciy+abDqrrdXrMC1UuSL6UJyCG+6wxpvBFy202C1a3a6qbFJvsutI7xXVQpqQGjE8aXWEG9GKEdZD3PiA5kgVj3upCAKSWraoOA4kKAAkwoAQ1beAvF4Uty2npXSr4SisQllxVVEKTHFxFDuWDHwUF9WWdpqV5d8Ho5SrGs/4/ZdTwpz1198gJmRMgzgQUIkRgEsWeQBYrYByfrRh6P/+StqhAC00QJjy3gzw3o2DfdZ0yypfI0+7CIQ/ZRaOlW6XXF2qkvnLKXtJYYXRUMprlX6SZ6FYkMmX+lURR1KVMhon7nrgvuWvqHzoKpCpl1BzWI01toLIjVaTZzxz46FNs4PPZlegO2yUkHfB3Tq8U8t99sVAOiEaFMWqFoMisIhiYDUHFM1eLFhChhoJ2VOo+SZZPa7JMbY45mHMpKBNQYcvTZMfv/hfh+G/KOP5waFWJRq7CFK9cRsgUd4AoL98LN4xdtE8cnQIV9KohfAS8Y8hEvSWEefAFtNUHJ0OYF/uTIfGF++Wx2YTJ7fhleqFe1xtanBjKf0p/vcYKKKQGBAM1T8rKinUUE4MzQgdikgHkwtyc7E029zPIPmqRCvOkck8WWnhuqumsBj9ZxJSyYUt+VSc1UtSQEwkIBBmAPKjQstgMSB6+5NgW+b0GlLXMoRBwjqhERDZAyzbw2yO8hfUG4WeSUNQ122CPSCKULJQPjiorHiYf4J2MCVMolD0zl4sV61s71lDL4tG+X77MHuWW245Tv6cFa5cUoRE13hA83otf3l2O6kcUZQwLPAAAAE4AZ4GFaZJbwNX1sj8YM8gS+bAbeBIlXHMonNOO9jzz7eUsU0DxpKZhfI5Esaze+chdHORbs1BRknHmxXpAo0eEuqnbFEH8dkgtRVRyw/rch5UeQHLfHEP8V+a20HY04Kx6nk2iUvxIs/PciP9fyPwJpbKKLXRTrCBn9j+tgoPNgvzwUAi4jtHK7fPMT9mwdiJqeBuM0mRjzoSEX7j1psvjSEEOdJo0FkbGtdKLrAr3/mX5nnI2m32YijzlNrHpPYtjHJYRGSpLfzBKkDbhFF7zVzbZXYgBAnzeTgPvDKTRJyrVOpQ10dFUEMQDyPaeb7ceFla2FLKbJk2H1uhywnna9IzEJCOoCW0yi9FLaYDWa8r4bRx7OsuIrT9ZHpH8CY1Ln2MgRSD1belmloHctUAbMODNFxxsM2AISoUrbGSiBWCKS9VWi1LEAAgEFVv389yauxGfurNR61pK7gz07YlekRpjo88mtqapoWWhRSIWF0/79Kz5DgmPG0m1z75K5jt0juW9FmltNwGL8UIqUICCbbn0IskNg1ZVOCKoLOxCBD3Fpuz7wLsKKhskzxv039rcmasrL4fmjjrHbKql90V7V5FdJePvFSalt18kE5Sodk8XFJNJMfHREOcAMsxSWMgySLQ44UzQvLFkLSkpCA3+GHBU0a6NZt6SgkKjU/TvCMqtCHyAaVpO+9JwnfpBmrA/buRUfcVbGdwSQvvzuTMUIrbQ0xBKTAEPLJKUX/e000mB+w1I9B9JoRxuZl7Wnmgt8qxXh1tkPh7qkbLJQrRjRtTHCWq6FvELkyV9aEwitX5SR4hTNNGWmI8ArSQYCt1SYGzXRpIs4Pk6HAB58clFLrnzlEFLMvTFRLuV+cJhBQIbGh/VNRH9DCfyxXPjySVrfzpqnLm5OLFBOjE2TRGC89OK7qutZK0T8aViSEPt7fQwOLgaXoG3EbU6RqtIOE9aVkQjtdaSYHfTuzTreZVEqt04HE1zg7FviwRAenStKjQBM6WyRxyvA5tcS1cp3HKx36VLvg166C5RP39eqfblLDjfsv7KweEZe9XRnAKqSgOn5leK/B4+jyRspe0YCpGrl7fzkV7iI75ZT+ul0bWEhF0kQ4FaKDAVpEWBUkwoENHS3yroOnoHVHysDSClmXpionDNtghLgoqh1pCpAttDRCQ+ctEjGMsNfjG6UJCms0JRtdFTfKRMoMsYpRvXk1WJpWQF+gf2YtNLWKaL1TokhX57KEgtXKzAfr76JXfwwQhOpRfs3l8Gqp9QjDZnSA7PDfn+qFWwYKH8L9MIvpzNHkAAABsAZ4GGaZJbwADG96SOxEPRWPf9Nqpp+S0TTsDE+ADMNI9gani3qdrEdcORjtQoSAR9awywAel7HA3GRQxNYK0K4pIGdAtrHIYERQVuf88z78VMFIrnYG2o63PlEsOqNgoMQXfhfUJjADlxNzgIXoUvaGKiISyEEETddSmAGcUq6iZdVAJgrIus9/EBD5eqEm6JsdytTjHGSPV3C89ede/e68nq7CG5OAQJs4eJMcPrXeQO3+6G3LQQetyNB941qJ460JcT8YKotaBAUiAvxFxWVSGwmQxo5h1TNpX77S7znYRwSWWVYABJpwARRDY0cqdHKl1UUDjAMVZNaFCSgMu1fexe/NwS7rLy5j2dGKV+PfnxLX5OJ4aOy6ru8JtuDtKZnddwCXhLXVgdf74RJNXqnsPqKqjqw8K6O+a7dih38J5/CZ3E3YVVVmJCqAisoJ1cyiDKykmxIjAxO9wMSPbaJZ8s8iiqlZVOIwYk33tQOkqDCmIQgKIgERkQBRwrcOaFXUIWD029QM9BLjgd799vFNV+30YWQ6OeqRaaWo7JqFYlA6YWlMJanqUFAJajl+gP5T86yF9d7Jner5eqvnfebGjXcbZtvbP+GY/vSnmRjoaUB0tZXrF7tUjmuC0ol8zDjha3FgOyewNgpGoaGNLLn7QwfmLC61rjL9UvlZTugqTDL0hGhSlkpzQQohECt3kpYAlRlkoA1BKjOkrZk1t1ioCDdJMMcy6VefIyPw+gp1MUdY53JFNRK8+YyYzCyEi8G1k+rBu5VcDMqdftEt7mqoEZpB43NTUbwBsgmyK1Ntumwq5Ke7drSO4ClmBRQjtkNwKu3XdTEuvrmkECdCrk26GcnXB7OvjNsL60s8nsmbboKKLGsnXXdLBylKB4yaiPA7ggQ2vTPyUhTGYqXVkS2RptFLd/npbEqr9dgRUTyPqPFcJKjCRrYqCJbQz96CH09obUBmyvbS7qFBQ2Px0cTkzOPQ0Bo9fRgSQ7dw7JLQwpzup3lKewjQjCGLmsyr2yl4LoBdEADfrjo+/zL2rQrZweF3WHz1H09SZsTe600usjLhVBScM2Asbmaejh3UmbVs0WaVIAUvdxYNzLex/0HW9kLMMy0WGkj0qlmtVM4gqhaeFq3cEjVeqw1x7p9r+IAHQa+84hnfPaRIxo6gz2m8SI15BRQXxUZM+tQUJoUsoK6WFMnrTRPWelmBiixPmZOGiMWuHeumM7SgxjCc0Hll91KhQOgAAAOABngYdpklvB2WUvhuJ57w07LlYej5aHEb4TPaNaET2wmhv8rG7V/ALKyQ73gFFk7+HmqTOU0X3vF0+X/LienJyReGkmw9Gn629C/bufqeQTV9jck/YrHufv+ENG3YiaaHx8DX5TPQDR4KQbKFeeT5tLvsx/TK8KfdZuMGJ6Di+Pt2o8EyFlj51NGM/Cy3LNleQBavlBTEs+xnfybLFy3HErDiJmQQcVdg1cgQoi3g/zDZdboo+YRe6RQ+IBdo+5iFpHQ44kscJl/CRvc2kBxedepuQo9dZyixl5UuSPxTyRCEaT/z//gD+ZtELRDIIgiOFmDObqJIRUqEALDZSvNuryQCXWW7jfxtBWbz2fbEeNG5eMkSCNjq07JjS59hUPT69dhdSI0YtGCwklVcNRQrZb9ferEGxlH0IB0mHpEYhFuvtBmwLteu7HFp4ZXtoT3dfSqPfmo/C/y/e6fi0vXrm5y3WKzytGsOuhZpm7J3cqQVYYyu7MrzWV2MF1tI53oNEzLJ5t4gTXK4jzcJ0AbGr3BfxdQYkiqaaSSaMFeQSdQCSxVd7CSCJ4+C4JIVWz2L0AdNjmae2IBZlXGYSRgpBV7tAJWGoQUIRQkYShpm73zpVSrNBal0qwgNL4J3rruoYv/KOiYpONe58rHnRHmW3iy0EC6ZYV+wD0HvcboAOe0wISKQn5JdfyTVAoWpyRcmDAAv4wbSTmDty6BCT0qZ8oC8r3OnFGft6GaLnacEPN8eL+jM8t1j7olHP2njlzaHJ6Cm75dBBDrlfsOdClL5be6J0xud4PtsjeHrQSgcZFAHSISpP///2AH5WyUWFEdAskSgk7utMEEUtl1FWKFjxSZx7inwliqlFE/n7x/d3pfuuxZN6zS7eghqU60iglSJepXU4q1lkmloKZOy9Sk7m1BBOEiFFR1uMeLOkiZnVKo8ENTzfbjZ6AAdCvlkcp8TwqH98OT2PhRk8s3GjCd2m3S6aeyux0Tj40iMhpF0WLTZJaRpe9UlFx3+Gy13JQxPlF7BgtEXLolTEcKGNy7aYo9TDJUEsQ7sKKlKYDONNLWiwDDTAoi4wlc0yCVzd5vpXN+G2PXI9m/JBCtlCaqFCEgJeHoQREkVnBbFswGgClgEAMkwNr5/MxtV3ttqqi7h/+SCwV3TIyU3EmfaLRCioSxTQWHPqx1bouSOmyAdFUigf5ZWVpmJJARfCkPxJpoXV4t3wqyGqCRgoW3aELqX9brsmq84opRe7pv2Nld2RX9dwDG4nXHSYL5Syf4FdkslD7Qx2UDSgyEoA+wAADypBmgYwYCe3AAJoTc70oEp9Xa4eOkdMzf+uQXknRbbtG6KwSbRWEhOObdH0HyP3YBUpJKZYyJlqn4UX1b9lqMLGBtvv5PdSS2ZqoHf06rsQD3j5W/RbiRMtrEF2WceoIgN+QiM6XD12fuqtYLhnXjeDS/L6llQFhdqTmVSvdYG1VE2jAKGg+S/eMKJqKHpVWSn1aO+Rcrb5ZimZnzGKNgJVmcqOTg1SxdeAqaPvod2KwSPWrPb5N82eUxX2BEGtl4tC146KJ/3/uaUIuIMsbDxkDEXTMXVVdLgyJZ3JXfSxxwG/CWjvPVK1qmUCPKpUGO6LjSNfgMUUWlGE6tewSsT4usUMfRQBz88VLqS/dmeb61PDCVf++mhl96uHhZ2h50qFmxFk0ApS2PFo7TAjaR1LWloKK4ozuyPyYHtdwk9WJaFjerCf7KMxnD+BiTpYEIXvIy8xynyorvBHEGvs00Dmr2jxNFSNrmYxvkKv2Hw7YzDGOkUlp2ChR107VTT7zz+sYzUe542pYVmYt0JELRRmYUgOyhVusKwcE76irKJZhsgPnBf0nNVKoceOkmB8iwS9ECCPRQcQbMXMU02BxXsCR4VUTsPmhnXmT/i5XXHae+eONQu2ajZamCX6z6IoiZZhMMqpfUyfkZ70Ax4//AalMcNbpYtTjDpZCDKSdW0T6BG76t1aME+KXPvwGdSQOYGRmD3rzCeJ5fIU0ffukHDQzi+CPNUFMHMV4s73/5HuhmFSEE2GX30TvT2R743XylraFkWyxkPC3copT/SaO2upWbTxmGOcevkM3dm3rjdsYumvqtfjijeVniiw6mybRq38nQZobX0+MVbcEzvdQsmyfVna6eo+rAVqHESxhRwbHnrlp4WxXJuWhrg3+2xPBYPv+QD95rpBh+f06ezLcWB82t5Iu9IyETqxO7j+FOjU5vu8UDmBVelORsH5h/D0UYjdyphh4Mi1lwkonIjOzQ4k7gIoZq96fS+EdBF9gpgDnSRLIkv7Y4YMQRZGEuIWo/SM+NS0j5g4wx/MNEPW+kahIT1NvH5o4ZXlCk3nuuiIu3zfs8Ul3kK46NnFLXMDiST/kbvFT/c6/UT0Fl3TFsmKOE6l1kthFszFLKve8F807J1SUozn3Fp8SsxvDI8LcpLPKb0m3aYK72+7UyPDboErYem9UaAW+IYq4yXCB2b8dX0nCIuiH44ExZ4AblKjhRDDVP6bmgwNWEGDNxnWNkmrPcxtLO0dFyT6mF3YnddBkOMrNSg+QtzEEnS7fqU2Gc8Vi8DydmnEG9niKL/tP+ePcxLdphyzr55o63r+z9VzYKuv5SAHL8MQ++6h4YfXS2KPfkXGi5hDmtSgkeThJbbR1RcZf2oxIUVGFEYJTPhVFOX2st1XGrGk69p54xJo6yy671tvFDKMAFTMNqU5BZk0FWNK/7w/gHrmVmdmamI=
*/