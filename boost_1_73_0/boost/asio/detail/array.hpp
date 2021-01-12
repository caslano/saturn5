//
// detail/array.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_ARRAY_HPP
#define BOOST_ASIO_DETAIL_ARRAY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_ARRAY)
# include <array>
#else // defined(BOOST_ASIO_HAS_STD_ARRAY)
# include <boost/array.hpp>
#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_STD_ARRAY)
using std::array;
#else // defined(BOOST_ASIO_HAS_STD_ARRAY)
using boost::array;
#endif // defined(BOOST_ASIO_HAS_STD_ARRAY)

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_ARRAY_HPP

/* array.hpp
ZleyUMdr2Jz9XXa+g9apDkBny5n+O8CVSCvvKxRcCbtPz2sz6sFO+fpWjTlRriS8J5gTrcyciKN3Mntj6Z1hL9PGbo29TPPveZn9hufL7RQNsJKGI3OsvSq7BpyaDH3kiHtgDXFpaJh6+oiABMZzhitu325gBC8N5/O+jwX5wGE6NqN1f7+G8d/Mw5E3CnV8cBffCPa10RfDtnsJva2/nPzTAr9uq8Sncb9LWfe2XldEB8v+
*/