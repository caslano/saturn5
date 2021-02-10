//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_ROLE_HPP
#define BOOST_BEAST_ROLE_HPP

#include <boost/beast/core/detail/config.hpp>

namespace boost {
namespace beast {

/** The role of local or remote peer.

    Whether the endpoint is a client or server affects the
    behavior of teardown.
    The teardown behavior also depends on the type of the stream
    being torn down.
    
    The default implementation of teardown for regular
    TCP/IP sockets is as follows:

    @li In the client role, a TCP/IP shutdown is sent after
    reading all remaining data on the connection.

    @li In the server role, a TCP/IP shutdown is sent before
    reading all remaining data on the connection.

    When the next layer type is a `net::ssl::stream`,
    the connection is closed by performing the SSL closing
    handshake corresponding to the role type, client or server.
*/
enum class role_type
{
    /// The stream is operating as a client.
    client,

    /// The stream is operating as a server.
    server
};

} // beast
} // boost

#endif

/* role.hpp
cULRTEHe9IMi4xwxFmqCrBQKFJIuHQYiwrBPx0/4NxOxT7UA/X4w5wRc/R+Al0Cx1597qdqXOndzP/bKAwrDWZ4gnvqeP0ekJT6YqCz8h77OzbbrSMcnteOgEDUByjC2CiRqKjF4L0xOxzdIEFvAoD6sg4FmSRqElbMgb+ODqMlBGcq663QVx7CX+kE340rvJk1WsVRYM537czlCoLi21VlGZJC2SPBkag2tkQGzrrGJKPrUKNUBwe5R+2VxjESLjCtixmpHVRewI+Vk2j7ZIVb4mHQHJSxSa/U5dRGNp0aCZdF9l4SB2l/macdKlz6KH/FCL6Yd1YBTEHotVaj8boJpHGR8dM40NI0NJLZ7Tusoe2+iZIryMImp7EhJJnc6Drl8hBwzqjB8tvK3an+xivLw2pg0g+FQhQ4A1Qane6g3D2OuPEE0ykJYKiuthGWIp8Svr+ko2UWrav2dnS3uUv6rcv9FO2NgQt36+b2iJcgkXbY5MAhFsb4nok5K10CLJCtYqpkZAk1F1m0GZc+p/VNDBp8zMHAC5w5elk6LLqG6wv53SCU9tTkUwrMldYOF65nYEc5ajOWlhdw24QlnqYjTcbK6mW87TJsMj6AG9krRoVWhodMg8akSZAcFsrbEPlBRgDpVg6uLC0uG
*/