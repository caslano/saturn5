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