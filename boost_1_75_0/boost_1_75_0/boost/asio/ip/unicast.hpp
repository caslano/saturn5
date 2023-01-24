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
5UM2mKDOQzaZInwJLbw2Ej1WlBEZkLG9+Ola7uJtnyrTdC31xWOo9wVWmCK0VgWXob1NJp0aAaEvH3LcFDGcDzllihhl9eKDF6ML8suYcxujgM7twstNEdF8iMIUEQdZkqEWeqzA4gdGzCE0zuGWK2WmQn+2I1jkrDLW3HEgSIhXrDkmCFgdr0mG9jgemKUwhWj0066FKvxZBfeowh9sGmLTgE1JbEqwKYhNATY5scnBJiM2WYI9vlsy1CXXYNdnAmae1EPg9DncRdkIYr+2gtbMI36mR4ez/QT23QMMjtR35yOiTXI+Ig6PrKvQYSRTk3g80ceFa0DpVCpBTEAiJoCkGM34A7xS3QK4QtngSHYq9LmcuS9tW6xiJIwLQPEcZPCuqzWYWInSHwPWwEPjojTqNRWlqij0Mymt/uSWVyf4L2d9SGTsEbBGwToErFtlwoBBGcvL+akKHJSruPKG0ldzyDAAtMrXtHst/Jx0m7Fg8HtR05QWaLCVWD4kSvsc6ck1Jhkf4msCZfKSs6+Fx4Z1qHTiEetB8IDGVPxVPQn0BZuNaAc8Yxk/hZ08hR2HV0SmsH5T2I5T9I8gghXrqVJAK9Elo4l1Gx3BopXokt7ESnSJL7FuocVFq6DUTaTWSOO99JmPJhzK8zGYLwPwAIcB9gFM/xz7ZW+5h9zD29tbofD08vby9lB4tbjYnH07s6jGR5M5oEymSce7
*/