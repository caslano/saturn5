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
nk6ZtuZbiZfsMOKWvEgn31/pcr3DPnJ3+cs9Rxj+TUeC7LfKBD+nkD69ThoZ74J+I2XwVuVk+gCuPyn3rjYMxhvr8xyfIb4E+Jnt9BKkbj98xlIDGPr0gFykxhaRZhnDJo69V5C6rHa475HxUzE6I5oJ8jW9LSfDg19VRtANxW7ns0bU7RSlRa9oTa/gTRwZzv0KnSSLAyv4vGsjI3Fixuj24howPa8kZvfvxOnnGE4E46raYTKaR50MZqVvV+zLP919qZwoo9DCDneNeRjCeeVsP7QG3CR43sqUZp3wyRDgzkBCTwV94u4Ajr0PXmL3d/V4f162t2IqZD40ZEu6qZuIK5nyv9i1jFpcLcZI0K82miwO6il2CXJr1vNYdViUuvzHb7uKVo9QmGJ32Tp2U/w3jb33la08tt2lZ1uiZnPXtJILbCSjX3mDPNpvnsTVAVVd9teXzSfv8aB9uA1388HyS127fdPa47sJrinZzpbr6sJ+Px33Wd2bkJNWO1tkca/8voqvC6Xp8bKLEa4EcdmHgBekly8eNzlzs4mZVdTQ6fHXq7FCEpqvPm8hZ6qcn3hp95Gv7r3p7a6uXd6ft6rF7y3rav9IwNi2HucJzA/Fz00l7sXKQQ3R+ynLwk5djluIu+9zVKXp19oP1IaC3kE7YLje/6nQlmf25j3R8Q6zqS5u/4L1wWKrqZ6nKaOv5jmNAZD30Vaef/Pe
*/