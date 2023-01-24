/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   current_thread_id.hpp
 * \author Andrey Semashev
 * \date   12.09.2009
 *
 * The header contains implementation of a current thread id attribute
 */

#ifndef BOOST_LOG_ATTRIBUTES_CURRENT_THREAD_ID_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_CURRENT_THREAD_ID_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_LOG_NO_THREADS)
#error Boost.Log: The current_thread_id attribute is only available in multithreaded builds
#endif

#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/log/detail/thread_id.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_cast.hpp>
#include <boost/log/attributes/attribute_value_impl.hpp>
#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! Thread identifier type
typedef boost::log::aux::thread::id thread_id;

namespace attributes {

/*!
 * \brief A class of an attribute that always returns the current thread identifier
 *
 * \note This attribute can be registered globally, it will still return the correct
 *       thread identifier, no matter which thread emits the log record.
 */
class current_thread_id :
    public attribute
{
public:
    //! A held attribute value type
    typedef thread_id value_type;

protected:
    //! Factory implementation
    class BOOST_SYMBOL_VISIBLE impl :
        public attribute_value::impl
    {
    public:
        bool dispatch(type_dispatcher& dispatcher)
        {
            type_dispatcher::callback< value_type > callback =
                dispatcher.get_callback< value_type >();
            if (callback)
            {
                callback(boost::log::aux::this_thread::get_id());
                return true;
            }
            else
                return false;
        }

        intrusive_ptr< attribute_value::impl > detach_from_thread()
        {
            typedef attribute_value_impl< value_type > detached_value;
            return new detached_value(boost::log::aux::this_thread::get_id());
        }

        typeindex::type_index get_type() const { return typeindex::type_id< value_type >(); }
    };

public:
    /*!
     * Default constructor
     */
    current_thread_id() : attribute(new impl())
    {
    }
    /*!
     * Constructor for casting support
     */
    explicit current_thread_id(cast_source const& source) :
        attribute(source.as< impl >())
    {
    }
};

} // namespace attributes

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_CURRENT_THREAD_ID_HPP_INCLUDED_

/* current_thread_id.hpp
nRqPJST9aszd+1GRE3k3Xv5ZT29+0l+9ewFF94LKeBH99ObzL1Ol+hwv93s7ZgnXqqzhysjC3HtKGECbWGKjZ4f98rTVo3DRktlnUzyGYr2o+aJD3KQlaOANP7MQtykdHUB8WVJY1O4TSVFYdHtVflGUocKfhNYklHXej49OO8oCOMcreIyzB9P27G2LVgIbvosQMkVfNUoqhY8bHiWH4ieWxZc0P8TZzcaJua2MjJwGGyUmH7tJMrR9JtyR8arC/qJjhXnXyGtpGvsuQepGy6QY6LdX5twqr5pFrHI0VLyy8Pyp1SNXGUxh79SBSKIxWUinjr1/al0/4R8AWTCkZboxzXSSJ5S8PrI3v5N/eDs/3XeR0uFl7DfUkfRzrzp7gMhcuMGBYv6NSXioeje3DZ0RWUx/L4/52gcm29/qM9LANp2JPzKcdvWr5RhJyX+WZmVQPlkpQjLt7o47/7oYhyruS6pncK/ehP9ER1L/tZimOS9dE3vl8UYcL7V2KSmWnszCTaBJoIr4CZx+1hrnEKcgKoL0SiqNW1tc6052TdkNVmb+1wPSZT5muQs+U1Rb+jEdZDq2wOCdlJbm15bDSfqnJ5llTawl7UX/H6ocjiaMrrwr33Ymmr7qcP42BEKqGh473aRNqaxWRHN0ooydaU/0I2xv1ZkN5pTBcwW3fyQYdG7exiGDPp7zbmQr3Hu2WTt9hx8X1zXG7M6q
*/