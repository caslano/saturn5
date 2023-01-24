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
KDXyYdI4UShQ4wYLlbjBIoy3HBHPTIEqMjCehg3WIi31iJfDBo+4wmxkT6tfiRt8F/WVG2jcYFVAOOIgV//oV3wzeHsPbU4LDo1TnTafUfL9jL7+JPgaPaE0bvAJG3m23h8glT00cYNV5D+/tAbjBp+wycPWxA1WBeIMr9K4QReNGzyiJuXqyTzKcuDgzu/9AQfZDv9ibNvfv6cQk/k9lMDBB5XcX0gHR2zk6p+VWQkNHLxLDRw8Qu6DXpzkLtpzjtzzXNozDRw8ogQO/l2krE20foYE8Heq+OWmRpoLWU7zrRgV4TVMN29Pb3f7F/AJbv9YbcIvJxGTVITxNFywiizrzcIFF/cODRecDYU2J3EGW0xVwgXFk63M6TlEg0o1XPBdDBdEVAKH8MXAs2T9rGEijRN8Fwe7+gQOdvkJitT8rQ6y+AQb8V30VUAoDo0TfDpwlLSZ1TjBzSxO8AkWJ5gB/EgnCXvsZHE6DRSsAMN6wc4tsGzQ71wBDHrah1t4E11pbsyujm92bqGRgtvIwzdcGCk4d34rmqc7YJ1/fsbPjNMEDrM/JUCFp5+ul/lpSgf++oW/Q/wP4ZqDRyKCYWeDQt6qlY2dvzYpr0FSWVphNb132h8aiVcXo/LewE86ORLvrmlqCNbCaWqcWJb8liw83hIaiZeslNT1VyLxEqYpkXi24y2dROLdB4DQSLzmDPVbs+ta1Ei8ruTQ
*/