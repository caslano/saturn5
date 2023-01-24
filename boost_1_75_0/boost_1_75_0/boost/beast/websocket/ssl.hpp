//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_SSL_HPP
#define BOOST_BEAST_WEBSOCKET_SSL_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/websocket/teardown.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>

namespace boost {
namespace beast {

/** Tear down a `net::ssl::stream`.

    This tears down a connection. The implementation will call
    the overload of this function based on the `Stream` parameter
    used to consruct the socket. When `Stream` is a user defined
    type, and not a `net::ip::tcp::socket` or any
    `net::ssl::stream`, callers are responsible for
    providing a suitable overload of this function.

    @param role The role of the local endpoint

    @param stream The stream to tear down.

    @param ec Set to the error if any occurred.
*/
template<class SyncStream>
void
teardown(
    role_type role,
    net::ssl::stream<SyncStream>& stream,
    error_code& ec);

/** Start tearing down a `net::ssl::stream`.

    This begins tearing down a connection asynchronously.
    The implementation will call the overload of this function
    based on the `Stream` parameter used to consruct the socket.
    When `Stream` is a user defined type, and not a
    `net::ip::tcp::socket` or any `net::ssl::stream`,
    callers are responsible for providing a suitable overload
    of this function.

    @param role The role of the local endpoint

    @param stream The stream to tear down.

    @param handler The completion handler to invoke when the operation
    completes. The implementation takes ownership of the handler by
    performing a decay-copy. The equivalent function signature of
    the handler must be:
    @code
    void handler(
        error_code const& error // result of operation
    );
    @endcode
    Regardless of whether the asynchronous operation completes
    immediately or not, the handler will not be invoked from within
    this function. Invocation of the handler will be performed in a
    manner equivalent to using `net::post`.

*/
template<class AsyncStream, class TeardownHandler>
void
async_teardown(
    role_type role,
    net::ssl::stream<AsyncStream>& stream,
    TeardownHandler&& handler);

} // beast
} // boost

#include <boost/beast/websocket/impl/ssl.hpp>

#endif

/* ssl.hpp
m4gi1uJlt0pXJ7f8ruvwzvJ3/XHurq6U5jjXudVBVydv6NbUAvma9AJ2Ets83Wo9NS1mdFGOd4zrkNt9JvwO3L6TJfwN5K2JQnfQBglB/06IvzO8AeHaCWW7Dm9EQ/r8RobcVk2Au9MOEFGCwQKoQjaSKiQW01QhG7GOwO2NkkvekQ+cngYTFyEOVpBkSEOPYCAGlyemkWw5MEWRHOU3oFTnRptaCLK3itfwO9LBsmH8GjxaBqSIBBseOzlTUx3l3+DkDsAbXQfMKq/2x7If7DLnYpTPgIxWOYxgcaWxjh6U8N4HCp8Hs3Zj2BtHxUXcbiRN8skM7iBHmZccI3lHsuvWjTYgPzzYXrBvGtYe7JvhWpsCvQj8PYVt676scwNTmxML5NhTCuREU0EwkbU+EL70N7MEwBG2vsHYmuazWZH0vqHEah+uXeh6m7fbu8o2dtUpCLAEdh75hIrJugftEtcQPRN0Q8UpSjqjesraTA5rp/xsk5rtfFSlowvk41E0R33lh5o+RbaarwVAPPQT4BQG4pH8omG3DN9IN+KrHxRqiNuyuY4if6bCLmDPFP60Xa3fQ1IHG2xBEMLHMQg/bhEQftATHNzglSexK7UrrYCAGDVg/JZ8+fdms0++DgXtw1f7AJ6vAB3iwHbVG7xdYX91PvlvoCqQKKzobSzBG/TXoXe823eiF59sdJF/e2OBBtefjYtHJz4p4WCd
*/