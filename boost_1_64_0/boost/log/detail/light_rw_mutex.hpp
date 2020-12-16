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
VRns3/rWss6Zxmo/jEF2JaAfK79Jp8+fn1daXlCU5y+JalCK9b3WrpRwQ6xPTv97W39DMHcLNQcPPdfu9Fkv8bljrr/9ew99pemiPccaVl40r3/oObt5bt5+e632zm3P1lxbvz2hx0CODb9c3d+emKxz5KkwXue2/XRuOxLOhGPgFVC+k7OTOQoSON/TuZ7O89zzu8OIzul0Hhc8hzvmYw5zqIA52p36vYZsnZMVzQ+ef41ErHlXlM6vtuicSudTOpcKnkfp/Im5k3PO5J4v6VxJ50bkCzEXWqpzniM7I/OcSIiESIiESIiESIiESIiE/4dwTn7/FxVXyAOAM/z97/sNX4Ou5Uu+Udf/1yFepBRJ9X1vPLaN9X/yGNaGzWvJsSHXhg1rye78cUNkbbigtLSwYMVa07tx7vwdoyR/YV5B5aqQ68maX9fGbX/eqbqevFTSizyd+NsfmedYp/ZQtsfxjv5KybuIcjt4piBDPLnSnoH0bwGFDYZ74TWwCCLE6fOOUO/A6bprVIh11y6GdVdrPZb+It7uL/u9z45RxGu//KevyY6T5zVLut34zfJnS/flV5eNG/Tzvz8YWZP9T16TbbDOK72O1Ad8UzdF/a6mwR7wfNgLpsMk2B+mwgw4CI6EQzXfMJgJL4JD4Ew4FC6Cw+DVmi8XjoB58Dy4Wssp1fTxH3BN07CeGVnLNK9lnpN1zHO9hum5K/Jc71/snQlgFcUZgHdfAiQkQAhJCOGK3DchEO5LuRUwyn0mQAJEAolJgCCoEVFAQVO19cKKHEottbRFi4qViq1oqaKipQqKFS0qakREtFr7vf/9u2832UDSqr3ewp/v7ezM7NwzOzvzb+gIHaEjdISO0BE6/k3P//L5JP8EwL/+/L8Ut12s7/yFGXIcN3kuhH+FTXj+3xFlPf/LjV3fWHLq6vtG7K0wPb+3E+XQW4OBWe5Z+xG5/oZ5s+kz9iLPmAm4v6B+hOWWUA0x1pjO+QH107HWm+dfS99ftP9aA/M8vnDwET5Zum6W18Ec115ryOPgXvHzoPmCib8e35Q5LP6O5D5o41M/24qf0/nezwiPdeSq+078fbjCOvEEjf8w8WM06Z5q8P2wCmvF62pafCr+bDRnMr+Q4LEuvDPyRUJA/oJM4vxRJAWZpNeKyfNliFKuFzTzU9eRV+HbeH5dc1fWsXTNeX4nytbVQ37rOnL3N+8O6CL0l5BIv1vEX96S67rKW4ZuYfAsd3Fwqti/1nt/SV3PcmfreWsj1/dpWVP7hKizca/tj5qf9dtwqXL9cdd3hpz5306uP2tU+O6b3neMXN9qqJ5AV75ORK5ErO//bEGykvx5Wb38OlL3X8uvPfoB0DeQMOQIEp1G2arnzi/9KlL5/LLr0M1ifwx53sUrz/Cvet//w/5Z87iXXH/Ja84Qt5Xnaxy8QK7/odJ87SPXX66Yr1oupsj1n3vm6/4YyUPNT0edrWY9PFPvLPlahe/02fn9Hz4fOFfmA8dkmuMfbfvLzGc/2j7qphG9xobmA/+T5wP3mdpP67iiFPZEdvsNdE+FD46E0brOrAG8EDaGo2FLOAZ2gWOh33264/s5F8HxcAqcABfBSbAEToN3wxlwG5wJfwoz4eNwFtwL58DfwSy4D86Fx+B8eArmwM/hZTBa91DUgwthC7gIdoV5sDe8HA6ABXAwLITjYBHMhIthNlwK82AxLIDLYBG8Ai6FK+BqeCW8UfVorYcl/C+FN8Db4TXwHrgS/gyugo+rPq0n4Wr4W7gGPq3u/gjXw5fhTfAwLIV/gT+Ax/T8r3ruz88diPSF2m+XIg2QLYj/oNkiP936p2JhM2jN6yKih6ozbAHTYGs=
*/