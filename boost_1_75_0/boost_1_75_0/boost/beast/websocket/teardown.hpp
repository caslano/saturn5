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
DlqqWN4Jfb8Gl2fi2F5roEcjPRT2qJ25k/1fFo/qcdMiB/MapNTO3MT+V4/fAoVjyY5oy0xwoGqC4IZ0BI/RoU43kN+4LUw3IAgNCokG/NZ4HHKjIacxLKfBkNOg5wQW7bSSoNiG8oOm6svgzXUQfZpMr1nNcps8d1ok8fsr+C0HsSHZ5FGLs8Gm2/CeF/HuiXgvDH+vAj/v2yLSClunFRdFvBdHvI+OeB8X8V4a0QZwgyPbrYiSVhklbX6UtKooaYujpK2IkrY6Slp1lLS6KGk7o6Q1RElrjJKmREk7GCWtJUqaFGXdbFHSUqKkpUZJS+NpHM6q3AxvB773OFJieNLPjpS+KShUdVzIaMafHR1AH/aFuy1A/XmM8DrunnAYrcrmdfP6KCtqfagvm4eMTV6nsZ6iKP0ujpI2OkrauChplVHS5kdJq4qStjh8vr6PHHN1lG/qoqTtjJLWECWtMUqaEiXtYJS0FpH2x865Cvf/2Tm3bOF/cs4tjzGcc/+IMZxz82L+7Dk3YVDEOXdFUatzbuqp2jk3+yLtnJt+kXbO3X+Rds7dfdFfe86pE/k5Z5HQIcxB1BY+6Tkn4Lk0F5yB0G/vNe3DBeNcUC4cF9zWS6+njuEUo55CtmDhCDdPHrlfpkjTHUX1yxBpGXpamkhLEyfpyNRWMfDaCedp1/2fwfnmBf8JnNeqVh3O1/IXhPNl+PJn4FwujIDz
*/