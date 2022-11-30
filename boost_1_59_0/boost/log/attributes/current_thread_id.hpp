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
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
*/