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
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
*/