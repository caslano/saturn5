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
434d6U7jw2djiQ5XsFqHF2K9Tvt3pEMOMK/u4QcxXoc/xCQd3nCU565zvAda3XueD0cfXeQz0U+X+UoM0D18N9bGd8fLsF43+GOs0ek7vjUs1TneAyt1ng/HCl3mh9F/B+fyFgf6HnWBH0YujvPQg3y/Os8zMFrXeOpo19JVznzX2oa6Fh+DFY6XeD5W6jrffXBHSsY0eeQh7ksX+PQxfk+M6Tm0Iz2HSozh9u95/x3P8mDM1918YByPc/l4VOJafCFm6QrfgOmxNl6EubEGXoWqbnL7972TMT8PRinm5wMxURf4eIzTJb4Q5Zifb0Ax5ucXMCjWzH0L9kuHt8cwHZ6Ogg4vxEQdfhxTdfpBRzoR63X2h95r9NnRdXkW+ukqTznMPkfzWUd5XjHm6I50Ncbq2jHOK3rfonkZJuieYzvSZj+1D+YPX3icb02H9zre89LFEzrSXzApzuVvTLT+newJP4NBOp3YkQ7GAF3kH53kvdU9vMPJ/kxxboE/QlPnJvluMEc3+PBTfDu6zJuc6pnGeL4SM3WVP8Qac2ZP60i3YYVu8OcYE8dLvkeM1Xm+GLN1+GbM0+F0ur2O9fNslHWNj/u556Er/AzG6ybv+gv7qwvcMtm+xbl8FkbFeL4PM6yzzh9hsk5n2AdM1SW+AmtjT3g5JnR39frIM+2tDv8F03Xxl+bDeF3jVzBEh0+f4vnq8KUYHWN48K/MuXNXrw/BZB2+DTN0kxee5VnrdLZ38mz/WId3wRIdnofVOrwIyfzhV9FP56Z2pJPO8ex0k7PnmieO82lYp8OZ8/xzu3T1ugtDdJG3LvtzIpqfxtKYh/f6tTXoAr99vucYYy5wrWnuRVe5+RvP3Zj8hd4ZjLHOIp+JUbrMV2KE7uG7MV7XeBnG6gZ/jKE6XeT3EIN0jvfAAJ3nw9En5uczMUyX+Ur0i/n5bqyP94eXoTXm5/7T/f5YczefhVm6h19Djy5e3JEuR2ZXx3nrS+yVrvC1v/N8dfUyv70V92x8nqtYruu87+/9NsY8XMdc3eQpf/B75dzwAyjr8JuYrcObXu7b0+GtsUSX+LAr7I+u87Ir/T7r3B/9GYr1usw1FHYzhouz/AbqCj+OGbrBm1/teekSf4jROvcn7wbycS6vnG3/dfc11oI5cS5fe61/HGP4fczW6c8d6QeYqUt8FZbo8BdYqsPf6LFXOnwN+gyzJ9x+nefleJYHozWuywdikC7w8RigS3wh+ugK73y9+9zdPvNCjNMNPn+Oe9RN/vtf7YlrhRfdYLwO73Kjb1/X+aW5npHx3X/rSN+52V7pOn+OWcaEfzTPGB2+AjUd7neLd16Ht8daHR6JjHnCF2OQDt+DUXGtW337qOnw56jr8EW3+cZ1gz/GcHOmqmeHITrHe2C0zvPhyOsin4luXeaH0H8P42/3fJDVNW65w98T4jhPQLfu4fnIxBheh8k6fMRdfvd0+GeYp7N3+/vnfHuu6zz8Xveii7wOhZj/PutEXuf5cIyOMXwd6jp86P3uV4fPQPq2NfCLGKGbvOwB9zLc+/CgP7sxzPFczTPEUN3DazFNZ//pz3qM1XUe/JA16zx/jFm6++GOtOVCf6brIvd/xPp1gWdjjK7ywEWuEfPzaxgV8zzq9wNLdfgerNThOxf7HmNtj7l39IvxfDgGxbX4TAzQZd7scfsz3Bj+PYbrKv9xib3S2Sf9nmCiLvBklHSZ12OK7n7K+/wv30Ac50fqvlmde9q7HMScfNQz3lUd/ghNHd7z3577nu6RT1xqbTq8+3/ssw4fjDG6xqtR0mmZdxJTdI6PQlmX+HHM1g3e61n7rwv8FKbrJrcv9z3qLA/GRF3lJ7A=
*/