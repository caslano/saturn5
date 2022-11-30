//
// detail/socket_option.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_DETAIL_SOCKET_OPTION_HPP
#define BOOST_ASIO_IP_DETAIL_SOCKET_OPTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <boost/asio/detail/socket_ops.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/throw_exception.hpp>
#include <boost/asio/ip/address.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {
namespace detail {
namespace socket_option {

// Helper template for implementing multicast enable loopback options.
template <int IPv4_Level, int IPv4_Name, int IPv6_Level, int IPv6_Name>
class multicast_enable_loopback
{
public:
#if defined(__sun) || defined(__osf__)
  typedef unsigned char ipv4_value_type;
  typedef unsigned char ipv6_value_type;
#elif defined(_AIX) || defined(__hpux) || defined(__QNXNTO__) 
  typedef unsigned char ipv4_value_type;
  typedef unsigned int ipv6_value_type;
#else
  typedef int ipv4_value_type;
  typedef int ipv6_value_type;
#endif

  // Default constructor.
  multicast_enable_loopback()
    : ipv4_value_(0),
      ipv6_value_(0)
  {
  }

  // Construct with a specific option value.
  explicit multicast_enable_loopback(bool v)
    : ipv4_value_(v ? 1 : 0),
      ipv6_value_(v ? 1 : 0)
  {
  }

  // Set the value of the boolean.
  multicast_enable_loopback& operator=(bool v)
  {
    ipv4_value_ = v ? 1 : 0;
    ipv6_value_ = v ? 1 : 0;
    return *this;
  }

  // Get the current value of the boolean.
  bool value() const
  {
    return !!ipv4_value_;
  }

  // Convert to bool.
  operator bool() const
  {
    return !!ipv4_value_;
  }

  // Test for false.
  bool operator!() const
  {
    return !ipv4_value_;
  }

  // Get the level of the socket option.
  template <typename Protocol>
  int level(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return IPv6_Level;
    return IPv4_Level;
  }

  // Get the name of the socket option.
  template <typename Protocol>
  int name(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return IPv6_Name;
    return IPv4_Name;
  }

  // Get the address of the boolean data.
  template <typename Protocol>
  void* data(const Protocol& protocol)
  {
    if (protocol.family() == PF_INET6)
      return &ipv6_value_;
    return &ipv4_value_;
  }

  // Get the address of the boolean data.
  template <typename Protocol>
  const void* data(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return &ipv6_value_;
    return &ipv4_value_;
  }

  // Get the size of the boolean data.
  template <typename Protocol>
  std::size_t size(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return sizeof(ipv6_value_);
    return sizeof(ipv4_value_);
  }

  // Set the size of the boolean data.
  template <typename Protocol>
  void resize(const Protocol& protocol, std::size_t s)
  {
    if (protocol.family() == PF_INET6)
    {
      if (s != sizeof(ipv6_value_))
      {
        std::length_error ex("multicast_enable_loopback socket option resize");
        boost::asio::detail::throw_exception(ex);
      }
      ipv4_value_ = ipv6_value_ ? 1 : 0;
    }
    else
    {
      if (s != sizeof(ipv4_value_))
      {
        std::length_error ex("multicast_enable_loopback socket option resize");
        boost::asio::detail::throw_exception(ex);
      }
      ipv6_value_ = ipv4_value_ ? 1 : 0;
    }
  }

private:
  ipv4_value_type ipv4_value_;
  ipv6_value_type ipv6_value_;
};

// Helper template for implementing unicast hops options.
template <int IPv4_Level, int IPv4_Name, int IPv6_Level, int IPv6_Name>
class unicast_hops
{
public:
  // Default constructor.
  unicast_hops()
    : value_(0)
  {
  }

  // Construct with a specific option value.
  explicit unicast_hops(int v)
    : value_(v)
  {
  }

  // Set the value of the option.
  unicast_hops& operator=(int v)
  {
    value_ = v;
    return *this;
  }

  // Get the current value of the option.
  int value() const
  {
    return value_;
  }

  // Get the level of the socket option.
  template <typename Protocol>
  int level(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return IPv6_Level;
    return IPv4_Level;
  }

  // Get the name of the socket option.
  template <typename Protocol>
  int name(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return IPv6_Name;
    return IPv4_Name;
  }

  // Get the address of the data.
  template <typename Protocol>
  int* data(const Protocol&)
  {
    return &value_;
  }

  // Get the address of the data.
  template <typename Protocol>
  const int* data(const Protocol&) const
  {
    return &value_;
  }

  // Get the size of the data.
  template <typename Protocol>
  std::size_t size(const Protocol&) const
  {
    return sizeof(value_);
  }

  // Set the size of the data.
  template <typename Protocol>
  void resize(const Protocol&, std::size_t s)
  {
    if (s != sizeof(value_))
    {
      std::length_error ex("unicast hops socket option resize");
      boost::asio::detail::throw_exception(ex);
    }
#if defined(__hpux)
    if (value_ < 0)
      value_ = value_ & 0xFF;
#endif
  }

private:
  int value_;
};

// Helper template for implementing multicast hops options.
template <int IPv4_Level, int IPv4_Name, int IPv6_Level, int IPv6_Name>
class multicast_hops
{
public:
#if defined(BOOST_ASIO_WINDOWS) && defined(UNDER_CE)
  typedef int ipv4_value_type;
#else
  typedef unsigned char ipv4_value_type;
#endif
  typedef int ipv6_value_type;

  // Default constructor.
  multicast_hops()
    : ipv4_value_(0),
      ipv6_value_(0)
  {
  }

  // Construct with a specific option value.
  explicit multicast_hops(int v)
  {
    if (v < 0 || v > 255)
    {
      std::out_of_range ex("multicast hops value out of range");
      boost::asio::detail::throw_exception(ex);
    }
    ipv4_value_ = (ipv4_value_type)v;
    ipv6_value_ = v;
  }

  // Set the value of the option.
  multicast_hops& operator=(int v)
  {
    if (v < 0 || v > 255)
    {
      std::out_of_range ex("multicast hops value out of range");
      boost::asio::detail::throw_exception(ex);
    }
    ipv4_value_ = (ipv4_value_type)v;
    ipv6_value_ = v;
    return *this;
  }

  // Get the current value of the option.
  int value() const
  {
    return ipv6_value_;
  }

  // Get the level of the socket option.
  template <typename Protocol>
  int level(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return IPv6_Level;
    return IPv4_Level;
  }

  // Get the name of the socket option.
  template <typename Protocol>
  int name(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return IPv6_Name;
    return IPv4_Name;
  }

  // Get the address of the data.
  template <typename Protocol>
  void* data(const Protocol& protocol)
  {
    if (protocol.family() == PF_INET6)
      return &ipv6_value_;
    return &ipv4_value_;
  }

  // Get the address of the data.
  template <typename Protocol>
  const void* data(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return &ipv6_value_;
    return &ipv4_value_;
  }

  // Get the size of the data.
  template <typename Protocol>
  std::size_t size(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return sizeof(ipv6_value_);
    return sizeof(ipv4_value_);
  }

  // Set the size of the data.
  template <typename Protocol>
  void resize(const Protocol& protocol, std::size_t s)
  {
    if (protocol.family() == PF_INET6)
    {
      if (s != sizeof(ipv6_value_))
      {
        std::length_error ex("multicast hops socket option resize");
        boost::asio::detail::throw_exception(ex);
      }
      if (ipv6_value_ < 0)
        ipv4_value_ = 0;
      else if (ipv6_value_ > 255)
        ipv4_value_ = 255;
      else
        ipv4_value_ = (ipv4_value_type)ipv6_value_;
    }
    else
    {
      if (s != sizeof(ipv4_value_))
      {
        std::length_error ex("multicast hops socket option resize");
        boost::asio::detail::throw_exception(ex);
      }
      ipv6_value_ = ipv4_value_;
    }
  }

private:
  ipv4_value_type ipv4_value_;
  ipv6_value_type ipv6_value_;
};

// Helper template for implementing ip_mreq-based options.
template <int IPv4_Level, int IPv4_Name, int IPv6_Level, int IPv6_Name>
class multicast_request
{
public:
  // Default constructor.
  multicast_request()
    : ipv4_value_(), // Zero-initialisation gives the "any" address.
      ipv6_value_() // Zero-initialisation gives the "any" address.
  {
  }

  // Construct with multicast address only.
  explicit multicast_request(const address& multicast_address)
    : ipv4_value_(), // Zero-initialisation gives the "any" address.
      ipv6_value_() // Zero-initialisation gives the "any" address.
  {
    if (multicast_address.is_v6())
    {
      using namespace std; // For memcpy.
      address_v6 ipv6_address = multicast_address.to_v6();
      address_v6::bytes_type bytes = ipv6_address.to_bytes();
      memcpy(ipv6_value_.ipv6mr_multiaddr.s6_addr, bytes.data(), 16);
      ipv6_value_.ipv6mr_interface = ipv6_address.scope_id();
    }
    else
    {
      ipv4_value_.imr_multiaddr.s_addr =
        boost::asio::detail::socket_ops::host_to_network_long(
            multicast_address.to_v4().to_uint());
      ipv4_value_.imr_interface.s_addr =
        boost::asio::detail::socket_ops::host_to_network_long(
            address_v4::any().to_uint());
    }
  }

  // Construct with multicast address and IPv4 address specifying an interface.
  explicit multicast_request(const address_v4& multicast_address,
      const address_v4& network_interface = address_v4::any())
    : ipv6_value_() // Zero-initialisation gives the "any" address.
  {
    ipv4_value_.imr_multiaddr.s_addr =
      boost::asio::detail::socket_ops::host_to_network_long(
          multicast_address.to_uint());
    ipv4_value_.imr_interface.s_addr =
      boost::asio::detail::socket_ops::host_to_network_long(
          network_interface.to_uint());
  }

  // Construct with multicast address and IPv6 network interface index.
  explicit multicast_request(
      const address_v6& multicast_address,
      unsigned long network_interface = 0)
    : ipv4_value_() // Zero-initialisation gives the "any" address.
  {
    using namespace std; // For memcpy.
    address_v6::bytes_type bytes = multicast_address.to_bytes();
    memcpy(ipv6_value_.ipv6mr_multiaddr.s6_addr, bytes.data(), 16);
    if (network_interface)
      ipv6_value_.ipv6mr_interface = network_interface;
    else
      ipv6_value_.ipv6mr_interface = multicast_address.scope_id();
  }

  // Get the level of the socket option.
  template <typename Protocol>
  int level(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return IPv6_Level;
    return IPv4_Level;
  }

  // Get the name of the socket option.
  template <typename Protocol>
  int name(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return IPv6_Name;
    return IPv4_Name;
  }

  // Get the address of the option data.
  template <typename Protocol>
  const void* data(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return &ipv6_value_;
    return &ipv4_value_;
  }

  // Get the size of the option data.
  template <typename Protocol>
  std::size_t size(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return sizeof(ipv6_value_);
    return sizeof(ipv4_value_);
  }

private:
  boost::asio::detail::in4_mreq_type ipv4_value_;
  boost::asio::detail::in6_mreq_type ipv6_value_;
};

// Helper template for implementing options that specify a network interface.
template <int IPv4_Level, int IPv4_Name, int IPv6_Level, int IPv6_Name>
class network_interface
{
public:
  // Default constructor.
  network_interface()
  {
    ipv4_value_.s_addr =
      boost::asio::detail::socket_ops::host_to_network_long(
          address_v4::any().to_uint());
    ipv6_value_ = 0;
  }

  // Construct with IPv4 interface.
  explicit network_interface(const address_v4& ipv4_interface)
  {
    ipv4_value_.s_addr =
      boost::asio::detail::socket_ops::host_to_network_long(
          ipv4_interface.to_uint());
    ipv6_value_ = 0;
  }

  // Construct with IPv6 interface.
  explicit network_interface(unsigned int ipv6_interface)
  {
    ipv4_value_.s_addr =
      boost::asio::detail::socket_ops::host_to_network_long(
          address_v4::any().to_uint());
    ipv6_value_ = ipv6_interface;
  }

  // Get the level of the socket option.
  template <typename Protocol>
  int level(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return IPv6_Level;
    return IPv4_Level;
  }

  // Get the name of the socket option.
  template <typename Protocol>
  int name(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return IPv6_Name;
    return IPv4_Name;
  }

  // Get the address of the option data.
  template <typename Protocol>
  const void* data(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return &ipv6_value_;
    return &ipv4_value_;
  }

  // Get the size of the option data.
  template <typename Protocol>
  std::size_t size(const Protocol& protocol) const
  {
    if (protocol.family() == PF_INET6)
      return sizeof(ipv6_value_);
    return sizeof(ipv4_value_);
  }

private:
  boost::asio::detail::in4_addr_type ipv4_value_;
  unsigned int ipv6_value_;
};

} // namespace socket_option
} // namespace detail
} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_DETAIL_SOCKET_OPTION_HPP

/* socket_option.hpp
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
*/