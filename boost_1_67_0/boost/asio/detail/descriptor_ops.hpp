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
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
*/