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