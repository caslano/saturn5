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
3AjDV209ast+kzoA112ev+5L7MEAf4uJx8rkSe4HmI6GkVjES9KZOs5DKKOnQY8WP4jhd9QWDLG1tHPJzuTkrXnXIbuVTx+LkAch/eMw5H8kpneZNGdn6gieAIglrH7TYWlCGFpa2CPpV/var5M2KmN7rwCr9i1qVLZYAsqykLzgrplTMdDfL+OTxgOorAhrb80FEXcWvTl3oT4ovh2s/PI0ZEAacmpN+CCTBiNc4ee58qhY3m3r1N6PuBYp+U4qJCZ0OEgH0nBFaVpBFGy70PR/rlQKWUo1fgsQYU8CairmUH/kxFmkKXusaAQ6Ncs6KpOGWgxXV69g1ASpuJVw5NpsCoWH68qe4ry9JeTFB76ZSI1ScHmZl+Bq6/0I0eOhQhOHz6DwsvaovDYUbkDVLO/6j3quf4Ip9YddcKZNwhW6eMrWh6L3AcBGz2/pa/xzomu6HXJErFSIyzddznTyK/vKYeV3WajDKsWApd5e8PpAExUTCsBnsqlOzbIv6jULdhx6fG2OSXYkwkabFWtv+kEw/YdiLXdSYdoCEtnfGBL4QgnaCmPwMcG2H1wdhlMaKmfhX4j26lLRcoraaICoZZ2KPZRTtLOw13OSKvpad72tjNKq0XKOtAiS9Rvnpjzc6/Xv7HX3bKObRUza
*/