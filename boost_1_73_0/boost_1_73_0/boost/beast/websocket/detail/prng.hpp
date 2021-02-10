//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_DETAIL_PRNG_HPP
#define BOOST_BEAST_WEBSOCKET_DETAIL_PRNG_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/config.hpp>
#include <cstdint>
#include <random>

namespace boost {
namespace beast {
namespace websocket {
namespace detail {

using generator = std::uint32_t(*)();

//------------------------------------------------------------------------------

// Manually seed the prngs, must be called
// before acquiring a prng for the first time.
//
BOOST_BEAST_DECL
std::uint32_t const*
prng_seed(std::seed_seq* ss = nullptr);

// Acquire a PRNG using the TLS implementation if it
// is available, otherwise using the no-TLS implementation.
//
BOOST_BEAST_DECL
generator
make_prng(bool secure);

} // detail
} // websocket
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/websocket/detail/prng.ipp>
#endif

#endif

/* prng.hpp
oxqkkmmgNBheFISFcYKbRjaHsC2PT8ugQsXC0mCUNES1z1X50UKsI6FktZZIhHXARanCMvtQy5Rrt9hl3lG0NXUF/s/WHPWmoCSKgd4khHnYg5gZYXy4nW9eL7cbuJ2s15PF5g6Wv8FkcUdgb+aLa2y9QDIN/LHS3CC5BlFWheBpy/n1rsDzgiGMr2fh9Ir45zeTFfIypOPklb2QD4ADlUbFlqHBhMyULhl5A1isarQpZKrAehHAOOiwEPpbIZOiTjmMjU2FGuVXJ1PklcYwOE0qXCHxy8AIx///dZToyVg9uq46SegviixETEzfmybBhFUsFoWw5J6dYK63s3eTm/lihqYqSzRQ196FQt/ZHE3utkanSfO/aoHd6aDhp9Hzi9EF9QrF7Jw7sAJCWhIl+zsl0oH3twcw3a7fwpBiLtunRKUEaOCVe5xFyzeXHr5zuK/cEHFmDpGQwvYHFCayPk0PgBDxwBtCiOcFbiYtWcmbDcCM2Sudkg5ac4Qx3OLucwC+Y1yuNtE2nK0Xk5uZDz2C6Tmas1GrSRjeLtfo2Z7hieaW4jpJXUPf18a6EiPuDnviCvBlotZvEVmUrMLDhYZRW/8RdumUirL/TBPBVDzBQ4U8QK9bf3Tm+DIR0224Wd6sZ39sZ+EG5XQc
*/