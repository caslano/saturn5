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
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
*/