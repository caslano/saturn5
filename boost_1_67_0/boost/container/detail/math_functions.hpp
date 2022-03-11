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