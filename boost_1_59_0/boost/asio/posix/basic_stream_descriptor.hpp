//
// posix/basic_stream_descriptor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/posix/basic_descriptor.hpp>

#if defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/push_options.hpp>

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
 * Synchronous @c read_some and @c write_some operations are thread safe with
 * respect to each other, if the underlying operating system calls are also
 * thread safe. This means that it is permitted to perform concurrent calls to
 * these synchronous operations on a single descriptor object. Other synchronous
 * operations, such as @c close, are not thread safe.
 *
 * @par Concepts:
 * AsyncReadStream, AsyncWriteStream, Stream, SyncReadStream, SyncWriteStream.
 */
template <typename Executor = any_io_executor>
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value,
        defaulted_constraint
      >::type = defaulted_constraint())
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
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
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
    : basic_descriptor<Executor>(std::move(other))
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
    basic_descriptor<Executor>::operator=(std::move(other));
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
   * descriptor. It is an initiating function for an @ref
   * asynchronous_operation, and always returns immediately.
   *
   * @param buffers One or more data buffers to be written to the descriptor.
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
   * descriptor.async_write_some(boost::asio::buffer(data, size), handler);
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
  async_write_some(const ConstBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(WriteToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WriteToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_write_some(this), token, buffers);
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
   * descriptor. It is an initiating function for an @ref
   * asynchronous_operation, and always returns immediately.
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
   * descriptor.async_read_some(boost::asio::buffer(data, size), handler);
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
  async_read_some(const MutableBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(ReadToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadToken,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_read_some(this), token, buffers);
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
          self_->impl_.get_implementation(), buffers,
          handler2.value, self_->impl_.get_executor());
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
          self_->impl_.get_implementation(), buffers,
          handler2.value, self_->impl_.get_executor());
    }

  private:
    basic_stream_descriptor* self_;
  };
};

} // namespace posix
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_POSIX_BASIC_STREAM_DESCRIPTOR_HPP

/* basic_stream_descriptor.hpp
bwS0MYtCAx//TYSapWnju+D2y0R7bBeu+RNtbU5vQvOy8Di/Q1ccdIgLawL/R9ge269V5/j+ru6fAstNU1OCwCistDK5dZ4pCdayf4AlrxM7S4asma8vtyDWTcVut8yuPeGxCzNDhFfExWIKTSG1YYdZ91qHpoMtYNVhxNBUd5Ck0Ot34qSRQg/jFlApD+KWULHISGimOghxqL4hJ1H76LDKYdUY0Tjh9rjS+lHtXb6PYo2bLQ36SIKtjAAILPfTqlgB5zcDjdCDrr8OaA3vuC23gh9EHvNaB91SUqKXJxJRLpIHCO0yJy/KTuGlfRECg+IjzQIsseVxGjBOD2W/7BPaEGbO2jscmfYxULuQPDXCoZiU47aUCC7/yBtWwuFwDvCkxkxAgC81kUSImT7C02EUEp+9/eKAhamjzsMwMLDhNDfeJRNjqxQ8XMSES1oJbHe6gSRQupvinuo9dU8j/RgCeATAkssbcYi4NFaSYRWdAWqi4q6+GI68o2PqmvY8BGBSzxGhoaEyYf/DctgBhcICHH1GYWkroSJk0Wqg4nmJfOfgBTm7Kzmj47NXVEA/klP0Qn/Lb0lq+w1FRATmTyeCAiZIJppw5v8nkOBMALylMzb/Hgk7iNSJxJlSb6+NuuaIpoKfdNiMBb303hzPPT1z/gO2edaSTDA98x6g/+A8zgz8TAWIDFgAma+SSn419SxCcZWdeW117Tn9ecT/VBmL6+3kUu2MEYjOQ+sdpluNU42DQXjNBVlfNg42SDlY8znSQa+PTilYDS0vQy9f9+RhoB/yes1gTzy6p4ewIIkia5ExeW2sS+lJToR1lGcOIOao5m92wADD52avzuwZU3eEh+Wmxtez40Hq+nrW2BqXWa9NvySOlbMkJNctJzVOjDXwHp/Iv2GEFt5an8++996zQVxbNASjPzhRBls+SDnFkvRobC4G3mD/wGt2mhIzLWS94+C5v2r5OfYRZB5oLCyyeCEoYTunB3qwdBjWS9QsCnNZsjY3FFFy62xQoB62AS+KGFpjtkvvRLxvFYhBeGpVypHU8hKZI6spNFYRUnN7ccx1TYVqGxiuAQHtIy5V6esjrrEJOMinhP5yTlIOneKbNhfS1U92UidMruD65KF1D03jeVQXGAerXUWSrENb8tJ1xvndNmR2Rmde9S3wTYkH6sgafnx3zdinmKfjeo56Wr/yvM8dyJqvIztSMXAuJ51a6mu5OsGxT9FD9qBYAX9wXC7KfpO4Bji8Ms5X+oOZrE2ZqkAZzrXBd7rViU3TTdiEkIQQRfRUqGqRH9+PKhCOjbe9oraKvWK0Qr2ihAepUttB2InMgdKB3hnDAcnJ2KHCockpLm84XmTgfvvvike6pGNoSnKUSvKAXzYjmjODROu01UuQ/8wAKnFaAvOSldkeFg/V9KoOEsL2HMxo2iCdsC7yED2o3wWrphGDiU7W69mRgqZ1AFDemd7FmN7F2n5B899HPWYzeqXXIKjxRQa2MVV6VjvIucYHuve/BrFKsyx2mIsYzPEiTHpHyWorqP8YVydYwOgtq61g/mNcnFABpaeqtoL7r1Ht7UBL0Nam8Q60PKSn94DOqiQEZTfCtKA2xLmG1HrVgQDSVt/NcIeddWmiCHBIgc+qP92gKCR5NsHUoABszgqSt0MOuK3cnyNn0Kyy4FW7HNDvn5+gRn/h0hy0ywpAEmrf7OQ56DNfVUKPdAWYxajIJFoVWERFlM5dI8qaqKSbsOS/XVkVvYWUO/LmJ+sA6D0IlCdrW/6qrB5phCG+dSu0vsGJs01i/qlaLkEpr/6+f1G3hrNeKZaUud6zQOWReLndAtFD8PKxlO9Q4d6CsRVPrvGLS6klXoogw+6O6jKgXhn4Ktziclz2anBX+GL0HVnFldfrCc912DVn6w1PdUrZzHZhe4drOaxl2GRi7Jzkq3QR2AzgwoEK1zozqOvB8P9oeRBe/h7pwQfxBwAMtsU7W1CA1b/sXAnPFp0kVh1VbTRt33aatpK7fi4XHoJhSfV3t9X0+fJVkrllf0xayuMla2r/5AM7NR5WkbiBCttx21Y1mxDBLBT2FoHhhpVogzkMhZuXmYf7cyMWzhuSnycpnSeskjnEiXjy5sBywWZYSNx312IKBZoLxF2bwdw9TK7+nDtJOlmQHtYhBLCrXkxVm9uoaRPtY9QjESpI7NzG4tNUUatsw97VXHaZpXN8my98x7BA+tEcCyZDrHxg+aeka7moif0kGoHbr2cYX3iuMv0nxsDvVblKH22SLZVnSs4CtzBzQ6MD5m8k9O/WNNtFPYsgMTnT/MHyNAkpJnchmMD74I/xfkwkI7z/6kNixnPQh3YuK9B47BB1+9D+PabC19Va+2bCPsRhWlUrQef8nLFaAgKW3hWacOwl4N9pl1tehpbjICgH+RmcI3bxmPIgZD5uML0JtJ8fryYd/reu0UPmwxi6DN42CCt7l75y/B715hl8dvSkvCDLvTy1ydBpu0HcJ4GGrFelwLGrgaEq53XlnOTBKV0W25XJQ8UlpezY3MOh8NotucqUsyiz8Fix6kR7b1PQASPJ3z2vkkYwxd9mvsYBeHGHn9NJi+LPgSTqr7S2ZooyyQrQr4Mff6BYsMV5xCj5g97M6GobUrAm9Fs+7IPHtOMyflt2vNSYL5r9nxQoxY8DkQ/tduJhQUslI2lX9W0Lmkbp+2gPK8Eyh86pq5EZjPJM5hAWYYwd8L+k0nLmh6hFg8r3V+BILcpsWHjRtsIsDsUePBsYba0cG3c+6kdaT1peGt8Og8byngNuB42b/Z+w3AMrdtWahUb0+Smc+kHlBpuQ2bbTi2XHUUWa2iw0UtrRaR+m9MqCDNNsl4notlcPnlzW4bGhNeM4dLHVxU1WsxQ6/sRSot5sCQCv3AvYKPAQDronS2LVB5vZ0oc1pCfLIiUF29NSgw3a1xmSLArYymXetcHN0I1Ta7jXEpJ7uxUWMXRhMBZLmlmrZiG+WW+s7xNYb1Gx0chhxdZmDeho1CRJMT3P7m0EZH0xiKhDBi4H+9tCeanoOqN7CLv1CYdhND4k3Xo8HGurQa8lehJoQem3MlQLJMI91h5ZpWgl0hn05M1U5ljUYnOnUHbZNqox6dfCqjxDocCqO2mg0uADJuWtLyP5VJEiccet4Fem4hC/8UHUdwZQ+Wd4whdIrVIruDOrU7dUtw8LmIqL2zfumS45/PSmjswyD45oTkeG1fASBtNLQA7eLZ7N92k7/guloSIaoR60qIefDiP6WuiEomQTYtekkz5tpKebVkkzhQIL3l+aM+czFJ7VbPnGvE7QY0YgWEmKD6S885jWWkksQcqjs7k3gPPKc9aaO11fJx6OK+TIpBCGdCLmyCIoCJC+KXpcEApmrXuoVj9ealq3DSmmUF0MPC3sOt0bdyXW2/OOZIGKvGoYrRFslPtEN7quMiK174HTw+ufJNw2BiAXLIck40rFxmiyKy6GVSuOhE2rw24ruoeJQZP5y/PRSpHlQLBQjEK/wBAMV9tUwOyuQqO2L0+cspFPkZvCOqKOdnYsJFGkRS68xFF9S9wcwcmRCfb3kGd8L3i02YlnwC8Y2GBB1cacf1/xwKp3tWk0kcmXhm9HXHjZ875XTMbSQkJ3dp4b0kWn2vctV68k85l2XVNuslcaZxgX6uflDhOphomPabjjpoGdiIh0CivSkzWxzyB80mCisKCFn3LTrznfP6DJKPj4maZI9bS0uJB2j/S8MR12CmR9ST1inegqbM8+fnE8jF/fPaW0SuMH08dLd2nPgrGQhu15K6Nfczq54OFJtOaahfWy+aXwbiftk1AY8M175ZEGMMRppkjddrnY6OHLBWAe1Sx9V+zLtFFhI/ufFelzOUIY5OyFDgcb4JkMEUAJNvSy6v4BvGNxve48eR3eCcVG196JOCvEO7usdfclhD3iPuljpCVNsi9JhjJe6cQMEobAGznbsO6XE8WzD0k+MiH+W/yIlOImVBoaGBF8cThpLBDaGel0GJPa+5KiLYjDG5lGb4joGZQMUvn/DS9etuRr31Mo54MWLGUqiY6RMk7liNBjxlKbkX1lDWQ3s/8XK3BQWSbPj2zk+NXQtvE2QBPN+ZTpZU/2KJ+jnQ07o5hzkmQcX5hVWd+pDSHqUkvuIz+wNSYPyQiBE59uXwp7FMEUUjVUH+l4oklDy3spFfCud3mFvIgmuL5vYobCn7NAcThyqtB6pvKgUZh5atIKIdnQXEjaCad8pGIAchSmfKVCiOEeVcis/KYCxVWY1smABZVnrZpW6nW8KnR61ZTt/6jayqSz/++BKp3lcNiKYqadr0XokjqzfkM7xzFbM4B9fmQ+gXJL8B2VsPt+0D5FG7XRY9RjlG8Ue9Rt1GLUbtRglGn0hHIfLB+sGLiDpIFkHe9+ZX7lfqW+YqGZIXida52LPXo9mh13HZfdFbDP5Vr7Vpuu8eJx6rHsseFx77E2UWh4fnHhcx1tgF0K6qbhZuNm4FFIxR5bAWoBSgGKgSiBgv3pMPkQ7tD08O4w/5DhEPiw6TD4EPXw87DtkOKwwoTiFLIlQcvJjVZeXOfkNYKhzzs/4UdA9DF45AtakNGb0ZyxWvnAgdAX2RfbF8Y3oJFYNkagZaatWf3I/cd9wf3bfc99xv3L/ZndYG1Y3uXxbZntl+bp329gbWtRH9oApJcrU14EM46pk8Tv3EgKt5f3TEETs7f1l8DuPmmC9wA/l6zvhjuNWZ5/jVQ0mlereytp62ZrWmt4q0UrY2vWdvE2y7bodtA2xrbHtsClvEuj1u2YG6fwm1EokhuY3wtJpAGvmZYBFvjWjjA19KYcI2kUMYMI/Qj9CB0pnQjZy4TVhBVmNmb2xu7abt+22O7cVtru3tcDyo3iD/uHAuGAz4zOjM/MKxqsnHCjSukC64zNfQ5/jntOeE4Wa39Ow4w8B9Z/pQQ58TnFORg51a890hk7hZNTPNmTyx5FxfeM3p+Z3KcVN6jT+5MVLO7NjFycmLAWorraI1S0IdtEC9DaI5jMFCSHYj2TJ2WhcomSloaK0gqfv5mzqpOVPL59HbW5HXjej8+kmfKAkVrZN/I1k1Pr7P6dAo4HDStjUpdKl0PLOxM/2YYhzzmvJd+kWyVPpNMl76QzJSekryWd8nndvd4p3lXeJBBhUNdYgVz4RCTtongzJDbzKUVeDpqiBDPstu64X3jFOT1t2Uj34YSycSr8upVg5Di1jvneFySFerBTqdMHkgJQw0ItZ0bypXXoUjST/wZ4riRqhsoOsBnyV/OyZWpWWhf20mVcPSrrM4ThrxODXfKRLYsI63jNamfqdnfk9LWHGOkA92vaHt7NFPSmTJ8sdPVk/TLqE/LCHHonuxccJ/0OqhABdP2BZDUllDX6OUrt9c6jhhLTVgLl3VnAnfGvvhrkt/9plXL7VySthEyEiFDtVOhW+ubnlvbW7xbuui9aIhkoGiU6LfaRlwkcizjRnPI9J1AGkgZyBKrESsSKxGrEugRbBG8Q/ZDvVOK173oqGiQ6LBohOS6+Nt0xHTfdM50x3SIrVubuo1iquvbOmSxVlRkD5lgI3cmdrnC+PWShD/93zorMXKYRvFGrQzXcu+L2+DG9ZInzIhPjqnFs3tgBLjTyDrI8P54bzXuRYjotAVtxgDohfZLRqLI6C615vEpuiaIhvZL2qMQ6Cw1LwZopqTRKiicie1BfieNj77OY1ss0rInDVElfdiQ/x9VutdNQSsiq/GHAgCTaPqjF1NVXqdjJ5aRzTUfL/akA+0GV9G46bRUlcGIxf+ft/71S+5+iAIijek0tUevIG49d5aEvvwdS0i79s4PsAkWMJhIv1YG07M8H8pXObo6Z0ayQ7dVrz2rSe70iZeKS57uniWdtdgIz9NGyVA9m+qpjZdExTOVCjuDVPnuy2Ql8JbJMBmdzG6uZiTQaWzor69sFTGqXciV5VjZHnz1NTc6ZyrZ5dV82LG+enYk1jNZFK0teNucWks+el507n49cm9ULzXPM08ydjfeT9fyT/FM81+4rBVnW88uJbfQClhRXyrzvsdAOR7fUVhgbbNuAIySH26OYvetDeO3ASUgvyWH54mc2X/EO9RrJtfbb4B0R1HnnKrg6kDCQLgiUz+edNee8/wAJqSytgvsoYFSUNWezeMWgZy0CfezQwYJ6MLBIVAtkveR78BQ1LtWOv3Ek8sV+anA2m4ueKPE5K0u0SleUSnUo2Sk89iRljsWr0PPlto4lo2WHS/Vq/qorlWrkasf7cmLsavRKl5L4RADe5t4DqNbtUNKgWbLgHJKu2KepL5Yo/ecEaeTgf7gkNNnJ3CwxxipDpLGD5GgkuXwEOJnbpp3RcEBgYA4DiJ1MWuWZ6vCqhfaTXvp4HFRnCr/1Pe22wFl7B9mTuwL134NPnnAqoWwtdQe2GMhmKNQ2+qlDWqRvM8o2iQmigcPrjtdHIsLHI7DHIzqT0mxw0Q8WCQuRMFIHamPKxxYNO0B4QbXHNc41wjXKNcZtPRtSyzcbVxtXeNfY1zjXNFpa2vi5RLpCMw64ZtoHtMgtEjKiypqk2Yn4Is9PNbZt2wmWYlKjBjlkLwLWZkogQh8c1oblkUGnpDJzOWQ7bQ+9s+hFXP9epZxRk9ch21JtsmfwWJR3bcwq/ddjxh2/jK6L6BnCIytRbJarl7vt+h709GJZyOJlPFCM64HryEpnQ3bTOUbtS1fjj9CrnTwU/+tMRXLju0leJjwuvCK6Ljwn6lEwYkzRH1IrZ9GE0Di293xjfV1WUsOZ03VwA2GGZ0ulVSfcHXZ3fsw8S6afKcdRi4IbhTp48dK65dqHfbZLVAtxbvrNk4nfy8X1p0FIICFOfLUvUHR3un/ETMRZneH60jjLkCqJlq6bFv1HgBZJc+MQUMExrTTytD9ymEC6RVTkPguyiqlKvLiYNYWA0Q8jEgb+M3aNFDBF0dz4RDpVmN/4MZY0jBA2hW02J+IkPJeH8kgp1Me6vUabWri1TLvNbjHZasSWcyLyitB7TclIT8dYTuW4WqiYbyk0V3jPnQCN/kO30eEwCSa0QZe2Cq82LdzMPcHEYNo0gkR4hNRtWffNYlEOfyZM+KZPe6uDtk1Aa/Mm/+xNvfYdV0ps0yVDkDpgw6hyb5I7aJH/QW7xaJfSMc+/w1FvVK7/aWBaM1dsfIS9cdv4b90rR9ry6h8DCgqOtJAXGRMiXO2+zLqrwj0ENs9hYAcS07sTTaOiBYo7T2U3pTEqrX10Jn+0xEZ1/4FSM6uX7On4I2yr3B3RRYwmJikGHO+WgKiG6qYghgbM54gxorPFjay5ZMbLC7VEhu9Wz4GWUzb6RpqOnLbNeuQeu0Wb5CubhZcHb7AXptBeN/2L/7ZBydrpXlDCoMO9l6Awf96CdZ7DIZjiqqOrovTq5V2Ao3v9ftzPU8JpWfHLPmC7asCd2UtJrVH4A87yLyo3IG+cWiJy4DS4rrAsNGNauHiN+tvGnLtJYlYQZ3UT3h22qwNi/hp0m7fCs7KZzEHyHYGkW4XneduHBVdJY6sbioQsISCJ0ItghRTeCnP1XaFi8iJnj/aQqImZatOPE8itYoR9L6a5rNtPY40nzmq3q+WQecLQmtx5ambMhe6C
*/