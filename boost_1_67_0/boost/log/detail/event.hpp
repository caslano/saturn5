/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   detail/event.hpp
 * \author Andrey Semashev
 * \date   24.07.2011
 */

#ifndef BOOST_LOG_DETAIL_EVENT_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_EVENT_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_LOG_NO_THREADS

#if defined(BOOST_THREAD_PLATFORM_PTHREAD)
#   include <boost/atomic/capabilities.hpp>
#   if (defined(linux) || defined(__linux) || defined(__linux__)) && BOOST_ATOMIC_INT_LOCK_FREE == 2
#       include <boost/atomic/atomic.hpp>
#       define BOOST_LOG_EVENT_USE_FUTEX
#   elif defined(_POSIX_SEMAPHORES) && (_POSIX_SEMAPHORES + 0) > 0 && BOOST_ATOMIC_FLAG_LOCK_FREE == 2
#       include <semaphore.h>
#       include <boost/cstdint.hpp>
#       include <boost/atomic/atomic_flag.hpp>
#       define BOOST_LOG_EVENT_USE_POSIX_SEMAPHORE
#   endif
#elif defined(BOOST_THREAD_PLATFORM_WIN32)
#   include <boost/cstdint.hpp>
#   define BOOST_LOG_EVENT_USE_WINAPI
#endif

#if !defined(BOOST_LOG_EVENT_USE_POSIX_SEMAPHORE) && !defined(BOOST_LOG_EVENT_USE_WINAPI)
#   include <boost/thread/mutex.hpp>
#   include <boost/thread/condition_variable.hpp>
#   define BOOST_LOG_EVENT_USE_BOOST_CONDITION
#endif

#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

#if defined(BOOST_LOG_EVENT_USE_FUTEX)

class futex_based_event
{
private:
    boost::atomic< int > m_state;

public:
    //! Default constructor
    BOOST_LOG_API futex_based_event();
    //! Destructor
    BOOST_LOG_API ~futex_based_event();

    //! Waits for the object to become signalled
    BOOST_LOG_API void wait();
    //! Sets the object to a signalled state
    BOOST_LOG_API void set_signalled();

    //  Copying prohibited
    BOOST_DELETED_FUNCTION(futex_based_event(futex_based_event const&))
    BOOST_DELETED_FUNCTION(futex_based_event& operator= (futex_based_event const&))
};

typedef futex_based_event event;

#elif defined(BOOST_LOG_EVENT_USE_POSIX_SEMAPHORE)

class sem_based_event
{
private:
    boost::atomic_flag m_state;
    sem_t m_semaphore;

public:
    //! Default constructor
    BOOST_LOG_API sem_based_event();
    //! Destructor
    BOOST_LOG_API ~sem_based_event();

    //! Waits for the object to become signalled
    BOOST_LOG_API void wait();
    //! Sets the object to a signalled state
    BOOST_LOG_API void set_signalled();

    //  Copying prohibited
    BOOST_DELETED_FUNCTION(sem_based_event(sem_based_event const&))
    BOOST_DELETED_FUNCTION(sem_based_event& operator= (sem_based_event const&))
};

typedef sem_based_event event;

#elif defined(BOOST_LOG_EVENT_USE_WINAPI)

class winapi_based_event
{
private:
    boost::uint32_t m_state;
    void* m_event;

public:
    //! Default constructor
    BOOST_LOG_API winapi_based_event();
    //! Destructor
    BOOST_LOG_API ~winapi_based_event();

    //! Waits for the object to become signalled
    BOOST_LOG_API void wait();
    //! Sets the object to a signalled state
    BOOST_LOG_API void set_signalled();

    //  Copying prohibited
    BOOST_DELETED_FUNCTION(winapi_based_event(winapi_based_event const&))
    BOOST_DELETED_FUNCTION(winapi_based_event& operator= (winapi_based_event const&))
};

typedef winapi_based_event event;

#else

class generic_event
{
private:
    boost::mutex m_mutex;
    boost::condition_variable m_cond;
    bool m_state;

public:
    //! Default constructor
    BOOST_LOG_API generic_event();
    //! Destructor
    BOOST_LOG_API ~generic_event();

    //! Waits for the object to become signalled
    BOOST_LOG_API void wait();
    //! Sets the object to a signalled state
    BOOST_LOG_API void set_signalled();

    //  Copying prohibited
    BOOST_DELETED_FUNCTION(generic_event(generic_event const&))
    BOOST_DELETED_FUNCTION(generic_event& operator= (generic_event const&))
};

typedef generic_event event;

#endif

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_NO_THREADS

#endif // BOOST_LOG_DETAIL_EVENT_HPP_INCLUDED_

/* event.hpp
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
*/