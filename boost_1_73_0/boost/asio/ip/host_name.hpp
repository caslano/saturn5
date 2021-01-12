//
// ip/host_name.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_HOST_NAME_HPP
#define BOOST_ASIO_IP_HOST_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <string>
#include <boost/system/error_code.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Get the current host name.
BOOST_ASIO_DECL std::string host_name();

/// Get the current host name.
BOOST_ASIO_DECL std::string host_name(boost::system::error_code& ec);

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ip/impl/host_name.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_IP_HOST_NAME_HPP

/* host_name.hpp
TF2gfAAoWyd7ZI27Ag06Tiy/veW0LCkPjy/Bfbc6r2X46+zQFU7cl6t3VvZNPc97+nzTiDJGTW5y1BwbwFHDFm9O2i8UQXu5/Ic7Ags6pEq8yeenncRyo+GwNYJ6RC+Uo0EaeELzuwPGxZlygCkHl/HLeHS5plFqKpGYhwwncFnkbl2vi+wwg0LDnbwtirPRo7xmdxp78ic+p9ahuWj7yT5obysaQeIuXUjT49ysyMrbU939
*/