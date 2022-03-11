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