//
// generic/datagram_protocol.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_GENERIC_DATAGRAM_PROTOCOL_HPP
#define BOOST_ASIO_GENERIC_DATAGRAM_PROTOCOL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <typeinfo>
#include <boost/asio/basic_datagram_socket.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/throw_exception.hpp>
#include <boost/asio/generic/basic_endpoint.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace generic {

/// Encapsulates the flags needed for a generic datagram-oriented socket.
/**
 * The boost::asio::generic::datagram_protocol class contains flags necessary
 * for datagram-oriented sockets of any address family and protocol.
 *
 * @par Examples
 * Constructing using a native address family and socket protocol:
 * @code datagram_protocol p(AF_INET, IPPROTO_UDP); @endcode
 * Constructing from a specific protocol type:
 * @code datagram_protocol p(boost::asio::ip::udp::v4()); @endcode
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Safe.
 *
 * @par Concepts:
 * Protocol.
 */
class datagram_protocol
{
public:
  /// Construct a protocol object for a specific address family and protocol.
  datagram_protocol(int address_family, int socket_protocol)
    : family_(address_family),
      protocol_(socket_protocol)
  {
  }

  /// Construct a generic protocol object from a specific protocol.
  /**
   * @throws @c bad_cast Thrown if the source protocol is not datagram-oriented.
   */
  template <typename Protocol>
  datagram_protocol(const Protocol& source_protocol)
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
    return BOOST_ASIO_OS_DEF(SOCK_DGRAM);
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
  friend bool operator==(const datagram_protocol& p1,
      const datagram_protocol& p2)
  {
    return p1.family_ == p2.family_ && p1.protocol_ == p2.protocol_;
  }

  /// Compare two protocols for inequality.
  friend bool operator!=(const datagram_protocol& p1,
      const datagram_protocol& p2)
  {
    return !(p1 == p2);
  }

  /// The type of an endpoint.
  typedef basic_endpoint<datagram_protocol> endpoint;

  /// The generic socket type.
  typedef basic_datagram_socket<datagram_protocol> socket;

private:
  int family_;
  int protocol_;
};

} // namespace generic
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_GENERIC_DATAGRAM_PROTOCOL_HPP

/* datagram_protocol.hpp
HoXOx4++nV/8PQn2B0s7LwrSzl2J1rE0bjLqKjFYO8fGRZCxdGGiZSxlesm2exeLJD7oWIr4oGMp4jseS7MSQx9LsxJDH0uzEkMbS29MDD6WFiRax9JHL9JYerH2Ljozlmpr48ZknpHPNvYq6AsouCZzGyvBXj92xqSZOY+jlEtU37gdl/Ax10bcdZNrEccyeN1Lkm9HLPXM5zfTGckwNBH+3uZ5sur/54Tfbx0fOJ7HiHypfg6txuEkiVur+y5LLAerSreg/LiXP1Z4JiAX4dzfV3kwrqXZnp4Vfb7jeswVKfPWcPTlhiQ1j7zZMq8jzyGNJ6rGZeZJJk9LEueR7pWeiEhPDw941FzSxOtB/T6ZCewxw+OO9kREedxRGm/fZOO9s5K1+elgc3qKJz9Z5aHRrN+FjLOqzZraZ/4Al/zE3wNt7W9EATcnGdsnx7/1lbWb1b5tvzhr+2xmnfmg9X7kJWWAVpZJnoiezEeIPjyRvq39405+VLWEfWp24FqgUSQbdZadOdHbUV/KJKpxKFHCl2HlGeHUdyjTT7XFfhK+FF8pRku+C5DnhBTWY8QYT0Rf1jHjslO0djCwvR10XMcLjWXTcR1rz7mzA+nnheU1A+QL2IvalVf55pLSbc5rBpYbZI17ITdJeDzG6TCnNQNl0iCjyrW4usZfWa3bC/hUMvck+PwsU/dKMu+Xq7O4GiR+jJzFJXMTvjs7coFzE/0c3GeYm1BvUzmfG8Tz8EEJxMTA2syxnDueN7fJznDak2J8ssvHd1W/lvDN6Ms9XXWgYGU9YIDs9+DboViWtZZef+HZjPCvJDwB6Yc57qHESDobXLnGPRTuheAdssTnu+ZYn/9qH3OK8MTIHmgr2mvJIG3cmBoYVHtgW9Q6ZpJ31yBtzCyyjOlauC6243dpoc5TQ2kLjYNd8isCJdLGMnkyrg+waQs1pdtqVJdzbAuUHaDK/SkJT4V9Z6Rjn4OMeifuj5S5Y+0G3bzruxKfjRE7jPvhmsxQ63yS7eZpib8UrSRGZMqVTKpjHz3O+0S5vIY++vRF7KPaHBD5xDXkU+2nOu8t1wxru9FboGHEFNRTWkqQekKXDVJPlB2n9tyWSfgBVwHu69CPKXOJyOQjvETCTThVoIe17tjXFwnPo/BLGM+609IZbXumQrmKz5A0NiE8X8KPu9a7wo37jOy7pyR+CMNhrtsR1uaVM5GPKJe8ylFr6FclPpNhjb8v7jcbczr6w5NrvV0+uQYh/Pxy7RZ5gypzB/SfAmw+TMc93PX3YOEaHiF7fYw7grgpEve5yEhPtCcO19fi2h4Q509fNY8FGs/hodrzt/5z5jElQKN4DzQIeYa4x0VGuSNihsZkxIzHy5jIHjGjY0ZFRngi8VzXjS9Bx9qNkr+bUfJpaq1+q1yLsh1XVyPRNRL/DZzJDxm5pskk2o6zpRK31TWK/InqHoMcx91rJT5GyvwoyuX1dK1sJmML1WbMJd/5dK2c8yxjbqhz1TybPl1gsydQZNOny6x9Wn17nzbc/tv7nIGhf3sP3qDf3s8aeGHf3s+iru9TVx+oNylhMvLbpmv11YWm11tcKIJNtZswthvqTln1LMbf5ep5oOLUGoXf83SQhywg7oU88F6G8bfckKfwDGueYpCnBsc8lW+uxnmyQfJEWZ/ufZ5f1dciUzzzXLKN8WXt8bp3EF3LN587fGcHHSz7VrivtsZieRy0KY8nJmEN7lgem2s3sSzyJlrKgnI+Xd8MPS9Ij3kx6lg/0qrjU9Cx2VHHLcUVtaWOOjY71gffH5jysLiLeZD60Jd993dl/1HflUVPC1zPLHjg2I7t/s1hf/1lSfF3v13b/V2Z/mw=
*/