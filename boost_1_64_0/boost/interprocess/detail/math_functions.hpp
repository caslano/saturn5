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
72zmJlshnyDML2i9UFlMY9URlmKBQJhf8niGaf2x0vfKFiy5+QjnSr6oPIqxoXOPmS0Oeh24Bllyig1baOzaevYtdA8PD8GsTdsXOj9g83JDfdMXFHh/Zea9fTPs3HhkX1OM+3sXKMZjKxcyy/XDsd88V/cixTguFyvGc3Uv8Vi2+HY414/hAv96lPPa+UujnMO/TPJ5ZjbtoD9f9nLN3Tv5CsV4vuyVzOhk3u7+Xjqdl/biAd9VE/jkfNdvTOSjvujVE3hkH/sa9g3lzLhJwc1vxntdG+VjVL1pvXTMI9dLRznPt7whytPE1okbHYdqnesV9fMmxbh+flMxvue3AjbECYf8u1lzmXD3HP121Md17pYo5zr3nSjn58p345z3R/Z5UHExjFs7eWgv59s6cHmu0+3sMc9t7MZXRiAe2XZCML8F1mV7vknko1pOYd3heciSTappJTXaZxfCujPqS8fNvUrFBo2xxzxt3i/gh4677m5ltFIq2u/JdwXcnvHzI19vJqVKo5Lw+ue7O3Acr8Qwfux7eOojhXGP5olIAq7RjnialI8/dQzSZYq8Pk4OGw0I4172USZDycJ7+j7BzMwG8N/PWva6703EevQHfOadPfigz9zZUA/5+jy5zvthZtTrxLT9zOlYdzB1nDkp9WcfEb52A8N8lDXqoaL+c9ZHId4Uxi+czu+ox5wGbZ6yFfuIj3uM42Tbyi99TjOoi9msXJN0Xqf3hOdT5Y/nFWsPlS6t3w44NQ5cv+0Y7ynzpNN4TsdTTsO1L3QeIdz/aWap/bmMOyYhf8bjsnww7GeZ8zHZxH7rM6qbyJ7zmP/8eF4ynW9u3/UXPB9EHdd5Ox2uxfF7X5ONDfjLjnM7xoqM/BXJxxvVxBUFrQF33P9m/irrrXphOG/+G4ZHPKXhNcepi0115/eg6y+q8rn/eicPPfff6MDlvOI32UM/zWGSKcTtD465tgv6H53ut7+3nO7aDZTnn1hvmBuoE67c/si+DxqmrafvRBiEkdJYfcBTw209edcxkLMOPO6PDDrv3TZoek8DvdzffC/K+d3/fpRzu/sA+MDsvp4FouhoXXfAKpSHf/N1993n76wfNrd7tgiP1nRr7vqu/9TMrcH+FzO9Ww6l899xjwkf+X+inNc2fij4nO7BQbMgya03X24Nxbx0La+5S9cKmrk++YrAhgbmL8BhF0g07NeX7xvo537gShP73DndK0/o4zJfhX0UM+7LrqoY92VXU4z3G1o9Y0Omf28n39Gzfg2nmxZF2ppWw0lZoK3ltGSxeQBDmGs7bbRSTWBtC5THOlbHw0PNSw0OyKjbuVPrWg6TfuFiuMd6Tm/Uq1VM0/qspUm7XMcoYTgbOJaWTAbV7Lt6Q9aThNaHb8SajZNZXlGp2efgxsyjcd7Eclpz4cbBrY6DIpgYYpsB6+mS29FZtjkxfzs6vNcWlpUT75otSfe3qcNrtiIW3mdrq9f1fbYhZk9lsfuKbYs672FMf7vt7EjfjnR3PeX/9qD3mZGiXrNXKMZjB08reH3CHX3WZ88n2cnT5U5iGObOPvfOq94FmByJg74fsI9qxmuhkdHIHF1GbFfF+PfrbsQKA925wQJM+/T2y9g9ximde0SYfL/uSRzeP5NcA4ZrP+5YPi9uy+uhNXfPvkmK8fO2y7L5+02eZM+TS5bA836yx8YS0wEy2ZjVAOOg++7tebKlGoWKfb5MIQanvJB/H6dVK7Vy9nPRLBIltq9mNVt3phKj5ZImDnjNfkrnuO1PzDs0nOJ2ADFUUTuQNFmeB5HmJZ/qwicUo9sTP5g4raZrulN3KOxDJKfHlGXdHhstllr1Zkp5MU0yEZ8e0uU=
*/