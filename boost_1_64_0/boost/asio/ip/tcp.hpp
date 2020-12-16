//
// ip/tcp.hpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_TCP_HPP
#define BOOST_ASIO_IP_TCP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/basic_socket_acceptor.hpp>
#include <boost/asio/basic_socket_iostream.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/detail/socket_option.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
#include <boost/asio/ip/basic_resolver.hpp>
#include <boost/asio/ip/basic_resolver_iterator.hpp>
#include <boost/asio/ip/basic_resolver_query.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Encapsulates the flags needed for TCP.
/**
 * The boost::asio::ip::tcp class contains flags necessary for TCP sockets.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Protocol, InternetProtocol.
 */
class tcp
{
public:
  /// The type of a TCP endpoint.
  typedef basic_endpoint<tcp> endpoint;

  /// Construct to represent the IPv4 TCP protocol.
  static tcp v4() BOOST_ASIO_NOEXCEPT
  {
    return tcp(BOOST_ASIO_OS_DEF(AF_INET));
  }

  /// Construct to represent the IPv6 TCP protocol.
  static tcp v6() BOOST_ASIO_NOEXCEPT
  {
    return tcp(BOOST_ASIO_OS_DEF(AF_INET6));
  }

  /// Obtain an identifier for the type of the protocol.
  int type() const BOOST_ASIO_NOEXCEPT
  {
    return BOOST_ASIO_OS_DEF(SOCK_STREAM);
  }

  /// Obtain an identifier for the protocol.
  int protocol() const BOOST_ASIO_NOEXCEPT
  {
    return BOOST_ASIO_OS_DEF(IPPROTO_TCP);
  }

  /// Obtain an identifier for the protocol family.
  int family() const BOOST_ASIO_NOEXCEPT
  {
    return family_;
  }

  /// The TCP socket type.
  typedef basic_stream_socket<tcp> socket;

  /// The TCP acceptor type.
  typedef basic_socket_acceptor<tcp> acceptor;

  /// The TCP resolver type.
  typedef basic_resolver<tcp> resolver;

#if !defined(BOOST_ASIO_NO_IOSTREAM)
  /// The TCP iostream type.
  typedef basic_socket_iostream<tcp> iostream;
#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

  /// Socket option for disabling the Nagle algorithm.
  /**
   * Implements the IPPROTO_TCP/TCP_NODELAY socket option.
   *
   * @par Examples
   * Setting the option:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::ip::tcp::no_delay option(true);
   * socket.set_option(option);
   * @endcode
   *
   * @par
   * Getting the current option value:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::ip::tcp::no_delay option;
   * socket.get_option(option);
   * bool is_set = option.value();
   * @endcode
   *
   * @par Concepts:
   * Socket_Option, Boolean_Socket_Option.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined no_delay;
#else
  typedef boost::asio::detail::socket_option::boolean<
    BOOST_ASIO_OS_DEF(IPPROTO_TCP), BOOST_ASIO_OS_DEF(TCP_NODELAY)> no_delay;
#endif

  /// Compare two protocols for equality.
  friend bool operator==(const tcp& p1, const tcp& p2)
  {
    return p1.family_ == p2.family_;
  }

  /// Compare two protocols for inequality.
  friend bool operator!=(const tcp& p1, const tcp& p2)
  {
    return p1.family_ != p2.family_;
  }

private:
  // Construct with a specific family.
  explicit tcp(int protocol_family) BOOST_ASIO_NOEXCEPT
    : family_(protocol_family)
  {
  }

  int family_;
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_TCP_HPP

/* tcp.hpp
xp3BV7+JrnLX+25fOtdqOR1I9a0jWlkR0DXMaiS6lC6/ruF0Sc+csLqYnySoLmYNPRFd51TPf6FrIFnw6XbyXV/ia6gyrEgr5/upaz5fipNFhpoVt/Nce5CzdQtWm7jqe8LqZ+r5Vkh6st1h4o6of9lT4r2R78BFEXUl/5pYU1dyVplTv/Eh8W/lfdoTWCdT1642cXzRUNZnVTvar2KPccRZUObUY68n/rFG37eB2M/Rtb7xkbztdtWzVrjudxFPoPxLnHprnzfw1afOPdFyrOfpglulq4NjLstMU465cq6HOZdtr+1cum+otsNP7bhpa7W0v1AdV9XXe09kexAWuwnr8rTB7ULXTAkbH1gX3JTTlw20nPRadUvam7jCXaMm3TX21PtA4uhGGWE3ZRTnaYfbz12HJNw455q7Wid32uWi7Xa4abfZrja4heyZp+ndLjIJhDFlOK+ksmRaQWlAL+dZkWkVVldW5z+E1ZHNhJdKfifIfhGXcL73Y1lry54DE7esEfNy/sysmfBzZlS+aT3uQTJnZllmoqdV6DrmKtcXuattuUZXxvplxqvMi9h7OvRzX1MdWL85gN3o3arb67hlNQno0b6hYWLSVW9W7ejUyu9DmDM7+XSF/qR+hGUNN+LUOJSyDtyfHWlYfKpP9iJo2y9WPtwSPQlN12HVzZ1cB73cFPRyP5J2Z7W3VyaeQ5dqqb7uDUl109cta3Zi+rqZRl9X+iSdXxFeDzczVA/X3GvzdF+7uzCpmJsxb3WnTpKD7rV10tH0haHU9J5yodgX0nvF6rNE8P4dF4h/uXWW9o8jTBxpEfVjnxP/xk59WKNHOUf8KmT/LLtdvx3HdVCfdaKo08TG8xPdROB8bpH1/bHHhOjOnrzerNZr0Jqkn8aH6l+9ZeuZNAlakzR74tjskWOGjxrpXA92f7cQHSzCnbiOGPGFXSd3f0JoGh/tzWNkpDSWl5Xrer76bFEznRpW5wBsTJZ2Q4Ci+XOmGX1II2P6lOPIC+fUvASuA86DmzlPUD1sSwzN4wHKIy9CHlUVLlI9EK5WXTj8T1wXbn+3uunC7Yvqwv3H6sIlDcS4Em66YHpsq390uaJBUePJr6x6NqoLdyxduL9bUqYcvmcO+11qjMVzjeP3Psdv+nnRY3ia36qbwftqZN2Mp1Q342nVzXgGNhe76ma49Z1L30UJL2veFaqOUydde643zIVnqA5JX3gx7Ke6ImfpGqNnw7thFnxGdaD2qA7UQTgM/gXmwAb2uWA3+EMo76eqmzQGzoXj4HWq+3Sz6j7dp7pPT6rO06vwQvgmzIdfwQKYQB5mwBRYAnvDUpgFZ8MLYZnqKE2Di2E5vB4uhFtVx+lB1XH6LbwYfgiXqK7SZTAJXgnT4XJ4ttqHwJVwJrwOXg5/Aq+B18NbVadpPVwKt8DL4b3wCrgDltv5g7fCv6iu0xF4m+o03Q4bUeF3wEx4F+wP74a5ah+l9snwHlioOlBlcBNcCDerTtPP4TbViXoGboV/VJ2oj/U8sbSTX8Jm8FewFdwJu8GH4BC4GxbCalgMH4Wz4eMBnSB9DiKNYXSCUnSNwpawl+oynQdbwTGwHZwGW8P5sI2u5ZkOr1L7NWrXZ07VodFnCr03FtfQoRnjkMuso1zeMeS2f8c6Of8P+jjfhy7Od6GH813o4Pw36d98H7o3Ub2bk9O72XA6ujaYwxhvH6+VgRnbJ6pnEz2iR/SIHtEjevwvHd/P+P+0eaXf0vj/s47x/7c9lhyzeORqBifBr7vzo17gW/7g0bnHXP8vTeQH6/p//vBp8s09JjlozFz9Us04cqrYp7sirfeSDzuJzBC3jAn49sQ24/PPxkk=
*/