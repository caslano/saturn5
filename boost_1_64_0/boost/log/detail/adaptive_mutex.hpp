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
H9uu1f1uvR66IDHE67HdP7bltclrw2IjNa+t/903j45x/nGor4Rt7ziukI45PlTRccU/Hg0Sv1ZOazMzXnn1Ydjqw3nd5QmojypaH9byr52rY7uetz9SjXCLTi9/O3/5j7TT8uv4eJeE7en83c0zlH+Z+FV1Kr8ZT7/TS7n/tTogr051YFtrbi7WPXg3czy8HMalELesDtqmZkzOxss+x+m+Vs0dOm/rHJf0uu7Jaf+oJP5tzPpqL/4JLv880VP8Dzp/o9BSf7EB9VdV4hlO85IZz+GbELJfWY1rcB1tv+06vUZHzqsk16a6H/C7R5Ss9EzU78eoX2ix+rlLUjzump4RYZ6QcYZhC9O82H9tFz/huS7cU6O4xBNCYa3n6OMPE93PM8Kjftre/u9HvOmltvfIwPZ2/i5zueNBrLZ9NfQ9Z/gexPYSfYZBTzAEqZXizZTZH9qlJpvXgu3+IVTCXOLYlsQ3v4m/jbL34Dxvectfvauv7Oo+AfdduIc04ws4EZVtfjP9ftVP91viTy/U8HgiDPGr6PvBvutkmu26WDpfnxVGWiDjkXjqIc9SD47Xhfb7W8qvC9JwWG9pv14hfh0cxgV7vK/byVUr4bzPpXj73k7q4NQ87h+lHup5wsOiq0Q3pa4qc9+P/wL8NiFvS//t7YkM036nfvtMvw6mX7z6nRA/f7qe8Cra571SiX7rQn9H++oc529SX1LRvmqZu6RsX/vmLvlO6qqd5ndSRX8yQH/RolvbM+Z6/c4JUhlpj9TlPMablvbUmc4+z+l4I+EaOvftNx3aU8c3j/g1d2pPM558L2s+fX+Bv/4beVzUcajWsd9/julf0+sfEui/zO8f7vKERngqhal/Rb8T7nFuB6nXGm/a6/n8AD3pTed6D72hbI1h6BqjPukOK6v3/Mz03Ol5+r3tnwLGlJESrqNjvZOGOabE0r5LEBkDKif5+rW6r0Vk3KhdNm7Eq99u9WPciI7AO9xzbmPHT5axo4uWucfNaneVAE3gYRYxRwm3wixzQXpadlo+VooKUyenFWQatvHU7HM7Jfz2EIeyk1bgN2fTzD63VfyecOhz9ngHZQzJl3CJfFff63ZI3ArFrQ/XXtkeRpZ5b79N0njMqKbnu+ot2YsI2YMVz7KxqcD3TCbpLt0le49ur18jmXEyJf1N+t2mPElf9jLlvteFdkTO8bIRI795hIi72xvMey7cQvivrvyWQnhcnhZ3ngCgXSPpc2MW8oy+bw7ezBjI1RISHRndItwdUo1Wrh7r7TOlNzLfIb55qET7jLiz6ah9pviwdJqAfUnCUSNyzqQQa7xOZrwPpTc52Z9Kl3gptngjifeWL787PFGR5thaX8uzBP893nTnh1KG6kgc6cdVd14j6rigcbcT9z1v3HkPES+eePE1dW1dbpxTZpyeGqde/NniJN+kcUo+8Z+nXnlx4jTOfuLslTjLCV8tyTKXWOc5sy8Nl77UT8bMFOLuQ3ZrfOpFJjtv2xbivgqR8bByyUvec/rdN5W5P2V136Pu9IXlUv8qDTWvdf9EGDlXT++59HzV47jHK3etbo0/wR9//q3nGH9c1Qj83kffh7xjirrpvLvHdW5rxCPtnL4Xl+bVZTw4WHb/IGPBIdELRactmJfN/TO5lrm20TNlPhi2yz4/TAzQrzB1+/ozpVTfS0HCkWTEncIY/o6Mndm5aRmp7QzSMMe9rBzrPuE6CZfkNF9oGq6zft/vfQlXyfb7yV6Na30+eL+4hZ3pu+UDrd94k/qV/NrLnHiL/o6vZe6hZT5iKXPKGcp8TMJd6HwPVcEyN3tXymz7baqmuMXIfqW13Inv/jHl3qPljrLEb+hdG0g=
*/