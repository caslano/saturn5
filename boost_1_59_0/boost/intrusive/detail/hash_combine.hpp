// Copyright 2005-2014 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  Based on Peter Dimov's proposal
//  http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2005/n1756.pdf
//  issue 6.18.
//
//  This also contains public domain code from MurmurHash. From the
//  MurmurHash header:
//
// MurmurHash3 was written by Austin Appleby, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.
//
// Copyright 2021 Ion Gaztanaga
// Refactored the original boost/container_hash/hash.hpp to avoid
// any heavy std header dependencies to just combine two hash
// values represented in a std::size_t type.

#ifndef BOOST_INTRUSIVE_DETAIL_HASH_COMBINE_HPP
#define BOOST_INTRUSIVE_DETAIL_HASH_COMBINE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/cstdint.hpp>

#if defined(_MSC_VER)
#  include <stdlib.h>
#  define BOOST_INTRUSIVE_HASH_ROTL32(x, r) _rotl(x,r)
#else
#  define BOOST_INTRUSIVE_HASH_ROTL32(x, r) (x << r) | (x >> (32 - r))
#endif

namespace boost {
namespace intrusive {
namespace detail {

template <typename SizeT>
inline void hash_combine_size_t(SizeT& seed, SizeT value)
{
   seed ^= value + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

inline void hash_combine_size_t(boost::uint32_t& h1, boost::uint32_t k1)
{
   const uint32_t c1 = 0xcc9e2d51;
   const uint32_t c2 = 0x1b873593;

   k1 *= c1;
   k1 = BOOST_INTRUSIVE_HASH_ROTL32(k1,15);
   k1 *= c2;

   h1 ^= k1;
   h1 = BOOST_INTRUSIVE_HASH_ROTL32(h1,13);
   h1 = h1*5+0xe6546b64;
}


   // Don't define 64-bit hash combine on platforms without 64 bit integers,
   // and also not for 32-bit gcc as it warns about the 64-bit constant.
   #if !defined(BOOST_NO_INT64_T) && \
       !(defined(__GNUC__) && ULONG_MAX == 0xffffffff)
   inline void hash_combine_size_t(boost::uint64_t& h, boost::uint64_t k)
   {
      const boost::uint64_t m = UINT64_C(0xc6a4a7935bd1e995);
      const int r = 47;

      k *= m;
      k ^= k >> r;
      k *= m;

      h ^= k;
      h *= m;

      // Completely arbitrary number, to prevent 0's
      // from hashing to 0.
      h += 0xe6546b64;
   }

   #endif // BOOST_NO_INT64_T

}  //namespace detail {
}  //namespace intrusive {
}  //namespace boost {

#endif   //BOOST_INTRUSIVE_DETAIL_HASH_COMBINE_HPP

/* hash_combine.hpp
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
*/