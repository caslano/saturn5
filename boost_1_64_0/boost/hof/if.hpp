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
5OjtEzMk217vPAF9kj5DYWcgU5+CwieIs84hUPgw+QcmHBVaWMJx8+UmM6yDN6+BORBh+DHY4szyeQHzBCo5M7nHoJATVw/GJ4ErhFedmLhQaFboLEvQFp7SQCfrcNtLpwRQgZ3XcwUaTkgiM/knTQXS4UXHdNNCTfA07TWzLuu162VdOoGPfNrbrYNIR/ONPGbyuGKJEHNrC+tyiT5e13md0veeQMvG+9+H2p5F/UxjYNpmk5EXOBV9dRZXdSqmd2C0NsOqoLxK0yWUYy4ze16vsh+3WHO86ZaOJDfNJyr/CaBTNfRN/Da6kfGbo04a0S56hwQk+BiRNd/qP9ryeyI5aPcQmBsrFB0LgJNJeqiW6AFQTOLNjaZiquDJmtWsRz+tVdbjvFVKlIDz1S+3RydiBMGIzik4RzsnvjHcRJNbl5vCoeb6r+lRsk7sE6/XcIMhF8a2yEr0nmGoy5rFGQZH8MgM5tDZDYiSc65QmZwc7ecDfv0pRoa86FEJJE6NMvciJXH4DTayoUa9hJ2PAetFyWoiyFZy+bDU+M85ZlX2Hk6Rhl3yMLuukBwgl7hyQ/Ls0tuPL7RcyxPcRXLuNA/8Xlm1Wdp1smp7/NwttaIgTLUbPJcbgjWcdTBG6CveaZYYAcDQHL9trnkAH9hXm0DlQvrgQqPhojvNif0pVYz56uXJWEMcIealQ4h9/HFEJPS5huHu8elw1u8uMU7Kx0lCm9NgDRoKJ7Y3jdyoWQkoqygJAYgz5ymUNVwCt+o8iQ0+ZGo3m7FBvYhK2tcnIMEkizlhJHHM9hDfnCNrlx4jWy+JNwStyOgnLyo37Tqq3Fnrj1e5xWenVO6GxbJyuUmV6/9Z60SZuhMf4Ip5S+PLlQ1Emyx4iFHwPZKpwyRaz/NjjE9Mu5pZN6xFtX2Ta+uzjdkLfeJ3ktWafmYofXu8SNQSOD5xbUhCkx2K4ZrHbWxA9JPNg+plqBYyzk9iwc0odjTWlavksU/npoFbY43967FT28BF6t1RGyny+3hzDmIuJBHz22RcEkSpgN90v4V8p2xIWgJKp6olIDcwJt0SMOrz3MVsKZYWgb/H7HhC+x3ekKb9QCEfs/1Y/691mdqxZraRFYQOUrLYNZ0ooZSfstcc7MWm6oiKBQ2NVtptrXfO6RbrNhjIBDZSR5NUDsa7GxDUYZHZf6Uamv2IqH0DGzyZyV786/H83YMcE905Ke6GhmT3A+uT3XfNTXZnzE6xf3h1sntXY7I7tjzl/D85/w+YQZdhCbJ5Glb3axeB6u6YpIAZw2qI0dN1HCTBMp5tfMQdkimcaM+ObZPbQ3s0X6hde5qYfLq11BZ0htrhCYvY9rUHqWun2YK5rRXWaTOtwZzWCtu0mbZgdmtFxrSZGUE7hbMC6+NPdu7f0GYsVZkkgRwYQscDuUqeakMWjw9W+o6BdjVHuxrRhpL4y3vXqGiOpUY8n77epe+dMMsVPA/GEPTabMC7ZgBXwJVQgdAnHwUmt1pRh1NCn3wcmGBUZHjok08Co4za9At9EgsMkFUK9F4+YjdGj7UBw/qzKYbnn7Lnd/DyJHt+NKnyiOY8+RrFWb/nYsVZd3lhuoAM8Y/mvnIvJ13xhlW+N65krw5wtT0ZpNTL1n7A0bed/lmNf9ke/mMk2HXlpzSTJ+2xnpUEr4uJOsy08bxuMmUwEEiFkAHK8Mr9dAd10bnYzfgdkP7g7RNxXGzb+HT+mk2KqJqnz3LECjGMsVJuVp5TZNUR8UiTSX05Hwt4nFTV/lTB7PY3HX27ydmP/9Hrz/XiwsvUfTq2oEv8+GdAeH1WQ6lyv3oWMuXLInbP/Tz7Mot207Thu5BSLA1tkOPHGcU=
*/