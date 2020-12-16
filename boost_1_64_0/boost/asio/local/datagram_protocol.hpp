//
// local/datagram_protocol.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_LOCAL_DATAGRAM_PROTOCOL_HPP
#define BOOST_ASIO_LOCAL_DATAGRAM_PROTOCOL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_LOCAL_SOCKETS) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/basic_datagram_socket.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/local/basic_endpoint.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace local {

/// Encapsulates the flags needed for datagram-oriented UNIX sockets.
/**
 * The boost::asio::local::datagram_protocol class contains flags necessary for
 * datagram-oriented UNIX domain sockets.
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
  /// Obtain an identifier for the type of the protocol.
  int type() const BOOST_ASIO_NOEXCEPT
  {
    return SOCK_DGRAM;
  }

  /// Obtain an identifier for the protocol.
  int protocol() const BOOST_ASIO_NOEXCEPT
  {
    return 0;
  }

  /// Obtain an identifier for the protocol family.
  int family() const BOOST_ASIO_NOEXCEPT
  {
    return AF_UNIX;
  }

  /// The type of a UNIX domain endpoint.
  typedef basic_endpoint<datagram_protocol> endpoint;

  /// The UNIX domain socket type.
  typedef basic_datagram_socket<datagram_protocol> socket;
};

} // namespace local
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_LOCAL_DATAGRAM_PROTOCOL_HPP

/* datagram_protocol.hpp
LvBR2BU+DnvAl2BP+CHsBT+BvaGdtsGwDxwCx8GhUMYXYDEcBsvgALgRDtd8KbN0zaxNzZcU/pyv+f+Mtj/Pwr7wOTgIPg/z4G54AnwBFsMXYSl8FdbCl+EHatfr6ZpAWa8ZcT36DLnf7+v1PtTr/QlOhgfgNPgRXAw/huXwM7gKfgp/rnY9z0fXw1H29HrO83ymImdzGmyndj88Sa9/MhwD8zW9p8DT4AzVTzhdj8a9V/3O81Ee1XNVHoOJ8NewBfwNTIZPwDSxh/q53aovMUo/9wvV90uYAH+l4VZi9mu4DRouDVZouKt8gfv4fdgFrtdyfg0cB38Ex8PrtV79EM5R/xr1P0/916j9BrVrPuj6J8p+lHx4VuP9W9gS7oat4B7YGr4I09Wu+li75J2vr6i+vZqv+zRf39R8fQ2mqd08Pzzina+Xan99GUyAl8NgP39Qww2M0s930XR0hZ1gN9gH9oAaXtfoUMejhM/Q8O1gW9gedhB7KN4FGj4hSrx3aD48COPhTke4Is9wUMP10XB9Hfle9aj3fTyg4T7S+3hQ8/mQpuNTmK52c95YA/p+r/r+oPr+qPo+gPJOqfqwm3RtVX3xUdJ1n+rbDuPg/dDU00e9y9NtGm6DlqfbNT6bYArcCNPUbspnA/quVX3Xqb4fqb4bVN/1qg+70be/AX2XqL51qu9S1Xe56rtM9WE3+g42oO8u1Xe36tui+raqvntgmtpVH42Yt74bVd9Nqu9m1Vev+n6q+rAbfekN6LtK9X1f9a1XfVervh/ANLWb52nVlx7lebpK9S1XfStUXzVMheepvlrYRu3m/aEBvQtU79mqt1D1FqneYtW7SPViN3qLGtB7kuo9WfXmq95TVG+B6p2perEbvXUN6L1A9X5X9dap3jWqd63qvQi2Ubt5X2xA7xLVW6Z6y1XvOap3qeqtUL3YQ++LDeido3pPU72nq94zVO+Zqnee6sVu2t39qjczSrvbQd8X/bAN7AjbqV3fA3TOMc/2Ud4DsvQ5oTMcBLvCXNgNzoDdYQEcAc+CPWEJ7AXLYW94CewDb4R94c0qfwccALfAgfAZmAOfg0Pg23AofA/m6vPVcHhAw38KM83cXpkvLPHPDjynyu8OfR7YAkfCe+CxcCs8Dt4LJ8Pt8FR4PyyCO+ByuBNep/bb4ePwXvgE/BV8Gj4J98HfwDfgM/CX8EX4K32e3QVfgS/Cd+Hv9Ll2jz7X2u494OuwP9wHB8E34GC4F46B78J8+AGcCQ/A0+FH8Dz4MbwM/tmMJ+gcV5gcpR/pqOUuE7aAnULlivmk3v15K+23Wmt/3gZ2EHsofJ2GbxEl/AC97kAYDwfBJNtfw2ebeY4yJ1PC95D3Cp1rj1xveBj2VftQtU+Hf4enqP1UeAQuhb3jySfYB94EB8B6OBBuhYPgo3Ao3KPur6t9P8yFH8Fh8FOYA/8JB8MEO29hN5gI5bxJOAGmwGKYCq+DreBPYBt4K2wLt8L2cBvMhA/BTvAt2BUegGPhx/AYGOhfdJ4f7OJxbiGQ95I4+Jq2B6/DjnAf7AzfcLxHFKi+sVHeI07VdmQW7ARnw55wDuwHT4MD4TxtJ+bC4WIPvRfVq/4ro7wXjVb9Y2AmHAtz4DFwGDwWToXj4QI4AVbDyfAiOAWuU/un8n6l85tgrbYPWZLuwO8a5HrBG2B/+GN4InwQToc79To/gUvgjfBi9b8S3gzr4U/hvbAevqDur8Lbod0WbYZt4R2wL3wADoEPwmPhTngS/BmcAe+Gp8I74WnwLjhP3UvgvbAM3ger4IOa3nVmvgf3WPO3NVyt6S3U984iOAAugkNgMcyHy+A8WAKLYSksg4vh99Q=
*/