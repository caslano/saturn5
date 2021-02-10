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
ato7qpulqQoZqZ10jwdPFLTK3uCoXrEQkqWQqgWSEivUELAtfDkEoD7fIBM8/EwIDDSTC4yNCQXrFVrJJeWtWDCuyVNmqBQKQZaydS6ihjMU+6CWTnA8kRKxeMLCOUcwRdKqhW+x39zu/uxeBZ3R8LJ/FVyPfu+BybNM4WCssyhCsGUeJpjTutHACpoUtWrDd2IgrKpAmgRWc8cLKjDmlDfd0IhW2g0XBVJZ0Dmu8AecGbQLgSJBPhlNXgfHV1ziaRdae4oIyoNN24R+6XRkKKYhc4OOrgXJlpWJSnCUU/WYRkmqLy452zq74kxxtzBLQDtVrEWaAo7ZOd9RTqqA2qF8ahXVr5vutDs3k0FBMebDUsh0XpiOz6BwcLuIq+JpLiIJFPWmiDrC+rEJQyVP10JGam3eOZdKIWT/qYmHvmdrj8fd9qy9h/DzkUftZtqbjCejy/6gd9/OcByH7pTwKresVjLqOe0XDV3OkYPGdxvY73pycj3r6PoI5bCobfmpVe1ODgftvg1FY4ELX5z9COqIzwJwB1kGVQWF1dRZsmJE1ms/mBp0+5Ogc92eAH3zXQq/OI4SzgGGOzQa9iiiCOFUxmU99GEUTLqj4eBuG7E/k8K9VdpQBBcf4WwfD71TZTia9lyP2KgWH73D
*/