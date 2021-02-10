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
YOUuBx3wyxZ1ogQfAHXye0Dtfg3U7JlTU7iBUOddd1SxFqDP3P7r8p/Ee9OjR4Njd/BTVnz55Ct3cbgfA7ZgaNTjtLhR6L7lcyehVk7OC0hm3412dzdyfffGNzWJ5x5Gc5ZwHrG6S22mgNiXT7Y+fxy+f//7vz8ZHJ+4g7dXRycPfn7Cn6NJ/OFjDPwXX/zNHfw8HNLHX7lnFz+7xwPq6E162+0KHdDbre+fbH3/KivWHxzNaPDoxGVPnn5xvxNuEtvMLkB8CxInzj8QfeFDW8FmtUirqWIWQX9FG4OzQxvt2XhGrKu7DY+xDW3Lr9zrq4tzWs0xTa2FHE+I3zBECZSJdmByrAQxEn4S26x5TJyuPp8u43Y07I9lQYehKqsjDsXpux9fnHM2hHudFkSkKkhcN3AVi7cA37zaFB9ov/4wGCIMF2riy9f0e/gY3+NlV71VjOYT/lwseUmif7BEGzRJ0SpI72mzSNjTc+P9Cp7rZuuwN90oF0gZYoFRl0ZNOxbsjeONBSlwrIi4Y2SGamY0syfvZ06fmb54RZKyTPg02ArF3hJsRZxUwaFKjcVHW/BmzdZTDtIavXn2+vzsT89evT8f0ScZDXbQhnLxDJfZpMzhxxh9NUpkeHw0lK8ICfDrRH6dfDU67Cz4
*/