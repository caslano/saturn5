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
V+LubErBubYk8CICf5biKfY4fmsZwTzY2s3lbsOTewqO/vS2Hd1GgzAB4gR72xOJwCRppfIcALwd5XlmhHYsFHy/aOHBe/3mgYdEEp72fQHvswFs+B0F790tHfjHFTzsA3GWty/T7DqJRudcdG34Jwreqwkd+K8V/Nbm14tVIR8uCMWV1+Bx+t/eqho04ee2hqAJP7d3NHgfR234xxq8j0M2fEcsgu3Hbe/piCNx2y8qpeRt57TgQwCz9sovEjZNjxW8f4pteC4SeG5WY9da8E8l/NNm8OSntWBVRqnPxXFkqEPw6J61w/O6vc7gEAUaQVFkl7H/wMNtQTEj8AjbxZU3Eu62oEjPRVF6j798LV7IcfjPR5xxD7VRtN+Hrl3gYNgTLdIyTmeAZnFUgiagNQpLr/PsbUFxAGzR9ns+botQtfAP3G0xUC0GcRq6kSW3RaRagPdGhzcLHJGXfOSzyVRsOA0sIuoSdodx5JzC1mDp8hmJ5kZ2LSxd4tcwrG3la0Mcwxbt8nbaJCjfpcjjZVQTtfNjGYk2NUg8WHj0MSwar5IuxR+j9DxOG67d7jnnF1qqjflFMcXpbFDHABcLxRTRK4ZWk5EbrXVb8LPHPKk56vfSdSn2DxmNWkxXIlogk6+z3FGpbouJaIHO
*/