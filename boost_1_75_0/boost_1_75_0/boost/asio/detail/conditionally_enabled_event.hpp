//
// detail/conditionally_enabled_event.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_CONDITIONALLY_ENABLED_EVENT_HPP
#define BOOST_ASIO_DETAIL_CONDITIONALLY_ENABLED_EVENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/conditionally_enabled_mutex.hpp>
#include <boost/asio/detail/event.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/null_event.hpp>
#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Mutex adapter used to conditionally enable or disable locking.
class conditionally_enabled_event
  : private noncopyable
{
public:
  // Constructor.
  conditionally_enabled_event()
  {
  }

  // Destructor.
  ~conditionally_enabled_event()
  {
  }

  // Signal the event. (Retained for backward compatibility.)
  void signal(conditionally_enabled_mutex::scoped_lock& lock)
  {
    if (lock.mutex_.enabled_)
      event_.signal(lock);
  }

  // Signal all waiters.
  void signal_all(conditionally_enabled_mutex::scoped_lock& lock)
  {
    if (lock.mutex_.enabled_)
      event_.signal_all(lock);
  }

  // Unlock the mutex and signal one waiter.
  void unlock_and_signal_one(
      conditionally_enabled_mutex::scoped_lock& lock)
  {
    if (lock.mutex_.enabled_)
      event_.unlock_and_signal_one(lock);
  }

  // If there's a waiter, unlock the mutex and signal it.
  bool maybe_unlock_and_signal_one(
      conditionally_enabled_mutex::scoped_lock& lock)
  {
    if (lock.mutex_.enabled_)
      return event_.maybe_unlock_and_signal_one(lock);
    else
      return false;
  }

  // Reset the event.
  void clear(conditionally_enabled_mutex::scoped_lock& lock)
  {
    if (lock.mutex_.enabled_)
      event_.clear(lock);
  }

  // Wait for the event to become signalled.
  void wait(conditionally_enabled_mutex::scoped_lock& lock)
  {
    if (lock.mutex_.enabled_)
      event_.wait(lock);
    else
      null_event().wait(lock);
  }

  // Timed wait for the event to become signalled.
  bool wait_for_usec(
      conditionally_enabled_mutex::scoped_lock& lock, long usec)
  {
    if (lock.mutex_.enabled_)
      return event_.wait_for_usec(lock, usec);
    else
      return null_event().wait_for_usec(lock, usec);
  }

private:
  boost::asio::detail::event event_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_CONDITIONALLY_ENABLED_EVENT_HPP

/* conditionally_enabled_event.hpp
CjNv8R9+RsZC1+67P9wGzepskvVIgPd8Rka/xTJYIT7p2VC8BZQj72N4l2h9l6ZExPttMWgwucnhte63kVFXKBGDvdz+3kIUi3KYF0tzoEVJwn5RqMXA4V0YxQe/8VgcAOu5NYDHf1/pzo7GfYiP5dYCvFtbmlsvdUfQPYeBt1krcM0aJR09aFsBlCIKT6R9BcrplHTR+rS0DlEvWjdIQq2DbF6M7keaumwxRoLkbUNS+dNiPKlYJlqrnTbSNoS6x6gzAsOvZoahK6g2IFQ7yOglalwJnryirWnBfe+pMaGfUteRkb6eE3yNp3NcGBe7yUb2mmCR6CayqNtqXOi15Oh7AXZ+XRiGdeTx08gRpw3v4KuVz735Gx5BE+IeI8cuRyc3D6GuZVyNw22kKbol4CCN0Ugg+wkY+jR+ZUMq8u5q0diwVgnRRYKANekdoEzPdTg9JjlWpeE2anbx9EbT16AXJ9lMe35e7vlJ2rPF9wawSRaPaiPDr5CjUbfSg/CcHKtLw8HJYBeASYN1MVbX7EHfB0bIffq+HOQaEpYb/66KORBHAcRQ3X04d05SfR+OV47iSWtcNg8KbU7y4ztqixTkx00OJ1n3rpxJ7SoNToH8XDqHA72GToZTYAi+uEljG1YxTiNZtzZcxX7SO+micPQvR1Es5+9wkOeiGAok+iogVLAzhoGjIFzCA8LmwFEyLEXGt5T1Lnp3JOsm
*/