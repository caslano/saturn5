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
NcExZD3oMW5NgxFp0FR9Fa6rvtPeQM0QREyQx0VhvP8KSe4g8Qk5u3DNJuGtYIpiIIdGhKkuHT5x9R0zGHoDKXk8ChsxIMJhaR4aU3tfhYyY5Elf3r/+++cKdYMyqTeTKT9LMuQMVjmNQp6T6i/p4pg2wD9qnjdorccd3JEESql1f3BiP0Hg0czopL2gBmhF6nKsK/aFkRnivDTEy4y9hkFa/BA2gV1QZz+WyP83bq6TufwVMMKmbow2fy3zFT7K6TqMI1JBxrHoJUKvXr1UX8XiRZNcJ8LdpjFq7/eV7fZGMfGHrooi7k3eXk7e7wFVm3T+8gF2Jc9Ik7/39eSbs7fqZPL+8uz07OT4chImWxB5s/Ntsu1St6y9eSIdTZo6Kk5zFKLUnU6t3E4jmRrZ0h2pvWifRHsHVUQjUcXbgmNBTAASvyOHvRhW/Rm0bpFWYiwMowdZ2oj3yt1IAVLnzt2qyIP0ntJqOz0+qguqAJHYudAPxGK0W48+htsdwObqX2SG3sosZ2wrOAMOlJJWjRnBchUCeHddOBWMTdxSLjfrtGWv/UBqRsKr4ZJjG/Ef6xypZihZm6AkR99B1Q2pBgiMRSq0QvWdbV29JPLvdGul97xmc4bO7Orr79++OZ9cpzBn1g8N4zxwKBbO
*/