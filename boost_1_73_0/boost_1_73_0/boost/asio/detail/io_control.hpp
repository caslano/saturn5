//
// detail/io_control.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IO_CONTROL_HPP
#define BOOST_ASIO_DETAIL_IO_CONTROL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {
namespace io_control {

// I/O control command for getting number of bytes available.
class bytes_readable
{
public:
  // Default constructor.
  bytes_readable()
    : value_(0)
  {
  }

  // Construct with a specific command value.
  bytes_readable(std::size_t value)
    : value_(static_cast<detail::ioctl_arg_type>(value))
  {
  }

  // Get the name of the IO control command.
  int name() const
  {
    return static_cast<int>(BOOST_ASIO_OS_DEF(FIONREAD));
  }

  // Set the value of the I/O control command.
  void set(std::size_t value)
  {
    value_ = static_cast<detail::ioctl_arg_type>(value);
  }

  // Get the current value of the I/O control command.
  std::size_t get() const
  {
    return static_cast<std::size_t>(value_);
  }

  // Get the address of the command data.
  detail::ioctl_arg_type* data()
  {
    return &value_;
  }

  // Get the address of the command data.
  const detail::ioctl_arg_type* data() const
  {
    return &value_;
  }

private:
  detail::ioctl_arg_type value_;
};

} // namespace io_control
} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_IO_CONTROL_HPP

/* io_control.hpp
XyK/3FAThG/moAAminGkGAN318C8GD2HfV68zsAlqGSPA8lLJc8WyjW0UZ/lAEgWT4LpuzwYkiB+qUrIECYUeraicuT5gkQPGu4txBLpOWRqHUta6DQe1CAIUoA7F4RuGGaNlAhHAc+KzWZCjV/kfLF9KItqwoXlR6IGk2aqDsoFlAVhGIF86o4q51m2jZxEap7vj1/ua8qTZJtnePIcQIUNaywRw6eG0dKDqjnoDjHiIMIo4pAz3SF4oCkExfv3ZceBJOxCreAwctkEgcfVlOQieZQTDgT0iYIBeRidh/jTAr3eBPLF6Nh4tkzkO3MUIqC5FMn4MenxefgqVxPyE4TlYABFinm5BTciETLBkH8ltTXUrJR9m3WgYkrhs3xtR4wOkovYsSR3dArfhA4N7yDCNCOXZMUD50l+0rST+E5lSETZhNLYyvZIH79NE/CM0cWsAzCMI/lkYYnVsDoCXBz0Tkca/+pV9wsMabstO3qquDQEwA1tY+4rQ9M2hFX+n6nmP+eB6+e7Qq6Q/mraSD9Toll+QUiqVhlR/Jy1/A7oRAy1EbdO1c1hkIzxTDvyhd9M0dJVLrlwVRP6RbauQWRVmZz78Bwn963liZ/yzjBDLE+0hKYqzej4jd+Z0gcR6jt+3mloyMJrlh3Z
*/