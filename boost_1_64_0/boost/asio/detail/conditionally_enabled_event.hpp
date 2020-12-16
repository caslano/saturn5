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
KC3KCB9RVpQT5UUFUVFUEpVFFVFVVBPVRQ1RU9QStUUdUVfUE/VFA+ErGopGorFoIpqKZqK58BMtREvRSrQWbURb0U60Fx1ER9FJdBb+oovoKrqJ7qKH6Cl6id6ij+gr+on+IkAMEIFioBgkBoshYqgYJoaLEWKkGCVGiyAxRowV40SwGC8miIlikpgspoipYpqYLmaImWKWmC3miLlinpgvFoiFYpEIEYvFErFULBPLxQoRKlaKVWK1WCPWijCxTqwXG8RGsUlsFlvEVhEutokIsV3sEDvFLrFb7BF7xT4RKfaLA+KgOCQOiyPiqDgmjosT4qQ4JaLEaXFGnBXnxHlxQUSLi+KSiBGXxRVxVVwT18UNcVPcErfFHXFX3BP3xQPxUDwSj0WsiBNPxFPxTDwXL8RL8Uq8Fm/EW/FOvBcfxEfxSXwW8eKL+Cq+iQTxXfwQP8Uv8Vv8YfulVFJLI6100iMTycQyiUwqk8nkMoVMKVPJ1DKNTCvTyb9keplB/i3/kf+R/5UZZSaZWWaRWaWXzCb/ldllDplT5pK5ZR6ZV+aT+WUBWVAWkoVlEVlUFpPFZQlZUnrLUrK0LCN9ZFlZTpaXFWRFWUlWllVkVVlNVpc1ZE1ZS9aWdWRdWU/Wlw2kr2woG8nGsolsKpvJ5tJPtpAtZSvZWraRbWU72V52kB1lJ9lZ+ssusqvsJrvLHrKn7CV7yz6yr+wn+8sAOUAGyoFykBwsh8ihcpgcLkfIkXKUHC2D5Bg5Vo6TwXK8nCAnyklyspwip8ppcrqcIWfKWXK2nCPnynlyvlwgF8pFMkQulkvkUrlMLpcrZKhcKVfJ1XKNXCvD5Dq5Xm6QG+UmuVlukVtluNwmI+R2uUPulLvkbrlH7pX7ZKTcLw/Ig/KQPCyPyKPymDwuT8iT8pSMkqflGXlWnpPn5QUZLS/KSzJGXpZX5FV5TV6XN+RNeUvelnfkXXlP3pcP5EP5SD6WsTJOPpFP5TP5XL6QL+Ur+Vq+kW/lO/lefpAf5Sf5WcbLL/Kr/CYT5Hf5Q/6Uv+Rv+Yfil0oprYyyyimPSqQSqyQqqUqmkqsUKqVKpVKrNCqtSqf+UulVBvW3+kf9R/1XZVSZVGaVRWVVXiqb+ldlVzlUTpVL5VZ5VF6VT+VXBVRBVUgVVkVUUVVMFVclVEnlrUqp0qqM8lFlVTlVXlVQFVUlVVlVUVVVNVVd1VA1VS1VW9VRdVU9VV81UL6qoWqkGqsmqqlqpporP9VCtVStVGvVRrVV7VR71UF1VJ1UZ+WvuqiuqpvqrnqonqqX6q36qL6qn+qvAtQAFagGqkFqsBqihqphargaoUaqUWq0ClJj1Fg1TgWr8WqCmqgmqclqipqqpqnpaoaaqWap2WqOmqvmqflqgVqoFqkQtVgtUUvVMrVcrVChaqVapVarNWqtClPr1Hq1QW1Um9RmtUVtVeFqm4pQ29UOtVPtUrvVHrVX7VORar86oA6qQ+qwOqKOqmPquDqhTqpTKkqdVmfUWXVOnVcXVLS6qC6pGHVZXVFX1TV1Xd1QN9UtdVvdUXfVPXVfPVAP1SP1WMWqOPVEPVXP1HP1Qr1Ur9Rr9Ua9Ve/Ue/VBfVSf1GcVr76or+qbSlDf1Q/1U/1Sv9UfWr/USmtttNVOe3QinVgn0Ul1Mp1cp9ApdSqdWqfRaXU6/ZdOrzPov/U/+j/6vzqjzqQz6yw6q/bS2fS/OrvOoXPqXDq3zqPz6nw6vy6gC+pCurAuoovqYrq4LqFLam9dSpfWZbSPLqvL6fK6gq6oK+nKuoquqqvp6rqGrqlr6dq6jq6r6+n6uoH21Q11I91YN9FNdTPdXPvpFrqlbqVb6zY=
*/