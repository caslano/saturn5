/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   contains.hpp
 * \author Andrey Semashev
 * \date   02.09.2012
 *
 * The header contains implementation of a \c contains predicate in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_PREDICATES_CONTAINS_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_PREDICATES_CONTAINS_HPP_INCLUDED_

#include <boost/phoenix/core/actor.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/embedded_string_type.hpp>
#include <boost/log/detail/unary_function_terminal.hpp>
#include <boost/log/detail/attribute_predicate.hpp>
#include <boost/log/expressions/attr_fwd.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/fallback_policy.hpp>
#include <boost/log/utility/functional/contains.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * The predicate checks if the attribute value contains a substring. The attribute value is assumed to be of a string type.
 */
#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template< typename T, typename SubstringT, typename FallbackPolicyT = fallback_to_none >
using attribute_contains = aux::attribute_predicate< T, SubstringT, contains_fun, FallbackPolicyT >;

#else // !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template< typename T, typename SubstringT, typename FallbackPolicyT = fallback_to_none >
class attribute_contains :
    public aux::attribute_predicate< T, SubstringT, contains_fun, FallbackPolicyT >
{
    typedef aux::attribute_predicate< T, SubstringT, contains_fun, FallbackPolicyT > base_type;

public:
    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param substring The expected attribute value substring
     */
    attribute_contains(attribute_name const& name, SubstringT const& substring) : base_type(name, substring)
    {
    }

    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param substring The expected attribute value substring
     * \param arg Additional parameter for the fallback policy
     */
    template< typename U >
    attribute_contains(attribute_name const& name, SubstringT const& substring, U const& arg) : base_type(name, substring, arg)
    {
    }
};

#endif // !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value,
 * which is assumed to be a string, contains the specified substring.
 */
template< typename T, typename FallbackPolicyT, typename TagT, template< typename > class ActorT, typename SubstringT >
BOOST_FORCEINLINE ActorT< aux::unary_function_terminal< attribute_contains< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type, FallbackPolicyT > > >
contains(attribute_actor< T, FallbackPolicyT, TagT, ActorT > const& attr, SubstringT const& substring)
{
    typedef aux::unary_function_terminal< attribute_contains< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type, FallbackPolicyT > > terminal_type;
    ActorT< terminal_type > act = {{ terminal_type(attr.get_name(), substring, attr.get_fallback_policy()) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value,
 * which is assumed to be a string, contains the specified substring.
 */
template< typename DescriptorT, template< typename > class ActorT, typename SubstringT >
BOOST_FORCEINLINE ActorT< aux::unary_function_terminal< attribute_contains< typename DescriptorT::value_type, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > >
contains(attribute_keyword< DescriptorT, ActorT > const&, SubstringT const& substring)
{
    typedef aux::unary_function_terminal< attribute_contains< typename DescriptorT::value_type, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > terminal_type;
    ActorT< terminal_type > act = {{ terminal_type(DescriptorT::get_name(), substring) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value,
 * which is assumed to be a string, contains the specified substring.
 */
template< typename T, typename SubstringT >
BOOST_FORCEINLINE phoenix::actor< aux::unary_function_terminal< attribute_contains< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > >
contains(attribute_name const& name, SubstringT const& substring)
{
    typedef aux::unary_function_terminal< attribute_contains< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > terminal_type;
    phoenix::actor< terminal_type > act = {{ terminal_type(name, substring) }};
    return act;
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_PREDICATES_CONTAINS_HPP_INCLUDED_

/* contains.hpp
r2+8JXMTk5z7Ts84bektr2VNHnx/3l/vbvg5Jft6SOxzR/a5j9hzKPY5l1hzJQ0/12S/dzPWnEvD7+P8PnMr+Y7KupaBOyPm41/VuZUEhLYJmAjuA3tBueoOEnd+qIO6S4bPxWbgOCzO/jo1rj3Ttnl+s39a5/vXgKE5f4j3HaDup2b+P3pPta4FmH3Vtada91XLukAHMHxfte6pjlgv2AWuAm33pOj6gdljXTLeus/arClUgHngSlDXFsy+a9uea703pa4912YtInGEfT1C92KbdYnhI2RtQvdlmzUKvVvFtlZh36fN2kXUPu03ocB6Rv17tfWuFdY5Qnu2q5Cf1Y3zZY1P49P4ND6NT+PT+DQ+//bn373+P7fcpeLyubPmlv4Q6//u+P7ezgyWg3uhdd/3Bkj2SkOlgxnzvBkY3588oXjMPAlMacloVOiiB0vegnsSpw123RFE3tvp/tjW4va3zCGgfRC61rpPVr+h+0x3i96W2aWL7PtkDW8mvAsd5ZUdoPa9sl6/52aIvjEUzVQYHagni/0i53BCMtnxW/bQ2vyQ/arWPbOG14Rv+pypM8qFN8fDmyO8kbpRF5hzFI+KXbPgN3ncYONe9dncIva9SJMEp53eJ7DDz/ld8jRhRFrvJH96a9LL7KFf11kUQ4h/c7JFD/X8cs9e3jPEv45Gp+5iec8Q/TFd8CPZPQuMH0ic+HM/vx+A1kMPdq5f721wr6krJ61FTkJ7gN08b615nq17gBdCrU3ehvYBu2nRWvNQ9wFjFr6HOCfoXtOeXDVyvq6J0Zchz89cXsLk/C2GnJcG3uDQvDD7ra2yjD9GPo9pKWViVtlMCpxdnuG3yL5dluGNKfs2uYXfKotGhgrF/lj2P/qtsux1T77xSL4Z/b99xL7EyeV/MdQJOUlyAvLxUOeAjDwMbYAe6Vy/HlyVEc1PSWOjC5m0xEzTUnnTLbKTEUN2sqJlwsxtvqmTmp00MB2hS4nvJiMT5hhIXDKwKZRPuudepjHnzSqxy8Amez5ZZUB5zRmqqjj2S8VOV91Db8Kn6WpJq76aVjNxJAiJfgvoMtJqr0kr0bAe2SYYmflc+CY5/fg/2t4e4Je1vrXrrm1A2sEbs7496S3s4LLUt1Kf5It9D77pVzkPqw9NXfj3lvHLuaUuDK/L7Hlhzg6s1GmeoZoXx0JL8LPqrbC8KJ7Grr2K0vjqL9za0tO0E9Vin2XLC9xa6wtzXmaF2B/p5r3Z9/eoqR/iP99l5NikW+yyXakN0aeaRnuhZYStxqSR6clEyWwnDffrwvuW6cfcBr0AWXXJedJgstT/ZUZXfktwytuufXf2xSfY9W170zDQfqAa2NoewGvt25g7KprJt+6Xvs1sUuVae/8Gf+Lv39S8FX//Bt6Y5e2Bt+vu39yAvbd/U52KnKR9//5Nm7fD+zdD5T0tZv/msR+wf4McYKZyoGV6mmsmeXvofZvg2bayFiFZbw59Al3hlsPaSFl3Nff2L6aFjJR5e5+m1nverM7+ObwN65/DH9H/oRXS9iIbzBf7R5xypyu6ZxLs/ZzaCJnEDz5p79PURsmkaZsWi90czqj0p5wnevU9mrtn2gvPducuUv45yP1mj8HizyxvXdfW5YNrGr41R0QOcrdJrpi9Im6WdQ+40bhKvh4t9vc65xPXO50m2vb4NA2ucVKxccvCYhJuFRm8sTNp6GufntIk3bcwPcWvZQH9kR4dksq/Af7H5d6f/Cj9kH14T+X9CeyfhDZBT0FPKyZJmQj1NRK9+iIbUA5yE+Pv50u/jnyM6r9p3nr79JtVp/5aSHTKQzfw/fx37HJfNrW8/KL5C0osY1eTf4PF7UqnwK4=
*/