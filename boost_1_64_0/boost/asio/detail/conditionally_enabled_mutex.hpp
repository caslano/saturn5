//
// detail/conditionally_enabled_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_CONDITIONALLY_ENABLED_MUTEX_HPP
#define BOOST_ASIO_DETAIL_CONDITIONALLY_ENABLED_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Mutex adapter used to conditionally enable or disable locking.
class conditionally_enabled_mutex
  : private noncopyable
{
public:
  // Helper class to lock and unlock a mutex automatically.
  class scoped_lock
    : private noncopyable
  {
  public:
    // Tag type used to distinguish constructors.
    enum adopt_lock_t { adopt_lock };

    // Constructor adopts a lock that is already held.
    scoped_lock(conditionally_enabled_mutex& m, adopt_lock_t)
      : mutex_(m),
        locked_(m.enabled_)
    {
    }

    // Constructor acquires the lock.
    explicit scoped_lock(conditionally_enabled_mutex& m)
      : mutex_(m)
    {
      if (m.enabled_)
      {
        mutex_.mutex_.lock();
        locked_ = true;
      }
      else
        locked_ = false;
    }

    // Destructor releases the lock.
    ~scoped_lock()
    {
      if (locked_)
        mutex_.mutex_.unlock();
    }

    // Explicitly acquire the lock.
    void lock()
    {
      if (mutex_.enabled_ && !locked_)
      {
        mutex_.mutex_.lock();
        locked_ = true;
      }
    }

    // Explicitly release the lock.
    void unlock()
    {
      if (locked_)
      {
        mutex_.unlock();
        locked_ = false;
      }
    }

    // Test whether the lock is held.
    bool locked() const
    {
      return locked_;
    }

    // Get the underlying mutex.
    boost::asio::detail::mutex& mutex()
    {
      return mutex_.mutex_;
    }

  private:
    friend class conditionally_enabled_event;
    conditionally_enabled_mutex& mutex_;
    bool locked_;
  };

  // Constructor.
  explicit conditionally_enabled_mutex(bool enabled)
    : enabled_(enabled)
  {
  }

  // Destructor.
  ~conditionally_enabled_mutex()
  {
  }

  // Determine whether locking is enabled.
  bool enabled() const
  {
    return enabled_;
  }

  // Lock the mutex.
  void lock()
  {
    if (enabled_)
      mutex_.lock();
  }

  // Unlock the mutex.
  void unlock()
  {
    if (enabled_)
      mutex_.unlock();
  }

private:
  friend class scoped_lock;
  friend class conditionally_enabled_event;
  boost::asio::detail::mutex mutex_;
  const bool enabled_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_CONDITIONALLY_ENABLED_MUTEX_HPP

/* conditionally_enabled_mutex.hpp
+m9SpiYTAGdRHAyaFwKCzQSVak6+D9oh33G8krgAz60OP0evQAjPc8dEgSmtegskzeVYdhkuAIwGzYsqRQfRLeysQHthFwxx4JxnhlrFyCeiCRhH/mE51t8sw9IiGhFADP+xqpEXeZ/L7iJram1ljMrKyFVHn+wO43P4CGNb86mb5wgm/uu/0I/JCO2Pgssa4U12c7Rzgcab/6E3QASIsMO4eCXBQGuFqliYZsYQLfGubW4lVdjwA7ehiO1ug6xDsHBdDIBtAQRaIe/rtKb29BJ0NqUHenvVfDos3qHLXdqDNNLRxJFNrSDm3HkpE5b5N7qh7lJ56fmQQlFYDS0AW7tw/dwjGudJrxaHjRSvGL5JCLRmYsAU9Alaq8+uzIs8TP3vCDv9cvDHUdjoU/G/wvNgb/SXDXmd1Fps8Y4S4CcqKkRUrWEHSnOtR0j5cSgq8efxOWwg7W93TLN045c7z8sG4/nvnhg9ZI6LfgT7PnjoV40sLEsksVfX2YQzGGLoMfLSaXKkGWcXjbO64qKbE694FUDWh/mN6MxL9IMD6XTQnmom5Fy5h0UbHQ==
*/