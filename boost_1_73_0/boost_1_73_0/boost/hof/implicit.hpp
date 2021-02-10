/*=============================================================================
    Copyright (c) 2012 Paul Fultz II
    implicit.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_IMPLICIT_H
#define BOOST_HOF_GUARD_FUNCTION_IMPLICIT_H

/// implicit
/// ========
/// 
/// Description
/// -----------
/// 
/// The `implicit` adaptor is a static function adaptor that uses the type
/// that the return value can be converted to, in order to determine the type
/// of the template parameter. In essence, it will deduce the type for the
/// template parameter using the type of variable the result is assigned to.
/// Since it is a static function adaptor, the function must be default
/// constructible.
/// 
/// Synopsis
/// --------
/// 
///     template<template <class...> class F>
///     class implicit<F>;
/// 
/// Semantics
/// ---------
/// 
///     assert(T(implicit<F>()(xs...)) == F<T>()(xs...));
/// 
/// Requirements
/// ------------
/// 
/// F must be a template class, that is a:
/// 
/// * [ConstFunctionObject](ConstFunctionObject)
/// * DefaultConstructible
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
///     using namespace boost::hof;
/// 
///     template<class T>
///     struct auto_caster
///     {
///         template<class U>
///         T operator()(U x)
///         {
///             return T(x);
///         }
///     };
/// 
///     static constexpr implicit<auto_caster> auto_cast = {};
/// 
///     struct auto_caster_foo
///     {
///         int i;
///         explicit auto_caster_foo(int i_) : i(i_) {}
/// 
///     };
/// 
///     int main() {
///         float f = 1.5;
///         int i = auto_cast(f);
///         auto_caster_foo x = auto_cast(1);
///         assert(1 == i);
///         assert(1 == x.i);
///     }
/// 

#include <boost/hof/pack.hpp>
#include <boost/hof/detail/result_of.hpp>

namespace boost { namespace hof { namespace detail {

template<class F, class Pack, class X, class=void>
struct is_implicit_callable
: std::false_type
{};

#if BOOST_HOF_NO_EXPRESSION_SFINAE
template<class F, class Pack, class X>
struct is_implicit_callable<F, Pack, X, typename std::enable_if<
    std::is_convertible<typename result_of<Pack, id_<F>>::type, X>::value
>::type>
: std::true_type
{};
#else
template<class F, class Pack, class X>
struct is_implicit_callable<F, Pack, X, typename std::enable_if<
    std::is_convertible<decltype(std::declval<Pack>()(std::declval<F>())), X>::value
>::type>
: std::true_type
{};
#endif

}


template<template <class...> class F>
struct implicit
{
    template<class Pack>
    struct invoker
    {
        Pack p;

        constexpr invoker(Pack pp) BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(Pack, Pack&&)
        : p(boost::hof::move(pp))
        {}

        template<class X, class=typename std::enable_if<detail::is_implicit_callable<F<X>, Pack, X>::value>::type>
        constexpr operator X() const BOOST_HOF_NOEXCEPT(noexcept(p(F<X>())))
        {
            return p(F<X>());
        }

#if !(defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7)
        invoker (const invoker&) = delete;
        invoker& operator= (const invoker&) = delete;

    private:
        friend struct implicit;
        invoker (invoker&&) = default;
#endif
    };

    struct make_invoker
    {
        template<class Pack>
        constexpr invoker<Pack> operator()(Pack p) const BOOST_HOF_NOEXCEPT(noexcept(invoker<Pack>(boost::hof::move(p))))
        {
            return invoker<Pack>(boost::hof::move(p));
        }

    };

    template<class... Ts>
    constexpr auto operator()(Ts&&... xs) const 
    BOOST_HOF_RETURNS
    (
        BOOST_HOF_RETURNS_CONSTRUCT(make_invoker)()(boost::hof::pack_basic(BOOST_HOF_FORWARD(Ts)(xs)...))
    );
};

}} // namespace boost::hof

#endif

/* implicit.hpp
X2DSOJiOG0GsOW7jXDAa3WCiUzpmEJOzSadjmd0MovqPVqtEnNxYkhyDeTDnFQbLVeu9vDgrslQb7fM9qtF5cg0evaFexj4cTcy++baXsx+VCoLswzB2Vy6TXiVQMpCLyQjzQlGGwXDQ28U5wIpiFWLmFRhBEodJzLMpT9QF24zPrSLY62/GR/1dqQqOhLWARzGeZiDmqVVYbQ4isnuZRKbPYuKlIiFfccUrWznlLffvtHZwPTe+E1nGC2zBjYui5uepcva2sBtaZTZNV0VAY+g94h9U7OFMEY4xMwed84tuL1XkVx50XN/2EodWC0BiunR8W5EiWkEqqPKRUmcRaNt7UvAXd5LgL92Tgr9kE22bFMks69Xx462qGH6LVVOM3LBVHskZWx5vGfYgk+9+wyrAzLbVdGTbMjngtm0VRGZeBbFt3hyizLy/Q4RXKzagskTge46n5RvMKXzTONzWrlorFE4E6jQfn1xdRzSE6vsDRy4JNLYooDTe3JOZC/k3XRWxucUHyqQvtU36TztIvGrA2kBvaNOajmWBpjdEVXC1Lf2s3/7XcPywDpKuoMkfIP2D0kADC5/3wOue/fqZg8fpx+n+OvoJaR6j36g96bx6hH6C7i+jn5TmMfoNLvqP0A6ptnbZn6sflwca
*/