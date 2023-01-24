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
+kLVF/8Xc+B8C5uYy024KeG0J+yJl5AHgYjh/Cbq7Kel8J/pVRHl473a4BKnFwbhsaJfEZcZA+7HTSGfe+H5WTCrGbzF9sstJqtkwdBUeiC7XExdLqJLKUH8jtMJ4gttdLyuLkUuD6OiUvyyLwD84LF25CiAn57986EEBFltlQlk79lkgCy+s/Foa5C9jF787QPTi5fEvhhq48Xj8a1hvZBgfc1TNsUC6OdZAb3/6QSlhbzIxR1ZZNOMgV9jTBP7DWi7O56gbb/y/9ceuOL+1ntga9zJ90CwC4a77X4agMHq/8X0OBefRnugjenJjzNPj9weEJEHliuSAbIcpyfOEAg8KnoVfvQ4rPDFWaciecFFXZ7MNOgd+CG2VqkgR8nMBVyaTCSRiDzuG/gZrYFNyvvi3C7UOU2yDg8JogWxAAsqt0VduRscc96DkOHizFG1ON7YOgtppPPpAqo42DPom2raKkzu3aqmh/hQmFyn4RzNwvuoc5QNmfkq7oYY8LPMmDDvEDibkcN2HTng+eShVFM1ihmLUZVD9CVYpcLeagO0CEGAKptt/k7w3hDxXuQvsHV7oO+OaXvbmPmRXIvDyrXUGL2ep3DonPYYnDEUxplDholu19rheujbAkdePYh17pxkxxjrHJtJ3ZpDvPHU7p5glit+iyeUZ8+lKFKTf3GrLe7c1Xgz5YYVICjQzpoE4p+GgjH1BUHvJ2K4
*/