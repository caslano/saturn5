//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_IMPL_SSL_HPP
#define BOOST_BEAST_WEBSOCKET_IMPL_SSL_HPP

#include <utility>

namespace boost {
namespace beast {

/*

    See
    http://stackoverflow.com/questions/32046034/what-is-the-proper-way-to-securely-disconnect-an-asio-ssl-socket/32054476#32054476

    Behavior of ssl::stream regarding close_notify

    If the remote host calls async_shutdown then the
    local host's async_read will complete with eof.

    If both hosts call async_shutdown then the calls
    to async_shutdown will complete with eof.

*/

template<class AsyncStream>
void
teardown(
    role_type,
    net::ssl::stream<AsyncStream>& stream,
    error_code& ec)
{
    stream.shutdown(ec);
}

template<
    class AsyncStream,
    class TeardownHandler>
void
async_teardown(
    role_type,
    net::ssl::stream<AsyncStream>& stream,
    TeardownHandler&& handler)
{
    stream.async_shutdown(
        std::forward<TeardownHandler>(handler));
}

} // beast
} // boost

#endif

/* ssl.hpp
nsZzIgEcIU9RD85DnqDrIFGjMuTzKDondM+x8V/AyPuIT2mGYIwcq2qv5UNmoTvuwS+vXv0OP8PLi5cXPlyLUmIOocVyg/rBh2HiZv7IxOPjwOCVD2hB5IOGapVJA0aldic0Ap3nMsbSYALCQIIm1nJDF7IEmyGkMkcYzxd309k7H3aZjDMm2asaTKbqPIFMbBE0xii3B45KaAsqJTiRJ9JYIqytVOWAtBEs6sIwB8uL3CgQWyFzsSEhYSGztjKvgyCudU7RB4mKTRC36Q8yW/yXyR0FUYg9qMqCVVAb9IFX+lCoRKY8UkFosqo3uTSZf4yGpMokUBoM5jlzEU6iOYSNEDbl8XkZVBSxtDwYVRqW2mWq+GIh1ZFZ0lqXJER1oEWJojL7UJcJarfYZd5KNDV1Bf5ma47xJqBKCgY6oxCmYQc2wkjjw+109ed8vYLb0XI5mq3uYP4WRrM7Jns/nV1T6yWJacDHSqMhcQ2yqHKJSaP5/Y7A84I+DK8n4fiK9ac3owXpCpJD9spOlg9AA5eGSpkqXYCAUqmKVw+DFkg8L2QZ53WCMDQ2kWqQXZ1MsTEO7qBplnRVo68AI53Ys0TJLnwvlxvm+sm4eJ0TRCU2MpeW/NA2ZqbIMTYjezpTtwIaP9WS6tqywG+D
*/