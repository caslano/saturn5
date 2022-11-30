/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2011 Helge Bahmann
 * Copyright (c) 2013-2014, 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/lock_pool.hpp
 *
 * This header contains declaration of the lock pool used to emulate atomic ops.
 */

#ifndef BOOST_ATOMIC_DETAIL_LOCK_POOL_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_LOCK_POOL_HPP_INCLUDED_

#include <cstddef>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/link.hpp>
#include <boost/atomic/detail/intptr.hpp>
#if defined(BOOST_WINDOWS)
#include <boost/winapi/thread.hpp>
#elif defined(BOOST_HAS_NANOSLEEP)
#include <time.h>
#else
#include <unistd.h>
#endif
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

BOOST_FORCEINLINE void wait_some() BOOST_NOEXCEPT
{
#if defined(BOOST_WINDOWS)
    boost::winapi::SwitchToThread();
#elif defined(BOOST_HAS_NANOSLEEP)
    // Do not use sched_yield or pthread_yield as at least on Linux it doesn't block the thread if there are no other
    // pending threads on the current CPU. Proper sleeping is guaranteed to block the thread, which allows other threads
    // to potentially migrate to this CPU and complete the tasks we're waiting for.
    struct ::timespec ts = {};
    ts.tv_sec = 0;
    ts.tv_nsec = 1000;
    ::nanosleep(&ts, NULL);
#else
    ::usleep(1);
#endif
}

namespace lock_pool {

BOOST_ATOMIC_DECL void* short_lock(atomics::detail::uintptr_t h) BOOST_NOEXCEPT;
BOOST_ATOMIC_DECL void* long_lock(atomics::detail::uintptr_t h) BOOST_NOEXCEPT;
BOOST_ATOMIC_DECL void unlock(void* ls) BOOST_NOEXCEPT;

BOOST_ATOMIC_DECL void* allocate_wait_state(void* ls, const volatile void* addr) BOOST_NOEXCEPT;
BOOST_ATOMIC_DECL void free_wait_state(void* ls, void* ws) BOOST_NOEXCEPT;
BOOST_ATOMIC_DECL void wait(void* ls, void* ws) BOOST_NOEXCEPT;
BOOST_ATOMIC_DECL void notify_one(void* ls, const volatile void* addr) BOOST_NOEXCEPT;
BOOST_ATOMIC_DECL void notify_all(void* ls, const volatile void* addr) BOOST_NOEXCEPT;

BOOST_ATOMIC_DECL void thread_fence() BOOST_NOEXCEPT;
BOOST_ATOMIC_DECL void signal_fence() BOOST_NOEXCEPT;

template< std::size_t Alignment >
BOOST_FORCEINLINE atomics::detail::uintptr_t hash_ptr(const volatile void* addr) BOOST_NOEXCEPT
{
    atomics::detail::uintptr_t ptr = (atomics::detail::uintptr_t)addr;
    atomics::detail::uintptr_t h = ptr / Alignment;

    // Since many malloc/new implementations return pointers with higher alignment
    // than indicated by Alignment, it makes sense to mix higher bits
    // into the lower ones. On 64-bit platforms, malloc typically aligns to 16 bytes,
    // on 32-bit - to 8 bytes.
    BOOST_CONSTEXPR_OR_CONST std::size_t malloc_alignment = sizeof(void*) >= 8u ? 16u : 8u;
    BOOST_IF_CONSTEXPR (Alignment != malloc_alignment)
        h ^= ptr / malloc_alignment;

    return h;
}

template< std::size_t Alignment, bool LongLock = false >
class scoped_lock
{
private:
    void* m_lock;

public:
    explicit scoped_lock(const volatile void* addr) BOOST_NOEXCEPT
    {
        atomics::detail::uintptr_t h = lock_pool::hash_ptr< Alignment >(addr);
        BOOST_IF_CONSTEXPR (!LongLock)
            m_lock = lock_pool::short_lock(h);
        else
            m_lock = lock_pool::long_lock(h);
    }
    ~scoped_lock() BOOST_NOEXCEPT
    {
        lock_pool::unlock(m_lock);
    }

    void* get_lock_state() const BOOST_NOEXCEPT
    {
        return m_lock;
    }

    BOOST_DELETED_FUNCTION(scoped_lock(scoped_lock const&))
    BOOST_DELETED_FUNCTION(scoped_lock& operator=(scoped_lock const&))
};

template< std::size_t Alignment >
class scoped_wait_state :
    public scoped_lock< Alignment, true >
{
private:
    void* m_wait_state;

public:
    explicit scoped_wait_state(const volatile void* addr) BOOST_NOEXCEPT :
        scoped_lock< Alignment, true >(addr)
    {
        m_wait_state = lock_pool::allocate_wait_state(this->get_lock_state(), addr);
    }
    ~scoped_wait_state() BOOST_NOEXCEPT
    {
        lock_pool::free_wait_state(this->get_lock_state(), m_wait_state);
    }

    void wait() BOOST_NOEXCEPT
    {
        lock_pool::wait(this->get_lock_state(), m_wait_state);
    }

    BOOST_DELETED_FUNCTION(scoped_wait_state(scoped_wait_state const&))
    BOOST_DELETED_FUNCTION(scoped_wait_state& operator=(scoped_wait_state const&))
};

} // namespace lock_pool
} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_LOCK_POOL_HPP_INCLUDED_

/* lock_pool.hpp
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
*/