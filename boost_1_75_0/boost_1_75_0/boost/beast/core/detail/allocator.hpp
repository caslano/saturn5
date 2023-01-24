//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_ALLOCATOR_HPP
#define BOOST_BEAST_DETAIL_ALLOCATOR_HPP

#include <boost/config.hpp>
#ifdef BOOST_NO_CXX11_ALLOCATOR
#include <boost/container/allocator_traits.hpp>
#else
#include <memory>
#endif

namespace boost {
namespace beast {
namespace detail {

// This is a workaround for allocator_traits
// implementations which falsely claim C++11
// compatibility.

#ifdef BOOST_NO_CXX11_ALLOCATOR
template<class Alloc>
using allocator_traits = boost::container::allocator_traits<Alloc>;

#else
template<class Alloc>
using allocator_traits = std::allocator_traits<Alloc>;

#endif

} // detail
} // beast
} // boost

#endif

/* allocator.hpp
SDFSSJAm2AcMxhjJRCsMuUsrtRkm+SPHfgWHXpMDNFtcEJUqhEFSLt5630B9iq/9VVmLf8Q+nC+SDLkPzSikdPAR4d4Zei7GJ1W0zHuZdli7G2BGQbKo6XvF7mKUzmOldKd66c1TVXoM5PpjlCdOIWH4y6/rsFCu/kX0olULJcm7bK5ydXHDJ3LdupQeYIcRu18GC/CtnUx0vLS0dT3vo6dvCJPcnY8Hh5FlIHUqdfCO+ZKCymjYkuk38wgbn8ah8arUtAxhw17/p1AVIx9lm+pxnLOrMwAIqzUdGehD6t8TlXTwHuCf5Ou/kF1V0UK5dLAxq6BTrKAQkqQwp5THGfk1WDFtSMeQwm5gQDCXpnP53M0d5Mbdxm8aHuIs7Pvt8bz8cQMK3R0UgJCJbSofva4j9EBCLiak3XG8+HOaRgs3+lS+CjDG2OI0Ia9eIv3R7aB8CiLFyCoqsRpquXoc0ELEH06a6bu0vUwTtHn2wHOftxJD1uJxMCayGduT2dkjxEQEOBP3FrjcaCry/HT7ayKDl77ogNxa7RO3at2pc9GBW3ELUPZI0x5k+vsY2nAL0F5SbAe/9Kv8r3M78lImAyaieYx0O3nVVluZRaYjviVu1YmcAJdYtzriRMa06bPBBtTnMasa1N+bdr527OLYdx2hcBZKT61T5k3oee9s97oy+7Cw6pa+JH0mk07akPAZ4+J/73FgxCawf67F
*/