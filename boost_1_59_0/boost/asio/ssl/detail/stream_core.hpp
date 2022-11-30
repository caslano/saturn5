//
// ssl/detail/stream_core.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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

  template <typename Executor>
  stream_core(SSL* ssl_impl, const Executor& ex)
    : engine_(ssl_impl),
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

#if defined(BOOST_ASIO_HAS_MOVE)
  stream_core(stream_core&& other)
    : engine_(BOOST_ASIO_MOVE_CAST(engine)(other.engine_)),
#if defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
      pending_read_(
         BOOST_ASIO_MOVE_CAST(boost::asio::deadline_timer)(
           other.pending_read_)),
      pending_write_(
         BOOST_ASIO_MOVE_CAST(boost::asio::deadline_timer)(
           other.pending_write_)),
#else // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
      pending_read_(
         BOOST_ASIO_MOVE_CAST(boost::asio::steady_timer)(
           other.pending_read_)),
      pending_write_(
         BOOST_ASIO_MOVE_CAST(boost::asio::steady_timer)(
           other.pending_write_)),
#endif // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
      output_buffer_space_(
          BOOST_ASIO_MOVE_CAST(std::vector<unsigned char>)(
            other.output_buffer_space_)),
      output_buffer_(other.output_buffer_),
      input_buffer_space_(
          BOOST_ASIO_MOVE_CAST(std::vector<unsigned char>)(
            other.input_buffer_space_)),
      input_buffer_(other.input_buffer_),
      input_(other.input_)
  {
    other.output_buffer_ = boost::asio::mutable_buffer(0, 0);
    other.input_buffer_ = boost::asio::mutable_buffer(0, 0);
    other.input_ = boost::asio::const_buffer(0, 0);
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  ~stream_core()
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  stream_core& operator=(stream_core&& other)
  {
    if (this != &other)
    {
      engine_ = BOOST_ASIO_MOVE_CAST(engine)(other.engine_);
#if defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
      pending_read_ =
        BOOST_ASIO_MOVE_CAST(boost::asio::deadline_timer)(
          other.pending_read_);
      pending_write_ =
        BOOST_ASIO_MOVE_CAST(boost::asio::deadline_timer)(
          other.pending_write_);
#else // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
      pending_read_ =
        BOOST_ASIO_MOVE_CAST(boost::asio::steady_timer)(
          other.pending_read_);
      pending_write_ =
        BOOST_ASIO_MOVE_CAST(boost::asio::steady_timer)(
          other.pending_write_);
#endif // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
      output_buffer_space_ =
        BOOST_ASIO_MOVE_CAST(std::vector<unsigned char>)(
          other.output_buffer_space_);
      output_buffer_ = other.output_buffer_;
      input_buffer_space_ =
        BOOST_ASIO_MOVE_CAST(std::vector<unsigned char>)(
          other.input_buffer_space_);
      input_buffer_ = other.input_buffer_;
      input_ = other.input_;
      other.output_buffer_ = boost::asio::mutable_buffer(0, 0);
      other.input_buffer_ = boost::asio::mutable_buffer(0, 0);
      other.input_ = boost::asio::const_buffer(0, 0);
    }
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

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
  boost::asio::mutable_buffer output_buffer_;

  // Buffer space used to read input intended for the engine.
  std::vector<unsigned char> input_buffer_space_;

  // A buffer that may be used to read input intended for the engine.
  boost::asio::mutable_buffer input_buffer_;

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