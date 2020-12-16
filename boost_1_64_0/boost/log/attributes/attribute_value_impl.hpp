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
kLiTvNFt77p7YhzanT7PkvAxm66uQ+UaHXddkvzMNhVlT1WIeY28h1/J1vzMyZyTIXuKHqxTmB+mB7crvXC1S0qel4rbWJ0+MXN+niv+HFb2ZQkDe9sesTuVXXfsmos+p5IqswDlX6xKSZpqJ9Z9mX9oqMxnjOd/eVYt7tLQKyPPuPU+DB2XqUqnoj0sfUZsaxJVuzaukEY13GXkVUg+9i2Rd6o8KDMVR+LNNfG2lCNxxow42/a2RcjjgiriMYbq43cXpZysg5EaAqS8xqDDWa/OZ/d66irpcnE9vrJx3f7Ckxb8JZ6pXm1zWXnnfqlOoyJxpI+5flievumJtr77posSZpg4rIgsIG7hTYqGSfek0zrBj7R67ZUMKZr/CwknTodzk70EVP6n+c5/3P74/E+T/LfGMbSCc/6HN9JxtJXA9cOTMmAiYisDS7h5FYqWwSLil+yYN2qQKHE5dJawxkoHOFDGogHIhjr0W02832OpXZGpOZk5KbmzszMs77Nse65mKHc9jer8n4g4zit0Oem+Sc8L7ld2zXW//RgTnMdjrz+mOb3TIZ363IS4Sm7lN0lkDfg6XEKe5jukM2Oc2sOXkZsxnb6kSFr12NX0BtPtVNd4V1nHdOK3zP+k33DYU/iR0nnRdcDlOP5pP8LED+nndX5fVfa/dDUmtQ+5yqiw6gRJPz2eGxfpw69JH95BzSPGZ02fUjhWPKjSUUmFcZvl3V+YvNObpexbyTUpbmpeN7C838udwjinx5eqyr4XZVZNzDxumjPe1rLsW2XboOXd4XYVzjd8T/aGImFFcQ5EOnU1mUYx0TwHIiQ2NDDUq96rPeBVRC8XvUxTL2zBXt0fiE53rivJPvE70JmEbKeO7UTeR7qit0nmUrOj3e8fUzB7wk3M/XvneFfTYt85yn5b6fstdQNzVV6UI+a6HL3qc4zsNT8p7fYVZCX+1GnmWJ8nWWq0z/p8r3J7qzGMkJzqM37r+pxmq89OdVf0CQ99h7rbUNkfNdry/2E9l9H1SdfPLUqvqp4/5KvrCqpOtKEg08OpSapOlHeuE6K3LNxTJ0YVjhE2nd3oTFE68/fYdeScdFX+72C2hfoQH0mq6Lim1jb83pvuVAfSrHVAyrq3lHWBDJKLpawXIavMsm5etKx5OJKbOjVrSibjiuqvi1l70FC5v9sY56Ofxn9dfjMwcJmzYku5pCn7yg5l7+g23nr/N1nZV3SYuzu6TbC6na3sw53Oxhe3cs+txw//7ouKWxdAPDAj/fp+UpvFixlx0WYJ9vbKvEH9UhDPfr/VaOU7lCHffLSWoM/ye1e5HWl08lF++C3jrM5HXXZlWqg25Dzm/MR5GOadh151e0y0zAPLUL7CteZcp4VXvujzBGyDs+qLHrD1RbHSn6WZfpDUe5i5/RDUxugQ3MDYGNzJiFL3LhIGIb5gfBn0l+Cy1rzDzvmco1ipgztaufeFlzc+MMqyp7+lK804zEwgVsb1vyj3A/D1aMBbAe2MQYGtjY+DWhpRsq98l3K/ijOOPuJZVC3rPnxdvunKjx+C3wwuY7FPKzyTpqXa/x7cwXjGtSJgQMAnQUP1mQOfKbd9goON7KCdQeWMd4OSDBU3TO+LM+0yA+pT2qnGYL6/nuYaEBCq7zcrKH/bBkcRpup63M8JU9Iyc73Or+ip9Brodlk/3rwO0v30n9V1qBEla4z6mvrk9TbXLGMNmxJta430GQN3qLhfCbaPB7ESblPlT1RwZWardxij+f7708Zbrs6BnnALVLhVrfv99RxjvPL7WvAb5IxZd7ITMNTPYQvTFqXKBx3J685mmOTzS4y09SQfc5XOosAkyrAzZwfNdQ02Lrs=
*/