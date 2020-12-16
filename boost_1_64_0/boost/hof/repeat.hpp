/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    repeat.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_REPEAT_H
#define BOOST_HOF_GUARD_REPEAT_H

/// repeat
/// ======
/// 
/// Description
/// -----------
/// 
/// The `repeat` function decorator will repeatedly apply a function a given
/// number of times.
/// 
/// 
/// Synopsis
/// --------
/// 
///     template<class Integral>
///     constexpr auto repeat(Integral);
/// 
/// Semantics
/// ---------
/// 
///     assert(repeat(std::integral_constant<int, 0>{})(f)(xs...) == f(xs...));
///     assert(repeat(std::integral_constant<int, 1>{})(f)(xs...) == f(f(xs...)));
///     assert(repeat(0)(f)(xs...) == f(xs...));
///     assert(repeat(1)(f)(xs...) == f(f(xs...)));
/// 
/// Requirements
/// ------------
/// 
/// Integral must be:
/// 
/// * Integral
/// 
/// Or:
/// 
/// * IntegralConstant
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     struct increment
///     {
///         template<class T>
///         constexpr T operator()(T x) const
///         {
///             return x + 1;
///         }
///     };
/// 
///     int main() {
///         auto increment_by_5 = boost::hof::repeat(std::integral_constant<int, 5>())(increment());
///         assert(increment_by_5(1) == 6);
///     }
/// 

#include <boost/hof/always.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/result_of.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/decorate.hpp>
#include <boost/hof/first_of.hpp>
#include <boost/hof/detail/recursive_constexpr_depth.hpp>

namespace boost { namespace hof { namespace detail {

template<int N>
struct repeater
{
    template<class F, class... Ts>
    constexpr BOOST_HOF_SFINAE_RESULT(repeater<N-1>, id_<const F&>, result_of<const F&, id_<Ts>...>) 
    operator()(const F& f, Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS
    (
        repeater<N-1>()(f, f(BOOST_HOF_FORWARD(Ts)(xs)...))
    );
};

template<>
struct repeater<0>
{
    template<class F, class T>
    constexpr T operator()(const F&, T&& x) const
    BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT(T(x))
    {
        return x;
    }
};

struct repeat_constant_decorator
{
    template<class Integral, class F, class... Ts>
    constexpr auto operator()(Integral, const F& f, Ts&&... xs) const BOOST_HOF_RETURNS
    (
        detail::repeater<Integral::type::value>()
        (
            f, 
            BOOST_HOF_FORWARD(Ts)(xs)...
        )
    );
};

template<int Depth>
struct repeat_integral_decorator
{
    template<class Integral, class F, class T, class... Ts, class Self=repeat_integral_decorator<Depth-1>>
    constexpr auto operator()(Integral n, const F& f, T&& x, Ts&&... xs) const BOOST_HOF_RETURNS
    (
        (n) ? 
            Self()(n-1, f, f(BOOST_HOF_FORWARD(T)(x), BOOST_HOF_FORWARD(Ts)(xs)...)) :
            BOOST_HOF_FORWARD(T)(x)
    );
};

template<>
struct repeat_integral_decorator<0>
{
    template<class Integral, class F, class T, class Self=repeat_integral_decorator<0>>
#if BOOST_HOF_HAS_RELAXED_CONSTEXPR
    constexpr
#endif
    auto operator()(Integral n, const F& f, T x) const 
    BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT((n--, f(BOOST_HOF_FORWARD(T)(x))))
    -> decltype(f(BOOST_HOF_FORWARD(T)(x)))
    {
        while(n > 0)
        {
            n--;
            x = f(BOOST_HOF_FORWARD(T)(x));
        }
        return x;
    }
    // TODO: Add overload for lvalue
};

}

#if BOOST_HOF_HAS_RELAXED_CONSTEXPR
#define BOOST_HOF_REPEAT_CONSTEXPR_DEPTH 1
#else
#define BOOST_HOF_REPEAT_CONSTEXPR_DEPTH BOOST_HOF_RECURSIVE_CONSTEXPR_DEPTH
#endif

BOOST_HOF_DECLARE_STATIC_VAR(repeat, decorate_adaptor<
    boost::hof::first_of_adaptor<
    detail::repeat_constant_decorator, 
    detail::repeat_integral_decorator<BOOST_HOF_REPEAT_CONSTEXPR_DEPTH>
>>);

}} // namespace boost::hof

#endif

/* repeat.hpp
Tyfsurxs0zKi1jRdspXav9XUH+Kl21PLx2b/IF6Z/d7bDWYavIyvzFSQ7DdZHkGOrfEq/2S9ApNkC4TbR8ueH83me9HRNdE6u/CvTxBj4fcjMFXmbmjvEZghfy4ILEHTTWHRO4dReMV5wAD86MHZx+QbhD7MQzTd+Jb/nSPmT1IrFY72VVTlsxEE1D/LqnchzZPaKzpiSCQGvsSuTbOxd2grpcxzfEBf1Q77UdXgCfczi8BezBllvFmvj99U60abAVoteJkIgGWu0k85QeAsn5gKWYVzkkHNKdL0B10yXi7VIvMiipJ2SFzerDvoM8KCa3jx6AhkpevaJ3nkMjh+Ll8maD2mKCpHpvfTpiR676pPoHfpCjO9p9ZJeh+/7oj03nfH16VXkssnWN1Abm4z/hG5kw1ywdvq6f6m+HtdAsk7GnWSQ1kyjAv5D2YNUDe8oAOD23qdpG002TV1hagjt99vIkntNzeRmLGN5vY7a55svwbtiO034NKv0X6o3iz/J5gTm+7D+8QDdVJMC+X789Vcwtq3Qa59oVDCxR6fWIfhQZ3iEx1XSiOxR9amv0iZsr5z4/VVJdT3qKwvM7m++5ep+hr1+iYctT65HgxbwYKYWg/YNgDc3MPLAPRXSmL8u2SYOq9xiCIwPCMF9YWk3TstYl17vwvnGu93yBJ/vx/L9zsxmPR+f5uj3u+eK+T7fTt6tPdj6oz9WcMt5v0ZfPXPkTIZLmpdruq/RV46+vHVjB6yjB7pW+uOU9IdtXwm+cvvMC5eFa7SmXv7uTj+gLsFch3vS1g1GiR8eftgWtjqDdWff4Xx0g2q0pGyUq9YJX1idM2OyujP2yYnrYfsGUI3ioFLyOFRUkXmyqUhFW/3U3lpIJzyBhzDxVU3pVxflT7NPgV5vtuYsjxgEv+klPi3ErzVlF9Y09YHuGn+epU5saLXvP9PhnN5NT7mmM1JVXm1/zfD4f9ndfL+0j81Tn8Ke6SIhc2QQoub3fM93kA3MdVLZl2bkSzeWEI/OSpiqMEw9tpzPv3kIGsTVtDPNfRzzRz6uY6Nya6nnzR6xD9xkuE/UIod/pbb6HnIKgLdiZ+65dQovc9RexuCb+NDRLS5/dL7zeX8Fbe8ubbJ+HWb8etO49dm4xfI44/48yVqVqw/hlGb/uP3T1X2f0tTjReGi7duOOJ43EN5/tCQqjzDpMHkklRwKa8qFzkeJa7SQ3UKfzns/2z+/nX6oFD+b6rFjTNSU7iV6k9IlbRmq/dJg9+NPYqR3zz+G9T4jvP38yCq1xgBV3JUUBqEzyJxgd0rku8bOwAuq0VGdqU1m7HXgNlZG+ILtxvFKEDMiJZue6AarKiR8WdWb+bDtGXXqAFw0lhgC+YyDnD6xdy8qCoL7piMiNIXtBIq+J2fSgnHfoHT7z/s/Zclvj9qT+T/15vnL+tjaUP+Q5CENnCuuons9Jjbc1ly71x5vREkMDwYLTAAKvZf85S9aKIKN2frRl6L8/0txNEbppGJlqNBqUdySCcT6k6bYug5OY6uT1BOXZvcONi/U5WDRPPbi7igbCetjcpIBfH10i/p15hZfn9ie0hJ2mG6b2nk8bSV8Y0vMVHmSxsvK4eG0DBtPBbyIf5b1Jv4H8Yf8cupKvBhjAYgNypusR+4Lt6mp5AHDm/sUW7SPhUqflMvNLUrOl7FWO7WCsGvtauKT/2zP3dFsv5zynR9vu8Kplx/CN5qyi9Wamn3k9yOf1qafD9ADqrg5MiTzCJDAyWacyWaKDNOyAgjNGb8yDmcDihDDr4LFXXzDWO2vP7lfCYSh28+cQkLOyQ4HcMukdcfUt4Fs3ELcmmS1bdyVVQbeSqJzJvXSjI=
*/