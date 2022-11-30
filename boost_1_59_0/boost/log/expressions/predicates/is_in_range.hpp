/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   is_in_range.hpp
 * \author Andrey Semashev
 * \date   02.09.2012
 *
 * The header contains implementation of an \c is_in_range predicate in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_PREDICATES_IS_IN_RANGE_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_PREDICATES_IS_IN_RANGE_HPP_INCLUDED_

#include <utility>
#include <boost/phoenix/core/actor.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/embedded_string_type.hpp>
#include <boost/log/detail/unary_function_terminal.hpp>
#include <boost/log/detail/attribute_predicate.hpp>
#include <boost/log/expressions/attr_fwd.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/fallback_policy.hpp>
#include <boost/log/utility/functional/in_range.hpp>
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

template< typename T, typename BoundaryT, typename FallbackPolicyT = fallback_to_none >
using attribute_is_in_range = aux::attribute_predicate< T, std::pair< BoundaryT, BoundaryT >, in_range_fun, FallbackPolicyT >;

#else // !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template< typename T, typename BoundaryT, typename FallbackPolicyT = fallback_to_none >
class attribute_is_in_range :
    public aux::attribute_predicate< T, std::pair< BoundaryT, BoundaryT >, in_range_fun, FallbackPolicyT >
{
    typedef aux::attribute_predicate< T, std::pair< BoundaryT, BoundaryT >, in_range_fun, FallbackPolicyT > base_type;

public:
    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param boundaries The expected attribute value boundaries
     */
    attribute_is_in_range(attribute_name const& name, std::pair< BoundaryT, BoundaryT > const& boundaries) : base_type(name, boundaries)
    {
    }

    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param boundaries The expected attribute value boundaries
     * \param arg Additional parameter for the fallback policy
     */
    template< typename U >
    attribute_is_in_range(attribute_name const& name, std::pair< BoundaryT, BoundaryT > const& boundaries, U const& arg) : base_type(name, boundaries, arg)
    {
    }
};

#endif // !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value
 * is in the specified range. The range must be half-open, that is the predicate will be equivalent to <tt>least <= attr < most</tt>.
 */
template< typename T, typename FallbackPolicyT, typename TagT, template< typename > class ActorT, typename BoundaryT >
BOOST_FORCEINLINE ActorT< aux::unary_function_terminal< attribute_is_in_range< T, typename boost::log::aux::make_embedded_string_type< BoundaryT >::type, FallbackPolicyT > > >
is_in_range(attribute_actor< T, FallbackPolicyT, TagT, ActorT > const& attr, BoundaryT const& least, BoundaryT const& most)
{
    typedef typename boost::log::aux::make_embedded_string_type< BoundaryT >::type boundary_type;
    typedef aux::unary_function_terminal< attribute_is_in_range< T, boundary_type, FallbackPolicyT > > terminal_type;
    ActorT< terminal_type > act = {{ terminal_type(attr.get_name(), std::pair< boundary_type, boundary_type >(least, most), attr.get_fallback_policy()) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value
 * is in the specified range. The range must be half-open, that is the predicate will be equivalent to <tt>least <= attr < most</tt>.
 */
template< typename DescriptorT, template< typename > class ActorT, typename BoundaryT >
BOOST_FORCEINLINE ActorT< aux::unary_function_terminal< attribute_is_in_range< typename DescriptorT::value_type, typename boost::log::aux::make_embedded_string_type< BoundaryT >::type > > >
is_in_range(attribute_keyword< DescriptorT, ActorT > const&, BoundaryT const& least, BoundaryT const& most)
{
    typedef typename boost::log::aux::make_embedded_string_type< BoundaryT >::type boundary_type;
    typedef aux::unary_function_terminal< attribute_is_in_range< typename DescriptorT::value_type, boundary_type > > terminal_type;
    ActorT< terminal_type > act = {{ terminal_type(DescriptorT::get_name(), std::pair< boundary_type, boundary_type >(least, most)) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check if the attribute value
 * is in the specified range. The range must be half-open, that is the predicate will be equivalent to <tt>least <= attr < most</tt>.
 */
template< typename T, typename BoundaryT >
BOOST_FORCEINLINE phoenix::actor< aux::unary_function_terminal< attribute_is_in_range< T, typename boost::log::aux::make_embedded_string_type< BoundaryT >::type > > >
is_in_range(attribute_name const& name, BoundaryT const& least, BoundaryT const& most)
{
    typedef typename boost::log::aux::make_embedded_string_type< BoundaryT >::type boundary_type;
    typedef aux::unary_function_terminal< attribute_is_in_range< T, boundary_type > > terminal_type;
    phoenix::actor< terminal_type > act = {{ terminal_type(name, std::pair< boundary_type, boundary_type >(least, most)) }};
    return act;
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_PREDICATES_IS_IN_RANGE_HPP_INCLUDED_

/* is_in_range.hpp
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
*/