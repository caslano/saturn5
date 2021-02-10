//
// detail/win_static_mutex.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_STATIC_MUTEX_HPP
#define BOOST_ASIO_DETAIL_WIN_STATIC_MUTEX_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS)

#include <boost/asio/detail/scoped_lock.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

struct win_static_mutex
{
  typedef boost::asio::detail::scoped_lock<win_static_mutex> scoped_lock;

  // Initialise the mutex.
  BOOST_ASIO_DECL void init();

  // Initialisation must be performed in a separate function to the "public"
  // init() function since the compiler does not support the use of structured
  // exceptions and C++ exceptions in the same function.
  BOOST_ASIO_DECL int do_init();

  // Lock the mutex.
  void lock()
  {
    ::EnterCriticalSection(&crit_section_);
  }

  // Unlock the mutex.
  void unlock()
  {
    ::LeaveCriticalSection(&crit_section_);
  }

  bool initialised_;
  ::CRITICAL_SECTION crit_section_;
};

#if defined(UNDER_CE)
# define BOOST_ASIO_WIN_STATIC_MUTEX_INIT { false, { 0, 0, 0, 0, 0 } }
#else // defined(UNDER_CE)
# define BOOST_ASIO_WIN_STATIC_MUTEX_INIT { false, { 0, 0, 0, 0, 0, 0 } }
#endif // defined(UNDER_CE)

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/win_static_mutex.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // defined(BOOST_ASIO_WINDOWS)

#endif // BOOST_ASIO_DETAIL_WIN_STATIC_MUTEX_HPP

/* win_static_mutex.hpp
A5FriYDHstAJhVibrNoFJsl4tcBzkRPQ9q/g5EqDoSlt2YF3J9dvzt9ew7v9y8v9s+v3cH4M+2fvEevPk7NDtLeNlAIQ934gJFIOwJ75ji0sJvjjPo3G7lBM0FdG3mwm3LDRULKgE6FhJsIVgRmicknumen65gRFbhzdm8iN2KIBPd+BHZqN6n4NH0gp8iO8BvaAjUbjUNyC6yHGVqPxTqC9hQsvbdePwpesQUmeujUKHFRuYLrSMcnXQDdxVtfzSX0I/QA+Phh7aIY2TmiMTCngTijvPbg8PcZV4AoQrmW7E4Z8Z7uWdycBjQAmxzQUAj3UEmMzckL2hdPjXuOti6hh5KKYzgOgr0ghZmTNmeBZtL5uUHj5ICf4dGS6LXRzFJYcHiaONzQdYHm6nus8NJQouC5sGsZkhgKkL0b22FbuIMzRVC1M1gbSRwe7DxUKqncXxUgNsjuK0CqzB3iBSwXXbBBuJ1eO507UxVQ4fnZlBpPsIhCWHWSXfuCFXnY5MmMU9LwJBhmyM90A10T5b3HZoDE6GB9CXB+JFwC5AZCHu5OGjIaJZ+Cyha8NCoQIrTdv2rt7g+3kuumon/ZYb8a8f23ezAGtpmnteB591mDohVNgUeEVc5M+azqwC1q/Pz7par08TE/rQLfb
*/