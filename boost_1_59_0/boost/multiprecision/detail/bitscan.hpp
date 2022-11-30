///////////////////////////////////////////////////////////////
//  Copyright 2013 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt
//
// Comparison operators for cpp_int_backend:
//
#ifndef BOOST_MP_DETAIL_BITSCAN_HPP
#define BOOST_MP_DETAIL_BITSCAN_HPP

#include <cstdint>
#include <climits>
#include <type_traits>
#include <boost/multiprecision/detail/endian.hpp>
#include <boost/multiprecision/detail/standalone_config.hpp>

#if (defined(BOOST_MSVC) || (defined(__clang__) && defined(__c2__)) || (defined(BOOST_INTEL) && defined(_MSC_VER))) && (defined(_M_IX86) || defined(_M_X64))
#include <intrin.h>
#endif

namespace boost { namespace multiprecision { namespace detail {

template <class Unsigned>
inline BOOST_MP_CXX14_CONSTEXPR std::size_t find_lsb_default(Unsigned mask)
{
   std::size_t result = 0;
   while (!(mask & 1u))
   {
      mask >>= 1;
      ++result;
   }
   return result;
}

template <class Unsigned>
inline BOOST_MP_CXX14_CONSTEXPR std::size_t find_msb_default(Unsigned mask)
{
   std::size_t index = 0;
   while (mask)
   {
      ++index;
      mask >>= 1;
   }
   return --index;
}

template <class Unsigned>
inline BOOST_MP_CXX14_CONSTEXPR std::size_t find_lsb(Unsigned mask, const std::integral_constant<int, 0>&)
{
   return find_lsb_default(mask);
}

template <class Unsigned>
inline BOOST_MP_CXX14_CONSTEXPR std::size_t find_msb(Unsigned mask, const std::integral_constant<int, 0>&)
{
   return find_msb_default(mask);
}

#if (defined(BOOST_MSVC) || (defined(__clang__) && defined(__c2__)) || (defined(BOOST_INTEL) && defined(_MSC_VER))) && (defined(_M_IX86) || defined(_M_X64))

#pragma intrinsic(_BitScanForward, _BitScanReverse)

BOOST_FORCEINLINE std::size_t find_lsb(unsigned long mask, const std::integral_constant<int, 1>&)
{
   unsigned long result;
   _BitScanForward(&result, mask);
   return result;
}

BOOST_FORCEINLINE std::size_t find_msb(unsigned long mask, const std::integral_constant<int, 1>&)
{
   unsigned long result;
   _BitScanReverse(&result, mask);
   return result;
}
#ifdef _M_X64

#pragma intrinsic(_BitScanForward64, _BitScanReverse64)

BOOST_FORCEINLINE std::size_t find_lsb(unsigned __int64 mask, const std::integral_constant<int, 2>&)
{
   unsigned long result;
   _BitScanForward64(&result, mask);
   return result;
}
template <class Unsigned>
BOOST_FORCEINLINE std::size_t find_msb(Unsigned mask, const std::integral_constant<int, 2>&)
{
   unsigned long result;
   _BitScanReverse64(&result, mask);
   return result;
}
#endif

template <class Unsigned>
BOOST_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR std::size_t find_lsb(Unsigned mask)
{
   using ui_type = typename boost::multiprecision::detail::make_unsigned<Unsigned>::type;
   using tag_type = typename std::conditional<
       sizeof(Unsigned) <= sizeof(unsigned long),
       std::integral_constant<int, 1>,
#ifdef _M_X64
       typename std::conditional<
           sizeof(Unsigned) <= sizeof(__int64),
           std::integral_constant<int, 2>,
           std::integral_constant<int, 0> >::type
#else
       std::integral_constant<int, 0>
#endif
       >::type;
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
   if (BOOST_MP_IS_CONST_EVALUATED(mask))
   {
      return find_lsb_default(mask);
   }
   else
#endif
      return find_lsb(static_cast<ui_type>(mask), tag_type());
}

template <class Unsigned>
BOOST_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR std::size_t find_msb(Unsigned mask)
{
   using ui_type = typename boost::multiprecision::detail::make_unsigned<Unsigned>::type;
   using tag_type = typename std::conditional<
       sizeof(Unsigned) <= sizeof(unsigned long),
       std::integral_constant<int, 1>,
#ifdef _M_X64
       typename std::conditional<
           sizeof(Unsigned) <= sizeof(__int64),
           std::integral_constant<int, 2>,
           std::integral_constant<int, 0> >::type
#else
       std::integral_constant<int, 0>
#endif
       >::type;
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
   if (BOOST_MP_IS_CONST_EVALUATED(mask))
   {
      return find_msb_default(mask);
   }
   else
#endif
      return find_msb(static_cast<ui_type>(mask), tag_type());
}

#elif defined(BOOST_GCC) || defined(__clang__) || (defined(BOOST_INTEL) && defined(__GNUC__))

BOOST_FORCEINLINE std::size_t find_lsb(std::size_t mask, std::integral_constant<int, 1> const&)
{
   return __builtin_ctz(mask);
}
BOOST_FORCEINLINE std::size_t find_lsb(unsigned long mask, std::integral_constant<int, 2> const&)
{
   return __builtin_ctzl(mask);
}
BOOST_FORCEINLINE std::size_t find_lsb(unsigned long long mask, std::integral_constant<int, 3> const&)
{
   return __builtin_ctzll(mask);
}
BOOST_FORCEINLINE std::size_t find_msb(std::size_t mask, std::integral_constant<int, 1> const&)
{
   return sizeof(unsigned) * CHAR_BIT - 1 - __builtin_clz(mask);
}
BOOST_FORCEINLINE std::size_t find_msb(unsigned long mask, std::integral_constant<int, 2> const&)
{
   return sizeof(unsigned long) * CHAR_BIT - 1 - __builtin_clzl(mask);
}
BOOST_FORCEINLINE std::size_t find_msb(unsigned long long mask, std::integral_constant<int, 3> const&)
{
   return sizeof(unsigned long long) * CHAR_BIT - 1 - __builtin_clzll(mask);
}
#ifdef BOOST_HAS_INT128

BOOST_FORCEINLINE std::size_t find_msb(uint128_type mask, std::integral_constant<int, 0> const&)
{
   union
   {
      uint128_type    v;
      std::uint64_t sv[2];
   } val;
   val.v = mask;
#if BOOST_MP_ENDIAN_LITTLE_BYTE
   if (val.sv[1])
      return find_msb(val.sv[1], std::integral_constant<int, 3>()) + 64;
   return find_msb(val.sv[0], std::integral_constant<int, 3>());
#else
   if (val.sv[0])
      return find_msb(val.sv[0], std::integral_constant<int, 3>()) + 64;
   return find_msb(val.sv[1], std::integral_constant<int, 3>());
#endif
}
BOOST_FORCEINLINE std::size_t find_lsb(uint128_type mask, std::integral_constant<int, 0> const&)
{
   union
   {
      uint128_type    v;
      std::uint64_t sv[2];
   } val;
   val.v = mask;
#if BOOST_MP_ENDIAN_LITTLE_BYTE
   if (val.sv[0] == 0)
      return find_lsb(val.sv[1], std::integral_constant<int, 3>()) + 64;
   return find_lsb(val.sv[0], std::integral_constant<int, 3>());
#else
   if (val.sv[1] == 0)
      return find_lsb(val.sv[0], std::integral_constant<int, 3>()) + 64;
   return find_lsb(val.sv[1], std::integral_constant<int, 3>());
#endif
}
#endif

template <class Unsigned>
BOOST_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR std::size_t find_lsb(Unsigned mask)
{
   using ui_type = typename boost::multiprecision::detail::make_unsigned<Unsigned>::type;
   using tag_type = typename std::conditional<
       sizeof(Unsigned) <= sizeof(unsigned),
       std::integral_constant<int, 1>,
       typename std::conditional<
           sizeof(Unsigned) <= sizeof(unsigned long),
           std::integral_constant<int, 2>,
           typename std::conditional<
               sizeof(Unsigned) <= sizeof(unsigned long long),
               std::integral_constant<int, 3>,
               std::integral_constant<int, 0> >::type>::type>::type;
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
   if (BOOST_MP_IS_CONST_EVALUATED(mask))
   {
      return find_lsb_default(mask);
   }
   else
#endif
   return find_lsb(static_cast<ui_type>(mask), tag_type());
}
template <class Unsigned>
BOOST_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR std::size_t find_msb(Unsigned mask)
{
   using ui_type = typename boost::multiprecision::detail::make_unsigned<Unsigned>::type;
   using tag_type = typename std::conditional<
       sizeof(Unsigned) <= sizeof(unsigned),
       std::integral_constant<int, 1>,
       typename std::conditional<
           sizeof(Unsigned) <= sizeof(unsigned long),
           std::integral_constant<int, 2>,
           typename std::conditional<
               sizeof(Unsigned) <= sizeof(unsigned long long),
               std::integral_constant<int, 3>,
               std::integral_constant<int, 0> >::type>::type>::type;
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
   if (BOOST_MP_IS_CONST_EVALUATED(mask))
   {
      return find_msb_default(mask);
   }
   else
#endif
      return find_msb(static_cast<ui_type>(mask), tag_type());
}
#elif defined(BOOST_INTEL)
BOOST_FORCEINLINE std::size_t find_lsb(std::size_t mask, std::integral_constant<int, 1> const&)
{
   return _bit_scan_forward(mask);
}
BOOST_FORCEINLINE std::size_t find_msb(std::size_t mask, std::integral_constant<int, 1> const&)
{
   return _bit_scan_reverse(mask);
}
template <class Unsigned>
BOOST_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR std::size_t find_lsb(Unsigned mask)
{
   using ui_type = typename boost::multiprecision::detail::make_unsigned<Unsigned>::type;
   using tag_type = typename std::conditional<
       sizeof(Unsigned) <= sizeof(unsigned),
       std::integral_constant<int, 1>,
       std::integral_constant<int, 0> >::type;
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
   if (BOOST_MP_IS_CONST_EVALUATED(mask))
   {
      return find_lsb_default(mask);
   }
   else
#endif
      return find_lsb(static_cast<ui_type>(mask), tag_type());
}
template <class Unsigned>
BOOST_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR std::size_t find_msb(Unsigned mask)
{
   using ui_type = typename boost::multiprecision::detail::make_unsigned<Unsigned>::type;
   using tag_type = typename std::conditional<
       sizeof(Unsigned) <= sizeof(unsigned),
       std::integral_constant<int, 1>,
       std::integral_constant<int, 0> >::type;
#ifndef BOOST_MP_NO_CONSTEXPR_DETECTION
   if (BOOST_MP_IS_CONST_EVALUATED(mask))
   {
      return find_msb_default(mask);
   }
   else
#endif
      return find_msb(static_cast<ui_type>(mask), tag_type());
}
#else
template <class Unsigned>
BOOST_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR std::size_t find_lsb(Unsigned mask)
{
   return find_lsb(mask, std::integral_constant<int, 0>());
}
template <class Unsigned>
BOOST_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR std::size_t find_msb(Unsigned mask)
{
   return find_msb(mask, std::integral_constant<int, 0>());
}
#endif

}}} // namespace boost::multiprecision::detail

#endif

/* bitscan.hpp
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
*/