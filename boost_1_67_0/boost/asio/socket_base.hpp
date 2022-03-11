//
// socket_base.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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