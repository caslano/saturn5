//
// windows/object_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2011 Boris Schaeling (boris@highscore.de)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_OBJECT_HANDLE_HPP
#define BOOST_ASIO_WINDOWS_OBJECT_HANDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_OBJECT_HANDLE) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/windows/basic_object_handle.hpp>

namespace boost {
namespace asio {
namespace windows {

/// Typedef for the typical usage of an object handle.
typedef basic_object_handle<> object_handle;

} // namespace windows
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_WINDOWS_OBJECT_HANDLE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_WINDOWS_OBJECT_HANDLE_HPP

/* object_handle.hpp
h2jUf1BLAwQKAAAACAAtZ0pStNOY188BAAA8AwAAJgAJAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3NvY2tzNS5kVVQFAAG2SCRgXVJdi9swEHzXr9jHO2o7ydH0DlMK4Uq5owcNJO1L6YMjr21xitboI4n/fVey0yR9sYV2dmZ2Vm9k2hIcyXe3FCvL588dOf+77Mn6P1/EC+q+hM2P5++bJfSWTgOQgVYd0EAEwgeISLGqa6xLeCwWT8VcPFceW7JDObaIPM/FT4fgOwTXo1SNwvqWNYdd8GDRkT6MwERvqj2CJllpPRTw2sSKiIpgwn6HFpQDQ/7CmoHy8bJyLuxZpPLJICzmT/NCiG3HNeq94inogNaqGhlsBraBB0XBQWCj1ECeJ2MZM0XRASqLsA8+RCsCT1IHxzEw50YZiTz6w6J4zBh7UeCTCz3aRofI7BJwoACyMpNl5p3in7I6Kt+dxdmLMu0/RDmbRZAnSTr6bdTpSn75UMyz1IljcxTZYZynBk9Xein4KXfOJ20l5uzVHsVZWrmxM/lhppftdj2Ln6mTt8EzBMlFVuLMZLAaGmV5a5KMQek5OBKR/UbQ1FHRXEB3vrMU2m6E3UevsSlqAVm41hQiPYGbhJNLh7zMSqcRXJb6
*/