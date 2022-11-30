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
    BOOST_BEAST_ASYNC_TPARAM2 ReadHandler
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