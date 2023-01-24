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
UGY+RVVkhZNn6U9ff59u3Jk4QO3qXisoEXi6MohEAm55daEyCvR7BHqKoehZa3mcnoS+QnlRKy7hvr6+4qYXI8IR1rzr+Kmar9gxkK/oUX3FI1RucAXzFQURX9HRx1d81tY/zGnHuKm4Q/UVDuYroOyG3JCZCRcO5Y0DizK1C4yGbfQ8FEucno2TWfnNytdQ3nq4zWqxOOVNWi1TwUH4nWaIjPhcqEs8bVmfgT4Hisk3iw2WeWLQ4it2QDHKSBZSxeXPgwvgeVLDUPYYqJxMU5LyNIrHEHRiGlXAcot3Ik5YE9aJlRARXk87xiTInhd0H1KcCL4JrM21vda3NJMQ8SGHlH4moTjREJyBtRlF1mYS8PjSFzRrs9gNguOgyuLllBei/MAUgx8Yz0wHMlCNejGKr40EFangCqaCqIxCURkOd2zeVEVRgzGo8tU/aY7gqBgd1x+TZ/6JwmGgGSVmZCGTlwve0vzAAjM13yf0QMQgng5zHho/r5/aAPysjgNT5rXNAZIoTrtW+LdEi+tjaMk/PBxkUy4T5Iw/RTOTu4/OX+7DUDVIFb8elKGc2w/vgcuvpuka6gtLtBemg/3w55vB5mWk8MvELsv6JUAkiGdlh9dcHScGLN7scL74tQX3qARTMxLuQZxpzs6HC9CE+HBBiI8JFyQLz0BJOMjWTet52LET3pRgKk4GeVf5Agea4PfcfOUTrXfPAVYX
*/