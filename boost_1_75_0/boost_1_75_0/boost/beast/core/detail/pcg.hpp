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
hNuMQTtWfPWbZ9el5gqJ2UxgitX8qldqU6pOB6NSfjWPPS8xa1DyuZMyXnoCf0la/oQDkHkrPkkCf/bxXmg5VJQWEu5wJxy/J8lQ3L1H2TiuXDqVvD2Fl80BIPVYe5+WbzS/naq9YrSaEuKDuGXDr4Xa0aMUIGa7O8LU8xC3MfWJJjUAjGQPcK5njYD5kwUG4h26QF517Dcu+ZbmPI5wWgPdPcP3eZahcumyJkK658PjX/zMgfUQ5MOfx/ZQ0kjn9rYJLqwL3HKfrZ8KWgqatSaC+qbh+rnYgkUAfluBgcAxJIMb7wOfaJZpjqiaesdKaoHED9UQ4L9SIFDm3+VY/28O47f//VmlY2Uu7eJoaeX+3yPc02Ao3afg6AUbPm/wL/TXzqxFN9k83dg/kLU3AhrqxDoS0OIdJstyHBW9wjYIxEsbLtzyc6MgTAUhanZGTMbyonUttDlcnGgVa15otl6hZfZqfp57K8K5nVi3HSfDKgSu8Xk63lKuTmPjak1j+mzTYyfe+nryczI/+136Zgi/rNv9Y/FS5yuLUyj0y3ct6NT68yzJgnEousGbJPVfmu38jycPdfLklPS8LgtHgnjmyh7G4brxuqG6sbyEdShuSPtaKdwiWvHqkJMHUK4+RahpKBIZgoWzqAlY23XIkwnHelnwddToyKoTnGfrPPkV3LdG4yJtYs49lwwSvxVDacfknA5Alq/Dp2H3
*/