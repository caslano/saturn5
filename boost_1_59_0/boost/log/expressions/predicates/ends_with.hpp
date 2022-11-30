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
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
*/