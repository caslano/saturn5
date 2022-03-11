/* Proposed SG14 status_code
(C) 2018 - 2019 Niall Douglas <http://www.nedproductions.biz/> (5 commits)
File Created: Feb 2018


Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License in the accompanying file
Licence.txt or at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


Distributed under the Boost Software License, Version 1.0.
(See accompanying file Licence.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_OUTCOME_SYSTEM_ERROR2_GENERIC_CODE_HPP
#define BOOST_OUTCOME_SYSTEM_ERROR2_GENERIC_CODE_HPP

#include "status_error.hpp"

#include <cerrno>  // for error constants

BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_BEGIN

//! The generic error coding (POSIX)
enum class errc : int
{
  success = 0,
  unknown = -1,

  address_family_not_supported = EAFNOSUPPORT,
  address_in_use = EADDRINUSE,
  address_not_available = EADDRNOTAVAIL,
  already_connected = EISCONN,
  argument_list_too_long = E2BIG,
  argument_out_of_domain = EDOM,
  bad_address = EFAULT,
  bad_file_descriptor = EBADF,
  bad_message = EBADMSG,
  broken_pipe = EPIPE,
  connection_aborted = ECONNABORTED,
  connection_already_in_progress = EALREADY,
  connection_refused = ECONNREFUSED,
  connection_reset = ECONNRESET,
  cross_device_link = EXDEV,
  destination_address_required = EDESTADDRREQ,
  device_or_resource_busy = EBUSY,
  directory_not_empty = ENOTEMPTY,
  executable_format_error = ENOEXEC,
  file_exists = EEXIST,
  file_too_large = EFBIG,
  filename_too_long = ENAMETOOLONG,
  function_not_supported = ENOSYS,
  host_unreachable = EHOSTUNREACH,
  identifier_removed = EIDRM,
  illegal_byte_sequence = EILSEQ,
  inappropriate_io_control_operation = ENOTTY,
  interrupted = EINTR,
  invalid_argument = EINVAL,
  invalid_seek = ESPIPE,
  io_error = EIO,
  is_a_directory = EISDIR,
  message_size = EMSGSIZE,
  network_down = ENETDOWN,
  network_reset = ENETRESET,
  network_unreachable = ENETUNREACH,
  no_buffer_space = ENOBUFS,
  no_child_process = ECHILD,
  no_link = ENOLINK,
  no_lock_available = ENOLCK,
  no_message = ENOMSG,
  no_protocol_option = ENOPROTOOPT,
  no_space_on_device = ENOSPC,
  no_stream_resources = ENOSR,
  no_such_device_or_address = ENXIO,
  no_such_device = ENODEV,
  no_such_file_or_directory = ENOENT,
  no_such_process = ESRCH,
  not_a_directory = ENOTDIR,
  not_a_socket = ENOTSOCK,
  not_a_stream = ENOSTR,
  not_connected = ENOTCONN,
  not_enough_memory = ENOMEM,
  not_supported = ENOTSUP,
  operation_canceled = ECANCELED,
  operation_in_progress = EINPROGRESS,
  operation_not_permitted = EPERM,
  operation_not_supported = EOPNOTSUPP,
  operation_would_block = EWOULDBLOCK,
  owner_dead = EOWNERDEAD,
  permission_denied = EACCES,
  protocol_error = EPROTO,
  protocol_not_supported = EPROTONOSUPPORT,
  read_only_file_system = EROFS,
  resource_deadlock_would_occur = EDEADLK,
  resource_unavailable_try_again = EAGAIN,
  result_out_of_range = ERANGE,
  state_not_recoverable = ENOTRECOVERABLE,
  stream_timeout = ETIME,
  text_file_busy = ETXTBSY,
  timed_out = ETIMEDOUT,
  too_many_files_open_in_system = ENFILE,
  too_many_files_open = EMFILE,
  too_many_links = EMLINK,
  too_many_symbolic_link_levels = ELOOP,
  value_too_large = EOVERFLOW,
  wrong_protocol_type = EPROTOTYPE
};

namespace detail
{
  BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 inline const char *generic_code_message(errc code) noexcept
  {
    switch(code)
    {
    case errc::success:
      return "Success";
    case errc::address_family_not_supported:
      return "Address family not supported by protocol";
    case errc::address_in_use:
      return "Address already in use";
    case errc::address_not_available:
      return "Cannot assign requested address";
    case errc::already_connected:
      return "Transport endpoint is already connected";
    case errc::argument_list_too_long:
      return "Argument list too long";
    case errc::argument_out_of_domain:
      return "Numerical argument out of domain";
    case errc::bad_address:
      return "Bad address";
    case errc::bad_file_descriptor:
      return "Bad file descriptor";
    case errc::bad_message:
      return "Bad message";
    case errc::broken_pipe:
      return "Broken pipe";
    case errc::connection_aborted:
      return "Software caused connection abort";
    case errc::connection_already_in_progress:
      return "Operation already in progress";
    case errc::connection_refused:
      return "Connection refused";
    case errc::connection_reset:
      return "Connection reset by peer";
    case errc::cross_device_link:
      return "Invalid cross-device link";
    case errc::destination_address_required:
      return "Destination address required";
    case errc::device_or_resource_busy:
      return "Device or resource busy";
    case errc::directory_not_empty:
      return "Directory not empty";
    case errc::executable_format_error:
      return "Exec format error";
    case errc::file_exists:
      return "File exists";
    case errc::file_too_large:
      return "File too large";
    case errc::filename_too_long:
      return "File name too long";
    case errc::function_not_supported:
      return "Function not implemented";
    case errc::host_unreachable:
      return "No route to host";
    case errc::identifier_removed:
      return "Identifier removed";
    case errc::illegal_byte_sequence:
      return "Invalid or incomplete multibyte or wide character";
    case errc::inappropriate_io_control_operation:
      return "Inappropriate ioctl for device";
    case errc::interrupted:
      return "Interrupted system call";
    case errc::invalid_argument:
      return "Invalid argument";
    case errc::invalid_seek:
      return "Illegal seek";
    case errc::io_error:
      return "Input/output error";
    case errc::is_a_directory:
      return "Is a directory";
    case errc::message_size:
      return "Message too long";
    case errc::network_down:
      return "Network is down";
    case errc::network_reset:
      return "Network dropped connection on reset";
    case errc::network_unreachable:
      return "Network is unreachable";
    case errc::no_buffer_space:
      return "No buffer space available";
    case errc::no_child_process:
      return "No child processes";
    case errc::no_link:
      return "Link has been severed";
    case errc::no_lock_available:
      return "No locks available";
    case errc::no_message:
      return "No message of desired type";
    case errc::no_protocol_option:
      return "Protocol not available";
    case errc::no_space_on_device:
      return "No space left on device";
    case errc::no_stream_resources:
      return "Out of streams resources";
    case errc::no_such_device_or_address:
      return "No such device or address";
    case errc::no_such_device:
      return "No such device";
    case errc::no_such_file_or_directory:
      return "No such file or directory";
    case errc::no_such_process:
      return "No such process";
    case errc::not_a_directory:
      return "Not a directory";
    case errc::not_a_socket:
      return "Socket operation on non-socket";
    case errc::not_a_stream:
      return "Device not a stream";
    case errc::not_connected:
      return "Transport endpoint is not connected";
    case errc::not_enough_memory:
      return "Cannot allocate memory";
#if ENOTSUP != EOPNOTSUPP
    case errc::not_supported:
      return "Operation not supported";
#endif
    case errc::operation_canceled:
      return "Operation canceled";
    case errc::operation_in_progress:
      return "Operation now in progress";
    case errc::operation_not_permitted:
      return "Operation not permitted";
    case errc::operation_not_supported:
      return "Operation not supported";
#if EAGAIN != EWOULDBLOCK
    case errc::operation_would_block:
      return "Resource temporarily unavailable";
#endif
    case errc::owner_dead:
      return "Owner died";
    case errc::permission_denied:
      return "Permission denied";
    case errc::protocol_error:
      return "Protocol error";
    case errc::protocol_not_supported:
      return "Protocol not supported";
    case errc::read_only_file_system:
      return "Read-only file system";
    case errc::resource_deadlock_would_occur:
      return "Resource deadlock avoided";
    case errc::resource_unavailable_try_again:
      return "Resource temporarily unavailable";
    case errc::result_out_of_range:
      return "Numerical result out of range";
    case errc::state_not_recoverable:
      return "State not recoverable";
    case errc::stream_timeout:
      return "Timer expired";
    case errc::text_file_busy:
      return "Text file busy";
    case errc::timed_out:
      return "Connection timed out";
    case errc::too_many_files_open_in_system:
      return "Too many open files in system";
    case errc::too_many_files_open:
      return "Too many open files";
    case errc::too_many_links:
      return "Too many links";
    case errc::too_many_symbolic_link_levels:
      return "Too many levels of symbolic links";
    case errc::value_too_large:
      return "Value too large for defined data type";
    case errc::wrong_protocol_type:
      return "Protocol wrong type for socket";
    default:
      return "unknown";
    }
  }
}  // namespace detail

/*! The implementation of the domain for generic status codes, those mapped by `errc` (POSIX).
 */
class _generic_code_domain : public status_code_domain
{
  template <class> friend class status_code;
  template <class StatusCode> friend class detail::indirecting_domain;
  using _base = status_code_domain;

public:
  //! The value type of the generic code, which is an `errc` as per POSIX.
  using value_type = errc;
  using string_ref = _base::string_ref;

public:
  //! Default constructor
  constexpr explicit _generic_code_domain(typename _base::unique_id_type id = 0x746d6354f4f733e9) noexcept : _base(id) {}
  _generic_code_domain(const _generic_code_domain &) = default;
  _generic_code_domain(_generic_code_domain &&) = default;
  _generic_code_domain &operator=(const _generic_code_domain &) = default;
  _generic_code_domain &operator=(_generic_code_domain &&) = default;
  ~_generic_code_domain() = default;

  //! Constexpr singleton getter. Returns the constexpr generic_code_domain variable.
  static inline constexpr const _generic_code_domain &get();

  virtual _base::string_ref name() const noexcept override { return string_ref("generic domain"); }  // NOLINT
protected:
  virtual bool _do_failure(const status_code<void> &code) const noexcept override  // NOLINT
  {
    assert(code.domain() == *this);                                           // NOLINT
    return static_cast<const generic_code &>(code).value() != errc::success;  // NOLINT
  }
  virtual bool _do_equivalent(const status_code<void> &code1, const status_code<void> &code2) const noexcept override  // NOLINT
  {
    assert(code1.domain() == *this);                            // NOLINT
    const auto &c1 = static_cast<const generic_code &>(code1);  // NOLINT
    if(code2.domain() == *this)
    {
      const auto &c2 = static_cast<const generic_code &>(code2);  // NOLINT
      return c1.value() == c2.value();
    }
    return false;
  }
  virtual generic_code _generic_code(const status_code<void> &code) const noexcept override  // NOLINT
  {
    assert(code.domain() == *this);                  // NOLINT
    return static_cast<const generic_code &>(code);  // NOLINT
  }
  virtual _base::string_ref _do_message(const status_code<void> &code) const noexcept override  // NOLINT
  {
    assert(code.domain() == *this);                           // NOLINT
    const auto &c = static_cast<const generic_code &>(code);  // NOLINT
    return string_ref(detail::generic_code_message(c.value()));
  }
#if defined(_CPPUNWIND) || defined(__EXCEPTIONS) || defined(BOOST_OUTCOME_STANDARDESE_IS_IN_THE_HOUSE)
  BOOST_OUTCOME_SYSTEM_ERROR2_NORETURN virtual void _do_throw_exception(const status_code<void> &code) const override  // NOLINT
  {
    assert(code.domain() == *this);                           // NOLINT
    const auto &c = static_cast<const generic_code &>(code);  // NOLINT
    throw status_error<_generic_code_domain>(c);
  }
#endif
};
//! A specialisation of `status_error` for the generic code domain.
using generic_error = status_error<_generic_code_domain>;
//! A constexpr source variable for the generic code domain, which is that of `errc` (POSIX). Returned by `_generic_code_domain::get()`.
constexpr _generic_code_domain generic_code_domain;
inline constexpr const _generic_code_domain &_generic_code_domain::get()
{
  return generic_code_domain;
}
// Enable implicit construction of generic_code from errc
BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 inline generic_code make_status_code(errc c) noexcept
{
  return generic_code(in_place, c);
}


/*************************************************************************************************************/


template <class T> inline bool status_code<void>::equivalent(const status_code<T> &o) const noexcept
{
  if(_domain && o._domain)
  {
    if(_domain->_do_equivalent(*this, o))
    {
      return true;
    }
    if(o._domain->_do_equivalent(o, *this))
    {
      return true;
    }
    generic_code c1 = o._domain->_generic_code(o);
    if(c1.value() != errc::unknown && _domain->_do_equivalent(*this, c1))
    {
      return true;
    }
    generic_code c2 = _domain->_generic_code(*this);
    if(c2.value() != errc::unknown && o._domain->_do_equivalent(o, c2))
    {
      return true;
    }
  }
  // If we are both empty, we are equivalent, otherwise not equivalent
  return (!_domain && !o._domain);
}
//! True if the status code's are semantically equal via `equivalent()`.
template <class DomainType1, class DomainType2> inline bool operator==(const status_code<DomainType1> &a, const status_code<DomainType2> &b) noexcept
{
  return a.equivalent(b);
}
//! True if the status code's are not semantically equal via `equivalent()`.
template <class DomainType1, class DomainType2> inline bool operator!=(const status_code<DomainType1> &a, const status_code<DomainType2> &b) noexcept
{
  return !a.equivalent(b);
}
//! True if the status code's are semantically equal via `equivalent()` to `make_status_code(T)`.
template <class DomainType1, class T,                                                                       //
          class MakeStatusCodeResult = typename detail::safe_get_make_status_code_result<const T &>::type,  // Safe ADL lookup of make_status_code(), returns void if not found
          typename std::enable_if<is_status_code<MakeStatusCodeResult>::value, bool>::type = true>          // ADL makes a status code
inline bool operator==(const status_code<DomainType1> &a, const T &b)
{
  return a.equivalent(make_status_code(b));
}
//! True if the status code's are semantically equal via `equivalent()` to `make_status_code(T)`.
template <class T, class DomainType1,                                                                       //
          class MakeStatusCodeResult = typename detail::safe_get_make_status_code_result<const T &>::type,  // Safe ADL lookup of make_status_code(), returns void if not found
          typename std::enable_if<is_status_code<MakeStatusCodeResult>::value, bool>::type = true>          // ADL makes a status code
inline bool operator==(const T &a, const status_code<DomainType1> &b)
{
  return b.equivalent(make_status_code(a));
}
//! True if the status code's are not semantically equal via `equivalent()` to `make_status_code(T)`.
template <class DomainType1, class T,                                                                       //
          class MakeStatusCodeResult = typename detail::safe_get_make_status_code_result<const T &>::type,  // Safe ADL lookup of make_status_code(), returns void if not found
          typename std::enable_if<is_status_code<MakeStatusCodeResult>::value, bool>::type = true>          // ADL makes a status code
inline bool operator!=(const status_code<DomainType1> &a, const T &b)
{
  return !a.equivalent(make_status_code(b));
}
//! True if the status code's are semantically equal via `equivalent()` to `make_status_code(T)`.
template <class T, class DomainType1,                                                                       //
          class MakeStatusCodeResult = typename detail::safe_get_make_status_code_result<const T &>::type,  // Safe ADL lookup of make_status_code(), returns void if not found
          typename std::enable_if<is_status_code<MakeStatusCodeResult>::value, bool>::type = true>          // ADL makes a status code
inline bool operator!=(const T &a, const status_code<DomainType1> &b)
{
  return !b.equivalent(make_status_code(a));
}

BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_END

#endif

/* generic_code.hpp
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
*/