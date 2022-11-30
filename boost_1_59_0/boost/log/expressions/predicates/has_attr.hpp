/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   has_attr.hpp
 * \author Andrey Semashev
 * \date   23.07.2012
 *
 * The header contains implementation of a generic attribute presence checker in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_PREDICATES_HAS_ATTR_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_PREDICATES_HAS_ATTR_HPP_INCLUDED_

#include <boost/phoenix/core/actor.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/attributes/value_visitation.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/detail/unary_function_terminal.hpp>
#include <boost/log/utility/functional/nop.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * An attribute value presence checker.
 */
template< typename T >
class has_attribute
{
public:
    //! Function result_type
    typedef bool result_type;
    //! Expected attribute value type
    typedef T value_type;

private:
    //! Attribute value name
    const attribute_name m_name;
    //! Visitor invoker
    value_visitor_invoker< value_type > m_visitor_invoker;

public:
    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     */
    explicit has_attribute(attribute_name const& name) : m_name(name)
    {
    }

    /*!
     * Checking operator
     *
     * \param arg A set of attribute values or a log record
     * \return \c true if the log record contains the sought attribute value, \c false otherwise
     */
    template< typename ArgT >
    result_type operator() (ArgT const& arg) const
    {
        return m_visitor_invoker(m_name, arg, nop()).code() == visitation_result::ok;
    }
};

/*!
 * An attribute value presence checker. This specialization does not check the type of the attribute value.
 */
template< >
class has_attribute< void >
{
public:
    //! Function result_type
    typedef bool result_type;
    //! Expected attribute value type
    typedef void value_type;

private:
    //! Attribute name
    const attribute_name m_name;

public:
    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     */
    explicit has_attribute(attribute_name const& name) : m_name(name)
    {
    }

    /*!
     * Checking operator
     *
     * \param attrs A set of attribute values
     * \return \c true if the log record contains the sought attribute value, \c false otherwise
     */
    result_type operator() (attribute_value_set const& attrs) const
    {
        return attrs.find(m_name) != attrs.end();
    }

    /*!
     * Checking operator
     *
     * \param rec A log record
     * \return \c true if the log record contains the sought attribute value, \c false otherwise
     */
    result_type operator() (boost::log::record_view const& rec) const
    {
        return operator()(rec.attribute_values());
    }
};

/*!
 * The function generates a terminal node in a template expression. The node will check for the attribute value
 * presence in a log record. The node will also check that the attribute value has the specified type, if present.
 */
template< typename AttributeValueT >
BOOST_FORCEINLINE phoenix::actor< aux::unary_function_terminal< has_attribute< AttributeValueT > > > has_attr(attribute_name const& name)
{
    typedef aux::unary_function_terminal< has_attribute< AttributeValueT > > terminal_type;
    phoenix::actor< terminal_type > act = {{ terminal_type(name) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check for the attribute value
 * presence in a log record.
 */
BOOST_FORCEINLINE phoenix::actor< aux::unary_function_terminal< has_attribute< void > > > has_attr(attribute_name const& name)
{
    typedef aux::unary_function_terminal< has_attribute< void > > terminal_type;
    phoenix::actor< terminal_type > act = {{ terminal_type(name) }};
    return act;
}

/*!
 * The function generates a terminal node in a template expression. The node will check for the attribute value
 * presence in a log record. The node will also check that the attribute value has the specified type, if present.
 */
template< typename DescriptorT, template< typename > class ActorT >
BOOST_FORCEINLINE ActorT< aux::unary_function_terminal< has_attribute< typename DescriptorT::value_type > > > has_attr(attribute_keyword< DescriptorT, ActorT > const&)
{
    typedef aux::unary_function_terminal< has_attribute< typename DescriptorT::value_type > > terminal_type;
    ActorT< terminal_type > act = {{ terminal_type(DescriptorT::get_name()) }};
    return act;
}

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_PREDICATES_HAS_ATTR_HPP_INCLUDED_

/* has_attr.hpp
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
*/