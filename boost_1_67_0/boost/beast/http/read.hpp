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