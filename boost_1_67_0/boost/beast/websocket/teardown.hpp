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