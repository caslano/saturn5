//
// ip/multicast.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_MULTICAST_HPP
#define BOOST_ASIO_IP_MULTICAST_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <boost/asio/ip/detail/socket_option.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {
namespace multicast {

/// Socket option to join a multicast group on a specified interface.
/**
 * Implements the IPPROTO_IP/IP_ADD_MEMBERSHIP socket option.
 *
 * @par Examples
 * Setting the option to join a multicast group:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::address multicast_address =
 *   boost::asio::ip::address::from_string("225.0.0.1");
 * boost::asio::ip::multicast::join_group option(multicast_address);
 * socket.set_option(option);
 * @endcode
 *
 * @par Concepts:
 * SettableSocketOption.
 */
#if defined(GENERATING_DOCUMENTATION)
typedef implementation_defined join_group;
#else
typedef boost::asio::ip::detail::socket_option::multicast_request<
  BOOST_ASIO_OS_DEF(IPPROTO_IP),
  BOOST_ASIO_OS_DEF(IP_ADD_MEMBERSHIP),
  BOOST_ASIO_OS_DEF(IPPROTO_IPV6),
  BOOST_ASIO_OS_DEF(IPV6_JOIN_GROUP)> join_group;
#endif

/// Socket option to leave a multicast group on a specified interface.
/**
 * Implements the IPPROTO_IP/IP_DROP_MEMBERSHIP socket option.
 *
 * @par Examples
 * Setting the option to leave a multicast group:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::address multicast_address =
 *   boost::asio::ip::address::from_string("225.0.0.1");
 * boost::asio::ip::multicast::leave_group option(multicast_address);
 * socket.set_option(option);
 * @endcode
 *
 * @par Concepts:
 * SettableSocketOption.
 */
#if defined(GENERATING_DOCUMENTATION)
typedef implementation_defined leave_group;
#else
typedef boost::asio::ip::detail::socket_option::multicast_request<
  BOOST_ASIO_OS_DEF(IPPROTO_IP),
  BOOST_ASIO_OS_DEF(IP_DROP_MEMBERSHIP),
  BOOST_ASIO_OS_DEF(IPPROTO_IPV6),
  BOOST_ASIO_OS_DEF(IPV6_LEAVE_GROUP)> leave_group;
#endif

/// Socket option for local interface to use for outgoing multicast packets.
/**
 * Implements the IPPROTO_IP/IP_MULTICAST_IF socket option.
 *
 * @par Examples
 * Setting the option:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::address_v4 local_interface =
 *   boost::asio::ip::address_v4::from_string("1.2.3.4");
 * boost::asio::ip::multicast::outbound_interface option(local_interface);
 * socket.set_option(option);
 * @endcode
 *
 * @par Concepts:
 * SettableSocketOption.
 */
#if defined(GENERATING_DOCUMENTATION)
typedef implementation_defined outbound_interface;
#else
typedef boost::asio::ip::detail::socket_option::network_interface<
  BOOST_ASIO_OS_DEF(IPPROTO_IP),
  BOOST_ASIO_OS_DEF(IP_MULTICAST_IF),
  BOOST_ASIO_OS_DEF(IPPROTO_IPV6),
  BOOST_ASIO_OS_DEF(IPV6_MULTICAST_IF)> outbound_interface;
#endif

/// Socket option for time-to-live associated with outgoing multicast packets.
/**
 * Implements the IPPROTO_IP/IP_MULTICAST_TTL socket option.
 *
 * @par Examples
 * Setting the option:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::multicast::hops option(4);
 * socket.set_option(option);
 * @endcode
 *
 * @par
 * Getting the current option value:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::multicast::hops option;
 * socket.get_option(option);
 * int ttl = option.value();
 * @endcode
 *
 * @par Concepts:
 * GettableSocketOption, SettableSocketOption.
 */
#if defined(GENERATING_DOCUMENTATION)
typedef implementation_defined hops;
#else
typedef boost::asio::ip::detail::socket_option::multicast_hops<
  BOOST_ASIO_OS_DEF(IPPROTO_IP),
  BOOST_ASIO_OS_DEF(IP_MULTICAST_TTL),
  BOOST_ASIO_OS_DEF(IPPROTO_IPV6),
  BOOST_ASIO_OS_DEF(IPV6_MULTICAST_HOPS)> hops;
#endif

/// Socket option determining whether outgoing multicast packets will be
/// received on the same socket if it is a member of the multicast group.
/**
 * Implements the IPPROTO_IP/IP_MULTICAST_LOOP socket option.
 *
 * @par Examples
 * Setting the option:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::multicast::enable_loopback option(true);
 * socket.set_option(option);
 * @endcode
 *
 * @par
 * Getting the current option value:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::multicast::enable_loopback option;
 * socket.get_option(option);
 * bool is_set = option.value();
 * @endcode
 *
 * @par Concepts:
 * GettableSocketOption, SettableSocketOption.
 */
#if defined(GENERATING_DOCUMENTATION)
typedef implementation_defined enable_loopback;
#else
typedef boost::asio::ip::detail::socket_option::multicast_enable_loopback<
  BOOST_ASIO_OS_DEF(IPPROTO_IP),
  BOOST_ASIO_OS_DEF(IP_MULTICAST_LOOP),
  BOOST_ASIO_OS_DEF(IPPROTO_IPV6),
  BOOST_ASIO_OS_DEF(IPV6_MULTICAST_LOOP)> enable_loopback;
#endif

} // namespace multicast
} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_MULTICAST_HPP

/* multicast.hpp
SMmddrpDbuEt0uv4Dqpws+U3Yn7Wj/xGLOlLImspeF5r+2UtdZJmOPiSStOowvU6j0khGTJNntqa9prImr9fq/i1KrxGpx8n8T6jYrwZzrbIpNakIENFgHE/TxYe/plrAavlN/Cgdd+X5DVLPSvT9dmDlZaVoel1nUfUczfotROvIf9G6O/mOvU49v+Ez0xA91Knci6i/n08pN9c7lXpe6JT4V8PojfuK72pe9U6rakLu508LgtyX4LGQd+FBpF/5/jYdrJ64TIvOxHeUq3Hz6rw51T6/ADpLXpbrtNP02s396twt6fd1GueySrcRPheFX7EaTdiq3ep+AfEbsL8E2LZCWn6thOz3r+o0t2q9jzsMX/3RadvUOfJ29m/O4n1pBnpkT0LyHYYMtt42E7+MSVkJ2+CZ0yMaSfLwnsw507Q6z9j2g365h76Psl2Y6TLb5piN7dDAfLvnhDbbtp3tnvaDby6Ts8n/JwKX48s4fVnyCwLw8O6f0alaRFbCj9jgsT7jFUTzXCqpZ5VoVV8LuFDpOee2FWYf6ZKn6Ly3HxZe12bts1fqfgrxI7C6ctj2RFpbHbk7D+knRxW6S6x2FmTUpBeN67Kku4oWwF2lGraUSBkRz87wT4n13YWa0TnWTb7UXrUtpOi0ipdedmOXrfpH8R/Ej8MajCR/LsmutmO2lViGqXoxWE3wjda7x09psKDvdYuSfpiCev0rv1NFmnywIdUmrcbq/hfbIXnRNZIJafZ+hxsw5oP4Yhcyg7Wix1khU6Uab+4JXL2zzdVuiVYFWUw72neAcpnSKHt7WIdUg3OSHIuW+r8qYba+8u9Tshn7rfzj3DsVbLuSX1XIL49qWH7QO8e7yR0G0ffgn6kb7H3I/eILfgl0wzozXLym+RpC82hHXKGlz0Ir7/P/Sqy7tRSNrud7slw+nyvoKwqb9nMUnvJJXyFXnYp8RNUHe9HL4syzLrsn19oLZNzjZ29nM8Olt9VkXE0uB4cavoAruXkLOXymO1R+MpU+DzC3So8z2dtX2IgUvYwT4n2Cz+twgt8bu/zKp3HVBVeR/h+SR/dD8vZI5J+kvYX7lHhoE5PazIF0u+FO1X8WSo+qLTURhuNvHc+JWWyt+FIX36Hil/hM9vlDdRjHjo+Sjq//0q9B3+9tMvZhP1yBtcaaZdPQBdCz0PF3LsKeo/EjQOfj6Ptmn7CHZPtfkK13Tb0WQvoQO5F+vUWF59gZwyf4OCQUObrpV9fCfnNM26meNmRZ1vWfWGD4p1rTIucOSXPy/fyJyU+V+933arCC3ir+6L8sPjXMzvak823su/fPCS9Ti9UKLibhtUT0UMNH4errS3fZD5QrfcvzLet95e043UZXlTh+1kz53Ntd8s1z1i9N/gFFf4M6xgyFM8j8GDHtnPmfqvS3GuOc7kXem660VR3aUg0vbc9dWrojIAJ/MtiS9JwUdIvTX7uFah7Pu6E076Lu4yijWz1bjqEbYw0/V6zP0tfq99N5KfaQDhNkDRzJpImo3NvpJ3Y09SSZok6R+Uy/Zw/SRo5H4t2EvKlZ0+Mr53UTbW0E8KDIuEZhuVsBupJn2VSGePdcUDpGjmkLayR/S+9U11tIDz0ttqCrqPfK55SIy/SBuQ5BV5jb4kf7+r31vt0vKufu8Ya7+3Xksbp1z7iMj7Knyb+mPZrxbbEto+p55xmDOX/cP29jv9amdfneIj6c9SNc8x8En3XdbI3+zkZ9zwCXTfaXKfuXq8yVHZr48JTqscW71Hh2+39mqWtXqHiP2I9d0OeMU37iUNKvMc79ZLeOm6+TIU/67QD6UMuUfGfFLsw+fseN1dNi88uXlfpBjlkN88C6CE=
*/