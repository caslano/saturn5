//
// detail/std_event.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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