//
// basic_file.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_FILE_HPP
#define BOOST_ASIO_BASIC_FILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_FILE) \
  || defined(GENERATING_DOCUMENTATION)

#include <string>
#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/cstdint.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/io_object_impl.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/file_base.hpp>
#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_file_service.hpp>
#elif defined(BOOST_ASIO_HAS_IO_URING)
# include <boost/asio/detail/io_uring_file_service.hpp>
#endif

#if defined(BOOST_ASIO_HAS_MOVE)
# include <utility>
#endif // defined(BOOST_ASIO_HAS_MOVE)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if !defined(BOOST_ASIO_BASIC_FILE_FWD_DECL)
#define BOOST_ASIO_BASIC_FILE_FWD_DECL

// Forward declaration with defaulted arguments.
template <typename Executor = any_io_executor>
class basic_file;

#endif // !defined(BOOST_ASIO_BASIC_FILE_FWD_DECL)

/// Provides file functionality.
/**
 * The basic_file class template provides functionality that is common to both
 * stream-oriented and random-access files.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename Executor>
class basic_file
  : public file_base
{
public:
  /// The type of the executor associated with the object.
  typedef Executor executor_type;

  /// Rebinds the file type to another executor.
  template <typename Executor1>
  struct rebind_executor
  {
    /// The file type when rebound to the specified executor.
    typedef basic_file<Executor1> other;
  };

  /// The native representation of a file.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined native_handle_type;
#elif defined(BOOST_ASIO_HAS_IOCP)
  typedef detail::win_iocp_file_service::native_handle_type native_handle_type;
#elif defined(BOOST_ASIO_HAS_IO_URING)
  typedef detail::io_uring_file_service::native_handle_type native_handle_type;
#endif

  /// Construct a basic_file without opening it.
  /**
   * This constructor initialises a file without opening it.
   *
   * @param ex The I/O executor that the file will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the file.
   */
  explicit basic_file(const executor_type& ex)
    : impl_(0, ex)
  {
  }

  /// Construct a basic_file without opening it.
  /**
   * This constructor initialises a file without opening it.
   *
   * @param context An execution context which provides the I/O executor that
   * the file will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the file.
   */
  template <typename ExecutionContext>
  explicit basic_file(ExecutionContext& context,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : impl_(0, 0, context)
  {
  }

  /// Construct and open a basic_file.
  /**
   * This constructor initialises a file and opens it.
   *
   * @param ex The I/O executor that the file will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the file.
   *
   * @param path The path name identifying the file to be opened.
   *
   * @param open_flags A set of flags that determine how the file should be
   * opened.
   */
  explicit basic_file(const executor_type& ex,
      const char* path, file_base::flags open_flags)
    : impl_(0, ex)
  {
    boost::system::error_code ec;
    impl_.get_service().open(impl_.get_implementation(), path, open_flags, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  /// Construct a basic_file without opening it.
  /**
   * This constructor initialises a file and opens it.
   *
   * @param context An execution context which provides the I/O executor that
   * the file will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the file.
   *
   * @param path The path name identifying the file to be opened.
   *
   * @param open_flags A set of flags that determine how the file should be
   * opened.
   */
  template <typename ExecutionContext>
  explicit basic_file(ExecutionContext& context,
      const char* path, file_base::flags open_flags,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : impl_(0, 0, context)
  {
    boost::system::error_code ec;
    impl_.get_service().open(impl_.get_implementation(), path, open_flags, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  /// Construct and open a basic_file.
  /**
   * This constructor initialises a file and opens it.
   *
   * @param ex The I/O executor that the file will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the file.
   *
   * @param path The path name identifying the file to be opened.
   *
   * @param open_flags A set of flags that determine how the file should be
   * opened.
   */
  explicit basic_file(const executor_type& ex,
      const std::string& path, file_base::flags open_flags)
    : impl_(0, ex)
  {
    boost::system::error_code ec;
    impl_.get_service().open(impl_.get_implementation(),
        path.c_str(), open_flags, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  /// Construct a basic_file without opening it.
  /**
   * This constructor initialises a file and opens it.
   *
   * @param context An execution context which provides the I/O executor that
   * the file will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the file.
   *
   * @param path The path name identifying the file to be opened.
   *
   * @param open_flags A set of flags that determine how the file should be
   * opened.
   */
  template <typename ExecutionContext>
  explicit basic_file(ExecutionContext& context,
      const std::string& path, file_base::flags open_flags,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : impl_(0, 0, context)
  {
    boost::system::error_code ec;
    impl_.get_service().open(impl_.get_implementation(),
        path.c_str(), open_flags, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  /// Construct a basic_file on an existing native file handle.
  /**
   * This constructor initialises a file object to hold an existing native file.
   *
   * @param ex The I/O executor that the file will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the file.
   *
   * @param native_file A native file handle.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_file(const executor_type& ex, const native_handle_type& native_file)
    : impl_(0, ex)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(
        impl_.get_implementation(), native_file, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

  /// Construct a basic_file on an existing native file.
  /**
   * This constructor initialises a file object to hold an existing native file.
   *
   * @param context An execution context which provides the I/O executor that
   * the file will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the file.
   *
   * @param native_file A native file.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_file(ExecutionContext& context, const native_handle_type& native_file,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : impl_(0, 0, context)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(
        impl_.get_implementation(), native_file, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a basic_file from another.
  /**
   * This constructor moves a file from one object to another.
   *
   * @param other The other basic_file object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_file(const executor_type&) constructor.
   */
  basic_file(basic_file&& other) BOOST_ASIO_NOEXCEPT
    : impl_(std::move(other.impl_))
  {
  }

  /// Move-assign a basic_file from another.
  /**
   * This assignment operator moves a file from one object to another.
   *
   * @param other The other basic_file object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_file(const executor_type&) constructor.
   */
  basic_file& operator=(basic_file&& other)
  {
    impl_ = std::move(other.impl_);
    return *this;
  }

  // All files have access to each other's implementations.
  template <typename Executor1>
  friend class basic_file;

  /// Move-construct a basic_file from a file of another executor type.
  /**
   * This constructor moves a file from one object to another.
   *
   * @param other The other basic_file object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_file(const executor_type&) constructor.
   */
  template <typename Executor1>
  basic_file(basic_file<Executor1>&& other,
      typename constraint<
        is_convertible<Executor1, Executor>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : impl_(std::move(other.impl_))
  {
  }

  /// Move-assign a basic_file from a file of another executor type.
  /**
   * This assignment operator moves a file from one object to another.
   *
   * @param other The other basic_file object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_file(const executor_type&) constructor.
   */
  template <typename Executor1>
  typename constraint<
    is_convertible<Executor1, Executor>::value,
    basic_file&
  >::type operator=(basic_file<Executor1> && other)
  {
    basic_file tmp(std::move(other));
    impl_ = std::move(tmp.impl_);
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Get the executor associated with the object.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT
  {
    return impl_.get_executor();
  }

  /// Open the file using the specified path.
  /**
   * This function opens the file so that it will use the specified path.
   *
   * @param path The path name identifying the file to be opened.
   *
   * @param open_flags A set of flags that determine how the file should be
   * opened.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * @code
   * boost::asio::stream_file file(my_context);
   * file.open("/path/to/my/file", boost::asio::stream_file::read_only);
   * @endcode
   */
  void open(const char* path, file_base::flags open_flags)
  {
    boost::system::error_code ec;
    impl_.get_service().open(impl_.get_implementation(), path, open_flags, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  /// Open the file using the specified path.
  /**
   * This function opens the file so that it will use the specified path.
   *
   * @param path The path name identifying the file to be opened.
   *
   * @param open_flags A set of flags that determine how the file should be
   * opened.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @par Example
   * @code
   * boost::asio::stream_file file(my_context);
   * boost::system::error_code ec;
   * file.open("/path/to/my/file", boost::asio::stream_file::read_only, ec);
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   */
  BOOST_ASIO_SYNC_OP_VOID open(const char* path,
      file_base::flags open_flags, boost::system::error_code& ec)
  {
    impl_.get_service().open(impl_.get_implementation(), path, open_flags, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Open the file using the specified path.
  /**
   * This function opens the file so that it will use the specified path.
   *
   * @param path The path name identifying the file to be opened.
   *
   * @param open_flags A set of flags that determine how the file should be
   * opened.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * @code
   * boost::asio::stream_file file(my_context);
   * file.open("/path/to/my/file", boost::asio::stream_file::read_only);
   * @endcode
   */
  void open(const std::string& path, file_base::flags open_flags)
  {
    boost::system::error_code ec;
    impl_.get_service().open(impl_.get_implementation(),
        path.c_str(), open_flags, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  /// Open the file using the specified path.
  /**
   * This function opens the file so that it will use the specified path.
   *
   * @param path The path name identifying the file to be opened.
   *
   * @param open_flags A set of flags that determine how the file should be
   * opened.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @par Example
   * @code
   * boost::asio::stream_file file(my_context);
   * boost::system::error_code ec;
   * file.open("/path/to/my/file", boost::asio::stream_file::read_only, ec);
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   */
  BOOST_ASIO_SYNC_OP_VOID open(const std::string& path,
      file_base::flags open_flags, boost::system::error_code& ec)
  {
    impl_.get_service().open(impl_.get_implementation(),
        path.c_str(), open_flags, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Assign an existing native file to the file.
  /*
   * This function opens the file to hold an existing native file.
   *
   * @param native_file A native file.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void assign(const native_handle_type& native_file)
  {
    boost::system::error_code ec;
    impl_.get_service().assign(
        impl_.get_implementation(), native_file, ec);
    boost::asio::detail::throw_error(ec, "assign");
  }

  /// Assign an existing native file to the file.
  /*
   * This function opens the file to hold an existing native file.
   *
   * @param native_file A native file.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID assign(const native_handle_type& native_file,
      boost::system::error_code& ec)
  {
    impl_.get_service().assign(
        impl_.get_implementation(), native_file, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Determine whether the file is open.
  bool is_open() const
  {
    return impl_.get_service().is_open(impl_.get_implementation());
  }

  /// Close the file.
  /**
   * This function is used to close the file. Any asynchronous read or write
   * operations will be cancelled immediately, and will complete with the
   * boost::asio::error::operation_aborted error.
   *
   * @throws boost::system::system_error Thrown on failure. Note that, even if
   * the function indicates an error, the underlying descriptor is closed.
   */
  void close()
  {
    boost::system::error_code ec;
    impl_.get_service().close(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "close");
  }

  /// Close the file.
  /**
   * This function is used to close the file. Any asynchronous read or write
   * operations will be cancelled immediately, and will complete with the
   * boost::asio::error::operation_aborted error.
   *
   * @param ec Set to indicate what error occurred, if any. Note that, even if
   * the function indicates an error, the underlying descriptor is closed.
   *
   * @par Example
   * @code
   * boost::asio::stream_file file(my_context);
   * ...
   * boost::system::error_code ec;
   * file.close(ec);
   * if (ec)
   * {
   *   // An error occurred.
   * }
   * @endcode
   */
  BOOST_ASIO_SYNC_OP_VOID close(boost::system::error_code& ec)
  {
    impl_.get_service().close(impl_.get_implementation(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Release ownership of the underlying native file.
  /**
   * This function causes all outstanding asynchronous read and write
   * operations to finish immediately, and the handlers for cancelled
   * operations will be passed the boost::asio::error::operation_aborted error.
   * Ownership of the native file is then transferred to the caller.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note This function is unsupported on Windows versions prior to Windows
   * 8.1, and will fail with boost::asio::error::operation_not_supported on
   * these platforms.
   */
#if defined(BOOST_ASIO_MSVC) && (BOOST_ASIO_MSVC >= 1400) \
  && (!defined(_WIN32_WINNT) || _WIN32_WINNT < 0x0603)
  __declspec(deprecated("This function always fails with "
        "operation_not_supported when used on Windows versions "
        "prior to Windows 8.1."))
#endif
  native_handle_type release()
  {
    boost::system::error_code ec;
    native_handle_type s = impl_.get_service().release(
        impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "release");
    return s;
  }

  /// Release ownership of the underlying native file.
  /**
   * This function causes all outstanding asynchronous read and write
   * operations to finish immediately, and the handlers for cancelled
   * operations will be passed the boost::asio::error::operation_aborted error.
   * Ownership of the native file is then transferred to the caller.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note This function is unsupported on Windows versions prior to Windows
   * 8.1, and will fail with boost::asio::error::operation_not_supported on
   * these platforms.
   */
#if defined(BOOST_ASIO_MSVC) && (BOOST_ASIO_MSVC >= 1400) \
  && (!defined(_WIN32_WINNT) || _WIN32_WINNT < 0x0603)
  __declspec(deprecated("This function always fails with "
        "operation_not_supported when used on Windows versions "
        "prior to Windows 8.1."))
#endif
  native_handle_type release(boost::system::error_code& ec)
  {
    return impl_.get_service().release(impl_.get_implementation(), ec);
  }

  /// Get the native file representation.
  /**
   * This function may be used to obtain the underlying representation of the
   * file. This is intended to allow access to native file functionality
   * that is not otherwise provided.
   */
  native_handle_type native_handle()
  {
    return impl_.get_service().native_handle(impl_.get_implementation());
  }

  /// Cancel all asynchronous operations associated with the file.
  /**
   * This function causes all outstanding asynchronous read and write
   * operations to finish immediately, and the handlers for cancelled
   * operations will be passed the boost::asio::error::operation_aborted error.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls to cancel() will always fail with
   * boost::asio::error::operation_not_supported when run on Windows XP, Windows
   * Server 2003, and earlier versions of Windows, unless
   * BOOST_ASIO_ENABLE_CANCELIO is defined. However, the CancelIo function has
   * two issues that should be considered before enabling its use:
   *
   * @li It will only cancel asynchronous operations that were initiated in the
   * current thread.
   *
   * @li It can appear to complete without error, but the request to cancel the
   * unfinished operations may be silently ignored by the operating system.
   * Whether it works or not seems to depend on the drivers that are installed.
   *
   * For portable cancellation, consider using the close() function to
   * simultaneously cancel the outstanding operations and close the file.
   *
   * When running on Windows Vista, Windows Server 2008, and later, the
   * CancelIoEx function is always used. This function does not have the
   * problems described above.
   */
#if defined(BOOST_ASIO_MSVC) && (BOOST_ASIO_MSVC >= 1400) \
  && (!defined(_WIN32_WINNT) || _WIN32_WINNT < 0x0600) \
  && !defined(BOOST_ASIO_ENABLE_CANCELIO)
  __declspec(deprecated("By default, this function always fails with "
        "operation_not_supported when used on Windows XP, Windows Server 2003, "
        "or earlier. Consult documentation for details."))
#endif
  void cancel()
  {
    boost::system::error_code ec;
    impl_.get_service().cancel(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "cancel");
  }

  /// Cancel all asynchronous operations associated with the file.
  /**
   * This function causes all outstanding asynchronous read and write
   * operations to finish immediately, and the handlers for cancelled
   * operations will be passed the boost::asio::error::operation_aborted error.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls to cancel() will always fail with
   * boost::asio::error::operation_not_supported when run on Windows XP, Windows
   * Server 2003, and earlier versions of Windows, unless
   * BOOST_ASIO_ENABLE_CANCELIO is defined. However, the CancelIo function has
   * two issues that should be considered before enabling its use:
   *
   * @li It will only cancel asynchronous operations that were initiated in the
   * current thread.
   *
   * @li It can appear to complete without error, but the request to cancel the
   * unfinished operations may be silently ignored by the operating system.
   * Whether it works or not seems to depend on the drivers that are installed.
   *
   * For portable cancellation, consider using the close() function to
   * simultaneously cancel the outstanding operations and close the file.
   *
   * When running on Windows Vista, Windows Server 2008, and later, the
   * CancelIoEx function is always used. This function does not have the
   * problems described above.
   */
#if defined(BOOST_ASIO_MSVC) && (BOOST_ASIO_MSVC >= 1400) \
  && (!defined(_WIN32_WINNT) || _WIN32_WINNT < 0x0600) \
  && !defined(BOOST_ASIO_ENABLE_CANCELIO)
  __declspec(deprecated("By default, this function always fails with "
        "operation_not_supported when used on Windows XP, Windows Server 2003, "
        "or earlier. Consult documentation for details."))
#endif
  BOOST_ASIO_SYNC_OP_VOID cancel(boost::system::error_code& ec)
  {
    impl_.get_service().cancel(impl_.get_implementation(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Get the size of the file.
  /**
   * This function determines the size of the file, in bytes.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  uint64_t size() const
  {
    boost::system::error_code ec;
    uint64_t s = impl_.get_service().size(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "size");
    return s;
  }

  /// Get the size of the file.
  /**
   * This function determines the size of the file, in bytes.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  uint64_t size(boost::system::error_code& ec) const
  {
    return impl_.get_service().size(impl_.get_implementation(), ec);
  }

  /// Alter the size of the file.
  /**
   * This function resizes the file to the specified size, in bytes. If the
   * current file size exceeds @c n then any extra data is discarded. If the
   * current size is less than @c n then the file is extended and filled with
   * zeroes.
   *
   * @param n The new size for the file.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void resize(uint64_t n)
  {
    boost::system::error_code ec;
    impl_.get_service().resize(impl_.get_implementation(), n, ec);
    boost::asio::detail::throw_error(ec, "resize");
  }

  /// Alter the size of the file.
  /**
   * This function resizes the file to the specified size, in bytes. If the
   * current file size exceeds @c n then any extra data is discarded. If the
   * current size is less than @c n then the file is extended and filled with
   * zeroes.
   *
   * @param n The new size for the file.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID resize(uint64_t n, boost::system::error_code& ec)
  {
    impl_.get_service().resize(impl_.get_implementation(), n, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Synchronise the file to disk.
  /**
   * This function synchronises the file data and metadata to disk. Note that
   * the semantics of this synchronisation vary between operation systems.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void sync_all()
  {
    boost::system::error_code ec;
    impl_.get_service().sync_all(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "sync_all");
  }

  /// Synchronise the file to disk.
  /**
   * This function synchronises the file data and metadata to disk. Note that
   * the semantics of this synchronisation vary between operation systems.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID sync_all(boost::system::error_code& ec)
  {
    impl_.get_service().sync_all(impl_.get_implementation(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Synchronise the file data to disk.
  /**
   * This function synchronises the file data to disk. Note that the semantics
   * of this synchronisation vary between operation systems.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void sync_data()
  {
    boost::system::error_code ec;
    impl_.get_service().sync_data(impl_.get_implementation(), ec);
    boost::asio::detail::throw_error(ec, "sync_data");
  }

  /// Synchronise the file data to disk.
  /**
   * This function synchronises the file data to disk. Note that the semantics
   * of this synchronisation vary between operation systems.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID sync_data(boost::system::error_code& ec)
  {
    impl_.get_service().sync_data(impl_.get_implementation(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

protected:
  /// Protected destructor to prevent deletion through this type.
  /**
   * This function destroys the file, cancelling any outstanding asynchronous
   * operations associated with the file as if by calling @c cancel.
   */
  ~basic_file()
  {
  }

#if defined(BOOST_ASIO_HAS_IOCP)
  detail::io_object_impl<detail::win_iocp_file_service, Executor> impl_;
#elif defined(BOOST_ASIO_HAS_IO_URING)
  detail::io_object_impl<detail::io_uring_file_service, Executor> impl_;
#endif

private:
  // Disallow copying and assignment.
  basic_file(const basic_file&) BOOST_ASIO_DELETED;
  basic_file& operator=(const basic_file&) BOOST_ASIO_DELETED;
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_FILE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_BASIC_FILE_HPP

/* basic_file.hpp
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
*/