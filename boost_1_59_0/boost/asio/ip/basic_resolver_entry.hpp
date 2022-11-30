//
// ip/basic_resolver_entry.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_BASIC_RESOLVER_ENTRY_HPP
#define BOOST_ASIO_IP_BASIC_RESOLVER_ENTRY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <string>
#include <boost/asio/detail/string_view.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// An entry produced by a resolver.
/**
 * The boost::asio::ip::basic_resolver_entry class template describes an entry
 * as returned by a resolver.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename InternetProtocol>
class basic_resolver_entry
{
public:
  /// The protocol type associated with the endpoint entry.
  typedef InternetProtocol protocol_type;

  /// The endpoint type associated with the endpoint entry.
  typedef typename InternetProtocol::endpoint endpoint_type;

  /// Default constructor.
  basic_resolver_entry()
  {
  }

  /// Construct with specified endpoint, host name and service name.
  basic_resolver_entry(const endpoint_type& ep,
      BOOST_ASIO_STRING_VIEW_PARAM host, BOOST_ASIO_STRING_VIEW_PARAM service)
    : endpoint_(ep),
      host_name_(static_cast<std::string>(host)),
      service_name_(static_cast<std::string>(service))
  {
  }

  /// Get the endpoint associated with the entry.
  endpoint_type endpoint() const
  {
    return endpoint_;
  }

  /// Convert to the endpoint associated with the entry.
  operator endpoint_type() const
  {
    return endpoint_;
  }

  /// Get the host name associated with the entry.
  std::string host_name() const
  {
    return host_name_;
  }

  /// Get the host name associated with the entry.
  template <class Allocator>
  std::basic_string<char, std::char_traits<char>, Allocator> host_name(
      const Allocator& alloc = Allocator()) const
  {
    return std::basic_string<char, std::char_traits<char>, Allocator>(
        host_name_.c_str(), alloc);
  }

  /// Get the service name associated with the entry.
  std::string service_name() const
  {
    return service_name_;
  }

  /// Get the service name associated with the entry.
  template <class Allocator>
  std::basic_string<char, std::char_traits<char>, Allocator> service_name(
      const Allocator& alloc = Allocator()) const
  {
    return std::basic_string<char, std::char_traits<char>, Allocator>(
        service_name_.c_str(), alloc);
  }

private:
  endpoint_type endpoint_;
  std::string host_name_;
  std::string service_name_;
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_BASIC_RESOLVER_ENTRY_HPP

/* basic_resolver_entry.hpp
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
*/