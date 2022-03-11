//
// posix/basic_stream_descriptor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_POSIX_BASIC_STREAM_DESCRIPTOR_HPP
#define BOOST_ASIO_POSIX_BASIC_STREAM_DESCRIPTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/posix/descriptor.hpp>

#if defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR) \
  || defined(GENERATING_DOCUMENTATION)

namespace boost {
namespace asio {
namespace posix {

/// Provides stream-oriented descriptor functionality.
/**
 * The posix::basic_stream_descriptor class template provides asynchronous and
 * blocking stream-oriented descriptor functionality.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 *
 * @par Concepts:
 * AsyncReadStream, AsyncWriteStream, Stream, SyncReadStream, SyncWriteStream.
 */
template <typename Executor = executor>
class basic_stream_descriptor
  : public basic_descriptor<Executor>
{
public:
  /// The type of the executor associated with the object.
  typedef Executor executor_type;

  /// Rebinds the descriptor type to another executor.
  template <typename Executor1>
  struct rebind_executor
  {
    /// The descriptor type when rebound to the specified executor.
    typedef basic_stream_descriptor<Executor1> other;
  };

  /// The native representation of a descriptor.
  typedef typename basic_descriptor<Executor>::native_handle_type
    native_handle_type;

  /// Construct a stream descriptor without opening it.
  /**
   * This constructor creates a stream descriptor without opening it. The
   * descriptor needs to be opened and then connected or accepted before data
   * can be sent or received on it.
   *
   * @param ex The I/O executor that the descriptor will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * descriptor.
   */
  explicit basic_stream_descriptor(const executor_type& ex)
    : basic_descriptor<Executor>(ex)
  {
  }

  /// Construct a stream descriptor without opening it.
  /**
   * This constructor creates a stream descriptor without opening it. The
   * descriptor needs to be opened and then connected or accepted before data
   * can be sent or received on it.
   *
   * @param context An execution context which provides the I/O executor that
   * the descriptor will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the descriptor.
   */
  template <typename ExecutionContext>
  explicit basic_stream_descriptor(ExecutionContext& context,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : basic_descriptor<Executor>(context)
  {
  }

  /// Construct a stream descriptor on an existing native descriptor.
  /**
   * This constructor creates a stream descriptor object to hold an existing
   * native descriptor.
   *
   * @param ex The I/O executor that the descriptor will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * descriptor.
   *
   * @param native_descriptor The new underlying descriptor implementation.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_stream_descriptor(const executor_type& ex,
      const native_handle_type& native_descriptor)
    : basic_descriptor<Executor>(ex, native_descriptor)
  {
  }

  /// Construct a stream descriptor on an existing native descriptor.
  /**
   * This constructor creates a stream descriptor object to hold an existing
   * native descriptor.
   *
   * @param context An execution context which provides the I/O executor that
   * the descriptor will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the descriptor.
   *
   * @param native_descriptor The new underlying descriptor implementation.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_stream_descriptor(ExecutionContext& context,
      const native_handle_type& native_descriptor,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : basic_descriptor<Executor>(context, native_descriptor)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a stream descriptor from another.
  /**
   * This constructor moves a stream descriptor from one object to another.
   *
   * @param other The other stream descriptor object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_stream_descriptor(const executor_type&)
   * constructor.
   */
  basic_stream_descriptor(basic_stream_descriptor&& other) BOOST_ASIO_NOEXCEPT
    : descriptor(std::move(other))
  {
  }

  /// Move-assign a stream descriptor from another.
  /**
   * This assignment operator moves a stream descriptor from one object to
   * another.
   *
   * @param other The other stream descriptor object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_stream_descriptor(const executor_type&)
   * constructor.
   */
  basic_stream_descriptor& operator=(basic_stream_descriptor&& other)
  {
    descriptor::operator=(std::move(other));
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Write some data to the descriptor.
  /**
   * This function is used to write data to the stream descriptor. The function
   * call will block until one or more bytes of the data has been written
   * successfully, or until an error occurs.
   *
   * @param buffers One or more data buffers to be written to the descriptor.
   *
   * @returns The number of bytes written.
   *
   * @throws boost::system::system_error Thrown on failure. An error code of
   * boost::asio::error::eof indicates that the connection was closed by the
   * peer.
   *
   * @note The write_some operation may not transmit all of the data to the
   * peer. Consider using the @ref write function if you need to ensure that
   * all data is written before the blocking operation completes.
   *
   * @par Example
   * To write a single data buffer use the @ref buffer function as follows:
   * @code
   * descriptor.write_some(boost::asio::buffer(data, size));
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

  /// Write some data to the descriptor.
  /**
   * This function is used to write data to the stream descriptor. The function
   * call will block until one or more bytes of the data has been written
   * successfully, or until an error occurs.
   *
   * @param buffers One or more data buffers to be written to the descriptor.
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
   * This function is used to asynchronously write data to the stream
   * descriptor. The function call always returns immediately.
   *
   * @param buffers One or more data buffers to be written to the descriptor.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param handler The handler to be called when the write operation completes.
   * Copies will be made of the handler as required. The function signature of
   * the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes written.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @note The write operation may not transmit all of the data to the peer.
   * Consider using the @ref async_write function if you need to ensure that all
   * data is written before the asynchronous operation completes.
   *
   * @par Example
   * To write a single data buffer use the @ref buffer function as follows:
   * @code
   * descriptor.async_write_some(boost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on writing multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename ConstBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) WriteHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
      void (boost::system::error_code, std::size_t))
  async_write_some(const ConstBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(WriteHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WriteHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_write_some(this), handler, buffers);
  }

  /// Read some data from the descriptor.
  /**
   * This function is used to read data from the stream descriptor. The function
   * call will block until one or more bytes of data has been read successfully,
   * or until an error occurs.
   *
   * @param buffers One or more buffers into which the data will be read.
   *
   * @returns The number of bytes read.
   *
   * @throws boost::system::system_error Thrown on failure. An error code of
   * boost::asio::error::eof indicates that the connection was closed by the
   * peer.
   *
   * @note The read_some operation may not read all of the requested number of
   * bytes. Consider using the @ref read function if you need to ensure that
   * the requested amount of data is read before the blocking operation
   * completes.
   *
   * @par Example
   * To read into a single data buffer use the @ref buffer function as follows:
   * @code
   * descriptor.read_some(boost::asio::buffer(data, size));
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

  /// Read some data from the descriptor.
  /**
   * This function is used to read data from the stream descriptor. The function
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
   * This function is used to asynchronously read data from the stream
   * descriptor. The function call always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be read.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param handler The handler to be called when the read operation completes.
   * Copies will be made of the handler as required. The function signature of
   * the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes read.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @note The read operation may not read all of the requested number of bytes.
   * Consider using the @ref async_read function if you need to ensure that the
   * requested amount of data is read before the asynchronous operation
   * completes.
   *
   * @par Example
   * To read into a single data buffer use the @ref buffer function as follows:
   * @code
   * descriptor.async_read_some(boost::asio::buffer(data, size), handler);
   * @endcode
   * See the @ref buffer documentation for information on reading into multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) ReadHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
      void (boost::system::error_code, std::size_t))
  async_read_some(const MutableBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(ReadHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_read_some(this), handler, buffers);
  }

private:
  class initiate_async_write_some
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_write_some(basic_stream_descriptor* self)
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
          self_->impl_.get_implementation(), buffers, handler2.value,
          self_->impl_.get_implementation_executor());
    }

  private:
    basic_stream_descriptor* self_;
  };

  class initiate_async_read_some
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_read_some(basic_stream_descriptor* self)
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
          self_->impl_.get_implementation(), buffers, handler2.value,
          self_->impl_.get_implementation_executor());
    }

  private:
    basic_stream_descriptor* self_;
  };
};

} // namespace posix
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_POSIX_BASIC_STREAM_DESCRIPTOR_HPP

/* basic_stream_descriptor.hpp
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
*/