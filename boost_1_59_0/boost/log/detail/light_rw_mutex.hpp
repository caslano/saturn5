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
+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
*/