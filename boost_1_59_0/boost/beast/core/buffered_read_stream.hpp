//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_BUFFERED_READ_STREAM_HPP
#define BOOST_BEAST_BUFFERED_READ_STREAM_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/multi_buffer.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/io_context.hpp>
#include <cstdint>
#include <utility>

namespace boost {
namespace beast {

/** A <em>Stream</em> with attached <em>DynamicBuffer</em> to buffer reads.

    This wraps a <em>Stream</em> implementation so that calls to write are
    passed through to the underlying stream, while calls to read will
    first consume the input sequence stored in a <em>DynamicBuffer</em> which
    is part of the object.

    The use-case for this class is different than that of the
    `net::buffered_read_stream`. It is designed to facilitate
    the use of `net::read_until`, and to allow buffers
    acquired during detection of handshakes to be made transparently
    available to callers. A hypothetical implementation of the
    buffered version of `net::ssl::stream::async_handshake`
    could make use of this wrapper.

    Uses:

    @li Transparently leave untouched input acquired in calls
      to `net::read_until` behind for subsequent callers.

    @li "Preload" a stream with handshake input data acquired
      from other sources.

    Example:
    @code
    // Process the next HTTP header on the stream,
    // leaving excess bytes behind for the next call.
    //
    template<class Stream, class DynamicBuffer>
    void process_http_message(
        buffered_read_stream<Stream, DynamicBuffer>& stream)
    {
        // Read up to and including the end of the HTTP
        // header, leaving the sequence in the stream's
        // buffer. read_until may read past the end of the
        // headers; the return value will include only the
        // part up to the end of the delimiter.
        //
        std::size_t bytes_transferred =
            net::read_until(
                stream.next_layer(), stream.buffer(), "\r\n\r\n");

        // Use buffers_prefix() to limit the input
        // sequence to only the data up to and including
        // the trailing "\r\n\r\n".
        //
        auto header_buffers = buffers_prefix(
            bytes_transferred, stream.buffer().data());

        ...

        // Discard the portion of the input corresponding
        // to the HTTP headers.
        //
        stream.buffer().consume(bytes_transferred);

        // Everything we read from the stream
        // is part of the content-body.
    }
    @endcode

    @tparam Stream The type of stream to wrap.

    @tparam DynamicBuffer The type of stream buffer to use.
*/
template<class Stream, class DynamicBuffer>
class buffered_read_stream
{
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");

    struct ops;

    DynamicBuffer buffer_;
    std::size_t capacity_ = 0;
    Stream next_layer_;

public:
    /// The type of the internal buffer
    using buffer_type = DynamicBuffer;

    /// The type of the next layer.
    using next_layer_type =
        typename std::remove_reference<Stream>::type;

    /** Move constructor.

        @note The behavior of move assignment on or from streams
        with active or pending operations is undefined.
    */
    buffered_read_stream(buffered_read_stream&&) = default;

    /** Move assignment.

        @note The behavior of move assignment on or from streams
        with active or pending operations is undefined.
    */
    buffered_read_stream& operator=(buffered_read_stream&&) = default;

    /** Construct the wrapping stream.

        @param args Parameters forwarded to the `Stream` constructor.
    */
    template<class... Args>
    explicit
    buffered_read_stream(Args&&... args);

    /// Get a reference to the next layer.
    next_layer_type&
    next_layer() noexcept
    {
        return next_layer_;
    }

    /// Get a const reference to the next layer.
    next_layer_type const&
    next_layer() const noexcept
    {
        return next_layer_;
    }
    
    using executor_type =
        beast::executor_type<next_layer_type>;

    /** Get the executor associated with the object.
    
        This function may be used to obtain the executor object that the stream
        uses to dispatch handlers for asynchronous operations.

        @return A copy of the executor that stream will use to dispatch handlers.
    */
    executor_type
    get_executor() noexcept
    {
        return next_layer_.get_executor();
    }

    /** Access the internal buffer.

        The internal buffer is returned. It is possible for the
        caller to break invariants with this function. For example,
        by causing the internal buffer size to increase beyond
        the caller defined maximum.
    */
    DynamicBuffer&
    buffer() noexcept
    {
        return buffer_;
    }

    /// Access the internal buffer
    DynamicBuffer const&
    buffer() const noexcept
    {
        return buffer_;
    }

    /** Set the maximum buffer size.

        This changes the maximum size of the internal buffer used
        to hold read data. No bytes are discarded by this call. If
        the buffer size is set to zero, no more data will be buffered.

        Thread safety:
            The caller is responsible for making sure the call is
            made from the same implicit or explicit strand.

        @param size The number of bytes in the read buffer.

        @note This is a soft limit. If the new maximum size is smaller
        than the amount of data in the buffer, no bytes are discarded.
    */
    void
    capacity(std::size_t size) noexcept
    {
        capacity_ = size;
    }

    /** Read some data from the stream.

        This function is used to read data from the stream.
        The function call will block until one or more bytes of
        data has been read successfully, or until an error occurs.

        @param buffers One or more buffers into which the data will be read.

        @return The number of bytes read.

        @throws system_error Thrown on failure.
    */
    template<class MutableBufferSequence>
    std::size_t
    read_some(MutableBufferSequence const& buffers);

    /** Read some data from the stream.

        This function is used to read data from the stream.
        The function call will block until one or more bytes of
        data has been read successfully, or until an error occurs.

        @param buffers One or more buffers into which the data will be read.

        @param ec Set to the error, if any occurred.

        @return The number of bytes read, or 0 on error.
    */
    template<class MutableBufferSequence>
    std::size_t
    read_some(MutableBufferSequence const& buffers,
        error_code& ec);

    /** Start an asynchronous read.

        This function is used to asynchronously read data from
        the stream. The function call always returns immediately.

        @param buffers One or more buffers into which the data
        will be read. Although the buffers object may be copied
        as necessary, ownership of the underlying memory blocks
        is retained by the caller, which must guarantee that they
        remain valid until the handler is called.

        @param handler The completion handler to invoke when the operation
        completes. The implementation takes ownership of the handler by
        performing a decay-copy. The equivalent function signature of
        the handler must be:
        @code
        void handler(
            error_code const& error,      // result of operation
            std::size_t bytes_transferred // number of bytes transferred
        );
        @endcode        
        Regardless of whether the asynchronous operation completes
        immediately or not, the handler will not be invoked from within
        this function. Invocation of the handler will be performed in a
        manner equivalent to using `net::post`.
    */
    template<
        class MutableBufferSequence,
        BOOST_BEAST_ASYNC_TPARAM2 ReadHandler =
            net::default_completion_token_t<executor_type>>
    BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
    async_read_some(
        MutableBufferSequence const& buffers,
        ReadHandler&& handler =
            net::default_completion_token_t<executor_type>{});

    /** Write some data to the stream.

        This function is used to write data to the stream.
        The function call will block until one or more bytes of the
        data has been written successfully, or until an error occurs.

        @param buffers One or more data buffers to be written to the stream.

        @return The number of bytes written.

        @throws system_error Thrown on failure.
    */
    template<class ConstBufferSequence>
    std::size_t
    write_some(ConstBufferSequence const& buffers)
    {
        static_assert(is_sync_write_stream<next_layer_type>::value,
            "SyncWriteStream type requirements not met");
        return next_layer_.write_some(buffers);
    }

    /** Write some data to the stream.

        This function is used to write data to the stream.
        The function call will block until one or more bytes of the
        data has been written successfully, or until an error occurs.

        @param buffers One or more data buffers to be written to the stream.

        @param ec Set to the error, if any occurred.

        @return The number of bytes written.
    */
    template<class ConstBufferSequence>
    std::size_t
    write_some(ConstBufferSequence const& buffers,
        error_code& ec)
    {
        static_assert(is_sync_write_stream<next_layer_type>::value,
            "SyncWriteStream type requirements not met");
        return next_layer_.write_some(buffers, ec);
    }

    /** Start an asynchronous write.

        This function is used to asynchronously write data from
        the stream. The function call always returns immediately.

        @param buffers One or more data buffers to be written to
        the stream. Although the buffers object may be copied as
        necessary, ownership of the underlying memory blocks is
        retained by the caller, which must guarantee that they
        remain valid until the handler is called.

        @param handler The completion handler to invoke when the operation
        completes. The implementation takes ownership of the handler by
        performing a decay-copy. The equivalent function signature of
        the handler must be:
        @code
        void handler(
            error_code const& error,      // result of operation
            std::size_t bytes_transferred // number of bytes transferred
        );
        @endcode
        Regardless of whether the asynchronous operation completes
        immediately or not, the handler will not be invoked from within
        this function. Invocation of the handler will be performed in a
        manner equivalent to using `net::post`.
    */
    template<
        class ConstBufferSequence,
        BOOST_BEAST_ASYNC_TPARAM2 WriteHandler =
            net::default_completion_token_t<executor_type>>
    BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
    async_write_some(
        ConstBufferSequence const& buffers,
        WriteHandler&& handler =
            net::default_completion_token_t<executor_type>{});
};

} // beast
} // boost

#include <boost/beast/core/impl/buffered_read_stream.hpp>

#endif

/* buffered_read_stream.hpp
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
*/