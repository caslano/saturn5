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
gnaBDoPOgBIfcrvmgMpAu0FND3Xbk3X/un/dv+5f96/71/3r/nX/un/dv+5f96/7p37/Zvv/wi3+TRfD/j/Z5Yl9GhuR/ncCPmBKSjcU11bgsLvidRWlEnc0u+3jfzfsuauKNzHGJd8NbMnEvbWzrGifP1Lnl/47kG35s5wwjFPzCtdVlxZXrS9jEnzn/AOxNYDrfvXOmTL0yXNC4tehJGiLYIznO2mYAajznlS8eie9iO+kszs4/zEHCH3w/hn66M4PPCHXRAfTGdK4r8nmJMfNd2m0s5sLOoYbp30Yr2xOVs1dvmDemsK8mctnLg6cL55V6K+sKF+/3VgmUt7K7nCGyGe6+im7Qy1N5IznLkKG6bCsFM8AZc8zVcLTsd8cJvZ358La3nX+HRXm8UxWZVZAWzmNpxU8fw3wRKQpnndDtKfj+36WreRL2bf0lmvU22Rr3UBDsGdo3/QU6FkINQQtS2lelnJkmVE2Tp2j+TUJP4h2G6Zk0BtqNvnbz7/+o/BcpvflomwgEoBvSvxaKc85qP+UcLwTzURZxaeqslqp+SshzxzwXCf+UaZ5eka5FN9S8mlp7QVfXYAvpv6Avm6gC/qm0V5jPiKfZP40n1CT/hIIxxjufRRp7gik2ad+l6dnvMt8ZnUy+VrBVzoafX9DzFycfdgvSmdz+XHIF3uNeUpEfV0vdpx5nqg+LpsztleIzndPw8VIw3ii9B8PfcVHFevrHslPFt7/9O/QPsymnRna08FIniXAMcoX4A20p784t6dxhWWV1ah0h/ZE2UE8S9Bi28x4n/TRoS4tvv08wTzF014PN3TCtkqfV9rQ8LxB0UOdV4t785rVj2NdT+XrTn7RoAcmoZ04lcv6CozkhRsqijfCosyxbCgfI/FDJO8iQtshLb5HhzaQ/CbDkteA0BDJl6Rr9EtHe/yJoHjiO4hpdsrThqrSUru8cPx9m/XMvDEdH8NosecRxn/G/hH6ucO6vBnycZ75mMo2Ox50MvA8OW+fDzFABY/eXovnimJMoRxSSUGPCvTb+Uj/GEj6bc/RnoiYzp3Trtlrmcfuvb2sNrM/hN7+YHrTXxWf+5b2BNmQbGa19nLCWKaqvWdHW+2MX4Nu9UF185eWVol+ju0d8iHZGqv27KDf69HWsvtRYJwKol9hcW1NWWFF6ZbSCsfya7jA8lN+qDhQZLFNjgZNgfFEYzD96D1APUN1c7ZY4DMsu8Bz7xTyX4R77Aq0yYikdvvNEJ4j2nPjkKSXAtmoDsdSq79Ba9m3BMtbSam/psy53bZcpHI/a6PbG9CtNZhuMjQ6t9nWTurm1GZ397bq9ma2fLzgrFv55jLq51R2kO+cfk5ll9HH2udPQT9vMP1qytHdHXWDbOf6u5NuiZR+C2nGB/iA+yZhrHbSDeUGg/Aaw7MXazfMU9R6YbLIfjusr369INeSdPmprlqv1goSb/DrMFHCz4X1lxmlPMPxa6+0PnymLBO+ZpQDwvhrhoSPhnlxKlx02GxXZVhv1x1hsdK3M1EP0zCZ/1Yq+rb3hnStb69i39Z49oLnszKHvmGuxvOrjLb87gBabKn/Fq/5xkEYp21LeCvsyXrD/inWkPYRpH1LIO1+N+zQ0r4VYb1/qwaEb+vE+fRt/YJ1gGvZqr6ljA3P9P20ca/i+HkVKB8C9X93qO+Kysqra/3WOSbzDjlVr9dNlPVLYGgVv0zQzXbdEgs8KHLxDMNrroR7Sz2l4D6nQVsD5TRitm4tzXoiTxTC18taYox5vq94MmO51olOVTxLQxjLtfx9UfTqK3VxsIO6aDLOf1X9oFxwzW/5RuQl2vNvBCXyG5q3A+OCK8G+LjZVbim1nQs=
*/