//
// detail/descriptor_ops.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_DESCRIPTOR_OPS_HPP
#define BOOST_ASIO_DETAIL_DESCRIPTOR_OPS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS) \
  && !defined(BOOST_ASIO_WINDOWS_RUNTIME) \
  && !defined(__CYGWIN__)

#include <cstddef>
#include <boost/asio/error.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {
namespace descriptor_ops {

// Descriptor state bits.
enum
{
  // The user wants a non-blocking descriptor.
  user_set_non_blocking = 1,

  // The descriptor has been set non-blocking.
  internal_non_blocking = 2,

  // Helper "state" used to determine whether the descriptor is non-blocking.
  non_blocking = user_set_non_blocking | internal_non_blocking,

  // The descriptor may have been dup()-ed.
  possible_dup = 4
};

typedef unsigned char state_type;

template <typename ReturnType>
inline ReturnType error_wrapper(ReturnType return_value,
    boost::system::error_code& ec)
{
  ec = boost::system::error_code(errno,
      boost::asio::error::get_system_category());
  return return_value;
}

BOOST_ASIO_DECL int open(const char* path, int flags,
    boost::system::error_code& ec);

BOOST_ASIO_DECL int close(int d, state_type& state,
    boost::system::error_code& ec);

BOOST_ASIO_DECL bool set_user_non_blocking(int d,
    state_type& state, bool value, boost::system::error_code& ec);

BOOST_ASIO_DECL bool set_internal_non_blocking(int d,
    state_type& state, bool value, boost::system::error_code& ec);

typedef iovec buf;

BOOST_ASIO_DECL std::size_t sync_read(int d, state_type state, buf* bufs,
    std::size_t count, bool all_empty, boost::system::error_code& ec);

BOOST_ASIO_DECL bool non_blocking_read(int d, buf* bufs, std::size_t count,
    boost::system::error_code& ec, std::size_t& bytes_transferred);

BOOST_ASIO_DECL std::size_t sync_write(int d, state_type state,
    const buf* bufs, std::size_t count, bool all_empty,
    boost::system::error_code& ec);

BOOST_ASIO_DECL bool non_blocking_write(int d,
    const buf* bufs, std::size_t count,
    boost::system::error_code& ec, std::size_t& bytes_transferred);

BOOST_ASIO_DECL int ioctl(int d, state_type& state, long cmd,
    ioctl_arg_type* arg, boost::system::error_code& ec);

BOOST_ASIO_DECL int fcntl(int d, int cmd, boost::system::error_code& ec);

BOOST_ASIO_DECL int fcntl(int d, int cmd,
    long arg, boost::system::error_code& ec);

BOOST_ASIO_DECL int poll_read(int d,
    state_type state, boost::system::error_code& ec);

BOOST_ASIO_DECL int poll_write(int d,
    state_type state, boost::system::error_code& ec);

BOOST_ASIO_DECL int poll_error(int d,
    state_type state, boost::system::error_code& ec);

} // namespace descriptor_ops
} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/descriptor_ops.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // !defined(BOOST_ASIO_WINDOWS)
       //   && !defined(BOOST_ASIO_WINDOWS_RUNTIME)
       //   && !defined(__CYGWIN__)

#endif // BOOST_ASIO_DETAIL_DESCRIPTOR_OPS_HPP

/* descriptor_ops.hpp
g04EHRvG80d4w7S/0EB0CYJaFyh0uB4/dwaUPt6PU14ldoz47T4k8MBrY2IrdjzNLqBUO6Qw47qQgCNaRadqjYliLXlfCkx0iRwJWKM5FWXCEHXhb/h6Zab+wKosMcJAX3+62VvS0wVobtFAjOmoqWE45zMQzWZQkAjTIGkijG1KxGMQY53XyqjHNiX2ifXRNYz0jvZiWPCliERdzWDJMDFU7gKxKqfQKqfYqryCSXyOHSOXhLeAz8manzF8Mj6+Gx/7eMRGj5FaFEKITblFR4fXjkTbcgvijnhQwrO2uPMNjbRMXyfW3MxsBuAamUaYMSkwSyU3xyeLJZz/TTpe5Vwed/UrFodhr5QNKnwhNJwzJo3LGzjD4VafqUS+DgVEqU2V0OD5/GwejQlkVo7wNWX3GmdcvXg7ko2dZBhhVIeYZ9KuSQqIOXgOA7dAEA/CTlviBhwqjj8BTqCFyUbT7GRo0wLigcniXJhf63QRfceN1yQ2zCBgp9LY23D81RQmiQFwgSzXghDlDgT4nIFIr2QZFnbFncwc2RJxuqW5zt0K8j0t6OA7Qb7vBB18B3zeLAheePyQJZ0T+LpBshJh8lVMyjkYulJsMFo2rXcZrgBxOIeOQ7AlwGhYTDCvPkG+PkEnfYJ8fQJbn+QEkMBSsZ4tF0dDrU92p59SCHpJGiEvTmZtbuzwNYf4hYeYUSLLIOJvsnPqa7gmHTlC6gIgc3b3WQku4xi6G7t+Tdl57KqgRA/ev02gHkx3OmcEViV4v7IHFWXhXN9jbE89TcP/DYDVMYM3xYppjIpjbM1aTbpmDDqaMcgzY+CaEZSTxxxuEG7deeMPOh7+zmyhOIlzQwU9QRyr1lFD0rDez2VnJT6NWysn62F8OMaWUAO8NRbGGs3o1V9zWP0zABNBo/JELQPaOp9ZRajNjngLAh/xwT0uowdJtNQZ3V6Gkfb/yJSpCO8sWX1LXozVGG9ot8CiIhxXDB4xN3RvTeIbJJW4UU3qhU9T7YxFMCE0gI/aGoUQr8jYDNzbptAfm0KFmgr+XwsH/4+Fg//DwsiTPo5VKTuV/Z8ZrQpbDXdAglzjB7GpkzhULfdgP9zKMEA9oMFEu8N2tdaqxgOLidM/iE39+Ib0spTJYBnK4mgoh1YMDg2EU0gnw4fC4oeREhrRsZrkwfQpw6UQOnAuDj+ylgpwFsym53LaOL5WH9PxZYMUQeskjR7imlMW4WiUhQN9WTTaO9RvYCNz/CKJy8RXn1xBYFDQG4G1bpLoUXpfNhXoEAztc1ko5tLojcumvXJ5uxJYtbE1X5vqFKQuE/fcFehO6vUhQ8VDltcWRE3dlF6SNQEvMhCmRW5FtaJRT3R3eW6RwaKRFnAyYGHpJMeqXjFwZYvRwCwKhqtsGAI7S2KrzZMBI9FZGtii3ObmbcmtBm+KZTEu3mDVSx6Rz7UvlMQT/qXwj9FCOJ3NUcMYJZYKrZyEnVi/ICsz9wGaj5d8m7ZVTWQ6NGXMB7crZ43brEwhHmIGY5rZFOaYzWGC2VQ4u1wypywenEAz+XR+djSXR+c3CUGnZpNolC/DGlTDgTBPqCezK7OcsnOefHEnnTrq00mXF9QjT4eZxqa0ASywGBcDwYwaYhQyKDG+xkZmq1ug3MAPMj/wZ/feLmVoaa4FLm1o7a4FLp9Xie6NK0qHwxVZI9IxS0eptbwHnRcnyFxN3BUn6LziBPYCExgLTNBpgQleaEEJ5l1QtPwFQ21grjzA81g417L5Mbldd6MfyJz4B9aNgCCtGOjSTg3uxIekwwyH5AXmOHJ0nuXp4W90dG5DGn0HKfQKi9qUcNExL2K7gKNU7IwOUah3gQpHy82IZTA=
*/