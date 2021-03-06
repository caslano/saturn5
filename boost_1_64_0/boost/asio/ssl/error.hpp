//
// ssl/error.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_ERROR_HPP
#define BOOST_ASIO_SSL_ERROR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/ssl/detail/openssl_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace error {

enum ssl_errors
{
  // Error numbers are those produced by openssl.
};

extern BOOST_ASIO_DECL
const boost::system::error_category& get_ssl_category();

static const boost::system::error_category&
  ssl_category BOOST_ASIO_UNUSED_VARIABLE
  = boost::asio::error::get_ssl_category();

} // namespace error
namespace ssl {
namespace error {

enum stream_errors
{
#if defined(GENERATING_DOCUMENTATION)
  /// The underlying stream closed before the ssl stream gracefully shut down.
  stream_truncated,

  /// The underlying SSL library returned a system error without providing
  /// further information.
  unspecified_system_error,

  /// The underlying SSL library generated an unexpected result from a function
  /// call.
  unexpected_result
#else // defined(GENERATING_DOCUMENTATION)
# if (OPENSSL_VERSION_NUMBER < 0x10100000L) \
    && !defined(OPENSSL_IS_BORINGSSL) \
    && !defined(BOOST_ASIO_USE_WOLFSSL)
  stream_truncated = ERR_PACK(ERR_LIB_SSL, 0, SSL_R_SHORT_READ),
# else
  stream_truncated = 1,
# endif
  unspecified_system_error = 2,
  unexpected_result = 3
#endif // defined(GENERATING_DOCUMENTATION)
};

extern BOOST_ASIO_DECL
const boost::system::error_category& get_stream_category();

static const boost::system::error_category&
  stream_category BOOST_ASIO_UNUSED_VARIABLE
  = boost::asio::ssl::error::get_stream_category();

} // namespace error
} // namespace ssl
} // namespace asio
} // namespace boost

namespace boost {
namespace system {

template<> struct is_error_code_enum<boost::asio::error::ssl_errors>
{
  static const bool value = true;
};

template<> struct is_error_code_enum<boost::asio::ssl::error::stream_errors>
{
  static const bool value = true;
};

} // namespace system
} // namespace boost

namespace boost {
namespace asio {
namespace error {

inline boost::system::error_code make_error_code(ssl_errors e)
{
  return boost::system::error_code(
      static_cast<int>(e), get_ssl_category());
}

} // namespace error
namespace ssl {
namespace error {

inline boost::system::error_code make_error_code(stream_errors e)
{
  return boost::system::error_code(
      static_cast<int>(e), get_stream_category());
}

} // namespace error
} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ssl/impl/error.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_SSL_ERROR_HPP

/* error.hpp
blieGwpcl/M9RZQ+Bt0JcMqsKEA/ZxSkqlRAPZ+a4D5i0UtW1iIRrGYOM1odfxkqxfgXO0fUf934/6ZJBHfodJ+d8jnl8wg4kEZ8LDSe3JTTzGfQO3zIaC17/cLD3H+JOSwON4oGMoYC8WgJuBzNqLNzMpR8OnaDm0qjkZ/VchTL/M+dC9gSR4ySYXoGvsq+qdYyT6VKE67Gl/W9PZYdvxF4Ccuvs/+DZ4iyMaL89UywWYJ3jPCawUdsHrvDO6c2bEAHQgvcyKrDEVrjKpZxYTczpYQD4QqISdtKnB8GgJHPaMxQIpwr40iNtYDw5L/60TAC32QpuoZbrMsKWfYvks4y58+iD3vPwBdrUxTW6Ct1J4D370nzXl6xzRjtyD+anyUOlKEBTVOTblB5GIPYsaUB3gtAxwPpgPrY22P/CqqWWr8Mgsii7hDx7SzrQIJ5GToypIpnDX1u53L6rdfOOUTiDPLdZNihUHHuBP5LXm8jTr1n2fg0oZw7g2Dk3uAanBUiXCq58qO8So5GMwXDDzHIzHBPJQ1wyH21r5sMplvBnD/BLwJZJmZGOA==
*/