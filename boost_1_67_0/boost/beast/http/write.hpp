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