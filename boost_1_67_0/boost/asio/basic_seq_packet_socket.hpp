//
// basic_seq_packet_socket.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_SEQ_PACKET_SOCKET_HPP
#define BOOST_ASIO_BASIC_SEQ_PACKET_SOCKET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <boost/asio/basic_socket.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if !defined(BOOST_ASIO_BASIC_SEQ_PACKET_SOCKET_FWD_DECL)
#define BOOST_ASIO_BASIC_SEQ_PACKET_SOCKET_FWD_DECL

// Forward declaration with defaulted arguments.
template <typename Protocol, typename Executor = executor>
class basic_seq_packet_socket;

#endif // !defined(BOOST_ASIO_BASIC_SEQ_PACKET_SOCKET_FWD_DECL)

/// Provides sequenced packet socket functionality.
/**
 * The basic_seq_packet_socket class template provides asynchronous and blocking
 * sequenced packet socket functionality.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename Protocol, typename Executor>
class basic_seq_packet_socket
  : public basic_socket<Protocol, Executor>
{
public:
  /// The type of the executor associated with the object.
  typedef Executor executor_type;

  /// Rebinds the socket type to another executor.
  template <typename Executor1>
  struct rebind_executor
  {
    /// The socket type when rebound to the specified executor.
    typedef basic_seq_packet_socket<Protocol, Executor1> other;
  };

  /// The native representation of a socket.
#if defined(GENERATING_DOCUMENTATION)
  typedef implementation_defined native_handle_type;
#else
  typedef typename basic_socket<Protocol,
    Executor>::native_handle_type native_handle_type;
#endif

  /// The protocol type.
  typedef Protocol protocol_type;

  /// The endpoint type.
  typedef typename Protocol::endpoint endpoint_type;

  /// Construct a basic_seq_packet_socket without opening it.
  /**
   * This constructor creates a sequenced packet socket without opening it. The
   * socket needs to be opened and then connected or accepted before data can
   * be sent or received on it.
   *
   * @param ex The I/O executor that the socket will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the socket.
   */
  explicit basic_seq_packet_socket(const executor_type& ex)
    : basic_socket<Protocol, Executor>(ex)
  {
  }

  /// Construct a basic_seq_packet_socket without opening it.
  /**
   * This constructor creates a sequenced packet socket without opening it. The
   * socket needs to be opened and then connected or accepted before data can
   * be sent or received on it.
   *
   * @param context An execution context which provides the I/O executor that
   * the socket will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the socket.
   */
  template <typename ExecutionContext>
  explicit basic_seq_packet_socket(ExecutionContext& context,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : basic_socket<Protocol, Executor>(context)
  {
  }

  /// Construct and open a basic_seq_packet_socket.
  /**
   * This constructor creates and opens a sequenced_packet socket. The socket
   * needs to be connected or accepted before data can be sent or received on
   * it.
   *
   * @param ex The I/O executor that the socket will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the socket.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_seq_packet_socket(const executor_type& ex,
      const protocol_type& protocol)
    : basic_socket<Protocol, Executor>(ex, protocol)
  {
  }

  /// Construct and open a basic_seq_packet_socket.
  /**
   * This constructor creates and opens a sequenced_packet socket. The socket
   * needs to be connected or accepted before data can be sent or received on
   * it.
   *
   * @param context An execution context which provides the I/O executor that
   * the socket will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the socket.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_seq_packet_socket(ExecutionContext& context,
      const protocol_type& protocol,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : basic_socket<Protocol, Executor>(context, protocol)
  {
  }

  /// Construct a basic_seq_packet_socket, opening it and binding it to the
  /// given local endpoint.
  /**
   * This constructor creates a sequenced packet socket and automatically opens
   * it bound to the specified endpoint on the local machine. The protocol used
   * is the protocol associated with the given endpoint.
   *
   * @param ex The I/O executor that the socket will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the socket.
   *
   * @param endpoint An endpoint on the local machine to which the sequenced
   * packet socket will be bound.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_seq_packet_socket(const executor_type& ex,
      const endpoint_type& endpoint)
    : basic_socket<Protocol, Executor>(ex, endpoint)
  {
  }

  /// Construct a basic_seq_packet_socket, opening it and binding it to the
  /// given local endpoint.
  /**
   * This constructor creates a sequenced packet socket and automatically opens
   * it bound to the specified endpoint on the local machine. The protocol used
   * is the protocol associated with the given endpoint.
   *
   * @param context An execution context which provides the I/O executor that
   * the socket will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the socket.
   *
   * @param endpoint An endpoint on the local machine to which the sequenced
   * packet socket will be bound.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_seq_packet_socket(ExecutionContext& context,
      const endpoint_type& endpoint,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : basic_socket<Protocol, Executor>(context, endpoint)
  {
  }

  /// Construct a basic_seq_packet_socket on an existing native socket.
  /**
   * This constructor creates a sequenced packet socket object to hold an
   * existing native socket.
   *
   * @param ex The I/O executor that the socket will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the socket.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @param native_socket The new underlying socket implementation.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  basic_seq_packet_socket(const executor_type& ex,
      const protocol_type& protocol, const native_handle_type& native_socket)
    : basic_socket<Protocol, Executor>(ex, protocol, native_socket)
  {
  }

  /// Construct a basic_seq_packet_socket on an existing native socket.
  /**
   * This constructor creates a sequenced packet socket object to hold an
   * existing native socket.
   *
   * @param context An execution context which provides the I/O executor that
   * the socket will use, by default, to dispatch handlers for any asynchronous
   * operations performed on the socket.
   *
   * @param protocol An object specifying protocol parameters to be used.
   *
   * @param native_socket The new underlying socket implementation.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  template <typename ExecutionContext>
  basic_seq_packet_socket(ExecutionContext& context,
      const protocol_type& protocol, const native_handle_type& native_socket,
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : basic_socket<Protocol, Executor>(context, protocol, native_socket)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a basic_seq_packet_socket from another.
  /**
   * This constructor moves a sequenced packet socket from one object to
   * another.
   *
   * @param other The other basic_seq_packet_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_seq_packet_socket(const executor_type&)
   * constructor.
   */
  basic_seq_packet_socket(basic_seq_packet_socket&& other) BOOST_ASIO_NOEXCEPT
    : basic_socket<Protocol, Executor>(std::move(other))
  {
  }

  /// Move-assign a basic_seq_packet_socket from another.
  /**
   * This assignment operator moves a sequenced packet socket from one object to
   * another.
   *
   * @param other The other basic_seq_packet_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_seq_packet_socket(const executor_type&)
   * constructor.
   */
  basic_seq_packet_socket& operator=(basic_seq_packet_socket&& other)
  {
    basic_socket<Protocol, Executor>::operator=(std::move(other));
    return *this;
  }

  /// Move-construct a basic_seq_packet_socket from a socket of another protocol
  /// type.
  /**
   * This constructor moves a sequenced packet socket from one object to
   * another.
   *
   * @param other The other basic_seq_packet_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_seq_packet_socket(const executor_type&)
   * constructor.
   */
  template <typename Protocol1, typename Executor1>
  basic_seq_packet_socket(basic_seq_packet_socket<Protocol1, Executor1>&& other,
      typename enable_if<
        is_convertible<Protocol1, Protocol>::value
          && is_convertible<Executor1, Executor>::value
      >::type* = 0)
    : basic_socket<Protocol, Executor>(std::move(other))
  {
  }

  /// Move-assign a basic_seq_packet_socket from a socket of another protocol
  /// type.
  /**
   * This assignment operator moves a sequenced packet socket from one object to
   * another.
   *
   * @param other The other basic_seq_packet_socket object from which the move
   * will occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_seq_packet_socket(const executor_type&)
   * constructor.
   */
  template <typename Protocol1, typename Executor1>
  typename enable_if<
    is_convertible<Protocol1, Protocol>::value
      && is_convertible<Executor1, Executor>::value,
    basic_seq_packet_socket&
  >::type operator=(basic_seq_packet_socket<Protocol1, Executor1>&& other)
  {
    basic_socket<Protocol, Executor>::operator=(std::move(other));
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destroys the socket.
  /**
   * This function destroys the socket, cancelling any outstanding asynchronous
   * operations associated with the socket as if by calling @c cancel.
   */
  ~basic_seq_packet_socket()
  {
  }

  /// Send some data on the socket.
  /**
   * This function is used to send data on the sequenced packet socket. The
   * function call will block until the data has been sent successfully, or an
   * until error occurs.
   *
   * @param buffers One or more data buffers to be sent on the socket.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @returns The number of bytes sent.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @par Example
   * To send a single data buffer use the @ref buffer function as follows:
   * @code
   * socket.send(boost::asio::buffer(data, size), 0);
   * @endcode
   * See the @ref buffer documentation for information on sending multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename ConstBufferSequence>
  std::size_t send(const ConstBufferSequence& buffers,
      socket_base::message_flags flags)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().send(
        this->impl_.get_implementation(), buffers, flags, ec);
    boost::asio::detail::throw_error(ec, "send");
    return s;
  }

  /// Send some data on the socket.
  /**
   * This function is used to send data on the sequenced packet socket. The
   * function call will block the data has been sent successfully, or an until
   * error occurs.
   *
   * @param buffers One or more data buffers to be sent on the socket.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes sent. Returns 0 if an error occurred.
   *
   * @note The send operation may not transmit all of the data to the peer.
   * Consider using the @ref write function if you need to ensure that all data
   * is written before the blocking operation completes.
   */
  template <typename ConstBufferSequence>
  std::size_t send(const ConstBufferSequence& buffers,
      socket_base::message_flags flags, boost::system::error_code& ec)
  {
    return this->impl_.get_service().send(
        this->impl_.get_implementation(), buffers, flags, ec);
  }

  /// Start an asynchronous send.
  /**
   * This function is used to asynchronously send data on the sequenced packet
   * socket. The function call always returns immediately.
   *
   * @param buffers One or more data buffers to be sent on the socket. Although
   * the buffers object may be copied as necessary, ownership of the underlying
   * memory blocks is retained by the caller, which must guarantee that they
   * remain valid until the handler is called.
   *
   * @param flags Flags specifying how the send call is to be made.
   *
   * @param handler The handler to be called when the send operation completes.
   * Copies will be made of the handler as required. The function signature of
   * the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes sent.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Example
   * To send a single data buffer use the @ref buffer function as follows:
   * @code
   * socket.async_send(boost::asio::buffer(data, size), 0, handler);
   * @endcode
   * See the @ref buffer documentation for information on sending multiple
   * buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename ConstBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) WriteHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(WriteHandler,
      void (boost::system::error_code, std::size_t))
  async_send(const ConstBufferSequence& buffers,
      socket_base::message_flags flags,
      BOOST_ASIO_MOVE_ARG(WriteHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<WriteHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_send(this), handler, buffers, flags);
  }

  /// Receive some data on the socket.
  /**
   * This function is used to receive data on the sequenced packet socket. The
   * function call will block until data has been received successfully, or
   * until an error occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param out_flags After the receive call completes, contains flags
   * associated with the received data. For example, if the
   * socket_base::message_end_of_record bit is set then the received data marks
   * the end of a record.
   *
   * @returns The number of bytes received.
   *
   * @throws boost::system::system_error Thrown on failure. An error code of
   * boost::asio::error::eof indicates that the connection was closed by the
   * peer.
   *
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code
   * socket.receive(boost::asio::buffer(data, size), out_flags);
   * @endcode
   * See the @ref buffer documentation for information on receiving into
   * multiple buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence>
  std::size_t receive(const MutableBufferSequence& buffers,
      socket_base::message_flags& out_flags)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().receive_with_flags(
        this->impl_.get_implementation(), buffers, 0, out_flags, ec);
    boost::asio::detail::throw_error(ec, "receive");
    return s;
  }

  /// Receive some data on the socket.
  /**
   * This function is used to receive data on the sequenced packet socket. The
   * function call will block until data has been received successfully, or
   * until an error occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param in_flags Flags specifying how the receive call is to be made.
   *
   * @param out_flags After the receive call completes, contains flags
   * associated with the received data. For example, if the
   * socket_base::message_end_of_record bit is set then the received data marks
   * the end of a record.
   *
   * @returns The number of bytes received.
   *
   * @throws boost::system::system_error Thrown on failure. An error code of
   * boost::asio::error::eof indicates that the connection was closed by the
   * peer.
   *
   * @note The receive operation may not receive all of the requested number of
   * bytes. Consider using the @ref read function if you need to ensure that the
   * requested amount of data is read before the blocking operation completes.
   *
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code
   * socket.receive(boost::asio::buffer(data, size), 0, out_flags);
   * @endcode
   * See the @ref buffer documentation for information on receiving into
   * multiple buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence>
  std::size_t receive(const MutableBufferSequence& buffers,
      socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags)
  {
    boost::system::error_code ec;
    std::size_t s = this->impl_.get_service().receive_with_flags(
        this->impl_.get_implementation(), buffers, in_flags, out_flags, ec);
    boost::asio::detail::throw_error(ec, "receive");
    return s;
  }

  /// Receive some data on a connected socket.
  /**
   * This function is used to receive data on the sequenced packet socket. The
   * function call will block until data has been received successfully, or
   * until an error occurs.
   *
   * @param buffers One or more buffers into which the data will be received.
   *
   * @param in_flags Flags specifying how the receive call is to be made.
   *
   * @param out_flags After the receive call completes, contains flags
   * associated with the received data. For example, if the
   * socket_base::message_end_of_record bit is set then the received data marks
   * the end of a record.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns The number of bytes received. Returns 0 if an error occurred.
   *
   * @note The receive operation may not receive all of the requested number of
   * bytes. Consider using the @ref read function if you need to ensure that the
   * requested amount of data is read before the blocking operation completes.
   */
  template <typename MutableBufferSequence>
  std::size_t receive(const MutableBufferSequence& buffers,
      socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags, boost::system::error_code& ec)
  {
    return this->impl_.get_service().receive_with_flags(
        this->impl_.get_implementation(), buffers, in_flags, out_flags, ec);
  }

  /// Start an asynchronous receive.
  /**
   * This function is used to asynchronously receive data from the sequenced
   * packet socket. The function call always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param out_flags Once the asynchronous operation completes, contains flags
   * associated with the received data. For example, if the
   * socket_base::message_end_of_record bit is set then the received data marks
   * the end of a record. The caller must guarantee that the referenced
   * variable remains valid until the handler is called.
   *
   * @param handler The handler to be called when the receive operation
   * completes. Copies will be made of the handler as required. The function
   * signature of the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes received.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code
   * socket.async_receive(boost::asio::buffer(data, size), out_flags, handler);
   * @endcode
   * See the @ref buffer documentation for information on receiving into
   * multiple buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) ReadHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
      void (boost::system::error_code, std::size_t))
  async_receive(const MutableBufferSequence& buffers,
      socket_base::message_flags& out_flags,
      BOOST_ASIO_MOVE_ARG(ReadHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_receive_with_flags(this), handler,
        buffers, socket_base::message_flags(0), &out_flags);
  }

  /// Start an asynchronous receive.
  /**
   * This function is used to asynchronously receive data from the sequenced
   * data socket. The function call always returns immediately.
   *
   * @param buffers One or more buffers into which the data will be received.
   * Although the buffers object may be copied as necessary, ownership of the
   * underlying memory blocks is retained by the caller, which must guarantee
   * that they remain valid until the handler is called.
   *
   * @param in_flags Flags specifying how the receive call is to be made.
   *
   * @param out_flags Once the asynchronous operation completes, contains flags
   * associated with the received data. For example, if the
   * socket_base::message_end_of_record bit is set then the received data marks
   * the end of a record. The caller must guarantee that the referenced
   * variable remains valid until the handler is called.
   *
   * @param handler The handler to be called when the receive operation
   * completes. Copies will be made of the handler as required. The function
   * signature of the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   std::size_t bytes_transferred           // Number of bytes received.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * @par Example
   * To receive into a single data buffer use the @ref buffer function as
   * follows:
   * @code
   * socket.async_receive(
   *     boost::asio::buffer(data, size),
   *     0, out_flags, handler);
   * @endcode
   * See the @ref buffer documentation for information on receiving into
   * multiple buffers in one go, and how to use it with arrays, boost::array or
   * std::vector.
   */
  template <typename MutableBufferSequence,
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        std::size_t)) ReadHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ReadHandler,
      void (boost::system::error_code, std::size_t))
  async_receive(const MutableBufferSequence& buffers,
      socket_base::message_flags in_flags,
      socket_base::message_flags& out_flags,
      BOOST_ASIO_MOVE_ARG(ReadHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_initiate<ReadHandler,
      void (boost::system::error_code, std::size_t)>(
        initiate_async_receive_with_flags(this),
        handler, buffers, in_flags, &out_flags);
  }

private:
  class initiate_async_send
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_send(basic_seq_packet_socket* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename WriteHandler, typename ConstBufferSequence>
    void operator()(BOOST_ASIO_MOVE_ARG(WriteHandler) handler,
        const ConstBufferSequence& buffers,
        socket_base::message_flags flags) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a WriteHandler.
      BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

      detail::non_const_lvalue<WriteHandler> handler2(handler);
      self_->impl_.get_service().async_send(
          self_->impl_.get_implementation(), buffers, flags,
          handler2.value, self_->impl_.get_implementation_executor());
    }

  private:
    basic_seq_packet_socket* self_;
  };

  class initiate_async_receive_with_flags
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_receive_with_flags(basic_seq_packet_socket* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename ReadHandler, typename MutableBufferSequence>
    void operator()(BOOST_ASIO_MOVE_ARG(ReadHandler) handler,
        const MutableBufferSequence& buffers,
        socket_base::message_flags in_flags,
        socket_base::message_flags* out_flags) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ReadHandler.
      BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

      detail::non_const_lvalue<ReadHandler> handler2(handler);
      self_->impl_.get_service().async_receive_with_flags(
          self_->impl_.get_implementation(), buffers, in_flags, *out_flags,
          handler2.value, self_->impl_.get_implementation_executor());
    }

  private:
    basic_seq_packet_socket* self_;
  };
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BASIC_SEQ_PACKET_SOCKET_HPP

/* basic_seq_packet_socket.hpp
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
*/