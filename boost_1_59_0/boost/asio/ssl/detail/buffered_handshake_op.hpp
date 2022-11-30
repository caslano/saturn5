//
// ssl/detail/buffered_handshake_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_BUFFERED_HANDSHAKE_OP_HPP
#define BOOST_ASIO_SSL_DETAIL_BUFFERED_HANDSHAKE_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/ssl/detail/engine.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {
namespace detail {

template <typename ConstBufferSequence>
class buffered_handshake_op
{
public:
  static BOOST_ASIO_CONSTEXPR const char* tracking_name()
  {
    return "ssl::stream<>::async_buffered_handshake";
  }

  buffered_handshake_op(stream_base::handshake_type type,
      const ConstBufferSequence& buffers)
    : type_(type),
      buffers_(buffers),
      total_buffer_size_(boost::asio::buffer_size(buffers_))
  {
  }

  engine::want operator()(engine& eng,
      boost::system::error_code& ec,
      std::size_t& bytes_transferred) const
  {
    return this->process(eng, ec, bytes_transferred,
        boost::asio::buffer_sequence_begin(buffers_),
        boost::asio::buffer_sequence_end(buffers_));
  }

  template <typename Handler>
  void call_handler(Handler& handler,
      const boost::system::error_code& ec,
      const std::size_t& bytes_transferred) const
  {
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler)(ec, bytes_transferred);
  }

private:
  template <typename Iterator>
  engine::want process(engine& eng,
      boost::system::error_code& ec,
      std::size_t& bytes_transferred,
      Iterator begin, Iterator end) const
  {
    Iterator iter = begin;
    std::size_t accumulated_size = 0;

    for (;;)
    {
      engine::want want = eng.handshake(type_, ec);
      if (want != engine::want_input_and_retry
          || bytes_transferred == total_buffer_size_)
        return want;

      // Find the next buffer piece to be fed to the engine.
      while (iter != end)
      {
        const_buffer buffer(*iter);

        // Skip over any buffers which have already been consumed by the engine.
        if (bytes_transferred >= accumulated_size + buffer.size())
        {
          accumulated_size += buffer.size();
          ++iter;
          continue;
        }

        // The current buffer may have been partially consumed by the engine on
        // a previous iteration. If so, adjust the buffer to point to the
        // unused portion.
        if (bytes_transferred > accumulated_size)
          buffer = buffer + (bytes_transferred - accumulated_size);

        // Pass the buffer to the engine, and update the bytes transferred to
        // reflect the total number of bytes consumed so far.
        bytes_transferred += buffer.size();
        buffer = eng.put_input(buffer);
        bytes_transferred -= buffer.size();
        break;
      }
    }
  }

  stream_base::handshake_type type_;
  ConstBufferSequence buffers_;
  std::size_t total_buffer_size_;
};

} // namespace detail
} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_DETAIL_BUFFERED_HANDSHAKE_OP_HPP

/* buffered_handshake_op.hpp
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
*/