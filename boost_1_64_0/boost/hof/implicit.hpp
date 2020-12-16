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
HWslMj/0NJGXhNFrEQTbMtF+sfUF4ruAhUB7BbKJbq6iHyILj6EUVJJIQt78iq8WG4jfFshuK+GDlK69+JgpWpBCNksWgkJ8PHJJwBAo2Li8XrSXYQGvY9vOWWupmyC6w5m6kKkUcE6Ea6SCi0ugtatW5KkygqdCYqKvyr3pq0bXLC9jH0hEvJ+loJkYOlQKewyHyoLDsUpYF9A/vhnzBF0ZLSWdT7P3wJ0LUsIWnqRqzHWM/vH5f/qPiYVs4amWI7deFKvLQ5tGkz0ZH8Yqxq9XLKgDOVElBnOwC7V+I91+WNmvujy2ukD88nLFlGigZc4rbp7DeYcOfRKYTwcKp6IpR2mn0AptPxUrdEBrlit0U4OyObfpLCl9r51qxlqrYvnMWNppZmhQhZbI0BMXFU+k78EUwQ5l9XyWqQQqoiF24XzGFZGbd9LAu4HePS0H0bHHXg5MewbBzVOrK4ONU2dVBtfq55Trs8pL923MapCKizf1Nm3W6/Vl+tqyUBchb1tpZtBFZe21wwPI+0NC3rZpmUDeHxLynmmdVkXI+0NC3jNt06oIeX9IyHtmxrQqIO+GEbtRgnUpkPffQ/ukxQ+7ef97SeJ9xyel/ol9FlZl/Lxxv3GfnHFuwABfigPU5FlFV6sojw6ny4rOIAMcOXQCRPd/VivpzLMwLCuuIFKHT8YjZ9sXigGFSgZqEPNI1+aK5zcrZlc+hu6S1WrCtgMNJpb6rUvNUuHJcHZgVUPILTLkRLVbpP4UP8Cpsbwu36N8FRTuC1coAYztL0peZ66SNwWJzNOG5S70xvwEWmAQ0QKuq9VxxzbiiIY2cvBGBDsJ3f75KnX37xK59M92Bev1+mx9trH09yl1yNGzO770F7f2meaQS//41rnWaTXG0p/bOtc2rcZY+p2tczOm1WQEsnjoApHvRruO0omqnyU+udww9iVtcyueKNGn+P+ZuaPql5b/VyAa/an8Pw5H1ZLtCZbndqRNf9qsE0yfn2y/kXl8kSq7N1KNY/XbT1Mb9v6xdbmx9bli0Ub2AXrsgX6IXZSOfsAQ/2OF3Js6W75IS5jPR8N4bK3cwQmwXTcztbBonSICAskGiBeCHRMzA+v9pzNSrBOPg8EES/wwt18vfsfhbpOqyEGGXwskURWDiIwYSFSFy6QqBsSpivPrRd+LjiIrNO2zkxUp9Hiu8RF9mlLpcfQHBaw8JbnrUsMDRT2GI+N84yMeuDpd/giwHyt/hOekz1/tB50tpGrbJzzzONr021mM9Dr2q/bTevruBQo3Bbxi4XwZ7Ud0rjeZTkZoeew/fQSOsgNZbaV8b53ISd0KestmCWa1lbHf2BisE4ettMGYfpcVifNU4qzpwzPg5in4AeJaLYEfUTQ+Scdn6vHvwqf7dR2ekbwfs1+asv+7JNGt7J0GJohvr0S1mdj4Yo2q+lysrFYfDLiK8yRDnnb2Z0pG+BmifoJK8XkzhZtSMN/D5hUeM1HAQXVDOYdO5JJ/wk+4DbAcwqYK4b0kysnAA9CeBm4TPzpVRssVr1YbUmOBX8o4BMkdko8vvjmuO3ZMKzNtOzEfOxLclgnJ7p+muLUU9+sp7pLk/GJn5k+FqYtdZyiOwnCNPLxiCCDU9k0jEyaiD0PrSgMo2zfM7forRr/Jn+DNMX1Du3O94tI5CRfx0tsvRVyevEUeNbnSh58+Jzk8tTyK85E8weroKfyB44TPW5McrvDD9yenn7/EOjPSu/hB3MaxyWJDqe2V09UxLn175XhFac0JtleOyDj5GO2F8Fj1sduL4jw/8xjtgfCrjhOee2Wa9oK/fuaJtleOqPEcu71Kum4em769Sryib/UJtleJeHnMMdo=
*/