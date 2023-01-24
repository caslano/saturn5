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
p/XXGwTILfthVmPvbwwgA/ZLgLR/gQBSMIUBciG+ev0UHSAP3GcBpEtYPYA8cnUoQL7dJwBy59UKIDvu1QCSbAFE8radDm1GggS9gO1x8nhUMMlWnOBNvfWl3uB6mPxUMfkgTr54H8xg3NTGJj9qn5x8x+dp8ndO5sn3wVfHTtap70P3WupxHxv1hYPXZoVPp77gGD+2V0z+bp+a/OfFZCdL0k8gakzrJ22A4BZ/qZgpaCrTStx9ioImq7vJkoImqPsx2n3LFpZM1DUdqOuffZC65oZmEuv+hKStnZ5g+jcXw+0+pp+lTHH/S5eL5tHlQnFpduyAxHEON3kc7sXQvVK+VwL3/myP9+6a24CNqexnwRAipx5RVDRXnTXCFLdvUEgOkNImYSzTNw3TxG9bdFBlEcIwXOZahExGCOxvQVsWQney01VR7dCpEGYPqXJfg/j/9FRUXSugVILMzBZNx0EgfZBMfTuf3knZLx3OTyxAh3MRMc8EZvS76eES8bDuNjiccYvQDycRtxeqzs+T9PIFLYqsQ3qZNnxLgNw97sEhlT78u03HYEK2BNrHdP67yr1onxzWD6JnmICg7Qk+mkD1YjaAfG8YKs9dNMuRn/r8n+MsWYbcaFgyZFEX+SWv/zP1JWq3WG9XP9NdAtO7tZPpJGOCZWQXeP/mZCtgY/lkimAbm5igZcHrm4q4m1dfMpj4L4m94//FOaDn
*/