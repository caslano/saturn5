//
// posix/stream_descriptor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_POSIX_STREAM_DESCRIPTOR_HPP
#define BOOST_ASIO_POSIX_STREAM_DESCRIPTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/posix/basic_stream_descriptor.hpp>

namespace boost {
namespace asio {
namespace posix {

/// Typedef for the typical usage of a stream-oriented descriptor.
typedef basic_stream_descriptor<> stream_descriptor;

} // namespace posix
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_POSIX_STREAM_DESCRIPTOR_HPP

/* stream_descriptor.hpp
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
*/