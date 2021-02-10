//
// ssl/detail/read_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_READ_OP_HPP
#define BOOST_ASIO_SSL_DETAIL_READ_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/ssl/detail/engine.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {
namespace detail {

template <typename MutableBufferSequence>
class read_op
{
public:
  read_op(const MutableBufferSequence& buffers)
    : buffers_(buffers)
  {
  }

  engine::want operator()(engine& eng,
      boost::system::error_code& ec,
      std::size_t& bytes_transferred) const
  {
    boost::asio::mutable_buffer buffer =
      boost::asio::detail::buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence>::first(buffers_);

    return eng.read(buffer, ec, bytes_transferred);
  }

  template <typename Handler>
  void call_handler(Handler& handler,
      const boost::system::error_code& ec,
      const std::size_t& bytes_transferred) const
  {
    handler(ec, bytes_transferred);
  }

private:
  MutableBufferSequence buffers_;
};

} // namespace detail
} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_DETAIL_READ_OP_HPP

/* read_op.hpp
p/BxYXQEXjIahvPpWMyrc+xGPA9PL8OjeSPlWfJthFRdqxprrfkMsUBWjZIwBUozl13s2FNdFDTtoz/tHL847XKo4NI5atQWNYCKiR7W3jXGxplRC7vdwDQFSOIBH4LG3qRio6Td5WKhy9K3Iv2JM2XlKfo49TyQV87/7f0eCFRaj1aqpzzsymst2p84WIE9QHJbNcn918F8A1BLAwQKAAAACAAtZ0pSHSXVkuoBAAD7AwAAKwAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3JlbW90ZS1uYW1lLmRVVAUAAbZIJGBtU02r2zAQvOtX7KXQQmxKj7n20sKDB/2g9KjYa0s8WWskOa7/fWcVJ01f3tHWzOzMaPUkcTxS4kkKN9FObL47SeVIz+YLh/lIv5IvTLKUeSlUhCwNPjAptCebqTje6fXAfLaFR0nbkfw0Q8nGsrNN0zTmUS5IZ8O9aPAv/FqWVqaRS0vvn2PY6mmdNtsE+eEB7jMtmftDPZhtcfqnWxQ7tB+M+eGuuj4EOjFle8ZoHyuhW1Ji+F4lvfg4Uu8TdwWhWvo60CYLrRrr5uJGtoAOA1fyjXSgySJRXhJXbudsHPmtQebGgaVBgPfxLNUCkAFmEaQ4RJG5eIntJch9cK1Q
*/