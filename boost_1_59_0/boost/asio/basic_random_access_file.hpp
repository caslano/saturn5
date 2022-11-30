//
// basic_random_access_file.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_RANDOM_ACCESS_FILE_HPP
#define BOOST_ASIO_BASIC_RANDOM_ACCESS_FILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_FILE) \
  || defined(GENERATING_DOCUMENTATION)

#include <cstddef>
#include <boost/asio/async_result.hpp>
#include <boost/asio/basic_file.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if !defined(BOOST_ASIO_BASIC_RANDOM_ACCESS_FILE_FWD_DECL)
#define BOOST_ASIO_BASIC_RANDOM_ACCESS_FILE_FWD_DECL

// Forward declaration with defaulted arguments.
template <typename Executor = any_io_executor>
class basic_random_access_file;

#endif // !defined(BOOST_ASIO_BASIC_RANDOM_ACCESS_FILE_FWD_DECL)

/// Provides random-access file functionality.
/**
 * The basic_random_access_file class template provides asynchronous and
 * blocking random-access file functionality.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 *
 * Synchronous @c read_some_at and @c write_some_at operations are thread safe
 * with respect to each other, if the underlying operating system calls are
 * also thread safe. This means that it is permitted to perform concurrent
 * calls to these synchronous operations on a single file object. Other
 * synchronous operations, such as @c open or @c close, are not thread safe.
 */
template <typename Executor>
class basic_random_access_file
  : public basic_file<Executor>
{
public:
  /// The type of the executor associated with the object.
  typedef Executor executor_type;

  /// Rebinds the file type to another executor.
  template <typename Executor1>
  struct rebind_executor
  {
    /// The file type when rebound to the specified executor.
    typedef basic_random_access_file<Executor1> other;
  };

  /// The native representation of a file.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined native_handle_type;
#else
  typedef typename basic_file<Executor>::native_handle_type native_handle_type;
#endif

  /// Construct a basic_random_access_file without opening it.
  /**
   * This constructor initialises a file without opening it. The file needs to
   * be opened before data can be read from or or written to it.
   *
   * @param ex The I/O executor that the file will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the file.
   */
  explicit basic_random_access_file(const executor_type& ex)
    : basic_file<Executor>(ex)
  {
  }

  /// Construct a basic_random_access_file without opening it.
  /**
   * This constructor initialises a file without opening it. The file needs to
   * be opened before data can be read from or or written to it.
   *
   * @param context An execution context which provides the I/O executor that
   * the file will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the file.
   */
  template <typename ExecutionContext>
  explicit basic_random_access_file(ExecutionContext& context,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : basic_file<Executor>(context)
  {
  }

  /// Construct and open a basic_random_access_file.
  /**
   * This constructor initialises and opens a file.
   *
   * @param ex The I/O executor that the file will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the file.
   *
   * @param path The path name identifying the file to be opened.
   *
   * @param open_flags A set of flags that determine how the file should be
   * opened.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_random_access_file(const executor_type& ex,
      const char* path, file_base::flags open_flags)
    : basic_file<Executor>(ex, path, open_flags)
  {
  }

  /// Construct and open a basic_random_access_file.
  /**
   * This constructor initialises and opens a file.
   *
   * @param context An execution context which provides the I/O executor that
   * the file will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the file.
   *
   * @param path The path name identifying the file to be opened.
   *
   * @param open_flags A set of flags that determine how the file should be
   * opened.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_random_access_file(ExecutionContext& context,
      const char* path, file_base::flags open_flags,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : basic_file<Executor>(context, path, open_flags)
  {
  }

  /// Construct and open a basic_random_access_file.
  /**
   * This constructor initialises and opens a file.
   *
   * @param ex The I/O executor that the file will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the file.
   *
   * @param path The path name identifying the file to be opened.
   *
   * @param open_flags A set of flags that determine how the file should be
   * opened.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_random_access_file(const executor_type& ex,
      const std::string& path, file_base::flags open_flags)
    : basic_file<Executor>(ex, path, open_flags)
  {
  }

  /// Construct and open a basic_random_access_file.
  /**
   * This constructor initialises and opens a file.
   *
   * @param context An execution context which provides the I/O executor that
   * the file will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the file.
   *
   * @param path The path name identifying the file to be opened.
   *
   * @param open_flags A set of flags that determine how the file should be
   * opened.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_random_access_file(ExecutionContext& context,
      const std::string& path, file_base::flags open_flags,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : basic_file<Executor>(context, path, open_flags)
  {
  }

  /// Construct a basic_random_access_file on an existing native file.
  /**
   * This constructor initialises a random-access file object to hold an
   * existing native file.
   *
   * @param ex The I/O executor that the file will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the file.
   *
   * @param native_file The new underlying file implementation.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_random_access_file(const executor_type& ex,
      const native_handle_type& native_file)
    : basic_file<Executor>(ex, native_file)
  {
  }

  /// Construct a basic_random_access_file on an existing native file.
  /**
   * This constructor initialises a random-access file object to hold an
   * existing native file.
   *
   * @param context An execution context which provides the I/O executor that
   * the file will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the file.
   *
   * @param native_file The new underlying file implementation.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_random_access_file(ExecutionContext& context,
      const native_handle_type& native_file,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : basic_file<Executor>(context, native_file)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a basic_random_access_file from another.
  /**
   * This constructor moves a random-access file from one object to another.
   *
   * @param other The other basic_random_access_file object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_random_access_file(const executor_type&)
   * constructor.
   */
  basic_random_access_file(basic_random_access_file&& other) BOOST_ASIO_NOEXCEPT
    : basic_file<Executor>(std::move(other))
  {
  }

  /// Move-assign a basic_random_access_file from another.
  /**
   * This assignment operator moves a random-access file from one object to
   * another.
   *
   * @param other The other basic_random_access_file object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_random_access_file(const executor_type&)
   * constructor.
   */
  basic_random_access_file& operator=(basic_random_access_file&& other)
  {
    basic_file<Executor>::operator=(std::move(other));
    return *this;
  }

  /// Move-construct a basic_random_access_file from a file of another executor
  /// type.
  /**
   * This constructor moves a random-access file from one object to another.
   *
   * @param other The other basic_random_access_file object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_random_access_file(const executor_type&)
   * constructor.
   */
  template <typename Executor1>
  basic_random_access_file(basic_random_access_file<Executor1>&& other,
      typename constraint<
        is_convertible<Executor1, Executor>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : basic_file<Executor>(std::move(other))
  {
  }

  /// Move-assign a basic_random_access_file from a file of another executor
  /// type.
  /**
   * This assignment operator moves a random-access file from one object to
   * another.
   *
   * @param other The other basic_random_access_file object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_random_access_file(const executor_type&)
   * constructor.
   */
  template <typename Executor1>
  typename constraint<
    is_convertible<Executor1, Executor>::value,
    basic_random_access_file&
  >::type operator=(basic_random_access_file<Executor1>&& other)
  {
    basic_file<Executor>::operator=(std::move(other));
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destroys the file.
  /**
   * This function destroys the file, cancelling any outstanding asynchronous
   * operations associated with the file as if by calling @c cancel.
   */
  ~basic_random_access_file()
  {
  }

  /// Write some data to the handle at the specified offset.
  /**
   * This function is used to write data to the random-access handle. The
   * function call will block until one or more bytes of the data has been
   * written successfully, or until an error occurs.
   *
   * @param offset The offset at which the data will be written.
   *
   * @param buffers One or more data buffers to be written to the handle.
   *
   * @returns The number of bytes written.
   *
   * @throws boost::system::system_error Thrown on failure. An error code of
   * boost::asio::error::eof indicates that the end of the file was reached.
   *
   * @note The write_some_at operation may not write all of the data. Consider
   * using the @ref write_at function if you need to ensure that all data is
   * written before the blocking operation completes.
   *
   * @par Example
   * To write a single data buffer use the @ref buffer function as follows:
   * @code
   * handle.write_some_at(42, boost::asio::buffer(data, size));
   * @endcode
   * See the @ref buffer documentation for information on writing multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename ConstBufferSequence>
  std::size_t write_some_at(uint64_t offset,
      const ConstBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().write_some_at(
        this->impl_.get_implementation(), offset, buffers, ec);
    boost::asio::detail::throw_error(ec, "write_some_at");
    return s;
  }

  /// Write some data to the handle at the specified offset.
  /**
   * This function is used to write data to the random-access handle. The
   * function call will block until one or more bytes of the data has been
   * written successfully, or until an error occurs.
   *
   * @param offset The offset at which the data will be written.
   *
   * @param buffers One or more data buffers to be written to the handle.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes written. Returns 0 if an error occurred.
   *
   * @note The write_some operation may not write all of the data to the
   * file. Consider using the @ref write_at function if you need to ensure that
   * all data is written before the blocking operation completes.
   */
  template <typename ConstBufferSequence>
  std::size_t write_some_at(uint64_t offset,
      const ConstBufferSequence& buffers, boost::system::error_code& ec)
  {
    return this->impl_.get_service().write_some_at(
        this->impl_.get_implementation(), offset, buffers, ec);
  }

  /// Start an asynchronous write at the specified offset.
  /**
   * This function is used to asynchronously write data to the random-access
   * handle. It is an initiating function for an @ref asynchronous_operation,
   * and always returns immediately.
   *
   * @param offset The offset at which the data will be written.
   *
   * @param buffers One or more data buffers to be written to the handle.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the completion handler is called.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the write completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred // Number of bytes written.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code, std::size_t) @endcode
   *
   * @note The write operation may not write all of the data to the file.
   * Consider using the @ref async_write_at function if you need to ensure that
   * all data is written before the asynchronous operation completes.
   *
   * @par Example
   * To write a single data buffer use the @ref buffer function as follows:
   * @code
   * handle.async_write_some_at(42, boost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on writing multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   *
   * @par Per-Operation Cancellation
   * This asynchronous operation supports cancellation for the following
   * boost::asio::cancellation_type values:
   *
   * @li @c cancellation_type::terminal
   *
   * @li @c cancellation_type::partial
   *
   * @li @c cancellation_type::total
   */
  template <typename ConstBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) WriteToken
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteToken,
      void (boost::system::error_code, std::size_t))
  async_write_some_at(uint64_t offset,
      const ConstBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(WriteToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WriteToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_write_some_at(this), token, offset, buffers);
  }

  /// Read some data from the handle at the specified offset.
  /**
   * This function is used to read data from the random-access handle. The
   * function call will block until one or more bytes of data has been read
   * successfully, or until an error occurs.
   *
   * @param offset The offset at which the data will be read.
   *
   * @param buffers One or more buffers into which the data will be read.
   *
   * @returns The number of bytes read.
   *
   * @throws boost::system::system_error Thrown on failure. An error code of
   * boost::asio::error::eof indicates that the end of the file was reached.
   *
   * @note The read_some operation may not read all of the requested number of
   * bytes. Consider using the @ref read_at function if you need to ensure that
   * the requested amount of data is read before the blocking operation
   * completes.
   *
   * @par Example
   * To read into a single data buffer use the @ref buffer function as follows:
   * @code
   * handle.read_some_at(42, boost::asio::buffer(data, size));
   * @endcode
   * See the @ref buffer documentation for information on reading into multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence>
  std::size_t read_some_at(uint64_t offset,
      const MutableBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().read_some_at(
        this->impl_.get_implementation(), offset, buffers, ec);
    boost::asio::detail::throw_error(ec, "read_some_at");
    return s;
  }

  /// Read some data from the handle at the specified offset.
  /**
   * This function is used to read data from the random-access handle. The
   * function call will block until one or more bytes of data has been read
   * successfully, or until an error occurs.
   *
   * @param offset The offset at which the data will be read.
   *
   * @param buffers One or more buffers into which the data will be read.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes read. Returns 0 if an error occurred.
   *
   * @note The read_some operation may not read all of the requested number of
   * bytes. Consider using the @ref read_at function if you need to ensure that
   * the requested amount of data is read before the blocking operation
   * completes.
   */
  template <typename MutableBufferSequence>
  std::size_t read_some_at(uint64_t offset,
      const MutableBufferSequence& buffers, boost::system::error_code& ec)
  {
    return this->impl_.get_service().read_some_at(
        this->impl_.get_implementation(), offset, buffers, ec);
  }

  /// Start an asynchronous read at the specified offset.
  /**
   * This function is used to asynchronously read data from the random-access
   * handle. It is an initiating function for an @ref asynchronous_operation,
   * and always returns immediately.
   *
   * @param offset The offset at which the data will be read.
   *
   * @param buffers One or more buffers into which the data will be read.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the completion handler is called.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the read completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred // Number of bytes read.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Completion Signature
   * @code void(boost::system::error_code, std::size_t) @endcode
   *
   * @note The read operation may not read all of the requested number of bytes.
   * Consider using the @ref async_read_at function if you need to ensure that
   * the requested amount of data is read before the asynchronous operation
   * completes.
   *
   * @par Example
   * To read into a single data buffer use the @ref buffer function as follows:
   * @code
   * handle.async_read_some_at(42, boost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on reading into multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   *
   * @par Per-Operation Cancellation
   * This asynchronous operation supports cancellation for the following
   * boost::asio::cancellation_type values:
   *
   * @li @c cancellation_type::terminal
   *
   * @li @c cancellation_type::partial
   *
   * @li @c cancellation_type::total
   */
  template <typename MutableBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) ReadToken
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadToken,
      void (boost::system::error_code, std::size_t))
  async_read_some_at(uint64_t offset,
      const MutableBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(ReadToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_read_some_at(this), token, offset, buffers);
  }

private:
  // Disallow copying and assignment.
  basic_random_access_file(const basic_random_access_file&) BOOST_ASIO_DELETED;
  basic_random_access_file& operator=(
      const basic_random_access_file&) BOOST_ASIO_DELETED;

  class initiate_async_write_some_at
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_write_some_at(basic_random_access_file* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename WriteHandler, typename ConstBufferSequence>
    void operator()(BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
        uint64_t offset, const ConstBufferSequence& buffers) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a WriteHandler.
      BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

      detail::non_const_lvalue<WriteHandler> handler2(handler);
      self_->impl_.get_service().async_write_some_at(
          self_->impl_.get_implementation(), offset, buffers,
          handler2.value, self_->impl_.get_executor());
    }

  private:
    basic_random_access_file* self_;
  };

  class initiate_async_read_some_at
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_read_some_at(basic_random_access_file* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename ReadHandler, typename MutableBufferSequence>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        uint64_t offset, const MutableBufferSequence& buffers) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      detail::non_const_lvalue<ReadHandler> handler2(handler);
      self_->impl_.get_service().async_read_some_at(
          self_->impl_.get_implementation(), offset, buffers,
          handler2.value, self_->impl_.get_executor());
    }

  private:
    basic_random_access_file* self_;
  };
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_FILE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_BASIC_RANDOM_ACCESS_FILE_HPP

/* basic_random_access_file.hpp
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
*/