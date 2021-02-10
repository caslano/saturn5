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
FmYncv+MvCxocZE0CkcE7R6TbrEYxG3fxlFwRmEZljvb6sQMthdBzA1Z7A7SCG3r2HsxY7QlAz94CZMB91Oxnd0f9BXxAHpscGppFozUUjoeHnmZ99uwadhF9CfUM5OjCTg5+mUdTvwSFgIvP43VgP5Nl988eSsdfg1puTwbagdQ3qhP2Ip9AvO/TiNBwNphaeeYmSD9YW3Wpu0tGaz2N3VRp85TBlE3TKDBw4R8WkGcgvHc3adNRpgaASR0WzUtsy/Deu+U/T6rpILGzgUwb5F5Wuc62dbEvmijUj0Cv7STk+aEK7cbU3OlIjESEwejJ/b1R+pnKDYJov/6bNF1jT86PCTb3JvD0hX+sNBRtXzRLauDLHtrbqowtVBvmVy346OeOWTcpUFJL32YckrM6zwss5jeDs6y2xiuCwaj8uOrsZ3WN5oozuk4G+f0nVw0CoFRaIrJRQlbXCPrWgS7aVvY4dneB9uZTTbXCJly70CVqzbFIrepfkFPMTRILfSysjc1c7KYr1rph7crFG6M1mEW06nofWS7FKz0djp9cs30pxbWIJD20nEFWxrUIWnkYzN8MeWo3CEfr8h4lFlZNqD3nWmiqjWovW2YCjrZJTlUcQ4DPM5NWmcanyAgWVtCFF1uabIUL+UsV+9N
*/