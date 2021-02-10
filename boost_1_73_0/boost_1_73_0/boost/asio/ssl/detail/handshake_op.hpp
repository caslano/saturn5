//
// ssl/detail/handshake_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_HANDSHAKE_OP_HPP
#define BOOST_ASIO_SSL_DETAIL_HANDSHAKE_OP_HPP

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

class handshake_op
{
public:
  handshake_op(stream_base::handshake_type type)
    : type_(type)
  {
  }

  engine::want operator()(engine& eng,
      boost::system::error_code& ec,
      std::size_t& bytes_transferred) const
  {
    bytes_transferred = 0;
    return eng.handshake(type_, ec);
  }

  template <typename Handler>
  void call_handler(Handler& handler,
      const boost::system::error_code& ec,
      const std::size_t&) const
  {
    handler(ec);
  }

private:
  stream_base::handshake_type type_;
};

} // namespace detail
} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_DETAIL_HANDSHAKE_OP_HPP

/* handshake_op.hpp
CAAtZ0pSC1c1r7cAAAAPAQAAKwAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3JhbmRvbS1maWxlLmRVVAUAAbZIJGAtj0FqxTAMRPc+xVzAOUAohVIoXfxdegE1VhyBLQXbn09uXzvNSkIavRk9TOOMQhos+00Su4/SB2+jfXffnI4ZX73HZgWFKYjGW45AjbAVy+6TGkcr54wsdXXee7ccvMp2ou2Mg9oOpcxohkHGatpIdMBeOzW8JCX8XvMqgQsHUL193PCZ8NNBl2Omc0iftYs6r/KofXmnYo2i/3mX5TGIymuTDp6AhdlRqnYdeM8xXE/DjqGY3B9QSwMECgAAAAgALWdKUuG3q+/+AgAAwQUAACUACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9yYW5nZS5kVVQFAAG2SCRgbVTLbtswELzzK7aX2i4s1Qaag4O2QFo4jYEgMZxcWvRCSyuLAEUKJGVFf99d0nLSJAcLJrWP2ZnR3lpzuAQnzQHFQ21doIO4Qd1ewg6DU3hEsEYPEGqE/RDQQ69CrQzsru5+rcWVo/SvMf+72DobbGG1v4Sbx8ctXNPvgR/Xm9u1+CkDHqwbLqEOoYWKfp4fldIosiwT54YydkqoYKpy
*/