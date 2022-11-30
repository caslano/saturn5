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
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
*/