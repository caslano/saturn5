//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_DETAIL_TYPE_TRAITS_HPP
#define BOOST_BEAST_WEBSOCKET_DETAIL_TYPE_TRAITS_HPP

#include <boost/beast/websocket/rfc6455.hpp>
#include <boost/beast/core/detail/is_invocable.hpp>

namespace boost {
namespace beast {
namespace websocket {
namespace detail {

template<class F>
using is_request_decorator =
    typename beast::detail::is_invocable<F,
        void(request_type&)>::type;

template<class F>
using is_response_decorator =
    typename beast::detail::is_invocable<F,
        void(response_type&)>::type;

} // detail
} // websocket
} // beast
} // boost

#endif

/* type_traits.hpp
PJzOfpv/EZ5dTy/PT58aXKBJtamd1BYbC3UxDkbKemGd+QE/yTD+C+gNoDHa2BZO1WGGHw717DeO09JQS6Q9amyCUGqfa/QhpR7F5DX8aO+K7v/3+iQdOkcsy1r9J67Gaif2FmKFoqjKz1NtXrSbAfjEUKodfcCgR/b6RHjW+dT5B1BLAwQKAAAACAAtZ0pSPcLKHakDAABOCAAAJQAJAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvaW1hcC1saXN0LmNVVAUAAbZIJGCtVW1v2zYQ/u5fcfMwzDY0K+s+bG3SYJ6TbkZb27AdZAECCLR0irjRpEZSdoyl/313lFS76DLvQ5U4lCk+L3zuxMSDL3d1YAAnryR8ErpoDIi5NX9g6v99dZI8Qf1DqHsaT4nEcIA8JX04DXmCXoAkjcoF3yfJKaF79sZ/YkbeJ3xLMwRj5NiUeysfCg+9cR++f/nyJ/gOXpy9OIvgSmiJCpYe9RrtQwQXWZj5uRCPj0OHlxGgB6GGDdWqkA6cyf1OWAS6VzJF7TAD4SBDl1q5pi9Sgy8QcqkQxrP53WT6awS7QqYFk+xNBa4wlcqgEFsEiynKbc1RCuvB5AQn8kw6T4SVl0YPSRvBo9045mB5oZwBsRVSiTUJCQ+F96V7
*/