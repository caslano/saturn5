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
au0HftjzjDRzkvGsaQb8LnSRsvyMspEVcSHpfhO5hrW5X0f6RDSV8ivX5Q43k3jRE+is9zBLXWu0Mdww67u+CitlX/ajoO/1NZUe2cPCDvd3k14gZ729LWTqPVxzHQFmxvN3Z+ofwt/qfBrnv4zHLXJ3csPfhKWwxs0t6tpGt7LzCkuzy0vUBz1OPQlSTsYHafenBmn3I7cHrz+MjamjDdJC5HWuUb3dryydVsoPVb6u/oh+m6DPNBNd/sGeYaa6/OtZy2FCA/Ul4Pc0y/t7qu7Duu3Bf/9myv53A6Qd6Ya8wx81h+7D5DHZo6fPyJ5dUnqBU5/k20XnPqDvbUfedKX77WMC14HaofyPkfsk4f3akQ6N/j1TcXLuC9eVbwe97ciuOPlG11RppoSrNFMAgqVZfru86XbakXYqzDpzAvYjqKeTkRLWlrkSyr0Ru+2C3ouJjn+S0UXuXZJyP2lOM6inJqtdIotZS/86KN9HcZQXl2b71obpJG3HhSpcqtmK1N5Kif4YiTVbyHe3Umflt8y6v1tTFdXaeTMbuR6R//0e773fqswt3+Ercz396t74lvLbJfUuE6kl7NQ3/O+/+jQzoO4lqPsq+lhJM+w1u5ROcZ7oEESjU5ppiE5BEDvyLWZ/W+dUr07Q54bW8HylE9vguizauux8Qydp8HwvKXH2fi/Z377X89W1Gftt67dXsdxrNZ9EnhNGWr+ZAfd6zoL8fP0z2p+VfoqUaTt8gqu+NriGqKYd88Y3p5V8Kyhloz1ykrWnWEB8WcvF8LyXNNiGevaik4/KHpb7shp5lTjF7/S/zoL8MnJZd1+6KP3b5L7Y4ROc9QS3pSpRv4sjk63fyMN/jrTyeYqyL79n8v3ibjLgAfW9YHnKsm8vPfXWs67oc8bK+IGxH+m/X5yqvs974M5VYy6Livx51OzBD87/YHAuY6Tqe74Du/4Wc8vFl1aNe/O73MKzu9eqOcOcH/Z9r57Tv1t61ZpxZyXvib6WweWJ6rvDPZWpt/XdOP/ApV/f+8Rv7+38EHZM63zptuIrv63r+eJrvxvdIf3DIX8l/V2s83evu/XZVzefv/+ihA2Jx8Z8P7nx3xdqvnfUfNeo/+7w1nR1f6bMTvlwxr702NIOtZccv594MsTG+btOfz6qxZU/Pdxl/Y4uvVZOGK77rlH3Hafuu0b996blKh8vv/+21z9+ISPj0hd+vaRw+X179N99tp1nnX9tY8Sn+dEtUzb0KCssHNqmSv/96DyVL3WjTumwsNd1lc8kD7sutvbnz+gL6mudf/Wi1148+O31+y64tnPbRyqZ72Zcrc6nPLu08kDXGU9ftWTCuiuf/NMW3Xei+u9NDyo7s5686N74HUn3T/jt7nOK9s+4s/Hf0VrzgKWOq/6J/aSHSxqd5W9r7D1J/h5g+L4TLXD6WlT/lPJrBmeKHaKt5hV8BzPEPUDcw+EPcDz8CZ4BD8Ab4EH4MDRN3zySCFPmSVki72395XrueVK3EC4J3gbbw9vl+nfAnnAllHjLuyrngsSb4q7G51fB0fA+eCq8H54OV8NZ8AE4Dz4IS+Af4VL4EKyEfzLseMv7HBwUJN5D0GsHT4Cd4IkS36EwU9zyfYy8o6h3Nex4v48ZLuFHwN5wHJwMJ0i8p8Kz4akwB06DRfDXEt/p8DpYBVfCGXA1PAuuU/fHN291FnwOZsMPYQ78HObCLyT8v2AhNE3iB1vAhTAFLoID4GI4FF4IT4MXwTPhUrgY/gYuhRfD2+ElcKXps/8wPA8+Bovgk7AYvgDnw09gCfxU9H+AV8KICOoe7AqvgRlwOTwBXgeHQ0t/CrweThf3bHE736fKc38byU/392k=
*/