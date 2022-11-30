//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_RFC6455_HPP
#define BOOST_BEAST_WEBSOCKET_RFC6455_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/static_string.hpp>
#include <boost/beast/core/string.hpp>
#include <boost/beast/http/empty_body.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>
#include <array>
#include <cstdint>

namespace boost {
namespace beast {
namespace websocket {

/// The type of object holding HTTP Upgrade requests
using request_type = http::request<http::empty_body>;

/// The type of object holding HTTP Upgrade responses
using response_type = http::response<http::string_body>;

/** Returns `true` if the specified HTTP request is a WebSocket Upgrade.

    This function returns `true` when the passed HTTP Request
    indicates a WebSocket Upgrade. It does not validate the
    contents of the fields: it just trivially accepts requests
    which could only possibly be a valid or invalid WebSocket
    Upgrade message.

    Callers who wish to manually read HTTP requests in their
    server implementation can use this function to determine if
    the request should be routed to an instance of
    @ref websocket::stream.

    @par Example
    @code
    void handle_connection(net::ip::tcp::socket& sock)
    {
        boost::beast::flat_buffer buffer;
        boost::beast::http::request<boost::beast::http::string_body> req;
        boost::beast::http::read(sock, buffer, req);
        if(boost::beast::websocket::is_upgrade(req))
        {
            boost::beast::websocket::stream<decltype(sock)> ws{std::move(sock)};
            ws.accept(req);
        }
    }
    @endcode

    @param req The HTTP Request object to check.

    @return `true` if the request is a WebSocket Upgrade.
*/
template<class Allocator>
bool
is_upgrade(beast::http::header<true,
    http::basic_fields<Allocator>> const& req);

/** Close status codes.

    These codes accompany close frames.

    @see <a href="https://tools.ietf.org/html/rfc6455#section-7.4.1">RFC 6455 7.4.1 Defined Status Codes</a>
*/
enum close_code : std::uint16_t
{
    /// Normal closure; the connection successfully completed whatever purpose for which it was created.
    normal          = 1000,

    /// The endpoint is going away, either because of a server failure or because the browser is navigating away from the page that opened the connection.
    going_away      = 1001,

    /// The endpoint is terminating the connection due to a protocol error.
    protocol_error  = 1002,

    /// The connection is being terminated because the endpoint received data of a type it cannot accept (for example, a text-only endpoint received binary data).
    unknown_data    = 1003,

    /// The endpoint is terminating the connection because a message was received that contained inconsistent data (e.g., non-UTF-8 data within a text message).
    bad_payload     = 1007,

    /// The endpoint is terminating the connection because it received a message that violates its policy. This is a generic status code, used when codes 1003 and 1009 are not suitable.
    policy_error    = 1008,

    /// The endpoint is terminating the connection because a data frame was received that is too large.
    too_big         = 1009,

    /// The client is terminating the connection because it expected the server to negotiate one or more extension, but the server didn't.
    needs_extension = 1010,

    /// The server is terminating the connection because it encountered an unexpected condition that prevented it from fulfilling the request.
    internal_error  = 1011,

    /// The server is terminating the connection because it is restarting.
    service_restart = 1012,

    /// The server is terminating the connection due to a temporary condition, e.g. it is overloaded and is casting off some of its clients.
    try_again_later = 1013,

    //----
    //
    // The following are illegal on the wire
    //

    /** Used internally to mean "no error"

        This code is reserved and may not be sent.
    */
    none            = 0,

    /** Reserved for future use by the WebSocket standard.

        This code is reserved and may not be sent.
    */
    reserved1       = 1004,

    /** No status code was provided even though one was expected.

        This code is reserved and may not be sent.
    */
    no_status       = 1005,

    /** Connection was closed without receiving a close frame
        
        This code is reserved and may not be sent.
    */
    abnormal        = 1006,

    /** Reserved for future use by the WebSocket standard.
        
        This code is reserved and may not be sent.
    */
    reserved2       = 1014,

    /** Reserved for future use by the WebSocket standard.
       
        This code is reserved and may not be sent.
    */
    reserved3       = 1015

    //
    //----

    //last = 5000 // satisfy warnings
};

/// The type representing the reason string in a close frame.
using reason_string = static_string<123, char>;

/// The type representing the payload of ping and pong messages.
using ping_data = static_string<125, char>;

/** Description of the close reason.

    This object stores the close code (if any) and the optional
    utf-8 encoded implementation defined reason string.
*/
struct close_reason
{
    /// The close code.
    std::uint16_t code = close_code::none;

    /// The optional utf8-encoded reason string.
    reason_string reason;

    /** Default constructor.

        The code will be none. Default constructed objects
        will explicitly convert to bool as `false`.
    */
    close_reason() = default;

    /// Construct from a code.
    close_reason(std::uint16_t code_)
        : code(code_)
    {
    }

    /// Construct from a reason string. code is @ref close_code::normal.
    close_reason(string_view s)
        : code(close_code::normal)
        , reason(s)
    {
    }

    /// Construct from a reason string literal. code is @ref close_code::normal.
    close_reason(char const* s)
        : code(close_code::normal)
        , reason(s)
    {
    }

    /// Construct from a close code and reason string.
    close_reason(close_code code_, string_view s)
        : code(code_)
        , reason(s)
    {
    }

    /// Returns `true` if a code was specified
    operator bool() const
    {
        return code != close_code::none;
    }
};

} // websocket
} // beast
} // boost

#include <boost/beast/websocket/impl/rfc6455.hpp>

#endif

/* rfc6455.hpp
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
*/