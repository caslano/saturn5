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