/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   ends_with.hpp
 * \author Andrey Semashev
 * \date   02.09.2012
 *
 * The header contains implementation of a \c ends_with predicate in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_PREDICATES_ENDS_WITH_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_PREDICATES_ENDS_WITH_HPP_INCLUDED_

#include <boost/phoenix/core/actor.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/embedded_string_type.hpp>
#include <boost/log/detail/unary_function_terminal.hpp>
#include <boost/log/detail/attribute_predicate.hpp>
#include <boost/log/expressions/attr_fwd.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/fallback_policy.hpp>
#include <boost/log/utility/functional/ends_with.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * The predicate checks if the attribute value ends with a substring. The attribute value is assumed to be of a string type.
 */
#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template< typename T, typename SubstringT, typename FallbackPolicyT = fallback_to_none >
using attribute_ends_with = aux::attribute_predicate< T, SubstringT, ends_with_fun, FallbackPolicyT >;

#else // !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template< typename T, typename SubstringT, typename FallbackPolicyT = fallback_to_none >
class attribute_ends_with :
    public aux::attribute_predicate< T, SubstringT, ends_with_fun, FallbackPolicyT >
{
    typedef aux::attribute_predicate< T, SubstringT, ends_with_fun, FallbackPolicyT > base_type;

public:
    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param substring The expected attribute value ending
     */
    attribute_ends_with(attribute_name const& name, SubstringT const& substring) : base_type(name, substring)
    {
    }

    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param substring The expected attribute value ending
     * \param arg Additional parameter for the fallback policy
     */
    template< typename U >
    attribute_ends_with(attribute_name const& name, SubstringT const& substring, U const& arg) : base_type(name, substring, arg)
    {
    }
};

#endif // !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value,
 * which is assumed to be a string, ends with the specified substring.
 */
template< typename T, typename FallbackPolicyT, typename TagT, template< typename > class ActorT, typename SubstringT >
BOOST_FORCEINLINE ActorT< aux::unary_function_terminal< attribute_ends_with< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type, FallbackPolicyT > > >
ends_with(attribute_actor< T, FallbackPolicyT, TagT, ActorT > const& attr, SubstringT const& substring)
{
    typedef aux::unary_function_terminal< attribute_ends_with< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type, FallbackPolicyT > > terminal_type;
    ActorT< terminal_type > act = {{ terminal_type(attr.get_name(), substring, attr.get_fallback_policy()) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value,
 * which is assumed to be a string, ends with the specified substring.
 */
template< typename DescriptorT, template< typename > class ActorT, typename SubstringT >
BOOST_FORCEINLINE ActorT< aux::unary_function_terminal< attribute_ends_with< typename DescriptorT::value_type, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > >
ends_with(attribute_keyword< DescriptorT, ActorT > const&, SubstringT const& substring)
{
    typedef aux::unary_function_terminal< attribute_ends_with< typename DescriptorT::value_type, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > terminal_type;
    ActorT< terminal_type > act = {{ terminal_type(DescriptorT::get_name(), substring) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value,
 * which is assumed to be a string, ends with the specified substring.
 */
template< typename T, typename SubstringT >
BOOST_FORCEINLINE phoenix::actor< aux::unary_function_terminal< attribute_ends_with< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > >
ends_with(attribute_name const& name, SubstringT const& substring)
{
    typedef aux::unary_function_terminal< attribute_ends_with< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > terminal_type;
    phoenix::actor< terminal_type > act = {{ terminal_type(name, substring) }};
    return act;
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_PREDICATES_ENDS_WITH_HPP_INCLUDED_

/* ends_with.hpp
lWaZZvdm/ub7zdebAz1ZvicI2OXCOy9PlrUdrfu/5X8ttHI2R3PoQkKfy6ml0z5fLxO3lawOb47yv4m8bQtZGG6izZlADi9QtdPftoa/UspVuTv89xdpT6nbV/YHc/PaH5y9racXeyCR1/sgaGmYGHuiU+0DmLuJ4p+HKIO4+k8bIvnS3nW08r507bE/dHhumXjQhh5HKB+ms3Cnue7s8rIg+xKONmaTb/Yc/foM3Ker3OS05X4XKTwT61m5UOPC7ev6ES5ESi0v2usSnn3XnXwkHQnqdKGoTqcfWExbkPU3yBeLhX3Ou5bExsW9I5il4u0l9sQQSbtl7Cocb1Msq85txY0e7enuuR8JFZynBX5ucx+PnN1WMiVL9e1jOfwVHik/krhkTziBO4ljw53G3erirGYp/gt/Am9Klrhxx8d0V33QsnnqufPzqefazZLNLjcBzWc2Tpw7kfBcvlnvpmoOe7mUP2+OoH/zUuTJFbebYjkSM+y7JyKe+xtWPJWo8E6SwYz3SRlOcGn6pbPvnI9ULFtrFp2RvPgccv5lfexfHDm8f3MYnZDPkbp6E/sJsVN77XGoGOJapSqfaad55MhrOY56k1gLV5k0ybeMXhtNUYnqL2/CYA90EW/CLiheV0h546bqnaDnTzNXcz/D0bvcnDPq5/D7qevEdeuppdvf2tRKgodOZ98x7nmspjeT0JGw8DSJzyyaMeAv
*/