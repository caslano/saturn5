/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   value_visitation.hpp
 * \author Andrey Semashev
 * \date   01.03.2008
 *
 * The header contains implementation of convenience tools to apply visitors to an attribute value
 * in the view.
 */

#ifndef BOOST_LOG_ATTRIBUTES_VALUE_VISITATION_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_VALUE_VISITATION_HPP_INCLUDED_

#include <boost/core/explicit_operator_bool.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/exceptions.hpp>
#include <boost/log/core/record.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/attribute_value.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/attributes/value_visitation_fwd.hpp>
#include <boost/log/attributes/fallback_policy.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/utility/type_dispatch/static_type_dispatcher.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief The class represents attribute value visitation result
 *
 * The main purpose of this class is to provide a convenient interface for checking
 * whether the attribute value visitation succeeded or not. It also allows to discover
 * the actual cause of failure, should the operation fail.
 */
class visitation_result
{
public:
    //! Error codes for attribute value visitation
    enum error_code
    {
        ok,                     //!< The attribute value has been visited successfully
        value_not_found,        //!< The attribute value is not present in the view
        value_has_invalid_type  //!< The attribute value is present in the view, but has an unexpected type
    };

private:
    error_code m_code;

public:
    /*!
     * Initializing constructor. Creates the result that is equivalent to the
     * specified error code.
     */
    BOOST_CONSTEXPR visitation_result(error_code code = ok) BOOST_NOEXCEPT : m_code(code) {}

    /*!
     * Checks if the visitation was successful.
     *
     * \return \c true if the value was visited successfully, \c false otherwise.
     */
    BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()
    /*!
     * Checks if the visitation was unsuccessful.
     *
     * \return \c false if the value was visited successfully, \c true otherwise.
     */
    bool operator! () const BOOST_NOEXCEPT { return (m_code != ok); }

    /*!
     * \return The actual result code of value visitation
     */
    error_code code() const BOOST_NOEXCEPT { return m_code; }
};

/*!
 * \brief Generic attribute value visitor invoker
 *
 * Attribute value invoker is a functional object that attempts to find and extract the stored
 * attribute value from the attribute value view or a log record. The extracted value is passed to
 * a unary function object (the visitor) provided by user.
 *
 * The invoker can be specialized on one or several attribute value types that should be
 * specified in the second template argument.
 */
template< typename T, typename FallbackPolicyT >
class value_visitor_invoker :
    private FallbackPolicyT
{
    typedef value_visitor_invoker< T, FallbackPolicyT > this_type;

public:
    //! Attribute value types
    typedef T value_type;

    //! Fallback policy
    typedef FallbackPolicyT fallback_policy;

    //! Function object result type
    typedef visitation_result result_type;

public:
    /*!
     * Default constructor
     */
    BOOST_DEFAULTED_FUNCTION(value_visitor_invoker(), {})

    /*!
     * Copy constructor
     */
    value_visitor_invoker(value_visitor_invoker const& that) : fallback_policy(static_cast< fallback_policy const& >(that))
    {
    }

    /*!
     * Initializing constructor
     *
     * \param arg Fallback policy argument
     */
    template< typename U >
    explicit value_visitor_invoker(U const& arg) : fallback_policy(arg) {}

    /*!
     * Visitation operator. Attempts to acquire the stored value of one of the supported types. If acquisition succeeds,
     * the value is passed to \a visitor.
     *
     * \param attr An attribute value to apply the visitor to.
     * \param visitor A receiving function object to pass the attribute value to.
     * \return The result of visitation.
     */
    template< typename VisitorT >
    result_type operator() (attribute_value const& attr, VisitorT visitor) const
    {
        if (!!attr)
        {
            static_type_dispatcher< value_type > disp(visitor);
            if (attr.dispatch(disp) || fallback_policy::apply_default(visitor))
            {
                return visitation_result::ok;
            }
            else
            {
                fallback_policy::on_invalid_type(attr.get_type());
                return visitation_result::value_has_invalid_type;
            }
        }

        if (fallback_policy::apply_default(visitor))
            return visitation_result::ok;

        fallback_policy::on_missing_value();
        return visitation_result::value_not_found;
    }

    /*!
     * Visitation operator. Looks for an attribute value with the specified name
     * and tries to acquire the stored value of one of the supported types. If acquisition succeeds,
     * the value is passed to \a visitor.
     *
     * \param name Attribute value name.
     * \param attrs A set of attribute values in which to look for the specified attribute value.
     * \param visitor A receiving function object to pass the attribute value to.
     * \return The result of visitation.
     */
    template< typename VisitorT >
    result_type operator() (attribute_name const& name, attribute_value_set const& attrs, VisitorT visitor) const
    {
        try
        {
            attribute_value_set::const_iterator it = attrs.find(name);
            if (it != attrs.end())
                return operator() (it->second, visitor);
            else
                return operator() (attribute_value(), visitor);
        }
        catch (exception& e)
        {
            // Attach the attribute name to the exception
            boost::log::aux::attach_attribute_name_info(e, name);
            throw;
        }
    }

    /*!
     * Visitation operator. Looks for an attribute value with the specified name
     * and tries to acquire the stored value of one of the supported types. If acquisition succeeds,
     * the value is passed to \a visitor.
     *
     * \param name Attribute value name.
     * \param rec A log record. The attribute value will be sought among those associated with the record.
     * \param visitor A receiving function object to pass the attribute value to.
     * \return The result of visitation.
     */
    template< typename VisitorT >
    result_type operator() (attribute_name const& name, record const& rec, VisitorT visitor) const
    {
        return operator() (name, rec.attribute_values(), visitor);
    }

    /*!
     * Visitation operator. Looks for an attribute value with the specified name
     * and tries to acquire the stored value of one of the supported types. If acquisition succeeds,
     * the value is passed to \a visitor.
     *
     * \param name Attribute value name.
     * \param rec A log record view. The attribute value will be sought among those associated with the record.
     * \param visitor A receiving function object to pass the attribute value to.
     * \return The result of visitation.
     */
    template< typename VisitorT >
    result_type operator() (attribute_name const& name, record_view const& rec, VisitorT visitor) const
    {
        return operator() (name, rec.attribute_values(), visitor);
    }

    /*!
     * \returns Fallback policy
     */
    fallback_policy const& get_fallback_policy() const
    {
        return *static_cast< fallback_policy const* >(this);
    }
};

/*!
 * The function applies a visitor to an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be visited.
 *
 * \param name The name of the attribute value to visit.
 * \param attrs A set of attribute values in which to look for the specified attribute value.
 * \param visitor A receiving function object to pass the attribute value to.
 * \return The result of visitation.
 */
template< typename T, typename VisitorT >
inline visitation_result
visit(attribute_name const& name, attribute_value_set const& attrs, VisitorT visitor)
{
    value_visitor_invoker< T > invoker;
    return invoker(name, attrs, visitor);
}

/*!
 * The function applies a visitor to an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be visited.
 *
 * \param name The name of the attribute value to visit.
 * \param rec A log record. The attribute value will be sought among those associated with the record.
 * \param visitor A receiving function object to pass the attribute value to.
 * \return The result of visitation.
 */
template< typename T, typename VisitorT >
inline visitation_result
visit(attribute_name const& name, record const& rec, VisitorT visitor)
{
    value_visitor_invoker< T > invoker;
    return invoker(name, rec, visitor);
}

/*!
 * The function applies a visitor to an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be visited.
 *
 * \param name The name of the attribute value to visit.
 * \param rec A log record view. The attribute value will be sought among those associated with the record.
 * \param visitor A receiving function object to pass the attribute value to.
 * \return The result of visitation.
 */
template< typename T, typename VisitorT >
inline visitation_result
visit(attribute_name const& name, record_view const& rec, VisitorT visitor)
{
    value_visitor_invoker< T > invoker;
    return invoker(name, rec, visitor);
}

/*!
 * The function applies a visitor to an attribute value. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be visited.
 *
 * \param value The attribute value to visit.
 * \param visitor A receiving function object to pass the attribute value to.
 * \return The result of visitation.
 */
template< typename T, typename VisitorT >
inline visitation_result
visit(attribute_value const& value, VisitorT visitor)
{
    value_visitor_invoker< T > invoker;
    return invoker(value, visitor);
}

/*!
 * The function applies a visitor to an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be visited.
 *
 * \param keyword The keyword of the attribute value to visit.
 * \param attrs A set of attribute values in which to look for the specified attribute value.
 * \param visitor A receiving function object to pass the attribute value to.
 * \return The result of visitation.
 */
template< typename DescriptorT, template< typename > class ActorT, typename VisitorT >
inline visitation_result
visit(expressions::attribute_keyword< DescriptorT, ActorT > const& keyword, attribute_value_set const& attrs, VisitorT visitor)
{
    value_visitor_invoker< typename DescriptorT::value_type > invoker;
    return invoker(keyword.get_name(), attrs, visitor);
}

/*!
 * The function applies a visitor to an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be visited.
 *
 * \param keyword The keyword of the attribute value to visit.
 * \param rec A log record. The attribute value will be sought among those associated with the record.
 * \param visitor A receiving function object to pass the attribute value to.
 * \return The result of visitation.
 */
template< typename DescriptorT, template< typename > class ActorT, typename VisitorT >
inline visitation_result
visit(expressions::attribute_keyword< DescriptorT, ActorT > const& keyword, record const& rec, VisitorT visitor)
{
    value_visitor_invoker< typename DescriptorT::value_type > invoker;
    return invoker(keyword.get_name(), rec, visitor);
}

/*!
 * The function applies a visitor to an attribute value from the view. The user has to explicitly specify the
 * type or set of possible types of the attribute value to be visited.
 *
 * \param keyword The keyword of the attribute value to visit.
 * \param rec A log record view. The attribute value will be sought among those associated with the record.
 * \param visitor A receiving function object to pass the attribute value to.
 * \return The result of visitation.
 */
template< typename DescriptorT, template< typename > class ActorT, typename VisitorT >
inline visitation_result
visit(expressions::attribute_keyword< DescriptorT, ActorT > const& keyword, record_view const& rec, VisitorT visitor)
{
    value_visitor_invoker< typename DescriptorT::value_type > invoker;
    return invoker(keyword.get_name(), rec, visitor);
}


#if !defined(BOOST_LOG_DOXYGEN_PASS)

template< typename T, typename VisitorT >
inline visitation_result attribute_value::visit(VisitorT visitor) const
{
    return boost::log::visit< T >(*this, visitor);
}

#endif // !defined(BOOST_LOG_DOXYGEN_PASS)

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_VALUE_VISITATION_HPP_INCLUDED_

/* value_visitation.hpp
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
*/