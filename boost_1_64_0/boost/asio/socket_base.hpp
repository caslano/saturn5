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
czROI1mDyqDH76z0FcPE+HCJm+nEuB7C2Bu0x94aCxXfdoX9bd3y28I1FO4FoXQ1BwLUeZZB3wRt+Ywqn2FirMg1APzmZQbtfLlBt6k0DJNtyH8929077LgoHZeNYh7EMQ9i1Dog5oEcv6iTOVa7sQO6GHTcZ/U247ji1Zn3JOk9w/V0Nebdpdm51IR5HC1jJhfttszr83g8TdvPNujpjRjfMn8Qx4y5UZqbjdPcXvz21Jbk+JVj0Z7PEXwHfnvEd8gw+cvHYEuAWnrilfW3eK5Bj4EW3aXqwTDF/wbsOWGnjVHxIoP+Ddqg0jKM8U45xvaZvIa1ixlvsoWiw83UN2zQFaBbVb4uGPgG4pPP+JV5uiAEHttA4XKwEOi3x8ZmWYdlcVo2WUsLJ+po3nCa5uTqKdrbQn3ngYeCFo1V8meYyH+HyU9D1Hh/pBwqmbNImxsTSRrBg0x7QFeOaWOK43KMDM+hxW80aD1oTJXLMNFu4+DT2QZ60ZBBOVD6c6qNzPwJeU0vO2qHIa0ZTkg/PQ5Nwzz53wLUI9tEc/aFBx392hSkpmHUr3cOdW41KAu65HMqf45xGbT/LQZ9FTReSYNAhtsyRhzyBdqst4EWj1bki0HVnvWUhtXqu0D7VfkME/mzuFVllBVJWpFrohXZRlqB71yx0ymBGgGDAoPIe0mUlmCt6xoOUjJbAz4ToP6rDdoGunlnpV/s9RBxCHHINQ4xjK1To3Ley/kXY3M3SoNXGTQCarxb+25XnBimeAnnNZ7rx8o41tlW6ngwXQYXK8YL0XxkMNwv556SvyB3ZfGLtu3qkfKXXK8h4yNMrtdKrqxHv9eh3yFfDsl+19OBshF7X9Bj45klkHmMDhKz1KpHQY7Xw8J02EQbLRyfizHTTt3vxreDlt2jzc3exRZ2wjaD1kkc5IKx9D7Wdke/QR7sCWvfksK3JPEtaIsh8S3tNt8xvwH/aXIe1ja0lVzfeP68D+V6sP3DBj0M6v28Ni5mgYv8BZ9XYwHXhGb1/ZmuEDXslVKp/X2DPA+zjfCdso3kPqV/h0E3gMp6Xd3wVJBS2BOEMD6eBJ76uEGtX1B954KxPET7Dcn5pq/NQbR/RK3LfK3m34Ew/h1jnzDo96BdX3B8B8e923BZlJohh8TKkZJoSbmn8NwPZOYHKIU0Mp6Si+upedTcLwk+0hCmhqk0xSfr0H61uJyANQm04YuqrRTmf48wchfWbNB2LR+OGW1RajP3cEPYw5VEnWS7Ye0ufQXz8F7ItYgvcdTRwr4Iol0qbzeMpzdwK2nBcB0tQB4LsD9YMNRUnlOqLyi5N0l9uwz6LWiDyodhbnM8hH5fCnlkgZKjM0HKgL9Es0uoWDDoUdDYLq3/EcZx4/YE3T4epB3ZBL1wOIl9k5I/qsqL1rqG9SyH9QzzYCHCFvaIdW1OwByT3YbPOTt9v2OOpYXV45v1exD1k/timZ6P58Nj1Gmso0Q5VpJaFinDpQPamOayfSZKGfRbZiBZjpfstcexD58XhbyXonnox3ngrfOG6ku+9BbWvKjDvLD2i/2V8YA0gz8y6Cug/JfVeOCY1h/V+cQm1R+SV3c+atAxoJJWBsdkGr6e8P1O316DXgta+RVtrM0CF/lNL2djlDay/Zb7d0oZAPoXjOOu3rjUwThlqNog1QrZafvvsD8EPSLqYLdL0MJ+C5qUOMgN4+nBs531sdrGIKPBoAbs8eRvZmGI6o1mCubV2rTdoadpp8I/DFr8NHQ+96ryOGYsC9Iyo4maB5vssZMOUnoY+8beRup+0qDrQGOV9EFbTneEzVKmcP311ofY8yKOeRHDvMD/D9jzIrMygXgd1IF9lEOi4/s=
*/