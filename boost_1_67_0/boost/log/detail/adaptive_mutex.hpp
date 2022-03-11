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