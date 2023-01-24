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
nonTL3F6JU6fxOmROP0Rpzfi9EWcnojTD3F6IU4fxOmBOP0Pp/fh9D2cnofT73B6HU6fw+lxOP0Np7fh9DWcnobTz3B6GU4fw+lhOP0Lp3fh9C2cnoXTr3B6FU6fwulROP0Jpzfh9CWcnoTTj3B6EU4fwulBOP0Hp/fg9B2cnoPTb3B6DU6fwekxOP0Fp7fg9BWcnoLTT3B6CU4fwekhfusfiN6B0zdwegZOv8DpFTh9AqdH4PQHnN6A0xdwegJOP8DpBTh9AKcH4N7/c+/9uff93Hv+vsM7yFdfbYYT+cygH3eaQbn01txZD5uh//Xw662RzeBRUODcIxbJKy7T6dj4Zljf4+CWlhfN0M/U5HBxWjOEJ8mluWU1Q+7aedfu5jTDHD49+nF+Mwwzs1sZUNQM3w1dDPq+bIb9752DQ141wxK1IT2K3iDpVy3rZnNZM3DyCbduclKA+J6wAualWiqs6HvJNDNjhtXtW7dixbqG5l3iO90M2ne5GZuYuFkmqavtHcXe3qeuEpLCvtrF7/e0T7HPxjni2+XUdfksvRC/ndb2FPtDq6NWqm+8+iYdHLrMvwLw+zkXxDwobyLopB5XIS8b78ba6+CV00llnziOSuTbRxF/iRs94PvyKpCnWje1hfH4tSNPHPkP/AlqsTtePBe+RDz2FkMUxrG7+PPSC1vxS2z8iW6E2LNQ/PluR2NbcSR66HmkSQr7
*/