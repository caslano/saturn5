//
// serial_port.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2008 Rep Invariant Systems, Inc. (info@repinvariant.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SERIAL_PORT_HPP
#define BOOST_ASIO_SERIAL_PORT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_SERIAL_PORT) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/basic_serial_port.hpp>

namespace boost {
namespace asio {

/// Typedef for the typical usage of a serial port.
typedef basic_serial_port<> serial_port;

} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_SERIAL_PORT)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_SERIAL_PORT_HPP

/* serial_port.hpp
HnYckXYckgqOyAjuSMvJhy2QwxDJ+lx96AF5csTrTZos89m9DTUzF0l4AgqWfuY/a8SNEdsL+EH9zw3WTYUW+6mZsKvcqYscnUExsMU8sLyWfw1utPALlMhXBla3ZytHyIio1gEH2LiKzoUf6zSfjdl97CaIxQie7OBDY7P27TPLMjHbgkC7py8wL5KcC8ysVcjW35TxGC/NZnPLdD1KO18qtT6up8nClY57UHgK7NVUc2du
*/