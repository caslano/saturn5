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
i4/QTEF6sExIJa+v37DZnsh4o09CfvWoYCVOo+GBqUUxyRSNsWoIfQORO2+gCtTzvMn4dx9iVtzMlS0OIGPCSFnFk0RFKdFNJo7Qs8GuUkpP1R3vgOIur/fs9SRpIIKsv95/YM0QTJEFVGSFrc2EjQ+4f9j0D29PDgYH+wLnldm3tqrzN6D055fHbwJjlrQ4ij/MC5gBum5GXfQhqC7LavRkSrOXHGlD8CItpxu0YNWeq+ug5LfCGP7wX/qfKApMhNE3TITRmnElDyBLMi+4KugdAF4ooHDksJNe/LPaX2mrrYVg1WrKFRRhP/wEHckhEjHhPkt7MvB1JiS5aWb1q+3tOzmW82FPSOk2pqz/M5tPJtu7u4dHWMFTDJlR++4v+gjrwWRbe7KeMaPJK4u4JqnEEcmbH54yv7yuhQhv7+30DzDDdRtqxM1/sfLwBc/n9dnlyY/nZ2+P37z5wJMExiBU2LVtm0ba1pqSqi4EjNflJKlkaUAdksYEpi6RWEaTJFc6LfsFmUYalUNwtibryV6XHgfOrj4ftNaowLgAeHra7d7XOJg4s8selvrQNgxPQxarktP26jwURSa0SnkIpU2SN2nvehnRkisEbygHUOSSOgc5k7+1Q8f8YBiN1aJVPwmD3A7tHXKHHrde
*/