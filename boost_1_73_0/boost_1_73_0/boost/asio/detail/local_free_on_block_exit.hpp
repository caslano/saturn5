//
// detail/local_free_on_block_exit.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_LOCAL_FREE_ON_BLOCK_EXIT_HPP
#define BOOST_ASIO_DETAIL_LOCAL_FREE_ON_BLOCK_EXIT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
#if !defined(BOOST_ASIO_WINDOWS_APP)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class local_free_on_block_exit
  : private noncopyable
{
public:
  // Constructor blocks all signals for the calling thread.
  explicit local_free_on_block_exit(void* p)
    : p_(p)
  {
  }

  // Destructor restores the previous signal mask.
  ~local_free_on_block_exit()
  {
    ::LocalFree(p_);
  }

private:
  void* p_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_WINDOWS_APP)
#endif // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)

#endif // BOOST_ASIO_DETAIL_LOCAL_FREE_ON_BLOCK_EXIT_HPP

/* local_free_on_block_exit.hpp
pVZwyw6KBx6TG/aS0p6SwHeKp0sxcnJWYbAUSiMToxv/B1BLAwQKAAAACAAtZ0pSMgpn+VZEAABFuwAAFQAJAGN1cmwtbWFzdGVyL2RvY3MvVE9ET1VUBQABtkgkYL19+37bSnLm/3gKjHZnLc2QlEhd7WT2RJblY+XIkmLJc2Y2k58GJEAJxyTAAKBp5vZY+wL7YlvfV9WNJiXb0kl+mWTGFNDoS3V13as6jr/3n1v+91b+I/9G32l7e/tvsf6ffPMX+ffbH2zH7Qf/drsVf++Df4s3+cGtjfC3+H37nVn9BbPC/2zju7/c4qc8iR58dXOfF3d13NwnTTwq55M0HmZxkY+yuCnjtIzzQt5l8XjezKtMPnft3ctZVf6SjeTbeTXpxVeTLKnl02wyied1vECvy3IuXeTFp44MUDRVPpw3WZwUaRTXWZGi3SxpRveZzSKfSp+fM35zV/9GxnwtzRdJlel7mY4MoX+2c19kNv207MRlFd8n0kVZyDqGWVZg5DpPsyqTUe2z4ItefDbmPBdJ0WBti7L6JF/LLJdxOW6HTOpOPOMaI99lPKykP/n/OG/i+Swey+hpXo/mdZ1Lk3icV3WDzgDHaZJP0HSSy7O6dHOP4kQgltxVWYZe8jqumxxP4ruyTGMZJmG/
*/