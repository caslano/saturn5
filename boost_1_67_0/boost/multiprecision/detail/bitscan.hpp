///////////////////////////////////////////////////////////////
//  Copyright 2013 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt
//
// Comparison operators for cpp_int_backend:
//
#ifndef BOOST_MP_DETAIL_BITSCAN_HPP
#define BOOST_MP_DETAIL_BITSCAN_HPP

#include <boost/predef/other/endian.h>
#include <boost/cstdint.hpp>

#if (defined(BOOST_MSVC) || (defined(__clang__) && defined(__c2__)) || (defined(BOOST_INTEL) && defined(_MSC_VER))) && (defined(_M_IX86) || defined(_M_X64))
#include <intrin.h>
#endif

namespace boost { namespace multiprecision { namespace detail {

template <class Unsigned>
inline BOOST_MP_CXX14_CONSTEXPR unsigned find_lsb_default(Unsigned mask)
{
   unsigned result = 0;
   while (!(mask & 1u))
   {
      mask >>= 1;
      ++result;
   }
   return result;
}

template <class Unsigned>
inline BOOST_MP_CXX14_CONSTEXPR unsigned find_msb_default(Unsigned mask)
{
   unsigned index = 0;
   while (mask)
   {
      ++index;
      mask >>= 1;
   }
   return --index;
}

template <class Unsigned>
inline BOOST_MP_CXX14_CONSTEXPR unsigned find_lsb(Unsigned mask, const mpl::int_<0>&)
{
   return find_lsb_default(mask);
}

template <class Unsigned>
inline BOOST_MP_CXX14_CONSTEXPR unsigned find_msb(Unsigned mask, const mpl::int_<0>&)
{
   return find_msb_default(mask);
}

#if (defined(BOOST_MSVC) || (defined(__clang__) && defined(__c2__)) || (defined(BOOST_INTEL) && defined(_MSC_VER))) && (defined(_M_IX86) || defined(_M_X64))

#pragma intrinsic(_BitScanForward, _BitScanReverse)

BOOST_FORCEINLINE unsigned find_lsb(unsigned long mask, const mpl::int_<1>&)
{
   unsigned long result;
   _BitScanForward(&result, mask);
   return result;
}

BOOST_FORCEINLINE unsigned find_msb(unsigned long mask, const mpl::int_<1>&)
{
   unsigned long result;
   _BitScanReverse(&result, mask);
   return result;
}
#ifdef _M_X64

#pragma intrinsic(_BitScanForward64, _BitScanReverse64)

BOOST_FORCEINLINE unsigned find_lsb(unsigned __int64 mask, const mpl::int_<2>&)
{
   unsigned long result;
   _BitScanForward64(&result, mask);
   return result;
}
template <class Unsigned>
BOOST_FORCEINLINE unsigned find_msb(Unsigned mask, const mpl::int_<2>&)
{
   unsigned long result;
   _BitScanReverse64(&result, mask);
   return result;
}
#endif

template <class Unsigned>
BOOST_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR unsigned find_lsb(Unsigned mask)
{
   typedef typename make_unsigned<Unsigned>::type ui_type;
   typedef typename mpl::if_c<
       sizeof(Unsigned) <= sizeof(unsigned long),
       mpl::int_<1>,
#ifdef _M_X64
       typename mpl::if_c<
           sizeof(Unsigned) <= sizeof(__int64),
           mpl::int_<2>,
           mpl::int_<0> >::type
#else
       mpl::int_<0>
#endif
       >::type tag_type;
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
BOOST_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR unsigned find_msb(Unsigned mask)
{
   typedef typename make_unsigned<Unsigned>::type ui_type;
   typedef typename mpl::if_c<
       sizeof(Unsigned) <= sizeof(unsigned long),
       mpl::int_<1>,
#ifdef _M_X64
       typename mpl::if_c<
           sizeof(Unsigned) <= sizeof(__int64),
           mpl::int_<2>,
           mpl::int_<0> >::type
#else
       mpl::int_<0>
#endif
       >::type tag_type;
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

BOOST_FORCEINLINE unsigned find_lsb(unsigned mask, mpl::int_<1> const&)
{
   return __builtin_ctz(mask);
}
BOOST_FORCEINLINE unsigned find_lsb(unsigned long mask, mpl::int_<2> const&)
{
   return __builtin_ctzl(mask);
}
BOOST_FORCEINLINE unsigned find_lsb(boost::ulong_long_type mask, mpl::int_<3> const&)
{
   return __builtin_ctzll(mask);
}
BOOST_FORCEINLINE unsigned find_msb(unsigned mask, mpl::int_<1> const&)
{
   return sizeof(unsigned) * CHAR_BIT - 1 - __builtin_clz(mask);
}
BOOST_FORCEINLINE unsigned find_msb(unsigned long mask, mpl::int_<2> const&)
{
   return sizeof(unsigned long) * CHAR_BIT - 1 - __builtin_clzl(mask);
}
BOOST_FORCEINLINE unsigned find_msb(boost::ulong_long_type mask, mpl::int_<3> const&)
{
   return sizeof(boost::ulong_long_type) * CHAR_BIT - 1 - __builtin_clzll(mask);
}
#ifdef BOOST_HAS_INT128

__extension__ typedef unsigned __int128 uint128_type;

BOOST_FORCEINLINE unsigned find_msb(uint128_type mask, mpl::int_<0> const&)
{
   union
   {
      uint128_type    v;
      boost::uint64_t sv[2];
   } val;
   val.v = mask;
#if BOOST_ENDIAN_LITTLE_BYTE
   if (val.sv[1])
      return find_msb(val.sv[1], mpl::int_<3>()) + 64;
   return find_msb(val.sv[0], mpl::int_<3>());
#else
   if (val.sv[0])
      return find_msb(val.sv[0], mpl::int_<3>()) + 64;
   return find_msb(val.sv[1], mpl::int_<3>());
#endif
}
BOOST_FORCEINLINE unsigned find_lsb(uint128_type mask, mpl::int_<0> const&)
{
   union
   {
      uint128_type    v;
      boost::uint64_t sv[2];
   } val;
   val.v = mask;
#if BOOST_ENDIAN_LITTLE_BYTE
   if (val.sv[0] == 0)
      return find_lsb(val.sv[1], mpl::int_<3>()) + 64;
   return find_lsb(val.sv[0], mpl::int_<3>());
#else
   if (val.sv[1] == 0)
      return find_lsb(val.sv[0], mpl::int_<3>()) + 64;
   return find_lsb(val.sv[1], mpl::int_<3>());
#endif
}
#endif

template <class Unsigned>
BOOST_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR unsigned find_lsb(Unsigned mask)
{
   typedef typename make_unsigned<Unsigned>::type ui_type;
   typedef typename mpl::if_c<
       sizeof(Unsigned) <= sizeof(unsigned),
       mpl::int_<1>,
       typename mpl::if_c<
           sizeof(Unsigned) <= sizeof(unsigned long),
           mpl::int_<2>,
           typename mpl::if_c<
               sizeof(Unsigned) <= sizeof(boost::ulong_long_type),
               mpl::int_<3>,
               mpl::int_<0> >::type>::type>::type tag_type;
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
BOOST_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR unsigned find_msb(Unsigned mask)
{
   typedef typename make_unsigned<Unsigned>::type ui_type;
   typedef typename mpl::if_c<
       sizeof(Unsigned) <= sizeof(unsigned),
       mpl::int_<1>,
       typename mpl::if_c<
           sizeof(Unsigned) <= sizeof(unsigned long),
           mpl::int_<2>,
           typename mpl::if_c<
               sizeof(Unsigned) <= sizeof(boost::ulong_long_type),
               mpl::int_<3>,
               mpl::int_<0> >::type>::type>::type tag_type;
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
BOOST_FORCEINLINE unsigned find_lsb(unsigned mask, mpl::int_<1> const&)
{
   return _bit_scan_forward(mask);
}
BOOST_FORCEINLINE unsigned find_msb(unsigned mask, mpl::int_<1> const&)
{
   return _bit_scan_reverse(mask);
}
template <class Unsigned>
BOOST_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR unsigned find_lsb(Unsigned mask)
{
   typedef typename make_unsigned<Unsigned>::type ui_type;
   typedef typename mpl::if_c<
       sizeof(Unsigned) <= sizeof(unsigned),
       mpl::int_<1>,
       mpl::int_<0> >::type tag_type;
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
BOOST_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR unsigned find_msb(Unsigned mask)
{
   typedef typename make_unsigned<Unsigned>::type ui_type;
   typedef typename mpl::if_c<
       sizeof(Unsigned) <= sizeof(unsigned),
       mpl::int_<1>,
       mpl::int_<0> >::type tag_type;
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
BOOST_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR unsigned find_lsb(Unsigned mask)
{
   return find_lsb(mask, mpl::int_<0>());
}
template <class Unsigned>
BOOST_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR unsigned find_msb(Unsigned mask)
{
   return find_msb(mask, mpl::int_<0>());
}
#endif

}}} // namespace boost::multiprecision::detail

#endif

/* bitscan.hpp
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
*/