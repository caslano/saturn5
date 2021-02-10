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
RWM5E5QK/Nh8JCu5mgd0r1VETdC1SRs7HOdFAM3iM3QP6M36yzoN7+UIPrY7OxJOACoSWNTrHJtOTqiDyxt3s8ew9e3Xm17aoGPqNho+dcJ5dmBz6rDz7+yMvQLJk2NTYdw7rSr1SxmcTUp/RQ1imcAJssFLvn7klwEgTB/rvnYsDlizWHs5yu6uD7NBCv0N1go8PnkbwXJJnQufV7x/c31BTaapo+KL24eYvk7852A2/sm791R24h8zKezjTCXK1T0wJMjiMsHtHWimOfJYg1bBR7jkOP9c+OJWVjkWWVWCVpUzkHSKdRzICQYbboBErGR+Uwtr19pE+bGjLdRWOowJHm/gExxfTWc3k8H1qHc5CKjGbmpFuV+xuupNJl/G17hca1aGqDTblZD81bNWcUxYETxnUCLXmwMP7mxtXSBbYxSmi4U2K6ThXeGeGfzcuxyOBqjrasXJgXP03IliMLsZnpVskqATNxGgVUaGjSidTQYXg/6UVzHrZZguODRPGV6ZL79tXipiYLL4y/jn1lureX2BkqiVSDG+8WPDu8igjcy36zRM8tszFDy1reUPgJJfwgKyOJ4LUNYiS0IeHP1dncoQM53HxeejxeNfmV3Ohb9m1vdDPl8VqK4HvbOz3rTHU+IzV4LOhxcD
*/