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
3aWm1aQF+vjqyj5v9iL83fzr/cYcJJxlZX6f9u0QapHW9r52RPvaf1BLAwQKAAAACAAtZ0pSBs8rc/0CAAB3BgAAIwAJAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvZ2V0aW5mby5jVVQFAAG2SCRgrVRdT9tAEHz3rxilKkqQG9M+FQioKNA2okoQMUKRkKyLfcbXOnfW3ZkQlf737jp2gX6Il16U3Hm9OzM73jja/X8rwC5eXEnzTWjR3lRcWPNVpv7v2UnygO2Hqm5of4kkwmPJQzLAyyUP6DclScsy4nOSvER0w9r4J+LKm4SPFKEyrhybamPVbeHRHw/wdn//Pd7g3d67vRCnQitZYu6lXkp7G2KUNZEPhbi/Hzp5HEJ6iHLYQsWFcnAm92thJehcqlRqJzMIh0y61KolXSgNX0jkqpQYzy4Wk+mnEOtCpQWDbEwNV5i6zFCIOwkrU6nuthiVsB4mp3ICz5TzBFh7ZfSQuCW8tCvHGEwvSmcg7oQqxZKIhEfhfeUOoiitbUnqo8ykLkq79oeFX/3qZEEiVmIDU3l4g9rJEJwZYmUylfNOhlCwqpelckX4qIaodBYZCyfLkrGoTkm3lS0xb+0JOQ0VKVaeN2e0Y6p1YVbPEslHRslrq4mIfKCk
*/