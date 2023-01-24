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
AGYbpAMYCRAG8DjAYoBVAOsB3gcoBzgHUA/AbFcxXbbTU1za15tOcw1H+wZVi+3lkfCY6eHTAkcOTc/Judt+7rafu+2HtpOJsvDctLx0XXReFi5QMV1lYTqpO1IRk5pVqHMcg2CYZfLJOjYqDweyEVk5OtzXDWaY5c19ExkmG32npRay4ThBY5gFHmQZDOcpunTIqECHY2C8pRa+OIsVJhiMoQlXZGpueg5iKnL1C18MvtvRF5MFp6cXYFJmMBNcQCgIzs8qDJ4eO4Wp9yDrUyFLWF1cXmJWui40M7WAOY8pY9l0ioxhfvVMLMhiSUrmkgzCQvMWLICwaVm5ULzvXXwSmQGYPpSMtVjh7kU6aCPgJpQvFFBl4fSFjtUZZrfHNF3qQl0z/wzgB3iRqYpLYHBuemx+Vi5ZS2Xug1rJ0bHNEPydCc3JKxQ4wshkobjQI4w9GSaXcFV0bVfE6Ar1CxyhlR7T8lKhNHMLUguWEG529Yx1qq0npLU1JddRW/2blZ1himURWbnphBrGROwRWQWFLPIzfDHIxz+I33SYRpPKYVa5xoH8X3KKk8is9JhS6Jh0RkDJ9AW6aKhmJOIJIlm40JeaE1aQtVAHdT8S/cKyCufjADw2PzUN8snxjF0CM+sFOFaOy4tbGius6ZDpJXoyS2SYGw1visswNxXADcIJEDsdnmAO0enyGSbFMzYHLY0kPHdhVkFeLvIl
*/