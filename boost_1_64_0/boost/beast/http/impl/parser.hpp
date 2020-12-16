//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_IMPL_PARSER_HPP
#define BOOST_BEAST_HTTP_IMPL_PARSER_HPP

#include <boost/throw_exception.hpp>
#include <stdexcept>

namespace boost {
namespace beast {
namespace http {

template<bool isRequest, class Body, class Allocator>
parser<isRequest, Body, Allocator>::
parser()
    : rd_(m_.base(), m_.body())
{
}

template<bool isRequest, class Body, class Allocator>
template<class Arg1, class... ArgN, class>
parser<isRequest, Body, Allocator>::
parser(Arg1&& arg1, ArgN&&... argn)
    : m_(
        std::forward<Arg1>(arg1),
        std::forward<ArgN>(argn)...)
    , rd_(m_.base(), m_.body())
{
    m_.clear();
}

template<bool isRequest, class Body, class Allocator>
template<class OtherBody, class... Args, class>
parser<isRequest, Body, Allocator>::
parser(
    parser<isRequest, OtherBody, Allocator>&& other,
    Args&&... args)
    : basic_parser<isRequest>(std::move(other))
    , m_(other.release(), std::forward<Args>(args)...)
    , rd_(m_.base(), m_.body())
{
    if(other.rd_inited_)
        BOOST_THROW_EXCEPTION(std::invalid_argument{
            "moved-from parser has a body"});
}

} // http
} // beast
} // boost

#endif

/* parser.hpp
3uNKGp730q09Evm7/yRfxYs8nKA6slS1IRLlAb3GdXgY+k7a0U13XVvr8EC4lpTP6+GGEZ98Vko424TXevKcqX4CClzjsN/zJ+a5trK51pWvKs2zo9uzi/mq8uyhlpam+9Ion6oESScfFe58aH1W0eobNkaiPBZ5ry/nCSu/WOLM0/w5aeSIr0aYgu5CLre5GpnTzbv9u4ZFeRqOzmNIk60TnmB07h7m/YYBfGG4wsm5UQ4ngLxSbsmrp+zXaYOZjuQoZqPb7lP26kYITdqWe8SVnbJqnFOMn0xosR0Oif6r0Xpba7hFRn+0ho2+L0eozOgXatirf7RQ2JJ2BoVrhE3kuxCZadF3xS22PXsNCfcJW8amH1Obio9MJ/gxPYwNY9z9V6Ptaa3hx/hwYfLBo6In+fOMJ0eUb/0YGRqjOIz7ZC9OsL9hEqPm2/6oA41XILy7iwnPkPCu0FtDacK7+9IIO462YqcuTLwZhue1WMILNQw7ZYnw1xP4g2Um7mlyz4sIL5Dwe0LLQj0c/i1h9VtQvtcs0fkw+Qop58tJZ6LhFYaUk+vEG8K5G0TnnNCL0XbAOZM3dJYMWB6yuOKkFZK2sJNwrkmTsVnpxY5fQD1x7oiWIbTPmm7SKYpLZ5fanYgxHy7i54LVkod0DTt5GiFl6ZC22bIhUl/ZwntBSatI0+o9KervVe3yUXhE7jkodB95kXPYaLecO2QNte4TbtqNtOnZDGibbA79WRmZPdMz0sI9o9zTDEmzvtbtQ7ZO4g8jPcKkd5WEX+Ud81dkbNrXi7ZCepvtfjJwkekjD2ofsSVX71uB3hYZw1o/GM7sZ3T3OOOY6l2H3j2j0UtvfdrR+eMAr84edO62dcJXpzk6q+N0DqCzVcbD1qOOzp1x9+pA5wpbJ6v1ZUfndtWZQDhTx8xMdMqz6Y/c81XEHkMrCa/JTu530c9KHxCtV6ughhpT/wrP2JrLuS2co59xztXPON8ax1G90csDl7g7DVcr1vaHc36XOe9pv4bXShvjmmljnjH+SeWQF5LxoeAocDx5Lj4ncYxpZlpX1RI4vmicPNOPyyW8hHyElMsZshafq/6S/v6RmsZI06fXSPhq3hNnmD49X9IYpTxT099MH7lE4mQykc1y9UkosBHuo+n+XHQq4tMM7JP5kr7hmzbUtTTVNOs9B4CvSXqTmCOElefspDkwvi8bXuu9Emd3gm3svvQSY//BLO1L6SvDmYRdfcn05ZD2ZacOtkuaQzTspNkr2h803VdId5PwVs+V88P1fEFYuaL9WreHs2aGe0I40DkFGiKePvPOPOk39Bcjpt+8S/nLxcf67aTPvGDnl1u3NG1tqNnSIv0Iu3n6UZm3HxkOqeGkalvP92/r5vc0rV9sLjcQWYRMId2958a3dTdT2wqcz/1E4k1XWzvp5Cb8Di4114aZun9WwjNkfH0Gu9+MrVtt2/c/JWEO4ug80Nept/EnbL5njz2z47+5pHPww2qv85CBilnELSoRe9U1tDhTXmjlOgPso20d3zpjp3NE/3S1kxM/17TRrRIOiS0yuedu5F573O8d47gWkz93mWlnjM3Jy+zw/3tLmSNSvmnO3rTK2R+vXN3RyCD0dsbKJ5OyfubZwn7eMH1N9UbL9Rwps6ib39V7S2J886VGf1BSXr/Wkz6PyD2VqwtKOfQ+8KQfkjRlrul9fhoQq7v+yGJkhN3WTdmch5bamqr1jC2xNs69tH1rvfU1vlNO/FzXPKyqqSba1SQe7UR1pjCKZ0bPEToo56ZxZkTgPOSvokMcCTtxCq0e6s++j4I8lu3MQwpc85CkXHb1UfO0f0rh5j+bcnj6QIv6VTQhQ5G1yCk=
*/