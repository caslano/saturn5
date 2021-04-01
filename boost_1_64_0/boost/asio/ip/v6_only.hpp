//
// ip/v6_only.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_V6_ONLY_HPP
#define BOOST_ASIO_IP_V6_ONLY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/socket_option.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Socket option for determining whether an IPv6 socket supports IPv6
/// communication only.
/**
 * Implements the IPPROTO_IPV6/IP_V6ONLY socket option.
 *
 * @par Examples
 * Setting the option:
 * @code
 * boost::asio::ip::tcp::socket socket(my_context);
 * ...
 * boost::asio::ip::v6_only option(true);
 * socket.set_option(option);
 * @endcode
 *
 * @par
 * Getting the current option value:
 * @code
 * boost::asio::ip::tcp::socket socket(my_context);
 * ...
 * boost::asio::ip::v6_only option;
 * socket.get_option(option);
 * bool v6_only = option.value();
 * @endcode
 *
 * @par Concepts:
 * GettableSocketOption, SettableSocketOption.
 */
#if defined(GENERATING_DOCUMENTATION)
typedef implementation_defined v6_only;
#elif defined(IPV6_V6ONLY)
typedef boost::asio::detail::socket_option::boolean<
    IPPROTO_IPV6, IPV6_V6ONLY> v6_only;
#else
typedef boost::asio::detail::socket_option::boolean<
    boost::asio::detail::custom_socket_option_level,
    boost::asio::detail::always_fail_option> v6_only;
#endif

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_V6_ONLY_HPP

/* v6_only.hpp
W+peAKSolySC0pddXGJrZZT0bQkfZA6SO7aXWfrL/wrBN6if+LQx9qK1n2aMY7D8d3HFVVAlUdjZ3sMDE5cmQpuIkB14CcGg3qs9rx/SL/ybjKi8MsDX+DQ+1Yu9+d23bz3BA4ROr8N3IkP6K7imkLZt56LTTRQGl+e4OTJ2HyeUoiToMnvZA9Uvmpb+fHO4VUX9x57P3To2ta+aXFshbeqqjbZOPAvDwkNCi3hxudO9bHuEu9Sy93awCUQAINviRUYSgROs7iOK3jIZfvbLdbGl693tfxeAYlGlNqxRcFIGy68zzPt1JHLLjnAn5JL9Fii/1yiJb2fIzcRNMCe9cYaEhelqMP7dcTPKxLMJDpldXktK3iJI60o9BhNFDLfS6enAXNulCmS5LabJIgF/MwryiLP4pOFPrTKDFoNA6QvwREDEA8B2oQrhVRFQldutLjQZsEFswq6O1wcI6NGYaNyUKOkO3xsli34jh/wEzhU7ZeYd8I/yL6iuxsZ2Kcs1u6PMl9um9Qe+8lRn+SGa6ThMULpEdYz+lq3al6Q4ucEWCk9jf/juheEPfQ==
*/