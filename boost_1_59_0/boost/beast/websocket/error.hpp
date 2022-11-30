//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_ERROR_HPP
#define BOOST_BEAST_WEBSOCKET_ERROR_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/error.hpp>

namespace boost {
namespace beast {
namespace websocket {

/// Error codes returned from @ref beast::websocket::stream operations.
enum class error
{
    /** The WebSocket stream was gracefully closed at both endpoints
    */
    closed = 1,

/*  The error codes error::failed and error::handshake_failed
    are no longer in use. Please change your code to compare values
    of type error_code against condition::handshake_failed
    and condition::protocol_violation instead.
            
    Apologies for the inconvenience.

    - VFALCO
*/
#if ! BOOST_BEAST_DOXYGEN
    unused1 = 2, // failed
    unused2 = 3, // handshake_failed
#endif

    /** The WebSocket operation caused a dynamic buffer overflow
    */
    buffer_overflow,

    /** The WebSocket stream produced an incomplete deflate block
    */
    partial_deflate_block,

    /** The WebSocket message  exceeded the locally configured limit
    */
    message_too_big,

    //
    // Handshake failure errors
    //
    // These will compare equal to condition::handshake_failed
    //

    /** The WebSocket handshake was not HTTP/1.1

        Error codes with this value will compare equal to @ref condition::handshake_failed
    */
    bad_http_version,

    /** The WebSocket handshake method was not GET

        Error codes with this value will compare equal to @ref condition::handshake_failed
    */
    bad_method,

    /** The WebSocket handshake Host field is missing

        Error codes with this value will compare equal to @ref condition::handshake_failed
    */
    no_host,

    /** The WebSocket handshake Connection field is missing

        Error codes with this value will compare equal to @ref condition::handshake_failed
    */
    no_connection,

    /** The WebSocket handshake Connection field is missing the upgrade token

        Error codes with this value will compare equal to @ref condition::handshake_failed
    */
    no_connection_upgrade,

    /** The WebSocket handshake Upgrade field is missing

        Error codes with this value will compare equal to @ref condition::handshake_failed
    */
    no_upgrade,

    /** The WebSocket handshake Upgrade field is missing the websocket token

        Error codes with this value will compare equal to @ref condition::handshake_failed
    */
    no_upgrade_websocket,

    /** The WebSocket handshake Sec-WebSocket-Key field is missing

        Error codes with this value will compare equal to @ref condition::handshake_failed
    */
    no_sec_key,

    /** The WebSocket handshake Sec-WebSocket-Key field is invalid

        Error codes with this value will compare equal to @ref condition::handshake_failed
    */
    bad_sec_key,

    /** The WebSocket handshake Sec-WebSocket-Version field is missing

        Error codes with this value will compare equal to @ref condition::handshake_failed
    */
    no_sec_version,

    /** The WebSocket handshake Sec-WebSocket-Version field is invalid

        Error codes with this value will compare equal to @ref condition::handshake_failed
    */
    bad_sec_version,

    /** The WebSocket handshake Sec-WebSocket-Accept field is missing

        Error codes with this value will compare equal to @ref condition::handshake_failed
    */
    no_sec_accept,

    /** The WebSocket handshake Sec-WebSocket-Accept field is invalid

        Error codes with this value will compare equal to @ref condition::handshake_failed
    */
    bad_sec_accept,

    /** The WebSocket handshake was declined by the remote peer

        Error codes with this value will compare equal to @ref condition::handshake_failed
    */
    upgrade_declined,

    //
    // Protocol errors
    //
    // These will compare equal to condition::protocol_violation
    //

    /** The WebSocket frame contained an illegal opcode

        Error codes with this value will compare equal to @ref condition::protocol_violation
    */
    bad_opcode,

    /** The WebSocket data frame was unexpected

        Error codes with this value will compare equal to @ref condition::protocol_violation
    */
    bad_data_frame,

    /** The WebSocket continuation frame was unexpected

        Error codes with this value will compare equal to @ref condition::protocol_violation
    */
    bad_continuation,

    /** The WebSocket frame contained illegal reserved bits

        Error codes with this value will compare equal to @ref condition::protocol_violation
    */
    bad_reserved_bits,

    /** The WebSocket control frame was fragmented

        Error codes with this value will compare equal to @ref condition::protocol_violation
    */
    bad_control_fragment,

    /** The WebSocket control frame size was invalid

        Error codes with this value will compare equal to @ref condition::protocol_violation
    */
    bad_control_size,

    /** The WebSocket frame was unmasked

        Error codes with this value will compare equal to @ref condition::protocol_violation
    */
    bad_unmasked_frame,

    /** The WebSocket frame was masked

        Error codes with this value will compare equal to @ref condition::protocol_violation
    */
    bad_masked_frame,

    /** The WebSocket frame size was not canonical

        Error codes with this value will compare equal to @ref condition::protocol_violation
    */
    bad_size,

    /** The WebSocket frame payload was not valid utf8

        Error codes with this value will compare equal to @ref condition::protocol_violation
    */
    bad_frame_payload,

    /** The WebSocket close frame reason code was invalid

        Error codes with this value will compare equal to @ref condition::protocol_violation
    */
    bad_close_code,

    /** The WebSocket close frame payload size was invalid

        Error codes with this value will compare equal to @ref condition::protocol_violation
    */
    bad_close_size,

    /** The WebSocket close frame payload was not valid utf8

        Error codes with this value will compare equal to @ref condition::protocol_violation
    */
    bad_close_payload
};

/// Error conditions corresponding to sets of error codes.
enum class condition
{
    /** The WebSocket handshake failed

        This condition indicates that the WebSocket handshake failed. If
        the corresponding HTTP response indicates the keep-alive behavior,
        then the handshake may be reattempted.
    */
    handshake_failed = 1,

    /** A WebSocket protocol violation occurred

        This condition indicates that the remote peer on the WebSocket
        connection sent data which violated the protocol.
    */
    protocol_violation
 };

} // websocket
} // beast
} // boost

#include <boost/beast/websocket/impl/error.hpp>
#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/websocket/impl/error.ipp>
#endif

#endif

/* error.hpp
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
*/