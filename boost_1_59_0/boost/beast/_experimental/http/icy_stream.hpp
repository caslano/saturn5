//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_ICY_STREAM_HPP
#define BOOST_BEAST_HTTP_ICY_STREAM_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/logic/tribool.hpp>
#include <type_traits>

namespace boost {
namespace beast {
namespace http {

/** Stream wrapper to process Shoutcast HTTP responses

    This wrapper replaces the word "ICY" in the first
    HTTP response received on the connection, with "HTTP/1.1".
    This allows the Beast parser to be used with Shoutcast
    servers, which send a non-standard HTTP message as the
    response.

    For asynchronous operations, the application must ensure
    that they are are all performed within the same implicit
    or explicit strand.

    @par Thread Safety
    @e Distinct @e objects: Safe.@n
    @e Shared @e objects: Unsafe.
    The application must also ensure that all asynchronous
    operations are performed within the same implicit or explicit strand.

    @par Example
    To use the @ref icy_stream template with an @ref tcp_stream
    you would write:
    @code
    http::icy_stream<tcp_stream> is(ioc);
    @endcode

    @tparam NextLayer The type representing the next layer, to which
    data will be read and written during operations. For synchronous
    operations, the type must support the <em>SyncStream</em> concept.
    For asynchronous operations, the type must support the
    <em>AsyncStream</em> concept.

    @note A stream object must not be moved or destroyed while there
    are pending asynchronous operations associated with it.

    @par Concepts
    <em>AsyncStream</em>, <em>SyncStream</em>
*/
template<class NextLayer>
class icy_stream
{
    NextLayer stream_;
    char buf_[8];
    unsigned char n_ = 0;
    bool detect_ = true;

    struct ops;

    static
    net::const_buffer
    version()
    {
        return {"HTTP/1.1", 8};
    }

public:
    /// The type of the next layer.
    using next_layer_type =
        typename std::remove_reference<NextLayer>::type;

    /// The type of the executor associated with the object.
    using executor_type = typename next_layer_type::executor_type;

    icy_stream(icy_stream&&) = default;
    icy_stream(icy_stream const&) = default;
    icy_stream& operator=(icy_stream&&) = default;
    icy_stream& operator=(icy_stream const&) = default;

    /** Destructor

        The treatment of pending operations will be the same as that
        of the next layer.
    */
    ~icy_stream() = default;

    /** Constructor

        Arguments, if any, are forwarded to the next layer's constructor.
    */
    template<class... Args>
    explicit
    icy_stream(Args&&... args);

    //--------------------------------------------------------------------------

    /** Get the executor associated with the object.
    
        This function may be used to obtain the executor object that the
        stream uses to dispatch handlers for asynchronous operations.

        @return A copy of the executor that stream will use to dispatch handlers.
    */
    executor_type
    get_executor() noexcept
    {
        return stream_.get_executor();
    }

    /** Get a reference to the next layer

        This function returns a reference to the next layer
        in a stack of stream layers.

        @return A reference to the next layer in the stack of
        stream layers.
    */
    next_layer_type&
    next_layer()
    {
        return stream_;
    }

    /** Get a reference to the next layer

        This function returns a reference to the next layer in a
        stack of stream layers.

        @return A reference to the next layer in the stack of
        stream layers.
    */
    next_layer_type const&
    next_layer() const
    {
        return stream_;
    }

    //--------------------------------------------------------------------------

    /** Read some data from the stream.

        This function is used to read data from the stream. The function call will
        block until one or more bytes of data has been read successfully, or until
        an error occurs.
        
        @param buffers The buffers into which the data will be read.
        
        @returns The number of bytes read.
        
        @throws system_error Thrown on failure.
        
        @note The `read_some` operation may not read all of the requested number of
        bytes. Consider using the function `net::read` if you need to ensure
        that the requested amount of data is read before the blocking operation
        completes.
    */
    template<class MutableBufferSequence>
    std::size_t
    read_some(MutableBufferSequence const& buffers);

    /** Read some data from the stream.

        This function is used to read data from the stream. The function call will
        block until one or more bytes of data has been read successfully, or until
        an error occurs.
        
        @param buffers The buffers into which the data will be read.
        
        @param ec Set to indicate what error occurred, if any.

        @returns The number of bytes read.
                
        @note The `read_some` operation may not read all of the requested number of
        bytes. Consider using the function `net::read` if you need to ensure
        that the requested amount of data is read before the blocking operation
        completes.
    */
    template<class MutableBufferSequence>
    std::size_t
    read_some(
        MutableBufferSequence const& buffers,
        error_code& ec);

    /** Start an asynchronous read.
    
        This function is used to asynchronously read one or more bytes of data from
        the stream. The function call always returns immediately.
        
        @param buffers The buffers into which the data will be read. Although the
        buffers object may be copied as necessary, ownership of the underlying
        buffers is retained by the caller, which must guarantee that they remain
        valid until the handler is called.

        @param handler The completion handler to invoke when the operation
        completes. The implementation takes ownership of the handler by
        performing a decay-copy. The equivalent function signature of
        the handler must be:
        @code
        void handler(
          const boost::system::error_code& error, // Result of operation.
          std::size_t bytes_transferred           // Number of bytes read.
        );
        @endcode
        Regardless of whether the asynchronous operation completes
        immediately or not, the handler will not be invoked from within
        this function. Invocation of the handler will be performed in a
        manner equivalent to using `net::post`.

        @note The `async_read_some` operation may not read all of the requested number of
        bytes. Consider using the function `net::async_read` if you need
        to ensure that the requested amount of data is read before the asynchronous
        operation completes.
    */
    template<
        class MutableBufferSequence,
        BOOST_BEAST_ASYNC_TPARAM2 ReadHandler =
            net::default_completion_token_t<executor_type>
    >
    BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
    async_read_some(
        MutableBufferSequence const& buffers,
        ReadHandler&& handler =
            net::default_completion_token_t<executor_type>{});

    /** Write some data to the stream.
    
        This function is used to write data on the stream. The function call will
        block until one or more bytes of data has been written successfully, or
        until an error occurs.
        
        @param buffers The data to be written.
        
        @returns The number of bytes written.
        
        @throws system_error Thrown on failure.
        
        @note The `write_some` operation may not transmit all of the data to the
        peer. Consider using the function `net::write` if you need to
        ensure that all data is written before the blocking operation completes.
    */
    template<class ConstBufferSequence>
    std::size_t
    write_some(ConstBufferSequence const& buffers);

    /** Write some data to the stream.
    
        This function is used to write data on the stream. The function call will
        block until one or more bytes of data has been written successfully, or
        until an error occurs.
        
        @param buffers The data to be written.
        
        @param ec Set to indicate what error occurred, if any.

        @returns The number of bytes written.
                
        @note The `write_some` operation may not transmit all of the data to the
        peer. Consider using the function `net::write` if you need to
        ensure that all data is written before the blocking operation completes.
    */
    template<class ConstBufferSequence>
    std::size_t
    write_some(
        ConstBufferSequence const& buffers,
        error_code& ec);

    /** Start an asynchronous write.
        
        This function is used to asynchronously write one or more bytes of data to
        the stream. The function call always returns immediately.
        
        @param buffers The data to be written to the stream. Although the buffers
        object may be copied as necessary, ownership of the underlying buffers is
        retained by the caller, which must guarantee that they remain valid until
        the handler is called.
        
        @param handler The completion handler to invoke when the operation
        completes. The implementation takes ownership of the handler by
        performing a decay-copy. The equivalent function signature of
        the handler must be:
        @code
        void handler(
          error_code const& error,          // Result of operation.
          std::size_t bytes_transferred     // Number of bytes written.
        );
        @endcode
        Regardless of whether the asynchronous operation completes
        immediately or not, the handler will not be invoked from within
        this function. Invocation of the handler will be performed in a
        manner equivalent to using `net::post`.
        
        @note The `async_write_some` operation may not transmit all of the data to
        the peer. Consider using the function `net::async_write` if you need
        to ensure that all data is written before the asynchronous operation completes.
    */
    template<
        class ConstBufferSequence,
        BOOST_BEAST_ASYNC_TPARAM2 WriteHandler =
            net::default_completion_token_t<executor_type>
    >
    BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
    async_write_some(
        ConstBufferSequence const& buffers,
        WriteHandler&& handler =
            net::default_completion_token_t<executor_type>{});
};

} // http
} // beast
} // boost

#include <boost/beast/_experimental/http/impl/icy_stream.hpp>

#endif

/* icy_stream.hpp
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
*/