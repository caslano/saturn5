//
// windows/stream_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_STREAM_HANDLE_HPP
#define BOOST_ASIO_WINDOWS_STREAM_HANDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/windows/basic_stream_handle.hpp>

namespace boost {
namespace asio {
namespace windows {

/// Typedef for the typical usage of a stream-oriented handle.
typedef basic_stream_handle<> stream_handle;

} // namespace windows
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_WINDOWS_STREAM_HANDLE_HPP

/* stream_handle.hpp
roWcestYKpljB8H3h9v1hzHQMxn8NGTGFWEL+pKSLkLBVJfvy3WBbmXUzmpv9bxmrdP30bP0XfprI8mcav5qHT/Fw55Dokgn4NsjsozJZa4zHmw1aGcdjDyAm8st5Q5zp6CJ6/Ez+JV8EaGa2EDcKB6HAm8nrZIotClQZuUI+SvZXamg9FOWoE9F9OMp7Y6m6JP1BfoKfbN+BuwxHgo936DSPOz1fG9Sg8wl35KqtElPpX+m79BPaRegh8AEswI7gt3GvuK68Uv5rfzniBxPcaa4AF78FPLaSTmpeKoTtU56pDEGfnWhQaV72OvD35AEejVN2F1QFm+4Fvwy/gH/Biq9PtT5eKm9PE32RbZ4w6FsNKgsD3suJ50Uo0tBwxj0DvpHuivTC5plOkOgInewF9gm0AH9ucHcc64d/5PgIVYXm4gXxSips5QhuSIO8+TLyhG1kmYg50ZoUzU33Uevp/N6hr5RDzVkeOLr9jyVh+1/GkC93ye+dCR9HMj5GVOXvcWmARt+Ae6VhdvI5n/g2whR0BijhUXwcYFSvuQil7LxaZ6yQzmkZKib1Z3aJe03jUUsfq3/opeH2zpr9DWv2DrBw57jDYJCuAhPXYWuQdPo3xb0ZjjnU3Qunc7sZWqw9dg2bBQrcSacawm+Ht8c2TwISLQd2Xuev807w5c2EJqi3/tJ0+EWz0gj5cXyfvmaPFidrZpGF2OAMcu4
*/