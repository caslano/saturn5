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
udxyTOnr4uJscplTXuUjaZ2Fi3Qo6fA2jiFXW3UUdABpr7vF/aO91+EfiFp0vr9JLn/A++NKhQt5fHwwjHe8PD4UES/o2ZHTCzh0tPXNoJ/K2sgwpQ9bcsA4U3TL7vv35DWs5fVRyVbt6VHkb8DD40LpB5j6qp31oHLoaK37bHeONt5252iXM/T290pX1vmuGSvtMXDYWr9aDhkDur/vU3FlMD0RXiuCeNmBsfjYLhHtPSH/SqLF23GHWGm1Sf9BZ09Hu0J01nMBV4h2WNAVot0Xgq4Q7TbX7g7t/q7dHdp7Z9yJrHjataFdD7ZrQ7ssviGBnd+Ae0ElfxzPgXoONx4D1by9z3e+JuG+d0A1jyuPgPKdrfdUfzae/ySev4Mt4b5HOklHvPrp/u5686uWtG0PfsLH99q3wqKxPfUJf/HOp/UP5ZVvuZ832xOfyJ6AB76VLs4vXwDvl0vK7XvXUzqR8qgX4M/5lPyHPOfVSH5db3kZTR/ykrdEZIM+8/H11aDDPFuXDTrMozB/jo5yCGfrYBEO3x4sFnfzoNk7inEWx23me3gTfVg8u1VachqCeFlIDm88Wh2UIyR0lgdxcr86hFcu3ux9gaCLN2fvwnLjZuNtN6Jqbvc9s0kfD3hkU3sNYS9sS6zyQt7XhMqrbNwtmeLvWwdkj5wDBOgsN221MWGv7nV1WMtFm423XbTZeiX7EbPksuOezddN
*/