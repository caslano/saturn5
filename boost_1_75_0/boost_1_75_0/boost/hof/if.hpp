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
pC4Bn7ArHvl+ymB7VvaefRxTQBiLOce/LR7qM4eoccGCf4zcaSp3AbdsIWD8ep34oGebcjZw5yhCdyfxFv+2I2Tn0NgTP+Y5PkhUzXJRT8dANfjEZhMqqCbyscEqjeXwtU63XRAB31DCt2Kag8zRy5fRFzGEFjlD89Ta3DyGqB1LJreMATFNXLhjO7yGNMpNkeRVP/QLLyO59fgtiCxw9inNWbhqJB33GoEn5mzjA6tVuUzvTFazF0liWaReDLrmpECKnwsFb/l7yM497lFsXdGC0UHfARGIr4hQU7lcW5dtdN3XuJySKEkUUgYxWnGNRHbUj45YRHUy8piLzM2kdoRKXyxZOLtqLxy4pn9E8mUyAf0cxdM5dL4IUSJVT6J2CfM3hwkt8hsV0xP9Vj2Ul8ELFo9RS1S0kaMeP9uxY0jjuzTYJP1uMg3s5VEXjQ0qF56u6vJ+Dme/p35mM+FuAMdwfZvJlyg8m8E9ZKizZtIID8Q5Qrl/EePtNv64qqViSwrK7bMJP90goX2XVKAmOvHQJV5oLDzd1SUm/yWlo9ClWZzMWtfCJVXvl/48XkoEr6m4DfR1oIZyo67pj89GwPGRQTcbywkNEwnl1td0WJSbs1Qql9PWKWDxJGDfNkbch8x0FCjNrqMR5XSGrU3kX0mXCDv07tscvud64p72Au95IiYslRYpNyXTwOsRd/mhhA3c45VmXo60PPX+
*/