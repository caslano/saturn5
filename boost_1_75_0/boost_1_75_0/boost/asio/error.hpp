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
TomgdNaIoHRkz6MtkHHStmdje+3aLvzsiKPWdi2/ZIRFfATqfgS5B8SpSVVGgBxkrJDLgmNR82CFfa7lSMXsPV4No2FKRRRViRXIzh5mJYVyfr4yK1+9heVgbJkQtKr+GN1F2ecSR+NAyg57OGNrcARbJOOFUEZTCGVVRHN9JkMM/6jnEUUELwGBH5ecPcEb2QbJ9RGe2PjQEhyD4MpemT2GP/F7jgRLNq7DQ+j9Ykr0JZI4f0eTraeJcoWGPqWI2fjrPZj1W+jfhSYn413t6jn9NWrAYQz0s/M5vPEkBBAQaX6JzxemAVWEJapvsjOpyacXYEBC5sku9votwTthOGY1IaHZ2tcJo1ydFmjG+zerOqmjAb/gZVUMts+rM2w234ShZwsGchoP1SdBKT5EqvAW8yVfmFetr/pwIP2WYp75BYk5P9I3rfFBSkSP/b+rUrp6lSc+v6LK334uqkREAtSBz6Pfidt+SPzCBaoZuZ+hmtH/gWrGL1Rzi2Wo5p1oyrPJ2thTn44ACTU1zhbXxbpkVt4rrsGXZPK0P+Gt9MXarxlMT73h7NHq4GxVH3e2NPZsHidS2ihl/2eQsqZbpKNUiY1+E+yEkE5A7CtEtwWVX87LDTlU04p7U0w43/MM+V8H/s0Wpd7EFktsgazlyGyxDLIhLC62Azvh6lTHuLIltMlC5D1Zo6eoe7uyFrq/H4GhthwIbLhFstTf
*/