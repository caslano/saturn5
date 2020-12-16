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
va9s8OfJVEbJ4pr5FaHjhT83fr/u6UFY2drb9xe3Uy237wBkR36K6Y+jOkfA3pzDMiDmHB2095YN8buKNwUfORo3fNucqyBH2QnGHJtsC8cnXAfcvitJf+vPvuOa9lLYO3zsMbOTEvDWAkFy3Hfb3r6yNc9slpouWbi4oiL0nVb+j2/xe0VgnTrpMkZt9xhkOuW0rV4XGmvDzTevnEbF0VB/s6vK+XXvvesQvcIdbPqQGHHXIfV9yIC4PqTJZ6Ip/7xAudr0AnbsN3XWmihqq4cg1xLpiP0b5cHczIn664nGfx+nu7Vh9+LISdjXlpvruTZfJc1oU4n6xOOUnw1dtIcu0kZSV4TU56d6QYle644dP3rkhCnFJeMmjz6RfqWand61pip9gplLYOpLeVH4PF/fWVlTZd9T7fXQ34rzGq7bvObscp3CwkBe0Ye8oo/OHWb7V3TQuRGNx0xtmRR1bVwmXyP8hl2WCWNE5v7xt7umdfanm92tcbrXE3jzLtOtXFRp+saEdaHweeZeKjTXXf/uTw1bH9aP7f+boXtIeds+q9Ccs+kE1rXeEZLP6/C/c9f5XFw9L3EedzbR3nbG5W/abuYvpD0lbe2/RFv7wkXG/vDZgrJ3xq29/pGsU1etrr7l4qSt/b60tdf6c+Z7a3HEvEOY52wt/xt7Ud//7X3/t/b9nyHbfKrHiep/12Y+S/9jQ6i1MvWtV9+Oi+PWUpslW8bZ8FJYBr1w5vsozIwPJxtVRzaqrWSj6oWrVbj0kHBZCheFaTDmC1e3i3B/ly3u5zAN/sO3Vttaheseshf93bLZ3ABzZbvdWW4v3c0J0+Wc9M2Qvq18+m5TuFYh4dopXDbMgO194XYqXFpIuPeVzw9gqmymvXBOj8R6OsRvID1TfOllJwon22vTFlWun/rSK+yRuP4LlV5P1X8vpTcPGaRwjyhcFpyhcN1kk9tDtvv7wyrYB14OD5ANeD9YJ/f1sFC2rz3h/Tqv+tc3FvrmkPp/R/nbAVvJZj0G3/WFH6TwWSHhf6/w21Q+f4Ct4eu+8CN2Ef4phX9a4X+r8Jt94YsLE7ffO9V+74KyTaf94vaFr91F+i8r/VeU/qtKf6svfJ3Cx0LCv6nwf4QZmpMThW/5bPTXKvyoEBv9B6T/T9XPPAgHaQ7EYM15GKa5EIdrLsTROi/9qPTE+XtO+m1R/p5X/l7w6Zet8KND9HtM+j3uzamQfr+Ufk9Kv03wCM2pGKHzds1JxX+wiT+45mSu4u8I82Ae7AY7aS5UZ8VTiGxQPIcqnogJz2GGk7z7S2N/YFHI/XWx7q9LYSe5u8o9BF4OT4JXwBlyl8ArYZnOz5fbS69O6VWEpLdK6V0DO8ndVe4hmgN0kub+TJfbDXsdLNX5OcbtlafGfeDAkPJcrXq6UffDN2FvzQ3q57oVTzEyU/GMUDyt4ChvvrfqZQ3sojlE+8PvqP7Xqd6/a+odt+JdYcc5GF9RvG3hUsV7nPQbp3o+AfaA49VuJqjfQ8wcC8SUxxSV/ynwTHiq+sUZmqt0GvwWPB2uhSXS53ZHYwnweOmTA2+SPoN1fxwCTTnq/jhU+R8K22uOSEd4mMrjK7C75oz0hEeofIarnI+EB2rOyMHwaM15GKG5PyPhsfAYzf3h/4Y5ZtJ3TMicokrpdZbaUxXMh+dIj2rpUQP76vwAuFh6nA0PkftwuY+RP80Z0bgAeQyZM3Ke6u98pbNUczpq1S4uVPy47X1bp/jykNq4+/Yo//3dTH+bm+lvZxP+RqXVzwEZfiZzI85MzgFJNAdkxyHpyXkgyXkg/1HzQJZyv65GHkK2I9kLmceFzERqkZuQx5HtSGwRc0OQ8Ug=
*/