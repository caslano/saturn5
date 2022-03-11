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