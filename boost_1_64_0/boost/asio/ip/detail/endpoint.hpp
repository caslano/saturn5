//
// ip/detail/endpoint.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_DETAIL_ENDPOINT_HPP
#define BOOST_ASIO_IP_DETAIL_ENDPOINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <string>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/winsock_init.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/ip/address.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {
namespace detail {

// Helper class for implementating an IP endpoint.
class endpoint
{
public:
  // Default constructor.
  BOOST_ASIO_DECL endpoint() BOOST_ASIO_NOEXCEPT;

  // Construct an endpoint using a family and port number.
  BOOST_ASIO_DECL endpoint(int family,
      unsigned short port_num) BOOST_ASIO_NOEXCEPT;

  // Construct an endpoint using an address and port number.
  BOOST_ASIO_DECL endpoint(const boost::asio::ip::address& addr,
      unsigned short port_num) BOOST_ASIO_NOEXCEPT;

  // Copy constructor.
  endpoint(const endpoint& other) BOOST_ASIO_NOEXCEPT
    : data_(other.data_)
  {
  }

  // Assign from another endpoint.
  endpoint& operator=(const endpoint& other) BOOST_ASIO_NOEXCEPT
  {
    data_ = other.data_;
    return *this;
  }

  // Get the underlying endpoint in the native type.
  boost::asio::detail::socket_addr_type* data() BOOST_ASIO_NOEXCEPT
  {
    return &data_.base;
  }

  // Get the underlying endpoint in the native type.
  const boost::asio::detail::socket_addr_type* data() const BOOST_ASIO_NOEXCEPT
  {
    return &data_.base;
  }

  // Get the underlying size of the endpoint in the native type.
  std::size_t size() const BOOST_ASIO_NOEXCEPT
  {
    if (is_v4())
      return sizeof(boost::asio::detail::sockaddr_in4_type);
    else
      return sizeof(boost::asio::detail::sockaddr_in6_type);
  }

  // Set the underlying size of the endpoint in the native type.
  BOOST_ASIO_DECL void resize(std::size_t new_size);

  // Get the capacity of the endpoint in the native type.
  std::size_t capacity() const BOOST_ASIO_NOEXCEPT
  {
    return sizeof(data_);
  }

  // Get the port associated with the endpoint.
  BOOST_ASIO_DECL unsigned short port() const BOOST_ASIO_NOEXCEPT;

  // Set the port associated with the endpoint.
  BOOST_ASIO_DECL void port(unsigned short port_num) BOOST_ASIO_NOEXCEPT;

  // Get the IP address associated with the endpoint.
  BOOST_ASIO_DECL boost::asio::ip::address address() const BOOST_ASIO_NOEXCEPT;

  // Set the IP address associated with the endpoint.
  BOOST_ASIO_DECL void address(
      const boost::asio::ip::address& addr) BOOST_ASIO_NOEXCEPT;

  // Compare two endpoints for equality.
  BOOST_ASIO_DECL friend bool operator==(const endpoint& e1,
      const endpoint& e2) BOOST_ASIO_NOEXCEPT;

  // Compare endpoints for ordering.
  BOOST_ASIO_DECL friend bool operator<(const endpoint& e1,
      const endpoint& e2) BOOST_ASIO_NOEXCEPT;

  // Determine whether the endpoint is IPv4.
  bool is_v4() const BOOST_ASIO_NOEXCEPT
  {
    return data_.base.sa_family == BOOST_ASIO_OS_DEF(AF_INET);
  }

#if !defined(BOOST_ASIO_NO_IOSTREAM)
  // Convert to a string.
  BOOST_ASIO_DECL std::string to_string() const;
#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

private:
  // The underlying IP socket address.
  union data_union
  {
    boost::asio::detail::socket_addr_type base;
    boost::asio::detail::sockaddr_in4_type v4;
    boost::asio::detail::sockaddr_in6_type v6;
  } data_;
};

} // namespace detail
} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ip/detail/impl/endpoint.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_IP_DETAIL_ENDPOINT_HPP

/* endpoint.hpp
k1nglxmlMikqcxv2B+SdZenKRE8jK1Jc1di3y7vG5RdFkjmM/VdyH7v8AnO+GjJxyXq+hpfvNfHUSFNmsqY75vLtifXrW5HSPhG5HbJG3xW8C8ZZNd+BRmNvgn0uZf4gcj9pTv1g5qT4zNokn47hQ5hidYO83/h+FygxPLfg57/3uq1wx2BOSxr6NT7iIq20s2T0W33XsNW+qGROSUWxPq+4/fdm7qX+9yDcuAfqO48+r+BWLXLcw9StGLcZyfoMo2HLIX0gbtIHmv2v6Htwk77HPDuN9D0fGzm7vXMNSFhLdR1L5LpH36Jn8DPRIh34Xqt6tddiOhBfpu+ZaM70hfJIFOmZSOVSzL14qNiXsg6Ty/mcZO73k8W/yOpKGpzvnnP1HetLElF8Es9Dfj3Jt5uG6hFuIy1ZXyerHuGgSVOGDB89JXvk2NGTppBPVDlLSy3z/l4HXUDn89fKZqHnu9d+/gp/PrNu35Ywa+IR5oT1RreEX7ePayA0fTuRrQqbPqM6KmlcEiaNhDN6o+f2Ca83iswJ641yzhC9Uc4TUW90QPPQ/G1Hfl2E/M3nwo2QNw2T4vimUO78rmT8Td90gvlSvVH9XsA5atRZ09TQPP0C2erweVJ12MjtinC16sPif8L6sFvqsNZiP/+1GSZfuwh/qGa+cgaOyZlCL1voy1P/cGtcOvKUFVpXxt/cb44jT/3D5CnL1FVwnla3CM3T/cha34TLE92N7ne7wfdNnOEIRjwC+SJccLrH1SHdKZruDZJGjbNGmypvGZrOHcinh0un6QYilz/hTD+wMnw/gMyJ9wP9w/QDK2vpB4akhW9bWeHzRzcQMW+EqbVt4X/i/cDxtK3UVqF5qkY2P2yepBuQND8WmifC1NoH4H/ifcBjx9EHvB8mT88QvorzO/T8Rw06N3vwWEcfsDQ0TxomRd95QuoJ/xPvA5aGyRPnCFtP1T8IzdNThF8XLk+Oenoi3D3oGPW07iTq6Yk61JOsi/s9zF0IP4fg3zen4WFJzyVVY4sOzfrr7K7DGmb2yCsfHHmOwpxGtvu1zw+4LOPD0ntfvCd3VOrSPS9Fmutw/HMUws+BiDR3IdLciP+8OQ3f9dyFCHMmZE7DVgyHvNPHkf8/Wr73YHSBuZZ53zW/fe+1+Tq2cI/j9w7H782O3/c7ft+lv1dh7nb83uD4vdHx+xeO35v4fQRe5ZhXgY5BxHkVg/G2OUTnVWRDO1wOZrWGo8uV/MbCARpuv4b7I3TDV2ED+BpsDg/ANCt4vkK1xtfTHap3f6vOz7gddrPzDbNVT34c/BmcCLfAqXArLIb3wSq7DOA1cBt8Ut1/B7fDP8Md8F34oOrX74QyJ0X16R+DbeDjsCOshp3V3h0+ofryT8Lz4bNwJnweLoYvwCrVn18Hfw13wBdhNdwD96j7XvgU9FIOT8NYeAfsCO+EGZBwWg869ghHaf2ZetD5Cck6P6EDvBqeDq/R8lsFz1W7P74jGl/zMPFdpvVaxV9DuBQ20XkRTeHlMEXtvn0+dYwOttX4nPt8LtZ2cRFMhRdLPWPX8GvNGBXfZDR8krZlS/X5G8GRet48bVejYVudv9IdjtX5GRNgLpwE8+D5cA7Mh+WwAC7QeS2XqX2Z2q9SuWtggaaPNqfjN6RB0xeHydX0XafpW6PldD08ReeBdIE3arpugkN0PshwtRM/+0ToGIGOwRyRNHP94G7pvKFOer2dpddXFjyo9XsIFsI39Xr4M5wN/wKXwLfgavhXeAt8B94H34UPwyPwWfgRfAl+DPfDz+AB+LnOTzkK/6b2T9T+BXS7eF1Xe5I9nwu2hl/BbPg1nAxtuRLohQtgDFwGY+FKWA8=
*/