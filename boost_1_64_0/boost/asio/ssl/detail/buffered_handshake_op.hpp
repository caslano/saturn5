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
boyswCu5yRjyMEXzUkHF9B+QWNPHHZLLjYa5hO1kWULHo0uZX20BrRkALJnongI9umXSAIw7mjAMT530wJhsWlvc6N32aR36f31Y/F90ek5XTdzQYxTe7PBZ6x1mxOi4KTwuM/wzJLFFnXHuMbDap9VlJ6nsYGYwZfF00Kbojy1f2VO7tBYAQTNFBoJqo0T7SiC/LvzrQnpPScjxdXAlX7tsPeCWaJqRPmfTOwdQ6RNC8dQL/eBWoXWh4DwY4HdrVzrBHgN7XhpA5zKgl8cGx3Iu4ubKtPK7DpEhmammje5+RBEGg6SXiTSOsbVZRu+Lw3jvoTEH8UBahKtcC/Uqyw1q1nCcCf4BeDVSR+zwLbEcHlb05b+4M2zrjA6mRsYXM7iojvI0JAT0xWrWWXcsz93+4puCOx3AI1GLDQDeay2jtDIqP1zHU2Oe2l0QirpKHCy7ufBBlneAWd753hbh1uLyMu+T7hmqnX1hjJLhVaALwAEEd7hgTltNSqrcQPBUh7UA+mT+tuA4yJGiSoQDaLWGq6EAnJZ361JV3b/bfvbjwhxhDDPkUhJBFQ==
*/