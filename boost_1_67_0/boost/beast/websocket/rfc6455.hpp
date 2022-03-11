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