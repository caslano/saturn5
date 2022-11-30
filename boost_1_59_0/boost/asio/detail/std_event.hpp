//
// detail/std_event.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STD_EVENT_HPP
#define BOOST_ASIO_DETAIL_STD_EVENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)

#include <chrono>
#include <condition_variable>
#include <boost/asio/detail/assert.hpp>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class std_event
  : private noncopyable
{
public:
  // Constructor.
  std_event()
    : state_(0)
  {
  }

  // Destructor.
  ~std_event()
  {
  }

  // Signal the event. (Retained for backward compatibility.)
  template <typename Lock>
  void signal(Lock& lock)
  {
    this->signal_all(lock);
  }

  // Signal all waiters.
  template <typename Lock>
  void signal_all(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    (void)lock;
    state_ |= 1;
    cond_.notify_all();
  }

  // Unlock the mutex and signal one waiter.
  template <typename Lock>
  void unlock_and_signal_one(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    state_ |= 1;
    bool have_waiters = (state_ > 1);
    lock.unlock();
    if (have_waiters)
      cond_.notify_one();
  }

  // Unlock the mutex and signal one waiter who may destroy us.
  template <typename Lock>
  void unlock_and_signal_one_for_destruction(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    state_ |= 1;
    bool have_waiters = (state_ > 1);
    if (have_waiters)
      cond_.notify_one();
    lock.unlock();
  }

  // If there's a waiter, unlock the mutex and signal it.
  template <typename Lock>
  bool maybe_unlock_and_signal_one(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    state_ |= 1;
    if (state_ > 1)
    {
      lock.unlock();
      cond_.notify_one();
      return true;
    }
    return false;
  }

  // Reset the event.
  template <typename Lock>
  void clear(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    (void)lock;
    state_ &= ~std::size_t(1);
  }

  // Wait for the event to become signalled.
  template <typename Lock>
  void wait(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    unique_lock_adapter u_lock(lock);
    while ((state_ & 1) == 0)
    {
      waiter w(state_);
      cond_.wait(u_lock.unique_lock_);
    }
  }

  // Timed wait for the event to become signalled.
  template <typename Lock>
  bool wait_for_usec(Lock& lock, long usec)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    unique_lock_adapter u_lock(lock);
    if ((state_ & 1) == 0)
    {
      waiter w(state_);
      cond_.wait_for(u_lock.unique_lock_, std::chrono::microseconds(usec));
    }
    return (state_ & 1) != 0;
  }

private:
  // Helper class to temporarily adapt a scoped_lock into a unique_lock so that
  // it can be passed to std::condition_variable::wait().
  struct unique_lock_adapter
  {
    template <typename Lock>
    explicit unique_lock_adapter(Lock& lock)
      : unique_lock_(lock.mutex().mutex_, std::adopt_lock)
    {
    }

    ~unique_lock_adapter()
    {
      unique_lock_.release();
    }

    std::unique_lock<std::mutex> unique_lock_;
  };

  // Helper to increment and decrement the state to track outstanding waiters.
  class waiter
  {
  public:
    explicit waiter(std::size_t& state)
      : state_(state)
    {
      state_ += 2;
    }

    ~waiter()
    {
      state_ -= 2;
    }

  private:
    std::size_t& state_;
  };

  std::condition_variable cond_;
  std::size_t state_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)

#endif // BOOST_ASIO_DETAIL_STD_EVENT_HPP

/* std_event.hpp
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
*/