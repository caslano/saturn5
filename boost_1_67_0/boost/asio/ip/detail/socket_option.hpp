//
// detail/socket_option.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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