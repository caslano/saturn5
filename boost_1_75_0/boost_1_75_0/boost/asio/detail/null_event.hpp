//
// detail/null_event.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_EVENT_HPP
#define BOOST_ASIO_DETAIL_NULL_EVENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class null_event
  : private noncopyable
{
public:
  // Constructor.
  null_event()
  {
  }

  // Destructor.
  ~null_event()
  {
  }

  // Signal the event. (Retained for backward compatibility.)
  template <typename Lock>
  void signal(Lock&)
  {
  }

  // Signal all waiters.
  template <typename Lock>
  void signal_all(Lock&)
  {
  }

  // Unlock the mutex and signal one waiter.
  template <typename Lock>
  void unlock_and_signal_one(Lock&)
  {
  }

  // If there's a waiter, unlock the mutex and signal it.
  template <typename Lock>
  bool maybe_unlock_and_signal_one(Lock&)
  {
    return false;
  }

  // Reset the event.
  template <typename Lock>
  void clear(Lock&)
  {
  }

  // Wait for the event to become signalled.
  template <typename Lock>
  void wait(Lock&)
  {
    do_wait();
  }

  // Timed wait for the event to become signalled.
  template <typename Lock>
  bool wait_for_usec(Lock&, long usec)
  {
    do_wait_for_usec(usec);
    return true;
  }

private:
  BOOST_ASIO_DECL static void do_wait();
  BOOST_ASIO_DECL static void do_wait_for_usec(long usec);
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/null_event.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_DETAIL_NULL_EVENT_HPP

/* null_event.hpp
+czBOrgMpj0IwhGePVmIhQxMMOdFt2rd+ShmYMXzWJuy6oRs4tzN7zKPM0Z2wiMQl+dlNQqj1eyRSqBBn3HBD75Ft/KOw2Qqkg/A3zIltkje5yAniyGGWUgM70K/L1+XjZErZZ5VexOxSSv4eMlvxyYS0qOdF9t4h7pFLx4YwtL9mvbIHr3+XIcGSD9huNwvy851gBKgi0s/wsIc2subYhCpzphnzyS9IEdFCQYuNpYL79Dz7DX5LM/+Gwc/TteyPLskkme/cjvk2XHSSeld7w70Yr5da+gvMpTluug6yrlIpu3sjWTaKHuUad/ay4Q1y+/BNxc5WQnyfRxm2qs5zLTzCTnOZk9Cps3qoPqCyyCVr47DfNsC3zLyId/+Zii2D+XFuyOdWsliGMr0T/p2XEx3cugv5dw7KOfeQTn3Dsq5d7CcG3272bcDJRFomFgkj1/HqL0xTIYGdI50qfo5Q87t13PuXTwJ9RpdetzHOM9SdAPbCd/YjgGCuM/mo5/Skh7fdnKy0Un301FJ96N9k26kMXgPJt35LOlerCbdp7Wkm/RcfI6i02ChlnQvVpPu08E5atJ9RZ+k+3w16U5Vk+5RLOmmtvbu99JnMG7QpPu5qKT7CzS9+WrSHVKT7o06v6LegYSeku7d+u1eP4VZTewGJN3sJQPbg9XUVuRfJOlugqQ7brCk+2rx7TQxDOk2zqkRw5huhyndRuly
*/