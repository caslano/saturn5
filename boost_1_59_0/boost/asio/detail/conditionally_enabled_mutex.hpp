//
// detail/conditionally_enabled_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
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
*/