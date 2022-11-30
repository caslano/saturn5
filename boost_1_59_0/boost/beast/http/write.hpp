//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_WRITE_HPP
#define BOOST_BEAST_HTTP_WRITE_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/serializer.hpp>
#include <boost/beast/http/type_traits.hpp>
#include <boost/beast/http/detail/chunk_encode.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/asio/async_result.hpp>
#include <iosfwd>
#include <limits>
#include <memory>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {
namespace http {

/** Write part of a message to a stream using a serializer.

    This function is used to write part of a message to a stream using
    a caller-provided HTTP/1 serializer. The call will block until one
    of the following conditions is true:
        
    @li One or more bytes have been transferred.

    @li The function @ref serializer::is_done returns `true`

    @li An error occurs on the stream.

    This operation is implemented in terms of one or more calls
    to the stream's `write_some` function.

    The amount of data actually transferred is controlled by the behavior
    of the underlying stream, subject to the buffer size limit of the
    serializer obtained or set through a call to @ref serializer::limit.
    Setting a limit and performing bounded work helps applications set
    reasonable timeouts. It also allows application-level flow control
    to function correctly. For example when using a TCP/IP based
    stream.

    @param stream The stream to which the data is to be written.
    The type must support the <em>SyncWriteStream</em> concept.

    @param sr The serializer to use.

    @return The number of bytes written to the stream.

    @throws system_error Thrown on failure.

    @see serializer
*/
template<
    class SyncWriteStream,
    bool isRequest, class Body, class Fields>
std::size_t
write_some(
    SyncWriteStream& stream,
    serializer<isRequest, Body, Fields>& sr);

/** Write part of a message to a stream using a serializer.

    This function is used to write part of a message to a stream using
    a caller-provided HTTP/1 serializer. The call will block until one
    of the following conditions is true:
        
    @li One or more bytes have been transferred.

    @li The function @ref serializer::is_done returns `true`

    @li An error occurs on the stream.

    This operation is implemented in terms of one or more calls
    to the stream's `write_some` function.

    The amount of data actually transferred is controlled by the behavior
    of the underlying stream, subject to the buffer size limit of the
    serializer obtained or set through a call to @ref serializer::limit.
    Setting a limit and performing bounded work helps applications set
    reasonable timeouts. It also allows application-level flow control
    to function correctly. For example when using a TCP/IP based
    stream.
    
    @param stream The stream to which the data is to be written.
    The type must support the <em>SyncWriteStream</em> concept.

    @param sr The serializer to use.

    @param ec Set to indicate what error occurred, if any.

    @return The number of bytes written to the stream.

    @see async_write_some, serializer
*/
template<
    class SyncWriteStream,
    bool isRequest, class Body, class Fields>
std::size_t
write_some(
    SyncWriteStream& stream,
    serializer<isRequest, Body, Fields>& sr,
    error_code& ec);

/** Write part of a message to a stream asynchronously using a serializer.

    This function is used to write part of a message to a stream
    asynchronously using a caller-provided HTTP/1 serializer. The function
    call always returns immediately. The asynchronous operation will continue
    until one of the following conditions is true:

    @li One or more bytes have been transferred.

    @li The function @ref serializer::is_done returns `true`

    @li An error occurs on the stream.

    This operation is implemented in terms of zero or more calls to the stream's
    `async_write_some` function, and is known as a <em>composed operation</em>.
    The program must ensure that the stream performs no other writes
    until this operation completes.

    The amount of data actually transferred is controlled by the behavior
    of the underlying stream, subject to the buffer size limit of the
    serializer obtained or set through a call to @ref serializer::limit.
    Setting a limit and performing bounded work helps applications set
    reasonable timeouts. It also allows application-level flow control
    to function correctly. For example when using a TCP/IP based
    stream.
    
    @param stream The stream to which the data is to be written.
    The type must support the <em>AsyncWriteStream</em> concept.

    @param sr The serializer to use.
    The object must remain valid at least until the
    handler is called; ownership is not transferred.

    @param handler The completion handler to invoke when the operation
    completes. The implementation takes ownership of the handler by
    performing a decay-copy. The equivalent function signature of
    the handler must be:
    @code
    void handler(
        error_code const& error,        // result of operation
        std::size_t bytes_transferred   // the number of bytes written to the stream
    );
    @endcode
    Regardless of whether the asynchronous operation completes
    immediately or not, the handler will not be invoked from within
    this function. Invocation of the handler will be performed in a
    manner equivalent to using `net::post`.

    @see serializer
*/
template<
    class AsyncWriteStream,
    bool isRequest, class Body, class Fields,
    BOOST_BEAST_ASYNC_TPARAM2 WriteHandler =
        net::default_completion_token_t<
            executor_type<AsyncWriteStream>>>
BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
async_write_some(
    AsyncWriteStream& stream,
    serializer<isRequest, Body, Fields>& sr,
    WriteHandler&& handler =
        net::default_completion_token_t<
            executor_type<AsyncWriteStream>>{});

//------------------------------------------------------------------------------

/** Write a header to a stream using a serializer.

    This function is used to write a header to a stream using a
    caller-provided HTTP/1 serializer. The call will block until one
    of the following conditions is true:

    @li The function @ref serializer::is_header_done returns `true`

    @li An error occurs.

    This operation is implemented in terms of one or more calls
    to the stream's `write_some` function.

    @param stream The stream to which the data is to be written.
    The type must support the <em>SyncWriteStream</em> concept.

    @param sr The serializer to use.

    @return The number of bytes written to the stream.

    @throws system_error Thrown on failure.

    @note The implementation will call @ref serializer::split with
    the value `true` on the serializer passed in.

    @see serializer
*/
template<
    class SyncWriteStream,
    bool isRequest, class Body, class Fields>
std::size_t
write_header(
    SyncWriteStream& stream,
    serializer<isRequest, Body, Fields>& sr);

/** Write a header to a stream using a serializer.

    This function is used to write a header to a stream using a
    caller-provided HTTP/1 serializer. The call will block until one
    of the following conditions is true:

    @li The function @ref serializer::is_header_done returns `true`

    @li An error occurs.

    This operation is implemented in terms of one or more calls
    to the stream's `write_some` function.

    @param stream The stream to which the data is to be written.
    The type must support the <em>SyncWriteStream</em> concept.

    @param sr The serializer to use.

    @param ec Set to indicate what error occurred, if any.

    @return The number of bytes written to the stream.

    @note The implementation will call @ref serializer::split with
    the value `true` on the serializer passed in.

    @see serializer
*/
template<
    class SyncWriteStream,
    bool isRequest, class Body, class Fields>
std::size_t
write_header(
    SyncWriteStream& stream,
    serializer<isRequest, Body, Fields>& sr,
    error_code& ec);

/** Write a header to a stream asynchronously using a serializer.

    This function is used to write a header to a stream asynchronously
    using a caller-provided HTTP/1 serializer. The function call always
    returns immediately. The asynchronous operation will continue until
    one of the following conditions is true:

    @li The function @ref serializer::is_header_done returns `true`

    @li An error occurs.

    This operation is implemented in terms of zero or more calls to the stream's
    `async_write_some` function, and is known as a <em>composed operation</em>.
    The program must ensure that the stream performs no other writes
    until this operation completes.

    @param stream The stream to which the data is to be written.
    The type must support the <em>AsyncWriteStream</em> concept.

    @param sr The serializer to use.
    The object must remain valid at least until the
    handler is called; ownership is not transferred.

    @param handler The completion handler to invoke when the operation
    completes. The implementation takes ownership of the handler by
    performing a decay-copy. The equivalent function signature of
    the handler must be:
    @code
    void handler(
        error_code const& error,        // result of operation
        std::size_t bytes_transferred   // the number of bytes written to the stream
    );
    @endcode
    Regardless of whether the asynchronous operation completes
    immediately or not, the handler will not be invoked from within
    this function. Invocation of the handler will be performed in a
    manner equivalent to using `net::post`.

    @note The implementation will call @ref serializer::split with
    the value `true` on the serializer passed in.

    @see serializer
*/
template<
    class AsyncWriteStream,
    bool isRequest, class Body, class Fields,
    BOOST_BEAST_ASYNC_TPARAM2 WriteHandler =
        net::default_completion_token_t<
            executor_type<AsyncWriteStream>>>
BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
async_write_header(
    AsyncWriteStream& stream,
    serializer<isRequest, Body, Fields>& sr,
    WriteHandler&& handler =
        net::default_completion_token_t<
            executor_type<AsyncWriteStream>>{});

//------------------------------------------------------------------------------

/** Write a complete message to a stream using a serializer.

    This function is used to write a complete message to a stream using
    a caller-provided HTTP/1 serializer. The call will block until one
    of the following conditions is true:

    @li The function @ref serializer::is_done returns `true`

    @li An error occurs.

    This operation is implemented in terms of one or more calls
    to the stream's `write_some` function.

    @param stream The stream to which the data is to be written.
    The type must support the <em>SyncWriteStream</em> concept.

    @param sr The serializer to use.

    @return The number of bytes written to the stream.

    @throws system_error Thrown on failure.

    @see serializer
*/
template<
    class SyncWriteStream,
    bool isRequest, class Body, class Fields>
std::size_t
write(
    SyncWriteStream& stream,
    serializer<isRequest, Body, Fields>& sr);

/** Write a complete message to a stream using a serializer.

    This function is used to write a complete message to a stream using
    a caller-provided HTTP/1 serializer. The call will block until one
    of the following conditions is true:

    @li The function @ref serializer::is_done returns `true`

    @li An error occurs.

    This operation is implemented in terms of one or more calls
    to the stream's `write_some` function.

    @param stream The stream to which the data is to be written.
    The type must support the <em>SyncWriteStream</em> concept.

    @param sr The serializer to use.

    @param ec Set to the error, if any occurred.

    @return The number of bytes written to the stream.

    @see serializer
*/
template<
    class SyncWriteStream,
    bool isRequest, class Body, class Fields>
std::size_t
write(
    SyncWriteStream& stream,
    serializer<isRequest, Body, Fields>& sr,
   error_code& ec);

/** Write a complete message to a stream asynchronously using a serializer.

    This function is used to write a complete message to a stream
    asynchronously using a caller-provided HTTP/1 serializer. The
    function call always returns immediately. The asynchronous
    operation will continue until one of the following conditions is true:

    @li The function @ref serializer::is_done returns `true`

    @li An error occurs.

    This operation is implemented in terms of zero or more calls to the stream's
    `async_write_some` function, and is known as a <em>composed operation</em>.
    The program must ensure that the stream performs no other writes
    until this operation completes.

    @param stream The stream to which the data is to be written.
    The type must support the <em>AsyncWriteStream</em> concept.

    @param sr The serializer to use.
    The object must remain valid at least until the
    handler is called; ownership is not transferred.

    @param handler The completion handler to invoke when the operation
    completes. The implementation takes ownership of the handler by
    performing a decay-copy. The equivalent function signature of
    the handler must be:
    @code
    void handler(
        error_code const& error,        // result of operation
        std::size_t bytes_transferred   // the number of bytes written to the stream
    );
    @endcode
    Regardless of whether the asynchronous operation completes
    immediately or not, the handler will not be invoked from within
    this function. Invocation of the handler will be performed in a
    manner equivalent to using `net::post`.

    @see serializer
*/
template<
    class AsyncWriteStream,
    bool isRequest, class Body, class Fields,
    BOOST_BEAST_ASYNC_TPARAM2 WriteHandler =
        net::default_completion_token_t<
            executor_type<AsyncWriteStream>>>
BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
async_write(
    AsyncWriteStream& stream,
    serializer<isRequest, Body, Fields>& sr,
    WriteHandler&& handler =
        net::default_completion_token_t<
            executor_type<AsyncWriteStream>>{});

//------------------------------------------------------------------------------

/** Write a complete message to a stream.

    This function is used to write a complete message to a stream using
    HTTP/1. The call will block until one of the following conditions is true:

    @li The entire message is written.

    @li An error occurs.

    This operation is implemented in terms of one or more calls to the stream's
    `write_some` function. The algorithm will use a temporary @ref serializer
    with an empty chunk decorator to produce buffers.

    @note This function only participates in overload resolution
    if @ref is_mutable_body_writer for <em>Body</em> returns `true`.

    @param stream The stream to which the data is to be written.
    The type must support the <em>SyncWriteStream</em> concept.

    @param msg The message to write.

    @return The number of bytes written to the stream.

    @throws system_error Thrown on failure.

    @see message
*/
template<
    class SyncWriteStream,
    bool isRequest, class Body, class Fields>
#if BOOST_BEAST_DOXYGEN
std::size_t
#else
typename std::enable_if<
    is_mutable_body_writer<Body>::value,
    std::size_t>::type
#endif
write(
    SyncWriteStream& stream,
    message<isRequest, Body, Fields>& msg);

/** Write a complete message to a stream.

    This function is used to write a complete message to a stream using
    HTTP/1. The call will block until one of the following conditions is true:

    @li The entire message is written.

    @li An error occurs.

    This operation is implemented in terms of one or more calls to the stream's
    `write_some` function. The algorithm will use a temporary @ref serializer
    with an empty chunk decorator to produce buffers.

    @note This function only participates in overload resolution
    if @ref is_mutable_body_writer for <em>Body</em> returns `false`.

    @param stream The stream to which the data is to be written.
    The type must support the <em>SyncWriteStream</em> concept.

    @param msg The message to write.

    @return The number of bytes written to the stream.

    @throws system_error Thrown on failure.

    @see message
*/
template<
    class SyncWriteStream,
    bool isRequest, class Body, class Fields>
#if BOOST_BEAST_DOXYGEN
std::size_t
#else
typename std::enable_if<
    ! is_mutable_body_writer<Body>::value,
    std::size_t>::type
#endif
write(
    SyncWriteStream& stream,
    message<isRequest, Body, Fields> const& msg);

/** Write a complete message to a stream.

    This function is used to write a complete message to a stream using
    HTTP/1. The call will block until one of the following conditions is true:

    @li The entire message is written.

    @li An error occurs.

    This operation is implemented in terms of one or more calls to the stream's
    `write_some` function. The algorithm will use a temporary @ref serializer
    with an empty chunk decorator to produce buffers.

    @note This function only participates in overload resolution
    if @ref is_mutable_body_writer for <em>Body</em> returns `true`.

    @param stream The stream to which the data is to be written.
    The type must support the <em>SyncWriteStream</em> concept.

    @param msg The message to write.

    @param ec Set to the error, if any occurred.

    @return The number of bytes written to the stream.

    @see message
*/
template<
    class SyncWriteStream,
    bool isRequest, class Body, class Fields>
#if BOOST_BEAST_DOXYGEN
std::size_t
#else
typename std::enable_if<
    is_mutable_body_writer<Body>::value,
    std::size_t>::type
#endif
write(
    SyncWriteStream& stream,
    message<isRequest, Body, Fields>& msg,
    error_code& ec);

/** Write a complete message to a stream.

    This function is used to write a complete message to a stream using
    HTTP/1. The call will block until one of the following conditions is true:

    @li The entire message is written.

    @li An error occurs.

    This operation is implemented in terms of one or more calls to the stream's
    `write_some` function. The algorithm will use a temporary @ref serializer
    with an empty chunk decorator to produce buffers.

    @note This function only participates in overload resolution
    if @ref is_mutable_body_writer for <em>Body</em> returns `false`.

    @param stream The stream to which the data is to be written.
    The type must support the <em>SyncWriteStream</em> concept.

    @param msg The message to write.

    @param ec Set to the error, if any occurred.

    @return The number of bytes written to the stream.

    @see message
*/
template<
    class SyncWriteStream,
    bool isRequest, class Body, class Fields>
#if BOOST_BEAST_DOXYGEN
std::size_t
#else
typename std::enable_if<
    ! is_mutable_body_writer<Body>::value,
    std::size_t>::type
#endif
write(
    SyncWriteStream& stream,
    message<isRequest, Body, Fields> const& msg,
    error_code& ec);

/** Write a complete message to a stream asynchronously.

    This function is used to write a complete message to a stream asynchronously
    using HTTP/1. The function call always returns immediately. The asynchronous
    operation will continue until one of the following conditions is true:

    @li The entire message is written.

    @li An error occurs.

    This operation is implemented in terms of zero or more calls to the stream's
    `async_write_some` function, and is known as a <em>composed operation</em>.
    The program must ensure that the stream performs no other writes
    until this operation completes. The algorithm will use a temporary
    @ref serializer with an empty chunk decorator to produce buffers.

    @note This function only participates in overload resolution
    if @ref is_mutable_body_writer for <em>Body</em> returns `true`.

    @param stream The stream to which the data is to be written.
    The type must support the <em>AsyncWriteStream</em> concept.

    @param msg The message to write.
    The object must remain valid at least until the
    handler is called; ownership is not transferred.

    @param handler The completion handler to invoke when the operation
    completes. The implementation takes ownership of the handler by
    performing a decay-copy. The equivalent function signature of
    the handler must be:
    @code
    void handler(
        error_code const& error,        // result of operation
        std::size_t bytes_transferred   // the number of bytes written to the stream
    );
    @endcode
    Regardless of whether the asynchronous operation completes
    immediately or not, the handler will not be invoked from within
    this function. Invocation of the handler will be performed in a
    manner equivalent to using `net::post`.

    @see message
*/
template<
    class AsyncWriteStream,
    bool isRequest, class Body, class Fields,
    BOOST_BEAST_ASYNC_TPARAM2 WriteHandler =
        net::default_completion_token_t<
            executor_type<AsyncWriteStream>>>
BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
async_write(
    AsyncWriteStream& stream,
    message<isRequest, Body, Fields>& msg,
    WriteHandler&& handler =
        net::default_completion_token_t<
            executor_type<AsyncWriteStream>>{}
#ifndef BOOST_BEAST_DOXYGEN
    , typename std::enable_if<
        is_mutable_body_writer<Body>::value>::type* = 0
#endif
    );

/** Write a complete message to a stream asynchronously.

    This function is used to write a complete message to a stream asynchronously
    using HTTP/1. The function call always returns immediately. The asynchronous
    operation will continue until one of the following conditions is true:

    @li The entire message is written.

    @li An error occurs.

    This operation is implemented in terms of zero or more calls to the stream's
    `async_write_some` function, and is known as a <em>composed operation</em>.
    The program must ensure that the stream performs no other writes
    until this operation completes. The algorithm will use a temporary
    @ref serializer with an empty chunk decorator to produce buffers.

    @note This function only participates in overload resolution
    if @ref is_mutable_body_writer for <em>Body</em> returns `false`.

    @param stream The stream to which the data is to be written.
    The type must support the <em>AsyncWriteStream</em> concept.

    @param msg The message to write.
    The object must remain valid at least until the
    handler is called; ownership is not transferred.

    @param handler The completion handler to invoke when the operation
    completes. The implementation takes ownership of the handler by
    performing a decay-copy. The equivalent function signature of
    the handler must be:
    @code
    void handler(
        error_code const& error,        // result of operation
        std::size_t bytes_transferred   // the number of bytes written to the stream
    );
    @endcode
    Regardless of whether the asynchronous operation completes
    immediately or not, the handler will not be invoked from within
    this function. Invocation of the handler will be performed in a
    manner equivalent to using `net::post`.

    @see message
*/
template<
    class AsyncWriteStream,
    bool isRequest, class Body, class Fields,
    BOOST_BEAST_ASYNC_TPARAM2 WriteHandler =
        net::default_completion_token_t<
            executor_type<AsyncWriteStream>>>
BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
async_write(
    AsyncWriteStream& stream,
    message<isRequest, Body, Fields> const& msg,
    WriteHandler&& handler =
        net::default_completion_token_t<
            executor_type<AsyncWriteStream>>{}
#ifndef BOOST_BEAST_DOXYGEN
    , typename std::enable_if<
        ! is_mutable_body_writer<Body>::value>::type* = 0
#endif
    );


//------------------------------------------------------------------------------

/** Serialize an HTTP/1 header to a `std::ostream`.

    The function converts the header to its HTTP/1 serialized
    representation and stores the result in the output stream.

    @param os The output stream to write to.

    @param msg The message fields to write.
*/
template<bool isRequest, class Fields>
std::ostream&
operator<<(std::ostream& os,
    header<isRequest, Fields> const& msg);

/** Serialize an HTTP/1 message to a `std::ostream`.

    The function converts the message to its HTTP/1 serialized
    representation and stores the result in the output stream.

    The implementation will automatically perform chunk encoding if
    the contents of the message indicate that chunk encoding is required.

    @param os The output stream to write to.

    @param msg The message to write.
*/
template<bool isRequest, class Body, class Fields>
std::ostream&
operator<<(std::ostream& os,
    message<isRequest, Body, Fields> const& msg);

} // http
} // beast
} // boost

#include <boost/beast/http/impl/write.hpp>

#endif

/* write.hpp
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
*/