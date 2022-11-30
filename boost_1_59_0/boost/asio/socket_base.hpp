//
// socket_base.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SOCKET_BASE_HPP
#define BOOST_ASIO_SOCKET_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/io_control.hpp>
#include <boost/asio/detail/socket_option.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// The socket_base class is used as a base for the basic_stream_socket and
/// basic_datagram_socket class templates so that we have a common place to
/// define the shutdown_type and enum.
class socket_base
{
public:
  /// Different ways a socket may be shutdown.
  enum shutdown_type
  {
#if defined(GENERATING_DOCUMENTATION)
    /// Shutdown the receive side of the socket.
    shutdown_receive = implementation_defined,

    /// Shutdown the send side of the socket.
    shutdown_send = implementation_defined,

    /// Shutdown both send and receive on the socket.
    shutdown_both = implementation_defined
#else
    shutdown_receive = BOOST_ASIO_OS_DEF(SHUT_RD),
    shutdown_send = BOOST_ASIO_OS_DEF(SHUT_WR),
    shutdown_both = BOOST_ASIO_OS_DEF(SHUT_RDWR)
#endif
  };

  /// Bitmask type for flags that can be passed to send and receive operations.
  typedef int message_flags;

#if defined(GENERATING_DOCUMENTATION)
  /// Peek at incoming data without removing it from the input queue.
  static const int message_peek = implementation_defined;

  /// Process out-of-band data.
  static const int message_out_of_band = implementation_defined;

  /// Specify that the data should not be subject to routing.
  static const int message_do_not_route = implementation_defined;

  /// Specifies that the data marks the end of a record.
  static const int message_end_of_record = implementation_defined;
#else
  BOOST_ASIO_STATIC_CONSTANT(int,
      message_peek = BOOST_ASIO_OS_DEF(MSG_PEEK));
  BOOST_ASIO_STATIC_CONSTANT(int,
      message_out_of_band = BOOST_ASIO_OS_DEF(MSG_OOB));
  BOOST_ASIO_STATIC_CONSTANT(int,
      message_do_not_route = BOOST_ASIO_OS_DEF(MSG_DONTROUTE));
  BOOST_ASIO_STATIC_CONSTANT(int,
      message_end_of_record = BOOST_ASIO_OS_DEF(MSG_EOR));
#endif

  /// Wait types.
  /**
   * For use with basic_socket::wait() and basic_socket::async_wait().
   */
  enum wait_type
  {
    /// Wait for a socket to become ready to read.
    wait_read,

    /// Wait for a socket to become ready to write.
    wait_write,

    /// Wait for a socket to have error conditions pending.
    wait_error
  };

  /// Socket option to permit sending of broadcast messages.
  /**
   * Implements the SOL_SOCKET/SO_BROADCAST socket option.
   *
   * @par Examples
   * Setting the option:
   * @code
   * boost::asio::ip::udp::socket socket(my_context);
   * ...
   * boost::asio::socket_base::broadcast option(true);
   * socket.set_option(option);
   * @endcode
   *
   * @par
   * Getting the current option value:
   * @code
   * boost::asio::ip::udp::socket socket(my_context);
   * ...
   * boost::asio::socket_base::broadcast option;
   * socket.get_option(option);
   * bool is_set = option.value();
   * @endcode
   *
   * @par Concepts:
   * Socket_Option, Boolean_Socket_Option.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined broadcast;
#else
  typedef boost::asio::detail::socket_option::boolean<
    BOOST_ASIO_OS_DEF(SOL_SOCKET), BOOST_ASIO_OS_DEF(SO_BROADCAST)>
      broadcast;
#endif

  /// Socket option to enable socket-level debugging.
  /**
   * Implements the SOL_SOCKET/SO_DEBUG socket option.
   *
   * @par Examples
   * Setting the option:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::socket_base::debug option(true);
   * socket.set_option(option);
   * @endcode
   *
   * @par
   * Getting the current option value:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::socket_base::debug option;
   * socket.get_option(option);
   * bool is_set = option.value();
   * @endcode
   *
   * @par Concepts:
   * Socket_Option, Boolean_Socket_Option.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined debug;
#else
  typedef boost::asio::detail::socket_option::boolean<
    BOOST_ASIO_OS_DEF(SOL_SOCKET), BOOST_ASIO_OS_DEF(SO_DEBUG)> debug;
#endif

  /// Socket option to prevent routing, use local interfaces only.
  /**
   * Implements the SOL_SOCKET/SO_DONTROUTE socket option.
   *
   * @par Examples
   * Setting the option:
   * @code
   * boost::asio::ip::udp::socket socket(my_context);
   * ...
   * boost::asio::socket_base::do_not_route option(true);
   * socket.set_option(option);
   * @endcode
   *
   * @par
   * Getting the current option value:
   * @code
   * boost::asio::ip::udp::socket socket(my_context);
   * ...
   * boost::asio::socket_base::do_not_route option;
   * socket.get_option(option);
   * bool is_set = option.value();
   * @endcode
   *
   * @par Concepts:
   * Socket_Option, Boolean_Socket_Option.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined do_not_route;
#else
  typedef boost::asio::detail::socket_option::boolean<
    BOOST_ASIO_OS_DEF(SOL_SOCKET), BOOST_ASIO_OS_DEF(SO_DONTROUTE)>
      do_not_route;
#endif

  /// Socket option to send keep-alives.
  /**
   * Implements the SOL_SOCKET/SO_KEEPALIVE socket option.
   *
   * @par Examples
   * Setting the option:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::socket_base::keep_alive option(true);
   * socket.set_option(option);
   * @endcode
   *
   * @par
   * Getting the current option value:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::socket_base::keep_alive option;
   * socket.get_option(option);
   * bool is_set = option.value();
   * @endcode
   *
   * @par Concepts:
   * Socket_Option, Boolean_Socket_Option.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined keep_alive;
#else
  typedef boost::asio::detail::socket_option::boolean<
    BOOST_ASIO_OS_DEF(SOL_SOCKET), BOOST_ASIO_OS_DEF(SO_KEEPALIVE)> keep_alive;
#endif

  /// Socket option for the send buffer size of a socket.
  /**
   * Implements the SOL_SOCKET/SO_SNDBUF socket option.
   *
   * @par Examples
   * Setting the option:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::socket_base::send_buffer_size option(8192);
   * socket.set_option(option);
   * @endcode
   *
   * @par
   * Getting the current option value:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::socket_base::send_buffer_size option;
   * socket.get_option(option);
   * int size = option.value();
   * @endcode
   *
   * @par Concepts:
   * Socket_Option, Integer_Socket_Option.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined send_buffer_size;
#else
  typedef boost::asio::detail::socket_option::integer<
    BOOST_ASIO_OS_DEF(SOL_SOCKET), BOOST_ASIO_OS_DEF(SO_SNDBUF)>
      send_buffer_size;
#endif

  /// Socket option for the send low watermark.
  /**
   * Implements the SOL_SOCKET/SO_SNDLOWAT socket option.
   *
   * @par Examples
   * Setting the option:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::socket_base::send_low_watermark option(1024);
   * socket.set_option(option);
   * @endcode
   *
   * @par
   * Getting the current option value:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::socket_base::send_low_watermark option;
   * socket.get_option(option);
   * int size = option.value();
   * @endcode
   *
   * @par Concepts:
   * Socket_Option, Integer_Socket_Option.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined send_low_watermark;
#else
  typedef boost::asio::detail::socket_option::integer<
    BOOST_ASIO_OS_DEF(SOL_SOCKET), BOOST_ASIO_OS_DEF(SO_SNDLOWAT)>
      send_low_watermark;
#endif

  /// Socket option for the receive buffer size of a socket.
  /**
   * Implements the SOL_SOCKET/SO_RCVBUF socket option.
   *
   * @par Examples
   * Setting the option:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::socket_base::receive_buffer_size option(8192);
   * socket.set_option(option);
   * @endcode
   *
   * @par
   * Getting the current option value:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::socket_base::receive_buffer_size option;
   * socket.get_option(option);
   * int size = option.value();
   * @endcode
   *
   * @par Concepts:
   * Socket_Option, Integer_Socket_Option.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined receive_buffer_size;
#else
  typedef boost::asio::detail::socket_option::integer<
    BOOST_ASIO_OS_DEF(SOL_SOCKET), BOOST_ASIO_OS_DEF(SO_RCVBUF)>
      receive_buffer_size;
#endif

  /// Socket option for the receive low watermark.
  /**
   * Implements the SOL_SOCKET/SO_RCVLOWAT socket option.
   *
   * @par Examples
   * Setting the option:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::socket_base::receive_low_watermark option(1024);
   * socket.set_option(option);
   * @endcode
   *
   * @par
   * Getting the current option value:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::socket_base::receive_low_watermark option;
   * socket.get_option(option);
   * int size = option.value();
   * @endcode
   *
   * @par Concepts:
   * Socket_Option, Integer_Socket_Option.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined receive_low_watermark;
#else
  typedef boost::asio::detail::socket_option::integer<
    BOOST_ASIO_OS_DEF(SOL_SOCKET), BOOST_ASIO_OS_DEF(SO_RCVLOWAT)>
      receive_low_watermark;
#endif

  /// Socket option to allow the socket to be bound to an address that is
  /// already in use.
  /**
   * Implements the SOL_SOCKET/SO_REUSEADDR socket option.
   *
   * @par Examples
   * Setting the option:
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::socket_base::reuse_address option(true);
   * acceptor.set_option(option);
   * @endcode
   *
   * @par
   * Getting the current option value:
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::socket_base::reuse_address option;
   * acceptor.get_option(option);
   * bool is_set = option.value();
   * @endcode
   *
   * @par Concepts:
   * Socket_Option, Boolean_Socket_Option.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined reuse_address;
#else
  typedef boost::asio::detail::socket_option::boolean<
    BOOST_ASIO_OS_DEF(SOL_SOCKET), BOOST_ASIO_OS_DEF(SO_REUSEADDR)>
      reuse_address;
#endif

  /// Socket option to specify whether the socket lingers on close if unsent
  /// data is present.
  /**
   * Implements the SOL_SOCKET/SO_LINGER socket option.
   *
   * @par Examples
   * Setting the option:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::socket_base::linger option(true, 30);
   * socket.set_option(option);
   * @endcode
   *
   * @par
   * Getting the current option value:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::socket_base::linger option;
   * socket.get_option(option);
   * bool is_set = option.enabled();
   * unsigned short timeout = option.timeout();
   * @endcode
   *
   * @par Concepts:
   * Socket_Option, Linger_Socket_Option.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined linger;
#else
  typedef boost::asio::detail::socket_option::linger<
    BOOST_ASIO_OS_DEF(SOL_SOCKET), BOOST_ASIO_OS_DEF(SO_LINGER)>
      linger;
#endif

  /// Socket option for putting received out-of-band data inline.
  /**
   * Implements the SOL_SOCKET/SO_OOBINLINE socket option.
   *
   * @par Examples
   * Setting the option:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::socket_base::out_of_band_inline option(true);
   * socket.set_option(option);
   * @endcode
   *
   * @par
   * Getting the current option value:
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::socket_base::out_of_band_inline option;
   * socket.get_option(option);
   * bool value = option.value();
   * @endcode
   *
   * @par Concepts:
   * Socket_Option, Boolean_Socket_Option.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined out_of_band_inline;
#else
  typedef boost::asio::detail::socket_option::boolean<
    BOOST_ASIO_OS_DEF(SOL_SOCKET), BOOST_ASIO_OS_DEF(SO_OOBINLINE)>
      out_of_band_inline;
#endif

  /// Socket option to report aborted connections on accept.
  /**
   * Implements a custom socket option that determines whether or not an accept
   * operation is permitted to fail with boost::asio::error::connection_aborted.
   * By default the option is false.
   *
   * @par Examples
   * Setting the option:
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::socket_base::enable_connection_aborted option(true);
   * acceptor.set_option(option);
   * @endcode
   *
   * @par
   * Getting the current option value:
   * @code
   * boost::asio::ip::tcp::acceptor acceptor(my_context);
   * ...
   * boost::asio::socket_base::enable_connection_aborted option;
   * acceptor.get_option(option);
   * bool is_set = option.value();
   * @endcode
   *
   * @par Concepts:
   * Socket_Option, Boolean_Socket_Option.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined enable_connection_aborted;
#else
  typedef boost::asio::detail::socket_option::boolean<
    boost::asio::detail::custom_socket_option_level,
    boost::asio::detail::enable_connection_aborted_option>
    enable_connection_aborted;
#endif

  /// IO control command to get the amount of data that can be read without
  /// blocking.
  /**
   * Implements the FIONREAD IO control command.
   *
   * @par Example
   * @code
   * boost::asio::ip::tcp::socket socket(my_context);
   * ...
   * boost::asio::socket_base::bytes_readable command(true);
   * socket.io_control(command);
   * std::size_t bytes_readable = command.get();
   * @endcode
   *
   * @par Concepts:
   * IO_Control_Command, Size_IO_Control_Command.
   */
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined bytes_readable;
#else
  typedef boost::asio::detail::io_control::bytes_readable bytes_readable;
#endif

  /// The maximum length of the queue of pending incoming connections.
#if defined(GENERATING_DOCUMENTATION)
  static const int max_listen_connections = implementation_defined;
#else
  BOOST_ASIO_STATIC_CONSTANT(int, max_listen_connections
      = BOOST_ASIO_OS_DEF(SOMAXCONN));
#endif

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use max_listen_connections.) The maximum length of the queue
  /// of pending incoming connections.
#if defined(GENERATING_DOCUMENTATION)
  static const int max_connections = implementation_defined;
#else
  BOOST_ASIO_STATIC_CONSTANT(int, max_connections
      = BOOST_ASIO_OS_DEF(SOMAXCONN));
#endif
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

protected:
  /// Protected destructor to prevent deletion through this type.
  ~socket_base()
  {
  }
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SOCKET_BASE_HPP

/* socket_base.hpp
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
*/