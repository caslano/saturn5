/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attribute_value_impl.hpp
 * \author Andrey Semashev
 * \date   24.06.2007
 *
 * The header contains an implementation of a basic attribute value implementation class.
 */

#ifndef BOOST_LOG_ATTRIBUTES_ATTRIBUTE_VALUE_IMPL_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_ATTRIBUTE_VALUE_IMPL_HPP_INCLUDED_

#include <boost/type_index.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute_value.hpp>
#include <boost/log/utility/type_dispatch/type_dispatcher.hpp>
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <boost/type_traits/remove_reference.hpp>
#endif
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace attributes {

/*!
 * \brief Basic attribute value implementation class
 *
 * This class can be used as a boilerplate for simple attribute values. The class implements all needed
 * interfaces of attribute values and allows to store a single value of the type specified as a template parameter.
 * The stored value can be dispatched with type dispatching mechanism.
 */
template< typename T >
class attribute_value_impl :
    public attribute_value::impl
{
public:
    //! Value type
    typedef T value_type;

private:
    //! Attribute value
    const value_type m_value;

public:
    /*!
     * Constructor with initialization of the stored value
     */
    explicit attribute_value_impl(value_type const& v) : m_value(v) {}
    /*!
     * Constructor with initialization of the stored value
     */
    explicit attribute_value_impl(BOOST_RV_REF(value_type) v) : m_value(boost::move(v)) {}

    /*!
     * Attribute value dispatching method.
     *
     * \param dispatcher The dispatcher that receives the stored value
     *
     * \return \c true if the value has been dispatched, \c false otherwise
     */
    virtual bool dispatch(type_dispatcher& dispatcher)
    {
        type_dispatcher::callback< value_type > callback = dispatcher.get_callback< value_type >();
        if (callback)
        {
            callback(m_value);
            return true;
        }
        else
            return false;
    }

    /*!
     * \return The attribute value type
     */
    typeindex::type_index get_type() const { return typeindex::type_id< value_type >(); }

    /*!
     * \return Reference to the contained value.
     */
    value_type const& get() const { return m_value; }
};

/*!
 * The function creates an attribute value from the specified object.
 */
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

template< typename T >
inline attribute_value make_attribute_value(T&& v)
{
    typedef typename remove_cv< typename remove_reference< T >::type >::type value_type;
    return attribute_value(new attribute_value_impl< value_type >(boost::forward< T >(v)));
}

#else // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

template< typename T >
inline attribute_value make_attribute_value(T const& v)
{
    typedef typename remove_cv< T >::type value_type;
    return attribute_value(new attribute_value_impl< value_type >(v));
}

template< typename T >
inline attribute_value make_attribute_value(rv< T > const& v)
{
    typedef typename remove_cv< T >::type value_type;
    return attribute_value(new attribute_value_impl< value_type >(v));
}

#endif // !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

} // namespace attributes

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_ATTRIBUTE_VALUE_IMPL_HPP_INCLUDED_

/* attribute_value_impl.hpp
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
*/