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
i29KX5qW35Xtmij5lvA7uspJ1KzOKR7BeLM9RoLQmyz9PSSp9H3Uek0foR/xXEdT36mbxO/Uqd9m/m7qjHuN+m/XunN/iV+vm+weFM/mS1wKvh33RwpdoYVA4zMDKzF70bNeQ6wXz3DtMF7SP2rmGfIF+P8wfcFxL+ztQrdRevxsyZvJvbK6liTxnbUgpIk00qj6hOl+2kSkvEF7Uusva4VtUV6xxE3Xw9U60dSc1MxCg8XUnr49Uqa/0I1Bd5E8vUTnHo9D/Ix8N8q9jaZ3GKnypyKOvvVAw+uA0E2hO28gtgNfiW6+MK0gtSgtiz4Po4GydxiyJQkGIkFQ7vmVfBBY2y8gZBAWvf1D/R2m9Tb1rLNS9jWa8ltQxfp2b7Pu3KJfLbE4N7nUQp++zmOtK4LnM+PdcE+9m/S5Ww+598E/eNAtDrvT13vQd3nQmw9b+zBI4Zp3LeMcP+BnOr53R9x/2b4PG2R8D/t+vF3yHmQ/Zln2/ZjxA1W/fEToQxb9eJB8i50S/wLlryt/vNp7v1bo1nqcFgD99FQtnPLhliPG/e+gIw1Qa9MjjuKe9DukUXQTzU4mrJCyT1MmuJ7dRXg0TdqisKggIzUXWdRzt0iaSPgySTXbmDCvsuuylSvbJN0+S7lyVuIGq7W+9vKOD8LqYAjT8J3wzhFc+9sraXaCt4dqyfjrJXPoF2HVy+6/k4cl31DGw9uLxPurNcVa8pyJiK8t3yrBkAuSZpdZbik59WcpL0KtL77nLE93yakzEr9YC0KacEnjulfCe/byaOhRd3m0XMoepeSRkXiX3NtjKY/ekrjmSh79DbRZHn1tIY8SgddCHo0MxLetjT2ohl2b/4KAkImB4aF+foG1/EIDA/3qw5ytUZDlPmvyVLa8Y10TD3L/Pb9DG4kvxdsNsf+mildmpuaY+lrREa4nG7TKdyf8mA0SeVgdP+HjzHZ0FvJwr4U8PGghD49ZyMOTwDQpj/2I9xOBX1vIySMvu8u54fI+UobQr4E2xwcddadjQVuNbRLo3/55h3NsswZojG0qjlrIxYy8Ksc2fV4x8qU62G9ZzjA7mcj4garvdZX8rRxOGr3smEGP8LYB4Ji4o6S/R9InqfL62sq1NpJ+sYM8yPTdbWVSZ0lf4LCSSbkSt0qNdbRfO21x60H+zdeO4hvW0TJ1i7EO5f85yV+i/HK1F3qu45C2RNnWDpB7OQ6zXAnneGiePO+Y1lJroPyiZEj6RvpCrUSNpwdLG0bR35GLTlHjngLJ09tRmZxZcOyinMnRweOSZ5DbuCde7hU5rORMsvO7KjlTAtosZ85byJneHPek47c7sS7HPQuuq3LcEyftEvaj7PpKLfr5Oot+XmbRz7db9PPewPMW/XnEK+79M/LX7nS0B73Rg97hQWcesx73TOSBSic47nnSwXHPq5b9u3rjHsm7kH2cZdmPexjfX/XBzUI/4LCZvzB9FzUnWCH0aofduUFrJX4V+7Qrf7z1WIV9b5ukae9I1Q+ZxyrMaz9WCWcdV0m6j/D7WkuVGfgbsZVBiQH0sYQUx0V+6e2w8v+ZNoh9H796J6SfXhzrSXnzLeXMJxI3R8nIFCmzP+OlLPO4h88cqnfGbOu7SsY9G6TcDqrcelL/9mrcc0Li/VW5myR+uRaDZw0wj30kXbGljPpC6vKunKwXTtnxgaT/q15Pf1fJqBNSdhTli4ueUOnYp/YJj7GPlHuz+9jH2XaWMultieuoZJJ23F0mfVPJ2GdwPfSt+mrs07OmY5/1xysf+0yU+J/h7frbfFf7sc9W8gfHPswXoodq7/7Pj32+sZCVh151l3Xzj7uPfRr+xj2+tQf9JWnKRqWre4E=
*/