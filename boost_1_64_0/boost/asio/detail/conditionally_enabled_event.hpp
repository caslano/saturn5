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
Ifwq5jXjZge95WWAz2bEP4EBAzxUGe++KjlZL1vR3PBr/BTLX4RrWK3PNuxz521QF1LPQzsYEklcPc56b1oXXNA6vjMjPLqv4nJufi/vIXd+advboCBicSCY9pHq4kiiMs3WuYG1es7ZrpQYtN2gIoX8CY1mPaXFUsxZYJgWgZbzrr7PWaTwmvEcbVkpJiLD5YdfXt6B9oDxRQ5EZ41k8/HB8OtC6ml0kD8RKRLTeveViHJ/sZpz92z27do+oEMZ+HXWaloMCMQEGekPXJ30txZWUZUNOeKee4rUGsXH3BGAc04tqaiuI0TQSRP0eX+wGL3gwqLIECj994BHrdK4x3B7Utrrn5h8zmqNGCeb1SrqlzOdGdnr6uDRKRJCJfuGo7UNe0cxwDFwK1XrEr1U+OWxJXF0Yce9OXCcWQKZrG2VY2lENl/pOjWEzTAQqJjdMBd+cYEJ0L6i2bHGOif2etpsJi/HJ5CtBrbdZK5haREaazbwiJ/SltkMW+rFo9pRNl8nvtzwynzGee2N6XiHJMADARYXacx41IAehoS0rs4+5Pfu8mfhCFdQgg==
*/