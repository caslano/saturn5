/* Proposed SG14 status_code
(C) 2018 - 2020 Niall Douglas <http://www.nedproductions.biz/> (5 commits)
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
  constexpr explicit _generic_code_domain(typename _base::unique_id_type id = 0x746d6354f4f733e9) noexcept
      : _base(id)
  {
  }
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


template <class T> inline BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 bool status_code<void>::equivalent(const status_code<T> &o) const noexcept
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
template <class DomainType1, class DomainType2> BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 inline bool operator==(const status_code<DomainType1> &a, const status_code<DomainType2> &b) noexcept
{
  return a.equivalent(b);
}
//! True if the status code's are not semantically equal via `equivalent()`.
template <class DomainType1, class DomainType2> BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 inline bool operator!=(const status_code<DomainType1> &a, const status_code<DomainType2> &b) noexcept
{
  return !a.equivalent(b);
}
//! True if the status code's are semantically equal via `equivalent()` to `make_status_code(T)`.
BOOST_OUTCOME_SYSTEM_ERROR2_TEMPLATE(class DomainType1, class T,                                                                       //
                       class MakeStatusCodeResult = typename detail::safe_get_make_status_code_result<const T &>::type)  // Safe ADL lookup of make_status_code(), returns void if not found
BOOST_OUTCOME_SYSTEM_ERROR2_TREQUIRES(BOOST_OUTCOME_SYSTEM_ERROR2_TPRED(is_status_code<MakeStatusCodeResult>::value))                                // ADL makes a status code
BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 inline bool operator==(const status_code<DomainType1> &a, const T &b)
{
  return a.equivalent(make_status_code(b));
}
//! True if the status code's are semantically equal via `equivalent()` to `make_status_code(T)`.
BOOST_OUTCOME_SYSTEM_ERROR2_TEMPLATE(class T, class DomainType1,                                                                       //
                       class MakeStatusCodeResult = typename detail::safe_get_make_status_code_result<const T &>::type)  // Safe ADL lookup of make_status_code(), returns void if not found
BOOST_OUTCOME_SYSTEM_ERROR2_TREQUIRES(BOOST_OUTCOME_SYSTEM_ERROR2_TPRED(is_status_code<MakeStatusCodeResult>::value))                                // ADL makes a status code
BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 inline bool operator==(const T &a, const status_code<DomainType1> &b)
{
  return b.equivalent(make_status_code(a));
}
//! True if the status code's are not semantically equal via `equivalent()` to `make_status_code(T)`.
BOOST_OUTCOME_SYSTEM_ERROR2_TEMPLATE(class DomainType1, class T,                                                                       //
                       class MakeStatusCodeResult = typename detail::safe_get_make_status_code_result<const T &>::type)  // Safe ADL lookup of make_status_code(), returns void if not found
BOOST_OUTCOME_SYSTEM_ERROR2_TREQUIRES(BOOST_OUTCOME_SYSTEM_ERROR2_TPRED(is_status_code<MakeStatusCodeResult>::value))                                // ADL makes a status code
BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 inline bool operator!=(const status_code<DomainType1> &a, const T &b)
{
  return !a.equivalent(make_status_code(b));
}
//! True if the status code's are semantically equal via `equivalent()` to `make_status_code(T)`.
BOOST_OUTCOME_SYSTEM_ERROR2_TEMPLATE(class T, class DomainType1,                                                                       //
                       class MakeStatusCodeResult = typename detail::safe_get_make_status_code_result<const T &>::type)  // Safe ADL lookup of make_status_code(), returns void if not found
BOOST_OUTCOME_SYSTEM_ERROR2_TREQUIRES(BOOST_OUTCOME_SYSTEM_ERROR2_TPRED(is_status_code<MakeStatusCodeResult>::value))                                // ADL makes a status code
BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 inline bool operator!=(const T &a, const status_code<DomainType1> &b)
{
  return !b.equivalent(make_status_code(a));
}
//! True if the status code's are semantically equal via `equivalent()` to `quick_status_code_from_enum<T>::code_type(b)`.
template <class DomainType1, class T,                                                     //
          class QuickStatusCodeType = typename quick_status_code_from_enum<T>::code_type  // Enumeration has been activated
          >
BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 inline bool operator==(const status_code<DomainType1> &a, const T &b)
{
  return a.equivalent(QuickStatusCodeType(b));
}
//! True if the status code's are semantically equal via `equivalent()` to `quick_status_code_from_enum<T>::code_type(a)`.
template <class T, class DomainType1,                                                     //
          class QuickStatusCodeType = typename quick_status_code_from_enum<T>::code_type  // Enumeration has been activated
          >
BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 inline bool operator==(const T &a, const status_code<DomainType1> &b)
{
  return b.equivalent(QuickStatusCodeType(a));
}
//! True if the status code's are not semantically equal via `equivalent()` to `quick_status_code_from_enum<T>::code_type(b)`.
template <class DomainType1, class T,                                                     //
          class QuickStatusCodeType = typename quick_status_code_from_enum<T>::code_type  // Enumeration has been activated
          >
BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 inline bool operator!=(const status_code<DomainType1> &a, const T &b)
{
  return !a.equivalent(QuickStatusCodeType(b));
}
//! True if the status code's are not semantically equal via `equivalent()` to `quick_status_code_from_enum<T>::code_type(a)`.
template <class T, class DomainType1,                                                     //
          class QuickStatusCodeType = typename quick_status_code_from_enum<T>::code_type  // Enumeration has been activated
          >
BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 inline bool operator!=(const T &a, const status_code<DomainType1> &b)
{
  return !b.equivalent(QuickStatusCodeType(a));
}


BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_END

#endif

/* generic_code.hpp
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
*/