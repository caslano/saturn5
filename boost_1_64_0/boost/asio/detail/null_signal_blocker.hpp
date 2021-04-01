//
// detail/null_signal_blocker.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_SIGNAL_BLOCKER_HPP
#define BOOST_ASIO_DETAIL_NULL_SIGNAL_BLOCKER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS) \
  || defined(BOOST_ASIO_WINDOWS) \
  || defined(BOOST_ASIO_WINDOWS_RUNTIME) \
  || defined(__CYGWIN__) \
  || defined(__SYMBIAN32__)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class null_signal_blocker
  : private noncopyable
{
public:
  // Constructor blocks all signals for the calling thread.
  null_signal_blocker()
  {
  }

  // Destructor restores the previous signal mask.
  ~null_signal_blocker()
  {
  }

  // Block all signals for the calling thread.
  void block()
  {
  }

  // Restore the previous signal mask.
  void unblock()
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_HAS_THREADS)
       // || defined(BOOST_ASIO_WINDOWS)
       // || defined(BOOST_ASIO_WINDOWS_RUNTIME)
       // || defined(__CYGWIN__)
       // || defined(__SYMBIAN32__)

#endif // BOOST_ASIO_DETAIL_NULL_SIGNAL_BLOCKER_HPP

/* null_signal_blocker.hpp
8VdF23lx9a7pYrq5ORs9xWzh7B3MDo/cgEhj0WE0yYh2pDZ00JkgZ8hb1mpwAzix+pvQ9sexaEDzbQ6epRLB+J+1SI8rC4MlPHprXX3a9ZPcxOHPlPaxPLYsfQak/XanE3ZjKT3ibP0JqFXrNDgj4kVuDblz6tqJqMISHOwq4Jc5mqc5VtnL5Bl+dQc6SmMD2FUVBDMdJP6C0lUDWmIhzpKQqob/sSQaJLPljWV+qmWENZFaOq1hDywY8cL7mV//zr+EhZ89ZOkDSu1Q5ZPCRMPBdH8txJ2iJrVAJLr97SWe5YXKWa/izZWHo3Js1qBf9JnGkxcF2YyrIoXUIL7/8+sY5thMtwh0hpiI+AKWmwVyVQId6TMWbEO6iQTIYsA+pGesPF3ulNHNLbabR+8CqyrleiFfZDtL9e87z85cFzXQMcLzt2Je3YWoEJP2upl5fImpANQjSOSs4uYzYd4qfOHBuzjhp3mJlO6u/kwEriterUMegc99SIdWQ6fRCHlhbWqId+tWazXyEBsTTOlKZqJ6yiEelI3UFaxM0/IZZTSsWRxwf81GVHZk1A==
*/