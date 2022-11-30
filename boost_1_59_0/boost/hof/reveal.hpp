/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    reveal.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_REVEAL_H
#define BOOST_HOF_GUARD_FUNCTION_REVEAL_H

/// reveal
/// ======
/// 
/// Description
/// -----------
/// 
/// The `reveal` function adaptor helps shows the error messages that get
/// masked on some compilers. Sometimes an error in a function that causes a
/// substitution failure, will remove the function from valid overloads. On
/// compilers without a backtrace for substitution failure, this will mask the
/// error inside the function. The `reveal` adaptor will expose these error
/// messages while still keeping the function SFINAE-friendly.
/// 
/// Sample
/// ------
/// 
/// If we take the `print` example from the quick start guide like this:
/// 
///     namespace adl {
/// 
///     using std::begin;
/// 
///     template<class R>
///     auto adl_begin(R&& r) BOOST_HOF_RETURNS(begin(r));
///     }
/// 
///     BOOST_HOF_STATIC_LAMBDA_FUNCTION(for_each_tuple) = [](const auto& sequence, auto f) BOOST_HOF_RETURNS
///     (
///         boost::hof::unpack(boost::hof::proj(f))(sequence)
///     );
/// 
///     auto print = boost::hof::fix(boost::hof::first_of(
///         [](auto, const auto& x) -> decltype(std::cout << x, void())
///         {
///             std::cout << x << std::endl;
///         },
///         [](auto self, const auto& range) -> decltype(self(*adl::adl_begin(range)), void())
///         {
///             for(const auto& x:range) self(x);
///         },
///         [](auto self, const auto& tuple) -> decltype(for_each_tuple(tuple, self), void())
///         {
///             return for_each_tuple(tuple, self);
///         }
///     ));
/// 
/// Which prints numbers and vectors:
/// 
///     print(5);
/// 
///     std::vector<int> v = { 1, 2, 3, 4 };
///     print(v);
/// 
/// However, if we pass a type that can't be printed, we get an error like
/// this:
/// 
///     print.cpp:49:5: error: no matching function for call to object of type 'boost::hof::fix_adaptor<boost::hof::first_of_adaptor<(lambda at print.cpp:29:9), (lambda at print.cpp:33:9), (lambda at print.cpp:37:9)> >'
///         print(foo{});
///         ^~~~~
///     fix.hpp:158:5: note: candidate template ignored: substitution failure [with Ts = <foo>]: no matching function for call to object of type 'const boost::hof::first_of_adaptor<(lambda at
///           print.cpp:29:9), (lambda at print.cpp:33:9), (lambda at print.cpp:37:9)>'
///         operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
/// 
/// Which is short and gives very little information why it can't be called.
/// It doesn't even show the overloads that were try. However, using the
/// `reveal` adaptor we can get more info about the error like this:
/// 
///     print.cpp:49:5: error: no matching function for call to object of type 'boost::hof::reveal_adaptor<boost::hof::fix_adaptor<boost::hof::first_of_adaptor<(lambda at print.cpp:29:9), (lambda at print.cpp:33:9),
///           (lambda at print.cpp:37:9)> >, boost::hof::fix_adaptor<boost::hof::first_of_adaptor<(lambda at print.cpp:29:9), (lambda at print.cpp:33:9), (lambda at print.cpp:37:9)> > >'
///         boost::hof::reveal(print)(foo{});
///         ^~~~~~~~~~~~~~~~~~
///     reveal.hpp:149:20: note: candidate template ignored: substitution failure [with Ts = <foo>, $1 = void]: no matching function for call to object of type '(lambda at print.cpp:29:9)'
///         constexpr auto operator()(Ts&&... xs) const
///                        ^
///     reveal.hpp:149:20: note: candidate template ignored: substitution failure [with Ts = <foo>, $1 = void]: no matching function for call to object of type '(lambda at print.cpp:33:9)'
///         constexpr auto operator()(Ts&&... xs) const
///                        ^
///     reveal.hpp:149:20: note: candidate template ignored: substitution failure [with Ts = <foo>, $1 = void]: no matching function for call to object of type '(lambda at print.cpp:37:9)'
///         constexpr auto operator()(Ts&&... xs) const
///                        ^
///     fix.hpp:158:5: note: candidate template ignored: substitution failure [with Ts = <foo>]: no matching function for call to object of type 'const boost::hof::first_of_adaptor<(lambda at
///           print.cpp:29:9), (lambda at print.cpp:33:9), (lambda at print.cpp:37:9)>'
///         operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
/// 
/// So now the error has a note for each of the lambda overloads it tried. Of
/// course this can be improved even further by providing custom reporting of
/// failures.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     reveal_adaptor<F> reveal(F f);
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [ConstInvocable](ConstInvocable)
/// * MoveConstructible
/// 
/// Reporting Failures
/// ------------------
/// 
/// By default, `reveal` reports the substitution failure by trying to call
/// the function. However, more detail expressions can be be reported from a
/// template alias by using `as_failure`. This is done by defining a nested
/// `failure` struct in the function object and then inheriting from
/// `as_failure`. Also multiple failures can be reported by using
/// `with_failures`.
/// 
/// Synopsis
/// --------
/// 
///     // Report failure by instantiating the Template
///     template<template<class...> class Template>
///     struct as_failure;
/// 
///     // Report multiple falures
///     template<class... Failures>
///     struct with_failures;
/// 
///     // Report the failure for each function
///     template<class... Fs>
///     struct failure_for;
/// 
///     // Get the failure of a function
///     template<class F>
///     struct get_failure;
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     struct sum_f
///     {
///         template<class T, class U>
///         using sum_failure = decltype(std::declval<T>()+std::declval<U>());
/// 
///         struct failure
///         : boost::hof::as_failure<sum_failure>
///         {};
/// 
///         template<class T, class U>
///         auto operator()(T x, U y) const BOOST_HOF_RETURNS(x+y);
///     };
/// 
///     int main() {
///         assert(sum_f()(1, 2) == 3);
///     }
/// 

#include <boost/hof/always.hpp>
#include <boost/hof/returns.hpp>
#include <boost/hof/is_invocable.hpp>
#include <boost/hof/identity.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/holder.hpp>
#include <boost/hof/detail/join.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/detail/using.hpp>

#ifndef BOOST_HOF_REVEAL_USE_TEMPLATE_ALIAS
#ifdef __clang__
#define BOOST_HOF_REVEAL_USE_TEMPLATE_ALIAS 1
#else
#define BOOST_HOF_REVEAL_USE_TEMPLATE_ALIAS 0
#endif
#endif

namespace boost { namespace hof { 

namespace detail {


template<class T, class=void>
struct has_failure
: std::false_type
{};

template<class T>
struct has_failure<T, typename holder<
    typename T::failure
>::type>
: std::true_type
{};

struct identity_failure
{
    template<class T>
    T operator()(T&& x);

    template<class T>
    static T&& val();
#if BOOST_HOF_REVEAL_USE_TEMPLATE_ALIAS
    template<template<class...> class Template, class... Ts>
    BOOST_HOF_USING(defer, Template<Ts...>);
#else
    template<template<class...> class Template, class... Ts>
    static auto defer(Ts&&...) -> Template<Ts...>;
#endif

};

}

template<class F, class=void>
struct get_failure
{
    template<class... Ts>
    struct of
    {
#if BOOST_HOF_REVEAL_USE_TEMPLATE_ALIAS
        template<class Id>
        using apply = decltype(Id()(std::declval<F>())(std::declval<Ts>()...));
#else
        template<class Id>
        static auto apply(Id id) -> decltype(id(std::declval<F>())(std::declval<Ts>()...));
#endif
    };
};

template<class F>
struct get_failure<F, typename std::enable_if<detail::has_failure<F>::value>::type>
: F::failure
{};

template<template<class...> class Template>
struct as_failure
{
    template<class... Ts>
    struct of
    {
#if BOOST_HOF_REVEAL_USE_TEMPLATE_ALIAS
        template<class Id>
        using apply = typename Id::template defer<Template, Ts...>;
#else
        template<class Id>
        static auto apply(Id) -> decltype(Id::template defer<Template, Ts...>());
#endif
    };
};

namespace detail {
template<class Failure, class... Ts>
BOOST_HOF_USING_TYPENAME(apply_failure, Failure::template of<Ts...>);

template<class F, class Failure>
struct reveal_failure
{
    // Add default constructor to make clang 3.4 happy
    constexpr reveal_failure()
    {}
    // This is just a placeholder to produce a note in the compiler, it is
    // never called
    template<
        class... Ts, 
        class=typename std::enable_if<(!is_invocable<F, Ts...>::value)>::type
    >
    constexpr auto operator()(Ts&&... xs) const
#if BOOST_HOF_REVEAL_USE_TEMPLATE_ALIAS
        -> typename apply_failure<Failure, Ts...>::template apply<boost::hof::detail::identity_failure>;
#else
        -> decltype(apply_failure<Failure, Ts...>::apply(boost::hof::detail::identity_failure()));
#endif
};

template<class F, class Failure=get_failure<F>, class=void>
struct traverse_failure 
: reveal_failure<F, Failure>
{
    constexpr traverse_failure()
    {}
};

template<class F, class Failure>
struct traverse_failure<F, Failure, typename holder< 
    typename Failure::children
>::type> 
: Failure::children::template overloads<F>
{
    constexpr traverse_failure()
    {}
};

template<class Failure, class Transform, class=void>
struct transform_failures 
: Transform::template apply<Failure>
{};

template<class Failure, class Transform>
struct transform_failures<Failure, Transform, typename holder< 
    typename Failure::children
>::type> 
: Failure::children::template transform<Transform>
{};

}

template<class Failure, class... Failures>
struct failures;

template<class... Fs>
struct with_failures
{
    typedef BOOST_HOF_JOIN(failures, Fs...) children;
};

template<class Failure, class... Failures>
struct failures 
{
    template<class Transform>
    BOOST_HOF_USING(transform, with_failures<detail::transform_failures<Failure, Transform>, detail::transform_failures<Failures, Transform>...>);

    template<class F, class FailureBase=BOOST_HOF_JOIN(failures, Failures...)>
    struct overloads
    : detail::traverse_failure<F, Failure>, FailureBase::template overloads<F>
    {
        constexpr overloads()
        {}
        using detail::traverse_failure<F, Failure>::operator();
        using FailureBase::template overloads<F>::operator();
    };
};

template<class Failure>
struct failures<Failure>
{
    template<class Transform>
    BOOST_HOF_USING(transform, with_failures<detail::transform_failures<Failure, Transform>>);

    template<class F>
    BOOST_HOF_USING(overloads, detail::traverse_failure<F, Failure>);
};

template<class Transform, class... Fs>
struct failure_map
: with_failures<detail::transform_failures<get_failure<Fs>, Transform>...>
{};

template<class... Fs>
struct failure_for
: with_failures<get_failure<Fs>...>
{};

template<class F, class Base=detail::callable_base<F>>
struct reveal_adaptor
: detail::traverse_failure<Base>, Base
{
    typedef reveal_adaptor fit_rewritable1_tag;
    using detail::traverse_failure<Base>::operator();
    using Base::operator();

    BOOST_HOF_INHERIT_CONSTRUCTOR(reveal_adaptor, Base);
};
// Avoid double reveals, it causes problem on gcc 4.6
template<class F>
struct reveal_adaptor<reveal_adaptor<F>>
: reveal_adaptor<F>
{
    typedef reveal_adaptor fit_rewritable1_tag;
    BOOST_HOF_INHERIT_CONSTRUCTOR(reveal_adaptor, reveal_adaptor<F>);
};

BOOST_HOF_DECLARE_STATIC_VAR(reveal, detail::make<reveal_adaptor>);

}} // namespace boost::hof

#endif

/* reveal.hpp
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
*/