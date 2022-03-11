//
// detail/posix_event.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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