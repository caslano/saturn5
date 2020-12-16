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
qmbhFwft2NnCO/pvYNmN+Sx5bKXyM1lu1buvKL89yubnQzmGJYCWbOyC5SzLFXePKQ24pA1kox/42Z5uSYL7+CMwbkcqn2MJ5prtf7+1fFiAdopn3iv7/fXVuuLXhHm98PH1uiP5vZAORhJIc57y3n3Z7VQy1v018ntZ+Wh32T0HdKUE0dbV50Sd0mDfUQ73mdLAzje+r5mWo2tXzus1953QoT8Zxq1YQTMHa2xO4+43ocF4JM1gn3hVPicDa1O01P89KkOakZin5ePw5ytJN5ZiwN9feLf+9+WbFrybMq+ieRO6irdtHVk/C/qoNPRu4zU5xrHQONlVnUyYPm4AvdvYzelfUCupdW0D6xtD/ZBuAy2JsVrVvpPVkrrjXi3sY6AYs9tog8J8LrRdUdU+cKcSNA3/pd3i3fgHc3rPlE32p04gPfR98h7lI0XfZVVzFRvEzHseGLud0tdBtJ3jDFa45KewM++DtC7WwHVYo/78vLRuptqmMVqvQ/nVy2P5NEYr4OHPV0cbPRCiiR7fWH3oEffI3t/4KjhXse03bd0s/Jw+nNNVTYqN7oOBv0Dj1+Z76c5rDdYmyMG0Ls1bwSx4TVwq732/kddxRTVe1KZh7W2IITaQrr1ouMcFWuJfYpSLHW8n/J4HXp5vPdo4LO79fp3jn9+FWjtrInvT7RevYTKUgdefCS/Nmk5E3gg+4QV9GlmNvB72yAz/gqZuWlMZDR1TQhpFdfpJQEtsaCEE2Ua5chyLWA5XAZvbkFzoOHeLPs02t7Zng49KNdxtf+fuVGZBG2VlNeEl/DoOYyEzmfO8omPVmjZC16BjKDN8s0r6ZkFHtGxb3aziR4Yyf2f2SCK3yK1s2mbRR+ghHctDoCV39z5ULa9Vzm8T/rq7hYxejHfJOdYnO4ELqrIotLW43vaYw6F/7yX8GmZ918pa1Tm/+eGbQRrHc/jbm49fvHZytEPXmY/mdXSsEj7Yum4yIa4dzt9E3zt/ifDtWB05N10w/4nv/gF4rhf30D/L61mTrmusiklPaYfxTfzvCd8IjTVa1UaQ8T3e6fkegufYzXAzHME5ZH9iZ3vco7K6HFPG+SCaCgU79vrMfOD/7BwD09F0dWir+j/zvzbbnO1gsgXs+/W8rrXotbG6U8vF5/XY9dHP6g2Ed8WSa1/0Kv5H3nK2uwPOa2/L4l/cRfstBde8wnUo7/bY7/fnGCAOCaWF/4+812fJejSZT597FJm/ysAEMUnNxz6v6cEPteizlM4bVf3n8eaH8Bc4xbAzDNfevJ7n2wBT2JqQ+jzV7T8XPD0MtKxr8x95iqPZwsqa8XzSo/N+wprqYOVw0M/1a3Ho57DnPTOnfZ5xxps6WOblZXpWeXZO93ypPOiA7Bb9mB8Vb5UvkzqD5LKJsmZ7W0WdV0mduq2NakWagzW+eB1j2eS0numO66prl8vb4Zt2oBl7g+l3jnEWc8wLRK1bKYRftPnWAfp0jHvXa8i4qUr5ykq9YPHmnhrHeIvUXYXOKONqxiHID27hmCOK1KulaUIbu0W9O8elfTunvdqAwjQGCFLwoGy3HvfBd5F2BG9C9NYPw4J7CtK/J6dfa5RO8ZnUot1KyL7l2Zh8gMo91AL22WX9sH3RNfVDOa1jXRoTI/u2w4I+36Dj8lFSd6y8dsYtRbq5t0lpP0X6qdL5EpR10W6YvZT2a1T/TdfUvlnWe7BfjPc3yXh7y4MzvOrbPC5IWPcPgZ7M51DV3i7He6vo30+pjkhdySiWOiLX1yntr0m9tayV5M4sx3lzg47zn6mO6DqE2Aw6gtn6xjaffUxed0qvVZnolnq9Oad1n89pHWtcZzrp9KLRaVpefC4=
*/