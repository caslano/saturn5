//
// ssl/detail/stream_core.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_STREAM_CORE_HPP
#define BOOST_ASIO_SSL_DETAIL_STREAM_CORE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
# include <boost/asio/deadline_timer.hpp>
#else // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
# include <boost/asio/steady_timer.hpp>
#endif // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
#include <boost/asio/ssl/detail/engine.hpp>
#include <boost/asio/buffer.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {
namespace detail {

struct stream_core
{
  // According to the OpenSSL documentation, this is the buffer size that is
  // sufficient to hold the largest possible TLS record.
  enum { max_tls_record_size = 17 * 1024 };

  template <typename Executor>
  stream_core(SSL_CTX* context, const Executor& ex)
    : engine_(context),
      pending_read_(ex),
      pending_write_(ex),
      output_buffer_space_(max_tls_record_size),
      output_buffer_(boost::asio::buffer(output_buffer_space_)),
      input_buffer_space_(max_tls_record_size),
      input_buffer_(boost::asio::buffer(input_buffer_space_))
  {
    pending_read_.expires_at(neg_infin());
    pending_write_.expires_at(neg_infin());
  }

  ~stream_core()
  {
  }

  // The SSL engine.
  engine engine_;

#if defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
  // Timer used for storing queued read operations.
  boost::asio::deadline_timer pending_read_;

  // Timer used for storing queued write operations.
  boost::asio::deadline_timer pending_write_;

  // Helper function for obtaining a time value that always fires.
  static boost::asio::deadline_timer::time_type neg_infin()
  {
    return boost::posix_time::neg_infin;
  }

  // Helper function for obtaining a time value that never fires.
  static boost::asio::deadline_timer::time_type pos_infin()
  {
    return boost::posix_time::pos_infin;
  }

  // Helper function to get a timer's expiry time.
  static boost::asio::deadline_timer::time_type expiry(
      const boost::asio::deadline_timer& timer)
  {
    return timer.expires_at();
  }
#else // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
  // Timer used for storing queued read operations.
  boost::asio::steady_timer pending_read_;

  // Timer used for storing queued write operations.
  boost::asio::steady_timer pending_write_;

  // Helper function for obtaining a time value that always fires.
  static boost::asio::steady_timer::time_point neg_infin()
  {
    return (boost::asio::steady_timer::time_point::min)();
  }

  // Helper function for obtaining a time value that never fires.
  static boost::asio::steady_timer::time_point pos_infin()
  {
    return (boost::asio::steady_timer::time_point::max)();
  }

  // Helper function to get a timer's expiry time.
  static boost::asio::steady_timer::time_point expiry(
      const boost::asio::steady_timer& timer)
  {
    return timer.expiry();
  }
#endif // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)

  // Buffer space used to prepare output intended for the transport.
  std::vector<unsigned char> output_buffer_space_;

  // A buffer that may be used to prepare output intended for the transport.
  const boost::asio::mutable_buffer output_buffer_;

  // Buffer space used to read input intended for the engine.
  std::vector<unsigned char> input_buffer_space_;

  // A buffer that may be used to read input intended for the engine.
  const boost::asio::mutable_buffer input_buffer_;

  // The buffer pointing to the engine's unconsumed input.
  boost::asio::const_buffer input_;
};

} // namespace detail
} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_DETAIL_STREAM_CORE_HPP

/* stream_core.hpp
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
*/