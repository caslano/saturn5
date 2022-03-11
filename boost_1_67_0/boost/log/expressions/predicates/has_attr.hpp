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