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
OWmEKcf7e3uue9tpd9VL19/f23WeHPqhoENPmj+Z7cnJb+qrvQf6yrDpyz1NqbqdBfM4++WI6cHjkjrr/cRVf117fxdZxJis25zzldl4XzHGJh/YeQPrWnswNkm1tbugdOg69oE93HbeaNy5Sq5xXBuSCZphzVXFio4umbeoaG1deUltaUWR76a4uPbDaU+TMpkSPlV0txY7xKgPezjf4Xk2MNcoMtxYs9Hhnp9F5v4GpId2EwN7QKaKriQN8DP3+8h97WeEUw8pKrAe9c0EpQp8erBelLAw7Jwp8A5as8b8kzfFuZZMr1tZHuv8thX6vMRoc22YI617Zyq5Gj2+b3pe4NhsuH1pray23k4b5CtLqHW/5B2pEmgj9gvivtxTqvqY62f1mrHdEp7gKeE678U6jlRtE+ivcXKutfO7jv6Oc5/wv2ztP2SZMw5ou7/w+OMYzHWGxvoirvPeLOG1dNv5Rwa+8Wg7pFkSHgf9RWk7Sbni97SainoWa+yteTIN536BnskQt3wPejDB+t/9/TbO9c/5gTXDjroIHXHt3y8lXfh+lm0v78LzAv2XYjvNRV6L+0l5S4aLSmU5kIrRba+EZe3n62uErWUZMgwu1slQ7UzyEK3bFOJm38M2Zjt/e9b5wemdAeZGR3qL5q1YOHf5/Pyi+UsLii70rRXtEy9pL7KdMcv0B8LXMpz1kHmw1m2tga6Og/4s6xJ9a7W62rf2kfaGe9MvXvvJ/Wx5HDwr+LzVHGvM389/3qp+vCxduDL/kgVcWOdcG8k8Uk6vSXKeo6vD9Tq0bpy7mh58VjPXIOEejny1uuRrajb8Q+YL3QztJE/zfcfC1l3sEDb3+zjSvqoLaU9k2qdJOhmnI633XOBeBu2h0sqz0EOVQXvHZYDwMz/LuDtlMGt2cL4mZVsJCZWvupra+lD5opyR7vvPMN22+j8nOI2zssEfKo3GWeXnBaWRcqHPHUb4mZ87fF4Xzio/AUwKD3W+cOjzbeeLXbNZ/8gau/Lklpv3XXRF0rGo22/o/jm27vbgQp3zG8pOXPftwbnba+v+ecru9unO3nnK9RL/tkfue+G1Z3Jytj6zoqHyjoePyZkA8P/BLwr/+mjV8KMf7Ghe8OKor/0NNpvFv+WVy0feW/xYzCdin/MknnzkKfQnYs9u34G21Jildz96++8fPaKmz/iWUo9K/PXJt7699dLPXfGJ8Zftjs/t++rZO8c5lB3AAknnSzeV3fnw0L8/eXTI2t8f3Pbd8Rh3ZFj+Dzz+ue/94sdXn7o2Yf/gCdH/WBrKXl6oc5+7b68wHgT/gvsXHn2sKrcpu+1nb7x/x1i8pwbsockei/2Q/43yraH24v/F+P9D4/8B4/+Pjf8/CPyXZ3S7R+y4qYP8P4s2/lr8dgNoqwFhMq+4R/F9BZ1MPHACcBpwMnA2cCpwIfAcYDkwF1gBnA/cCDwX2ACcAfwccCbwfoY/AJwFfAo4G/gd4Bzgy8C5wNfI9xdgNjCO5xQPBM7nOaFNinvjuW+gnXvItzHdF4FvCDAfeB5wCbAMuIznky5nulYBm4GX8BzmAuAB+v8YuBLYRvcLdB8GXszzmBcBP7DCma6DivvRgX2ZrkQ5p1YusVU4gOe+juQ5r+cAjwJX8LzXVcAYxPcR4DGen/s6z889DvwE8G88J/Nt4GeAJ4H3AU/xXN13gfuA7wEfB74PfBIYjniPACOAf+J9XgdGAU8Do4HhHvgzP8WK+8m5R93KT1/gSuYnGXzyHgccBBwBHAtMBY4DpgGnAtOB5wMzgAuAmcDLgaN5nxxQM+8TyfuY557ewfvcCYwA3mXItXQgdwvlbqXcbYZcawdyn6XcPZQ=
*/