//
// is_write_buffered.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IS_WRITE_BUFFERED_HPP
#define BOOST_ASIO_IS_WRITE_BUFFERED_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/buffered_stream_fwd.hpp>
#include <boost/asio/buffered_write_stream_fwd.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

namespace detail {

template <typename Stream>
char is_write_buffered_helper(buffered_stream<Stream>* s);

template <typename Stream>
char is_write_buffered_helper(buffered_write_stream<Stream>* s);

struct is_write_buffered_big_type { char data[10]; };
is_write_buffered_big_type is_write_buffered_helper(...);

} // namespace detail

/// The is_write_buffered class is a traits class that may be used to determine
/// whether a stream type supports buffering of written data.
template <typename Stream>
class is_write_buffered
{
public:
#if defined(GENERATING_DOCUMENTATION)
  /// The value member is true only if the Stream type supports buffering of
  /// written data.
  static const bool value;
#else
  BOOST_ASIO_STATIC_CONSTANT(bool,
      value = sizeof(detail::is_write_buffered_helper((Stream*)0)) == 1);
#endif
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IS_WRITE_BUFFERED_HPP

/* is_write_buffered.hpp
LodzJntNsVEMjTlFjXGf6XoIur+1EBUykPMAP0A5D0TkPBA8EKi3W+oTjGo7jMhkYFG0CgLTwoGagLfM702BNVl3msySTrOCT/l34mGPx2p5GVkVyQIhFZFcrENjlLgLbfSgAHYk8Qk61Hx8/jQ6tLf9O1G1Zp5FTWmOaEpz160Ubc8GJGFOoN+q3Ajr/mIONV6ZxFRuLLLv9OCAbA/hHNuC0dBnBJvCGIUg6I+3WJrvGBdnbyO7RxWjhjlPklQEM4T6bryglQJrZAzQy/PGhZL7o1YG7whPzZzhTX9kKp3gKXrBy/yRNdjslyOa/XLXlkG8QM7mb6SR+VH4GoV0Wc+OJ4UDkNZDSgx/JA7hRhUbMCEKGnRugN8VQ/7HDvM0t7EKe/BGGPsNk4itu3YJtjsF2x25JMIjAEul8eSWI7g77PUONHnDXUozusRKM4qojSEnX1aYzFoDpwYCvbIiN3we3dBnVePJ87cXyFvwFPMkB05Fo63FWNhDraek1l4JT5SbpmDgB8Q2GKnn1YSwQQ7zB5PCDs7UfnO7e2+lPapXJLOxPfuj1QKnkcfeiz9Cl5Xxrv2KzDr3Rqu3Bv8GtQBREBU1ttSM9PIjsG/80cGRek4Nogzk+aOgnp1JuF1tPj44lhxG2wQWm6AIX8yl2mBJkjJ4ORrrpY0jI5Gx0GRlVNZKWUGEhjK8wPhjuGM42uicl0AxVjqnCC1F
*/