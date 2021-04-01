#ifndef BOOST_ENDIAN_DETAIL_ORDER_HPP_INCLUDED
#define BOOST_ENDIAN_DETAIL_ORDER_HPP_INCLUDED

// Copyright 2019 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/core/scoped_enum.hpp>

#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

# define BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER little

#elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

# define BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER big

#elif defined(__BYTE_ORDER__) && defined(__ORDER_PDP_ENDIAN__) && __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__

# error The Boost.Endian library does not support platforms with PDP endianness.

#elif defined(__LITTLE_ENDIAN__)

# define BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER little

#elif defined(__BIG_ENDIAN__)

# define BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER big

#elif defined(_MSC_VER) || defined(__i386__) || defined(__x86_64__)

# define BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER little

#else

# error The Boost.Endian library could not determine the endianness of this platform.

#endif

namespace boost
{
namespace endian
{

BOOST_SCOPED_ENUM_START(order)
{
    big,
    little,
    native = BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER

}; BOOST_SCOPED_ENUM_END

} // namespace endian
} // namespace boost

#undef BOOST_ENDIAN_NATIVE_ORDER_INITIALIZER

#endif  // BOOST_ENDIAN_DETAIL_ORDER_HPP_INCLUDED

/* order.hpp
avq61L+aG6QvKy3IKx/QOI8bU6ZH4p80EmJk+M0HVSlh1CR0ECoW9aSyrkPxLaBezJT8jLm1uitFkpPn1NJRyvZEwjcOukevowUxG7NbQqxmudvC12DZr1GLdB78khxiznOQvmgUekqqL40DSwduAZFP4qz+a6600neyWAZYv7LwL/8+/w+AY3mU/5LsxD2XD8Cf2cWDmQURDTJCGcG/l+ixEAAqTZAfFAw6Q8t1fBlj203UfhqOtwe2FyuQtluw4Lzg+0UjQ+xC/icDgGNpe/m2pFvjz88/QQVytvALWiBfnil0mMjdZaX7ZxF/spGBFe6H0PH/XFOUw/30xakru2qniH0oricBJfmbDY6rl2rKDY0c3IOuOVfhDLHaS73q9IBY5RFBA7J/cvuqZZAdOIB61Ws5cwB9YBhc5TYoI4f7UZQULSLlDp7zL9dVLx61xPe9lLtX/vm8Qb3l70k5WCZ0icp7sZ4BN6seWx/d55cRwUZUocg+C6QGjgmgsUd5/2TxG+Y2F8EZyvYTPuyrBRS2Ph0VnGIqalDQhUW78NvX9Fq40+P0WWJj1Q==
*/