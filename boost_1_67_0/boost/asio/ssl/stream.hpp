//
// ssl/stream.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_STREAM_HPP
#define BOOST_ASIO_SSL_STREAM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/asio/ssl/detail/buffered_handshake_op.hpp>
#include <boost/asio/ssl/detail/handshake_op.hpp>
#include <boost/asio/ssl/detail/io.hpp>
#include <boost/asio/ssl/detail/read_op.hpp>
#include <boost/asio/ssl/detail/shutdown_op.hpp>
#include <boost/asio/ssl/detail/stream_core.hpp>
#include <boost/asio/ssl/detail/write_op.hpp>
#include <boost/asio/ssl/stream_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {

/// Provides stream-oriented functionality using SSL.
/**
 * The stream class template provides asynchronous and blocking stream-oriented
 * functionality using SSL.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe. The application must also ensure that all
 * asynchronous operations are performed within the same implicit or explicit
 * strand.
 *
 * @par Example
 * To use the SSL stream template with an ip::tcp::socket, you would write:
 * @code
 * boost::asio::io_context my_context;
 * boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
 * boost::asio::ssl::stream<asio:ip::tcp::socket> sock(my_context, ctx);
 * @endcode
 *
 * @par Concepts:
 * AsyncReadStream, AsyncWriteStream, Stream, SyncReadStream, SyncWriteStream.
 */
template <typename Stream>
class stream :
  public stream_base,
  private noncopyable
{
public:
  /// The native handle type of the SSL stream.
  typedef SSL* native_handle_type;

  /// Structure for use with deprecated impl_type.
  struct impl_struct
  {
    SSL* ssl;
  };

  /// The type of the next layer.
  typedef typename remove_reference<Stream>::type next_layer_type;

  /// The type of the lowest layer.
  typedef typename next_layer_type::lowest_layer_type lowest_layer_type;

  /// The type of the executor associated with the object.
  typedef typename lowest_layer_type::executor_type executor_type;

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Construct a stream.
  /**
   * This constructor creates a stream and initialises the underlying stream
   * object.
   *
   * @param arg The argument to be passed to initialise the underlying stream.
   *
   * @param ctx The SSL context to be used for the stream.
   */
  template <typename Arg>
  stream(Arg&& arg, context& ctx)
    : next_layer_(BOOST_ASIO_MOVE_CAST(Arg)(arg)),
      core_(ctx.native_handle(), next_layer_.lowest_layer().get_executor())
  {
  }
#else // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  template <typename Arg>
  stream(Arg& arg, context& ctx)
    : next_layer_(arg),
      core_(ctx.native_handle(), next_layer_.lowest_layer().get_executor())
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destructor.
  /**
   * @note A @c stream object must not be destroyed while there are pending
   * asynchronous operations associated with it.
   */
  ~stream()
  {
  }

  /// Get the executor associated with the object.
  /**
   * This function may be used to obtain the executor object that the stream
   * uses to dispatch handlers for asynchronous operations.
   *
   * @return A copy of the executor that stream will use to dispatch handlers.
   */
  executor_type get_executor() BOOST_ASIO_NOEXCEPT
  {
    return next_layer_.lowest_layer().get_executor();
  }

  /// Get the underlying implementation in the native type.
  /**
   * This function may be used to obtain the underlying implementation of the
   * context. This is intended to allow access to context functionality that is
   * not otherwise provided.
   *
   * @par Example
   * The native_handle() function returns a pointer of type @c SSL* that is
   * suitable for passing to functions such as @c SSL_get_verify_result and
   * @c SSL_get_peer_certificate:
   * @code
   * boost::asio::ssl::stream<asio:ip::tcp::socket> sock(my_context, ctx);
   *
   * // ... establish connection and perform handshake ...
   *
   * if (X509* cert = SSL_get_peer_certificate(sock.native_handle()))
   * {
   *   if (SSL_get_verify_result(sock.native_handle()) == X509_V_OK)
   *   {
   *     // ...
   *   }
   * }
   * @endcode
   */
  native_handle_type native_handle()
  {
    return core_.engine_.native_handle();
  }

  /// Get a reference to the next layer.
  /**
   * This function returns a reference to the next layer in a stack of stream
   * layers.
   *
   * @return A reference to the next layer in the stack of stream layers.
   * Ownership is not transferred to the caller.
   */
  const next_layer_type& next_layer() const
  {
    return next_layer_;
  }

  /// Get a reference to the next layer.
  /**
   * This function returns a reference to the next layer in a stack of stream
   * layers.
   *
   * @return A reference to the next layer in the stack of stream layers.
   * Ownership is not transferred to the caller.
   */
  next_layer_type& next_layer()
  {
    return next_layer_;
  }

  /// Get a reference to the lowest layer.
  /**
   * This function returns a reference to the lowest layer in a stack of
   * stream layers.
   *
   * @return A reference to the lowest layer in the stack of stream layers.
   * Ownership is not transferred to the caller.
   */
  lowest_layer_type& lowest_layer()
  {
    return next_layer_.lowest_layer();
  }

  /// Get a reference to the lowest layer.
  /**
   * This function returns a reference to the lowest layer in a stack of
   * stream layers.
   *
   * @return A reference to the lowest layer in the stack of stream layers.
   * Ownership is not transferred to the caller.
   */
  const lowest_layer_type& lowest_layer() const
  {
    return next_layer_.lowest_layer();
  }

  /// Set the peer verification mode.
  /**
   * This function may be used to configure the peer verification mode used by
   * the stream. The new mode will override the mode inherited from the context.
   *
   * @param v A bitmask of peer verification modes. See @ref verify_mode for
   * available values.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_set_verify.
   */
  void set_verify_mode(verify_mode v)
  {
    boost::system::error_code ec;
    set_verify_mode(v, ec);
    boost::asio::detail::throw_error(ec, "set_verify_mode");
  }

  /// Set the peer verification mode.
  /**
   * This function may be used to configure the peer verification mode used by
   * the stream. The new mode will override the mode inherited from the context.
   *
   * @param v A bitmask of peer verification modes. See @ref verify_mode for
   * available values.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_set_verify.
   */
  BOOST_ASIO_SYNC_OP_VOID set_verify_mode(
      verify_mode v, boost::system::error_code& ec)
  {
    core_.engine_.set_verify_mode(v, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Set the peer verification depth.
  /**
   * This function may be used to configure the maximum verification depth
   * allowed by the stream.
   *
   * @param depth Maximum depth for the certificate chain verification that
   * shall be allowed.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_set_verify_depth.
   */
  void set_verify_depth(int depth)
  {
    boost::system::error_code ec;
    set_verify_depth(depth, ec);
    boost::asio::detail::throw_error(ec, "set_verify_depth");
  }

  /// Set the peer verification depth.
  /**
   * This function may be used to configure the maximum verification depth
   * allowed by the stream.
   *
   * @param depth Maximum depth for the certificate chain verification that
   * shall be allowed.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_set_verify_depth.
   */
  BOOST_ASIO_SYNC_OP_VOID set_verify_depth(
      int depth, boost::system::error_code& ec)
  {
    core_.engine_.set_verify_depth(depth, ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Set the callback used to verify peer certificates.
  /**
   * This function is used to specify a callback function that will be called
   * by the implementation when it needs to verify a peer certificate.
   *
   * @param callback The function object to be used for verifying a certificate.
   * The function signature of the handler must be:
   * @code bool verify_callback(
   *   bool preverified, // True if the certificate passed pre-verification.
   *   verify_context& ctx // The peer certificate and other context.
   * ); @endcode
   * The return value of the callback is true if the certificate has passed
   * verification, false otherwise.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note Calls @c SSL_set_verify.
   */
  template <typename VerifyCallback>
  void set_verify_callback(VerifyCallback callback)
  {
    boost::system::error_code ec;
    this->set_verify_callback(callback, ec);
    boost::asio::detail::throw_error(ec, "set_verify_callback");
  }

  /// Set the callback used to verify peer certificates.
  /**
   * This function is used to specify a callback function that will be called
   * by the implementation when it needs to verify a peer certificate.
   *
   * @param callback The function object to be used for verifying a certificate.
   * The function signature of the handler must be:
   * @code bool verify_callback(
   *   bool preverified, // True if the certificate passed pre-verification.
   *   verify_context& ctx // The peer certificate and other context.
   * ); @endcode
   * The return value of the callback is true if the certificate has passed
   * verification, false otherwise.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @note Calls @c SSL_set_verify.
   */
  template <typename VerifyCallback>
  BOOST_ASIO_SYNC_OP_VOID set_verify_callback(VerifyCallback callback,
      boost::system::error_code& ec)
  {
    core_.engine_.set_verify_callback(
        new detail::verify_callback<VerifyCallback>(callback), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Perform SSL handshaking.
  /**
   * This function is used to perform SSL handshaking on the stream. The
   * function call will block until handshaking is complete or an error occurs.
   *
   * @param type The type of handshaking to be performed, i.e. as a client or as
   * a server.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void handshake(handshake_type type)
  {
    boost::system::error_code ec;
    handshake(type, ec);
    boost::asio::detail::throw_error(ec, "handshake");
  }

  /// Perform SSL handshaking.
  /**
   * This function is used to perform SSL handshaking on the stream. The
   * function call will block until handshaking is complete or an error occurs.
   *
   * @param type The type of handshaking to be performed, i.e. as a client or as
   * a server.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID handshake(handshake_type type,
      boost::system::error_code& ec)
  {
    detail::io(next_layer_, core_, detail::handshake_op(type), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Perform SSL handshaking.
  /**
   * This function is used to perform SSL handshaking on the stream. The
   * function call will block until handshaking is complete or an error occurs.
   *
   * @param type The type of handshaking to be performed, i.e. as a client or as
   * a server.
   *
   * @param buffers The buffered data to be reused for the handshake.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ConstBufferSequence>
  void handshake(handshake_type type, const ConstBufferSequence& buffers)
  {
    boost::system::error_code ec;
    handshake(type, buffers, ec);
    boost::asio::detail::throw_error(ec, "handshake");
  }

  /// Perform SSL handshaking.
  /**
   * This function is used to perform SSL handshaking on the stream. The
   * function call will block until handshaking is complete or an error occurs.
   *
   * @param type The type of handshaking to be performed, i.e. as a client or as
   * a server.
   *
   * @param buffers The buffered data to be reused for the handshake.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  template <typename ConstBufferSequence>
  BOOST_ASIO_SYNC_OP_VOID handshake(handshake_type type,
      const ConstBufferSequence& buffers, boost::system::error_code& ec)
  {
    detail::io(next_layer_, core_,
        detail::buffered_handshake_op<ConstBufferSequence>(type, buffers), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Start an asynchronous SSL handshake.
  /**
   * This function is used to asynchronously perform an SSL handshake on the
   * stream. This function call always returns immediately.
   *
   * @param type The type of handshaking to be performed, i.e. as a client or as
   * a server.
   *
   * @param handler The handler to be called when the handshake operation
   * completes. Copies will be made of the handler as required. The equivalent
   * function signature of the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error // Result of operation.
   * ); @endcode
   */
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code))
        HandshakeHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(HandshakeHandler,
      void (boost::system::error_code))
  async_handshake(handshake_type type,
      BOOST_ASIO_MOVE_ARG(HandshakeHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<HandshakeHandler,
      void (boost::system::error_code)>(
        initiate_async_handshake(this), handler, type);
  }

  /// Start an asynchronous SSL handshake.
  /**
   * This function is used to asynchronously perform an SSL handshake on the
   * stream. This function call always returns immediately.
   *
   * @param type The type of handshaking to be performed, i.e. as a client or as
   * a server.
   *
   * @param buffers The buffered data to be reused for the handshake. Although
   * the buffers object may be copied as necessary, ownership of the underlying
   * buffers is retained by the caller, which must guarantee that they remain
   * valid until the handler is called.
   *
   * @param handler The handler to be called when the handshake operation
   * completes. Copies will be made of the handler as required. The equivalent
   * function signature of the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred // Amount of buffers used in handshake.
   * ); @endcode
   */
  template <typename ConstBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) BufferedHandshakeHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(BufferedHandshakeHandler,
      void (boost::system::error_code, std::size_t))
  async_handshake(handshake_type type, const ConstBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(BufferedHandshakeHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<BufferedHandshakeHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_buffered_handshake(this), handler, type, buffers);
  }

  /// Shut down SSL on the stream.
  /**
   * This function is used to shut down SSL on the stream. The function call
   * will block until SSL has been shut down or an error occurs.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  void shutdown()
  {
    boost::system::error_code ec;
    shutdown(ec);
    boost::asio::detail::throw_error(ec, "shutdown");
  }

  /// Shut down SSL on the stream.
  /**
   * This function is used to shut down SSL on the stream. The function call
   * will block until SSL has been shut down or an error occurs.
   *
   * @param ec Set to indicate what error occurred, if any.
   */
  BOOST_ASIO_SYNC_OP_VOID shutdown(boost::system::error_code& ec)
  {
    detail::io(next_layer_, core_, detail::shutdown_op(), ec);
    BOOST_ASIO_SYNC_OP_VOID_RETURN(ec);
  }

  /// Asynchronously shut down SSL on the stream.
  /**
   * This function is used to asynchronously shut down SSL on the stream. This
   * function call always returns immediately.
   *
   * @param handler The handler to be called when the handshake operation
   * completes. Copies will be made of the handler as required. The equivalent
   * function signature of the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error // Result of operation.
   * ); @endcode
   */
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code))
        ShutdownHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ShutdownHandler,
      void (boost::system::error_code))
  async_shutdown(
      BOOST_ASIO_MOVE_ARG(ShutdownHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ShutdownHandler,
      void (boost::system::error_code)>(
        initiate_async_shutdown(this), handler);
  }

  /// Write some data to the stream.
  /**
   * This function is used to write data on the stream. The function call will
   * block until one or more bytes of data has been written successfully, or
   * until an error occurs.
   *
   * @param buffers The data to be written.
   *
   * @returns The number of bytes written.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note The write_some operation may not transmit all of the data to the
   * peer. Consider using the @ref write function if you need to ensure that all
   * data is written before the blocking operation completes.
   */
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t n = write_some(buffers, ec);
    boost::asio::detail::throw_error(ec, "write_some");
    return n;
  }

  /// Write some data to the stream.
  /**
   * This function is used to write data on the stream. The function call will
   * block until one or more bytes of data has been written successfully, or
   * until an error occurs.
   *
   * @param buffers The data to be written to the stream.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes written. Returns 0 if an error occurred.
   *
   * @note The write_some operation may not transmit all of the data to the
   * peer. Consider using the @ref write function if you need to ensure that all
   * data is written before the blocking operation completes.
   */
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers,
      boost::system::error_code& ec)
  {
    return detail::io(next_layer_, core_,
        detail::write_op<ConstBufferSequence>(buffers), ec);
  }

  /// Start an asynchronous write.
  /**
   * This function is used to asynchronously write one or more bytes of data to
   * the stream. The function call always returns immediately.
   *
   * @param buffers The data to be written to the stream. Although the buffers
   * object may be copied as necessary, ownership of the underlying buffers is
   * retained by the caller, which must guarantee that they remain valid until
   * the handler is called.
   *
   * @param handler The handler to be called when the write operation completes.
   * Copies will be made of the handler as required. The equivalent function
   * signature of the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes written.
   * ); @endcode
   *
   * @note The async_write_some operation may not transmit all of the data to
   * the peer. Consider using the @ref async_write function if you need to
   * ensure that all data is written before the asynchronous operation
   * completes.
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

  /// Read some data from the stream.
  /**
   * This function is used to read data from the stream. The function call will
   * block until one or more bytes of data has been read successfully, or until
   * an error occurs.
   *
   * @param buffers The buffers into which the data will be read.
   *
   * @returns The number of bytes read.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note The read_some operation may not read all of the requested number of
   * bytes. Consider using the @ref read function if you need to ensure that the
   * requested amount of data is read before the blocking operation completes.
   */
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t n = read_some(buffers, ec);
    boost::asio::detail::throw_error(ec, "read_some");
    return n;
  }

  /// Read some data from the stream.
  /**
   * This function is used to read data from the stream. The function call will
   * block until one or more bytes of data has been read successfully, or until
   * an error occurs.
   *
   * @param buffers The buffers into which the data will be read.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes read. Returns 0 if an error occurred.
   *
   * @note The read_some operation may not read all of the requested number of
   * bytes. Consider using the @ref read function if you need to ensure that the
   * requested amount of data is read before the blocking operation completes.
   */
  template <typename MutableBufferSequence>
  std::size_t read_some(const MutableBufferSequence& buffers,
      boost::system::error_code& ec)
  {
    return detail::io(next_layer_, core_,
        detail::read_op<MutableBufferSequence>(buffers), ec);
  }

  /// Start an asynchronous read.
  /**
   * This function is used to asynchronously read one or more bytes of data from
   * the stream. The function call always returns immediately.
   *
   * @param buffers The buffers into which the data will be read. Although the
   * buffers object may be copied as necessary, ownership of the underlying
   * buffers is retained by the caller, which must guarantee that they remain
   * valid until the handler is called.
   *
   * @param handler The handler to be called when the read operation completes.
   * Copies will be made of the handler as required. The equivalent function
   * signature of the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes read.
   * ); @endcode
   *
   * @note The async_read_some operation may not read all of the requested
   * number of bytes. Consider using the @ref async_read function if you need to
   * ensure that the requested amount of data is read before the asynchronous
   * operation completes.
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
  class initiate_async_handshake
  {
  public:
    typedef typename stream::executor_type executor_type;

    explicit initiate_async_handshake(stream* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename HandshakeHandler>
    void operator()(BOOST_ASIO_MOVE_ARG(HandshakeHandler) handler,
        handshake_type type) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a HandshakeHandler.
      BOOST_ASIO_HANDSHAKE_HANDLER_CHECK(HandshakeHandler, handler) type_check;

      boost::asio::detail::non_const_lvalue<HandshakeHandler> handler2(handler);
      detail::async_io(self_->next_layer_, self_->core_,
          detail::handshake_op(type), handler2.value);
    }

  private:
    stream* self_;
  };

  class initiate_async_buffered_handshake
  {
  public:
    typedef typename stream::executor_type executor_type;

    explicit initiate_async_buffered_handshake(stream* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename BufferedHandshakeHandler, typename ConstBufferSequence>
    void operator()(BOOST_ASIO_MOVE_ARG(BufferedHandshakeHandler) handler,
        handshake_type type, const ConstBufferSequence& buffers) const
    {
      // If you get an error on the following line it means that your
      // handler does not meet the documented type requirements for a
      // BufferedHandshakeHandler.
      BOOST_ASIO_BUFFERED_HANDSHAKE_HANDLER_CHECK(
          BufferedHandshakeHandler, handler) type_check;

      boost::asio::detail::non_const_lvalue<
          BufferedHandshakeHandler> handler2(handler);
      detail::async_io(self_->next_layer_, self_->core_,
          detail::buffered_handshake_op<ConstBufferSequence>(type, buffers),
          handler2.value);
    }

  private:
    stream* self_;
  };

  class initiate_async_shutdown
  {
  public:
    typedef typename stream::executor_type executor_type;

    explicit initiate_async_shutdown(stream* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename ShutdownHandler>
    void operator()(BOOST_ASIO_MOVE_ARG(ShutdownHandler) handler) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ShutdownHandler.
      BOOST_ASIO_HANDSHAKE_HANDLER_CHECK(ShutdownHandler, handler) type_check;

      boost::asio::detail::non_const_lvalue<ShutdownHandler> handler2(handler);
      detail::async_io(self_->next_layer_, self_->core_,
          detail::shutdown_op(), handler2.value);
    }

  private:
    stream* self_;
  };

  class initiate_async_write_some
  {
  public:
    typedef typename stream::executor_type executor_type;

    explicit initiate_async_write_some(stream* self)
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

      boost::asio::detail::non_const_lvalue<WriteHandler> handler2(handler);
      detail::async_io(self_->next_layer_, self_->core_,
          detail::write_op<ConstBufferSequence>(buffers), handler2.value);
    }

  private:
    stream* self_;
  };

  class initiate_async_read_some
  {
  public:
    typedef typename stream::executor_type executor_type;

    explicit initiate_async_read_some(stream* self)
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

      boost::asio::detail::non_const_lvalue<ReadHandler> handler2(handler);
      detail::async_io(self_->next_layer_, self_->core_,
          detail::read_op<MutableBufferSequence>(buffers), handler2.value);
    }

  private:
    stream* self_;
  };

  Stream next_layer_;
  detail::stream_core core_;
};

} // namespace ssl
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_STREAM_HPP

/* stream.hpp
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
*/