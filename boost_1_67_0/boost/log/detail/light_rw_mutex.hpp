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
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
*/