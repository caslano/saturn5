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
O/yB7Kd/KPvpzXAMfB6Og+iM/Xm9nv3gTthfdogD4SfwIJiDjgfDXDgEdoZDYQE8DBbKPr43HAmPlX38aIjUTofHwXnwJHgp/Cq8Unbz35Pd/HqYCu+BafA+mA43wlbwNZgJX4fc6rVplOPHMANOlN5jEcZe9tr8hEpHYx2wPGRPwkI3fdgTZsNecAzcT/dTbzgB7i/78z7wNNgPzoQHqJ6LdH/gtva0dUq3b4g97YHKx0CYCg+BuXCI8nGo8jEUdofDYB94hOI397zi72jiD5ZTF8XfFcZgPmwLu6v/6GbSw6347O9d/X4nPvJi5hmY42jZ5R4rfUbBQ+FxcBi8GB4JR8Oj5Z4Cx2v+wIlwDpwAF8CJcDGcDJ+D0+DvFG47nCK9ToafwNNlF10OS+FcWA7nwYthBcRm14RfBRfCH8v9IKx045P7E7k/h9WwDQ2pBvaB7vUBcDGcLncJPAdWwnPhN+H58El4IXxB/rbCZfBtuBzugKUwm/KcBTtA198m7QW48erdt5X9T7CT3RMb2S/DPjZ8/7//z73//l9sYFti/9pS29ft3J+xazKdImQsUomsQNYjm5EPr0natSaP5JE8kkfySB7JI3kkj+SRPJJH8vjvOtKQqn1j/2/OlJWf7U4C2KM5AK59/+0FfDCV7WphJLjeq6P1E9fyPSVu/USrhFlBsRlruzbs15fo21XLvzmFfwtM9C2t5d/GWvptMtE3wtPPcs8/ueakFWe8ubXXo0unjitbPmxNy7+Vhn9zTfTtNvG3ww/MeLvqVfW9E0nx2XyO1/j3STA/xWlyDDW5D9//5z58w+uSY3jJI3kkj+SRPJJH8kgeyeNf7J0HeBZFGoD3L4FAgoQAAUIx9N47IoQiAlKi9KJJgAChxgQ4ENQIKnh6imdDRQUFBQ4VC4oCioiKyimWU+yoWE+xIaKi3rtfvp3s/tk/BOXunnsuvw5vZqfs7JRvZmfnm/n/+/0H9f9nTT4B5//Z+v8Nm7Bu6CHR/+cIl+zMGdnnZU1KL7hVnur/3+TS/++v8wPNdQ/sejo/kP+lW7c1cxLTA7NnTU6fOXvS3BlZrn3dMxOPfV6BW1frVdXJ/lOI9XtwGmxM4B0F92PmQRMr98ueMjc3y7W2XVT9dE29huFJErEPx/6r2DuEBlkxrjCycbfq0Tph6gfrWUcDjo7sB3LtSmuaFTLnCOQctK/tCra0zg3aes8rdI39TUl2nJSX6xyMnyX8XGuY6vSmmfucon6c+J4OVrOWSnyrCO93DkkSvip/Y/ut53K3i71wjf6vX9vu5dTOqQtfO/57y7r0I3LvnqHyTnjV35pNuiZIOnYHE40e7aTZctqPPI+epfiV6G1TH4IS5zqufSlxDgypjrLuFyB5a85XucWOm/zyy0NvOClHn7xJdPTg+FFmurfCIX2eUXqW3kNVxd1eaC/3HomfJRLH5dwHu4lzc7Ay1+wwyUlOmDyJdwRhaoqfqqGWop8+WJ6hAY1+pa3XEGodVzGunxzBV96kPadQ/0vCVjG6GaJrTdhvK9lh82+Ij4mLD110ND6mjGX2srgHN4wnzB7nfjH5W+M4oEJuaFk+dV7PL5H7JvrmnV86l4t7Lblnkt7zEPf83k5nXP6m+FBCkfMu+mG3o5mSWKDLcQvpu1WN/fc7LKS8TXWhV+l1x/4WJhfjnPPCGsZidSiXG53WQj3oFeaa03YrSXuh7XFN2p7oUa8z+hVah1UH+tcvda145QL7nw8au0dHs01ZS34TdO+T8XoWVsq3EbJII/fT528nfoeyFtTo8xNey4gc3UdhXksdWC1ni3Rxn2sgZdzQfZaAltkgCR9vznMcLfZ6VhyptMs=
*/