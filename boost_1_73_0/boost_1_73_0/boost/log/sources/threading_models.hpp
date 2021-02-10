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
BfAy79t89m5uesyZ4q0+b3gA5s8rsKwtfYyRdH6k729gPzD3ketxRIrmaijSrJwvMN78AB18VsZYJont6UktjOYZahrE7RO1oNAoAsLYNw1V5N56yE6Juq0R7sLLWiSApUx1erWkcOvzLnSfy+eyiz3FeOqdvB9O3YrfiiYxXGCZgyhbNbhy4fT8YjTxpqPh26vRz1cVxGPH/P+x06nAJ9dnZ0edx84zkWKt7nCi048OqNYJ9MwHzIrpfDeWuxGnCirGaZbu/i7yDDIqbOtYsipRKlAZOEujeN4asFU+eJdkMz854ZMwmPM3Fc06dVDPc6w5BJUusEaFfk42Oh2eXY7Yr5FmHhgv0LjPsZ74lHgN+szcwIOK1O4bUv+RSR4DyjB+kmRBRVMFzU7lK5hnd+q8UwcKnaYykGaqT+PDflGI5argPiXJ/BD2KP8ho1GumxZd2zjhW4FDt5EF/bTf1XBdNCSmyLTOkdr16GDtXrYUBOgtfe1s7FQGmcv4aw+zfXmnwmF7bZQLoWg9ccGXR6SFrOR2E6sqJYQqrh7130qLxzWPR9oln4kE/YdSTpyG2Voa6CfSka1jO+BZZdhTRfE93u7t9cwD7Ppq3hEzVmPsHakKM2W/UL21T8B3cVZKY7Cac1AKZMFrlRzZ
*/