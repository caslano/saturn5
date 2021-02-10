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
q+IMsqUaRspWSyi3YshYwVCvh1MGgzflGzurScPIVLnifFAbX5DjGOeYaOd6gHEFH5Ny/SrTMjA3pDDSsy9/eVK0uKvJ1HjQJju7yny1kcjGJjDuao/m/che5ERJ/hEFDP77RxFfODFnA2DzoBc6ZGGM1z2oGNoJ4BpOkO/ArULFmrZD0CQyyrsbx8rnqL7uSoVR2Sy7q2e+pLCJ6EnBGbbV2U3BSRp4sPNReocWpX1r+mqEkJTQDafoLcaW6X4VztjBfYOuGLDgbpbdWwXG+7fQF3rAmTj04AnDu8MAok6wFm0JAW6GJUFuQ14Pr4QUeMP4GHBe7GYIqenQNsuueRq7y/B83Q4glO8ljZbBJZpqlLG+Ew7sUe0/D3lTvTm5yLEfnT1l3WmVnjCeFI2YIWd+TmZ5UgXH1z+9cSFhDhmDTe0xs8wILm4Q8NBo9QqjFIq/Tu5VbpeiQIEdNQ+drlRmK6ZPClfiAdZ4PVoVSzcc74UuIZMYhJMmK8x6nVzB5RCJLJC669UWayJMMhTXyogp3r8rOXUfLGM3q3LtbAH1OJy5DL9WKEK7L34+fKiFf3dv6TALSddudPV4e3tz83wxvVmcFGEq/D2Z/bZYthCelUwBS5FCw6Cj7+yG5lEAr6qRNrFFeRSwthJJ
*/