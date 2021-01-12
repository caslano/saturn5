//
// windows/overlapped_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_OVERLAPPED_HANDLE_HPP
#define BOOST_ASIO_WINDOWS_OVERLAPPED_HANDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE) \
  || defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/windows/basic_overlapped_handle.hpp>

namespace boost {
namespace asio {
namespace windows {

/// Typedef for the typical usage of an overlapped handle.
typedef basic_overlapped_handle<> overlapped_handle;

} // namespace windows
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE)
       //   || defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_WINDOWS_OVERLAPPED_HANDLE_HPP

/* overlapped_handle.hpp
C2EuhlXATynpDUVguzjy6tHN9ZoZnuXzN7EZ+rKtSgHhGDSft3HeYlIXzw9eR824Tq73LItFGGJm2Zm486BB8fjfVbsGJfpNsaBDZtA8BFFyGA00aB0JCGfjLoVwii/w1N4Ey1gsKl6viGO0/1UiLf3VLfGqlQGOAwgipBiPdiSxf4h1d6r4h50I/HxW5yhE1Eyo1J961eh1qvEBMUVWWomoaXeu3unZhGUtfNjaesDGDdgP
*/