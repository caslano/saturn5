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
AUYPRtyi/4+NCOXaZGU6mfLVmHsdq4aLQbPxirAujbTPxDb6PdHJhVUotBpgYYdg4ClZS0VMOtE3WGM3Kn2vewv64E1viP9iwmkH+VsTy7E9h+2r9+35wUyIbk9LNKriaKKsBhELyYydPu+PPMWBKCMEUCykP54wRlBP5NqmD0wv5R7xUNGdGuSwgslRfaGhS9PT9/r7RVk8P4htORltLgK0grEdWM4rhnCO/4FYvY1inFriyOpsjx0S0m3p44dOIsKuZYjbZJ+TTleV7UWIBFHEQsdyrI0wNms5pR8HSSZTtAlIXz0x7YFvLBRZYa81Xhl6+6+71tJHQ+WR4QlW8zgj+Kl2RpJMHgIuWNiKcDKC4DrTjpwSIBqiFwPac8niVXNCfDWS1HYTYOnYocR/oH/gd+8x5mBdlSL0cgYyOf9FgN2HylGyK36Q0Gig5BoKeqNgF20wwOTUuxHUh3yCTp8uq0xjdHSmayH1Z1KvxQtH/UPtpE92AYuyPBnPnLqAL/qoNgqGd07+pQ+jdnIkHDm7v3r9IS5oaIEe8XQyBCf8UDf+ueQdF7u+Bw==
*/