//
// detail/null_thread.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_THREAD_HPP
#define BOOST_ASIO_DETAIL_NULL_THREAD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class null_thread
  : private noncopyable
{
public:
  // Constructor.
  template <typename Function>
  null_thread(Function, unsigned int = 0)
  {
    boost::asio::detail::throw_error(
        boost::asio::error::operation_not_supported, "thread");
  }

  // Destructor.
  ~null_thread()
  {
  }

  // Wait for the thread to exit.
  void join()
  {
  }

  // Get number of CPUs.
  static std::size_t hardware_concurrency()
  {
    return 1;
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_HAS_THREADS)

#endif // BOOST_ASIO_DETAIL_NULL_THREAD_HPP

/* null_thread.hpp
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
*/