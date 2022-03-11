//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_READ_HPP
#define BOOST_BEAST_DETAIL_READ_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/beast/core/detail/is_invocable.hpp>
#include <boost/asio/async_result.hpp>
#include <cstdlib>

namespace boost {
namespace beast {
namespace detail {

//------------------------------------------------------------------------------

/** Read data into a dynamic buffer from a stream until a condition is met.
    
    This function is used to read from a stream into a dynamic buffer until
    a condition is met. The call will block until one of the following is true:
    
    @li The specified dynamic buffer sequence is full (that is, it has
        reached its currently configured maximum size).

    @li The `completion_condition` function object returns 0.

    This operation is implemented in terms of zero or more calls to the
    stream's `read_some` function.
    
    @param stream The stream from which the data is to be read. The type
    must support the <em>SyncReadStream</em> requirements.
    
    @param buffer The dynamic buffer sequence into which the data will be read.
 
    @param completion_condition The function object to be called to determine
    whether the read operation is complete. The function object must be invocable
    with this signature:
    @code
    std::size_t
    completion_condition(
        // Modifiable result of latest read_some operation. 
        error_code& ec,
    
        // Number of bytes transferred so far.
        std::size_t bytes_transferred

        // The dynamic buffer used to store the bytes read
        DynamicBuffer& buffer
    );
    @endcode
    A non-zero return value indicates the maximum number of bytes to be read on
    the next call to the stream's `read_some` function. A return value of 0
    from the completion condition indicates that the read operation is complete;
    in this case the optionally modifiable error passed to the completion
    condition will be delivered to the caller as an exception.

    @returns The number of bytes transferred from the stream.

    @throws net::system_error Thrown on failure.
*/    
template<
    class SyncReadStream,
    class DynamicBuffer,
    class CompletionCondition
#if ! BOOST_BEAST_DOXYGEN
    , class = typename std::enable_if<
        is_sync_read_stream<SyncReadStream>::value &&
        net::is_dynamic_buffer<DynamicBuffer>::value &&
        detail::is_invocable<CompletionCondition,
            void(error_code&, std::size_t, DynamicBuffer&)>::value
    >::type
#endif
>
std::size_t
read(
    SyncReadStream& stream,
    DynamicBuffer& buffer,
    CompletionCondition completion_condition);

/** Read data into a dynamic buffer from a stream until a condition is met.
    
    This function is used to read from a stream into a dynamic buffer until
    a condition is met. The call will block until one of the following is true:
    
    @li The specified dynamic buffer sequence is full (that is, it has
        reached its currently configured maximum size).

    @li The `completion_condition` function object returns 0.
     
    This operation is implemented in terms of zero or more calls to the
    stream's `read_some` function.
    
    @param stream The stream from which the data is to be read. The type
    must support the <em>SyncReadStream</em> requirements.
    
    @param buffer The dynamic buffer sequence into which the data will be read.
 
    @param completion_condition The function object to be called to determine
    whether the read operation is complete. The function object must be invocable
    with this signature:
    @code
    std::size_t
    completion_condition(
        // Modifiable result of latest read_some operation. 
        error_code& ec,
    
        // Number of bytes transferred so far.
        std::size_t bytes_transferred

        // The dynamic buffer used to store the bytes read
        DynamicBuffer& buffer
    );
    @endcode
    A non-zero return value indicates the maximum number of bytes to be read on
    the next call to the stream's `read_some` function. A return value of 0
    from the completion condition indicates that the read operation is complete;
    in this case the optionally modifiable error passed to the completion
    condition will be delivered to the caller.

    @returns The number of bytes transferred from the stream.
*/    
template<
    class SyncReadStream,
    class DynamicBuffer,
    class CompletionCondition
#if ! BOOST_BEAST_DOXYGEN
    , class = typename std::enable_if<
        is_sync_read_stream<SyncReadStream>::value &&
        net::is_dynamic_buffer<DynamicBuffer>::value &&
        detail::is_invocable<CompletionCondition,
            void(error_code&, std::size_t, DynamicBuffer&)>::value
    >::type
#endif
>
std::size_t
read(
    SyncReadStream& stream,
    DynamicBuffer& buffer,
    CompletionCondition completion_condition,
    error_code& ec);

/** Asynchronously read data into a dynamic buffer from a stream until a condition is met.
    
    This function is used to asynchronously read from a stream into a dynamic
    buffer until a condition is met. The function call always returns immediately.
    The asynchronous operation will continue until one of the following is true:
    
    @li The specified dynamic buffer sequence is full (that is, it has
        reached its currently configured maximum size).

    @li The `completion_condition` function object returns 0.
    
    This operation is implemented in terms of zero or more calls to the stream's
    `async_read_some` function, and is known as a <em>composed operation</em>. The
    program must ensure that the stream performs no other read operations (such
    as `async_read`, the stream's `async_read_some` function, or any other composed
    operations that perform reads) until this operation completes.
    
    @param stream The stream from which the data is to be read. The type must
    support the <em>AsyncReadStream</em> requirements.
    
    @param buffer The dynamic buffer sequence into which the data will be read.
    Ownership of the object is retained by the caller, which must guarantee
    that it remains valid until the handler is called.

    @param completion_condition The function object to be called to determine
    whether the read operation is complete. The function object must be invocable
    with this signature:
    @code
    std::size_t
    completion_condition(
        // Modifiable result of latest async_read_some operation. 
        error_code& ec,

        // Number of bytes transferred so far.
        std::size_t bytes_transferred,

        // The dynamic buffer used to store the bytes read
        DynamicBuffer& buffer
    );
    @endcode
    A non-zero return value indicates the maximum number of bytes to be read on
    the next call to the stream's `async_read_some` function. A return value of 0
    from the completion condition indicates that the read operation is complete;
    in this case the optionally modifiable error passed to the completion
    condition will be delivered to the completion handler.

    @param handler The completion handler to invoke when the operation
    completes. The implementation takes ownership of the handler by
    performing a decay-copy. The equivalent function signature of
    the handler must be:
    @code
    void
    handler(
        error_code const& ec,               // Result of operation.

        std::size_t bytes_transferred       // Number of bytes copied into
                                            // the dynamic buffer. If an error
                                            // occurred, this will be the number
                                            // of bytes successfully transferred
                                            // prior to the error.
    );
    @endcode
    Regardless of whether the asynchronous operation completes
    immediately or not, the handler will not be invoked from within
    this function. Invocation of the handler will be performed in a
    manner equivalent to using `net::post`.
*/
template<
    class AsyncReadStream,
    class DynamicBuffer,
    class CompletionCondition,
    class ReadHandler
#if ! BOOST_BEAST_DOXYGEN
    , class = typename std::enable_if<
        is_async_read_stream<AsyncReadStream>::value &&
        net::is_dynamic_buffer<DynamicBuffer>::value &&
        detail::is_invocable<CompletionCondition,
            void(error_code&, std::size_t, DynamicBuffer&)>::value
    >::type
#endif
>
BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
async_read(
    AsyncReadStream& stream,
    DynamicBuffer& buffer,
    CompletionCondition&& completion_condition,
    ReadHandler&& handler);

} // detail
} // beast
} // boost

#include <boost/beast/core/detail/impl/read.hpp>

#endif

/* read.hpp
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
*/