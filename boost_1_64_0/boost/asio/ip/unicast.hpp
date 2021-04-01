//
// ip/unicast.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_UNICAST_HPP
#define BOOST_ASIO_IP_UNICAST_HPP

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
namespace unicast {

/// Socket option for time-to-live associated with outgoing unicast packets.
/**
 * Implements the IPPROTO_IP/IP_UNICAST_TTL socket option.
 *
 * @par Examples
 * Setting the option:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::unicast::hops option(4);
 * socket.set_option(option);
 * @endcode
 *
 * @par
 * Getting the current option value:
 * @code
 * boost::asio::ip::udp::socket socket(my_context);
 * ...
 * boost::asio::ip::unicast::hops option;
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
typedef boost::asio::ip::detail::socket_option::unicast_hops<
  BOOST_ASIO_OS_DEF(IPPROTO_IP),
  BOOST_ASIO_OS_DEF(IP_TTL),
  BOOST_ASIO_OS_DEF(IPPROTO_IPV6),
  BOOST_ASIO_OS_DEF(IPV6_UNICAST_HOPS)> hops;
#endif

} // namespace unicast
} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_UNICAST_HPP

/* unicast.hpp
Jt2C2/VTBaBQ9NTFIa+yNQzGE0NxpcSgCx1XVFblchLv6BzrestuxXdMlXmUThSmbJbLUmcCbeo7t1rvMyrjPkLExxof45EwxjTDXzJMX2fzWtrRgcp2bv5hKpcjiCDDL+OG9zAMtYMmzTzbI82TzY5xwmGeNDQ47ZLdKbRgQSVrjy+ihcCJssFjUn6tC45Z44vltnxwv/kQIIgDW9inVFMQb8v4KKU2Skc6HP5GtpuZxXbyXqBjMCnlkaZ4GVv9/uHcDteodq4EvX2JL/14B+s/SMln/VxcEAqf+1B3ZZFZL8bJzTrSSgnU+vVM02W3gSklhtI1kNXP8ZEgZkmAmedQ4krSE4dWy63OsPQQoYrU+Ys78D48KBspswQpnXcVofwCUUogBlwF91R1RhbgdlfA7e/VTVqhy4G+rqgl2l4fc1nlUx5EgayD3pubmwtuZ+Gpl2eRKL4SN2XHeezJiOJYTXWTGe6KiYs9Vh9VtjM1VSFzkcTSBpRKmlkEV7+lPUFLqDs8wgTkvSHcwliqIwCcgEFy8EHMpL7CkPyLKDNbHXAkfxxE9Sbgiw==
*/