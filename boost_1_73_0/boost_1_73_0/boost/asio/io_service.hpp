//
// io_service.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IO_SERVICE_HPP
#define BOOST_ASIO_IO_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/io_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if !defined(BOOST_ASIO_NO_DEPRECATED)
/// Typedef for backwards compatibility.
typedef io_context io_service;
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IO_SERVICE_HPP

/* io_service.hpp
SszUj4KTmdi6QNIMWbwvuzpy3FGSwhgxz70yNuAmfbLOhauM+hejIwLighSoYPx0sHpk9SrHdIEj6S31DlUmYZRD33GvLIAEAwQxcZY95Ek8oaxmptIwAiT+Q+OLmjZIzzWat5TYnFqYGONl281BcFCnNS+AMBTrASQOE/x/0dITL5Qh6OGjfsYLVm/PSI9Xe1BrRbIX3Gy6Xq76MocgAbNVzbZQZC6WItgO81KhIKth5G4SPrxQYVsfmC6sNk9TVwCBWhlaMhyj5mmw8Qr0D/Qd46t2p/zAPHcBvaP1uPgzdajFpNxG5ClPdw2shJroBpvtiEhDIqEtphZiO0yIXGJH2bVkGAu8m5TlDbTrGsdivIlo6sC95gAFPgXi2hBnUPvJJJjohcIfAEKHcHWRruLTmjWeFVRo4QrBAAq8FO8OM5fYATB1X6PxN5GLA4JF6MTcB9SLLyYlyUA0gUu8Tk0a3wOJ2eM931staIA9N4f+MqaJd4jkVJqevUtnqc8/PTm+SufrPP2MPzp79Ojk+A9Pj/c6cSLgSExJucfBZJ6RYgXhRheaik7HZA+DEH0jtknI+snwFNRpzmbtVNDQjb7OCmIktNgmnQcU5B4Y4mHLGvbfQhwamDWn8vs4xnticdjj4eXYCj0hMqKT
*/