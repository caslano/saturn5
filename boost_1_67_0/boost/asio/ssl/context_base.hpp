//
// ssl/context_base.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_CONTEXT_BASE_HPP
#define BOOST_ASIO_SSL_CONTEXT_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/ssl/detail/openssl_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {

/// The context_base class is used as a base for the basic_context class
/// template so that we have a common place to define various enums.
class context_base
{
public:
  /// Different methods supported by a context.
  enum method
  {
    /// Generic SSL version 2.
    sslv2,

    /// SSL version 2 client.
    sslv2_client,

    /// SSL version 2 server.
    sslv2_server,

    /// Generic SSL version 3.
    sslv3,

    /// SSL version 3 client.
    sslv3_client,

    /// SSL version 3 server.
    sslv3_server,

    /// Generic TLS version 1.
    tlsv1,

    /// TLS version 1 client.
    tlsv1_client,

    /// TLS version 1 server.
    tlsv1_server,

    /// Generic SSL/TLS.
    sslv23,

    /// SSL/TLS client.
    sslv23_client,

    /// SSL/TLS server.
    sslv23_server,

    /// Generic TLS version 1.1.
    tlsv11,

    /// TLS version 1.1 client.
    tlsv11_client,

    /// TLS version 1.1 server.
    tlsv11_server,

    /// Generic TLS version 1.2.
    tlsv12,

    /// TLS version 1.2 client.
    tlsv12_client,

    /// TLS version 1.2 server.
    tlsv12_server,

    /// Generic TLS version 1.3.
    tlsv13,

    /// TLS version 1.3 client.
    tlsv13_client,

    /// TLS version 1.3 server.
    tlsv13_server,

    /// Generic TLS.
    tls,

    /// TLS client.
    tls_client,

    /// TLS server.
    tls_server
  };

  /// Bitmask type for SSL options.
  typedef long options;

#if defined(GENERATING_DOCUMENTATION)
  /// Implement various bug workarounds.
  static const long default_workarounds = implementation_defined;

  /// Always create a new key when using tmp_dh parameters.
  static const long single_dh_use = implementation_defined;

  /// Disable SSL v2.
  static const long no_sslv2 = implementation_defined;

  /// Disable SSL v3.
  static const long no_sslv3 = implementation_defined;

  /// Disable TLS v1.
  static const long no_tlsv1 = implementation_defined;

  /// Disable TLS v1.1.
  static const long no_tlsv1_1 = implementation_defined;

  /// Disable TLS v1.2.
  static const long no_tlsv1_2 = implementation_defined;

  /// Disable TLS v1.3.
  static const long no_tlsv1_3 = implementation_defined;

  /// Disable compression. Compression is disabled by default.
  static const long no_compression = implementation_defined;
#else
  BOOST_ASIO_STATIC_CONSTANT(long, default_workarounds = SSL_OP_ALL);
  BOOST_ASIO_STATIC_CONSTANT(long, single_dh_use = SSL_OP_SINGLE_DH_USE);
  BOOST_ASIO_STATIC_CONSTANT(long, no_sslv2 = SSL_OP_NO_SSLv2);
  BOOST_ASIO_STATIC_CONSTANT(long, no_sslv3 = SSL_OP_NO_SSLv3);
  BOOST_ASIO_STATIC_CONSTANT(long, no_tlsv1 = SSL_OP_NO_TLSv1);
# if defined(SSL_OP_NO_TLSv1_1)
  BOOST_ASIO_STATIC_CONSTANT(long, no_tlsv1_1 = SSL_OP_NO_TLSv1_1);
# else // defined(SSL_OP_NO_TLSv1_1)
  BOOST_ASIO_STATIC_CONSTANT(long, no_tlsv1_1 = 0x10000000L);
# endif // defined(SSL_OP_NO_TLSv1_1)
# if defined(SSL_OP_NO_TLSv1_2)
  BOOST_ASIO_STATIC_CONSTANT(long, no_tlsv1_2 = SSL_OP_NO_TLSv1_2);
# else // defined(SSL_OP_NO_TLSv1_2)
  BOOST_ASIO_STATIC_CONSTANT(long, no_tlsv1_2 = 0x08000000L);
# endif // defined(SSL_OP_NO_TLSv1_2)
# if defined(SSL_OP_NO_TLSv1_3)
  BOOST_ASIO_STATIC_CONSTANT(long, no_tlsv1_3 = SSL_OP_NO_TLSv1_3);
# else // defined(SSL_OP_NO_TLSv1_3)
  BOOST_ASIO_STATIC_CONSTANT(long, no_tlsv1_3 = 0x20000000L);
# endif // defined(SSL_OP_NO_TLSv1_3)
# if defined(SSL_OP_NO_COMPRESSION)
  BOOST_ASIO_STATIC_CONSTANT(long, no_compression = SSL_OP_NO_COMPRESSION);
# else // defined(SSL_OP_NO_COMPRESSION)
  BOOST_ASIO_STATIC_CONSTANT(long, no_compression = 0x20000L);
# endif // defined(SSL_OP_NO_COMPRESSION)
#endif

  /// File format types.
  enum file_format
  {
    /// ASN.1 file.
    asn1,

    /// PEM file.
    pem
  };

#if !defined(GENERATING_DOCUMENTATION)
  // The following types and constants are preserved for backward compatibility.
  // New programs should use the equivalents of the same names that are defined
  // in the boost::asio::ssl namespace.
  typedef int verify_mode;
  BOOST_ASIO_STATIC_CONSTANT(int, verify_none = SSL_VERIFY_NONE);
  BOOST_ASIO_STATIC_CONSTANT(int, verify_peer = SSL_VERIFY_PEER);
  BOOST_ASIO_STATIC_CONSTANT(int,
      verify_fail_if_no_peer_cert = SSL_VERIFY_FAIL_IF_NO_PEER_CERT);
  BOOST_ASIO_STATIC_CONSTANT(int, verify_client_once = SSL_VERIFY_CLIENT_ONCE);
#endif

  /// Purpose of PEM password.
  enum password_purpose
  {
    /// The password is needed for reading/decryption.
    for_reading,

    /// The password is needed for writing/encryption.
    for_writing
  };

protected:
  /// Protected destructor to prevent deletion through this type.
  ~context_base()
  {
  }
};

} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_CONTEXT_BASE_HPP

/* context_base.hpp
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
*/