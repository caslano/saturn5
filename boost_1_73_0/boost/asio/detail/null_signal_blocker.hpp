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
bNQc30I250S3tpvv5fI7U36L5Xe6fiQbmD8kFDUCKbDa/MbyG7VdXg/JFW3tTDzTu/yjK+t88zF/o1vloOYRRQCPb1086OSdcnZrWsu8cIFk5HqkO0cMZ2KX3ickB3sSjLM1vFBaKbb8HmDs2m8xdhe2fBy1Kuv0ucTrgHZIa2UEJlnxSmdTlCK8S3Nx+3YbeA+l2TbADjJ5kYcg1CE7UoUUySuHozvhQIHKRgibyHSDwM9G
*/