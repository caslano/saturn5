//
// detail/pipe_select_interrupter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_PIPE_SELECT_INTERRUPTER_HPP
#define BOOST_ASIO_DETAIL_PIPE_SELECT_INTERRUPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS)
#if !defined(BOOST_ASIO_WINDOWS_RUNTIME)
#if !defined(__CYGWIN__)
#if !defined(__SYMBIAN32__)
#if !defined(BOOST_ASIO_HAS_EVENTFD)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class pipe_select_interrupter
{
public:
  // Constructor.
  BOOST_ASIO_DECL pipe_select_interrupter();

  // Destructor.
  BOOST_ASIO_DECL ~pipe_select_interrupter();

  // Recreate the interrupter's descriptors. Used after a fork.
  BOOST_ASIO_DECL void recreate();

  // Interrupt the select call.
  BOOST_ASIO_DECL void interrupt();

  // Reset the select interrupter. Returns true if the reset was successful.
  BOOST_ASIO_DECL bool reset();

  // Get the read descriptor to be passed to select.
  int read_descriptor() const
  {
    return read_descriptor_;
  }

private:
  // Open the descriptors. Throws on error.
  BOOST_ASIO_DECL void open_descriptors();

  // Close the descriptors.
  BOOST_ASIO_DECL void close_descriptors();

  // The read end of a connection used to interrupt the select call. This file
  // descriptor is passed to select such that when it is time to stop, a single
  // byte will be written on the other end of the connection and this
  // descriptor will become readable.
  int read_descriptor_;

  // The write end of a connection used to interrupt the select call. A single
  // byte may be written to this to wake up the select which is waiting for the
  // other end to become readable.
  int write_descriptor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/pipe_select_interrupter.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // !defined(BOOST_ASIO_HAS_EVENTFD)
#endif // !defined(__SYMBIAN32__)
#endif // !defined(__CYGWIN__)
#endif // !defined(BOOST_ASIO_WINDOWS_RUNTIME)
#endif // !defined(BOOST_ASIO_WINDOWS)

#endif // BOOST_ASIO_DETAIL_PIPE_SELECT_INTERRUPTER_HPP

/* pipe_select_interrupter.hpp
8FeoZvnxaDMGFlg1JFxdNn9KE8mR/H+v8GwyOFXKhfRxzlWi/7BqLCW87p4tzjuADYHz2FBhurgRhWPO789CHLHaGmCMoQnCfZapAIM0/1IFsUJUc9qCzmjQRyBrQXoLzzTPRFYcKrVgDfbnevcr9qVjhyCj+Z9sbejAeZH96c/6Nk2cJv0NsSmyRHa2HxZ7M8GYfx7LQj9XckmGTFtK4c/FkLBEK/EEoNxslODWCF2G8gn4yB9mZTgG6TDCmzhtehS+5AaMB96pR8uKiFZnfWuy9AHp+xgnIe1Vx6atgDb5C+qadhwiaGkeE7TdcYKw7HtQKH4Qwq4kwqX2zqLaCBopS6JVAzkW4wHSKkX2iYlX8D1va3N4fKPTVWhjf4aGm3mbZN6NFQ26qUHPID1qeLo5/8buVTw+aUf1gL9bvhTyqkZ6MWLvgMxjUwu6qxUJAAPqtkZoEw0uIbDEeiJSwnt0NGCxEdHEYc5sQYeeBPJxb/lRAawfLkrAlbWX2dTkT5nob418UVVQQEoY2Orm/PpPpLYx4Pj1iCrQwC5lzQkfpJk4JZqmYMPhJQ==
*/