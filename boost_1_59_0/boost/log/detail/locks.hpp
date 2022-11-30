/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   locks.hpp
 * \author Andrey Semashev
 * \date   30.05.2010
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_LOCKS_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_LOCKS_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

#ifndef BOOST_LOG_NO_THREADS

// Forward declaration of Boost.Thread locks. Specified here to avoid including Boost.Thread,
// which would bring in many dependent headers, including a great deal of Boost.DateTime.
template< typename >
class lock_guard;
template< typename >
class shared_lock_guard;
template< typename >
class shared_lock;
template< typename >
class upgrade_lock;
template< typename >
class unique_lock;

template< typename >
struct is_mutex_type;

#endif // BOOST_LOG_NO_THREADS

BOOST_LOG_OPEN_NAMESPACE

//! An auxiliary pseudo-lock to express no locking requirements in logger features
template< typename MutexT >
class no_lock
{
public:
    /*!
     * Constructs the pseudo-lock. The mutex is not affected during the construction.
     */
    explicit no_lock(MutexT&) BOOST_NOEXCEPT {}

private:
    no_lock(no_lock const&);
    no_lock& operator= (no_lock const&);
};

namespace aux {

#ifndef BOOST_LOG_NO_THREADS

//! A trait to detect if the mutex supports exclusive locking
template< typename MutexT >
struct is_exclusively_lockable
{
    typedef char true_type;
    struct false_type { char t[2]; };

    template< typename T >
    static true_type check_lockable(T*, void (T::*)() = &T::lock, void (T::*)() = &T::unlock);
    static false_type check_lockable(void*);

    enum value_t { value = sizeof(check_lockable((MutexT*)NULL)) == sizeof(true_type) };
};

//! A trait to detect if the mutex supports shared locking
template< typename MutexT >
struct is_shared_lockable
{
    typedef char true_type;
    struct false_type { char t[2]; };

    template< typename T >
    static true_type check_shared_lockable(T*, void (T::*)() = &T::lock_shared, void (T::*)() = &T::unlock_shared);
    static false_type check_shared_lockable(void*);

    enum value_t { value = sizeof(check_shared_lockable((MutexT*)NULL)) == sizeof(true_type) };
};

//! A scope guard that automatically unlocks the mutex on destruction
template< typename MutexT >
struct exclusive_auto_unlocker
{
    explicit exclusive_auto_unlocker(MutexT& m) BOOST_NOEXCEPT : m_Mutex(m)
    {
    }
    ~exclusive_auto_unlocker()
    {
        m_Mutex.unlock();
    }

    BOOST_DELETED_FUNCTION(exclusive_auto_unlocker(exclusive_auto_unlocker const&))
    BOOST_DELETED_FUNCTION(exclusive_auto_unlocker& operator= (exclusive_auto_unlocker const&))

protected:
    MutexT& m_Mutex;
};

//! An analogue to the minimalistic \c lock_guard template. Defined here to avoid including Boost.Thread.
template< typename MutexT >
struct exclusive_lock_guard
{
    explicit exclusive_lock_guard(MutexT& m) BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(m.lock())) : m_Mutex(m)
    {
        m.lock();
    }
    ~exclusive_lock_guard()
    {
        m_Mutex.unlock();
    }

    BOOST_DELETED_FUNCTION(exclusive_lock_guard(exclusive_lock_guard const&))
    BOOST_DELETED_FUNCTION(exclusive_lock_guard& operator= (exclusive_lock_guard const&))

private:
    MutexT& m_Mutex;
};

//! An analogue to the minimalistic \c lock_guard template that locks \c shared_mutex with shared ownership.
template< typename MutexT >
struct shared_lock_guard
{
    explicit shared_lock_guard(MutexT& m) BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(m.lock_shared())) : m_Mutex(m)
    {
        m.lock_shared();
    }
    ~shared_lock_guard()
    {
        m_Mutex.unlock_shared();
    }

    BOOST_DELETED_FUNCTION(shared_lock_guard(shared_lock_guard const&))
    BOOST_DELETED_FUNCTION(shared_lock_guard& operator= (shared_lock_guard const&))

private:
    MutexT& m_Mutex;
};

//! A deadlock-safe lock type that exclusively locks two mutexes
template< typename MutexT1, typename MutexT2 >
class multiple_unique_lock2
{
public:
    multiple_unique_lock2(MutexT1& m1, MutexT2& m2) BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR(m1.lock()) && BOOST_NOEXCEPT_EXPR(m2.lock())) :
        m_p1(&m1),
        m_p2(&m2)
    {
        // Yes, it's not conforming, but it works
        // and it doesn't require to #include <functional>
        if (static_cast< void* >(m_p1) < static_cast< void* >(m_p2))
        {
            m_p1->lock();
            m_p2->lock();
        }
        else
        {
            m_p2->lock();
            m_p1->lock();
        }
    }
    ~multiple_unique_lock2()
    {
        m_p2->unlock();
        m_p1->unlock();
    }

private:
    MutexT1* m_p1;
    MutexT2* m_p2;
};

#endif // BOOST_LOG_NO_THREADS

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_LOCKS_HPP_INCLUDED_

/* locks.hpp
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
*/