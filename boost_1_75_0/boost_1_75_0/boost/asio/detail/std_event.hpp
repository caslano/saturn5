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
jH8AHqbEq+IPCIVqU3IsmjXCCRXe7TMt5mrn1y8ZqAlo6xWsa0wV2z5pFBW8SH7SJF0/PjUPJafAP0D48Rq9hlyUaOTJ9l24EUCnhT/fR1kYfMRZd4XviQX6KkKTh6zbRg8T1ME8Ge0id4loiSCwLRmVi9jezfm64ty3moZ9TqpZtj7JbCI0HMsFJ7bPjE+6debEpKStqfCUY3uk2D4HoufcmlRxbmso8FYIrIbAtNMz2HZQSDN/WjCJH+HW6OxBSLSAsvJGCBx8vb2aLg95Y3n4eO0pV8X9g82X9KCEOz3Hsvl+alwv3sEJeXgmhDw0lJ7Yy686zs9nyUR/ou8R6o1toEQDHI1lY8XaCPHuK4p4n4krbrhL4WLkfr4Fmvn9XVcc/tJmNXe9Gaopfy6tZilVFgSCuO/+CdBBKupXoHu7cCRszGWktexWfSTgSVtiq2Ij4RKVFGzV6ITIMZlx+g85dYMISeiza0dDmpI9ssG2Da90c5OGZbhfelDKuWa/dIFn/nw3KX2T7lBhUZ/C9H8YZjX+HiAmzguZ87TIMxB1CKNSoRSH84xgdnzKj/FyuS43SWWJ0pTAQLJzoj5CnltAWwb9GLbvQndYGwJj0ddxeYubmJbRAVbK0pL8UPaNMWynNTsu/HxTz/FFTlI+vLEJ8NoUq8+a8SRRLTFKL7EVnZKRfSLD61WVw/wzbAY99iMzKDu17KHrFRWl
*/