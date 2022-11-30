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
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
*/