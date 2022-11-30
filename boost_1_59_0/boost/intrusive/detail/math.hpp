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
#include <cstring>

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
      BOOST_INTRUSIVE_BSR_INTRINSIC( &log2, x );
      return static_cast<std::size_t>(log2);
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
      {  return (::boost::ulong_long_type)__builtin_clzll(n); }
   };
   #endif

   template<>
   struct builtin_clz_dispatch<unsigned long>
   {
      static unsigned long call(unsigned long n)
      {  return (unsigned long)__builtin_clzl(n); }
   };

   template<>
   struct builtin_clz_dispatch<unsigned int>
   {
      static unsigned int call(unsigned int n)
      {  return (unsigned int)__builtin_clz(n); }
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
   unsigned x;
   std::memcpy(&x, &val, sizeof(float));
   const int log_2 = int((x >> 23) & 255) - 128;
   x &= ~(unsigned(255u) << 23u);
   x += unsigned(127) << 23u;
   std::memcpy(&val, &x, sizeof(float));
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