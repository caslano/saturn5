//
// ssl/detail/buffered_handshake_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
    handler(ec, bytes_transferred);
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