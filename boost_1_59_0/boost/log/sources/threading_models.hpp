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

#include <boost/type_traits/has_nothrow_constructor.hpp>
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
    void lock_shared() const BOOST_NOEXCEPT {}
    bool try_lock_shared() const BOOST_NOEXCEPT { return true; }
    template< typename TimeT >
    bool timed_lock_shared(TimeT const&) const BOOST_NOEXCEPT { return true; }
    void unlock_shared() const BOOST_NOEXCEPT {}
    void lock() const BOOST_NOEXCEPT {}
    bool try_lock() const BOOST_NOEXCEPT { return true; }
    template< typename TimeT >
    bool timed_lock(TimeT const&) const BOOST_NOEXCEPT { return true; }
    void unlock() const BOOST_NOEXCEPT {}
    void lock_upgrade() const BOOST_NOEXCEPT {}
    bool try_lock_upgrade() const BOOST_NOEXCEPT { return true; }
    template< typename TimeT >
    bool timed_lock_upgrade(TimeT const&) const BOOST_NOEXCEPT { return true; }
    void unlock_upgrade() const BOOST_NOEXCEPT {}
    void unlock_upgrade_and_lock() const BOOST_NOEXCEPT {}
    void unlock_and_lock_upgrade() const BOOST_NOEXCEPT {}
    void unlock_and_lock_shared() const BOOST_NOEXCEPT {}
    void unlock_upgrade_and_lock_shared() const BOOST_NOEXCEPT {}

    void swap(single_thread_model&) BOOST_NOEXCEPT {}
};

inline void swap(single_thread_model&, single_thread_model&) BOOST_NOEXCEPT
{
}

#if !defined(BOOST_LOG_NO_THREADS)

//! Multi-thread locking model with maximum locking capabilities
template< typename MutexT >
struct multi_thread_model
{
    multi_thread_model() BOOST_NOEXCEPT_IF(boost::has_nothrow_constructor< MutexT >::value) {}
    multi_thread_model(multi_thread_model const&) BOOST_NOEXCEPT_IF(boost::has_nothrow_constructor< MutexT >::value) {}
    multi_thread_model& operator= (multi_thread_model const&) BOOST_NOEXCEPT { return *this; }
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    multi_thread_model(multi_thread_model&&) BOOST_NOEXCEPT_IF(boost::has_nothrow_constructor< MutexT >::value) {}
    multi_thread_model& operator= (multi_thread_model&&) BOOST_NOEXCEPT { return *this; }
#endif

    void lock_shared() const { m_Mutex.lock_shared(); }
    bool try_lock_shared() const { return m_Mutex.try_lock_shared(); }
    template< typename TimeT >
    bool timed_lock_shared(TimeT const& t) const { return m_Mutex.timed_lock_shared(t); }
    void unlock_shared() const BOOST_NOEXCEPT { m_Mutex.unlock_shared(); }
    void lock() const { m_Mutex.lock(); }
    bool try_lock() const { return m_Mutex.try_lock(); }
    template< typename TimeT >
    bool timed_lock(TimeT const& t) const { return m_Mutex.timed_lock(t); }
    void unlock() const BOOST_NOEXCEPT { m_Mutex.unlock(); }
    void lock_upgrade() const { m_Mutex.lock_upgrade(); }
    bool try_lock_upgrade() const { return m_Mutex.try_lock_upgrade(); }
    template< typename TimeT >
    bool timed_lock_upgrade(TimeT const& t) const { return m_Mutex.timed_lock_upgrade(t); }
    void unlock_upgrade() const BOOST_NOEXCEPT { m_Mutex.unlock_upgrade(); }
    void unlock_upgrade_and_lock() const { m_Mutex.unlock_upgrade_and_lock(); }
    void unlock_and_lock_upgrade() const { m_Mutex.unlock_and_lock_upgrade(); }
    void unlock_and_lock_shared() const { m_Mutex.unlock_and_lock_shared(); }
    void unlock_upgrade_and_lock_shared() const { m_Mutex.unlock_upgrade_and_lock_shared(); }

    void swap(multi_thread_model&) BOOST_NOEXCEPT {}

private:
    //! Synchronization primitive
    mutable MutexT m_Mutex;
};

template< typename MutexT >
inline void swap(multi_thread_model< MutexT >&, multi_thread_model< MutexT >&) BOOST_NOEXCEPT
{
}

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