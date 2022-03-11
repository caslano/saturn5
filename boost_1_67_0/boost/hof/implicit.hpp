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
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
*/