/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   thread_specific.hpp
 * \author Andrey Semashev
 * \date   01.03.2008
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_THREAD_SPECIFIC_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_THREAD_SPECIFIC_HPP_INCLUDED_

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if !defined(BOOST_LOG_NO_THREADS)

#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! Base class for TLS to hide platform-specific storage management
class thread_specific_base
{
private:
#if defined(BOOST_THREAD_PLATFORM_WIN32)
    typedef unsigned long key_storage;
#else
    typedef void* key_storage;
#endif

    key_storage m_Key;

protected:
    BOOST_LOG_API thread_specific_base();
    BOOST_LOG_API ~thread_specific_base();
    BOOST_LOG_API void* get_content() const;
    BOOST_LOG_API void set_content(void* value) const;

    //  Copying prohibited
    BOOST_DELETED_FUNCTION(thread_specific_base(thread_specific_base const&))
    BOOST_DELETED_FUNCTION(thread_specific_base& operator= (thread_specific_base const&))
};

//! A TLS wrapper for small POD types with least possible overhead
template< typename T >
class thread_specific :
    public thread_specific_base
{
    BOOST_STATIC_ASSERT_MSG(sizeof(T) <= sizeof(void*) && is_pod< T >::value, "Boost.Log: Thread-specific values must be PODs and must not exceed the size of a pointer");

    //! Union to perform type casting
    union value_storage
    {
        void* as_pointer;
        T as_value;
    };

public:
    //! Default constructor
    BOOST_DEFAULTED_FUNCTION(thread_specific(), {})
    //! Initializing constructor
    thread_specific(T const& value)
    {
        set(value);
    }
    //! Assignment
    thread_specific& operator= (T const& value)
    {
        set(value);
        return *this;
    }

    //! Accessor
    T get() const
    {
        value_storage cast = {};
        cast.as_pointer = thread_specific_base::get_content();
        return cast.as_value;
    }

    //! Setter
    void set(T const& value)
    {
        value_storage cast = {};
        cast.as_value = value;
        thread_specific_base::set_content(cast.as_pointer);
    }
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // !defined(BOOST_LOG_NO_THREADS)

#endif // BOOST_LOG_DETAIL_THREAD_SPECIFIC_HPP_INCLUDED_

/* thread_specific.hpp
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
*/