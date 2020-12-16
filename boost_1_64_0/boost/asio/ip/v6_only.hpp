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
mSpy97mSyeW5rtbq7g8/A+2EZJc/r8P62CFZ0t+xZsMI5JA28+RfEfsRvhGN17Xww6flFEebSdHxzTSR2+JqRFqGaVpyTfipuDay0yJrpx9CPsNeG5LrJtFbzJIMid5x/A+rJ6HyuX75+lW/C1m/QWWqkbk+CRl31Y8TOsS6E+MT+OdNDLkOtJ2MkbQ1j3gd5Il/dzO+eoXYE4LSdZhz3m2nK6GqKkR/Q2Xi+La6wZaJqXrXL/ORyqSoTCYy99gy9Za2SYxJsPxy42rENRa5jbZc4tLz/TITVcZftpuR2YSMZ+neWLenGWXQLMlftgVJPmPHN9FOF2azHV/S0oM1dUuca3dPIcwbTWWcjrhhHcZ6/eNvXNcRxnb1ug0d25Xxt8VS3nwDaxo0BkQZWRzIYhphsjHD7T72Kx3rlS6atj5vsRnf0msAf70GtM2vkTB9tb/xx5Es5dM3lm9gGF/5dLBqlk9QmWp5pNdhj5ZhUh6SjqBxxWrNV3OzBiltC9kjQfmS28Y09JKkP1kveSrQ9PtlYxx+U7W9+/3ij3m/aaj9OuFJZ4HYk4x9alCaJ+uNri2mASYVswK5pK9D0ixVIXtUSLpsN9PPq3xbLeNAeWZETqcpzyxJl8QnaeumaVulOgE/0XZyjeoElH8iaSNh4fUBUiRNKkfojlYe35vjg8f/Va6JFSx3SeiYv9kPZbnIzbeSkFM9AA2bUnN8X8KUBKcheCy/PGgsH7mgsfyI65rsErlTzf2WPq9Q2ppeD1eI/xLm33fm232MY2yf4nLcO+78JHhs/2dib2z5+4utXDP3YtZLXwH/E8b1y339yi2fmHH9oPZSnKD6ldpehmAO4nPkU2kvdvu1W7OjvZTOD4wnqxy5jDdlW2D6Gc9ntl8f6VdW0y5bca5fSL/SJKRfScbusdND+r5ucsy+xXktaNlJuoL6zHVNfMItuV91gl94yD9pzJd0VbG1hu9ZjAu2Yv7UmdOnUeCBfC6iNANrS90qYQ55NN8ax1lWS33muV3sKzzD3eTGfdDq4+lFWPxoJ+3/gZ+25a9Sg5+/SKLG1dM8k6wR+xrPG9ZGd2t9Jin/e7LsV3QtT9d3YDZbH7g2uhtKnNWS3jkFs6cH9EdvlDiu8zxsPevW607PczphkDHpGiNxzEjWa8yx/tV1Iv+eyfM/j9r2RDnHeSa+pzy7rc91TS/uKhKnR2X85xhPqC6O60/bue6xM0Dy9qr7HesqZHAz4bojM0ja+BBbhlL9HWeK132saC1GN6yppO1H2PtZrVW/a5QdhvxvIcQuzPPWA65lbupFn3PTP7f9f6n6YIHy4JxyTY6R8J08T3LO5MBzbllFZVHJIke/0EzkYoze22Epl0Szh1AHOc9Vpt9oqfKylpOxD/QMsF50p3Bu+zr/QOJY5XHTJ2V4fPXcooU8D9v6udLngRA9ueb2NSXxLWGfpN6k3Hbz18spkjf7Gr9AZNp4HkHC8YxungO3iH+c0fd6TvKQzr0uRtstLUPc6kvaHpZ6LSyoLPClrSpUt8qU+2dSV43V7k/b2ZKOVb69nIwO4zoph/2eQBpnGR2tr3zXhLseIVNpc63FvfZrhXbOIUVodMDf8uXN5SaOw+Qn5LoNfpcwa3BdKudZ6+7tbqt17w9zhoQZKWGKTX3lOMtE9W5StLwPS1znuRpRLt3Zb8r//H3W0cDzepYvPklES73O/ynhEt3x5DONs7zsigl7fbvbSdshpC8t1YS13yFKE3jeS/K/l1S9kxjTLNF7+djEmPjwOtztNExX7Lx38LzdlmftGE9CYkInfnjja3kHX+q7niK+eywT/7bm2d8+T15jfddouDQp5F1DZSqx3+8=
*/