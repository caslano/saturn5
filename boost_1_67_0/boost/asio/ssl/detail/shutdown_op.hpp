//
// ssl/detail/shutdown_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_SHUTDOWN_OP_HPP
#define BOOST_ASIO_SSL_DETAIL_SHUTDOWN_OP_HPP

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

class shutdown_op
{
public:
  engine::want operator()(engine& eng,
      boost::system::error_code& ec,
      std::size_t& bytes_transferred) const
  {
    bytes_transferred = 0;
    return eng.shutdown(ec);
  }

  template <typename Handler>
  void call_handler(Handler& handler,
      const boost::system::error_code& ec,
      const std::size_t&) const
  {
    if (ec == boost::asio::error::eof)
    {
      // The engine only generates an eof when the shutdown notification has
      // been received from the peer. This indicates that the shutdown has
      // completed successfully, and thus need not be passed on to the handler.
      handler(boost::system::error_code());
    }
    else
    {
      handler(ec);
    }
  }
};

} // namespace detail
} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_DETAIL_SHUTDOWN_OP_HPP

/* shutdown_op.hpp
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
*/