//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_DETAIL_SOFT_MUTEX_HPP
#define BOOST_BEAST_WEBSOCKET_DETAIL_SOFT_MUTEX_HPP

#include <boost/assert.hpp>

namespace boost {
namespace beast {
namespace websocket {
namespace detail {

// used to order reads, writes in websocket streams

class soft_mutex
{
    int id_ = 0;

public:
    soft_mutex() = default;
    soft_mutex(soft_mutex const&) = delete;
    soft_mutex& operator=(soft_mutex const&) = delete;

    soft_mutex(soft_mutex&& other) noexcept
        : id_(boost::exchange(other.id_, 0))
    {
    }

    soft_mutex& operator=(soft_mutex&& other) noexcept
    {
        id_ = other.id_;
        other.id_ = 0;
        return *this;
    }

    // VFALCO I'm not too happy that this function is needed
    void
    reset()
    {
        id_ = 0;
    }

    bool
    is_locked() const noexcept
    {
        return id_ != 0;
    }

    template<class T>
    bool
    is_locked(T const*) const noexcept
    {
        return id_ == T::id;
    }

    template<class T>
    void
    lock(T const*)
    {
        BOOST_ASSERT(id_ == 0);
        id_ = T::id;
    }

    template<class T>
    void
    unlock(T const*)
    {
        BOOST_ASSERT(id_ == T::id);
        id_ = 0;
    }

    template<class T>
    bool
    try_lock(T const*)
    {
        // If this assert goes off it means you are attempting to
        // simultaneously initiate more than one of same asynchronous
        // operation, which is not allowed. For example, you must wait
        // for an async_read to complete before performing another
        // async_read.
        //
        BOOST_ASSERT(id_ != T::id);
        if(id_ != 0)
            return false;
        id_ = T::id;
        return true;
    }

    template<class T>
    bool
    try_unlock(T const*) noexcept
    {
        if(id_ != T::id)
            return false;
        id_ = 0;
        return true;
    }
};

} // detail
} // websocket
} // beast
} // boost

#endif

/* soft_mutex.hpp
Lqiq7aKa7H1qzn8RefukpncXbKV7obaHz8DB8HmtP3vgFPh3eC58AS7SvVcvgi/DS+ErcBV8Da6Fr8Pt8E34OHwL7oJvw3/onuBvwv3wn7qX8zfwM90z+HMYIO24qbzQ9a4w2UdeHNS9fr+CleDXsKradW9bXXdKmWt499624zSfx2s+n635fA5sCtNhb5gFB8DJcAicAofDDDgGZsIJECNyZSKcqf5IB+nSNZZwr5aPfb8Dmo5l+KsDL4N14ZV6n2tgBrxW470OzoWPwWXwRngdvEnL4Wa4Ht4GH4Or4bNwDfwA3qn5fRcMkYb1MAneDVvAe+EpcBMcCh+EGfAhOA9ugYvgVngx3AavhtvhjfAquBVyb91zXdcJwjGY2Ig919freGADbA3vgd3gvbCv2gfAjXCIXtd6wbq76PXifvxVgA/ASvBBWNW2a/ipZv0ZdV7lbjO7HjjnIuKvGtwOG8HHoe3+BGwPd8IusGaYPZDhLuzD4NNwGtwNZ8Nn4SL4HPwLfAHeAl+Ea+FeuAm+BLfCl+Fe+Ap8A76v6T0Af4EfQbu8PoHt4WdwJPwSjocH4Z/g1/A6+C28Ex6G6+AP8Dn4I/wQ/qzjE4vnqAmDsA4MwxQYCzvB8nAorACzYCI8D1bVcWB1eD2sATfBZLgD1oTab+u6I9x8+u3L7fvDK2AjeCVsApfDHvAazedr4RB4HRwPb4TZ8CYdx98ML4Qr4cXwNngrXA23wDvgdrgGvgPXwvfgOngA/g1+ATfCH+HdMEhar4Zl4T1Q5beus2FM6SO/hwWQK3A4rAlHwAbQvQd0Bzgaan/DGpbo/c04PSNhPGwOz9Z4smAXeA4cCDPgeDgBpqu7ppf1JNH7m0Ga3sGa3iGa3qGwCUzT+w3V+LY4ayd0DUmsnjWxUdvPt/irCr/T+A7DpvAIbAd/hMPgz3AEPCdIOcJfsc+Dv8GLoMX1v4IwvB3GwA2wDNwMy8IdMBa+DMvBt+BJ8HNYEdrllwjDsDKUugerw2qwMawOW8AaOm9QCw6GteFEmAKnwrpwJqwHF8OG8HLYCN4Em8HbYHP4EGwBX4Ot4FuwLXwXtoe/wY4wQP51gtVhN1gb9oTdYR/YC/aFGKs/nAYHwhnwDLgYDoOr4Wi4Ho6D98Hx8BF4NvwHJJ+l/OQ8za3efjEeztD60F3rw6lafj20PvTUcuwNB8D+cAgcAIfDPnAM7AsnwNN0nN0PzlR/Wh/1+zNt26c+7tf7vA/bw8/hWPgRXAQ/gRfAL6D2B/p9ljGlT3+QrWcJTIcnwxn6PDM1PPOx+u1QvrcSnrRb1Omg9ic6v/CAyqfNsBV8GLaFj8BO8FHYFQ6Oof7AbTrvsB2mw8fgVLgTzoVPwvPhLvgX+BS8De6GT8Nn4Yvwefg63APfh3+Hn+v1b+FrsDxpfh3Whm/Ak+GbsBV8C54C34GnwnfhMPghzIEHYD78CN4BP4Nr4edwi/p7CR6CB+H3MClIPeA568A+sAnsCzvD02Bf2A8OgP3hODgQ5sBBcCEcDJfCI9p//ArvhhbXn4Nh+CEsB7+DJ8EaIeaNYE9YDY6BYTgR1oILYR14DWwAV8GGcA1sDDfDZvAV2AIehq1hjTDtE3aHHeAZsCMcDTvDsbALzIGnwD/BBvBy2FPfT/eb7zF6LoWeWf+q1sO5+n66APaG58HBcCEcCS+E42C+ysHF8BK4BN4Cl+n72mVwO7wc7oFXwP3wavg5vBb+Cq+Hdr24AdaAK2AzeCPsBG+GXeBKOAiuhmlwDRwJ74LnwHUwE66HzDmW6EwAzgLwPQMgLcfs/e/Z9z/6nv+Ea3l8+/wf6oGB4VZF9/JfBtdhXHv3R9u3X/c=
*/