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
7w+ar9d0XPujjmN/AZeAb4DLwL+Ba0GLcr4WCIHvAntquxsCvh8cCn4ULAS/Ag4DvwaOAJ8CR4LHwRTwVTAVPAmmgwNC0fQmg73As8He4HlgH3A+2BdcCobBZWA2WAHmgK1gf/A+9X8czAO/BhaA3wYHgdpudG2fOalPuzmpd/q9Ac4E/w5eqnehVYOpWs5pYCvYE3wU7AV+DMwAv6R08o4Ffh/MAl8GM8HfgX81dr90LRm8SuRx2/1qRu7B4JXgFJsGnA1uAVeB14DrwWs1f+lmTZS+Vct9iOQn+vckzx8Ifh0cDj4FFoHf0n7nIDhb/cXqLwG/A64CvwuuUb516q9Q/+Xg0+BO8BnVy/dUL98GPwk+B34Z/AH4LfAw+B31P63+58Afgj8CfwQeBX8M/ln4tT2DlIn4M8Cfgn3Ao2Au+Ly2gxpL17XAParfXuBa1UcOdPngANVDgbbzQdq+h4JbwRHgzeBg8J3qfwDMAx9Wv/aDuqZCP+/TD35A7QruAUeDj4KTwY9ofdsLngd+VPvFj4HrwX3gVeAnwe3gp8Cd4KfB+8DPgJ8DPwt+H2wDfwB+HvwZ+ITO478KHge/Bq5M7dxdUe/fkGI9icMO2mkbaP9mG2gvbkj5t9lBszam/MtsoeVsTOmSPbT/Z1to2CgMtIc2YWPKm2oTbdbGlP8Ku2glyLkFtxv3JO4YLlyD7Lhy3HbcHtxB3AlcXm2KNR9XjtuKewj3GO4w7iQu73J0jKvC7cDtxR3AvYhL35RiTdh02rba6b/Tf6f/Tv+d/jv9d/rv9N/pv3+x/b+W5tq6iJj/65b9P9t+39Fxcft980Pe+3xm2d+mXpNtRe0xzZk37+IVc+atlgN8m+UBVvQ7k5VT5dvE2BkZeDp3X08fvd8Ffvl+0Gnn7tkAeU4EyVNXVxskz4k3QZ6qJCOH/CWrPNa1vvJEqisb6qsivvIoT0q35LnPFsBOSs+UNeImI0/YK08ksbx+PcUlj/LkmTPUY8W/3lrA/9nm21NNIn6uWfnOMOea68U/2OpJ3nLN+UIu1NLHO8/xjxLacr4STjPfnn5Kz+F9sxPf6sa+PSUvzm9P9VtU8zyXzg6m+OtsX5DOqFNBOtuXoLMDATrTJOI2KhN01mdrsM7gdensa/9knfE8j85OaAO8Tu9Ou0p1VrLVV2da7106M2cX1wvP5aTD6Wec6lLTynboTZOJ601pzkrQkaEz5XCD0C3gi4D0f4KO9HkJOmpN8/YNs+2+ClkctuzoF1yflYmOchL7qq2n1jfAL3I6betl9vD2nedOswsxUR41jGb5ygL9qfWbfrLc5yPLeXY/5SOLfoziK0u4G7LEyumA2hy8Xuvy1bieyFLoliUSUE6uujxZeOqkLi+P12VNKxs6+baP366ktD4rHfW5QOm0PjtpTZ1eIbQLrfGOOj1MbYMNH9f5Oh3TSYHWaZ6L3/VMV9ml9Ip/q5+n9zzOtM8tJ+irg7JT+oHmjOmPNe9x+3qNJB23a/ELiVe7jIZ/VOD3cEuh+anQjBF/ieEZYs6JnzO6c/YXbV0VOXTltr0ocuo32f52Ds5X3T3Uy1vv59h17W0x3ZWunLPy4tKoZR6qf5HbwrJ8R+DWI7yn1gYaNQ/OOw+LMjx9FXIRHiyX+bDURyb4Tq2/avRpl20ZXl3NRabiQJnkyxFfeYrfBB3tzNT7ndRGhZ3QfHvM85PH0V1oP0p7dsmkfGHijP0ZtT0Ti8s3Z+Mf1zFqbCfqaLT98hy33RlXG96pNvNGaV4KceeTl0aTl5WlKyUjcpMwao3m4Yg7D0qfJW32Ymmz1VvMvEbj3TZ26hoqNb4mHm/y+czIzucTWVxtkec=
*/