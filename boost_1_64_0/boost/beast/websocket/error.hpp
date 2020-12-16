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
8ysfZVHdUr41C1felKeO6wvlvg/J9WmMhKOUyxDN++sDk/eZuLxr2Hyr2sNXSFMfgrs0gY8itxfyz6luH52qiPCUTDns1/1mDEdX9/U0+8w2N1UZXpO5rvuuBds8x7PvmtxDzmWb/WdJN55XqJz/5eoX9hb1C2s3+TcTCiYFiT4otv5h0Z0bsvvLAeR1RMum6QxytbmqxoZ17HNKYLT65/xCdEaEJrC6fDarvxFaxi+sfPoW17mSX2Rf/xJ1uZZ3kcMCfzcvCIGi+yvr3dzzESTKlQuxHqd7mJr+GpO+wrVYKWk+KvyPhHmU+W2vlHQKj6t/O7yQWt3Hb6OOWY3KC2k9LcHmVUwyGzZGLN8ym/1CJd7bxPfE9uHIJv1h9m/+6KypWVMzMsLh0VruhH4sv/VBZdc5puEa3yL3Kceq85OW313eVvV1eE77+7Pa3/Onx5dXBzX/Pq/6T7J/V9jPHiaf54neamsOLWa48tLvl3NLrYGcm4DMR9zjwl+Zr3TGDnZ/PFfSej9jT26Xx5LUnocnb8/Daxvs82M397/ia/3XPvr4imvvaH38rJmpPQ8ve4P2PHzVMt8Uk/GnjPh/5u9c/dvmwOh+ePrMKM+hCfvhPaPfdX4WHKbvkUfre+TJ4EFwqn4Xew74ArhE3y9foO+XG/X98uX6fvmd4BHwKn3PvF2/p/2AhPW9r/P8p8+O5Eu+Dz0DtI8R+r52tPIq8sAzwHzlTVysvImx+p5/HHiT8lDeo9c/oDyTe8BCfR8/CXwanAy+CE4BjyjP5C/gdPB18HSwR4j8gH3AmXY64Czw4xr+FDgHfBCcC34OPAv8Gng2uA8sBv/N3pnAV1HccXxfLkLeA0II4QohIEIQREQEq6igIKCIKYeAoiGQcEiEmAQVRQ14oYjG1iq2KrRS60Er2tZqPYrVtmirRcUbW6rYWqWK1qvW2n538tvJ7ss+kgDS6+3n8883szvHf46d3Tf7n5ln4FS4FY6CH8OJ8As4CRbQVibDwXAKPBa6/sfB0fA0OAYuguNhm1TzDiH7FP320u+f4jj7lBUO/mVHdBC8ChbLjmgiXK3v6XVwnuyfFsneqcaNE54Hr4eXwRvg1Qqn9PmdlTj9byn9W5T+GqW/VunfpfRvVfrrlP53lf5tSv8OpX+n0iec7Fb0O0m/S4rj7FbuxksOvEd2VvfKjuuHcBjcCI+EP4YT4H1aB/In8BT4AJwJH4IV8BHp9TO4VOGlB79tEuvxmPT4hfT4pfT4lfTYIj2ekB5PSo9fS4+npMdm6fGs9HhOehDe1sdG6fHNkPr4i+73d3W/v6f7fafW63wfHgU/g+Nk9zJFdi+l8CPd1x/DZfBTuEr+Zceg3wvUC1IcZ8dwiuwMZuj+Pg0Olj3DENkvfAXOlD1YKTxV54mf90y9o4M1ij9XY2uO7HEc2eNkwH/CtjBC+DyYBgtkX9NHdk0DYQwOhW3gUbCt7LDaQWNXJ33aw9Nl9zRHdk8L4+yeLpF909dgJ3gL7Cz9KS+9p5t72Oifb+xr6o+hsgscBnPh4aqnI9ROhqsfLodHQ3Q1evK/sb8aAavhSLgCHqv+d4rWTZ0Ob5Pd5N2QPBn7kanwATgKvgxHw1eVzh/gOPg2xNbL9IcnQMrMXM+BE2AXOBEOgCVwMCyD44w/z55T7956Jy+Os+fsq/wXKd8HqH32V/sfoP7hIMW3ydG7Kvyd4suDDym+eep/Fuj+qzDxaf9NWKnn3Fm6H6vgSNmTzoZnw3J4CTwDViv9JVpX9zx4hdaP/QZcCm+FF8q+6iJ4n9aP/ZnsU5+Cy+EWeDF8WfFv1zqruQuwpUH8661+yv+dT8lMrruaXHc1ue4=
*/