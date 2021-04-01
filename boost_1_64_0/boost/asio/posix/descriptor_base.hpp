//
// posix/descriptor_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_POSIX_DESCRIPTOR_BASE_HPP
#define BOOST_ASIO_POSIX_DESCRIPTOR_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/io_control.hpp>
#include <boost/asio/detail/socket_option.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace posix {

/// The descriptor_base class is used as a base for the descriptor class as a
/// place to define the associated IO control commands.
class descriptor_base
{
public:
  /// Wait types.
  /**
   * For use with descriptor::wait() and descriptor::async_wait().
   */
  enum wait_type
  {
    /// Wait for a descriptor to become ready to read.
    wait_read,

    /// Wait for a descriptor to become ready to write.
    wait_write,

    /// Wait for a descriptor to have error conditions pending.
    wait_error
  };

  /// IO control command to get the amount of data that can be read without
  /// blocking.
  /**
   * Implements the FIONREAD IO control command.
   *
   * @par Example
   * @code
   * boost::asio::posix::stream_descriptor descriptor(my_context);
   * ...
   * boost::asio::descriptor_base::bytes_readable command(true);
   * descriptor.io_control(command);
   * std::size_t bytes_readable = command.get();
   * @endcode
   *
   * @par Concepts:
   * IoControlCommand.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined bytes_readable;
#else
  typedef boost::asio::detail::io_control::bytes_readable bytes_readable;
#endif

protected:
  /// Protected destructor to prevent deletion through this type.
  ~descriptor_base()
  {
  }
};

} // namespace posix
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_POSIX_DESCRIPTOR_BASE_HPP

/* descriptor_base.hpp
YklMJhZGAvvQxXW913GT3Pl9TNri/0jAdb9cHLLMCeeEa1QqOIX8os6A0u4OfAstV2L0s5rUQEK0mkdQWCdvg5I0c4ll9OntqbYrwfggDbgSX+P3LppSNPvvvsfFSe2xRuijtWHxfRVgHQkCIdltm9CR31dK32inxCuUCGh7FiAlplKJFuLW9It4ie5weB0lt9YJrKWk1u7GELeQmgRZSAkxgJhWmrlcEC92gPw/BZMxuQKJCJ+psqX2IsjUmU+UWlvAybv6LkEaCqckpO1hpMTloCNP1yCCYtA2NgpjaP1zI3N0l5AcasVOtsKppJaCXPdRwpepZFK+MefUbaF+x+8vUu4DHTYZN0jwzleXHExrRaQeerMRYBbrtGRmwzI9idS0kI5x6oGufRDK1ZN/siMlTw+g2+W7TO5ke2YV+3XP8OciKsq/WO9mm6wd2Fbhksv4h3YpZA5qu8neAAp4wezu+DrhVuSejqOq0mBelAeIdGg6Q8k26/go2soFMOMdLAPzF0oHf+4PVc7hNjLkR5/KPc+GNoyPiV5XMv94z3ObTlfHoe/uaG9DXg==
*/