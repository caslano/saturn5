//
// ip/udp.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_UDP_HPP
#define BOOST_ASIO_IP_UDP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/basic_datagram_socket.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
#include <boost/asio/ip/basic_resolver.hpp>
#include <boost/asio/ip/basic_resolver_iterator.hpp>
#include <boost/asio/ip/basic_resolver_query.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Encapsulates the flags needed for UDP.
/**
 * The boost::asio::ip::udp class contains flags necessary for UDP sockets.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Protocol, InternetProtocol.
 */
class udp
{
public:
  /// The type of a UDP endpoint.
  typedef basic_endpoint<udp> endpoint;

  /// Construct to represent the IPv4 UDP protocol.
  static udp v4() BOOST_ASIO_NOEXCEPT
  {
    return udp(BOOST_ASIO_OS_DEF(AF_INET));
  }

  /// Construct to represent the IPv6 UDP protocol.
  static udp v6() BOOST_ASIO_NOEXCEPT
  {
    return udp(BOOST_ASIO_OS_DEF(AF_INET6));
  }

  /// Obtain an identifier for the type of the protocol.
  int type() const BOOST_ASIO_NOEXCEPT
  {
    return BOOST_ASIO_OS_DEF(SOCK_DGRAM);
  }

  /// Obtain an identifier for the protocol.
  int protocol() const BOOST_ASIO_NOEXCEPT
  {
    return BOOST_ASIO_OS_DEF(IPPROTO_UDP);
  }

  /// Obtain an identifier for the protocol family.
  int family() const BOOST_ASIO_NOEXCEPT
  {
    return family_;
  }

  /// The UDP socket type.
  typedef basic_datagram_socket<udp> socket;

  /// The UDP resolver type.
  typedef basic_resolver<udp> resolver;

  /// Compare two protocols for equality.
  friend bool operator==(const udp& p1, const udp& p2)
  {
    return p1.family_ == p2.family_;
  }

  /// Compare two protocols for inequality.
  friend bool operator!=(const udp& p1, const udp& p2)
  {
    return p1.family_ != p2.family_;
  }

private:
  // Construct with a specific family.
  explicit udp(int protocol_family) BOOST_ASIO_NOEXCEPT
    : family_(protocol_family)
  {
  }

  int family_;
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_UDP_HPP

/* udp.hpp
Ws16c9vEvtNqjlu4sa9iR3y2/6u6ht8Cx9jbQokj1qRxidjfDzu23b1e2LFtM2a4XsL+WvzKY22/cnOeWyVsc5OXX4r9m7B5kbXqdL7crzvL+nYLGaML3bNW5aoDcrclxsQwpHcDqH0dvLfx2GuHiV+6LdHTNGRM72rsbXUNsecc42TP6xjYC/BFjHMdsd/o2jj2732dMcbuM7/VNW5+54jvJX4/qms+vOyQ/71PlnPVbawlL8xaeRMhbdKMoeVHGAMrrmUMLDPGd6I7MKmY6zGH7W/X8UHXTZ3GwAgTNAbWTewV1kDOp9dP0BhYF/Evtc4JjIERR+1jYDfHRx4DO1v8yugTXBHXhdnzLawLo2UevP5BTOi4yu/7MGYbHzSuMjp7/KgR2UNkdEvy+FKfkDEVwpz42Bbxhd3rcHNsaPr+gKyVEDZ9OuoTOY2Eq30/0YQTH/d5qU903Oe/fdxnoIz7/OTwyo+vO/OWooF7P1iTf+P8r6PjPnUZ99G1Drjn+b4bv2FxL3P8/hiTZZ4/6N90rYMOFvUBLZ27mwZPg51gN9gdZsKxsCecpnPU59vhdI7+6fBW2AfugGfoHld94Z/gmfBT2A/Gc67+Ogd9gM45P1vnmp8Dz4UDYRkcAhfCofAitS9R++VwGFwNh8Pb4Ai4DebqXPMfwqfU/qzan4cj4UE4Cn4A86CL8jgPJsHR8HQ4Ag6D4+AkOMnMldZ7DrwjzFzppjrekKrjDS10nKGlzulPh9Olzsgf/IHuKdgarlJ/szdRfOTxgDeMHEdC7XLbouMG/7fjBt/V/N3o2EF07ODbHDvI7Oe18jDlmBv6RccMokf0iB7RI3pEj+gRPaJH9Ige0SN6RI//lOP7GP+funhKEQP4tgbASY3/t2ZW2xl8pF7HIqAey45a4p1SWlY2a365JfoBuxz6AV31u3ic5rUe5h7CV1uBcc7cUaNGjMuTeGSsyoo8Pqhja7o/guoejOQcTW0B+Os+uAfiJl0FhVOmTZ8n+g/2KXRO1euNZa575aLA2JqGa2Wl6Dzh98Xeg4qJsQr5pXvx8Evj0TH4d0TuNLGPMPG0CIzROeYAFxv/oeIfk2lxlMwp0nSMlPWFZa9B1ZXw+fPPjLe2EP/lVmck/HuNxbltt/gQ/YFUft1pyxu7kQ2ZW53i30/E5DuBfNcTuaRkiZOdsgLz9x+VePupHV0DsTeQPfoy8beon0c6yB59e0V/IJv/EfbRS9Yw7T3Ea4dpUHUoZD6wyuQgM1rmAy/tVHM+cEfscdh30gbfbGaPP/Ob+GbDyZjduFd3rvs49OsyDk07UbccSBvAzW4DqiNgxkmlnoPG+RNjda4riWwHV2obrXKHaaO1t08N0820k/vEXugK1y5HGPkuZk/JLWJf4IrQLlU+w8yx3yz2+a4a7dDU/yvi391VQ2fArDkx12P7/5DyGE4Y35oTRzwSxtlOjR5MV/Fbg32hzk/3y8eZPViYAWR0hrbL+Se5arRj0+5/Kf5FrrNpEw0dOgmlGFdHX1v4QVPf7z0tSD3uj3f2udNW8KubzoI995p0Bs29zgvTdiaGaTv5tbSdnLjwbWe1t0bbMV1bxLZDmOC285i31raDfHDbecRba9tBPrjt7PTW3nbe8tbedpbGhLYdKzZy2xkQE9J2VD5OdWCC285T3trbzuPeyG3nxx20D2kqv03beUL6Fp3Hfxxtx4r99tpOT9U72R6v8w0xTTAP2eHt++43yXbb0ceBKdMq55VGajMqm2b21X1N7JutWfz/McZfdoSbXah1x7k03NXU1ESJyzcj33dvCLS3gnkz9F6SZ86VKucajX2/2G+1mhNHFTEjh3twPMmWxlM=
*/