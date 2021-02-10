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
A1gsoplb/oy0wcf3vIEjS6Wnx7/DUXKRyIFWKjRI0AWAqdXQCMz2Lr90ThvRWo8LshtLWjQxeZJ9llMcxf/w8ewGoD2//PHy7VsXuOHDTTFAzWSrDrOzNFRPqB6h8KR0yGD9tyYcAcOCJiozZ491Rbxr6p55jyKzh1kGZRJquwHKWnB72hJglw+PvRcoQkKptbMX0+QLmHD9QmmCYaxjC73RK/A5xB9nt3BfbG5x6WsZnkJfW6XxsHcwELV3kbVuoTTwmOgndCrMYfto5gVC25eKz/TJRmChK5F9rb+47RRUw+nCxJKkJbU6O/26Y0FTiAz1vmYlrRs6mY01Wb1cdZzkFruxZhlpSWQ4Gh0ThZcWnixc9V++BGC/kSjbyuN2hOuWmzv7uZlQ13QWhc1MI/5rdXtEIGKKZBZSFirsQiKhr1rgkjqLExcVjzimnlonVfqN1i2U4znA2H4Ny8Nixd5DdxzCUVgwAYkb8m+KYFDwxDFydlSCfQ4Q94929wHEJ+cTvxXYqNV3cV+aXIpGAQ8DB1d/v74eQTum+L7S6FM2n21uddqSFKFLFAq9S6Jxe3hxeRMFsS9+Vk4YCHHqWYGtRwNBpAeJ0tH3EqWPw7+F9GrAPyU36JeWWlOb1qPmC4uaeaCORCQ4oBk2
*/