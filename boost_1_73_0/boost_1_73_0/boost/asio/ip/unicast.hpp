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
Io/UptjUt30HV1BLAwQKAAAACAAtZ0pSueWd0IgAAAC/AAAAKAAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3BhcmFsbGVsLmRVVAUAAbZIJGBtjbEKwkAQBfv9ivcDCVYRrhMbCwXBLt2S2ySHl9uwtyn8e4MINpYDw8xjVvOAnq5apoCVjXOWTBfJa8BdbFRb4MaljmIVqfycU4wSA45t17UHOrPLpPYKGLQUGTxpwbBZpqZp6MZPqR/E+o0mr//D4N3UZUeJcIXPApNpy2yoYokzLbwvrKU3UEsDBAoAAAAIAC1nSlIm+X/5kAAAAM4AAAAkAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvcGFzcy5kVVQFAAG2SCRgfYxBDoJAEATv84p+gPgAYkyMF0w4kOAHVh3YjSuz2Rkw/N4V7946Vd3dyjTWSE6VTrmkQ/LZKR+p4ZhqdEXghzBIhnlGymFxxnjySl0Wk7tErdH3Da5tT+fiRslrDVUPiwo3m6eqquj79ueMLkNhQSHJgkwoaVZ+QHnh7CIsvFh32yw6NcjEeIcYceOtuKcPUEsDBAoAAAAIAC1nSlJrofCNxgAAABsBAAAqAAkAY3VybC1tYXN0ZXIvZG9jcy9j
*/