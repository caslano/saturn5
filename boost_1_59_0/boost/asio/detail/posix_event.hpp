//
// detail/posix_event.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_POSIX_EVENT_HPP
#define BOOST_ASIO_DETAIL_POSIX_EVENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_PTHREADS)

#include <cstddef>
#include <pthread.h>
#include <boost/asio/detail/assert.hpp>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class posix_event
  : private noncopyable
{
public:
  // Constructor.
  BOOST_ASIO_DECL posix_event();

  // Destructor.
  ~posix_event()
  {
    ::pthread_cond_destroy(&cond_);
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
    ::pthread_cond_broadcast(&cond_); // Ignore EINVAL.
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
      ::pthread_cond_signal(&cond_); // Ignore EINVAL.
  }

  // Unlock the mutex and signal one waiter who may destroy us.
  template <typename Lock>
  void unlock_and_signal_one_for_destruction(Lock& lock)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    state_ |= 1;
    bool have_waiters = (state_ > 1);
    if (have_waiters)
      ::pthread_cond_signal(&cond_); // Ignore EINVAL.
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
      ::pthread_cond_signal(&cond_); // Ignore EINVAL.
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
    while ((state_ & 1) == 0)
    {
      state_ += 2;
      ::pthread_cond_wait(&cond_, &lock.mutex().mutex_); // Ignore EINVAL.
      state_ -= 2;
    }
  }

  // Timed wait for the event to become signalled.
  template <typename Lock>
  bool wait_for_usec(Lock& lock, long usec)
  {
    BOOST_ASIO_ASSERT(lock.locked());
    if ((state_ & 1) == 0)
    {
      state_ += 2;
      timespec ts;
#if (defined(__MACH__) && defined(__APPLE__)) \
      || (defined(__ANDROID__) && (__ANDROID_API__ < 21) \
          && defined(HAVE_PTHREAD_COND_TIMEDWAIT_RELATIVE))
      ts.tv_sec = usec / 1000000;
      ts.tv_nsec = (usec % 1000000) * 1000;
      ::pthread_cond_timedwait_relative_np(
          &cond_, &lock.mutex().mutex_, &ts); // Ignore EINVAL.
#else // (defined(__MACH__) && defined(__APPLE__))
      // || (defined(__ANDROID__) && (__ANDROID_API__ < 21)
      //     && defined(HAVE_PTHREAD_COND_TIMEDWAIT_RELATIVE))
      if (::clock_gettime(CLOCK_MONOTONIC, &ts) == 0)
      {
        ts.tv_sec += usec / 1000000;
        ts.tv_nsec += (usec % 1000000) * 1000;
        ts.tv_sec += ts.tv_nsec / 1000000000;
        ts.tv_nsec = ts.tv_nsec % 1000000000;
        ::pthread_cond_timedwait(&cond_,
            &lock.mutex().mutex_, &ts); // Ignore EINVAL.
      }
#endif // (defined(__MACH__) && defined(__APPLE__))
       // || (defined(__ANDROID__) && (__ANDROID_API__ < 21)
       //     && defined(HAVE_PTHREAD_COND_TIMEDWAIT_RELATIVE))
      state_ -= 2;
    }
    return (state_ & 1) != 0;
  }

private:
  ::pthread_cond_t cond_;
  std::size_t state_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/posix_event.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_HAS_PTHREADS)

#endif // BOOST_ASIO_DETAIL_POSIX_EVENT_HPP

/* posix_event.hpp
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
*/