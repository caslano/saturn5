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
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
*/