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
5MCiKJF2LG+fc5OONDXr5zrH6bUm9YZpJv6fmVw/w5YfQO38uO4T0sMNALFF0dU/egqZxjLcP/xqt0DYcpb0FLlIydNBmGKuWr7W0e0eG/ghelaZsE+I2SrzXvzmT59RMfY3tfAxtSs760y+S37xQD9UzCXLoK1VY27FlR9jTMQHjX+YLs4KVgxO5V1g17UOItBV+VXytZFd089a0sEo2UEU1stnp40VUJUkos2AXcK0e8H6nR2jNQHhjtus5+ersPGOpSa31PqgJtCUAejVZQLAHxuROObn/U7K7d+wbFlf2SGfDyYT0Zrsh/N+R4tVbcsMBqpOfqbSKXBS6Ov4hc/rhpqrqEWZdwbkAKh7dJJ26RR6hsqD8F5hix16RaccYWKsf+D8y7tSdVmWsIR60v9IuChoa7fV/ktxxPDDZpVMV8mpmKvXDo/josdgivtWUMFp+Jnu6eJ8xOVZb1whdlwY7WPBBGO5xqChDBnVBX7zU4oEsNww7I4Ab+JMG5WE1JNZxghttcThDfqHdDQxllQJQlQOKexsYfSTWvuTkEIppAXjiEtdq1BKnXvxL2qzAFRomtxffhJUHF3S5Klg8Aade/MEF3vqt4saJ9Uq65ZUdb0IVBrqAdzJ0nJZnB0CQOKBOLZzqg7DYNf3stQxmrvG1xcXf+bsroLa4LI4gLNIkSKlWHEttGiRosELFCvF3b1IcIfgUHRxJx/u
*/