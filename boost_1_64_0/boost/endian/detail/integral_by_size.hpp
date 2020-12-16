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
Kug9Krvhk93wbS2kbvhiu78ruuEbSN2olyskj+yGr4Lew7Ib5bIb5VuHUzfKY8OoG+UDqRuY5kEkUzeAuOi9XnbDK7vh3TqKuuGNTVkluuEdSN2oS8MbofS8seiagccbkTS8UZeeN+5rG3i80ZSGNyLpeeO1qwcebwTT8EZTet445uqBxxuz0vBGMD1vRFcOPN6oScMbs9Lzxk2tA483GtPwRk163njyqoHHG9VpeKMxPW8Mv2rg8cbcNLxRnZ43glcOPN6oTcMbc9PzxuIVA483FqXhjdr0vLFlOfFGGnJclJ4cF1FJr0LdOIkqNCSO2w27yOqtnN7yqcbAquXOmy5bNsNIFMdTZR7VAVlZOQZa4MrKk1XnS/WEK4OhKVBD80ILDY3qk6zMi4tMrsybrDqfehDkygBBQxWCbqTKyhWhy8o83DF646rzqQfVXBngrFjhLNTSL5xFLXH27rJ+4azOEmc/X9YvnM2yxNl5y/qFs7mWOCtd1i+chS1x1r20XziLWOLs8qX9wlmNJc6OW9ovnNVa4mxvc79wVm+Jsxua+4WzJkucndrcL5w1WuLs7Sv6hbNFlji7iyrz6lMBzmaa3NqYePbbRtwsvMKIG1moXOIgyIUAB0MVDiZfYcSBLOSVfQ1xIV1QF5v6Kgt5WN5QIdGnEtWnZ5Zk7FPYsk+3LsnYpxrLPn17ScY+RSz7NHFJxj7VWvbJkblPUcs+/XZxxj7NsuzTzYsz9qnOsk8XLM7Yp7mWffItztiness+vbsoY58aLfu0c1HGPjVZ9um6RRn7tMiyT7VUiO2bghVt+V0yeh0n0xmwlc5kOHtPsgjUH3CIMsuNZfB1ZcjRRgDjd6ChAaco1Gos1CoKwZfoSbe2ojgMFIlC1xgLXSMKFbURAHEXn/1K7yG7NGjwN/gb/A3+Bn8H/TPvx60T939MUVddnHgaX3XRLLfN7hZBIkrA+d72bQCqS9lWoVf8kE/wfelTqvFsszy5vIFzTC/Eu57gZB+fO98H3sJbaznDqsPoMq+7+bAzXSWwKCyuElh3kPOHeav97MkflL/WKY2Z/LUKhvftr/Vew6C/1iHy11o7NK2/VlHpoL/WoL9Wnw0Z9Nfq109zldo7ycJfq+ySD9Zf6+xJ1v5a8wty8Nc6bNL/hb/Wgost/LWqHe+Lv5br4r79tV6eeyj9tVryPzB/rePmfrT9tcZP7MNfy2301/IY/bW8Rn+t8tz8tcaNMfhr+TJsIPlw4ydDHlcWecrS5pHhLwMDqTGWm3L5MCAdTbd96/dwQgNbEoA/OEhqY84d++tFxUrZ8WBCvtwwG0hdMzt4uJUJruPMX3XHZNdq4Y+wwxUpO9zQi9gO59a38wZS12oU3tVOIhsKybr4x3q3RxgKRypDYUWdwfjJW40DqVf1iHLTPrcbrbMdrz3x6y45YDXwR5hoD1Mm2shsg4mWd8MHUteq07LZ5pJF/5Zdq09hs8UXDnw2q0vHZnLD5NidV51m5LCfXDDwOSyYjsM6Rp3q2yQHrA7+GNnssVkDn82iadnMfuOp/5FdC6aw2T/PH/hstigdm8k9q2fWNV9k5LCPnz/wOSySdiLbvC/YJgdsUcpEFvjmwGezxrRsds/Zvb2ya5EUNrvgvIHPZuG0bLb997UrZdcaU9js6ujAZ7O5GdgMt7uPGrl6jpHNfnnuwGezUFo2u2HeOiUX56aw2bMzBz6bzUrLZt+dctntsmuhFDY7cI41m6WjbLnJP9b5y9ONRH3fOZZEze9as7xCK/rm0Z98S9fQkZgKFDHNPseSmPhda5ZHjF/g3kCnNmUb/VuOOMd6/Eyd9MhOeuWu/9QZM8cLbI1Q2NpVa4k=
*/