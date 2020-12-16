/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_MATH_HPP
#define BOOST_INTRUSIVE_DETAIL_MATH_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <cstddef>
#include <climits>
#include <boost/intrusive/detail/mpl.hpp>

namespace boost {
namespace intrusive {
namespace detail {

///////////////////////////
// floor_log2  Dispatcher
////////////////////////////

#if defined(_MSC_VER) && (_MSC_VER >= 1300)

   }}} //namespace boost::intrusive::detail

   //Use _BitScanReverseXX intrinsics

   #if defined(_M_X64) || defined(_M_AMD64) || defined(_M_IA64)   //64 bit target
      #define BOOST_INTRUSIVE_BSR_INTRINSIC_64_BIT
   #endif

   #ifndef __INTRIN_H_   // Avoid including any windows system header
      #ifdef __cplusplus
      extern "C" {
      #endif // __cplusplus

      #if defined(BOOST_INTRUSIVE_BSR_INTRINSIC_64_BIT)   //64 bit target
         unsigned char _BitScanReverse64(unsigned long *index, unsigned __int64 mask);
         #pragma intrinsic(_BitScanReverse64)
      #else //32 bit target
         unsigned char _BitScanReverse(unsigned long *index, unsigned long mask);
         #pragma intrinsic(_BitScanReverse)
      #endif

      #ifdef __cplusplus
      }
      #endif // __cplusplus
   #endif // __INTRIN_H_

   #ifdef BOOST_INTRUSIVE_BSR_INTRINSIC_64_BIT
      #define BOOST_INTRUSIVE_BSR_INTRINSIC _BitScanReverse64
      #undef BOOST_INTRUSIVE_BSR_INTRINSIC_64_BIT
   #else
      #define BOOST_INTRUSIVE_BSR_INTRINSIC _BitScanReverse
   #endif

   namespace boost {
   namespace intrusive {
   namespace detail {

   inline std::size_t floor_log2 (std::size_t x)
   {
      unsigned long log2;
      BOOST_INTRUSIVE_BSR_INTRINSIC( &log2, (unsigned long)x );
      return log2;
   }

   #undef BOOST_INTRUSIVE_BSR_INTRINSIC

#elif defined(__GNUC__) && ((__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)) //GCC >=3.4

   //Compile-time error in case of missing specialization
   template<class Uint>
   struct builtin_clz_dispatch;

   #if defined(BOOST_HAS_LONG_LONG)
   template<>
   struct builtin_clz_dispatch< ::boost::ulong_long_type >
   {
      static ::boost::ulong_long_type call(::boost::ulong_long_type n)
      {  return __builtin_clzll(n); }
   };
   #endif

   template<>
   struct builtin_clz_dispatch<unsigned long>
   {
      static unsigned long call(unsigned long n)
      {  return __builtin_clzl(n); }
   };

   template<>
   struct builtin_clz_dispatch<unsigned int>
   {
      static unsigned int call(unsigned int n)
      {  return __builtin_clz(n); }
   };

   inline std::size_t floor_log2(std::size_t n)
   {
      return sizeof(std::size_t)*CHAR_BIT - std::size_t(1) - builtin_clz_dispatch<std::size_t>::call(n);
   }

#else //Portable methods

////////////////////////////
// Generic method
////////////////////////////

   inline std::size_t floor_log2_get_shift(std::size_t n, true_ )//power of two size_t
   {  return n >> 1;  }

   inline std::size_t floor_log2_get_shift(std::size_t n, false_ )//non-power of two size_t
   {  return (n >> 1) + ((n & 1u) & (n != 1)); }

   template<std::size_t N>
   inline std::size_t floor_log2 (std::size_t x, integral_constant<std::size_t, N>)
   {
      const std::size_t Bits = N;
      const bool Size_t_Bits_Power_2= !(Bits & (Bits-1));

      std::size_t n = x;
      std::size_t log2 = 0;

      std::size_t remaining_bits = Bits;
      std::size_t shift = floor_log2_get_shift(remaining_bits, bool_<Size_t_Bits_Power_2>());
      while(shift){
         std::size_t tmp = n >> shift;
         if (tmp){
            log2 += shift, n = tmp;
         }
         shift = floor_log2_get_shift(shift, bool_<Size_t_Bits_Power_2>());
      }

      return log2;
   }

   ////////////////////////////
   // DeBruijn method
   ////////////////////////////

   //Taken from:
   //http://stackoverflow.com/questions/11376288/fast-computing-of-log2-for-64-bit-integers
   //Thanks to Desmond Hume

   inline std::size_t floor_log2 (std::size_t v, integral_constant<std::size_t, 32>)
   {
      static const int MultiplyDeBruijnBitPosition[32] =
      {
         0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
         8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
      };

      v |= v >> 1;
      v |= v >> 2;
      v |= v >> 4;
      v |= v >> 8;
      v |= v >> 16;

      return MultiplyDeBruijnBitPosition[(std::size_t)(v * 0x07C4ACDDU) >> 27];
   }

   inline std::size_t floor_log2 (std::size_t v, integral_constant<std::size_t, 64>)
   {
      static const std::size_t MultiplyDeBruijnBitPosition[64] = {
      63,  0, 58,  1, 59, 47, 53,  2,
      60, 39, 48, 27, 54, 33, 42,  3,
      61, 51, 37, 40, 49, 18, 28, 20,
      55, 30, 34, 11, 43, 14, 22,  4,
      62, 57, 46, 52, 38, 26, 32, 41,
      50, 36, 17, 19, 29, 10, 13, 21,
      56, 45, 25, 31, 35, 16,  9, 12,
      44, 24, 15,  8, 23,  7,  6,  5};

      v |= v >> 1;
      v |= v >> 2;
      v |= v >> 4;
      v |= v >> 8;
      v |= v >> 16;
      v |= v >> 32;
      return MultiplyDeBruijnBitPosition[((std::size_t)((v - (v >> 1))*0x07EDD5E59A4E28C2ULL)) >> 58];
   }


   inline std::size_t floor_log2 (std::size_t x)
   {
      const std::size_t Bits = sizeof(std::size_t)*CHAR_BIT;
      return floor_log2(x, integral_constant<std::size_t, Bits>());
   }

#endif

//Thanks to Laurent de Soras in
//http://www.flipcode.com/archives/Fast_log_Function.shtml
inline float fast_log2 (float val)
{
   union caster_t
   {
      unsigned x;
      float val;
   } caster;

   caster.val = val;
   unsigned x = caster.x;
   const int log_2 = int((x >> 23) & 255) - 128;
   x &= ~(unsigned(255u) << 23u);
   x += unsigned(127) << 23u;
   caster.x = x;
   val = caster.val;
   //1+log2(m), m ranging from 1 to 2
   //3rd degree polynomial keeping first derivate continuity.
   //For less precision the line can be commented out
   val = ((-1.f/3.f) * val + 2.f) * val - (2.f/3.f);
   return val + static_cast<float>(log_2);
}

inline bool is_pow2(std::size_t x)
{  return (x & (x-1)) == 0;  }

template<std::size_t N>
struct static_is_pow2
{
   static const bool value = (N & (N-1)) == 0;
};

inline std::size_t ceil_log2 (std::size_t x)
{
   return static_cast<std::size_t>(!(is_pow2)(x)) + floor_log2(x);
}

inline std::size_t ceil_pow2 (std::size_t x)
{
   return std::size_t(1u) << (ceil_log2)(x);
}

inline std::size_t previous_or_equal_pow2(std::size_t x)
{
   return std::size_t(1u) << floor_log2(x);
}

template<class SizeType, std::size_t N>
struct numbits_eq
{
   static const bool value = sizeof(SizeType)*CHAR_BIT == N;
};

template<class SizeType, class Enabler = void >
struct sqrt2_pow_max;

template <class SizeType>
struct sqrt2_pow_max<SizeType, typename voider<typename enable_if< numbits_eq<SizeType, 32> >::type>::type>
{
   static const SizeType value = 0xb504f334;
   static const std::size_t pow   = 31;
};

#ifndef BOOST_NO_INT64_T

template <class SizeType>
struct sqrt2_pow_max<SizeType, typename voider<typename enable_if< numbits_eq<SizeType, 64> >::type>::type>
{
   static const SizeType value = 0xb504f333f9de6484ull;
   static const std::size_t pow   = 63;
};

#endif   //BOOST_NO_INT64_T

// Returns floor(pow(sqrt(2), x * 2 + 1)).
// Defined for X from 0 up to the number of bits in size_t minus 1.
inline std::size_t sqrt2_pow_2xplus1 (std::size_t x)
{
   const std::size_t value = (std::size_t)sqrt2_pow_max<std::size_t>::value;
   const std::size_t pow   = (std::size_t)sqrt2_pow_max<std::size_t>::pow;
   return (value >> (pow - x)) + 1;
}

} //namespace detail
} //namespace intrusive
} //namespace boost

#endif //BOOST_INTRUSIVE_DETAIL_MATH_HPP

/* math.hpp
Jz587yW54W2xnSXyf1v2Rodx5ReMGzjz7G6/WPPgmeFturnPbw03X7XpNs6aagPO3SZa022xudtQCzevtunzYY/VPFzDVpo8F+fDzrh99b/le34M8bdb93/j93vG778Yvz8w4r5j/H7X+P228du/tlvHCnVcdm3Q2u51utbwDthG12ym6FrO4+BWvfTv1rm898DTNPx0eL+uBX0ATtc1nvm6xnOxruGshj+Fa1TuZvXfCrfAe3UN5wPqf0jXguI8z8BaTe8XcDP8pa79/LX6X4Y/g6+p3B5dK7o3aO3o+/Ax+IH6D8BH4V81/Eu4Cf5T9XwGdznjSjKGJfXXAbcN51HbSl7YGbaGGTBZbSmlw26wn/oHwe5wPDxJbTb1hCWwF/y+2FrSNdTwR3AArIED4dNwENwKB8NatUn3W3gK3KfhVnmHw2QydhpMh6fDIfAMXftY5YwbMB6i7SIBV4rz6BpRi6tga10rmqxrRTvo2uE0uBqeCK+HGXAN7K3HT4Y3wGHwRzBLw23bWLWafrTWq2kb6xPkpH+H7eDfYEd4CPaDX2j7+xKOUbkJumYz2wKcBaPUppwPLoMt4GqVuwHEqu2rNnADbAs3wUSt73bwd7C92sBqq/XbQW3LpcH34Nek/5Ha8vtEj3+txw/DeEhe8Ota/ij9dqvfndfCUbhuUfU2J9rAVIjzdNR6pk05tiLGqW2IIngSnA97wRWwt15nfeAzahPiTzBT2/0AOMrr90+Alr8YDoSVGl6t4ddq+Dp4CnwYDoXb4HC4A54KX4anwffgGfATeCb0RdHGYAc4CqbDMbAPHAeHw4kwF06Fc2A2LILT4UUwBy6E58IymAur4Wx4FTwPXgPnwGvhhXA1nAd/rPI1sATeAy+Cj8Iy+AQsh7+HF8O/wMXwTXgB3A/z4LswH34I58K/wkL4KVwAv4GlMDGa6wumwmWwC7wE9oKXwmFwORwHL4Mz4RXwfFjN/wVwCbwILoXlEq5rlr36LU6/Da6FXXDJ2p8/j1w8rNXr9ld63WyH/eGL2n/v0LXsv4ZjNHy8+nPgb7Qf3wnnwpdgudpqq1Jbbddp+Fq11XYf3A03wFfhJrXVthm+BrfAP2l//me4De6FO+Ab8FW1KbkPvgnfgji5vt6GX8N3YEfKSpj0ax/AHvBD2B9+ZNeT/T1Fn1VjvIFru7fXy9FoIpNLjFAuPUK5TEMuH2fKdTbksiKUy45QLj9CufII5aobkTvg9a+hz8I1tFY+ZwFrqWHwOvkqwtfjahf4Il4z/+9cL19pccuRr5c/0rXyR7JOXtfIN7A+HlLPh3CJpawtx2XjSnGrcJtwe3CehayVx+XgluM24HbhvlrYvJ6q+a/5r/mv+a/5r/mvKX/f9fz/Cv7PW1q8uOTCZXmFlVXWEoCjnv//WYrH2Tv5pmidX+lFH8yCmbyopk/xz1mYkTd9zLS8yrI8fp07ZvrZY2fljcrJ9X8T75fh35OK9y9nvn53iXead6418iyzC1znWap+r+jpI3oonTGn5WQ5Psg72xPN94gWvCu1cB/7CtJjzqXqAPvK8QW8c5/izImaLmGtvYN58z3oiZK5NYP9MzjKSksKl3k0vhV0nsh+j9lJ54lcsqRRslA2MTLG2n8jcinOfJly8X/MM3Wt5O1L0b+ojH0DHd0nTkUGy5GtPW1FZqjILKyYZ+j9i+jJc9XbUeee10XxrYUKiZ7f0hfdnl2v0ny6/7ez/7tRP9SzsT/qOtHXPWzdmHPcE2grh6x0VnQjkcSWdhqfE7Ze5wP0JiyWsIeS/OFj2/v5Be7Zdv55Olvhn5ManxtszRGgvCFzBGh31DTtzhgT6CNhUraAvcFX+QI=
*/