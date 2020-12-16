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
4+f5HnsHPDNhbF6r9vgKNP924ELyv9ub/yrevJqrRQW+OlCeLN88UpYaX2Dy+Gw38piQH1OeE/rqHV+4fopD+a/Nmx8yIvaeXHkxd5oL/WCTN/hddwf/AX/sPuVydHgS9w77m5pwrufe5M72qcjgaftP9PW2/UX2/OD6xPzIHKGiks+VKiqv9isfeE6t7as8Lv3uCPvXl0JfeQLbC/Tt1hXi3XXl8JtYV2L92H1Z3rxcYPergXkpW3912bLF8wPqf7EnT/W1VU77cJqn7HieKyLNjQ0R0w9Ak5DvH3U731EZct39gD7XrY892V59LEUf5e3q46K5FwToozyuD7VRJMsy8e+MO6GP8gR9HOmGPpABPzJ0oI/zY22vn3/9aG1XH5VNtc21lRV1/jpp9dQRm95hr7QTOmlN0MlPu6GTaP5tGTpXR9bmeHVyoT1eBOukkg9+STJgzFB9xPJytAt5cfaXd/f3yneRPScPlq9qcq2/bG3tt2eNL4jGp7nLsiSUGO+2q7c8Hm/y/lwX8u7X1s2Yn2bKVsIWmTDkSLwDPtc7zpTY65uBeov46uxoN8YYc++4jyzL7fUCf1k2RzYaQyK+Mp3ohkxm/XeAV6ZSZLJafWUS03SxOt+cuG7QemryNPut/6o8PZVB1kGRJ+wvT0NTVTUK2ugnj/L07JI8sTKryfPq52LkKfSVR83XlUl19Z8fnKKO/MrsZJ5/mRX5yqRfFweUWdEpytPss9azPd9fnmJ/ediUqPaVpfhNkCVc4JXlEmQpCZAlUuFfTiWnKItfOe0t8L5PXoos5f6y8CFypLah3reclCds+tRPn8L7ol87OzQwSniDroltxU1FtlavbJGA+bdZE7tTeBqsMP+vMGtimpau7+qasCajcyVDU0Ra0Jj1MENn1sI+JXSLXWthWboWln0Ka2FH3Ou7ut5rnudq+ymDvTqaaLezbT46Cu6vjZ7mbvPXE+mZtcNjwuNMSnVl6IoYWaEzunLRGn1VbvPqq7/qK7cL+oqtHR4Tv+uZrno1aIhXZ0X2eOuvMx1P/PX1e399aVrZ+GP7BpJM3O6O6inbtWcgNEY//W5Q/XRzv8DMV1z7BfIsl16OqV6kM1HdTEcvu27w04sZ1/z6JuUJO+bShlzncDGapFPuv3Lxh828y6TrahfhQm8ZTyAv+/zzYsbEoHL+yg3+5Ux6pv/oLeUcTcq5/gSN9h/QmLI2dKa8f+5T3se1vF/uQnnH+g+eiV+fl9AWpg7zbwvlb/fqyYzTATpqeruvjkjLs4emyaiODE2RZw9N6YyO7nr7m9sm3Hto5nmu8XrRcH8dhbd7daRzB1/9DN/uqx/SSewrNkoaqhvi/foKITF6mbfdq5f9qpd3dUEv7r5C5HHpZO0Ir05m2O96ATqJVPjXmWcCdNJmdOKwPWzqi8arTohXnQiN0ckffHTyNx1fPjey6zox9m4T29JI71xqvL2efaOfTsxcyrf/hMf0n9nSf8bITf8JTdfX5531f4bozPbrMxLuc8gb5bV1/wXbLumNLlv3C1atXLCsdPFFy4w1f3keecvz2r2H19iZ+qC/PX9oum7Pn2d67Pl/0G3P/7Q9lP8CeygfE/rv/3TPdz7UNH9p63Ujd3xl3IBLT9tD6Y49FJ1syZ5JHliKQ0X0pno+DkzVbxaTwZEOGxI2vgymgK+AMb4T7fB9X/meU74fGD49bwak+PB9Ufm+BCaDbcpHoJ7vgl35eoPNyvcjSPqBPwbzwJ+AQ8CfgSPAo+BE8HlwCvgCuBz8OVgK/gp8K/gSuBH8JbgJPAY2Snxcjn3tyPFVleNJlePrKscBleObKsdTKse3VI6DKsczKsd3VY4=
*/