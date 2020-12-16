//
// generic/seq_packet_protocol.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_GENERIC_SEQ_PACKET_PROTOCOL_HPP
#define BOOST_ASIO_GENERIC_SEQ_PACKET_PROTOCOL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <typeinfo>
#include <boost/asio/basic_seq_packet_socket.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/throw_exception.hpp>
#include <boost/asio/generic/basic_endpoint.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace generic {

/// Encapsulates the flags needed for a generic sequenced packet socket.
/**
 * The boost::asio::generic::seq_packet_protocol class contains flags necessary
 * for seq_packet-oriented sockets of any address family and protocol.
 *
 * @par Examples
 * Constructing using a native address family and socket protocol:
 * @code seq_packet_protocol p(AF_INET, IPPROTO_SCTP); @endcode
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Protocol.
 */
class seq_packet_protocol
{
public:
  /// Construct a protocol object for a specific address family and protocol.
  seq_packet_protocol(int address_family, int socket_protocol)
    : family_(address_family),
      protocol_(socket_protocol)
  {
  }

  /// Construct a generic protocol object from a specific protocol.
  /**
   * @throws @c bad_cast Thrown if the source protocol is not based around
   * sequenced packets.
   */
  template <typename Protocol>
  seq_packet_protocol(const Protocol& source_protocol)
    : family_(source_protocol.family()),
      protocol_(source_protocol.protocol())
  {
    if (source_protocol.type() != type())
    {
      std::bad_cast ex;
      boost::asio::detail::throw_exception(ex);
    }
  }

  /// Obtain an identifier for the type of the protocol.
  int type() const BOOST_ASIO_NOEXCEPT
  {
    return BOOST_ASIO_OS_DEF(SOCK_SEQPACKET);
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

  /// Compare two protocols for equality.
  friend bool operator==(const seq_packet_protocol& p1,
      const seq_packet_protocol& p2)
  {
    return p1.family_ == p2.family_ && p1.protocol_ == p2.protocol_;
  }

  /// Compare two protocols for inequality.
  friend bool operator!=(const seq_packet_protocol& p1,
      const seq_packet_protocol& p2)
  {
    return !(p1 == p2);
  }

  /// The type of an endpoint.
  typedef basic_endpoint<seq_packet_protocol> endpoint;

  /// The generic socket type.
  typedef basic_seq_packet_socket<seq_packet_protocol> socket;

private:
  int family_;
  int protocol_;
};

} // namespace generic
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_GENERIC_SEQ_PACKET_PROTOCOL_HPP

/* seq_packet_protocol.hpp
6KW6VaHYKDnVJWVj1fvQcyGcs8n3oZZ6nWI6myGJenpBr6OtZVn0VOeEOulHGa/S77EL0E+r37PUbzj1GwiaivrNM+mHx9w4fcOLVvWrzjKlzEBll4RvKDapb1RV/HCl/9OjO9ZfO8cU9zKcy4r0EUb6pvwciTLZUjM/9Xb5QYMNkh/KpDjlh/HD/qn52d3LWj+TIdBkzQ/HKvnY1C4/lBnodG4u44d36dzciLjQzs3dHd0mvIx20LNAkyDQYsmP6g/6vKhvfM4J/1iXR33jo6WRGOwsXfL0U/ZaH0h4kgv/KpvIl72BM3Y7tolsz3vHZ+xO1MZTntNQxPwvBt2Om+T1MeW/UmxxdHlfz3xqvD71XcgGCS8Q3krw4q2Asi37jMT1sf1+uVbixsi3Gw2ol1zodiDwHUWvdpuQL2vfWpCnDjzPjwJP+KDAdxm9BoCH5QYbGBD5tTQbwf9CgD8my9XZbymM5bveUI77eB7B5ewXU1iOzaZyrPUXVpVucHwekX+gsXzog/oDiUtWev81BH87cUadcS97/9F8jmFMtz5ff47nQ1pflQ9tXmSe64vO10ieqrT8QC6052sfPl8hD52qDOcJHbfR6WfQKctJJ3xFVAkv5FBqDsZS6mU6s7tLem0z6FXUx3TuCvXKcdILBm3lxRVLajetC0zh7PSCbGjnrwTTq74vbQpAfUGrQX8MPENt9MK4Zi4u9luDXpSNUzbi6yS80OXhNwA51ucRZS5jGKcXSDie/G1nH+jPL9om8Zmq/x5CCVzVCZ/plaYxP8f0DFP1xpIdx76ayfJpti8fU7XZlg9kad+tyqJNSl8e5FH9tzq24/5rzpvPkDfewzTHmyD/4tms2Y6CzkHI65X8lY8vQZUXqiGpZl2183gEGfWMrpN8+f36PDFe5em+zI7zZDMmqTqrk3zhHlqeaIt4MtZqi/jDQF/zGmwRWW1iLCk6n7DaIUKm67aSJ2hnaNavJs6q3/vIUJGtfvI4Ff3eSLToRxndM68T+iE9W1vO3Hirfj9CXupt9aMhp8uxDCEX1JYT8V235TzRbcv5X2PLOUNsOccO8w3o/eDVn/3sh7+6bPidC9zdtpx6W062ecxT5T282DG8oP6WOa76m7Z43B+VOY/FFq+SNgh+YDjwGqAm1xBELp9yKym3SifXGERuDeWupNxHdLYSTZRLApltEK+l3HXACGAd0APcAYwFfhyYCLxep0dzED1qmF4t9diik2sJIncV5a6mXIVOrjWIXCHliihX3C6HDuQsV0K5UsptoFw2yEu5ZMqFAzMpdyNtST7B8tkJ7MewJp9F+SQb+aWUzwN6gcuACQxDHgii/HAbW6dhlB8OjAOOoPxI2iplAAcyPJhhpgtBZ9usTKY7hulewnSzmO5YYArDaQxr6TYF0TeV6Q5iumlMdwjTHQwcyPBghmnjzHW3lJHFxjme7TKB8v1oQzWAtlk+YBZtmqbTVmkW43MZpv5cG+OeZv1pg+YDTmb6U5juVCAI/Yi2p7T9y9H1u2ame7lNv5vNcpkHHEkbsNHAXKa/CDiFYbZnrNOc2/ODbM8PsT03KTlQELmbKbeLcp9ScrLOcbQ1/jLlvgJ062w0t4HyKPdRkNlmfDfbwa20xWpgO7gTmE5bzAzg7bRB+xwwG7iH9XgHcB5tSRfSlnQ15bV208z7j7NpN19juX+DetzN9ngf9TgITGV4CPAe4AjadmbyuhonaIM/0KafP8r7HGL6j7O9Pqaz/crxOtt+vaXjKwqRr74DvpYQbcm67ci67ci67cg6tiPLvrtztmTnYe+Vfr/blQuqAe0DHQWdBnkegN0YqAi0E3Q/6CToPCjtQdiNgdY=
*/