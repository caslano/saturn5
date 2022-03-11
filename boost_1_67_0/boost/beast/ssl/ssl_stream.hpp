//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_SSL_STREAM_HPP
#define BOOST_BEAST_CORE_SSL_STREAM_HPP

#include <boost/beast/core/detail/config.hpp>

// This include is necessary to work with `ssl::stream` and `boost::beast::websocket::stream`
#include <boost/beast/websocket/ssl.hpp>

#include <boost/beast/core/flat_stream.hpp>

// VFALCO We include this because anyone who uses ssl will
//        very likely need to check for ssl::error::stream_truncated
#include <boost/asio/ssl/error.hpp>

#include <boost/asio/ssl/stream.hpp>
#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {

/** Provides stream-oriented functionality using OpenSSL

    The stream class template provides asynchronous and blocking
    stream-oriented functionality using SSL.

    @par Thread Safety
    @e Distinct @e objects: Safe.@n
    @e Shared @e objects: Unsafe. The application must also ensure that all
    asynchronous operations are performed within the same implicit or explicit
    strand.

    @par Example
    To use this template with a @ref tcp_stream, you would write:
    @code
        net::io_context ioc;
        net::ssl::context ctx{net::ssl::context::tlsv12};
        beast::ssl_stream<beast::tcp_stream> sock{ioc, ctx};
    @endcode

    In addition to providing an interface identical to `net::ssl::stream`,
    the wrapper has the following additional properties:

    @li Satisfies @b MoveConstructible

    @li Satisfies @b MoveAssignable

    @li Constructible from a moved socket.

    @li Uses @ref flat_stream internally, as a performance work-around for a
        limitation of `net::ssl::stream` when writing buffer sequences
        having length greater than one.

    @par Concepts:
        @li AsyncReadStream
        @li AsyncWriteStream
        @li Stream
        @li SyncReadStream
        @li SyncWriteStream
*/
template<class NextLayer>
class ssl_stream
    : public net::ssl::stream_base
{
    using ssl_stream_type = net::ssl::stream<NextLayer>;
    using stream_type = boost::beast::flat_stream<ssl_stream_type>;

    std::unique_ptr<stream_type> p_;

public:
    /// The native handle type of the SSL stream.
    using native_handle_type =
        typename ssl_stream_type::native_handle_type;

    /// Structure for use with deprecated impl_type.
    using impl_struct = typename ssl_stream_type::impl_struct;

    /// The type of the next layer.
    using next_layer_type = typename ssl_stream_type::next_layer_type;

    /// The type of the executor associated with the object.
    using executor_type = typename stream_type::executor_type;

    /** Construct a stream.

        This constructor creates a stream and initialises the underlying stream
        object.

        @param arg The argument to be passed to initialise the underlying stream.

        @param ctx The SSL context to be used for the stream.
    */
    template<class Arg>
    ssl_stream(
        Arg&& arg,
        net::ssl::context& ctx)
        : p_(new stream_type{
            std::forward<Arg>(arg), ctx})
    {
    }

    /** Get the executor associated with the object.

        This function may be used to obtain the executor object that the stream
        uses to dispatch handlers for asynchronous operations.

        @return A copy of the executor that stream will use to dispatch handlers.
    */
    executor_type
    get_executor() noexcept
    {
        return p_->get_executor();
    }

    /** Get the underlying implementation in the native type.

        This function may be used to obtain the underlying implementation of the
        context. This is intended to allow access to context functionality that is
        not otherwise provided.

        @par Example
        The native_handle() function returns a pointer of type @c SSL* that is
        suitable for passing to functions such as @c SSL_get_verify_result and
        @c SSL_get_peer_certificate:
        @code
        boost::beast::ssl_stream<net::ip::tcp::socket> ss{ioc, ctx};

        // ... establish connection and perform handshake ...

        if (X509* cert = SSL_get_peer_certificate(ss.native_handle()))
        {
          if (SSL_get_verify_result(ss.native_handle()) == X509_V_OK)
          {
            // ...
          }
        }
        @endcode
    */
    native_handle_type
    native_handle() noexcept
    {
        return p_->next_layer().native_handle();
    }

    /** Get a reference to the next layer.

        This function returns a reference to the next layer in a stack of stream
        layers.

        @note The next layer is the wrapped stream and not the @ref flat_stream
        used in the implementation.

        @return A reference to the next layer in the stack of stream layers.
        Ownership is not transferred to the caller.
    */
    next_layer_type const&
    next_layer() const noexcept
    {
        return p_->next_layer().next_layer();
    }

    /** Get a reference to the next layer.

        This function returns a reference to the next layer in a stack of stream
        layers.

        @note The next layer is the wrapped stream and not the @ref flat_stream
        used in the implementation.

        @return A reference to the next layer in the stack of stream layers.
        Ownership is not transferred to the caller.
    */
    next_layer_type&
    next_layer() noexcept
    {
        return p_->next_layer().next_layer();
    }

    /** Set the peer verification mode.

        This function may be used to configure the peer verification mode used by
        the stream. The new mode will override the mode inherited from the context.

        @param v A bitmask of peer verification modes.

        @throws boost::system::system_error Thrown on failure.

        @note Calls @c SSL_set_verify.
    */
    void
    set_verify_mode(net::ssl::verify_mode v)
    {
        p_->next_layer().set_verify_mode(v);
    }

    /** Set the peer verification mode.

        This function may be used to configure the peer verification mode used by
        the stream. The new mode will override the mode inherited from the context.

        @param v A bitmask of peer verification modes. See `verify_mode` for
        available values.

        @param ec Set to indicate what error occurred, if any.

        @note Calls @c SSL_set_verify.
    */
    void
    set_verify_mode(net::ssl::verify_mode v,
        boost::system::error_code& ec)
    {
        p_->next_layer().set_verify_mode(v, ec);
    }

    /** Set the peer verification depth.

        This function may be used to configure the maximum verification depth
        allowed by the stream.

        @param depth Maximum depth for the certificate chain verification that
        shall be allowed.

        @throws boost::system::system_error Thrown on failure.

        @note Calls @c SSL_set_verify_depth.
    */
    void
    set_verify_depth(int depth)
    {
        p_->next_layer().set_verify_depth(depth);
    }

    /** Set the peer verification depth.

        This function may be used to configure the maximum verification depth
        allowed by the stream.

        @param depth Maximum depth for the certificate chain verification that
        shall be allowed.

        @param ec Set to indicate what error occurred, if any.

        @note Calls @c SSL_set_verify_depth.
    */
    void
    set_verify_depth(
        int depth, boost::system::error_code& ec)
    {
        p_->next_layer().set_verify_depth(depth, ec);
    }

    /** Set the callback used to verify peer certificates.

        This function is used to specify a callback function that will be called
        by the implementation when it needs to verify a peer certificate.

        @param callback The function object to be used for verifying a certificate.
        The function signature of the handler must be:
        @code bool verify_callback(
          bool preverified, // True if the certificate passed pre-verification.
          verify_context& ctx // The peer certificate and other context.
        ); @endcode
        The return value of the callback is true if the certificate has passed
        verification, false otherwise.

        @throws boost::system::system_error Thrown on failure.

        @note Calls @c SSL_set_verify.
    */
    template<class VerifyCallback>
    void
    set_verify_callback(VerifyCallback callback)
    {
        p_->next_layer().set_verify_callback(callback);
    }

    /** Set the callback used to verify peer certificates.

        This function is used to specify a callback function that will be called
        by the implementation when it needs to verify a peer certificate.

        @param callback The function object to be used for verifying a certificate.
        The function signature of the handler must be:
        @code bool verify_callback(
          bool preverified, // True if the certificate passed pre-verification.
          net::verify_context& ctx // The peer certificate and other context.
        ); @endcode
        The return value of the callback is true if the certificate has passed
        verification, false otherwise.

        @param ec Set to indicate what error occurred, if any.

        @note Calls @c SSL_set_verify.
    */
    template<class VerifyCallback>
    void
    set_verify_callback(VerifyCallback callback,
        boost::system::error_code& ec)
    {
        p_->next_layer().set_verify_callback(callback, ec);
    }

    /** Perform SSL handshaking.

        This function is used to perform SSL handshaking on the stream. The
        function call will block until handshaking is complete or an error occurs.

        @param type The type of handshaking to be performed, i.e. as a client or as
        a server.

        @throws boost::system::system_error Thrown on failure.
    */
    void
    handshake(handshake_type type)
    {
        p_->next_layer().handshake(type);
    }

    /** Perform SSL handshaking.

        This function is used to perform SSL handshaking on the stream. The
        function call will block until handshaking is complete or an error occurs.

        @param type The type of handshaking to be performed, i.e. as a client or as
        a server.

        @param ec Set to indicate what error occurred, if any.
    */
    void
    handshake(handshake_type type,
        boost::system::error_code& ec)
    {
        p_->next_layer().handshake(type, ec);
    }

    /** Perform SSL handshaking.

        This function is used to perform SSL handshaking on the stream. The
        function call will block until handshaking is complete or an error occurs.

        @param type The type of handshaking to be performed, i.e. as a client or as
        a server.

        @param buffers The buffered data to be reused for the handshake.

        @throws boost::system::system_error Thrown on failure.
    */
    template<class ConstBufferSequence>
    void
    handshake(
        handshake_type type, ConstBufferSequence const& buffers)
    {
        p_->next_layer().handshake(type, buffers);
    }

    /** Perform SSL handshaking.

        This function is used to perform SSL handshaking on the stream. The
        function call will block until handshaking is complete or an error occurs.

        @param type The type of handshaking to be performed, i.e. as a client or as
        a server.

        @param buffers The buffered data to be reused for the handshake.

        @param ec Set to indicate what error occurred, if any.
    */
    template<class ConstBufferSequence>
    void
    handshake(handshake_type type,
        ConstBufferSequence const& buffers,
            boost::system::error_code& ec)
    {
        p_->next_layer().handshake(type, buffers, ec);
    }

    /** Start an asynchronous SSL handshake.

        This function is used to asynchronously perform an SSL handshake on the
        stream. This function call always returns immediately.

        @param type The type of handshaking to be performed, i.e. as a client or as
        a server.

        @param handler The handler to be called when the handshake operation
        completes. Copies will be made of the handler as required. The equivalent
        function signature of the handler must be:
        @code void handler(
          const boost::system::error_code& error // Result of operation.
        ); @endcode
    */
    template<class HandshakeHandler>
    BOOST_ASIO_INITFN_RESULT_TYPE(HandshakeHandler, void(boost::system::error_code))
    async_handshake(handshake_type type,
        BOOST_ASIO_MOVE_ARG(HandshakeHandler) handler)
    {
        return p_->next_layer().async_handshake(type,
            BOOST_ASIO_MOVE_CAST(HandshakeHandler)(handler));
    }

    /** Start an asynchronous SSL handshake.

        This function is used to asynchronously perform an SSL handshake on the
        stream. This function call always returns immediately.

        @param type The type of handshaking to be performed, i.e. as a client or as
        a server.

        @param buffers The buffered data to be reused for the handshake. Although
        the buffers object may be copied as necessary, ownership of the underlying
        buffers is retained by the caller, which must guarantee that they remain
        valid until the handler is called.

        @param handler The handler to be called when the handshake operation
        completes. Copies will be made of the handler as required. The equivalent
        function signature of the handler must be:
        @code void handler(
          const boost::system::error_code& error, // Result of operation.
          std::size_t bytes_transferred // Amount of buffers used in handshake.
        ); @endcode
    */
    template<class ConstBufferSequence, class BufferedHandshakeHandler>
    BOOST_ASIO_INITFN_RESULT_TYPE(BufferedHandshakeHandler, void(boost::system::error_code, std::size_t))
    async_handshake(handshake_type type, ConstBufferSequence const& buffers,
        BOOST_ASIO_MOVE_ARG(BufferedHandshakeHandler) handler)
    {
        return p_->next_layer().async_handshake(type, buffers,
            BOOST_ASIO_MOVE_CAST(BufferedHandshakeHandler)(handler));
    }

    /** Shut down SSL on the stream.

        This function is used to shut down SSL on the stream. The function call
        will block until SSL has been shut down or an error occurs.

        @throws boost::system::system_error Thrown on failure.
    */
    void
    shutdown()
    {
        p_->next_layer().shutdown();
    }

    /** Shut down SSL on the stream.

        This function is used to shut down SSL on the stream. The function call
        will block until SSL has been shut down or an error occurs.

        @param ec Set to indicate what error occurred, if any.
    */
    void
    shutdown(boost::system::error_code& ec)
    {
        p_->next_layer().shutdown(ec);
    }

    /** Asynchronously shut down SSL on the stream.

        This function is used to asynchronously shut down SSL on the stream. This
        function call always returns immediately.

        @param handler The handler to be called when the handshake operation
        completes. Copies will be made of the handler as required. The equivalent
        function signature of the handler must be:
        @code void handler(
          const boost::system::error_code& error // Result of operation.
        ); @endcode
    */
    template<class ShutdownHandler>
    BOOST_ASIO_INITFN_RESULT_TYPE(ShutdownHandler, void(boost::system::error_code))
    async_shutdown(BOOST_ASIO_MOVE_ARG(ShutdownHandler) handler)
    {
        return p_->next_layer().async_shutdown(
            BOOST_ASIO_MOVE_CAST(ShutdownHandler)(handler));
    }

    /** Write some data to the stream.

        This function is used to write data on the stream. The function call will
        block until one or more bytes of data has been written successfully, or
        until an error occurs.

        @param buffers The data to be written.

        @returns The number of bytes written.

        @throws boost::system::system_error Thrown on failure.

        @note The `write_some` operation may not transmit all of the data to the
        peer. Consider using the `net::write` function if you need to
        ensure that all data is written before the blocking operation completes.
    */
    template<class ConstBufferSequence>
    std::size_t
    write_some(ConstBufferSequence const& buffers)
    {
        return p_->write_some(buffers);
    }

    /** Write some data to the stream.

        This function is used to write data on the stream. The function call will
        block until one or more bytes of data has been written successfully, or
        until an error occurs.

        @param buffers The data to be written to the stream.

        @param ec Set to indicate what error occurred, if any.

        @returns The number of bytes written. Returns 0 if an error occurred.

        @note The `write_some` operation may not transmit all of the data to the
        peer. Consider using the `net::write` function if you need to
        ensure that all data is written before the blocking operation completes.
    */
    template<class ConstBufferSequence>
    std::size_t
    write_some(ConstBufferSequence const& buffers,
        boost::system::error_code& ec)
    {
        return p_->write_some(buffers, ec);
    }

    /** Start an asynchronous write.

        This function is used to asynchronously write one or more bytes of data to
        the stream. The function call always returns immediately.

        @param buffers The data to be written to the stream. Although the buffers
        object may be copied as necessary, ownership of the underlying buffers is
        retained by the caller, which must guarantee that they remain valid until
        the handler is called.

        @param handler The handler to be called when the write operation completes.
        Copies will be made of the handler as required. The equivalent function
        signature of the handler must be:
        @code void handler(
          const boost::system::error_code& error, // Result of operation.
          std::size_t bytes_transferred           // Number of bytes written.
        ); @endcode

        @note The `async_write_some` operation may not transmit all of the data to
        the peer. Consider using the `net::async_write` function if you
        need to ensure that all data is written before the asynchronous operation
        completes.
    */
    template<class ConstBufferSequence, class WriteHandler>
    BOOST_ASIO_INITFN_RESULT_TYPE(WriteHandler, void(boost::system::error_code, std::size_t))
    async_write_some(ConstBufferSequence const& buffers,
        BOOST_ASIO_MOVE_ARG(WriteHandler) handler)
    {
        return p_->async_write_some(buffers,
            BOOST_ASIO_MOVE_CAST(WriteHandler)(handler));
    }

    /** Read some data from the stream.

        This function is used to read data from the stream. The function call will
        block until one or more bytes of data has been read successfully, or until
        an error occurs.

        @param buffers The buffers into which the data will be read.

        @returns The number of bytes read.

        @throws boost::system::system_error Thrown on failure.

        @note The `read_some` operation may not read all of the requested number of
        bytes. Consider using the `net::read` function if you need to ensure
        that the requested amount of data is read before the blocking operation
        completes.
    */
    template<class MutableBufferSequence>
    std::size_t
    read_some(MutableBufferSequence const& buffers)
    {
        return p_->read_some(buffers);
    }

    /** Read some data from the stream.

        This function is used to read data from the stream. The function call will
        block until one or more bytes of data has been read successfully, or until
        an error occurs.

        @param buffers The buffers into which the data will be read.

        @param ec Set to indicate what error occurred, if any.

        @returns The number of bytes read. Returns 0 if an error occurred.

        @note The `read_some` operation may not read all of the requested number of
        bytes. Consider using the `net::read` function if you need to ensure
        that the requested amount of data is read before the blocking operation
        completes.
    */
    template<class MutableBufferSequence>
    std::size_t
    read_some(MutableBufferSequence const& buffers,
        boost::system::error_code& ec)
    {
        return p_->read_some(buffers, ec);
    }

    /** Start an asynchronous read.

        This function is used to asynchronously read one or more bytes of data from
        the stream. The function call always returns immediately.

        @param buffers The buffers into which the data will be read. Although the
        buffers object may be copied as necessary, ownership of the underlying
        buffers is retained by the caller, which must guarantee that they remain
        valid until the handler is called.

        @param handler The handler to be called when the read operation completes.
        Copies will be made of the handler as required. The equivalent function
        signature of the handler must be:
        @code void handler(
          const boost::system::error_code& error, // Result of operation.
          std::size_t bytes_transferred           // Number of bytes read.
        ); @endcode

        @note The `async_read_some` operation may not read all of the requested
        number of bytes. Consider using the `net::async_read` function
        if you need to ensure that the requested amount of data is read before
        the asynchronous operation completes.
    */
    template<class MutableBufferSequence, class ReadHandler>
    BOOST_ASIO_INITFN_RESULT_TYPE(ReadHandler, void(boost::system::error_code, std::size_t))
    async_read_some(MutableBufferSequence const& buffers,
        BOOST_ASIO_MOVE_ARG(ReadHandler) handler)
    {
        return p_->async_read_some(buffers,
            BOOST_ASIO_MOVE_CAST(ReadHandler)(handler));
    }

    // These hooks are used to inform boost::beast::websocket::stream on
    // how to tear down the connection as part of the WebSocket
    // protocol specifications
    #if ! BOOST_BEAST_DOXYGEN
    template<class SyncStream>
    friend
    void
    teardown(
        boost::beast::role_type role,
        ssl_stream<SyncStream>& stream,
        boost::system::error_code& ec);

    template<class AsyncStream, class TeardownHandler>
    friend
    void
    async_teardown(
        boost::beast::role_type role,
        ssl_stream<AsyncStream>& stream,
        TeardownHandler&& handler);
    #endif
};

#if ! BOOST_BEAST_DOXYGEN
template<class SyncStream>
void
teardown(
    boost::beast::role_type role,
    ssl_stream<SyncStream>& stream,
    boost::system::error_code& ec)
{
    // Just forward it to the underlying ssl::stream
    using boost::beast::websocket::teardown;
    teardown(role, *stream.p_, ec);
}

template<class AsyncStream, class TeardownHandler>
void
async_teardown(
    boost::beast::role_type role,
    ssl_stream<AsyncStream>& stream,
    TeardownHandler&& handler)
{
    // Just forward it to the underlying ssl::stream
    using boost::beast::websocket::async_teardown;
    async_teardown(role, *stream.p_,
        std::forward<TeardownHandler>(handler));
}
#endif

} // beast
} // boost

#endif

/* ssl_stream.hpp
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
*/