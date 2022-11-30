/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    if_.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_IF_H
#define BOOST_HOF_GUARD_IF_H

/// if
/// ==
/// 
/// Description
/// -----------
/// 
/// The `if_` function decorator makes the function callable if the boolean
/// condition is true. The `if_c` version can be used to give a boolean
/// condition directly(instead of relying on an integral constant).
/// 
/// When `if_` is false, the function is not callable. It is a subtitution
/// failure to call the function.
/// 
/// Synopsis
/// --------
/// 
///     template<class IntegralConstant>
///     constexpr auto if_(IntegralConstant);
/// 
///     template<bool B, class F>
///     constexpr auto if_c(F);
/// 
/// Requirements
/// ------------
/// 
/// IntegralConstant must be:
/// 
/// * IntegralConstant
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
/// 
///     struct sum_f
///     {
///         template<class T>
///         int operator()(T x, T y) const
///         {
///             return boost::hof::first_of(
///                 boost::hof::if_(std::is_integral<T>())(boost::hof::_ + boost::hof::_),
///                 boost::hof::always(0)
///             )(x, y);
///         }
///     };
/// 
///     int main() {
///         assert(sum_f()(1, 2) == 3);
///         assert(sum_f()("", "") == 0);
///     }
/// 
/// References
/// ----------
/// 
/// * [static_if](static_if)
/// 

#include <boost/hof/always.hpp>
#include <boost/hof/detail/callable_base.hpp>
#include <boost/hof/detail/forward.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {

namespace detail {

template<class C, class...>
struct if_depend
: C
{};

template<bool Cond, class F>
struct if_adaptor : detail::callable_base<F>
{
    BOOST_HOF_INHERIT_CONSTRUCTOR(if_adaptor, detail::callable_base<F>)
};

template<class F>
struct if_adaptor<false, F>
{
    template<class... Ts>
    constexpr if_adaptor(Ts&&...) noexcept
    {}
};

template<bool Cond>
struct make_if_f
{
    constexpr make_if_f() noexcept
    {}
    template<class F>
    constexpr if_adaptor<Cond, F> operator()(F f) const BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(F, F&&)
    {
        return if_adaptor<Cond, F>(static_cast<F&&>(f));
    }
};

struct if_f
{
    constexpr if_f()
    {}
    template<class Cond, bool B=Cond::type::value>
    constexpr make_if_f<B> operator()(Cond) const noexcept
    {
        return {};
    }
};

}
#if BOOST_HOF_HAS_VARIABLE_TEMPLATES
template<bool B>
BOOST_HOF_STATIC_CONSTEXPR detail::make_if_f<B> if_c = {};
#else
template<bool B, class F>
constexpr detail::if_adaptor<B, F> if_c(F f) BOOST_HOF_NOEXCEPT_CONSTRUCTIBLE(F, F&&)
{
    return detail::if_adaptor<B, F>(static_cast<F&&>(f));
}
#endif

BOOST_HOF_DECLARE_STATIC_VAR(if_, detail::if_f);

}} // namespace boost::hof

#endif

/* if.hpp
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
*/