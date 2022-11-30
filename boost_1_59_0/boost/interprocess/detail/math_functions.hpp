//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Stephen Cleary 2000.
// (C) Copyright Ion Gaztanaga 2007-2012.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//    http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
// This file is a slightly modified file from Boost.Pool
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_MATH_FUNCTIONS_HPP
#define BOOST_INTERPROCESS_DETAIL_MATH_FUNCTIONS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <climits>
#include <boost/static_assert.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

// Greatest common divisor and least common multiple

//
// gcd is an algorithm that calculates the greatest common divisor of two
//  integers, using Euclid's algorithm.
//
// Pre: A > 0 && B > 0
// Recommended: A > B
template <typename Integer>
inline Integer gcd(Integer A, Integer B)
{
   do
   {
      const Integer tmp(B);
      B = A % B;
      A = tmp;
   } while (B != 0);

   return A;
}

//
// lcm is an algorithm that calculates the least common multiple of two
//  integers.
//
// Pre: A > 0 && B > 0
// Recommended: A > B
template <typename Integer>
inline Integer lcm(const Integer & A, const Integer & B)
{
   Integer ret = A;
   ret /= gcd(A, B);
   ret *= B;
   return ret;
}

template <typename Integer>
inline Integer log2_ceil(const Integer & A)
{
   Integer i = 0;
   Integer power_of_2 = 1;

   while(power_of_2 < A){
      power_of_2 <<= 1;
      ++i;
   }
   return i;
}

template <typename Integer>
inline Integer upper_power_of_2(const Integer & A)
{
   Integer power_of_2 = 1;

   while(power_of_2 < A){
      power_of_2 <<= 1;
   }
   return power_of_2;
}

//This function uses binary search to discover the
//highest set bit of the integer
inline std::size_t floor_log2 (std::size_t x)
{
   const std::size_t Bits = sizeof(std::size_t)*CHAR_BIT;
   const bool Size_t_Bits_Power_2= !(Bits & (Bits-1));
   BOOST_STATIC_ASSERT(((Size_t_Bits_Power_2)== true));

   std::size_t n = x;
   std::size_t log2 = 0;

   for(std::size_t shift = Bits >> 1; shift; shift >>= 1){
      std::size_t tmp = n >> shift;
      if (tmp)
         log2 += shift, n = tmp;
   }

   return log2;
}

} // namespace ipcdetail
} // namespace interprocess
} // namespace boost

#endif

/* math_functions.hpp
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
*/