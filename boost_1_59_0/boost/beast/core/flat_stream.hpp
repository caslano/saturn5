//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_FLAT_STREAM_HPP
#define BOOST_BEAST_CORE_FLAT_STREAM_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/beast/core/detail/flat_stream.hpp>
#include <boost/asio/async_result.hpp>
#include <cstdlib>
#include <utility>

namespace boost {
namespace beast {

/** Stream wrapper to improve write performance.

    This wrapper flattens writes for buffer sequences having length
    greater than 1 and total size below a predefined amount, using
    a dynamic memory allocation. It is primarily designed to overcome
    a performance limitation of the current version of `net::ssl::stream`,
    which does not use OpenSSL's scatter/gather interface for its
    low-level read some and write some operations.

    It is normally not necessary to use this class directly if you
    are already using @ref ssl_stream. The following examples shows
    how to use this class with the ssl stream that comes with
    networking:

    @par Example

    To use the @ref flat_stream template with SSL streams, declare
    a variable of the correct type. Parameters passed to the constructor
    will be forwarded to the next layer's constructor:

    @code
        flat_stream<net::ssl::stream<ip::tcp::socket>> fs{ioc, ctx};
    @endcode
    Alternatively you can write
    @code
        ssl::stream<ip::tcp::socket> ss{ioc, ctx};
        flat_stream<net::ssl::stream<ip::tcp::socket>&> fs{ss};
    @endcode

    The resulting stream may be passed to any stream algorithms which
    operate on synchronous or asynchronous read or write streams,
    examples include:
    
    @li `net::read`, `net::async_read`

    @li `net::write`, `net::async_write`

    @li `net::read_until`, `net::async_read_until`

    The stream may also be used as a template parameter in other
    stream wrappers, such as for websocket:
    @code
        websocket::stream<flat_stream<net::ssl::stream<ip::tcp::socket>>> ws{ioc, ctx};
    @endcode

    @tparam NextLayer The type representing the next layer, to which
    data will be read and written during operations. For synchronous
    operations, the type must support the @b SyncStream concept. For
    asynchronous operations, the type must support the @b AsyncStream
    concept. This type will usually be some variation of
    `net::ssl::stream`.

    @par Concepts
        @li SyncStream
        @li AsyncStream

    @see
        @li https://github.com/boostorg/asio/issues/100
        @li https://github.com/boostorg/beast/issues/1108
        @li https://stackoverflow.com/questions/38198638/openssl-ssl-write-from-multiple-buffers-ssl-writev
        @li https://stackoverflow.com/questions/50026167/performance-drop-on-port-from-beast-1-0-0-b66-to-boost-1-67-0-beast
*/
template<class NextLayer>
class flat_stream
#if ! BOOST_BEAST_DOXYGEN
    : private detail::flat_stream_base
#endif
{
    NextLayer stream_;
    flat_buffer buffer_;

    BOOST_STATIC_ASSERT(has_get_executor<NextLayer>::value);

    struct ops;

    template<class ConstBufferSequence>
    std::size_t
    stack_write_some(
        std::size_t size,
        ConstBufferSequence const& buffers,
        error_code& ec);

public:
    /// The type of the next layer.
    using next_layer_type =
        typename std::remove_reference<NextLayer>::type;

    /// The type of the executor associated with the object.
    using executor_type = beast::executor_type<next_layer_type>;

    flat_stream(flat_stream&&) = default;
    flat_stream(flat_stream const&) = default;
    flat_stream& operator=(flat_stream&&) = default;
    flat_stream& operator=(flat_stream const&) = default;

    /** Destructor

        The treatment of pending operations will be the same as that
        of the next layer.
    */
    ~flat_stream() = default;

    /** Constructor

        Arguments, if any, are forwarded to the next layer's constructor.
    */
    template<class... Args>
    explicit
    flat_stream(Args&&... args);

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
    next_layer() noexcept
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
    next_layer() const noexcept
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
        
        @throws boost::system::system_error Thrown on failure.
        
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
            error_code const& error,        // Result of operation.
            std::size_t bytes_transferred   // Number of bytes read.
        );
        @endcode
        Regardless of whether the asynchronous operation completes
        immediately or not, the handler will not be invoked from within
        this function. Invocation of the handler will be performed in a
        manner equivalent to using `net::post`.
        
        @note The `read_some` operation may not read all of the requested number of
        bytes. Consider using the function `net::async_read` if you need
        to ensure that the requested amount of data is read before the asynchronous
        operation completes.
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
    
        This function is used to write data on the stream. The function call will
        block until one or more bytes of data has been written successfully, or
        until an error occurs.
        
        @param buffers The data to be written.
        
        @returns The number of bytes written.
        
        @throws boost::system::system_error Thrown on failure.
        
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
            error_code const& ec,           // Result of operation.
            std::size_t bytes_transferred   // Number of bytes written.
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
            net::default_completion_token_t<executor_type>>
    BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
    async_write_some(
        ConstBufferSequence const& buffers,
        WriteHandler&& handler =
            net::default_completion_token_t<executor_type>{});
};

} // beast
} // boost

#include <boost/beast/core/impl/flat_stream.hpp>

#endif

/* flat_stream.hpp
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
*/