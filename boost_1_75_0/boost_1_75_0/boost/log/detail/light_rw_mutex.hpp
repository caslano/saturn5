/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   light_rw_mutex.hpp
 * \author Andrey Semashev
 * \date   24.03.2009
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_LIGHT_RW_MUTEX_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_LIGHT_RW_MUTEX_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_LOG_NO_THREADS

#include <boost/log/detail/header.hpp>

#if defined(BOOST_THREAD_POSIX) // This one can be defined by users, so it should go first
#define BOOST_LOG_LWRWMUTEX_USE_PTHREAD
#elif defined(BOOST_WINDOWS) && (BOOST_USE_WINAPI_VERSION+0) >= (BOOST_WINAPI_VERSION_WIN6+0)
#define BOOST_LOG_LWRWMUTEX_USE_SRWLOCK
#elif defined(BOOST_HAS_PTHREADS)
#define BOOST_LOG_LWRWMUTEX_USE_PTHREAD
#endif

#if defined(BOOST_LOG_LWRWMUTEX_USE_SRWLOCK)

#include <boost/winapi/srw_lock.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! A light read/write mutex that uses WinNT 6 and later APIs
class light_rw_mutex
{
    boost::winapi::SRWLOCK_ m_Mutex;

public:
    light_rw_mutex()
    {
        boost::winapi::InitializeSRWLock(&m_Mutex);
    }
    void lock_shared()
    {
        boost::winapi::AcquireSRWLockShared(&m_Mutex);
    }
    void unlock_shared()
    {
        boost::winapi::ReleaseSRWLockShared(&m_Mutex);
    }
    void lock()
    {
        boost::winapi::AcquireSRWLockExclusive(&m_Mutex);
    }
    void unlock()
    {
        boost::winapi::ReleaseSRWLockExclusive(&m_Mutex);
    }

    // Noncopyable
    BOOST_DELETED_FUNCTION(light_rw_mutex(light_rw_mutex const&))
    BOOST_DELETED_FUNCTION(light_rw_mutex& operator= (light_rw_mutex const&))
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#elif defined(BOOST_LOG_LWRWMUTEX_USE_PTHREAD)

#include <pthread.h>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! A light read/write mutex that maps directly onto POSIX threading library
class light_rw_mutex
{
    pthread_rwlock_t m_Mutex;

public:
    light_rw_mutex()
    {
        pthread_rwlock_init(&m_Mutex, NULL);
    }
    ~light_rw_mutex()
    {
        pthread_rwlock_destroy(&m_Mutex);
    }
    void lock_shared()
    {
        pthread_rwlock_rdlock(&m_Mutex);
    }
    void unlock_shared()
    {
        pthread_rwlock_unlock(&m_Mutex);
    }
    void lock()
    {
        pthread_rwlock_wrlock(&m_Mutex);
    }
    void unlock()
    {
        pthread_rwlock_unlock(&m_Mutex);
    }

    // Noncopyable
    BOOST_DELETED_FUNCTION(light_rw_mutex(light_rw_mutex const&))
    BOOST_DELETED_FUNCTION(light_rw_mutex& operator= (light_rw_mutex const&))
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#else

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! A light read/write mutex
class light_rw_mutex
{
    struct BOOST_LOG_MAY_ALIAS mutex_state { void* p; } m_Mutex;

public:
    BOOST_LOG_API light_rw_mutex();
    BOOST_LOG_API ~light_rw_mutex();
    BOOST_LOG_API void lock_shared();
    BOOST_LOG_API void unlock_shared();
    BOOST_LOG_API void lock();
    BOOST_LOG_API void unlock();

    // Noncopyable
    BOOST_DELETED_FUNCTION(light_rw_mutex(light_rw_mutex const&))
    BOOST_DELETED_FUNCTION(light_rw_mutex& operator= (light_rw_mutex const&))
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_NO_THREADS

#endif // BOOST_LOG_DETAIL_LIGHT_RW_MUTEX_HPP_INCLUDED_

/* light_rw_mutex.hpp
Tl6/h5aXMTRgybPQl1e0UhjV52wN1X5+AQG4LYXApV7EyiIhDFzdeLRpyTGB9WiUhT4IOPgFTD8fa6Zpm4S2CdgEANfI5NmuMhQAVtCAFcNBDLlMTzW8FQbRxioL/b7qRo+T35dFvPICyOGvf8GgwvvR85HXQ3cbfHxwsDhsDfLCZoMPt8s5Zfhy2oy5W3nJqJAy0brgbuzmTMjCPqel91iQ5giT089cJ0aGD0NtIfS4WoOQT/DKmTCJws9Skxy8kXVVtzgCbyDOmTloW/02bG4FI1gs8Hu4R4Wy7nqby4rggR5wS1WYA+99FGO/2oADZkeNg/IycDFsbX8exwVNXhluXwHWl8oahhOM8Fl+c5BmcD2DS+4fAKfAvpX8m78zHFttcPiuTMDVOQw+l9u0AZ6hgSxT/sbgEltPlgb79PL8NxkueMWcl3sG0o3uw8tNRQnV0SHwgWtWo9xZbF1eXWGvBc8A3go9Rl7E0zChEaww8C1FmEcGPsLrRYVNl/YoBN/L000Mr2v0212+QFkP5WMfxNoYTCs4AikNpjdi/MrfXcriFPv9Hqp7A942AW3z8S0MXmIo0QnxbZOwz/Hpx2L9MdLEuxCsPCkobzRb/1eXUhUV522SNl+rxbz37qgQfJc2VuYizg9jQ+J0ac8zCeiHlUNZHLXDpfJ6rWI/rFVhb+KNBQyn8lU7HBzeNgdl67s8JF9JW+yXo72e
*/