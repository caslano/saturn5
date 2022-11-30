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
#include <boost/type_traits/is_nothrow_move_constructible.hpp>
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
    explicit attribute_value_impl(BOOST_RV_REF(value_type) v) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_constructible< value_type >::value) :
        m_value(boost::move(v))
    {
    }

    /*!
     * Attribute value dispatching method.
     *
     * \param dispatcher The dispatcher that receives the stored value
     *
     * \return \c true if the value has been dispatched, \c false otherwise
     */
    bool dispatch(type_dispatcher& dispatcher) BOOST_OVERRIDE
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
    typeindex::type_index get_type() const BOOST_OVERRIDE { return typeindex::type_id< value_type >(); }

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