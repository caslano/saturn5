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
    template<class ConstBufferSequence, BOOST_BEAST_ASYNC_TPARAM2 WriteHandler>
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
    template<class MutableBufferSequence, BOOST_BEAST_ASYNC_TPARAM2 ReadHandler>
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
YLB79CwgdPm/3NnCthF10XveZk6SlIdOCFf2NtivZdN2RDclh1bh7ZvP5tsYdYivkqZRjx11MKR+NDyIUGmNk5saxzan7hsB0u3fbwGJLlQXGt8eIqjbFa954/PSocW+48Uc+4UTMEdmFNmy12rwiDzlB+6hF1IiwgsV4T2IKPZv+3WYne3cvTB/VcDPI5+3xqVDynlaTetHVtThX9RhDKBwE3GKJ3C8/WRS3EyyHdsshmuyDPuWE/BdDsxKiEEhAw1yysGahSmQz29hQK2RrudiNhqG4ctxiLdXFwLCgMAueaRpOxBx3A8nb37cU85Rfs/6LdpuTQ+GUcKeHA8o378XFcZErFHzm23rw6MOvCBNaLO7syuy7WtupcntGMGwgwzKi4T6/7uaZa3t+5THYeg5ylFJFHJdMSORCkh4zi2RGYp5c05cXAsLxWw+wjCW3gODUNyUY/ItPpPoo0loBLlaEm2pf/Nuqaprx1RuqVGHS0wJG4ac/RPV/v9CVfQSBdhmD91YcVd01QJOVxwJAIYA/7Yxz/A0Ps3F+jj5zWL8scfJyjEqwn3cqIxXepJxY+pqQ9JIx7nxIgZNx1nIrBPO4o4Gmg8Qr3VEfiDrlPqndi9X7VD/8N3SHP+IbcM4ghM1gFG5WTYpaIwjF4cwjWKvZS7hXLF9LuFYLa5KMEAFJm60dCRj66F0Ucr/ZeEBPPR5nq5Yy4g1QHk6QmEuzLPXziOCZ5gGNsQc2g9uErEmSjOpgHbsAWNZaMT8xHvjLrceH3unYoDd4f6Xn37O4sz3b+4x49hNbMKO5VLi55RbCvfv8FURDvOXim4LirGWWHW/HWNIjcgr5JFJDrJjSCM8rZWapBCMD7giWt1HhwSCY8USAugOjKTwHWKxUFJE0xWI6+HPM/eTgwl9mnO+Hh7UdbILgtH7vk0sbBZdx014CVPwSBkH/czaWeZEHbJ7fMphSvy9PRoXMMaxAsopAfPuPgak5v/6TTIF/cgIJHhm6qX1PffJtf+2f75f4DEU7WmEWxck1rncQrjgeVY5MCLsms+qbb0tzZqqIGPj2aijQ3CrE+X4OJf6QrbUGZBOjdlzbI32t0E6beqH0GhDeuR87hOJuZMNHqAGoWcMp+h/8vEsu6OCOoL06IndzVthizwAVMf+PAgzviu8nVR+ZBflENMeEQnwTNfBHcP73AZWv3S/dAFHBRZvWLdsuUxigB/Yh/h2Hp1JyOMJ9Tt3ehISQPV5nacZxUhECLnvF+BcjNpy3DNkHQ3QwNmv52/+t4LR+rjusL1g73mLLuz4cxHwhpQDGcX2SAnIvunoei+hEw8jGILIjJBdzSUifUV6kFY2I5ibx653ghC1j0zda4NH6r6xsb38/nnCv2Or3qelnBlpoR7MFBNSyGg040/03wpPjjc0GSf42E8Hd8Auh4e/NQ2g523KVjZEkG+/Srqwr+PCuGbErPvNLmH7yA8Y7nQSuaPJcRHywPRf/rY5sJP4mWezc0XltPKSyaaJ3T4kedashJFKQblR2sKUhblzgduGniQP4MHs2ObjDmZSZECZYRBL95LblaVeZvelI6fdrSDSjv4IO/od8Zm8LNme6l865V0OMKjAOWE5vhx/t9SnRoPJA694ctUjjObbNfrp+0h3UeoqOSRF+mkD8dcBQmw+8t2hvonJR1XB8aFm0dBV+oW2es7+jraUzJVsRqNh1MOLIZFNkaPQLxXqg1Wp4TtJjIVOfW/KB2OI8CAVyFGLqpRbsPlQpa9xh/kkdjS96+iUxoAHNDFIjGMDHGlpBYcR4CvHo9gZ91UObTRxnJy9QwUx3OT+RRmcR3VKMSmyxQkgSOsBnjG4dc5bt2nOk0WmOG253kA4i9am7kfJMW9wSfIcs08h2NCl35jFDgccjvD2sJRewfapwP4NEiGv93GMFNRKCgbZjXnHqGMFxNfdK9mBwjwcN57r1oP5F2SF+urZa0iin2tGCni8ecP23OgB5zeNFsxmOP7PW9kbkc6Jxfgbu2MDJZfK6uZzV5hgtkOYFTG++3hRFS0ygScipTnKvf5sEmIJ38AVCIPoyQFTglQ9nzcSxOmxzSVWFHUZvqnNx6xRoOW7y3VDnKqYVhoIDN1T2gSyHtZXnBQaFmUWuBDUrC/D0dCEglG3fjYY5IIWvVDfeW9IYAQhQv5PrtyJtbQo/LDfLnFLCxzf6zaNBcnDNYpkew3UNqvGNL84Bo8D3oEgSkmuq0RXvPIcU4hTwzGBcOWEUCyNYiUW4hj7/uoJLL2KF6AbX27aFpBfTVA2/j6aRZRIO7sqqmPtIMw+exAR6nBY8GDBkQG+4X6ZEe4FjIJvp9dxe+yoDBjvAgPShMNnmmGRF9HJrzB8MlTKK6dzxJ2ok3Hx/ZCcf61sfTSWLX1lCTo8udpsAv5tfLkOIyxE9dNooTvDtciWC4NaEwiiOOZExmOUMLToYPmwxWjAejgK0wcHVRw4f1bVJgSxE/Itb9TWiZrzzTBQc21vLEKaa/juytaX+wrdbg3o6K4ofuVoksHtod1t2yzXW5Pec21iXjLdAkCsqI9DFEsSdz5H3obkv41q3y/bYnQ5Yi3MbCqTaWfEnhfkLfFPyoGjS2Hg2vzNzZtyIDzJBy3g9a27SekrO2nwhgxabyv1vir06P0NDidCTThCqPFEGh3+kGcmwFSmxXFtR1gXOwnlE1BwbY/LYNqYfE67difuazxxflw2Ljzxqtq55UdNYOPfJbWAkxu41LbZ+R8Z2CGYaVIwZ8DxrXKY2A/B+aQl2nUpKoHrVUVUkGuU0qa6noFOnawJ7YdsCggfhh6WShmoLnBWPhK6Zt5q8oK7rzl3//b575jgAxVk3PVCRNkwEjY4VYpdFzo3kpWqFOTj5sGHnFSkEQacceAHRPCZZjufx+wLkvAnqRgRdWa3wfRehFuOJqTslMMDzK93NRsIgW5LlbpLGayWqmayhsRMOXNBt737kixI5r5bF7orFq4TFXBB6FMSpfZE2m9tg59fQkM7cVhhNC/RRNdtilkSUbCehAn2PLZKIEYj7PuX1OqEosAF+qoCSSnJzCkOjJr7V9nwWFdVi7fGOAJwb96/eUeqK3BGBfBusoMB6bzfSJ7DDgN/JkVkMBLwfjJnrjH36xIObv+WjjkDgY8joD8ALMbMzWvKUjfRZVvJeAA/Wr31KURmEP1vv4/wwH7wWuikAMu/dfUgXNDC9SMduehNjBcz/o+1ZfSe1yGfoAamQfvoOSdVkqRI0aAR184D3Op0ZrNn7O04eDEuyajYAaJUMf+1pK/71J6s+wY5fWBCfoP9VsKcjvZRfE+kg+jW8sR367xFkdenWl9vy4+rFjmnwFCOBc4MpmKb18NJnC4yOLxXjzvUWrchv4FSSqFU/L1MCh0NdJ57sbPgLp9UIp1EbGp7TFHERz3JzALO/vOMINbtpoMyrpNKO4Ywo/sL3BUURih+NrikieE+ToqoZajw+Sbs4gXs2ddnChb3Pn+xuzNcOwygiOv7XnMSHGmel01Hbl74IyO8FUHMA8Ba2GAGbEerVUH+o63IOLZ1uINe8V1gcFuv7l5WoU6UDC7apKrxFxGqlhI72PNl0XO8JP9eGNkUj7p+nD9ZHEbDUcPIJDEVxAjUWBwa3KXQom2iGxpru6kPclG54UJnCmyeI5jrreItDkxO+0r681Y4t+Ya/dQG+1WfOM8fw+zd8efCfQo453a8cMDlEzO7BXgwobU08aULMtjuohuMk/tW6SYAnXfD2AuDXejr//xbY2BirZ/RJdhfbkBDJx690H57QZdVA+koPqKeELbr5QUfAS7Jfah2QaxMSFIhuAOQhnmFF+wAG2cYMlyRBiIm7T1z8JluhnVsTwq67RD9wrCZTePRetv7ZMxQiyaaz4DeOvXvYrEmQL9MD2322SciNU87efwf9AItoXnWIjbJlQMPMej7P0ElbowglWmTvGcGGRxdCGQM8MupYbEVmyG/veHr38R7xps8GJC9iLQD0NwBqIA0C68FLMvdnKSO+tUL/WvG31tcd1CjGUK5mTddDOolaBb8rz9F8LaOaQjSeLzNrC6hPQZHE+9wwL4cW7IWNC4mPmlJojN6RFQaB2x6RAZDq+Xd0SPkI12F1jgyaorb7IZDAvFF9nw2X9eiwS2L2r2WMw04Opv+rexxXoq+Wsk11A3STekt8vCDBXFT3tZftAv8Ac7mrHCPBqGbcpeWUzULdXb82GwBPXrUPuQYMoyJabH+ZO1sWg+kL7Z0e5NgTE+F/6zGiIHFz6wIh2fe8RVZ9/Ugbfy/hRFJB5mT3U/t9+lpbQIuOxufayzv86tl4v3hlbvfDtorY4B3u5N1BtskFiY4tqGXuPBAIPRIXETLgbqDNZ/SAYN0H3P9P7ObgknuWEKTM95zLHCHPJ8FhIsS2duUpSu3FVinL4xyE74UY1ja0VBml3g+mJAJjgwuJ8UP4kpotVzj75iSo7GdVnDGvQq7lE8NpE/hrbqWegyp4eWraFOiNe9nJnKOu07KTrprLyPA/sQ3JivJVPeiLJNVlBH1/ELKra5DM46x6hiO1+Pifu/xSZkLjgl1oXmRFT3fr+zzdLyViVd97xJPa5obL0a6EM9zQQGqAHiweDoYLegDu4Ml/0u8XNdtdwkF6f/+uh4usu81ytxZFMcjYg1mYXCbpHfLbK//I6bU7jk2o1JH83CwmxkPRk6DEbA0x3gyB+2V4JQU+edURHcjKUUUDCjfOsAVaVNG51kYlzMHjJFj4FH+fkA9R870YBZK8DZ+7v50U/4Wm9eh7MKIs39YQ2x7okJ6jlXW6sGw/kCxd8b72tGnKigFVt7T0VJSTZBFaqK7QwVtEulHxTNF/hli7z40vsYITd20cDtQzslgEc6rShMw1cSsuInJU3EGeybHRIOHWoHx8mgVZ5gHLjCSYdYZQKf2TD3FxGJd490kHT3UZ7ctKIvU9kEDfHyUTFxtBSQ2IBToon3dEYG6jmpV8XsDS1Vmsf19GOsvCXD+n7Bqhyr7m4YJOovwudfXW0hgjeUs9ylsCt+BESc3J86HTH7u7VmHiJkY4AparvEBx/jSqgkMOWTzgSEEjYBoOCPSrtGjBwlfhiHhzms89Pu338SZLcuulULvfSa1sDUh4jzM8QCjvDaUEbmZT3oj8reQmBU9XUb3JPzI0O3s2yeqHCJQ+lu8oWwjw/TAjhg7JZ/j+/Vg4ecnnUJV1dT8ur6K4wE9mqC7zYjH/Y0v6ODNK2QC3+s+nGHkwJ1y1V56O+KAQ2g7SfdaGDK9dZ/DJ6Bh234E14JIqusKVFmUb9IXwE9Iqtor0MVEB9naauMa42SwOVuW6zncekN0pJmr2VoLd8OFq3XHd6TV1g5f/6ZLtHpdxXE5rVFz+jauXwC8t0TGmHfRV1mq7wWe5qq/JfoVYsVT1u2WGGGn/3yjFAfP1H6v71yN0aSisfiHy5Xvajs8wNCMG0XGQtYTVjWBvta367thXEvuOM3gyPb5T6HwjjI05YPI1jo6wkZkEWw/XjW1GWrQhtgESdTxDNsOffeyE38OvgSC1io0X6++MqNPkpkKYCbOnwXy46p1dKwLiQwXFDFm6BneXeutu4dvKbNtSRRpRlxTHMBvTS0IEGw7Xl4VZBRQdkh6dUdTyH+pcIv8We+6c7vpQbGz5vg+Mx8tBu+I3o/3kUe6J7cn8UvQ6dWIlE6BG1M8CKDXGetFpkGVvit2rBr5O9fmUbH6w0fmRfTUwZkE/tDwLUXdPl7D/JjzzNmmYR/642EXkfXJZQOM8YoA3vezYoKas9bz3QdVj3PsLDDkZh07T2XR4uLZ0n4E6Mg2fAPXrdshh3jrLEJWpqLhJElkPYmpd7y+BFl7n+OLSat5yGjeAO5r4i0C95Pvw1q6KN1Qk9PBTNN7bw5fVqDpANSnMdkeDM3fbpIRuJRghmx9hBPNIsf5ne3OmeiYCfta/aeoTLQn1/7m8vYpnYR/TdlQWW6yJl2e7/48d/FLtK5LhiUi/aA4KruyNIVna2WpOlBQpmFU1+JO5axtdy0tjPkecEqdEu5utMzDQMde+rk8viu96XNM11/VJBBc/KEHSwkjwUoUtiEbzQbtxFi5vXDBb2mpLoLoYzqeP8ngIbz1IwqiZl9ngDqbpIdjQHx494AECOLEv9z3fJZMUNz0N/JtgXG0/7JNSP3n6gXyDmK/+pr9NRrWE+0kTflH1q8Tqo0O57LuNqaDdNyV6iPZ4YldnXl3ho4wwBtxRSJtBfic2rxd8Dn+E/0GBNJAm1pK0fvLZwlpU5vd6Q+7D4aRCjrnZQAtEjx3RBo4aXx86hA7+4K4pDloLjdDDV1sWqPFgiPSweBn2hi5aWsyVu2B/+0rZfOaF9OAk1pMW5d6Nuj+cCAHUYfDjTH5IYCpJkzx35516svu5xZ2HS2aJp7AJ18df3HebJ/LabpBm8XB6HiCTWzG5PBSe4itkUqxGe/IwBi151tkNr3d6/TEN3njqTFEEou9NhT1XF4OQ891/6o44ZxDNDyO4qeMDxWMKRpqeSexOkX9qe+6lLzkbZc1hrGN2f4f8txGZSNdOlfFThEjnYvUWCxBYZIM+Ox4/UkaoUg7Fo3XJNMXP6gx84HwkgOcBARapD88Ib2QM1WT0B0nXe6QoHdzgPBds4hHU4wLaTo7IWZvBXSw+oJOsGAPU8EUfd/ap4RGzRzdsDUL7CmmuSTro8adl7YW1IpkkWlSH2iS44KFNEWkhhCEHroaMsFI5t5tATDECuZJXSXNOawEXKQteAAwqTzJKArPAlBkocwv3kdylPHqDKZrF0jXAc1PG+YEvZdGti3ZFf+8BC/xBXlxrh9uM1Hd4nvazVdJy4TXsFoLOZaXfUYxcYT+HbbwGfbFhrVTztG7WNDFQjsJrIxKTRv6F8ez9Bv7lGUYHxiPgMAUQc+/op5QLpYEUdTxMVPd45DyF6hWqvdLwB5voBwcxzjVOeMj7xPCPxhF0fFopBwVMb0EhphJAwtOgILhcZCg3CGJwkOlvyOmYXfWU24NMXbxE+4V8hEikL0sDSWN7QdiIGSrMfKW9okqPIMWyeTHTXXQZKKjZdN34JlWKHjLDdFoNfLQbLpF471zL8x956L53UapUHIwoNchYWkzWrSvzEC5bD6pMW/hn1p8s7zFH+oNfbzbao/ZGvzM7DACVzdV8tu2QIMDL51Du6LoNYwSKvnOYy46gNuaPLxa2tURn98/Qo0OMYBGGh7A2UVMQ4nwyuq4ABtIHd1mXKvZVkBuFwjXKn1i0CD5+5GFgIe3qA82SbKRcqeskBeM1YTSmqPhDRXvNJboLk1bI2uSuGl3HrfJ2oHNDJ2WRzQpuCSqFYuW15MWoVIyBK+tAFlrweR+X8HQeiu80cJzCY/CJUE7ps7Yl/clhM0iAU7aZ06XjhIdtv+YD+GrJlzZsDsN+yPs+UdcDyJB6nI2ltTv1SKaONXndJdLjsUdE1tD5VN+QnsUp3gkhRflhDgWP0Gs7yG1fhOD2xZuINFxgNhRTmmx9tdPnCPFRO1jjTOA88e5QFNLRReBNSWdGMMPmv5Y9zzW3QAEcTDiyWp8lCmw5VpcLU3CrYbfnQ69xgYHS1T2uR3wvOo0cMhB
*/