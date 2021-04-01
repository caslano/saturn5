//
// ip/resolver_base.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_RESOLVER_BASE_HPP
#define BOOST_ASIO_IP_RESOLVER_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// The resolver_base class is used as a base for the basic_resolver class
/// templates to provide a common place to define the flag constants.
class resolver_base
{
public:
#if defined(GENERATING_DOCUMENTATION)
  /// A bitmask type (C++ Std [lib.bitmask.types]).
  typedef unspecified flags;

  /// Determine the canonical name of the host specified in the query.
  static const flags canonical_name = implementation_defined;

  /// Indicate that returned endpoint is intended for use as a locally bound
  /// socket endpoint.
  static const flags passive = implementation_defined;

  /// Host name should be treated as a numeric string defining an IPv4 or IPv6
  /// address and no name resolution should be attempted.
  static const flags numeric_host = implementation_defined;

  /// Service name should be treated as a numeric string defining a port number
  /// and no name resolution should be attempted.
  static const flags numeric_service = implementation_defined;

  /// If the query protocol family is specified as IPv6, return IPv4-mapped
  /// IPv6 addresses on finding no IPv6 addresses.
  static const flags v4_mapped = implementation_defined;

  /// If used with v4_mapped, return all matching IPv6 and IPv4 addresses.
  static const flags all_matching = implementation_defined;

  /// Only return IPv4 addresses if a non-loopback IPv4 address is configured
  /// for the system. Only return IPv6 addresses if a non-loopback IPv6 address
  /// is configured for the system.
  static const flags address_configured = implementation_defined;
#else
  enum flags
  {
    canonical_name = BOOST_ASIO_OS_DEF(AI_CANONNAME),
    passive = BOOST_ASIO_OS_DEF(AI_PASSIVE),
    numeric_host = BOOST_ASIO_OS_DEF(AI_NUMERICHOST),
    numeric_service = BOOST_ASIO_OS_DEF(AI_NUMERICSERV),
    v4_mapped = BOOST_ASIO_OS_DEF(AI_V4MAPPED),
    all_matching = BOOST_ASIO_OS_DEF(AI_ALL),
    address_configured = BOOST_ASIO_OS_DEF(AI_ADDRCONFIG)
  };

  // Implement bitmask operations as shown in C++ Std [lib.bitmask.types].

  friend flags operator&(flags x, flags y)
  {
    return static_cast<flags>(
        static_cast<unsigned int>(x) & static_cast<unsigned int>(y));
  }

  friend flags operator|(flags x, flags y)
  {
    return static_cast<flags>(
        static_cast<unsigned int>(x) | static_cast<unsigned int>(y));
  }

  friend flags operator^(flags x, flags y)
  {
    return static_cast<flags>(
        static_cast<unsigned int>(x) ^ static_cast<unsigned int>(y));
  }

  friend flags operator~(flags x)
  {
    return static_cast<flags>(~static_cast<unsigned int>(x));
  }

  friend flags& operator&=(flags& x, flags y)
  {
    x = x & y;
    return x;
  }

  friend flags& operator|=(flags& x, flags y)
  {
    x = x | y;
    return x;
  }

  friend flags& operator^=(flags& x, flags y)
  {
    x = x ^ y;
    return x;
  }
#endif

protected:
  /// Protected destructor to prevent deletion through this type.
  ~resolver_base()
  {
  }
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_RESOLVER_BASE_HPP

/* resolver_base.hpp
o7/iegPkgGmdjF2kAcctmfDsdBRNGoobszSuw8esh452gg5jj+ZEGJ7NfBSypOrgt/BkPm/Wgs/6CZJpAdVB0655/GVhwbWjGtguIFkdhMy2sXz1eaaIVu96oLsIK27kDLbZYBsrvYEprpXRBE958w4D/zMW8FE08kX0ozBVuQiW8VCmjEf9DSiBgaVVI3rgMQjg0B0g5waCMtPKzbHJ9vaAXecJs61swgBEjvTGZScGlQ/1Nbxnxj7+Teq/WygsKOc0I+syCvo8RWZvXzBBzCutRjSQdPmvqlQpS2RKcwdg1btgtkEDWaJ9hLa2shx73HUc1DKWYxAplcuVu/zolBWgpQ9s5kvvfuUCgTRmPg/+RV1ZRB+YgKWHayUc5Ukgcq6SpOlCkPNF8YWNrue2MXVum2Yo7Z3HN0TeiYKsa9LolBntrpxRT+z/Z9NNNYN+qlHko2DKC8ufFV87hucbj87HoLzh9e5rf+u9VDgl7/Xh9r0MuXJL7TnCJKcN/76cqz//xycKST9xtJh1gBbcIk66NyI5CLpv/pN4TUT9MkJX7aypeqC43W8mAg==
*/