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