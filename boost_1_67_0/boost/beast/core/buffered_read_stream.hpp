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