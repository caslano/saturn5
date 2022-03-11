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