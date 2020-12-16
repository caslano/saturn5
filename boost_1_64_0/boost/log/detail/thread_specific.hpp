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
8Gl4IdwI28MX4EVwG+wAX4UXw10wH74BO8K34WXwQ9gVfgO76T1ResIvYW8YhV31KhgHB8JkeAvMhFfDQngNPAFHwHjadSQsC2XcAY6G1eAYWBOOhbXhONgAToaZcApsD6fCq+AtsDX94XZYCMW+D2fDh+EcuAougDvhPfAQ/CPM5XraNLfVNbiFuF24U7hM7Lp9cffgauEPXE/pQdzzuB24vbgK2HfPxbXHdcPJeku4BOy9abiWuE64vrhxuMe1LfgQ7gSugbYJT4OrcVtw+3BHcP0vIA5uJu5B3ErcDtxxXFob4uIG4cbhbsPdgzuOc2NDzsBl4trghuGmabtyGq4Brg2uG2467nncDtxevSZUe9wo3DTcXNwW3G7cPlzG/6jN+ezo/01zz9T6fy8Q1/fddb7e1857X6bDWNjc+901Dxyt/0vefgtAiA3AfNN2y00yh8joaVPE/y7vfvPU0yrVSU+XfBznSeo0Z8n5D8Sfhv8GSfNTM892jM4jgV8O33vurZMlDFV0r5Nur/N01rsrSb46DLXSiryzrbdMfN85Zz3cQW/X4R3nQWqdYoacf9WqykjTR8Qoa3V30NeD0xkndRWsFw+U8z9aaeoj0tjv/P03YZz08Eq6fn3X3ZY6rWd9EPzNt44bqB9X1raAYXLu78SIVsfJ+XXLVVxPNu3zmYT9mbr8zOiqy0TW2GqtnlXB8zL1N+By/hvrhIoK2dPP4q/zbypK06WO+tdV1O83lQLWVfxO0kngy9r3jNyNS5H48VZ59XHQ+oo6n4E+Pd+GdadIHTl+O1sBPiR53G4tZKSwstb154lsh1VWLeQbUlK17imuw5k+vUjCKsIeMHW2UmRl6SNvKyddK6YU3wSU9v205LlTpq+XPHfKrd9xfd8y/sZ8qt+7NuNd8p65bVOfTYl1HsxsbR3e4jqyeNeZe08rYW1G5Pre0M/RTFgN59bvaRX1uHs6rKnf19rBarAAZsCusAacCmvC6bAWfBjWhS/D8+Ah2AB+DRvCo/q97zhsDGP0e1iyfg+rBLNhDsyB58Nc2B42haNgHpwEm8H5+j3wOf3+9y5sA/fCtvAT2A4e0O+Fh/R74a86X34/JF/KWOq9wtv8j74XRI7IETkiR+SIHJHjf/c4a/r/oMFnRP/fQtzWWv/fqvX/6qL/4+B5vEhuGelRgeuuBRsBwtsATozyxvvS6KTHxf8puud9arOzDYC8SrYB/CznPxF/LfxHJM2jRl86pPNIUDuMvvTtSCkH1fSAkw2APH/bBiBhqJlW5N3M+sTE950r7Vpu3rClXcvNG7a0a7kRtkS7wkk5/zE6Yx9qJ0mlW32cxttJp2S7wtuc56ydRioVrW8kjYyANDIkjfB2hVoBddkW+1Cm9YWJq8+FtSvslXO/UvvR6kdy3l+CXaGP9IN41l/71tgVUkR2odVebXC0K3wg6bvsX8LYFZ7WabrUryXaFa6TcJWxKxwMsivMEvk52BUO/6ZdYcXoku0KSZLWn6zFaoCxK1gi24utYDHfrZzLtxv3h7UrlJGwlawUdcjUWS2RVbdqqI8C93bA/fvtCv+29ZGK2R5qldL24LOJunWj7o1G19aszjNx1JiQZ2LY785932s2HOuNUy061lVFdfV0Mt9u82ED/7d1eh7qfMLPXVog59dFH/XkOz3bdHznuUtVdV+oMo4wrLNYR83ANtvIPmEzi8k1y9wXsyWNl11LVKzLYe6S5HE6c5cI7/i8TNRzxe6T83+J9s1bmiH+ZIdnpHNa2co/B+ohOb/SpPWA+BMcnqHOaeXotPaQ1go5/7BJa5n4Y5yeozqt8POp1oyROjdprRL/OWY+1W3SJ5qa+VQ=
*/