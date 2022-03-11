/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   sources/threading_models.hpp
 * \author Andrey Semashev
 * \date   04.10.2008
 *
 * The header contains definition of threading models that can be used in loggers.
 * The header also provides a number of tags that can be used to express lock requirements
 * on a function callee.
 */

#ifndef BOOST_LOG_SOURCES_THREADING_MODELS_HPP_INCLUDED_
#define BOOST_LOG_SOURCES_THREADING_MODELS_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/locks.hpp> // is_mutex_type
#if !defined(BOOST_LOG_NO_THREADS)
#include <boost/mpl/bool.hpp>
#endif
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sources {

//! Single thread locking model
struct single_thread_model
{
    // We provide methods for the most advanced locking concept: UpgradeLockable
    void lock_shared() const {}
    bool try_lock_shared() const { return true; }
    template< typename TimeT >
    bool timed_lock_shared(TimeT const&) const { return true; }
    void unlock_shared() const {}
    void lock() const {}
    bool try_lock() const { return true; }
    template< typename TimeT >
    bool timed_lock(TimeT const&) const { return true; }
    void unlock() const {}
    void lock_upgrade() const {}
    bool try_lock_upgrade() const { return true; }
    template< typename TimeT >
    bool timed_lock_upgrade(TimeT const&) const { return true; }
    void unlock_upgrade() const {}
    void unlock_upgrade_and_lock() const {}
    void unlock_and_lock_upgrade() const {}
    void unlock_and_lock_shared() const {}
    void unlock_upgrade_and_lock_shared() const {}

    void swap(single_thread_model&) {}
};

#if !defined(BOOST_LOG_NO_THREADS)

//! Multi-thread locking model with maximum locking capabilities
template< typename MutexT >
struct multi_thread_model
{
    multi_thread_model() {}
    multi_thread_model(multi_thread_model const&) {}
    multi_thread_model& operator= (multi_thread_model const&) { return *this; }

    void lock_shared() const { m_Mutex.lock_shared(); }
    bool try_lock_shared() const { return m_Mutex.try_lock_shared(); }
    template< typename TimeT >
    bool timed_lock_shared(TimeT const& t) const { return m_Mutex.timed_lock_shared(t); }
    void unlock_shared() const { m_Mutex.unlock_shared(); }
    void lock() const { m_Mutex.lock(); }
    bool try_lock() const { return m_Mutex.try_lock(); }
    template< typename TimeT >
    bool timed_lock(TimeT const& t) const { return m_Mutex.timed_lock(t); }
    void unlock() const { m_Mutex.unlock(); }
    void lock_upgrade() const { m_Mutex.lock_upgrade(); }
    bool try_lock_upgrade() const { return m_Mutex.try_lock_upgrade(); }
    template< typename TimeT >
    bool timed_lock_upgrade(TimeT const& t) const { return m_Mutex.timed_lock_upgrade(t); }
    void unlock_upgrade() const { m_Mutex.unlock_upgrade(); }
    void unlock_upgrade_and_lock() const { m_Mutex.unlock_upgrade_and_lock(); }
    void unlock_and_lock_upgrade() const { m_Mutex.unlock_and_lock_upgrade(); }
    void unlock_and_lock_shared() const { m_Mutex.unlock_and_lock_shared(); }
    void unlock_upgrade_and_lock_shared() const { m_Mutex.unlock_upgrade_and_lock_shared(); }

    void swap(multi_thread_model&) {}

private:
    //! Synchronization primitive
    mutable MutexT m_Mutex;
};

#endif // !defined(BOOST_LOG_NO_THREADS)

} // namespace sources

BOOST_LOG_CLOSE_NAMESPACE // namespace log

#if !defined(BOOST_LOG_NO_THREADS) && !defined(BOOST_LOG_DOXYGEN_PASS)

template< >
struct is_mutex_type< boost::log::sources::single_thread_model > : mpl::true_
{
};

template< typename T >
struct is_mutex_type< boost::log::sources::multi_thread_model< T > > : mpl::true_
{
};

#endif // !defined(BOOST_LOG_NO_THREADS)

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SOURCES_THREADING_MODELS_HPP_INCLUDED_

/* threading_models.hpp
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
*/