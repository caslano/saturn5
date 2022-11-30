//
// ip/basic_resolver_query.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_BASIC_RESOLVER_QUERY_HPP
#define BOOST_ASIO_IP_BASIC_RESOLVER_QUERY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <string>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/ip/resolver_query_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// An query to be passed to a resolver.
/**
 * The boost::asio::ip::basic_resolver_query class template describes a query
 * that can be passed to a resolver.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename InternetProtocol>
class basic_resolver_query
  : public resolver_query_base
{
public:
  /// The protocol type associated with the endpoint query.
  typedef InternetProtocol protocol_type;

  /// Construct with specified service name for any protocol.
  /**
   * This constructor is typically used to perform name resolution for local
   * service binding.
   *
   * @param service A string identifying the requested service. This may be a
   * descriptive name or a numeric string corresponding to a port number.
   *
   * @param resolve_flags A set of flags that determine how name resolution
   * should be performed. The default flags are suitable for local service
   * binding.
   *
   * @note On POSIX systems, service names are typically defined in the file
   * <tt>/etc/services</tt>. On Windows, service names may be found in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\services</tt>. Operating systems
   * may use additional locations when resolving service names.
   */
  basic_resolver_query(const std::string& service,
      resolver_query_base::flags resolve_flags = passive | address_configured)
    : hints_(),
      host_name_(),
      service_name_(service)
  {
    typename InternetProtocol::endpoint endpoint;
    hints_.ai_flags = static_cast<int>(resolve_flags);
    hints_.ai_family = PF_UNSPEC;
    hints_.ai_socktype = endpoint.protocol().type();
    hints_.ai_protocol = endpoint.protocol().protocol();
    hints_.ai_addrlen = 0;
    hints_.ai_canonname = 0;
    hints_.ai_addr = 0;
    hints_.ai_next = 0;
  }

  /// Construct with specified service name for a given protocol.
  /**
   * This constructor is typically used to perform name resolution for local
   * service binding with a specific protocol version.
   *
   * @param protocol A protocol object, normally representing either the IPv4 or
   * IPv6 version of an internet protocol.
   *
   * @param service A string identifying the requested service. This may be a
   * descriptive name or a numeric string corresponding to a port number.
   *
   * @param resolve_flags A set of flags that determine how name resolution
   * should be performed. The default flags are suitable for local service
   * binding.
   *
   * @note On POSIX systems, service names are typically defined in the file
   * <tt>/etc/services</tt>. On Windows, service names may be found in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\services</tt>. Operating systems
   * may use additional locations when resolving service names.
   */
  basic_resolver_query(const protocol_type& protocol,
      const std::string& service,
      resolver_query_base::flags resolve_flags = passive | address_configured)
    : hints_(),
      host_name_(),
      service_name_(service)
  {
    hints_.ai_flags = static_cast<int>(resolve_flags);
    hints_.ai_family = protocol.family();
    hints_.ai_socktype = protocol.type();
    hints_.ai_protocol = protocol.protocol();
    hints_.ai_addrlen = 0;
    hints_.ai_canonname = 0;
    hints_.ai_addr = 0;
    hints_.ai_next = 0;
  }

  /// Construct with specified host name and service name for any protocol.
  /**
   * This constructor is typically used to perform name resolution for
   * communication with remote hosts.
   *
   * @param host A string identifying a location. May be a descriptive name or
   * a numeric address string. If an empty string and the passive flag has been
   * specified, the resolved endpoints are suitable for local service binding.
   * If an empty string and passive is not specified, the resolved endpoints
   * will use the loopback address.
   *
   * @param service A string identifying the requested service. This may be a
   * descriptive name or a numeric string corresponding to a port number. May
   * be an empty string, in which case all resolved endpoints will have a port
   * number of 0.
   *
   * @param resolve_flags A set of flags that determine how name resolution
   * should be performed. The default flags are suitable for communication with
   * remote hosts.
   *
   * @note On POSIX systems, host names may be locally defined in the file
   * <tt>/etc/hosts</tt>. On Windows, host names may be defined in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\hosts</tt>. Remote host name
   * resolution is performed using DNS. Operating systems may use additional
   * locations when resolving host names (such as NETBIOS names on Windows).
   *
   * On POSIX systems, service names are typically defined in the file
   * <tt>/etc/services</tt>. On Windows, service names may be found in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\services</tt>. Operating systems
   * may use additional locations when resolving service names.
   */
  basic_resolver_query(const std::string& host, const std::string& service,
      resolver_query_base::flags resolve_flags = address_configured)
    : hints_(),
      host_name_(host),
      service_name_(service)
  {
    typename InternetProtocol::endpoint endpoint;
    hints_.ai_flags = static_cast<int>(resolve_flags);
    hints_.ai_family = BOOST_ASIO_OS_DEF(AF_UNSPEC);
    hints_.ai_socktype = endpoint.protocol().type();
    hints_.ai_protocol = endpoint.protocol().protocol();
    hints_.ai_addrlen = 0;
    hints_.ai_canonname = 0;
    hints_.ai_addr = 0;
    hints_.ai_next = 0;
  }

  /// Construct with specified host name and service name for a given protocol.
  /**
   * This constructor is typically used to perform name resolution for
   * communication with remote hosts.
   *
   * @param protocol A protocol object, normally representing either the IPv4 or
   * IPv6 version of an internet protocol.
   *
   * @param host A string identifying a location. May be a descriptive name or
   * a numeric address string. If an empty string and the passive flag has been
   * specified, the resolved endpoints are suitable for local service binding.
   * If an empty string and passive is not specified, the resolved endpoints
   * will use the loopback address.
   *
   * @param service A string identifying the requested service. This may be a
   * descriptive name or a numeric string corresponding to a port number. May
   * be an empty string, in which case all resolved endpoints will have a port
   * number of 0.
   *
   * @param resolve_flags A set of flags that determine how name resolution
   * should be performed. The default flags are suitable for communication with
   * remote hosts.
   *
   * @note On POSIX systems, host names may be locally defined in the file
   * <tt>/etc/hosts</tt>. On Windows, host names may be defined in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\hosts</tt>. Remote host name
   * resolution is performed using DNS. Operating systems may use additional
   * locations when resolving host names (such as NETBIOS names on Windows).
   *
   * On POSIX systems, service names are typically defined in the file
   * <tt>/etc/services</tt>. On Windows, service names may be found in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\services</tt>. Operating systems
   * may use additional locations when resolving service names.
   */
  basic_resolver_query(const protocol_type& protocol,
      const std::string& host, const std::string& service,
      resolver_query_base::flags resolve_flags = address_configured)
    : hints_(),
      host_name_(host),
      service_name_(service)
  {
    hints_.ai_flags = static_cast<int>(resolve_flags);
    hints_.ai_family = protocol.family();
    hints_.ai_socktype = protocol.type();
    hints_.ai_protocol = protocol.protocol();
    hints_.ai_addrlen = 0;
    hints_.ai_canonname = 0;
    hints_.ai_addr = 0;
    hints_.ai_next = 0;
  }

  /// Get the hints associated with the query.
  const boost::asio::detail::addrinfo_type& hints() const
  {
    return hints_;
  }

  /// Get the host name associated with the query.
  std::string host_name() const
  {
    return host_name_;
  }

  /// Get the service name associated with the query.
  std::string service_name() const
  {
    return service_name_;
  }

private:
  boost::asio::detail::addrinfo_type hints_;
  std::string host_name_;
  std::string service_name_;
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_BASIC_RESOLVER_QUERY_HPP

/* basic_resolver_query.hpp
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
*/