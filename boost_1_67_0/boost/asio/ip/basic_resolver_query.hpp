//
// ip/basic_resolver_query.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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