//
// detail/conditionally_enabled_event.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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

  // Unlock the mutex and signal one waiter who may destroy us.
  void unlock_and_signal_one_for_destruction(
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
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
*/