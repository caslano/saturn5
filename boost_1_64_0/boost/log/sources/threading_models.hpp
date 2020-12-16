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
TIGnwZZwHWwFr4Cttd1ZaeaOyDPtt2uiijW8b4Lvf/AAjIUH9f30R9gL/gJz4CF4DXTUXz/8OwzAoOdRMAVWh21gDe2/YqB5X8ku/7kP6vvKj/q+ckjfV1ytRz6tR9Faj/xaj6ppPaqu9agG1O8aHVcnXMt3zZv6/vUulHOyYX34HkyG+2FT+CFsBz+C3eEncCj8DE6Ff4Vz4N9ggbjTs4F1TNj7vVEbtUnD36DfNVfDuvAaWB/eDRvCa2EavE7r842wF7wJ9oObtF5vhqPgzXAq3AKnwVvgbPWnCG6HS+Ht8Cx4B1wN74JrJVx9P3Z13FLHbbfCNqix2v4M1LNUs2FTSBwkfXJgGpwEz4AnwTXwZHghnAyvglPg9TAXboZT4Z1wGnwA5sGH4XT4HJwB98KZ8DU4C74HT4GfwNnwczgHHoRzYTDy82AUnA/j4QJYD+bDxrAAtoGFMA0uhJ1hEcyCi2A2LIZDYQkcBxfDCXAJnApPhfPgClgET4PL4BnwdEj9k/ewVfBcuAbq96iOc+Gn5Xv0Kz279luYDL+DmfB7OBQegLnwICyBP8Bv3dIzZz+8uXrlubP/hefO/kS+1NtS3emKGosqRl2OegD1JuonVKOt1Z0+qKmo1ahtqDdRB1CNbuFsWtRU1ErU9bdUnk9b+av8Vf7+td9vc/7f9Bly/N+/eP5f8Jy/Jqms+9J1Ba/rGM41+s1+ta4DSmmm6woIuCJru7Ff5r6t3GnWtb92u3nWtQHYPfKZCi1Evt62NkTd2tcFJcJ2Ir/Ysy6kdH3qWSJrxLNVUTN2RohZO0ySPW7yzLxcP5Ev9q5LNXPd3UR2htOWebVq5dzLfzCROKcG/674mpNtzSq6BlTyI+KcF0n3o649WaGHOYxA1dBxnU4teF83ZUS3Sc4s4mpGzz2R+I/WVl5wW7F1RWXt5dvKCfYqvl7Ma1fPRisg9kG7Mh/uWZe92DPvylogOZfSnHfYNLX03L1ABe54k3zRNDnyWq98a55gJvEjzphJnHXfRmzYnWKr9c7LlTCYT1NTLfmUm1+Qm1c0LX/67DL5Ze5CFHffu7GMoFnyEH8rlodl7eWbNdnNWyDj7LO6+JhFTo5xWtjyV/2wrwFNhIUiL/C1sq7rN+49dXOCzHm/TnpeJ7IBvlLZWLNWY6fIqpk0Mm2Irs0/VeRzPG6zzB73tSI73vcLz3aa+4Cau06KPPNjmF7GSQY+c67DhWJ/vMev/mY/3i0i6+GRTTTr6x4+XC59f3KrRN5racpulITJ/ZS6v7G4OXpmkga7Pk+a9DVraq8QP4f6/L6ARz7apMvDIf/U/5miT3diSP1EbS/fFD9+dpMYEfzW9Zu1tfeL3YCToHsZ3xZ7VX3vhcVluFkPc7fI030JyF7rKut5CrhwMrcvfyXrvoyB8jzXun3wdwT7Xr+BS/Av0k2WZy/HGnEzxT0ee+dRp5uadrl8tZ3CtEeVttuy/v/1ZtRd/j6QKOvDjD4N9R1m36t5R/Tj1c0mtU9bL+3IDlSo3U/ztvv/pvYkUfeBkT6YmTS1mmdpn9BR25r51XUPpq4ffh41sRvre1pKWzOzZPr8Obw3WO95u0ns3MfJCwFb36B+aF2NOON3g8gedx60nfNpcUufbsps9Vbh97i2U31CaZ2ZPWdW8SLvHbJXiX9POA/zfwZlpIau/xuXdFh1VBYlS/8NRYmd6Q0qtiZ4ZCt7H27WDRp9Xth63yvV52+ieDb4N3hSMA/Ev5Vz8rl/Nt/SN9va+u6t5TzfqFgnKcqaJ63KtvXmHGGRPR/VyTknypInFrf5Zu/SkyJ7JKo3qxVqRQWckqgo54qoOrY+AH+O/C74ocj7Oy0=
*/