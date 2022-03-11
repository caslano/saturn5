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