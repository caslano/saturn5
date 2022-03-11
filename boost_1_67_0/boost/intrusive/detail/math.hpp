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
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
*/