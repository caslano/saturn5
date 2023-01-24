//
// generic/stream_protocol.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_GENERIC_STREAM_PROTOCOL_HPP
#define BOOST_ASIO_GENERIC_STREAM_PROTOCOL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <typeinfo>
#include <boost/asio/basic_socket_iostream.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/throw_exception.hpp>
#include <boost/asio/generic/basic_endpoint.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace generic {

/// Encapsulates the flags needed for a generic stream-oriented socket.
/**
 * The boost::asio::generic::stream_protocol class contains flags necessary for
 * stream-oriented sockets of any address family and protocol.
 *
 * @par Examples
 * Constructing using a native address family and socket protocol:
 * @code stream_protocol p(AF_INET, IPPROTO_TCP); @endcode
 * Constructing from a specific protocol type:
 * @code stream_protocol p(boost::asio::ip::tcp::v4()); @endcode
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Protocol.
 */
class stream_protocol
{
public:
  /// Construct a protocol object for a specific address family and protocol.
  stream_protocol(int address_family, int socket_protocol)
    : family_(address_family),
      protocol_(socket_protocol)
  {
  }

  /// Construct a generic protocol object from a specific protocol.
  /**
   * @throws @c bad_cast Thrown if the source protocol is not stream-oriented.
   */
  template <typename Protocol>
  stream_protocol(const Protocol& source_protocol)
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
    return BOOST_ASIO_OS_DEF(SOCK_STREAM);
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
  friend bool operator==(const stream_protocol& p1, const stream_protocol& p2)
  {
    return p1.family_ == p2.family_ && p1.protocol_ == p2.protocol_;
  }

  /// Compare two protocols for inequality.
  friend bool operator!=(const stream_protocol& p1, const stream_protocol& p2)
  {
    return !(p1 == p2);
  }

  /// The type of an endpoint.
  typedef basic_endpoint<stream_protocol> endpoint;

  /// The generic socket type.
  typedef basic_stream_socket<stream_protocol> socket;

#if !defined(BOOST_ASIO_NO_IOSTREAM)
  /// The generic socket iostream type.
  typedef basic_socket_iostream<stream_protocol> iostream;
#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

private:
  int family_;
  int protocol_;
};

} // namespace generic
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_GENERIC_STREAM_PROTOCOL_HPP

/* stream_protocol.hpp
TfeUME03VMQ5X1iNo8T3rYjTsMfXs2C3eHwVbbQLj71/JRcfwv5IMv0d/cMFeIn+fWG1DaOUyacljPGJ62+sNQzrhq+Q9KzGd0l+id6FqmyIUL69XAZlwhgD/lRk8H15nA38TYzBAtkUvLKX833j+O3445lORehfOz7pjpd58VJveMpllDKreAlhM+yUjSo7ByWThlfyInxxbjSeAOtY18RWWfyRC1y+cNb7WrTmO9nrdxYbFHp9M0YhUye44c9nijvABzf2ZJRjklgTxB6DLyMW91hb0yy+m9Sz6Ys4Cs+PX7irc9k7Px2TiCYECw8Jfy5w1eWz6XMXfdqnc1/GSMWdXbRLzf8lFnywhkEtYLUce3Gn2kF51M2aXvrG47HB2djnRdWLTexLcBRoYLaiuL6Wuql9QViP4t6EOm9RfGCa+Hspvq3ibnEJRcUOCUv8n9ruUPayYpI7VCNR33/Haq8izqxXjpk4dk3dMtbhT+xsTFEy7bKUbIpvOUXJofyqb1iMxqkyez2seKoQTxLvx/9gTeq3s/PGMla1gm8LKtITH3fgrO9RJfid64AVX99kxOXfE4zI95UyZBbAeppI/E0S9l6APzOSOJk6VpW2Ex88yMcxl2HhbPafuclenpTqrznqfzE97bKSo95vaWtvDxSKxTd83OAiPiPhW4FHFE5tSFy5Sv+4aPaDJkJsdYqFXz08TYknS6xdEl/Q
*/