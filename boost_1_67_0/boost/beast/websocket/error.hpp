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