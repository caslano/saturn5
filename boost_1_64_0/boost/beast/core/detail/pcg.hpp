//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_DETAIL_PCG_HPP
#define BOOST_BEAST_CORE_DETAIL_PCG_HPP

#include <boost/core/ignore_unused.hpp>
#include <cstdint>
#include <random>

namespace boost {
namespace beast {
namespace detail {

class pcg
{
    std::uint64_t state_ = 0;
    std::uint64_t increment_;

public:
    using result_type = std::uint32_t;

    // Initialize the generator.
    // There are no restrictions on the input values.
    pcg(
        std::uint64_t seed,
        std::uint64_t stream)
    {
        // increment must be odd
        increment_ = 2 * stream + 1;
        boost::ignore_unused((*this)());
        state_ += seed;
        boost::ignore_unused((*this)());
    }

    std::uint32_t
    operator()()
    {
        std::uint64_t const p = state_;
        state_ = p *
            6364136223846793005ULL +
            increment_;
        std::uint32_t const x =
            static_cast<std::uint32_t>(
            ((p >> 18) ^ p) >> 27);
        std::uint32_t const r = p >> 59;
    #ifdef BOOST_MSVC
        return _rotr(x, r);
    #else
        return (x >> r) | (x << ((1 + ~r) & 31));
    #endif
    }
};

} // detail
} // beast
} // boost

#endif

/* pcg.hpp
l0SNrdLz7MsGnMvdaTVutn6rmRmLwvO17GJlRqeeKVjHAkY/Otk51C73GUwtJYSLxPdOeIKAeJeR/lDSYYVMbR3c83URYRu18fjaV8Vw+QNXa/82pp05f4JBv6LTGqZ3lSgWnaV/WkyEgOYq/iyXIga77g0RbEXWbb+nv9r1Gthmac9gXU8B9xGpol9PUpx2pXJwmzOKSPRIseA/fldDbR33KSAhAYBOk0WSaP1HZUEtdYrZ0XZXjHPsiO6QxhqietUnNBasC7aSHEj1PaxRy9cZqGUA2A4m1yK5XlI9dr0OcyfoqGpuJMVyIZFzMCfIOyyH8uoeTq1+E3T8q52cQU8qLw/oryVOc/cJ0EobTL9bdOTJ4wJiChOC8feKA4Af9WMRxxsRXsrbSHecQFGGP666qdVSVe+jFSGHQwzwN45m+J/nZoivLKNHx7m5BPWUJDfCUJa1WTArpCtgZiGzgnLedBtv73ifuPrB8m2GgrpP+sh1AXWmjAYirUXKw0uSj3/NZ1SoHdg2DA3/2QGigpgV6bTesTLsvhLBjSiHwfklcLyNC/M8b+l9Qg==
*/