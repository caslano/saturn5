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
6P8liJ+AsC/GL0s1+l/Ayc30/y5s75QE79enY7rcjUY8lYe/Fz8B6T85bHH5fTLSl6Sy/l/VdP+Xs/JwtzKzY1Lfr8OYznLqDz5ekb5QYfcfHrbef9iF5aXyLcB4bePb44H+aZk9nsUPN2OPJ0F7rEQ8sydv2M9DeibJI0rzkabz25CgftsQPwHT4/ywE+lv9WTyp5n8dlP9OP1xZm+J5acgndsj3N5MfpmP/2/eB/lPuxqtyu2vMTTBwiHQNmxw62rZxlPi0paNeC+b4qns/cdSl1t/4l9TQaPfJ5E1oKzv1wT0RkJGOHtublkJGF3W/WQtxeP11kY83phiaSgC6vioLRbVPCIePE1vWKqhd8yjUBDhR5MAZAtFhJcv2RtRTPEoGMQPzVWDMrzlPXqHy4XWb8yWb+T9HcNeD9rqwfC5jhIoYZ7RXvjSudGumC+GF1Y2QF1Nj2czpa8r9pr8qs8N3RRrv2mufHfBNCdoupUmuS7S4H+3RwsObdn7HTIe9GelNV423ODEu41u6BsdJ6OA+l+dX+cZ1EGWtGp/wNCzrvIHjQd2yC6SaC6zH1R+LHTUVDfyle1plEm3IC+xflXj91gkAngTKcibBgJ51PB7AyGhJy5saAguFwWIqSU1QAZB7CCoP2o1Y/00LfY8vvnhdCg3MovbW4F+wfvgI36IGVQBtjcaxEiX+EvoRwMj+Tndwk88EIxv6Cudx0kfklgfHNllgR5kAw0cH7fSWDSO6UR0HPsJ6YacoHZENVUURhrH68IoTnhkBI63NKSIxulMEJjpoZpwbVQ1xCLiwaDZJDdeWjHVS+LFu396XonwWhw8cjmmj/jQXFCWFeLMEl60GfG+HEOxeFVAwtqQNORyQkQnqWKW1zqeTwGcTtMAxxtTBTlDjpJBcnpM2dS+FnpUQ/NVPH5uabk+HphcTxiuxhcXb2EPTochEhcvKsfmI05nbMXosq8seXM6k3sJ0+FsytsROj9uPhAXaMFSIWLENXdDlNni5cfzike3dBYvh6gPhjfJGGaEDJxJvPB25vREzMnDcSbldMascekomxPHx3VKYrrmQbzV7mBUw6ZgXR0LxzgR7qtyKz6Et2C8nqC4aybECDdexOlxn3KEq7ABHxrQiSqGRIlPN2rvU+FYBlYkZILINP/oVp1Q7OplwmtzRLfQsLwYJIH9q4glaLg2Eg6BKLE4uo+JPMJuC+MalmMJr9cvogJ/BlUf4fXKKjAWasIKTZHcbhXUX5jzY6U3wkUhFQ3+jypivPB7fMZ6sHHBSGByo//kxDIH6lMLSVeoCij8Y0sRXRa+QRPvwppj6zUR9WUG1CTewAEfK7CeYU0m8XB5OgIZ6zWhuiUsp2Y14lUbhJGuhqO61SwSWPy+n6/xuwB1nogCvI83vomv0WgXrEz9VUCCoQvJtnBdaz3NTMP3F43n67N1hOKF4vi9umjIxkBpw7VG9kko/jTkR1F5SCHmpss3WiGgT8c6Zf8XF+RlK9gOYdULrK5KepHgTyCRyzUNBNiG1fojqk/PNen6Qix3bdQf0OKeja7cwM5H0E/nAcpG6T8Y/U70H4L++ehPRf869B9KGWyS/u7ordb9aHu7BS4/4gkCrwxmfmnKBS4iyDYS/YdB0JWoJ6peU8QZHn8UZNFgg14XkhGVeZ5IUJIQP1dGQ34VVzFBjoGVQn4J3bhz6/fBaBKdGeHlj0J5NY8XMsLRqEZq/NGoTCyWlHm8S14CWgUGhC2hItDyqivcjIZxaglf6rL313QxhpdvyYSBpw4EEQ0VCi/5SRXjWsTEwUlRjNpVNCiYuBGbx4+dCiQbXY8PUtUvGsQTAJEi6wM+U7LGZFShQos=
*/