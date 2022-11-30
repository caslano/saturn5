//
// error.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_ERROR_HPP
#define BOOST_ASIO_ERROR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/cerrno.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#if defined(BOOST_ASIO_WINDOWS) \
  || defined(__CYGWIN__) \
  || defined(BOOST_ASIO_WINDOWS_RUNTIME)
# include <winerror.h>
#else
# include <cerrno>
# include <netdb.h>
#endif

#if defined(GENERATING_DOCUMENTATION)
/// INTERNAL ONLY.
# define BOOST_ASIO_NATIVE_ERROR(e) implementation_defined
/// INTERNAL ONLY.
# define BOOST_ASIO_SOCKET_ERROR(e) implementation_defined
/// INTERNAL ONLY.
# define BOOST_ASIO_NETDB_ERROR(e) implementation_defined
/// INTERNAL ONLY.
# define BOOST_ASIO_GETADDRINFO_ERROR(e) implementation_defined
/// INTERNAL ONLY.
# define BOOST_ASIO_WIN_OR_POSIX(e_win, e_posix) implementation_defined
#elif defined(BOOST_ASIO_WINDOWS_RUNTIME)
# define BOOST_ASIO_NATIVE_ERROR(e) __HRESULT_FROM_WIN32(e)
# define BOOST_ASIO_SOCKET_ERROR(e) __HRESULT_FROM_WIN32(WSA ## e)
# define BOOST_ASIO_NETDB_ERROR(e) __HRESULT_FROM_WIN32(WSA ## e)
# define BOOST_ASIO_GETADDRINFO_ERROR(e) __HRESULT_FROM_WIN32(WSA ## e)
# define BOOST_ASIO_WIN_OR_POSIX(e_win, e_posix) e_win
#elif defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
# define BOOST_ASIO_NATIVE_ERROR(e) e
# define BOOST_ASIO_SOCKET_ERROR(e) WSA ## e
# define BOOST_ASIO_NETDB_ERROR(e) WSA ## e
# define BOOST_ASIO_GETADDRINFO_ERROR(e) WSA ## e
# define BOOST_ASIO_WIN_OR_POSIX(e_win, e_posix) e_win
#else
# define BOOST_ASIO_NATIVE_ERROR(e) e
# define BOOST_ASIO_SOCKET_ERROR(e) e
# define BOOST_ASIO_NETDB_ERROR(e) e
# define BOOST_ASIO_GETADDRINFO_ERROR(e) e
# define BOOST_ASIO_WIN_OR_POSIX(e_win, e_posix) e_posix
#endif

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace error {

enum basic_errors
{
  /// Permission denied.
  access_denied = BOOST_ASIO_SOCKET_ERROR(EACCES),

  /// Address family not supported by protocol.
  address_family_not_supported = BOOST_ASIO_SOCKET_ERROR(EAFNOSUPPORT),

  /// Address already in use.
  address_in_use = BOOST_ASIO_SOCKET_ERROR(EADDRINUSE),

  /// Transport endpoint is already connected.
  already_connected = BOOST_ASIO_SOCKET_ERROR(EISCONN),

  /// Operation already in progress.
  already_started = BOOST_ASIO_SOCKET_ERROR(EALREADY),

  /// Broken pipe.
  broken_pipe = BOOST_ASIO_WIN_OR_POSIX(
      BOOST_ASIO_NATIVE_ERROR(ERROR_BROKEN_PIPE),
      BOOST_ASIO_NATIVE_ERROR(EPIPE)),

  /// A connection has been aborted.
  connection_aborted = BOOST_ASIO_SOCKET_ERROR(ECONNABORTED),

  /// Connection refused.
  connection_refused = BOOST_ASIO_SOCKET_ERROR(ECONNREFUSED),

  /// Connection reset by peer.
  connection_reset = BOOST_ASIO_SOCKET_ERROR(ECONNRESET),

  /// Bad file descriptor.
  bad_descriptor = BOOST_ASIO_SOCKET_ERROR(EBADF),

  /// Bad address.
  fault = BOOST_ASIO_SOCKET_ERROR(EFAULT),

  /// No route to host.
  host_unreachable = BOOST_ASIO_SOCKET_ERROR(EHOSTUNREACH),

  /// Operation now in progress.
  in_progress = BOOST_ASIO_SOCKET_ERROR(EINPROGRESS),

  /// Interrupted system call.
  interrupted = BOOST_ASIO_SOCKET_ERROR(EINTR),

  /// Invalid argument.
  invalid_argument = BOOST_ASIO_SOCKET_ERROR(EINVAL),

  /// Message too long.
  message_size = BOOST_ASIO_SOCKET_ERROR(EMSGSIZE),

  /// The name was too long.
  name_too_long = BOOST_ASIO_SOCKET_ERROR(ENAMETOOLONG),

  /// Network is down.
  network_down = BOOST_ASIO_SOCKET_ERROR(ENETDOWN),

  /// Network dropped connection on reset.
  network_reset = BOOST_ASIO_SOCKET_ERROR(ENETRESET),

  /// Network is unreachable.
  network_unreachable = BOOST_ASIO_SOCKET_ERROR(ENETUNREACH),

  /// Too many open files.
  no_descriptors = BOOST_ASIO_SOCKET_ERROR(EMFILE),

  /// No buffer space available.
  no_buffer_space = BOOST_ASIO_SOCKET_ERROR(ENOBUFS),

  /// Cannot allocate memory.
  no_memory = BOOST_ASIO_WIN_OR_POSIX(
      BOOST_ASIO_NATIVE_ERROR(ERROR_OUTOFMEMORY),
      BOOST_ASIO_NATIVE_ERROR(ENOMEM)),

  /// Operation not permitted.
  no_permission = BOOST_ASIO_WIN_OR_POSIX(
      BOOST_ASIO_NATIVE_ERROR(ERROR_ACCESS_DENIED),
      BOOST_ASIO_NATIVE_ERROR(EPERM)),

  /// Protocol not available.
  no_protocol_option = BOOST_ASIO_SOCKET_ERROR(ENOPROTOOPT),

  /// No such device.
  no_such_device = BOOST_ASIO_WIN_OR_POSIX(
      BOOST_ASIO_NATIVE_ERROR(ERROR_BAD_UNIT),
      BOOST_ASIO_NATIVE_ERROR(ENODEV)),

  /// Transport endpoint is not connected.
  not_connected = BOOST_ASIO_SOCKET_ERROR(ENOTCONN),

  /// Socket operation on non-socket.
  not_socket = BOOST_ASIO_SOCKET_ERROR(ENOTSOCK),

  /// Operation cancelled.
  operation_aborted = BOOST_ASIO_WIN_OR_POSIX(
      BOOST_ASIO_NATIVE_ERROR(ERROR_OPERATION_ABORTED),
      BOOST_ASIO_NATIVE_ERROR(ECANCELED)),

  /// Operation not supported.
  operation_not_supported = BOOST_ASIO_SOCKET_ERROR(EOPNOTSUPP),

  /// Cannot send after transport endpoint shutdown.
  shut_down = BOOST_ASIO_SOCKET_ERROR(ESHUTDOWN),

  /// Connection timed out.
  timed_out = BOOST_ASIO_SOCKET_ERROR(ETIMEDOUT),

  /// Resource temporarily unavailable.
  try_again = BOOST_ASIO_WIN_OR_POSIX(
      BOOST_ASIO_NATIVE_ERROR(ERROR_RETRY),
      BOOST_ASIO_NATIVE_ERROR(EAGAIN)),

  /// The socket is marked non-blocking and the requested operation would block.
  would_block = BOOST_ASIO_SOCKET_ERROR(EWOULDBLOCK)
};

enum netdb_errors
{
  /// Host not found (authoritative).
  host_not_found = BOOST_ASIO_NETDB_ERROR(HOST_NOT_FOUND),

  /// Host not found (non-authoritative).
  host_not_found_try_again = BOOST_ASIO_NETDB_ERROR(TRY_AGAIN),

  /// The query is valid but does not have associated address data.
  no_data = BOOST_ASIO_NETDB_ERROR(NO_DATA),

  /// A non-recoverable error occurred.
  no_recovery = BOOST_ASIO_NETDB_ERROR(NO_RECOVERY)
};

enum addrinfo_errors
{
  /// The service is not supported for the given socket type.
  service_not_found = BOOST_ASIO_WIN_OR_POSIX(
      BOOST_ASIO_NATIVE_ERROR(WSATYPE_NOT_FOUND),
      BOOST_ASIO_GETADDRINFO_ERROR(EAI_SERVICE)),

  /// The socket type is not supported.
  socket_type_not_supported = BOOST_ASIO_WIN_OR_POSIX(
      BOOST_ASIO_NATIVE_ERROR(WSAESOCKTNOSUPPORT),
      BOOST_ASIO_GETADDRINFO_ERROR(EAI_SOCKTYPE))
};

enum misc_errors
{
  /// Already open.
  already_open = 1,

  /// End of file or stream.
  eof,

  /// Element not found.
  not_found,

  /// The descriptor cannot fit into the select system call's fd_set.
  fd_set_failure
};

inline const boost::system::error_category& get_system_category()
{
  return boost::system::system_category();
}

#if !defined(BOOST_ASIO_WINDOWS) && !defined(__CYGWIN__)

extern BOOST_ASIO_DECL
const boost::system::error_category& get_netdb_category();

extern BOOST_ASIO_DECL
const boost::system::error_category& get_addrinfo_category();

#else // !defined(BOOST_ASIO_WINDOWS) && !defined(__CYGWIN__)

inline const boost::system::error_category& get_netdb_category()
{
  return get_system_category();
}

inline const boost::system::error_category& get_addrinfo_category()
{
  return get_system_category();
}

#endif // !defined(BOOST_ASIO_WINDOWS) && !defined(__CYGWIN__)

extern BOOST_ASIO_DECL
const boost::system::error_category& get_misc_category();

static const boost::system::error_category&
  system_category BOOST_ASIO_UNUSED_VARIABLE
  = boost::asio::error::get_system_category();
static const boost::system::error_category&
  netdb_category BOOST_ASIO_UNUSED_VARIABLE
  = boost::asio::error::get_netdb_category();
static const boost::system::error_category&
  addrinfo_category BOOST_ASIO_UNUSED_VARIABLE
  = boost::asio::error::get_addrinfo_category();
static const boost::system::error_category&
  misc_category BOOST_ASIO_UNUSED_VARIABLE
  = boost::asio::error::get_misc_category();

} // namespace error
} // namespace asio
} // namespace boost

namespace boost {
namespace system {

template<> struct is_error_code_enum<boost::asio::error::basic_errors>
{
  static const bool value = true;
};

template<> struct is_error_code_enum<boost::asio::error::netdb_errors>
{
  static const bool value = true;
};

template<> struct is_error_code_enum<boost::asio::error::addrinfo_errors>
{
  static const bool value = true;
};

template<> struct is_error_code_enum<boost::asio::error::misc_errors>
{
  static const bool value = true;
};

} // namespace system
} // namespace boost

namespace boost {
namespace asio {
namespace error {

inline boost::system::error_code make_error_code(basic_errors e)
{
  return boost::system::error_code(
      static_cast<int>(e), get_system_category());
}

inline boost::system::error_code make_error_code(netdb_errors e)
{
  return boost::system::error_code(
      static_cast<int>(e), get_netdb_category());
}

inline boost::system::error_code make_error_code(addrinfo_errors e)
{
  return boost::system::error_code(
      static_cast<int>(e), get_addrinfo_category());
}

inline boost::system::error_code make_error_code(misc_errors e)
{
  return boost::system::error_code(
      static_cast<int>(e), get_misc_category());
}

} // namespace error
namespace stream_errc {
  // Simulates the proposed stream_errc scoped enum.
  using error::eof;
  using error::not_found;
} // namespace stream_errc
namespace socket_errc {
  // Simulates the proposed socket_errc scoped enum.
  using error::already_open;
  using error::not_found;
} // namespace socket_errc
namespace resolver_errc {
  // Simulates the proposed resolver_errc scoped enum.
  using error::host_not_found;
  const error::netdb_errors try_again = error::host_not_found_try_again;
  using error::service_not_found;
} // namespace resolver_errc
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#undef BOOST_ASIO_NATIVE_ERROR
#undef BOOST_ASIO_SOCKET_ERROR
#undef BOOST_ASIO_NETDB_ERROR
#undef BOOST_ASIO_GETADDRINFO_ERROR
#undef BOOST_ASIO_WIN_OR_POSIX

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/impl/error.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_ERROR_HPP

/* error.hpp
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
*/