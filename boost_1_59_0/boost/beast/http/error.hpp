//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_ERROR_HPP
#define BOOST_BEAST_HTTP_ERROR_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/error.hpp>

namespace boost {
namespace beast {
namespace http {

/// Error codes returned from HTTP algorithms and operations.
enum class error
{
    /** The end of the stream was reached.

        This error is returned when attempting to read HTTP data,
        and the stream returns the error `net::error::eof`
        before any octets corresponding to a new HTTP message have
        been received.
    */
    end_of_stream = 1,

    /** The incoming message is incomplete.

        This happens when the end of stream is reached during
        parsing and some octets have been received, but not the
        entire message.
    */
    partial_message,

    /** Additional buffers are required.

        This error is returned during parsing when additional
        octets are needed. The caller should append more data
        to the existing buffer and retry the parse operaetion.
    */
    need_more,

    /** An unexpected body was encountered during parsing.

        This error is returned when attempting to parse body
        octets into a message container which has the
        @ref empty_body body type.

        @see empty_body
    */
    unexpected_body,

    /** Additional buffers are required.

        This error is returned under the following conditions:

        @li During serialization when using @ref buffer_body.
        The caller should update the body to point to a new
        buffer or indicate that there are no more octets in
        the body.

        @li During parsing when using @ref buffer_body.
        The caller should update the body to point to a new
        storage area to receive additional body octets.
    */
    need_buffer,

    /** The end of a chunk was reached
    */
    end_of_chunk,

    /** Buffer maximum exceeded.

        This error is returned when reading HTTP content
        into a dynamic buffer, and the operation would
        exceed the maximum size of the buffer.
    */
    buffer_overflow,

    /** Header limit exceeded.

        The parser detected an incoming message header which
        exceeded a configured limit.
    */
    header_limit,

    /** Body limit exceeded.

        The parser detected an incoming message body which
        exceeded a configured limit.
    */
    body_limit,

    /** A memory allocation failed.

        When basic_fields throws std::bad_alloc, it is
        converted into this error by @ref parser.
    */
    bad_alloc,

    //
    // (parser errors)
    //

    /// The line ending was malformed
    bad_line_ending,

    /// The method is invalid.
    bad_method,

    /// The request-target is invalid.
    bad_target,

    /// The HTTP-version is invalid.
    bad_version,

    /// The status-code is invalid.
    bad_status,

    /// The reason-phrase is invalid.
    bad_reason,

    /// The field name is invalid.
    bad_field,

    /// The field value is invalid.
    bad_value,

    /// The Content-Length is invalid.
    bad_content_length,

    /// The Transfer-Encoding is invalid.
    bad_transfer_encoding,

    /// The chunk syntax is invalid.
    bad_chunk,

    /// The chunk extension is invalid.
    bad_chunk_extension,

    /// An obs-fold exceeded an internal limit.
    bad_obs_fold,

    /** The parser is stale.

        This happens when attempting to re-use a parser that has
        already completed parsing a message. Programs must construct
        a new parser for each message. This can be easily done by
        storing the parser in an boost or std::optional container.
    */
    stale_parser,

    /** The message body is shorter than expected.

        This error is returned by @ref file_body when an unexpected
        unexpected end-of-file condition is encountered while trying
        to read from the file.
    */
    short_read
};

} // http
} // beast
} // boost

#include <boost/beast/http/impl/error.hpp>
#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/http/impl/error.ipp>
#endif

#endif

/* error.hpp
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
*/