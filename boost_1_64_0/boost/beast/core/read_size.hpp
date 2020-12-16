//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_READ_SIZE_HELPER_HPP
#define BOOST_BEAST_READ_SIZE_HELPER_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/throw_exception.hpp>

namespace boost {
namespace beast {

/** Returns a natural read size.

    This function inspects the capacity, size, and maximum
    size of the dynamic buffer. Then it computes a natural
    read size given the passed-in upper limit. It favors
    a read size that does not require a reallocation, subject
    to a reasonable minimum to avoid tiny reads.

    @param buffer The dynamic buffer to inspect.

    @param max_size An upper limit on the returned value.

    @note If the buffer is already at its maximum size, zero
    is returned.
*/
template<class DynamicBuffer>
std::size_t
read_size(DynamicBuffer& buffer, std::size_t max_size);

/** Returns a natural read size or throw if the buffer is full.

    This function inspects the capacity, size, and maximum
    size of the dynamic buffer. Then it computes a natural
    read size given the passed-in upper limit. It favors
    a read size that does not require a reallocation, subject
    to a reasonable minimum to avoid tiny reads.

    @param buffer The dynamic buffer to inspect.

    @param max_size An upper limit on the returned value.

    @throws std::length_error if `max_size > 0` and the buffer
    is full.
*/
template<class DynamicBuffer>
std::size_t
read_size_or_throw(DynamicBuffer& buffer,
    std::size_t max_size);

} // beast
} // boost

#include <boost/beast/core/impl/read_size.hpp>

#endif

/* read_size.hpp
vXd5LFVJryN0JRr9KOqURT9Sq872e5dLJF9vjf2I5aSQxkmCQut2fYjp+yn+nSh0COMv5g83r0dnFmVppv1Id0uaoexnrjInkVZl2Nm6M/0tas28QOi7GK/ye/c58uQdEr/KvCbNMrnOW0WfM6fd7tnnWM88pJ0j6caa+qB73vJK7OvTJd195v5mzgveddqcXPAT/1bSp/xSQm4I9Pe7JuTGwMDQenUCa4cGh7v6UDD7kLGfKpx22TukvFApL8rUr5Kq6FeJzn5VbRuPCDcbD/JDDew8uObp1bfKzX2rEvuOB09Z960lXAtdSHuOPKDRt+Le8Ohb1bVRk3xDlG3GTKF72tlyMP0N6iy0QqEHOO7U0sRvhdFIH8u91/UntBBbm7QsSZPouFsvZB+SstnPB8ka9p/elH1y3n2Kz/5c0k9QfeRTSZ/HPuUqr5MWyd+ESUI3cayA7AjV2+OXuVDZqW18y4hrLHw1qxI7tXwpY5DD1A/5HO4/seiHEezzGZJusOMOnNSfq1/sy3EeZSyp4jfRnLbUoj+6fsuflnR7cW57vBo/HJY2esfUR93LW2dj6zFb0nR0xGh+sAUPtDwncbOU3VyL5N7D1UK31Gvh3hRtBqzuYky/t0WKp2Kk7ftqkZTHFZLvZdSno3Yd7pcgn9Xzlr7Fc+j4vBKhu8Nrf3i1zky4WvtyPGVAqYUMWGchA757w93Ga+qbZhrxHnThW4p2szE4X1eTy8/PKTM+N/zCQr6m/E5kBoRFgcf2Mnv/DA9Lns16DjiDMoTlXK/OWsn/vUF/BRu0lXa/yczT76L/BaHL9clae95zlVOBtdt5pv6QJ4McruGznD7q92u90K84bH6HmT5d/e6OPG3QjWzHusuc5Zv7O8vg724lfTXOI+12q99Oyqa1kq6zqZ+75y23GVtGmZ6vmWzGwoFzpf1gY8W2ek/Kex9rpnHKBqqDkUasiwZLH2M5UsZ05Gn/tvj40YVW3ySCzzT5+Gf6xRL/CmnVvpWd8Tbix/5Gu/cl4Yua/z579MNy773H0sZod9wz2p32lr+7snvr+oqtx4qy12ef//OIuePWfvr8wrCOpT8tWw+X4cyztOlYS5uOEjUPk7m2xNXht9C4Vy2GNgql3Ju2irYKT5B+ivTTpPeRPkD6IOlfk55g2JQD9wD3cy0/RY1PZY4i9agle1fkEpsGA48A+5AeTBp5xbZhDel1pMtIPwl07WEb5xqLcNyWSDsYyBe5GiFda9oo9Aa2Ao4DtuaeoDbcE9SWe3Ji+H6xwBPcU3aK9B+BnYH/ZDoHntENGAjsDqwN7AFsC4ynjUcvYAKwD3AQsC/bawAwBZgEzAbeAswFjqXNy63AZcCJtHmZBDwBnAw8Rfp90hXAFGAA3j8VWA+YDmwEzAA2BU4F9gRmAfsCs4FJwBzgLcA84HTgncA84EK270GXrORvXCKwodi64KINRkfgSqDwIXAEbWzSuZfqTuAG7rXayO+4CXiINjfv0ObmDh0039+gT5A+RToM9XoEeC3wF8COwK18n0eB/YG/BN4IfAz4OfBxYFEN9khdiu1HCew8tiOcRDjvs/nwXb7Ld/ku3+W7fJfv8l2+y3ddwnV11v/Tci/X+v/ONpo6N3iRQ5PL2O9wLbHQOI/6Jbe1FXl4cmpqumtdJdfrvGzmMflLv0foJrQFwOr5QYPWTXpWFMj8I1T+7mpto1DoDrrEm/Or9RU5b1+tmeZK+ihJn8Ty1PmV5vzUR3L/pVrnmCbpo037qrOp18c8WeIcej1oLIqgMTmthVInr8qtlv49Dphre14/2sPrfFe+I/RvC19y133PPGi9XpYYqMl1BpGxwP3Auzoayhw=
*/