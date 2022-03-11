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
    explicit no_lock(MutexT&) {}

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
    explicit exclusive_lock_guard(MutexT& m) : m_Mutex(m)
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
    explicit shared_lock_guard(MutexT& m) : m_Mutex(m)
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
    multiple_unique_lock2(MutexT1& m1, MutexT2& m2) :
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