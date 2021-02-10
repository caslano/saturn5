//
// is_read_buffered.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IS_READ_BUFFERED_HPP
#define BOOST_ASIO_IS_READ_BUFFERED_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/buffered_read_stream_fwd.hpp>
#include <boost/asio/buffered_stream_fwd.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

namespace detail {

template <typename Stream>
char is_read_buffered_helper(buffered_stream<Stream>* s);

template <typename Stream>
char is_read_buffered_helper(buffered_read_stream<Stream>* s);

struct is_read_buffered_big_type { char data[10]; };
is_read_buffered_big_type is_read_buffered_helper(...);

} // namespace detail

/// The is_read_buffered class is a traits class that may be used to determine
/// whether a stream type supports buffering of read data.
template <typename Stream>
class is_read_buffered
{
public:
#if defined(GENERATING_DOCUMENTATION)
  /// The value member is true only if the Stream type supports buffering of
  /// read data.
  static const bool value;
#else
  BOOST_ASIO_STATIC_CONSTANT(bool,
      value = sizeof(detail::is_read_buffered_helper((Stream*)0)) == 1);
#endif
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IS_READ_BUFFERED_HPP

/* is_read_buffered.hpp
gSiRJTqi68gDstWilXeSfSx9v+f2MUk83udB+HEEtv3B1knD+7NvO7Dh59bN2Yu0oKGCi0M/ibo8e04fO3wdhUdOwjOCHynDH3s2r42ohAhCpVK8xaYk0n5loh/claxcn8IdQp8JH1H11JQmUVj3GGJ7IXrT1FgD4zYJWmWTZl2BAk3LOQhQj84O/t1z/0mynA4o82T0FweD/Zat2eqTtHntNvQq0Kauw4utYQwiqfbLIgsd/Eb4Lw9bcgAVPSEa0wjDyX0qrONbsZd8PQIxIhHX+eXYT8HOlauMlJn1hd+LjL7llwUFMBUqCsRLWCUGUsqs6G05biREQ7kly0wIXIIXXUx464KmicB6Zv1yRAbufcHWqoWHlphVk/USavkETMU0+Jfb3uLOhCcwBiRi+9VxOQoCAT9q24USan4IpSnqs/LEsCpfJckzjT0wH9QirSNHIXq0eNF7Jhclbul0SmhTJ5X0CUOAmc3VfMaRwc49j4JvgNlNVybQ73kVY58wzy0LZV2tAMlWGwK8V6duHnRyKCo4hlBSGAp1s15lU4v8wHMS15wc5NrCLOh7HoUV8HaFY88wM4MQcMnCkxCng39BLjvkxbMVDaTAQj7i8w+DzdIioTmCl9b6jATL5t/bBbRT0iz6k8iqHB/J
*/