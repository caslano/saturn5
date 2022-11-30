//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_TEARDOWN_HPP
#define BOOST_BEAST_WEBSOCKET_TEARDOWN_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/role.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <type_traits>

namespace boost {
namespace beast {
namespace websocket {

/** Tear down a connection.

    This tears down a connection. The implementation will call
    the overload of this function based on the `Socket` parameter
    used to consruct the socket. When `Socket` is a user defined
    type, and not a `net::ip::tcp::socket` or any
    `net::ssl::stream`, callers are responsible for
    providing a suitable overload of this function.

    @param role The role of the local endpoint

    @param socket The socket to tear down.

    @param ec Set to the error if any occurred.
*/
template<class Socket>
void
teardown(
    role_type role,
    Socket& socket,
    error_code& ec)
{
    boost::ignore_unused(role, socket, ec);
/*
    If you are trying to use OpenSSL and this goes off, you need to
    add an include for <boost/beast/websocket/ssl.hpp>.

    If you are creating an instance of beast::websocket::stream with your
    own user defined type, you must provide an overload of teardown with
    the corresponding signature (including the role_type).
*/
    static_assert(sizeof(Socket)==-1,
        "Unknown Socket type in teardown.");
}

/** Start tearing down a connection.

    This begins tearing down a connection asynchronously.
    The implementation will call the overload of this function
    based on the `Socket` parameter used to consruct the socket.
    When `Stream` is a user defined type, and not a
    `net::ip::tcp::socket` or any `net::ssl::stream`,
    callers are responsible for providing a suitable overload
    of this function.

    @param role The role of the local endpoint

    @param socket The socket to tear down.

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
template<
    class Socket,
    class TeardownHandler>
void
async_teardown(
    role_type role,
    Socket& socket,
    TeardownHandler&& handler)
{
    boost::ignore_unused(role, socket, handler);
/*
    If you are trying to use OpenSSL and this goes off, you need to
    add an include for <boost/beast/websocket/ssl.hpp>.

    If you are creating an instance of beast::websocket::stream with your
    own user defined type, you must provide an overload of teardown with
    the corresponding signature (including the role_type).
*/
    static_assert(sizeof(Socket)==-1,
        "Unknown Socket type in async_teardown.");
}

} // websocket

//------------------------------------------------------------------------------

namespace websocket {

/** Tear down a `net::ip::tcp::socket`.

    This tears down a connection. The implementation will call
    the overload of this function based on the `Stream` parameter
    used to consruct the socket. When `Stream` is a user defined
    type, and not a `net::ip::tcp::socket` or any
    `net::ssl::stream`, callers are responsible for
    providing a suitable overload of this function.

    @param role The role of the local endpoint

    @param socket The socket to tear down.

    @param ec Set to the error if any occurred.
*/
template<class Protocol, class Executor>
void
teardown(
    role_type role,
    net::basic_stream_socket<
        Protocol, Executor>& socket,
    error_code& ec);

/** Start tearing down a `net::ip::tcp::socket`.

    This begins tearing down a connection asynchronously.
    The implementation will call the overload of this function
    based on the `Stream` parameter used to consruct the socket.
    When `Stream` is a user defined type, and not a
    `net::ip::tcp::socket` or any `net::ssl::stream`,
    callers are responsible for providing a suitable overload
    of this function.

    @param role The role of the local endpoint

    @param socket The socket to tear down.

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
template<
    class Protocol, class Executor,
    class TeardownHandler>
void
async_teardown(
    role_type role,
    net::basic_stream_socket<
        Protocol, Executor>& socket,
    TeardownHandler&& handler);

} // websocket
} // beast
} // boost

#include <boost/beast/websocket/impl/teardown.hpp>

#endif

/* teardown.hpp
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
*/