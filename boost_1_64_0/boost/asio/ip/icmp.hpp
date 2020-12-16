//
// ip/icmp.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_ICMP_HPP
#define BOOST_ASIO_IP_ICMP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/basic_raw_socket.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
#include <boost/asio/ip/basic_resolver.hpp>
#include <boost/asio/ip/basic_resolver_iterator.hpp>
#include <boost/asio/ip/basic_resolver_query.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Encapsulates the flags needed for ICMP.
/**
 * The boost::asio::ip::icmp class contains flags necessary for ICMP sockets.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Protocol, InternetProtocol.
 */
class icmp
{
public:
  /// The type of a ICMP endpoint.
  typedef basic_endpoint<icmp> endpoint;

  /// Construct to represent the IPv4 ICMP protocol.
  static icmp v4() BOOST_ASIO_NOEXCEPT
  {
    return icmp(BOOST_ASIO_OS_DEF(IPPROTO_ICMP),
        BOOST_ASIO_OS_DEF(AF_INET));
  }

  /// Construct to represent the IPv6 ICMP protocol.
  static icmp v6() BOOST_ASIO_NOEXCEPT
  {
    return icmp(BOOST_ASIO_OS_DEF(IPPROTO_ICMPV6),
        BOOST_ASIO_OS_DEF(AF_INET6));
  }

  /// Obtain an identifier for the type of the protocol.
  int type() const BOOST_ASIO_NOEXCEPT
  {
    return BOOST_ASIO_OS_DEF(SOCK_RAW);
  }

  /// Obtain an identifier for the protocol.
  int protocol() const BOOST_ASIO_NOEXCEPT
  {
    return protocol_;
  }

  /// Obtain an identifier for the protocol family.
  int family() const BOOST_ASIO_NOEXCEPT
  {
    return family_;
  }

  /// The ICMP socket type.
  typedef basic_raw_socket<icmp> socket;

  /// The ICMP resolver type.
  typedef basic_resolver<icmp> resolver;

  /// Compare two protocols for equality.
  friend bool operator==(const icmp& p1, const icmp& p2)
  {
    return p1.protocol_ == p2.protocol_ && p1.family_ == p2.family_;
  }

  /// Compare two protocols for inequality.
  friend bool operator!=(const icmp& p1, const icmp& p2)
  {
    return p1.protocol_ != p2.protocol_ || p1.family_ != p2.family_;
  }

private:
  // Construct with a specific family.
  explicit icmp(int protocol_id, int protocol_family) BOOST_ASIO_NOEXCEPT
    : protocol_(protocol_id),
      family_(protocol_family)
  {
  }

  int protocol_;
  int family_;
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_ICMP_HPP

/* icmp.hpp
s49/zgj9jlDP3xkQfpL6G/HV3FkRf9fw99ssfzNPpdJs5W/6dX0/Z2rofoHZVuXvIPRnM50ha8TACsiMGwAuEnnupoPIBe8FR4P3gWPAT4MTwfvBMnA/eLbcl+9byJor+gB5rv6+hXzHY7Dlux4rwHwJh/lbhH+SC/9q4Ud+JdcacJyEw3tMuoX/vS57TG4nyTDwU+AEcB9YAt4JloN3gbPBh8AF4L3gKvA+cD14P7gR/CxYBz4AbgMfBC8VPtGvrPHhN2UX/T5MulHgI+Ak8GvgOvCb8rzHwB3gN8Br5T7PxV5k/Qx4UJ6bAdbKc3tJNwX8AVgK/hCcCf4YPAt8DlwC/lTy+zm4F/wF+DD4K/Dr4K/Bx8BDYb3qNRtq3YrK19RbO2heb6f+s8FqcDy4GZwObhE72QcGwa1gBbgNrALrwfPABvAC8B3gRWAj2Aa2gzvBDrGvS8EU8twJDgQvBzPAd4KZ4HvAFnA32AleDV4Dvg/8oIT3SPhG8BrwJgnfKuE7wQ+An5HnPSbh74MfBH8Ffgh8UfL5C/hRcAh6eT84DLwWzAFN/jHge8Fx4I1gKXgTeBp4MzgLvB1cAnaBK8A7wA3gp8AacJ+Uv96Q36jBi6T+B4Ebpf4fNfMHnwDzwG+AIyQ8SsJl4DfBeeCT4EK5XwV+GzwX/I7ktwc6KPl9VPIbCu6S/PJIlwWOBNVcitT/aMlnHDgfnAguAyeBK8BScBVYJvnNAC8Ep4DbwKlgA1gCXgeWgx8004lcXYb8zgjeL3IFwBsgQ85VzgWvA4vBD4AzwA+By8HrwdXgR8ALzbKBtSa/tL9bwVbwRrAd3AteJvd3gR8Dr5fwzRK+HbwF7DLv6/5IfrMDn3bpj34v8r0MTgZfAcvAP4Fngkeln3kVbAb/CrZL+FIJ75V0+8DXwIfA18Hvg38TOei75Lcf6ljkSAdXiBz/kPx9vlB/kQQuAJPBW+T+PWAaeB84AHwCpC1Kfye/M4ATXPq7QaQbDGaIvfilvxgC5oODwUIJj5GwPt9Hnpvqcm5OM3Kb2AKmgDus5/vE4FsnfOcJ3/mgfi/GKEdAypEl5Rgm5ciRcmSDhRIeI2GRh7lzb3neIfJsF3kaLeUoisFXJ3xbhW+b8AVNXuFbKHwm/0zhy5b3boG8B0fIe6MQPB0cJc+5Btojz6FtqucM4e8r5DljhW8cOA0slvfNJHnfEKfa91SwCSyRdlIKfh4sA78JzgR/Bs4Gk8ljHpgBngEOBs+0fr/sbG//Iij+wQIwB1wo5SQc8U+Ev8Dk78f3y6pj8G8S/mrhrxH+agt/Zwz5K4R/sfAtEfkJa/5ua/79+G5dbwz+y4X/ncJ/heInLPyV0BHhHwlV+ezn2j8r9vgcmAT+VJ73M3A4+Dw4Avy5PO9JPYdCvYp95Zo+rTzvLHmvBMG54AJwKbgQXAsuAjeAi8EacBnYBC4H28ALwavAFfIeWQnukftd4GrwLnA9eI/c/xJYBX4NXAM+BZ4LPi3pnpF0vwHPB/8gYbM8yCpzDKocyhf3gdlSHmTU6briTNfTR7qW4/wuXOKbcIlvwp2Mb8Kl3J34Llziu3D/vu/C3cY+8B7oeegNKG8M33yDNkK7oH3QU9AhKHsscdB6qBPaBz0OvQT5xxEH1ULXQPuhp6FjUFEx31yBaqFO6DboS8WJ/eeJK3ElrsSVuBLX8V5v2f7/mvb2k7X//7UpPCO8xtPnXON5ZDbzJMWR9RwL1q1bu3TheevYRN3c0RRaw71QreFGqFb926rwFKp9JOa4cxr3Pk46f0o++3si64onxfE7O89nPKueb1t/8gHZo36LyLobSj+dcaW7vK11bM8x15+vWro=
*/