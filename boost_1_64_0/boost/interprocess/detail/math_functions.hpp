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
ZdGxoVSKeN+D1juphw+j7MVAkamTXgvFl+KrQ9vx2NFEq6ZokioIBQGxoadn2jn1tU7oaDqbaWdIjCpuJetyBJSMwz3EVxWLJqVDxo+7Lt6NGUI+B2RlV5lfT3gOqZQG+mNzXG6ANYTJdT/VYtSAN8BDKtyMfNGHyqfmZD1ZM3LKEmGdrfFWI+yU+1mOmrf/ZAgK4cev5AwvU3Y+z1HBVRqpojc5WKRf20kjeDkNL34W3xdjD6PyRZ8l1J1IGFqoUY/3amUchIBCIlSBd8PBHoYIzH6l7Yd9hSDArDpfKKdOCvYcimuj04jBx5RkevvX/QA5NPDF1AVBlskOslM1omR0/LxAm+Hfke9ZlvdDFcig8KSAg05tCZQJ49bdIxvoqYblYotMXJxzcjECZImd1bXYatsz5BcPCuZ+HZbdZA2016++kXJOm6y6E6HZPn9tR63D+O7SBGGjSDmmNyy+t9WueHtVncovWJ0dX/1x+O5PRjlVk2NND/lYBHJtV/KamSnFkk+wtA5hnNsqmMjyuCGXyZ3MjDWyPamSIzo34Lc3JQ9oQeJ+T3blJQ==
*/