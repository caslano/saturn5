//
// basic_stream_file.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_STREAM_FILE_HPP
#define BOOST_ASIO_BASIC_STREAM_FILE_HPP

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

#if !defined(BOOST_ASIO_BASIC_STREAM_FILE_FWD_DECL)
#define BOOST_ASIO_BASIC_STREAM_FILE_FWD_DECL

// Forward declaration with defaulted arguments.
template <typename Executor = any_io_executor>
class basic_stream_file;

#endif // !defined(BOOST_ASIO_BASIC_STREAM_FILE_FWD_DECL)

/// Provides stream-oriented file functionality.
/**
 * The basic_stream_file class template provides asynchronous and blocking
 * stream-oriented file functionality.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 *
 * @par Concepts:
 * AsyncReadStream, AsyncWriteStream, Stream, SyncReadStream, SyncWriteStream.
 */
template <typename Executor>
class basic_stream_file
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
    typedef basic_stream_file<Executor1> other;
  };

  /// The native representation of a file.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined native_handle_type;
#else
  typedef typename basic_file<Executor>::native_handle_type native_handle_type;
#endif

  /// Construct a basic_stream_file without opening it.
  /**
   * This constructor initialises a file without opening it. The file needs to
   * be opened before data can be read from or or written to it.
   *
   * @param ex The I/O executor that the file will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the file.
   */
  explicit basic_stream_file(const executor_type& ex)
    : basic_file<Executor>(ex)
  {
    this->impl_.get_service().set_is_stream(
        this->impl_.get_implementation(), true);
  }

  /// Construct a basic_stream_file without opening it.
  /**
   * This constructor initialises a file without opening it. The file needs to
   * be opened before data can be read from or or written to it.
   *
   * @param context An execution context which provides the I/O executor that
   * the file will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the file.
   */
  template <typename ExecutionContext>
  explicit basic_stream_file(ExecutionContext& context,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : basic_file<Executor>(context)
  {
    this->impl_.get_service().set_is_stream(
        this->impl_.get_implementation(), true);
  }

  /// Construct and open a basic_stream_file.
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
  basic_stream_file(const executor_type& ex,
      const char* path, file_base::flags open_flags)
    : basic_file<Executor>(ex)
  {
    boost::system::error_code ec;
    this->impl_.get_service().set_is_stream(
        this->impl_.get_implementation(), true);
    this->impl_.get_service().open(
        this->impl_.get_implementation(),
        path, open_flags, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  /// Construct and open a basic_stream_file.
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
  basic_stream_file(ExecutionContext& context,
      const char* path, file_base::flags open_flags,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : basic_file<Executor>(context)
  {
    boost::system::error_code ec;
    this->impl_.get_service().set_is_stream(
        this->impl_.get_implementation(), true);
    this->impl_.get_service().open(
        this->impl_.get_implementation(),
        path, open_flags, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  /// Construct and open a basic_stream_file.
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
  basic_stream_file(const executor_type& ex,
      const std::string& path, file_base::flags open_flags)
    : basic_file<Executor>(ex)
  {
    boost::system::error_code ec;
    this->impl_.get_service().set_is_stream(
        this->impl_.get_implementation(), true);
    this->impl_.get_service().open(
        this->impl_.get_implementation(),
        path.c_str(), open_flags, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  /// Construct and open a basic_stream_file.
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
  basic_stream_file(ExecutionContext& context,
      const std::string& path, file_base::flags open_flags,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : basic_file<Executor>(context)
  {
    boost::system::error_code ec;
    this->impl_.get_service().set_is_stream(
        this->impl_.get_implementation(), true);
    this->impl_.get_service().open(
        this->impl_.get_implementation(),
        path.c_str(), open_flags, ec);
    boost::asio::detail::throw_error(ec, "open");
  }

  /// Construct a basic_stream_file on an existing native file.
  /**
   * This constructor initialises a stream file object to hold an existing
   * native file.
   *
   * @param ex The I/O executor that the file will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the file.
   *
   * @param native_file The new underlying file implementation.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_stream_file(const executor_type& ex,
      const native_handle_type& native_file)
    : basic_file<Executor>(ex, native_file)
  {
    this->impl_.get_service().set_is_stream(
        this->impl_.get_implementation(), true);
  }

  /// Construct a basic_stream_file on an existing native file.
  /**
   * This constructor initialises a stream file object to hold an existing
   * native file.
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
  basic_stream_file(ExecutionContext& context,
      const native_handle_type& native_file,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : basic_file<Executor>(context, native_file)
  {
    this->impl_.get_service().set_is_stream(
        this->impl_.get_implementation(), true);
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a basic_stream_file from another.
  /**
   * This constructor moves a stream file from one object to another.
   *
   * @param other The other basic_stream_file object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_stream_file(const executor_type&)
   * constructor.
   */
  basic_stream_file(basic_stream_file&& other) BOOST_ASIO_NOEXCEPT
    : basic_file<Executor>(std::move(other))
  {
  }

  /// Move-assign a basic_stream_file from another.
  /**
   * This assignment operator moves a stream file from one object to another.
   *
   * @param other The other basic_stream_file object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_stream_file(const executor_type&)
   * constructor.
   */
  basic_stream_file& operator=(basic_stream_file&& other)
  {
    basic_file<Executor>::operator=(std::move(other));
    return *this;
  }

  /// Move-construct a basic_stream_file from a file of another executor
  /// type.
  /**
   * This constructor moves a stream file from one object to another.
   *
   * @param other The other basic_stream_file object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_stream_file(const executor_type&)
   * constructor.
   */
  template <typename Executor1>
  basic_stream_file(basic_stream_file<Executor1>&& other,
      typename constraint<
        is_convertible<Executor1, Executor>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
    : basic_file<Executor>(std::move(other))
  {
  }

  /// Move-assign a basic_stream_file from a file of another executor type.
  /**
   * This assignment operator moves a stream file from one object to another.
   *
   * @param other The other basic_stream_file object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_stream_file(const executor_type&)
   * constructor.
   */
  template <typename Executor1>
  typename constraint<
    is_convertible<Executor1, Executor>::value,
    basic_stream_file&
  >::type operator=(basic_stream_file<Executor1>&& other)
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
  ~basic_stream_file()
  {
  }

  /// Seek to a position in the file.
  /**
   * This function updates the current position in the file.
   *
   * @param offset The requested position in the file, relative to @c whence.
   *
   * @param whence One of @c seek_set, @c seek_cur or @c seek_end.
   *
   * @returns The new position relative to the beginning of the file.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  uint64_t seek(int64_t offset, file_base::seek_basis whence)
  {
    boost::system::error_code ec;
    uint64_t n = this->impl_.get_service().seek(
        this->impl_.get_implementation(), offset, whence, ec);
    boost::asio::detail::throw_error(ec, "seek");
    return n;
  }

  /// Seek to a position in the file.
  /**
   * This function updates the current position in the file.
   *
   * @param offset The requested position in the file, relative to @c whence.
   *
   * @param whence One of @c seek_set, @c seek_cur or @c seek_end.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The new position relative to the beginning of the file.
   */
  uint64_t seek(int64_t offset, file_base::seek_basis whence,
      boost::system::error_code& ec)
  {
    return this->impl_.get_service().seek(
        this->impl_.get_implementation(), offset, whence, ec);
  }

  /// Write some data to the file.
  /**
   * This function is used to write data to the stream file. The function call
   * will block until one or more bytes of the data has been written
   * successfully, or until an error occurs.
   *
   * @param buffers One or more data buffers to be written to the file.
   *
   * @returns The number of bytes written.
   *
   * @throws boost::system::system_error Thrown on failure. An error code of
   * boost::asio::error::eof indicates that the end of the file was reached.
   *
   * @note The write_some operation may not transmit all of the data to the
   * peer. Consider using the @ref write function if you need to ensure that
   * all data is written before the blocking operation completes.
   *
   * @par Example
   * To write a single data buffer use the @ref buffer function as follows:
   * @code
   * file.write_some(boost::asio::buffer(data, size));
   * @endcode
   * See the @ref buffer documentation for information on writing multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().write_some(
        this->impl_.get_implementation(), buffers, ec);
    boost::asio::detail::throw_error(ec, "write_some");
    return s;
  }

  /// Write some data to the file.
  /**
   * This function is used to write data to the stream file. The function call
   * will block until one or more bytes of the data has been written
   * successfully, or until an error occurs.
   *
   * @param buffers One or more data buffers to be written to the file.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes written. Returns 0 if an error occurred.
   *
   * @note The write_some operation may not transmit all of the data to the
   * peer. Consider using the @ref write function if you need to ensure that
   * all data is written before the blocking operation completes.
   */
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers,
      boost::system::error_code& ec)
  {
    return this->impl_.get_service().write_some(
        this->impl_.get_implementation(), buffers, ec);
  }

  /// Start an asynchronous write.
  /**
   * This function is used to asynchronously write data to the stream file.
   * It is an initiating function for an @ref asynchronous_operation, and always
   * returns immediately.
   *
   * @param buffers One or more data buffers to be written to the file.
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
   * @note The write operation may not transmit all of the data to the peer.
   * Consider using the @ref async_write function if you need to ensure that all
   * data is written before the asynchronous operation completes.
   *
   * @par Example
   * To write a single data buffer use the @ref buffer function as follows:
   * @code
   * file.async_write_some(boost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on writing multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   *
   * @par Per-Operation Cancellation
   * On POSIX or Windows operating systems, this asynchronous operation supports
   * cancellation for the following boost::asio::cancellation_type values:
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
  async_write_some(const ConstBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(WriteToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WriteToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_write_some(this), token, buffers);
  }

  /// Read some data from the file.
  /**
   * This function is used to read data from the stream file. The function
   * call will block until one or more bytes of data has been read successfully,
   * or until an error occurs.
   *
   * @param buffers One or more buffers into which the data will be read.
   *
   * @returns The number of bytes read.
   *
   * @throws boost::system::system_error Thrown on failure. An error code of
   * boost::asio::error::eof indicates that the end of the file was reached.
   *
   * @note The read_some operation may not read all of the requested number of
   * bytes. Consider using the @ref read function if you need to ensure that
   * the requested amount of data is read before the blocking operation
   * completes.
   *
   * @par Example
   * To read into a single data buffer use the @ref buffer function as follows:
   * @code
   * file.read_some(boost::asio::buffer(data, size));
   * @endcode
   * See the @ref buffer documentation for information on reading into multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().read_some(
        this->impl_.get_implementation(), buffers, ec);
    boost::asio::detail::throw_error(ec, "read_some");
    return s;
  }

  /// Read some data from the file.
  /**
   * This function is used to read data from the stream file. The function
   * call will block until one or more bytes of data has been read successfully,
   * or until an error occurs.
   *
   * @param buffers One or more buffers into which the data will be read.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes read. Returns 0 if an error occurred.
   *
   * @note The read_some operation may not read all of the requested number of
   * bytes. Consider using the @ref read function if you need to ensure that
   * the requested amount of data is read before the blocking operation
   * completes.
   */
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers,
      boost::system::error_code& ec)
  {
    return this->impl_.get_service().read_some(
        this->impl_.get_implementation(), buffers, ec);
  }

  /// Start an asynchronous read.
  /**
   * This function is used to asynchronously read data from the stream file.
   * It is an initiating function for an @ref asynchronous_operation, and always
   * returns immediately.
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
   * Consider using the @ref async_read function if you need to ensure that the
   * requested amount of data is read before the asynchronous operation
   * completes.
   *
   * @par Example
   * To read into a single data buffer use the @ref buffer function as follows:
   * @code
   * file.async_read_some(boost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on reading into multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   *
   * @par Per-Operation Cancellation
   * On POSIX or Windows operating systems, this asynchronous operation supports
   * cancellation for the following boost::asio::cancellation_type values:
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
  async_read_some(const MutableBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(ReadToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_read_some(this), token, buffers);
  }

private:
  // Disallow copying and assignment.
  basic_stream_file(const basic_stream_file&) BOOST_ASIO_DELETED;
  basic_stream_file& operator=(const basic_stream_file&) BOOST_ASIO_DELETED;

  class initiate_async_write_some
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_write_some(basic_stream_file* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename WriteHandler, typename ConstBufferSequence>
    void operator()(BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
        const ConstBufferSequence& buffers) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a WriteHandler.
      BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

      detail::non_const_lvalue<WriteHandler> handler2(handler);
      self_->impl_.get_service().async_write_some(
          self_->impl_.get_implementation(), buffers,
          handler2.value, self_->impl_.get_executor());
    }

  private:
    basic_stream_file* self_;
  };

  class initiate_async_read_some
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_read_some(basic_stream_file* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename ReadHandler, typename MutableBufferSequence>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        const MutableBufferSequence& buffers) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      detail::non_const_lvalue<ReadHandler> handler2(handler);
      self_->impl_.get_service().async_read_some(
          self_->impl_.get_implementation(), buffers,
          handler2.value, self_->impl_.get_executor());
    }

  private:
    basic_stream_file* self_;
  };
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_FILE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_BASIC_STREAM_FILE_HPP

/* basic_stream_file.hpp
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
*/