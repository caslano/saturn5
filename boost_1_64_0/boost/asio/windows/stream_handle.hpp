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
NmMPrUftybIz1jCh+4/uMTYRKC9uYxgbEeiwY01Y6urm/wUYP5pLKtfDwXhrJAEKEizlfBcFqyaOaHpreQV2z06+3RlusfffbhRFn6Skevjw1ZPSdSqus6+e+U4tVpB7hVhZ6yLW+nPBiwJYOxuTOuYvgGjSZDvzb39O0s+pk7WC8L32CkaWppIRJlpth2v4ES7PN5xU79ge1rlAvQRWl7vsz2nD1edTl2FP0VhA2/TdavEunBRATbPXLJh3UYWYE73qaVnoClp4EAwVHMFlwMWYxTS4DEVB0yFuZHFyen3N+eCb+xw+O6CQpyVSWJl9uarJc6p2RDt22+1hrEll1KxRJxaxcXodNJe4CdJmQvg4FSaM7HmckLxIhzl506YjSDU68RnaIxBxIM4ek/JS8Lphc0Zk88S2RfejDACHDe8RbwjEu6D+SLEQ8lK3O8y6Njv5HpvCcsFFZxsjy0zNVremD9kNfYiKjZ8eyVtHIEyq1S7iQurgeQIrWbKkB9yJWwFnjjubmhZ5qe8q4RfYIfY8QgBmPqtGRcqPObDJfL532guvMq8W7YvgKw==
*/