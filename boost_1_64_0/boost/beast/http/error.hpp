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
3PwyNZxbUJw7Oxt9FlFREwKOcC1Aa8y+dxodwPbaTzK2Hilpi7DXBIp1xqqJiSyz5olNaGPX9nWqNNeJ914Hu4d3nX2wwPzl+3uD94s2vt/1lkLrfP9Vf6yceP0FX+1q32Xa7X+7+DR9f+/aCdb5pxct+fSB62ac3PWLhRO/r5zWRtePquuX1vUb6/qftf2x0o8q5UTydbXh7We7P9LXP7kaRsAHoB0uvp5wayTcQxLuYTgQZV1f26bg3xMclW8JNN8RhPQNwZF+N6D/ZqD+vqaZ43HTTxTVLNxXFD7CR/gIH+EjfISP8BE+wseRHlHIov/0+3+m9fZ/5O/+PV3v/t007+S1MfW++4e8Zq99nUrNdepi/N/9D+86h/vuH/yd+r/XJ/Cm6hMoWTDFePCdUQtfT7p15s3vvrlL1yege2c/en0C9b/7SzmRfK3xe4d/XN7hN8g7/BPQDldXT7inJNzTEu6Z8Lt/o9/9M3jvnxF+9w8f4SN8hI/wET7CR/gIH+HjqBxRyLz/wPv/0RjvT7G/6U+0vt13vc4bhuOX4/FT37s7fjUeP/XNuuOX2sZj0+NX4e+Xeciv1t9vyCG/rCSPX/kCl81qx0920nL5GW3dft405Hj8vGmoET+x6U1fstvPm4YKf78hrvR5/LxpyGonfnZ3hzt9bj9vGvjD7edNQ474iU1v+jx+3jSktnf7edNQ4fHzpqG2vTuP5s4udqevgzvtXr9q5Sc2/fyMjm6bS8rL3OlTfhLOz6/GE262x2ZqJ3dcvH4Vyk9s+vnVdnLbXLwgt9SVvs5um16/auUnNsWvk/gZqf42s0tz8w7554i/2A3wrxF/sS3+rrSmeerpbE9dTHPb9vrVprnt4ifrenxI/9ygBvYArDGD9ROG1mdn275dY3ub17ZkbuNs79fYrg1im4oRkm1n/6ummr3agtoGIfZl2nFfH9w+SsHsD2mU7fhozT5tgbap+I2Ld5HGdqrXtvzQNM72Jo3tjEDbcxtbVrrFaNaYCbRd0th4V2hsTw1ie04jbe/S2M7xsy2NTki27TI+TLPXXmkQ29IghWTfjvvNGvsVXvvyg9C4+7JPY7vKa5sGsfFt1lTN3nrVAbYb32at0dheG2C78W1WXHNNOx5g+/DarAKN/W0B9hvfZm3U2K4NsN34Nis1TtOWB9hufJu1VGPbiPS33fg2a6fGdnyA7ca3WQNbaNrxANuNb7OqNLYzAmw3vs2q09jOCrB9eG3WpJaatjzSfyyz8e3Kao3tnADbjW9Xolpp2vIA241vV/I0tisCbB9eu1KjsV8VYL/x7UqHeE1bHmC78e3KEo3ttQG2G9+ubNfYrgmw3fh2JaO1ph0PsN34dqVSY7s2wHbj25XdGtt1AbYb366MT9C041H+tg+vXblXYz8+wH5jnoVaKdsFicH30q092NyyjV3XwoH6tZZE31lribjWs4+u6LvXWmpi1LuPrug7ay2Rhvr30T2o9GUfXQlvr7V0XpB98+KN//19dMcSR9lH15OHB5IMdUyJ4JsdmAmtPEz9yslDfhMazkOf/kDlPg33dOVOjNDkoehnOnl4qnIfExE0D0XfvbbkFOWuMn1u05j0jeVO0ebpRKXfJULyVOwdq/SLVZ6STNd6cvPwByo+JeJPgp08n6n84yNce7MtMlx7s5Uo/1FmE2OIimMy5/7+dXPZo9PSkThLuUwWt13OHlC1sDx3ruz9lQEnUL5aS/n6xFW2diOf2n/L+c+Qz5E9yBfIXuRLpG8KbUCCrwzmGEGP0VyDfuATW2epMmSqMlUdpDyuDlIe1wYpjxuC7AuWAR9QeqTRb728brLf2/oIwglTuHbVHm+ZLF8=
*/