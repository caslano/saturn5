// (C) Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef ITERATOR_DWA122600_HPP_
#define ITERATOR_DWA122600_HPP_

// This header is obsolete and will be deprecated.

#include <iterator>
#if defined(__SUNPRO_CC) && (defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION))
#include <cstddef>
#endif

namespace boost
{

namespace detail
{

using std::iterator_traits;
using std::distance;

#if defined(__SUNPRO_CC) && (defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION))
// std::distance from stlport with Oracle compiler 12.4 and 12.5 fails to deduce template parameters
// when one of the arguments is an array and the other one is a pointer.
template< typename T, std::size_t N >
inline typename std::iterator_traits< T* >::difference_type distance(T (&left)[N], T* right)
{
    return std::distance(static_cast< T* >(left), right);
}
#endif

} // namespace detail

} // namespace boost

#endif // ITERATOR_DWA122600_HPP_

/* iterator.hpp
JkafeCHqvZkMxdhWj1Dc0XKELG0RfSEIma6509s4mC6DGI1K0ZnLoRzcnnfcEMDaCoXgw2B3OQaQYIwHYxh/p1kWZcCwqSkEv0nAye51CNeogAl2Y0C74Z4BJGKIVcioveMWFbtURKy0L+gB2fssRkWMHiQk/v2AWIMinPXDziVeQjQac8NiEZ85b/r0XVFgbNZKvE2AFURtDKpFfWlu3a8wRWhHPla4jXDUB9tryr08DegZBoVk5Sy38I7A9ywSIfM+ULMtUQ+Xm047g16duqtgac1XQWAMiyhchrMwiC23qgCneYRXE/YIGallJitldnl/uReLwLOcurB64TSK/35PVqnBY1RFUYzJOIF/LXjYUPrzFhceyDEZ7mUYHzaMdm8X/Ibhjccd5Nd0NCF3CuMY3Xu/D6ATtNwtV7zGVWoE6eiduZ/5ezic6RNqenA1/DzcA0AsOejFoI99Iw5DZxVnddfslv6znEKYFrsfXT9wj/3AX64tN897STm8WwdB3FPwrmlkq++FM2x4TTdnyrLPvM5VP/XIW66iOXx0g5VnRYbSCnpdCM931H4kqj1sWs3P5+GneRKai44cEOw2vopYQ5DVMglPkwvvIozWQzwU4WuDPYUUEJngNdKDswZFimW8r2sUex64QRzi
*/