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
styiLAg0hyGYwPg/2EB0LdeWO3Fbg8zMB92ZGYEDEkprrkS1L22rcPWrsoV9YgCk/h0qvXgpjQa9OMugunA/W0WSevqySKJEB2OqzKxEUxDXLkXvsXTFbslg/iCfiJ6ls28Mzw3xqgM6iK+yOAiNc8fcgmge51GYSw1SUb+ROh1qEMRJR/HLlMyymkQPLYJaZAQrjiNer2IL9p4AG0i/zWkFx1iGioD6LCjte8j0jtdqHqW7IAycHkzNm4Td6yM=
*/