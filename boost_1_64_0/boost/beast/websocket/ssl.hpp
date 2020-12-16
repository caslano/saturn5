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
3KRc4xVzZWtyhsYHztQ4SqVs1argGFgtW6ca2fYs9o2PVCrd50PGR3I1PtIR9pGNWBEcLFuTTrKl6ap4C2A57AXPlu3kCtlM3qjxlru1rukv4MHwScWnfcD1zNS6t3H7gE/VONY0jV9NV/5OgXNlk3Q+PE3jRjOVfgm8zrhlm2T7e/PMM+kMrt9P3BzDPFsjpXO46nOybG2OULrDNQ40CU7V9VnwSNXzUXCprl+m69dqvOh22STdpes/1vWNslF6UTZKr+j6dl1/TzZLGRHaHYxB93oedK/3hKPhYfA4eISuj9b1YjgGzoVj4Rm6XqPrF8Fx8Hp4PLxJ12/T9XvgCXATHA+f1vWXdP0NeCL8DE6ATkr99SzoXu8IT4IDYDEcrOvDdX08nAgnyL1Z41sa29rrY1pbKr+8ca2tZyUe29pRtWfjW1uqdz3GNaJmz8e5Riz+/xzr2t29jPfmeFf9/sV7b7xr7Xl7d8yrueNdNYux30E2ITuQ3LOTY17JI3kkj+SRPJJH8kgeySN5JI/kkTz++4599/2/vKpqL3z/d/f3X+7u0V3szpv3Po/WVNWvSFlt9gD4QW/mOU+Mu16FdosWuibFxobg5QLHfl+v1LjpsUgb5CjZEOzsUP8NduLEErOpfUNsqERMnj39z4nlMSNNrwPrfZOqjST6VtLybxMt/SYS/m0o8beMPpXu+Y1vzBy/JC16941j+h9wdiviSPBtJdG3j5Z/C2vpN6/wb3OJv6lp3qrqmfBm3m9w3mqV5s0u1rzds2XTeA78iua1HqVvI73J96bLmAN2WWaT47l2LDdgmxgcv92BaNzWP14rm8NQe8PQMdjJvrHX7UjaCDPOyvhq47HV25GG8VQoe8H8kXbslHHTpsdKRyBh46OxYzmvcVDGQANjnhrrDIxxTgvY8IWNZwbGMDV+GRi7DI5XBscpNS6ZeBxyvBl/DB93TDzmSNxjA2OLdlwxdnly/DB5JI/kkTySR/JIHskjefz7jn33+79sycK99PvftV0da37/a4ovUZeeOX+2u9VGL10vDrmu7R5MHEcXkf5HKfwe18WG/YjsPoLTTBy67u0pQyLnagzhJwWOtUFmTj9Hw3zHbsh7GL3tTDNjCO6gAYa1h2Ay5rdB5qxjbZDlN7/B3tpnQ9wefmCud/GvbZ1wPdhMa+Nr0gjYS0+TvfTnKYwRiH/uS+h0o6stEFQO2JgXyFb5JOPvwpTTMY/aRmof8ut3S+Qm5cOL5yDZlkecu1vhxuosGx8N9tGUN5R9tMIMMO6FxDHeuH+Y4qafY/zPN9fy3PmI5tptKVqDWWH7oatnW12J33o77uMUj+v+qvXbB7/eetdz0HN0+5O4VmT1iBgb95nWvS3F1Xu664E9nLz1n8cTZqq5fnNKDtcrTbnWnFlZonpVec02+R9vy2NYhtEpkuVcFSlgnskOt+5TWbON+oqlLCti24H+zDBJa72LtnKiiaOH3FibG3dawrZzvLnezdvvwKQ5L81Ls/Zrbnrp0dbRvibhxOn+xOS3t0331fRdp/sjc70wkO6nNt3lkfp0s6JF7j9Z4emOJUwfU4aHU4a4bZsaYtpUWNq58EjjJ92uhzHIuPOcNpwz62FIn/x01lMsQJ/Y8pN96y4bP97ckJ9yvTSb/LRv4IMFLpu/T1pb+hXjykQPc5+mt+9sdHJ6j58weLCjc3/N8M4d/BXv3BsN5w7zzj3ScO5Q79zIhnMHe+cObDhn1GvLubvSvXNDE+1Ho/kAuk81ByPHnJtv3NMcb35ApXHPtOu3zwmso/2QhjwWIx3E47iXtmUG+hvTu3J3mVXCzXiuSc/e0zxmFqKSbYsKn2fb4uTW5t4=
*/