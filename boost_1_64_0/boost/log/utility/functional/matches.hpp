/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   matches.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains a predicate for checking if the provided string matches a regular expression.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_MATCHES_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_MATCHES_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! The metafunction detects the matching expression kind and returns a tag that is used to specialize \c match_traits
template< typename ExpressionT, typename = void >
struct matching_expression_kind;

//! The matching function implementation
template< typename ExpressionT, typename TagT = typename matching_expression_kind< ExpressionT >::type >
struct match_traits;

} // namespace aux

//! The regex matching functor
struct matches_fun
{
    typedef bool result_type;

    template< typename StringT, typename ExpressionT >
    bool operator() (StringT const& str, ExpressionT const& expr) const
    {
        typedef aux::match_traits< ExpressionT > impl;
        return impl::matches(str, expr);
    }
    template< typename StringT, typename ExpressionT, typename ArgT >
    bool operator() (StringT const& str, ExpressionT const& expr, ArgT const& arg) const
    {
        typedef aux::match_traits< ExpressionT > impl;
        return impl::matches(str, expr, arg);
    }
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_MATCHES_HPP_INCLUDED_

/* matches.hpp
kC+zZedfZ8uO/wZbYj/DdnC3JdYXbXWzpWhLX2a7q+y5td6WLPbUSjaPfRjHgMxjMcaxIbMYza+Pbf3amMsyDyd/58RXlDorfjzYtPK9pq22jegL++0f2YD/1aLkV2YciV/13pYevUqPvDDWPHZmHEsyi3mZx7BOYLv1C0v7bkH8zLYexTN9S79MewfmZ+S//+Cn5wakZWxf/Nd5yc823edpFnsyj2GdR/5v1LonErp2fbmvZ9uesxsPvuvXx+DMYoXfaedWqvvFDaBPQmKxHYafEMfBbyy2Y7CXHAC0D9AQtkcaCrQf0NZAo4C2Y3xtb5at++1MrrZXyvaCJbYX7Am0u25vOoq9d4S9p9+brmTvHQHalcV0urOYzr0sBhQJ9HNNHlvbA73HQN5eJu9JoHWAHgLqD/QZVt8DrJ4HtZgVW6uyNfoNt5jVXCZvAdC7gC4C2hxoGWufx4AOBroF6BAWA4oBeh/QyUBXAp3G8iWyfEnsOZU9p7FYUQbjZzF+NtAHgZYw/gLGX8iey4BuYfXI09aDYGNWD19Iqaweo5jdRwP1BjoGqAp0MmunGKB1gY4F2gDoOKDNWCywLdAJQDsDnQS0B3uP+1seK7eFgb8BxfYbDNQX6BCgQUCHsnKGAQ0DOpy16wgtlsDWV2ytd8MtlrCdyd3F5DwOtBXQ3ez9Er5mAJrG3lchZbH3p7L2mM7aI4HplQi0BdAkFmNIZn6YAnQs0FSg8UBnMnumA01iz6ns+RuUw+Y5oPGsfG9sz+q/WZBPBpoD1AdoLtAmQPOAdgA6m7V3PtBooAUs9lkEdCrQYqCXWSziwuu1i0NULa6ORTRi8Yiy/2BMIrivKy6R+A/GJm5CUqJk6bNuXlp8IprFKPTxiYpfEaM4AemSLlYRcMw4XrESUrlbvOIW6OEes5jsFrfYwWIX11/30WIXt+D/1z/vI3WFFA+pDFI5pEOQzkK6AunW+Ttxizt/d/7u/N35u/N35+/O352/O393/v4b/v5D8f+coqysf1n8fz3G/50iE6oPAUgSxv/nh0tafLuZzTi+faWlFp+t1kqSaozj6PeoK1jcvIfEKIuFxlTLRaUMYqFGe9LwTu1jnTEtax/rhLxGsU6j2CbkrV0si8cvS1uK8cxC7dkzML3lvz8O2dXD7Y4Pi+td0LW/QRzSsP0v1LruNM6oxSwU7awl/sksJhWl02dmWu1jePCeWxwquWiGiU9EEf8pyJiXZuwTUbWsq0VcjsV+QB/3eAErVx9/veF2PqIxjxfr2sUq/lqB+Roax4r/sbqQ+OslT/aNRPZSAxZ/DXPp+Kvir/CecfyV1akZ/u5vaMuwf6xOtYqbXrMb+2iAq54YN63NmAXvGMVJjeoEeWsfEw2oZf3/0bikvj1uObQ5Af8UFmeUdO2BccZatIf0K+KK0q+IK0r/ZHtYx/b+v2N1bT+2Ab/D4peTpySeL9we//3CJz4MLL8Tq6spVsdiZ7CGMo+dAS1z0uZAPYG20MW6Yth7PQxiXQN0sZX6LDZzN4vNNGbPYeyZ6cHmb+ijBnp0YvL4vYxuuvei2HseBu9NZe/FA5WBTtP0Z/OOcaxOuw/SBqgv0LZAg4C2A9oAaHtWjw5MXhQf84E2ZPI8dXdFEpm8JKBeQFNZPVKYvFRdfQIs6tODyenJ6tNL957E3vM0eK8Pe68vUAVoP6AXWYwm+I07MZr/pRhNBNgrGlIqpFJIGyAdgHQG0uU37sRm/p///kP4PzstG+H/vwT/X9gkSbIEIl3wX/vtFv5WkJbi+hn3Bhbq7gaUyuzfGZAk7b5zq5awhmwm3A1wSgCwU732rxfgwmKh7LxZEeafLjWC/x1ufK4=
*/