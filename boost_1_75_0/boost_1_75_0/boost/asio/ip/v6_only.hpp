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
ELjJGGuoXycXlqBHhDfgKvS5hMTo0nBb+usYxaQz84+o+EKNaXv1HziOsJtKNoNlZLmp5BSYK0u+/wO7MNNa3PPps3YDiohsXLQv64NXBU4nW2o0UKIpClOpjQR95g9jiL6VEyrVJbshpNSAVWgquYVYAGcDRmpYWaIGbKbwWx/JVq69TrJR3sb/KvLfG38g90Pse03b6yHUtL0Ok5WWwf/iE+riI4ByldfKEiu4I6RRcFuhYd5TU9iHuIYH2JFcw1B2CNcwhh3ANTzM9uUa0tR/NxKJ0j15L9eQoS5hwXWQECUj9blVRklbWdIR/lufG7Kf9GabyHByEGcexJ6HLqY79C94fvwAoVpmL0HeWOaCThd8rO8GnghZuRbLsaqjE4WrKvp5jK/Ue5nWYqYT5XqvlWsxyUQPvYraaIj6k0N450/et1JaD9e/rmiEmZXaRFhxoKQDxFcL2b/NIEHIQNmqLhFCbs0znyjDs9diiYEAb4FmoKCTYG0KF8kAbds6HepPKrladSTrh8NWGL91REKQtPFWDbWMtXoLxHKEWPnIE7TeLUPAJWw+Fu1GzjPqkpKO5BqpjNT/1j/I1Y+SbWge5y6pTWvX/IE3KxSQp6lk3R+YEBnN6KcU7VYRi5Yvxej0Wp2J2E2lq0lMFBk1G+Vcz/zucxhlNwqpJUXBMEW7CbFs92yPJJqH+pO16OXIX4o1MlJdvJ1ISBQI
*/