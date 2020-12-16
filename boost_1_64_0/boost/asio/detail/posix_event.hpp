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
XXWc80QQDRzu7u4Od3y4lrYHhbve0RY/CL02dwRqNC3u7u7u7u7u7u7u7j47MyuR4n8g2R/lu7z3dnd2VrJJdpN+t9Sse/WR1hzJxZMLLzxHf753jmUWW2KJSSeaKZW3IExhWWPDP8kJLKuysIUhMYEVhzjEIQ5xiEMc4hCHOMQhDnGIQxz+ReGWH36OQxziEIc4xCEOcYhDHOIQhzjEIQ7/8bBslxUHCPFtkDjEIQ5xiEMc4hCHOMQhDnGIw385THxf91jL4jp//GEQ+Dj4b5c6Dv47mdU1bRv+nht+n1jWpwtZXVNNOm0Xp9Es21s421qff/apwFqoadbbtbInsB5r3GnHhm0FY4FWhi+souOJSLbXshZbJbGOPlx1VeuzTyeyxppiDtCNhX+PPUUXxJ0EjgTeZeDjMj6VNdZUAh8HjucYz7LGg38nsyaYgkrUZY0Px0I/AeuFTZa1y9iWGX6HTRNNofOe2LCpxTbNBnaMp+wgf03Cf0/qs2k8azI4jtKPx39PGNBPAcdzgX78Dum3QnmMb00Fx/NBnAk65NESPyuY1wTWNHAsytXmcon6n24KEVckZOFxFx6jwMcvAO0D4k41FvzdGE+mS8KZuB5mZt9JXVdANyvrZmPdVdzeWsi3qrbnlMz2No7Aqm7NxCYQ2Gb1dtPS2CSoKxe3NbApEKv74k4jsG2dohl3BoFt7Y87C+r82BwCc70ytKJP54J2NiG0/TmMtj8P8Ni+WlXVrhpGm55LlHmcsbD8c3P5JwM/jS3iTgE/rivyxdjWvOyr+ViLaQT8uwDHgfrAnBbkOAsZccY18l0kkO+iU8AvkO9inMbirJVjwtRUR1uZdTSVqA+B1QCEci7GY0K39AvVg1t1vAYIhHfkAfposcj+6rWKpS1kb5UHqOdy63GAyz2GbV7KLB/rxguUbxnWLsva3kgbbLvUbNmVeqlYcexG3a21nKaHBkUyq66KaS7Pac7EPiP77MFKseRsVq+UnSaMsZDfWGDIitJH6EPbrQ+3RzAD+hPL2xPpT1v6cOkxFEEfQ6yVf7s85WKriDFDKJdjld/hm2q70nKHt235kgsTWA6RZiLQnlbFMkHebm2kzv1stSmEL6rDEuvl8ifN8v+JugmeRyYJnEfS3CamM/rNRKFzEI3Da8j2xHEzcDwdaMbxpR8cs8ex1oLjhbq6php72i5INTnQn+lPrJ62e/sSq+ftTN9Atm8DS3BjB7kle1bLFHLptdfJ5NIp61OhGScc3+7LrJZL5CiNCYJ8vpAbyK6eTfSn85nVs5DMZ5jOFEFdNlHIrJu209lCboPBgUy2wPntYoVtLuQSybVS6dXWWT2VKCQs1nWwfzCX7k3noACqjDl73XQunxnI2v2JNcVRD+QVzWGccf14Jsv4BIin0n3pQjpliyLafens6oU1oIyaX7eQWK0vvXpi0KeguuBCFzYYTEN+69vJ1azPKe7PGDfT158urDGQsvPpZMHO9yf6+lAnip3PbJi2PqV0qNAQA6xbw6Y4uXUTbMfYAT69huYmCHCrQbrJ1foGkmvJtHUZyJ/KVxpfeozCxzHx3txAv71Otj+RhSxS5LPOvJ1LFxKZrJ0YHEwN9MNf0hdTmHGS6IOBfAEcn8usK9vlHEY50onCmnZhjXWya9noJMFb46B/+xL5PNaDSFvjg9CeIDYxn+as8aedEZqT6Gf90HdyTkMMo16y3lyj3My2q07TLaWcEbfmYOdfb8yvKVZdVeS1k4X9D1IcrG/tNNfxnOZg0/GcWov9rPFsvcWUrD/NZWrFUsvdysEydWm8v7iNW21XKa0uU79VseKWrU97oUzjcpkGoEz2Ovl0zk4kof0=
*/