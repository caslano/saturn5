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
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
*/