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
ybpAHwdRkC5fB8JLLuqcOQsn87p9Hscq+9QeYkgRl+uyJMACUpq4y2Tn3a/nAp2sdrws0TV9/G0aXz9FEEOCYwbupC122FA1DpQ43yK/iijbG7DuHkwzo2wP2wevsq9nkNMnq0D5iInX3DD3rjbud6ufJRn0eIi53aEMYe/vUHEc9AjhTHoZq+JGc4qSJ/QELBHbxc+H6OUaWAfIzAQx6SU31sNqvH6Pk5aIJseyHybjhIf3mRoxZCbdu7/pTdCI7KouRb3aIrKOYiihpXwpaSqwLAfimrd25QC+I5sMm3x0hXU8x+jXgcXXPg6iQuFAMKmXFz6EAM7h5qKF8Tv/BgNnf+Y8QZ9EaMFwK9/Ft9RNBH/dukRZfCIBoUyl34zEJJgGg6sW28oizo+DczyQzfqczvKhCSGQie+8d/ZMhUgZxKi43WEq9NbP5J9M1S7lNUvqkEI3BpbO7+nhuzhrVz4QUgaRhlji9ogdHLXo9ccaYdQmjPCwKVmu36CWnN+ZBmmRpJyx22SavPl37bGNgSOBmsEXerNsICtAP+hEkg3qgmQjWh2/eLeAAg==
*/