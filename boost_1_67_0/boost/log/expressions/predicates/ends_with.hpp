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