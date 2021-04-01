//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_ROLE_HPP
#define BOOST_BEAST_ROLE_HPP

#include <boost/beast/core/detail/config.hpp>

namespace boost {
namespace beast {

/** The role of local or remote peer.

    Whether the endpoint is a client or server affects the
    behavior of teardown.
    The teardown behavior also depends on the type of the stream
    being torn down.
    
    The default implementation of teardown for regular
    TCP/IP sockets is as follows:

    @li In the client role, a TCP/IP shutdown is sent after
    reading all remaining data on the connection.

    @li In the server role, a TCP/IP shutdown is sent before
    reading all remaining data on the connection.

    When the next layer type is a `net::ssl::stream`,
    the connection is closed by performing the SSL closing
    handshake corresponding to the role type, client or server.
*/
enum class role_type
{
    /// The stream is operating as a client.
    client,

    /// The stream is operating as a server.
    server
};

} // beast
} // boost

#endif

/* role.hpp
1NJUHRDIvokh9KrrWRL5VdWJgAd83xFgYZVFdO/IUMYCQPjDEQsmsKQMi6g4FQoO6wG0kL7ej90Y1AoAhE80weU/hNkMUL19a76x7kXZnr0vOLX+6uMp7L/Cyp/uIbpYrDGC+j5ucxxlSCUldcpWzaJHLPdX/UvgZdm4dxkrCZDrLU+X3ibNwcDbzitljA7M+4am0Ziw7ocrqfJjheeElC7vbj108aCrfhNDVAKLogyOqus8Br9TgpxRpDPOZHckuk4JGHv4Yp1sSdDKJ5FwIbalx90JKt7b3xvpSYfPW1Mnfikw2J2CMIo+UKMnnFw3IdWPV+BoRNQKaeX39ZYuPH+8RZKg/Zp70m8OBHTZuggCydjTw+3ZP6HjsjbdLc3jc1SZ1HvWREu/FNLV1CF2knOlEc1iNplGeChkhdWenuvdwB9DA9oVIaTXdsiDPMgIHvPhr1VejSo/ueP+bqLJA/POgZip86sPeYaqyf0deaS/jvrOiZQWCF3+lG+yA9tgobgzSp5wdqJXVW7Jf9GnajpMCf9z0mmv+Ktb/bsOQB9lMCCWZekwUB+4cw==
*/