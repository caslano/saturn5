//
// error.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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