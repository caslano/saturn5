//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_STATIC_CONST_HPP
#define BOOST_BEAST_DETAIL_STATIC_CONST_HPP

/*  This is a derivative work, original copyright:

    Copyright Eric Niebler 2013-present

    Use, modification and distribution is subject to the
    Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)

    Project home: https://github.com/ericniebler/range-v3
*/

namespace boost {
namespace beast {
namespace detail {

template<typename T>
struct static_const
{
    static constexpr T value {};
};

template<typename T>
constexpr T static_const<T>::value;

#define BOOST_BEAST_INLINE_VARIABLE(name, type) \
    namespace \
    { \
        constexpr auto& name = \
            ::boost::beast::detail::static_const<type>::value; \
    }

} // detail
} // beast
} // boost

#endif

/* static_const.hpp
BQABtkgkYK1VbW/bNhD+rl9x9bDAMjQrbb+seSkWOO5mtLADO0URIIBAS6eIGy2qJGU7WPLfd0dLtox2CwaUfqFE3t1z99zxGA9+3AhgAC+OxP8SGjR7jRuj/8TUfV86SZ5g9yGte5pfAonhoPKUhPCyyhP0vUrSoFzwc5K8BHTPvvFfzJr3CT/SCqmx5khXj0Y+FA76oxBev3v3K/wCb07fnEZwLUqJChYOyyWahwguMr/yWyG226HF9xGgA6GGjanbQlqwOncbYRDoWckUS4sZCAsZ2tTIJb3IElyBkEuFMJrd3E2mv0ewKWRasJFHXYMtdK0yKMQawWCKcr2zUQnjQOekTsYzaR0ZrJ3U5ZCwERyalWUbDC+U1SDWQiqxJCDhoHCusmdxnNZGkfdxplMbp234w8Kt9pHckRMr8Qi6cuA01BYjYMkIVjqTOc9ECC1W9VJJW0QHbwiqzGJtwKJSbIv0JNqd2wiLhp6IxaAij6XjyerSMtSm0KsjQeKRreS1KQmIeCChTBPNEdRlhsYL+8hbiIZTT/C/pubgbwa6JGegd7WAyaIHS2GljeDL5PaP2edb+HI1n19Nb+9g9gGupnds7ONkek2plwRmALeVQUvgBuSqUhKzBvPHjTiIB3BxPV6M3jP8otAb
*/