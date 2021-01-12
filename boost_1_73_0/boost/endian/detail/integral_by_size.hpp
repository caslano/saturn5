#ifndef BOOST_ENDIAN_DETAIL_INTEGRAL_BY_SIZE_HPP_INCLUDED
#define BOOST_ENDIAN_DETAIL_INTEGRAL_BY_SIZE_HPP_INCLUDED

// Copyright 2019 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/cstdint.hpp>
#include <boost/config.hpp>
#include <cstddef>

namespace boost
{
namespace endian
{
namespace detail
{

template<std::size_t N> struct integral_by_size
{
};

template<> struct integral_by_size<1>
{
    typedef uint8_t type;
};

template<> struct integral_by_size<2>
{
    typedef uint16_t type;
};

template<> struct integral_by_size<4>
{
    typedef uint32_t type;
};

template<> struct integral_by_size<8>
{
    typedef uint64_t type;
};

#if defined(BOOST_HAS_INT128)

template<> struct integral_by_size<16>
{
    typedef uint128_type type;
};

#endif

} // namespace detail
} // namespace endian
} // namespace boost

#endif  // BOOST_ENDIAN_DETAIL_INTEGRAL_BY_SIZE_HPP_INCLUDED

/* integral_by_size.hpp
L/f78tsq9EY6q4hbINf9lCzfXIoKNExITxjFDsV4SY99HiXfvpPvxWk44wnnAsJJrHeKU0f9+CL2S7wgaUwJfiNO/M3F34X4Swiw0aFRx7D9DPfW//53kBz7d14JQ+5PWiLnb1qe9rG5me9SPt79aJJHlEPYXOe2geFznScw61xHzO+o+e9q/lrNh9WcGjH/axsx/+uj5on/p3sdEmSvwzP1Fndd6mvwj+8yA0vqDn4q7sRc
*/