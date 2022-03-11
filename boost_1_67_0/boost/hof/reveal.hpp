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