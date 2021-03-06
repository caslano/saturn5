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
luvCFFncO1zkmjJLLx8GheUdXAop3syAYsiAzpT85tLIqT7sWAJP18XtJaPyp9Hc11PBtpmou1bmtzlDth/L41q+tNbu1vSMf2VZI6PrXYNUNcfDyIHxQ2VSL7GJ2lhflnFnPsbfruUBGiPT+4ANJNf13fJXx7gKjGHbg0kol8OZBJT5CXEzwUZGt/gnQEKOW5mYbyClBM+T7vBEtXsEKXtXi/iAwYmfu3YPvTgLpQfFvS5nrxYfqa0CmGFNxkvNzG7YYfZnmaNpGZvVqn/nNQHot9kjmLonvssTCozX+lU6gLb6qslaKoVSMh95ynExurNZKJ8y6zQ3hV/VbS8n4wsmHKgoYiKb3XpCbau34FVh2I3rZt5JX3f3qTkvKegDdD+2CDqAh3LyH7k4obn5scp7hFiuReKlrT26y3fw5Fvt+K1i8aGRd85g5ZxeLtF0tDO2m5EG1rOtV4piggpCJB9E7oyz5aVlIxvEo9c3VmtzlHWxwEMov9v4naSt7khv/BNnxLp82SCVvmQa6Jw6OAMLJdJea3em7iT2l64cdBc94r+Acf5U4hXiWQ==
*/