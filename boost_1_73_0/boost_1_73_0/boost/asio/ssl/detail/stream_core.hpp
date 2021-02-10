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
Z0pSTTbpAP4AAABuAQAALgAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3JlcXVlc3QtdGFyZ2V0LmRVVAUAAbZIJGA1kM1qw0AMhO/7FEMu/aE2vYSCb6WXFEJjGvcBhC3bS5eVu6uNydt31yFHSSN9MzqKnxoE/ksctVIKE6s5sFsanBfu7XiFzozbAKOEXNp4XzBtEJVeXGxw6LrWvA8DDw3e6v2+fjUfpDxJuDaYVRdTVZXp2LmIPgUHFaTIIA9yysGT2gtjd0Pt8LiQzk+wPirTABmz2vpps1NGoGiWIBebiVm19X++jzVaCmr75Ci4ayGMyWGd2WMlr9sFgY0x8Wb5HiWa1eosSeEyrsiiozgjJ5Z8OmAgpQwhxSAc/UP5hnOybuDAUwEWAyabK3Fe4OxvznNqu8/T1xnPu9r8A1BLAwQKAAAACAAtZ0pSVbSVdvACAAD4BQAAJwAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3JlcXVlc3QuZFVUBQABtkgkYIVUYW/aMBD97l9x30YlErXrtEpomoRaOpBoiYB17UcTX4hVx2a2U8q/310SKEPd+i2yz+/ee/cuU2fXA/D4u8YQxaJ0Pg7gUQw9nX7LXVVJq76LMZrN
*/