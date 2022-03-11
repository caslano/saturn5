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