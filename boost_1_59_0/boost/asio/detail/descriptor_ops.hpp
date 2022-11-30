//
// detail/descriptor_ops.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/detail/cstdint.hpp>
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

inline void get_last_error(
    boost::system::error_code& ec, bool is_error_condition)
{
  if (!is_error_condition)
  {
    ec.assign(0, ec.category());
  }
  else
  {
    ec = boost::system::error_code(errno,
        boost::asio::error::get_system_category());
  }
}

BOOST_ASIO_DECL int open(const char* path, int flags,
    boost::system::error_code& ec);

BOOST_ASIO_DECL int open(const char* path, int flags, unsigned mode,
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

BOOST_ASIO_DECL std::size_t sync_read1(int d, state_type state, void* data,
    std::size_t size, boost::system::error_code& ec);

BOOST_ASIO_DECL bool non_blocking_read(int d, buf* bufs, std::size_t count,
    boost::system::error_code& ec, std::size_t& bytes_transferred);

BOOST_ASIO_DECL bool non_blocking_read1(int d, void* data, std::size_t size,
    boost::system::error_code& ec, std::size_t& bytes_transferred);

BOOST_ASIO_DECL std::size_t sync_write(int d, state_type state,
    const buf* bufs, std::size_t count, bool all_empty,
    boost::system::error_code& ec);

BOOST_ASIO_DECL std::size_t sync_write1(int d, state_type state,
    const void* data, std::size_t size, boost::system::error_code& ec);

BOOST_ASIO_DECL bool non_blocking_write(int d,
    const buf* bufs, std::size_t count,
    boost::system::error_code& ec, std::size_t& bytes_transferred);

BOOST_ASIO_DECL bool non_blocking_write1(int d,
    const void* data, std::size_t size,
    boost::system::error_code& ec, std::size_t& bytes_transferred);

#if defined(BOOST_ASIO_HAS_FILE)

BOOST_ASIO_DECL std::size_t sync_read_at(int d, state_type state,
    uint64_t offset, buf* bufs, std::size_t count, bool all_empty,
    boost::system::error_code& ec);

BOOST_ASIO_DECL std::size_t sync_read_at1(int d, state_type state,
    uint64_t offset, void* data, std::size_t size,
    boost::system::error_code& ec);

BOOST_ASIO_DECL bool non_blocking_read_at(int d, uint64_t offset,
    buf* bufs, std::size_t count, boost::system::error_code& ec,
    std::size_t& bytes_transferred);

BOOST_ASIO_DECL bool non_blocking_read_at1(int d, uint64_t offset,
    void* data, std::size_t size, boost::system::error_code& ec,
    std::size_t& bytes_transferred);

BOOST_ASIO_DECL std::size_t sync_write_at(int d, state_type state,
    uint64_t offset, const buf* bufs, std::size_t count, bool all_empty,
    boost::system::error_code& ec);

BOOST_ASIO_DECL std::size_t sync_write_at1(int d, state_type state,
    uint64_t offset, const void* data, std::size_t size,
    boost::system::error_code& ec);

BOOST_ASIO_DECL bool non_blocking_write_at(int d,
    uint64_t offset, const buf* bufs, std::size_t count,
    boost::system::error_code& ec, std::size_t& bytes_transferred);

BOOST_ASIO_DECL bool non_blocking_write_at1(int d,
    uint64_t offset, const void* data, std::size_t size,
    boost::system::error_code& ec, std::size_t& bytes_transferred);

#endif // defined(BOOST_ASIO_HAS_FILE)

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