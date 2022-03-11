/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attribute_predicate.hpp
 * \author Andrey Semashev
 * \date   02.09.2012
 *
 * The header contains implementation of a generic predicate in template expressions.
 */

#ifndef BOOST_LOG_DETAIL_ATTRIBUTE_PREDICATE_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_ATTRIBUTE_PREDICATE_HPP_INCLUDED_

#include <boost/phoenix/core/actor.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/value_visitation.hpp>
#include <boost/log/attributes/fallback_policy.hpp>
#include <boost/log/utility/functional/bind.hpp>
#include <boost/log/utility/functional/save_result.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace aux {

/*!
 * The predicate checks if the attribute value satisfies a predicate.
 */
template< typename T, typename ArgT, typename PredicateT, typename FallbackPolicyT = fallback_to_none >
class attribute_predicate
{
public:
    //! Function result_type
    typedef bool result_type;
    //! Expected attribute value type
    typedef T value_type;
    //! Predicate type
    typedef PredicateT predicate_type;
    //! Argument type for the predicate
    typedef ArgT argument_type;
    //! Fallback policy
    typedef FallbackPolicyT fallback_policy;

private:
    //! Argument for the predicate
    const argument_type m_arg;
    //! Attribute value name
    const attribute_name m_name;
    //! Visitor invoker
    value_visitor_invoker< value_type, fallback_policy > m_visitor_invoker;

public:
    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param pred_arg The predicate argument
     */
    attribute_predicate(attribute_name const& name, argument_type const& pred_arg) : m_arg(pred_arg), m_name(name)
    {
    }

    /*!
     * Initializing constructor
     *
     * \param name Attribute name
     * \param pred_arg The predicate argument
     * \param arg Additional parameter for the fallback policy
     */
    template< typename U >
    attribute_predicate(attribute_name const& name, argument_type const& pred_arg, U const& arg) : m_arg(pred_arg), m_name(name), m_visitor_invoker(arg)
    {
    }

    /*!
     * Checking operator
     *
     * \param arg A set of attribute values or a log record
     * \return \c true if the log record contains the sought attribute value, \c false otherwise
     */
    template< typename ArgumentT >
    result_type operator() (ArgumentT const& arg) const
    {
        typedef binder2nd< predicate_type, argument_type const& > visitor_type;

        bool res = false;
        m_visitor_invoker(m_name, arg, boost::log::save_result(visitor_type(predicate_type(), m_arg), res));
        return res;
    }
};

} // namespace aux

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_ATTRIBUTE_PREDICATE_HPP_INCLUDED_

/* attribute_predicate.hpp
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
*/