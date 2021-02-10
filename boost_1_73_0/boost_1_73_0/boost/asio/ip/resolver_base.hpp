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
g/eXx0rXsBSpmuQ/G6io6HS8N9l/ZF3OfUOcmXZROe5KR6h42Ew4jFkDjQMhyklVsLMPdC033bdn1GZ6Pgnrhf4SpkEPhhnRHvITq83XukgNklV7n2/zsDsYXXdZ5juChRLBeQlVYq9xOHqRqqPRIS9HqXoqU5+p0LBEQ4aA2JYdUkFQP/mdEIXabIup9vve7AWaHUBPYOZdgEZwooIDuKlkNzlQhmND7iLEgvWII79jPXbdvYkoCiCeWSpYoUKHAO2lpcFsW77o5bBtf2RnPlKdvZ6N1EnUUazDwiEDQAVBt9TAtbNwqjcQwpb4qkYjtF4xaEKnjHkHbJM5v5sVD8oGoSjInFGQ22WAdQnwAiyvII3Kw3nA+UQFsiFDrdvtU9Teg/H7YV88gqB9tpWPPLWu6mddDQx1u6uYWhzW2343cpPeZjzRoGw2wMhsoC8Q/gL5qpeU0meIdMS2QFzmD6GsEY/Dwo5ktJAyDfDTidTAjS+D0mS2ccXJ+JGX+IiB3A+OQTg5fjxyAvTs3PkUMFhvSEOcgtR/PIcHHXtZo4Em3+/Hkk69d4TF6Revv05WPOzHHUkchmAQP3Yqd/NDtr/voqWrOqEFKGXArsNcTFYS7m+6bOOscJyUTNE+iGhqCbHSFTL0TF6aQOWE
*/