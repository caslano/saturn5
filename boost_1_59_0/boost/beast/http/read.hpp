//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_READ_HPP
#define BOOST_BEAST_HTTP_READ_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/beast/http/basic_parser.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/asio/async_result.hpp>

namespace boost {
namespace beast {
namespace http {

//------------------------------------------------------------------------------

/** Read part of a message from a stream using a parser.

    This function is used to read part of a message from a stream into an
    instance of @ref basic_parser. The call will block until one of the
    following conditions is true:

    @li A call to @ref basic_parser::put with a non-empty buffer sequence
        is successful.

    @li An error occurs.

    This operation is implemented in terms of one or more calls to the stream's
    `read_some` function. The implementation may read additional bytes from
    the stream that lie past the end of the message being read. These additional
    bytes are stored in the dynamic buffer, which must be preserved for
    subsequent reads.

    If the end of file error is received while reading from the stream, then
    the error returned from this function will be:

    @li @ref error::end_of_stream if no bytes were parsed, or

    @li @ref error::partial_message if any bytes were parsed but the
        message was incomplete, otherwise:

    @li A successful result. The next attempt to read will return
        @ref error::end_of_stream

    @param stream The stream from which the data is to be read. The type must
    meet the <em>SyncReadStream</em> requirements.

    @param buffer Storage for additional bytes read by the implementation from
    the stream. This is both an input and an output parameter; on entry, the
    parser will be presented with any remaining data in the dynamic buffer's
    readable bytes sequence first. The type must meet the <em>DynamicBuffer</em>
    requirements.

    @param parser The parser to use.

    @return The number of bytes transferred from the stream.

    @throws system_error Thrown on failure.

    @note The function returns the total number of bytes transferred from the
    stream. This may be zero for the case where there is sufficient pre-existing
    message data in the dynamic buffer.
*/
template<
    class SyncReadStream,
    class DynamicBuffer,
    bool isRequest>
std::size_t
read_some(
    SyncReadStream& stream,
    DynamicBuffer& buffer,
    basic_parser<isRequest>& parser);

/** Read part of a message from a stream using a parser.

    This function is used to read part of a message from a stream into an
    instance of @ref basic_parser. The call will block until one of the
    following conditions is true:

    @li A call to @ref basic_parser::put with a non-empty buffer sequence
        is successful.

    @li An error occurs.

    This operation is implemented in terms of one or more calls to the stream's
    `read_some` function. The implementation may read additional bytes from
    the stream that lie past the end of the message being read. These additional
    bytes are stored in the dynamic buffer, which must be preserved for
    subsequent reads.

    If the end of file error is received while reading from the stream, then
    the error returned from this function will be:

    @li @ref error::end_of_stream if no bytes were parsed, or

    @li @ref error::partial_message if any bytes were parsed but the
        message was incomplete, otherwise:

    @li A successful result. The next attempt to read will return
        @ref error::end_of_stream

    @param stream The stream from which the data is to be read. The type must
    support the <em>SyncReadStream</em> requirements.

    @param buffer Storage for additional bytes read by the implementation from
    the stream. This is both an input and an output parameter; on entry, the
    parser will be presented with any remaining data in the dynamic buffer's
    readable bytes sequence first. The type must meet the <em>DynamicBuffer</em>
    requirements.

    @param parser The parser to use.

    @param ec Set to the error, if any occurred.

    @return The number of bytes transferred from the stream.

    @note The function returns the total number of bytes transferred from the
    stream. This may be zero for the case where there is sufficient pre-existing
    message data in the dynamic buffer.
*/
template<
    class SyncReadStream,
    class DynamicBuffer,
    bool isRequest>
std::size_t
read_some(
    SyncReadStream& stream,
    DynamicBuffer& buffer,
    basic_parser<isRequest>& parser,
    error_code& ec);

/** Read part of a message asynchronously from a stream using a parser.

    This function is used to asynchronously read part of a message from
    a stream into an instance of @ref basic_parser. The function call
    always returns immediately. The asynchronous operation will continue
    until one of the following conditions is true:

    @li A call to @ref basic_parser::put with a non-empty buffer sequence
        is successful.

    @li An error occurs.

    This operation is implemented in terms of zero or more calls to the
    next layer's `async_read_some` function, and is known as a <em>composed
    operation</em>. The program must ensure that the stream performs no other
    reads until this operation completes. The implementation may read additional
    bytes from the stream that lie past the end of the message being read.
    These additional bytes are stored in the dynamic buffer, which must be
    preserved for subsequent reads.

    If the end of file error is received while reading from the stream, then
    the error returned from this function will be:

    @li @ref error::end_of_stream if no bytes were parsed, or

    @li @ref error::partial_message if any bytes were parsed but the
        message was incomplete, otherwise:

    @li A successful result. The next attempt to read will return
        @ref error::end_of_stream

    @param stream The stream from which the data is to be read. The type
    must meet the <em>AsyncReadStream</em> requirements.

    @param buffer Storage for additional bytes read by the implementation from
    the stream. This is both an input and an output parameter; on entry, the
    parser will be presented with any remaining data in the dynamic buffer's
    readable bytes sequence first. The type must meet the <em>DynamicBuffer</em>
    requirements. The object must remain valid at least until the handler
    is called; ownership is not transferred.

    @param parser The parser to use. The object must remain valid at least until
    the handler is called; ownership is not transferred.

    @param handler The completion handler to invoke when the operation
    completes. The implementation takes ownership of the handler by
    performing a decay-copy. The equivalent function signature of
    the handler must be:
    @code
    void handler(
        error_code const& error,        // result of operation
        std::size_t bytes_transferred   // the total number of bytes transferred from the stream
    );
    @endcode
    Regardless of whether the asynchronous operation completes
    immediately or not, the handler will not be invoked from within
    this function. Invocation of the handler will be performed in a
    manner equivalent to using `net::post`.

    @note The completion handler will receive as a parameter the total number
    of bytes transferred from the stream. This may be zero for the case where
    there is sufficient pre-existing message data in the dynamic buffer.
*/
template<
    class AsyncReadStream,
    class DynamicBuffer,
    bool isRequest,
    BOOST_BEAST_ASYNC_TPARAM2 ReadHandler =
        net::default_completion_token_t<
            executor_type<AsyncReadStream>>>
BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
async_read_some(
    AsyncReadStream& stream,
    DynamicBuffer& buffer,
    basic_parser<isRequest>& parser,
    ReadHandler&& handler =
        net::default_completion_token_t<
            executor_type<AsyncReadStream>>{});

//------------------------------------------------------------------------------

/** Read a complete message header from a stream using a parser.

    This function is used to read a complete message header from a stream
    into an instance of @ref basic_parser. The call will block until one of the
    following conditions is true:

    @li @ref basic_parser::is_header_done returns `true`

    @li An error occurs.

    This operation is implemented in terms of one or more calls to the stream's
    `read_some` function. The implementation may read additional bytes from
    the stream that lie past the end of the message being read. These additional
    bytes are stored in the dynamic buffer, which must be preserved for
    subsequent reads.

    If the end of file error is received while reading from the stream, then
    the error returned from this function will be:

    @li @ref error::end_of_stream if no bytes were parsed, or

    @li @ref error::partial_message if any bytes were parsed but the
        message was incomplete, otherwise:

    @li A successful result. The next attempt to read will return
        @ref error::end_of_stream

    @param stream The stream from which the data is to be read. The type must
    meet the <em>SyncReadStream</em> requirements.

    @param buffer Storage for additional bytes read by the implementation from
    the stream. This is both an input and an output parameter; on entry, the
    parser will be presented with any remaining data in the dynamic buffer's
    readable bytes sequence first. The type must meet the <em>DynamicBuffer</em>
    requirements.

    @param parser The parser to use.

    @return The number of bytes transferred from the stream.

    @throws system_error Thrown on failure.

    @note The function returns the total number of bytes transferred from the
    stream. This may be zero for the case where there is sufficient pre-existing
    message data in the dynamic buffer. The implementation will call
    @ref basic_parser::eager with the value `false` on the parser passed in.
*/
template<
    class SyncReadStream,
    class DynamicBuffer,
    bool isRequest>
std::size_t
read_header(
    SyncReadStream& stream,
    DynamicBuffer& buffer,
    basic_parser<isRequest>& parser);

/** Read a complete message header from a stream using a parser.

    This function is used to read a complete message header from a stream
    into an instance of @ref basic_parser. The call will block until one of the
    following conditions is true:

    @li @ref basic_parser::is_header_done returns `true`

    @li An error occurs.

    This operation is implemented in terms of one or more calls to the stream's
    `read_some` function. The implementation may read additional bytes from
    the stream that lie past the end of the message being read. These additional
    bytes are stored in the dynamic buffer, which must be preserved for
    subsequent reads.

    If the end of file error is received while reading from the stream, then
    the error returned from this function will be:

    @li @ref error::end_of_stream if no bytes were parsed, or

    @li @ref error::partial_message if any bytes were parsed but the
        message was incomplete, otherwise:

    @li A successful result. The next attempt to read will return
        @ref error::end_of_stream

    @param stream The stream from which the data is to be read. The type must
    meet the <em>SyncReadStream</em> requirements.

    @param buffer Storage for additional bytes read by the implementation from
    the stream. This is both an input and an output parameter; on entry, the
    parser will be presented with any remaining data in the dynamic buffer's
    readable bytes sequence first. The type must meet the <em>DynamicBuffer</em>
    requirements.

    @param parser The parser to use.

    @param ec Set to the error, if any occurred.

    @return The number of bytes transferred from the stream.

    @note The function returns the total number of bytes transferred from the
    stream. This may be zero for the case where there is sufficient pre-existing
    message data in the dynamic buffer. The implementation will call
    @ref basic_parser::eager with the value `false` on the parser passed in.
*/
template<
    class SyncReadStream,
    class DynamicBuffer,
    bool isRequest>
std::size_t
read_header(
    SyncReadStream& stream,
    DynamicBuffer& buffer,
    basic_parser<isRequest>& parser,
    error_code& ec);

/** Read a complete message header asynchronously from a stream using a parser.

    This function is used to asynchronously read a complete message header from
    a stream into an instance of @ref basic_parser. The function call always
    returns immediately. The asynchronous operation will continue until one of
    the following conditions is true:

    @li @ref basic_parser::is_header_done returns `true`

    @li An error occurs.

    This operation is implemented in terms of zero or more calls to the
    next layer's `async_read_some` function, and is known as a <em>composed
    operation</em>. The program must ensure that the stream performs no other
    reads until this operation completes. The implementation may read additional
    bytes from the stream that lie past the end of the message being read.
    These additional bytes are stored in the dynamic buffer, which must be
    preserved for subsequent reads.

    If the end of file error is received while reading from the stream, then
    the error returned from this function will be:

    @li @ref error::end_of_stream if no bytes were parsed, or

    @li @ref error::partial_message if any bytes were parsed but the
        message was incomplete, otherwise:

    @li A successful result. The next attempt to read will return
        @ref error::end_of_stream

    @param stream The stream from which the data is to be read. The type
    must meet the <em>AsyncReadStream</em> requirements.

    @param buffer Storage for additional bytes read by the implementation from
    the stream. This is both an input and an output parameter; on entry, the
    parser will be presented with any remaining data in the dynamic buffer's
    readable bytes sequence first. The type must meet the <em>DynamicBuffer</em>
    requirements. The object must remain valid at least until the handler
    is called; ownership is not transferred.

    @param parser The parser to use. The object must remain valid at least until
    the handler is called; ownership is not transferred.

    @param handler The completion handler to invoke when the operation
    completes. The implementation takes ownership of the handler by
    performing a decay-copy. The equivalent function signature of
    the handler must be:
    @code
    void handler(
        error_code const& error,        // result of operation
        std::size_t bytes_transferred   // the total number of bytes transferred from the stream
    );
    @endcode
    Regardless of whether the asynchronous operation completes
    immediately or not, the handler will not be invoked from within
    this function. Invocation of the handler will be performed in a
    manner equivalent to using `net::post`.

    @note The completion handler will receive as a parameter the total number
    of bytes transferred from the stream. This may be zero for the case where
    there is sufficient pre-existing message data in the dynamic buffer. The
    implementation will call @ref basic_parser::eager with the value `false`
    on the parser passed in.
*/
template<
    class AsyncReadStream,
    class DynamicBuffer,
    bool isRequest,
    BOOST_BEAST_ASYNC_TPARAM2 ReadHandler =
        net::default_completion_token_t<
            executor_type<AsyncReadStream>>>
BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
async_read_header(
    AsyncReadStream& stream,
    DynamicBuffer& buffer,
    basic_parser<isRequest>& parser,
    ReadHandler&& handler =
        net::default_completion_token_t<
            executor_type<AsyncReadStream>>{});

//------------------------------------------------------------------------------

/** Read a complete message from a stream using a parser.

    This function is used to read a complete message from a stream into an
    instance of @ref basic_parser. The call will block until one of the
    following conditions is true:

    @li @ref basic_parser::is_done returns `true`

    @li An error occurs.

    This operation is implemented in terms of one or more calls to the stream's
    `read_some` function. The implementation may read additional bytes from
    the stream that lie past the end of the message being read. These additional
    bytes are stored in the dynamic buffer, which must be preserved for
    subsequent reads.

    If the end of file error is received while reading from the stream, then
    the error returned from this function will be:

    @li @ref error::end_of_stream if no bytes were parsed, or

    @li @ref error::partial_message if any bytes were parsed but the
        message was incomplete, otherwise:

    @li A successful result. The next attempt to read will return
        @ref error::end_of_stream

    @param stream The stream from which the data is to be read. The type must
    meet the <em>SyncReadStream</em> requirements.

    @param buffer Storage for additional bytes read by the implementation from
    the stream. This is both an input and an output parameter; on entry, the
    parser will be presented with any remaining data in the dynamic buffer's
    readable bytes sequence first. The type must meet the <em>DynamicBuffer</em>
    requirements.

    @param parser The parser to use.

    @return The number of bytes transferred from the stream.

    @throws system_error Thrown on failure.

    @note The function returns the total number of bytes transferred from the
    stream. This may be zero for the case where there is sufficient pre-existing
    message data in the dynamic buffer. The implementation will call
    @ref basic_parser::eager with the value `true` on the parser passed in.
*/
template<
    class SyncReadStream,
    class DynamicBuffer,
    bool isRequest>
std::size_t
read(
    SyncReadStream& stream,
    DynamicBuffer& buffer,
    basic_parser<isRequest>& parser);

/** Read a complete message from a stream using a parser.

    This function is used to read a complete message from a stream into an
    instance of @ref basic_parser. The call will block until one of the
    following conditions is true:

    @li @ref basic_parser::is_done returns `true`

    @li An error occurs.

    This operation is implemented in terms of one or more calls to the stream's
    `read_some` function. The implementation may read additional bytes from
    the stream that lie past the end of the message being read. These additional
    bytes are stored in the dynamic buffer, which must be preserved for
    subsequent reads.

    If the end of file error is received while reading from the stream, then
    the error returned from this function will be:

    @li @ref error::end_of_stream if no bytes were parsed, or

    @li @ref error::partial_message if any bytes were parsed but the
        message was incomplete, otherwise:

    @li A successful result. The next attempt to read will return
        @ref error::end_of_stream

    @param stream The stream from which the data is to be read. The type must
    meet the <em>SyncReadStream</em> requirements.

    @param buffer Storage for additional bytes read by the implementation from
    the stream. This is both an input and an output parameter; on entry, the
    parser will be presented with any remaining data in the dynamic buffer's
    readable bytes sequence first. The type must meet the <em>DynamicBuffer</em>
    requirements.

    @param parser The parser to use.

    @param ec Set to the error, if any occurred.

    @return The number of bytes transferred from the stream.

    @note The function returns the total number of bytes transferred from the
    stream. This may be zero for the case where there is sufficient pre-existing
    message data in the dynamic buffer. The implementation will call
    @ref basic_parser::eager with the value `true` on the parser passed in.
*/
template<
    class SyncReadStream,
    class DynamicBuffer,
    bool isRequest>
std::size_t
read(
    SyncReadStream& stream,
    DynamicBuffer& buffer,
    basic_parser<isRequest>& parser,
    error_code& ec);

/** Read a complete message asynchronously from a stream using a parser.

    This function is used to asynchronously read a complete message from a
    stream into an instance of @ref basic_parser. The function call always
    returns immediately. The asynchronous operation will continue until one
    of the following conditions is true:

    @li @ref basic_parser::is_done returns `true`

    @li An error occurs.

    This operation is implemented in terms of zero or more calls to the
    next layer's `async_read_some` function, and is known as a <em>composed
    operation</em>. The program must ensure that the stream performs no other
    reads until this operation completes. The implementation may read additional
    bytes from the stream that lie past the end of the message being read.
    These additional bytes are stored in the dynamic buffer, which must be
    preserved for subsequent reads.

    If the end of file error is received while reading from the stream, then
    the error returned from this function will be:

    @li @ref error::end_of_stream if no bytes were parsed, or

    @li @ref error::partial_message if any bytes were parsed but the
        message was incomplete, otherwise:

    @li A successful result. The next attempt to read will return
        @ref error::end_of_stream

    @param stream The stream from which the data is to be read. The type
    must meet the <em>AsyncReadStream</em> requirements.

    @param buffer Storage for additional bytes read by the implementation from
    the stream. This is both an input and an output parameter; on entry, the
    parser will be presented with any remaining data in the dynamic buffer's
    readable bytes sequence first. The type must meet the <em>DynamicBuffer</em>
    requirements. The object must remain valid at least until the handler
    is called; ownership is not transferred.

    @param parser The parser to use. The object must remain valid at least until
    the handler is called; ownership is not transferred.

    @param handler The completion handler to invoke when the operation
    completes. The implementation takes ownership of the handler by
    performing a decay-copy. The equivalent function signature of
    the handler must be:
    @code
    void handler(
        error_code const& error,        // result of operation
        std::size_t bytes_transferred   // the total number of bytes transferred from the stream
    );
    @endcode
    Regardless of whether the asynchronous operation completes
    immediately or not, the handler will not be invoked from within
    this function. Invocation of the handler will be performed in a
    manner equivalent to using `net::post`.

    @note The completion handler will receive as a parameter the total number
    of bytes transferred from the stream. This may be zero for the case where
    there is sufficient pre-existing message data in the dynamic buffer. The
    implementation will call @ref basic_parser::eager with the value `true`
    on the parser passed in.
*/
template<
    class AsyncReadStream,
    class DynamicBuffer,
    bool isRequest,
    BOOST_BEAST_ASYNC_TPARAM2 ReadHandler =
        net::default_completion_token_t<
            executor_type<AsyncReadStream>>>
BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
async_read(
    AsyncReadStream& stream,
    DynamicBuffer& buffer,
    basic_parser<isRequest>& parser,
    ReadHandler&& handler =
        net::default_completion_token_t<
            executor_type<AsyncReadStream>>{});

//------------------------------------------------------------------------------

/** Read a complete message from a stream.

    This function is used to read a complete message from a stream into an
    instance of @ref message. The call will block until one of the following
    conditions is true:

    @li The entire message is read in.

    @li An error occurs.

    This operation is implemented in terms of one or more calls to the stream's
    `read_some` function. The implementation may read additional bytes from
    the stream that lie past the end of the message being read. These additional
    bytes are stored in the dynamic buffer, which must be preserved for
    subsequent reads.

    If the end of file error is received while reading from the stream, then
    the error returned from this function will be:

    @li @ref error::end_of_stream if no bytes were parsed, or

    @li @ref error::partial_message if any bytes were parsed but the
        message was incomplete, otherwise:

    @li A successful result. The next attempt to read will return
        @ref error::end_of_stream

    @param stream The stream from which the data is to be read. The type must
    meet the <em>SyncReadStream</em> requirements.

    @param buffer Storage for additional bytes read by the implementation from
    the stream. This is both an input and an output parameter; on entry, the
    parser will be presented with any remaining data in the dynamic buffer's
    readable bytes sequence first. The type must meet the <em>DynamicBuffer</em>
    requirements.

    @param msg The container in which to store the message contents. This
    message container should not have previous contents, otherwise the behavior
    is undefined. The type must be meet the <em>MoveAssignable</em> and
    <em>MoveConstructible</em> requirements.

    @return The number of bytes transferred from the stream.

    @throws system_error Thrown on failure.

    @note The function returns the total number of bytes transferred from the
    stream. This may be zero for the case where there is sufficient pre-existing
    message data in the dynamic buffer. The implementation will call
    @ref basic_parser::eager with the value `true` on the parser passed in.
*/
template<
    class SyncReadStream,
    class DynamicBuffer,
    bool isRequest, class Body, class Allocator>
std::size_t
read(
    SyncReadStream& stream,
    DynamicBuffer& buffer,
    message<isRequest, Body, basic_fields<Allocator>>& msg);

/** Read a complete message from a stream.

    This function is used to read a complete message from a stream into an
    instance of @ref message. The call will block until one of the following
    conditions is true:

    @li The entire message is read in.

    @li An error occurs.

    This operation is implemented in terms of one or more calls to the stream's
    `read_some` function. The implementation may read additional bytes from
    the stream that lie past the end of the message being read. These additional
    bytes are stored in the dynamic buffer, which must be preserved for
    subsequent reads.

    If the end of file error is received while reading from the stream, then
    the error returned from this function will be:

    @li @ref error::end_of_stream if no bytes were parsed, or

    @li @ref error::partial_message if any bytes were parsed but the
        message was incomplete, otherwise:

    @li A successful result. The next attempt to read will return
        @ref error::end_of_stream

    @param stream The stream from which the data is to be read. The type must
    meet the <em>SyncReadStream</em> requirements.

    @param buffer Storage for additional bytes read by the implementation from
    the stream. This is both an input and an output parameter; on entry, the
    parser will be presented with any remaining data in the dynamic buffer's
    readable bytes sequence first. The type must meet the <em>DynamicBuffer</em>
    requirements.

    @param msg The container in which to store the message contents. This
    message container should not have previous contents, otherwise the behavior
    is undefined. The type must be meet the <em>MoveAssignable</em> and
    <em>MoveConstructible</em> requirements.

    @param ec Set to the error, if any occurred.

    @return The number of bytes transferred from the stream.

    @note The function returns the total number of bytes transferred from the
    stream. This may be zero for the case where there is sufficient pre-existing
    message data in the dynamic buffer. The implementation will call
    @ref basic_parser::eager with the value `true` on the parser passed in.
*/
template<
    class SyncReadStream,
    class DynamicBuffer,
    bool isRequest, class Body, class Allocator>
std::size_t
read(
    SyncReadStream& stream,
    DynamicBuffer& buffer,
    message<isRequest, Body, basic_fields<Allocator>>& msg,
    error_code& ec);

/** Read a complete message asynchronously from a stream.

    This function is used to asynchronously read a complete message from a
    stream into an instance of @ref message. The function call always returns
    immediately. The asynchronous operation will continue until one of the
    following conditions is true:

    @li The entire message is read in.

    @li An error occurs.

    This operation is implemented in terms of zero or more calls to the
    next layer's `async_read_some` function, and is known as a <em>composed
    operation</em>. The program must ensure that the stream performs no other
    reads until this operation completes. The implementation may read additional
    bytes from the stream that lie past the end of the message being read.
    These additional bytes are stored in the dynamic buffer, which must be
    preserved for subsequent reads.

    If the end of file error is received while reading from the stream, then
    the error returned from this function will be:

    @li @ref error::end_of_stream if no bytes were parsed, or

    @li @ref error::partial_message if any bytes were parsed but the
        message was incomplete, otherwise:

    @li A successful result. The next attempt to read will return
        @ref error::end_of_stream

    @param stream The stream from which the data is to be read. The type
    must meet the <em>AsyncReadStream</em> requirements.

    @param buffer Storage for additional bytes read by the implementation from
    the stream. This is both an input and an output parameter; on entry, the
    parser will be presented with any remaining data in the dynamic buffer's
    readable bytes sequence first. The type must meet the <em>DynamicBuffer</em>
    requirements. The object must remain valid at least until the handler
    is called; ownership is not transferred.

    @param msg The container in which to store the message contents. This
    message container should not have previous contents, otherwise the behavior
    is undefined. The type must be meet the <em>MoveAssignable</em> and
    <em>MoveConstructible</em> requirements. The object must remain valid
    at least until the handler is called; ownership is not transferred.

    @param handler The completion handler to invoke when the operation
    completes. The implementation takes ownership of the handler by
    performing a decay-copy. The equivalent function signature of
    the handler must be:
    @code
    void handler(
        error_code const& error,        // result of operation
        std::size_t bytes_transferred   // the total number of bytes transferred from the stream
    );
    @endcode
    Regardless of whether the asynchronous operation completes
    immediately or not, the handler will not be invoked from within
    this function. Invocation of the handler will be performed in a
    manner equivalent to using `net::post`.

    @note The completion handler will receive as a parameter the total number
    of bytes transferred from the stream. This may be zero for the case where
    there is sufficient pre-existing message data in the dynamic buffer. The
    implementation will call @ref basic_parser::eager with the value `true`
    on the parser passed in.
*/
template<
    class AsyncReadStream,
    class DynamicBuffer,
    bool isRequest, class Body, class Allocator,
    BOOST_BEAST_ASYNC_TPARAM2 ReadHandler =
        net::default_completion_token_t<
            executor_type<AsyncReadStream>>>
BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
async_read(
    AsyncReadStream& stream,
    DynamicBuffer& buffer,
    message<isRequest, Body, basic_fields<Allocator>>& msg,
    ReadHandler&& handler =
        net::default_completion_token_t<
            executor_type<AsyncReadStream>>{});

} // http
} // beast
} // boost

#include <boost/beast/http/impl/read.hpp>

#endif

/* read.hpp
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
*/