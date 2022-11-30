//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Stephen Cleary 2000.
// (C) Copyright Ion Gaztanaga 2007-2013.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//    http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
// This file is a slightly modified file from Boost.Pool
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_MATH_FUNCTIONS_HPP
#define BOOST_CONTAINER_DETAIL_MATH_FUNCTIONS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

#include <climits>
#include <boost/static_assert.hpp>

namespace boost {
namespace container {
namespace dtl {

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

template <typename Integer, bool Loop = true>
struct upper_power_of_2_loop_ct
{

   template <Integer I, Integer P>
   struct apply
   {
      static const Integer value =
         upper_power_of_2_loop_ct<Integer, (I > P*2)>::template apply<I, P*2>::value;
   };
};

template <typename Integer>
struct upper_power_of_2_loop_ct<Integer, false>
{
   template <Integer I, Integer P>
   struct apply
   {
      static const Integer value = P;
   };
};

template <typename Integer, Integer I>
struct upper_power_of_2_ct
{
   static const Integer value = upper_power_of_2_loop_ct<Integer, (I > 1)>::template apply<I, 2>::value;
};

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

template<std::size_t I1, std::size_t I2>
struct gcd_ct
{
   static const std::size_t Max = I1 > I2 ? I1 : I2;
   static const std::size_t Min = I1 < I2 ? I1 : I2;
   static const std::size_t value = gcd_ct<Min, Max % Min>::value;
};

template<std::size_t I1>
struct gcd_ct<I1, 0>
{
   static const std::size_t value = I1;
};

template<std::size_t I1>
struct gcd_ct<0, I1>
{
   static const std::size_t value = I1;
};

template<std::size_t I1, std::size_t I2>
struct lcm_ct
{
   static const std::size_t value = I1 * I2 / gcd_ct<I1, I2>::value;
};

} // namespace dtl
} // namespace container
} // namespace boost

#include <boost/container/detail/config_end.hpp>

#endif

/* math_functions.hpp
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
*/