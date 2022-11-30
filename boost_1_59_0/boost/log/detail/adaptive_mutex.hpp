/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   adaptive_mutex.hpp
 * \author Andrey Semashev
 * \date   01.08.2010
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_ADAPTIVE_MUTEX_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_ADAPTIVE_MUTEX_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_LOG_NO_THREADS

#include <boost/throw_exception.hpp>
#include <boost/thread/exceptions.hpp>
#include <boost/assert/source_location.hpp>

#if defined(BOOST_THREAD_POSIX) // This one can be defined by users, so it should go first
#define BOOST_LOG_ADAPTIVE_MUTEX_USE_PTHREAD
#elif defined(BOOST_WINDOWS)
#define BOOST_LOG_ADAPTIVE_MUTEX_USE_WINAPI
#elif defined(BOOST_HAS_PTHREADS)
#define BOOST_LOG_ADAPTIVE_MUTEX_USE_PTHREAD
#endif

#if defined(BOOST_LOG_ADAPTIVE_MUTEX_USE_WINAPI)

#include <boost/log/detail/pause.hpp>
#include <boost/winapi/thread.hpp>
#include <boost/detail/interlocked.hpp>

#if defined(__INTEL_COMPILER) || defined(_MSC_VER)
#    if defined(__INTEL_COMPILER)
#        define BOOST_LOG_COMPILER_BARRIER __memory_barrier()
#    elif defined(__clang__) // clang-win also defines _MSC_VER
#        define BOOST_LOG_COMPILER_BARRIER __atomic_signal_fence(__ATOMIC_SEQ_CST)
#    else
extern "C" void _ReadWriteBarrier(void);
#        if defined(BOOST_MSVC)
#            pragma intrinsic(_ReadWriteBarrier)
#        endif
#        define BOOST_LOG_COMPILER_BARRIER _ReadWriteBarrier()
#    endif
#elif defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
#    define BOOST_LOG_COMPILER_BARRIER __asm__ __volatile__("" : : : "memory")
#endif

#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! A mutex that performs spinning or thread yielding in case of contention
class adaptive_mutex
{
private:
    enum state
    {
        initial_pause = 2,
        max_pause = 16
    };

    long m_State;

public:
    adaptive_mutex() : m_State(0) {}

    bool try_lock()
    {
        return (BOOST_INTERLOCKED_COMPARE_EXCHANGE(&m_State, 1L, 0L) == 0L);
    }

    void lock()
    {
#if defined(BOOST_LOG_AUX_PAUSE)
        unsigned int pause_count = initial_pause;
#endif
        while (!try_lock())
        {
#if defined(BOOST_LOG_AUX_PAUSE)
            if (pause_count < max_pause)
            {
                for (unsigned int i = 0; i < pause_count; ++i)
                {
                    BOOST_LOG_AUX_PAUSE;
                }
                pause_count += pause_count;
            }
            else
            {
                // Restart spinning after waking up this thread
                pause_count = initial_pause;
                boost::winapi::SwitchToThread();
            }
#else
            boost::winapi::SwitchToThread();
#endif
        }
    }

    void unlock()
    {
#if (defined(_M_IX86) || defined(_M_AMD64)) && defined(BOOST_LOG_COMPILER_BARRIER)
        BOOST_LOG_COMPILER_BARRIER;
        m_State = 0L;
        BOOST_LOG_COMPILER_BARRIER;
#else
        BOOST_INTERLOCKED_EXCHANGE(&m_State, 0L);
#endif
    }

    //  Non-copyable
    BOOST_DELETED_FUNCTION(adaptive_mutex(adaptive_mutex const&))
    BOOST_DELETED_FUNCTION(adaptive_mutex& operator= (adaptive_mutex const&))
};

#undef BOOST_LOG_AUX_PAUSE
#undef BOOST_LOG_COMPILER_BARRIER

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#elif defined(BOOST_LOG_ADAPTIVE_MUTEX_USE_PTHREAD)

#include <pthread.h>
#include <boost/assert.hpp>
#include <boost/log/detail/header.hpp>

#if defined(PTHREAD_ADAPTIVE_MUTEX_INITIALIZER_NP)
#define BOOST_LOG_ADAPTIVE_MUTEX_USE_PTHREAD_MUTEX_ADAPTIVE_NP
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! A mutex that performs spinning or thread yielding in case of contention
class adaptive_mutex
{
private:
    pthread_mutex_t m_State;

public:
    adaptive_mutex()
    {
#if defined(BOOST_LOG_ADAPTIVE_MUTEX_USE_PTHREAD_MUTEX_ADAPTIVE_NP)
        pthread_mutexattr_t attrs;
        pthread_mutexattr_init(&attrs);
        pthread_mutexattr_settype(&attrs, PTHREAD_MUTEX_ADAPTIVE_NP);

        const int err = pthread_mutex_init(&m_State, &attrs);
        pthread_mutexattr_destroy(&attrs);
#else
        const int err = pthread_mutex_init(&m_State, NULL);
#endif
        if (BOOST_UNLIKELY(err != 0))
            throw_exception< thread_resource_error >(err, "Failed to initialize an adaptive mutex", "adaptive_mutex::adaptive_mutex()", __FILE__, __LINE__);
    }

    ~adaptive_mutex()
    {
        BOOST_VERIFY(pthread_mutex_destroy(&m_State) == 0);
    }

    bool try_lock()
    {
        const int err = pthread_mutex_trylock(&m_State);
        if (err == 0)
            return true;
        if (BOOST_UNLIKELY(err != EBUSY))
            throw_exception< lock_error >(err, "Failed to lock an adaptive mutex", "adaptive_mutex::try_lock()", __FILE__, __LINE__);
        return false;
    }

    void lock()
    {
        const int err = pthread_mutex_lock(&m_State);
        if (BOOST_UNLIKELY(err != 0))
            throw_exception< lock_error >(err, "Failed to lock an adaptive mutex", "adaptive_mutex::lock()", __FILE__, __LINE__);
    }

    void unlock()
    {
        BOOST_VERIFY(pthread_mutex_unlock(&m_State) == 0);
    }

    //  Non-copyable
    BOOST_DELETED_FUNCTION(adaptive_mutex(adaptive_mutex const&))
    BOOST_DELETED_FUNCTION(adaptive_mutex& operator= (adaptive_mutex const&))

private:
    template< typename ExceptionT >
    static BOOST_NOINLINE BOOST_LOG_NORETURN void throw_exception(int err, const char* descr, const char* func, const char* file, int line)
    {
        boost::throw_exception(ExceptionT(err, descr), boost::source_location(file, line, func));
    }
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif

#endif // BOOST_LOG_NO_THREADS

#endif // BOOST_LOG_DETAIL_ADAPTIVE_MUTEX_HPP_INCLUDED_

/* adaptive_mutex.hpp
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
*/