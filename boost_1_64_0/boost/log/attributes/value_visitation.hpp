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
sapF5gibYy76+PeRm5Dlv+mZdpVezyTOrBF1x+Us6QfEO9H5QreNcmJ/c4rsxDuRQ4rsxPuPJ4vsUDaqfmFEC2diUoKgZwUbg9Dr4aBlbg985o31mbi8Y661wSFzSdcu4F+v13NE+hi5ddS0C52/DOHvJLml6fQL8Gd9Nz4jTn7v+Sy5x9Jz9FiUh/ksnYkRKMk3YXm0XZDcqznkqfxq0fXjsnyafF5VOLmHkPxpyEfR9dOyfPzg+DSRnlvJ/U5Djh/uIrw+5B5D4a1CeKPountg0ZxgZBJyqIxLy1Y7xzhJJjkjQZVZvI6fiYtkUp0xq3L/yKP5lyzXJCPFXe6vHGdxuocnNoq1STHmjaR0LFTuQ7lkd0jMWxxt/geyOyjepYZPav+RXI5bqF6f8ytlfIT3C9fYIrltjqF0/WQvha8vn7DF2BzlOBvhPU/y9iCp3BPld6svkvtAKvcdkO9A5T4hUIo/fjDKNJbraR65v4qvb7+Kc+OTbGX8njDW+sXI6U2T5f9C8kf9bXjr5y3sDAj2W2qsZ3ku5zhrvVagvJSV6yI+IxmhWuoiYa3zvhQqy6WoMoeoPINkmURrG/nere7R1tLc6/5Fjq+c3N7i3dPVE3KWNpeC9LuFV43itattM3VwYhOLXDP38kjLSHSX+9saltPoqyLleSLJjYceoqddnp+vy+PnXZyzJz8HBFB+8u1y35bHGjvV8S3UhlZAvi5dzw9U6iVJTWs4pSFQqRdrOwhZZ60XyCS6l3cb93aQhBQqMv/kOpZlrGlau95tPIm3pqlvnptMglXm2BqSUdOd5l5ffUmujNKedPnLXm/N36g4a51uontTa9RjijIvPkJ18UtANeNogPyMs5/kI5zPQmy3a4P8DIo7H+ryQfIfHyjr/azjXTSNdxWU8e5hyluWMt6NJbs7RNtaj/D7k90gf296vrkUh7/ybF13PZ8HJsUxitrMSMxrDyl6iTSSvU8ep5Llcy0KneOkWQrnxUTzmFqd+l0v/1JGqq2D7UujsZ9zXJ2O8A6S/A/yOJki94mX4e76blcu5I/Q9Tdqn0iwzLOt9yrI6NrD0NWWdgM5Xfta/CynQWqr1n4RtU7TnhNVGb81ln4IGd34eHa1ZnzUjGcjud1LcaZY46y8QXPf1oy1M9e7yTVBnG5p2+c+xqfp7u9bNXK6PNQUY46of2X+9eQzRd+LXIj6X0nXlYIk+VS5/b1G7jdQW9+I9pdE5dkd7S/Z1s6Whb2CY6j95SC84yR/Tm5PcdYyjFvnvL8oMmmqTNYGN5kU63g2aq1bG0m1ykzXzbOS3Ms3Ik9TX5p748ccp1wPujbezn1sjLeOT6GOscOiM7pGZfsw7Ir0szZKWwdFB32J5F4N8KCzF+koJLkIZexdTWXbFbmoY8RKY++7JBsbUNr41P+8f4RhC6gg9EpDEOdc6rcNA2Ud8Zvk52wAy5F++lOyOxkg3ZcT5POtvqI20o/aYB7kW1K4uYGyPEpePAM0IvfXTHmMlOdyW8j9Ff8AjOvTjKa2AttZ41m/qspczjr/mrfWbf6Vah33ym5wa19p1vb143rul/p1DSE3nuq6rHKfaEZts4aii4+idL1hljXSRH07dHqDSLa/X1EZUCsW8+VOVAaH6azJY5AfQdffyHOjVPm5pim5R1Md5EO+K11v9FfKLFXNwztu/RbjbbIqU+De3xJ1c+QR3D9kOd3zz+3u/TJJNz5+/6zbPCrZOo+6RcwjJBlNnIZ7HtJ0clksJ683Wft4Y6r3MGUO8vJa8cwl5rgnya6Rsi7Xm8Ifrl1nEs8kVI5BSpytKM5YI1rSs/ekPvm2Pctoan/FHqTEHUNh3CrmJZs=
*/