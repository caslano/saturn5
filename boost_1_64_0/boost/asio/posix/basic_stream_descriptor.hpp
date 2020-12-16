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
9OQ6836cxIbIHWq1pN8/PZb+UMI4/yO04wnrSdjccDT8uGJKDuWm54d6gZ/qxBlg+0wDefXcJ0y9kntgrnCckydfhEm+XHcCF6d47wTeBa21W+qvs9aWyjWulexYRyzfukj5KV+6xI/Ilnhh0LpK/KndGWzkdtxDS7qESbquvKSkRhMATN9yJ/xhb15WlXFMUC/QCcwLfHo3kfnmRveaTFyX8tFH86HfLrjyMCgtyvwO3ADF2+Et9MtDpX0FZUsjJN48aBucKXwNmqdYOgWmbX1Y/CE5v5eO4h7CDR9vf3dypdTXWHgbLjuf8PAI530orrtlR8D3Mhk7kR2t78v6s14Efm5kx+feZB/OpSf3efajqpfpuH42ql4O+elFtraDdfKS8AxVHcTSyDU6SX1PVCfx9tvhHaMXdCYPu/Q7kjk4sdMWK9v3+OShtr62uZ08TBae8SpzLI1sUzZz3wR5C7VTKFV5L8TthLbVT1626p310EqQ9wPCc6bl6nM7cb+ds228mO7tq+61x1o/eeir9L7wgPatfKTWy5yBXB/rp4jrej+l7VvPlq135WFPT/8+ynpvQB7a76PgC+yjiHtz+6i5mof9vaLMmZpIBu4+eMNBeTBTg8B8KG+mzCcK0+Q7w+ot0WNtWiaGRs9Quu8Iq4nHdym/uZpfnk2YPltp8wT1bq+EOrklw1snH7DbdJAuIs0NTdXBeoDP1Mn+w+x4M3YS1/06SZqERVz3fpVkes9pPEjHUfTe2DmNVdOK3mKu1dKx3Xs+A3pzp9ZXs33v1IKm63dq8UzPnVo8x3On1qvyPWbQ+Yfg8xsfTrHDmwtueW3b8gfW3Dj+0kfCU3u+eOrnIt4sO1V95tvhd00bOm3zzyOPl7zn1pPv+OaaJ4POUbx55yKK5bk3W+HvR9YefPqNNbcfu+nE84TNE/ln/XHsmJWvb71578I1ecd73MqG1ZOpdvhXn1n1mw/XDTz29zt3z//RiE/9nr1MCd/389XD7i9/tNeNGQdDua9/iA36XqLnj6y+ZtXxtNs/8LY9/Y4e/OAdT576+Yp/1x1RzSL/9g89+P1ffKOoaNs3SrfU3vbB46d+3uNUzwUFnf95PX53i8zRikCqs7zvzFCbocP190CL9qa/dT/cOmHpO6S8x8bpXtQ0q9Xu6QZwGLgZnA3Wg3PBBvACMAKWgC1gJXgleAV4G3gNeDt4M9gIPgVeAR4E7wSPgFeDL4DXgi+B14F/Aa8H/672SHsi2zbwDPDt4ALwRnAZeBNYAd4CVoG3grXgLvAm8A7wTvBOcz+Tvo8A6bbfbWdZ9p6lUwVTwHmg2h03/GHlT/XhH6v848AkcLymc4by25GFyv8O4XefnbhI+UvAAeovAEvBEeBKcAp4CTgLXAUuAFeDl4E4OdOwDtwMloFXghXgdnC9c+9T5Zgucrj3PoeqHIVgP/XngiPAgeBIsAgcBer9QjofRYeSnvt+oXw9E1IATgQHgmeDgzQf+I1crZpOqY9cYbV3nAWOAvuB48EcrY/9wQvB3Hh5Ma8LLu+pms9pWk7TtbzPdtaX9waX90TlP0vLu0jTmeSsL8qf6cO/SPkXK98SMANcGudnDhAs/0zlP0f5Z6n8s0Fjp1b5c0U+x16p1ouTKWKntsP90qUN7NGVsQ83i/083B5cG+4E4UfU1uFa4rfgUmazv9jIXiRu5Oz4/up9+PfhYvuszzaSLvF1uFfx3w3uxZ0k/CAYPhN5wEIw81zQdlewr4irwk0lvJiwu/n9ftxafj8G+u3RbifuCHG7kO/9/G4jLNwU3bc9iP9V3FT8S3F1uF12HO44bsZ55EFtNm4FB0Wi+7w7+T0WnB+J7/c=
*/