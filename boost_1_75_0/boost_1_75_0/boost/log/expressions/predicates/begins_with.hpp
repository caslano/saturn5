/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   begins_with.hpp
 * \author Andrey Semashev
 * \date   02.09.2012
 *
 * The header contains implementation of a \c begins_with predicate in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_PREDICATES_BEGINS_WITH_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_PREDICATES_BEGINS_WITH_HPP_INCLUDED_

#include <boost/phoenix/core/actor.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/embedded_string_type.hpp>
#include <boost/log/detail/unary_function_terminal.hpp>
#include <boost/log/detail/attribute_predicate.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/fallback_policy.hpp>
#include <boost/log/expressions/attr_fwd.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/utility/functional/begins_with.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * The predicate checks if the attribute value begins with a substring. The attribute value is assumed to be of a string type.
 */
#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template< typename T, typename SubstringT, typename FallbackPolicyT = fallback_to_none >
using attribute_begins_with = aux::attribute_predicate< T, SubstringT, begins_with_fun, FallbackPolicyT >;

#else // !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template< typename T, typename SubstringT, typename FallbackPolicyT = fallback_to_none >
class attribute_begins_with :
    public aux::attribute_predicate< T, SubstringT, begins_with_fun, FallbackPolicyT >
{
    typedef aux::attribute_predicate< T, SubstringT, begins_with_fun, FallbackPolicyT > base_type;

public:
    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param substring The expected attribute value beginning
     */
    attribute_begins_with(attribute_name const& name, SubstringT const& substring) : base_type(name, substring)
    {
    }

    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param substring The expected attribute value beginning
     * \param arg Additional parameter for the fallback policy
     */
    template< typename U >
    attribute_begins_with(attribute_name const& name, SubstringT const& substring, U const& arg) : base_type(name, substring, arg)
    {
    }
};

#endif // !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value,
 * which is assumed to be a string, begins with the specified substring.
 */
template< typename T, typename FallbackPolicyT, typename TagT, template< typename > class ActorT, typename SubstringT >
BOOST_FORCEINLINE ActorT< aux::unary_function_terminal< attribute_begins_with< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type, FallbackPolicyT > > >
begins_with(attribute_actor< T, FallbackPolicyT, TagT, ActorT > const& attr, SubstringT const& substring)
{
    typedef aux::unary_function_terminal< attribute_begins_with< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type, FallbackPolicyT > > terminal_type;
    ActorT< terminal_type > act = {{ terminal_type(attr.get_name(), substring, attr.get_fallback_policy()) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value,
 * which is assumed to be a string, begins with the specified substring.
 */
template< typename DescriptorT, template< typename > class ActorT, typename SubstringT >
BOOST_FORCEINLINE ActorT< aux::unary_function_terminal< attribute_begins_with< typename DescriptorT::value_type, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > >
begins_with(attribute_keyword< DescriptorT, ActorT > const&, SubstringT const& substring)
{
    typedef aux::unary_function_terminal< attribute_begins_with< typename DescriptorT::value_type, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > terminal_type;
    ActorT< terminal_type > act = {{ terminal_type(DescriptorT::get_name(), substring) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value,
 * which is assumed to be a string, begins with the specified substring.
 */
template< typename T, typename SubstringT >
BOOST_FORCEINLINE phoenix::actor< aux::unary_function_terminal< attribute_begins_with< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > >
begins_with(attribute_name const& name, SubstringT const& substring)
{
    typedef aux::unary_function_terminal< attribute_begins_with< T, typename boost::log::aux::make_embedded_string_type< SubstringT >::type > > terminal_type;
    phoenix::actor< terminal_type > act = {{ terminal_type(name, substring) }};
    return act;
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_PREDICATES_BEGINS_WITH_HPP_INCLUDED_

/* begins_with.hpp
4fTR3ldO/HflLMkwqaXJjInf90oDsyr19jMV/Fh3sBNPpbb8KWXRyzyBl0ccXmwlTWguUwO5IpCB1+n7iPe31PkVRpJmA1MjPxckt83vRCaCTrjMNYKFu/R+N5R+awtSjC4mWPY5J054SL0SpIgdVTw1k7EZLQv3Z8C0klSOHil1/JDWw125+FkEdtG4tpPkPK82Puc2lwEJV0JnC8xzUVCbhQfTF6Tgervwjb2Z7RZidD8nilfv/wRHvJF+0/QItx+Qjc0mIAm7dTZwIcIN9gdD5yZ1RzFewQh0ZqvbtCzjCY27IpKO06jw+bij/SYURVdnRr4LOjCcDrpN/xs1J6GwdhNABuW44hrC3x+uRpoWp3uIw55jURt6XQ3hYnUf/O/XDsM+TFwxHFjMxyicjHMFvrw1gpSFewvhg8w3uRwU8DnwGrqIE+ZV0ISHGjTiff/pZHpVzRJi2mnn4uIqbF1h+htgswXK1/XqfjDfwiWmxMPuO84/4ogYfUZSpsv0S682DEX5npftLvywFWg+W3P4zXvD4SKRy1mBh8xO73Tx2T1M4WXeo+ZHadQx231X7lM8Hh56jFQ3FMVKFHzCAbVukdboqcnbsawBQtbZGIv8uNyjLYVIskJDRB5xMbkMQ6Vk9sNXHN5fnSQGJXuYb7YSe46+7uYKA13Rh0UN08sUGxg+fXez2voUZ+2rex6MWmOr8qPCszXfeAMy
*/