//
// posix/descriptor.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_POSIX_DESCRIPTOR_HPP
#define BOOST_ASIO_POSIX_DESCRIPTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/posix/basic_descriptor.hpp>

namespace boost {
namespace asio {
namespace posix {

/// Typedef for the typical usage of basic_descriptor.
typedef basic_descriptor<> descriptor;

} // namespace posix
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR)
       // || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_POSIX_DESCRIPTOR_HPP

/* descriptor.hpp
D8HiUQhwsppS4WaHkxlexQyzkSS6aZyT5TMYYWZuAxBV7dcli9slixza66r2u04x6BcDe+Wq1fEzLkraCZ4rmKHqxo85OvTNmKGu4Hh/nqT9mqR1mWkh3xIZvkO+gw1S4pW9QfoeuYY8UQjoTHV6TPv+Pm41P1rPiVLLZ/5pa9fztzV7qHlMi9I4eGJ0ad8mxdRlDz8ZDf354lCPDUGRdSpoVxQivfBT1nDTYq+gXqSBcR1v
*/