///////////////////////////////////////////////////////////////////////////////
//  Copyright 2021 John Maddock.
//  Copyright Christopher Kormanyos 2021. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MP_DETAIL_TABLES_HPP
#define BOOST_MP_DETAIL_TABLES_HPP

#include <algorithm>
#include <array>
#include <cstdint>

namespace boost { namespace multiprecision { namespace backends { namespace detail {
struct a029750
{
   static constexpr std::uint32_t a029750_as_constexpr(const std::uint32_t value)
   {
      // Sloane's A029750 List of numbers of the form 2^k times 1, 3, 5 or 7.
      // CoefficientList[Series[-(x + 1)^2 (x^2 + 1)^2/(2 x^4 - 1), {x, 0, 78}], x]
      return ((value <= UINT32_C(     32)) ? UINT32_C(     32) : ((value <=  UINT32_C(     40)) ?  UINT32_C(     40) : ((value <= UINT32_C(     48)) ? UINT32_C(     48) : ((value <= UINT32_C(     56)) ? UINT32_C(     56) :
             ((value <= UINT32_C(     64)) ? UINT32_C(     64) : ((value <=  UINT32_C(     80)) ?  UINT32_C(     80) : ((value <= UINT32_C(     96)) ? UINT32_C(     96) : ((value <= UINT32_C(    112)) ? UINT32_C(    112) :
             ((value <= UINT32_C(    128)) ? UINT32_C(    128) : ((value <=  UINT32_C(    160)) ?  UINT32_C(    160) : ((value <= UINT32_C(    192)) ? UINT32_C(    192) : ((value <= UINT32_C(    224)) ? UINT32_C(    224) :
             ((value <= UINT32_C(    256)) ? UINT32_C(    256) : ((value <=  UINT32_C(    320)) ?  UINT32_C(    320) : ((value <= UINT32_C(    384)) ? UINT32_C(    384) : ((value <= UINT32_C(    448)) ? UINT32_C(    448) :
             ((value <= UINT32_C(    512)) ? UINT32_C(    512) : ((value <=  UINT32_C(    640)) ?  UINT32_C(    640) : ((value <= UINT32_C(    768)) ? UINT32_C(    768) : ((value <= UINT32_C(    896)) ? UINT32_C(    896) :
             ((value <= UINT32_C(   1024)) ? UINT32_C(   1024) : ((value <=  UINT32_C(   1280)) ?  UINT32_C(   1280) : ((value <= UINT32_C(   1536)) ? UINT32_C(   1536) : ((value <= UINT32_C(   1792)) ? UINT32_C(   1792) :
             ((value <= UINT32_C(   2048)) ? UINT32_C(   2048) : ((value <=  UINT32_C(   2560)) ?  UINT32_C(   2560) : ((value <= UINT32_C(   3072)) ? UINT32_C(   3072) : ((value <= UINT32_C(   3584)) ? UINT32_C(   3584) :
             ((value <= UINT32_C(   4096)) ? UINT32_C(   4096) : ((value <=  UINT32_C(   5120)) ?  UINT32_C(   5120) : ((value <= UINT32_C(   6144)) ? UINT32_C(   6144) : ((value <= UINT32_C(   7168)) ? UINT32_C(   7168) :
             ((value <= UINT32_C(   8192)) ? UINT32_C(   8192) : ((value <=  UINT32_C(  10240)) ?  UINT32_C(  10240) : ((value <= UINT32_C(  12288)) ? UINT32_C(  12288) : ((value <= UINT32_C(  14336)) ? UINT32_C(  14336) :
             ((value <= UINT32_C(  16384)) ? UINT32_C(  16384) : ((value <=  UINT32_C(  20480)) ?  UINT32_C(  20480) : ((value <= UINT32_C(  24576)) ? UINT32_C(  24576) : ((value <= UINT32_C(  28672)) ? UINT32_C(  28672) :
             ((value <= UINT32_C(  32768)) ? UINT32_C(  32768) : ((value <=  UINT32_C(  40960)) ?  UINT32_C(  40960) : ((value <= UINT32_C(  49152)) ? UINT32_C(  49152) : ((value <= UINT32_C(  57344)) ? UINT32_C(  57344) :
             ((value <= UINT32_C(  65536)) ? UINT32_C(  65536) : ((value <=  UINT32_C(  81920)) ?  UINT32_C(  81920) : ((value <= UINT32_C(  98304)) ? UINT32_C(  98304) : ((value <= UINT32_C( 114688)) ? UINT32_C( 114688) :
             ((value <= UINT32_C( 131072)) ? UINT32_C( 131072) : ((value <=  UINT32_C( 163840)) ?  UINT32_C( 163840) : ((value <= UINT32_C( 196608)) ? UINT32_C( 196608) : ((value <= UINT32_C( 229376)) ? UINT32_C( 229376) :
             ((value <= UINT32_C( 262144)) ? UINT32_C( 262144) : ((value <=  UINT32_C( 327680)) ?  UINT32_C( 327680) : ((value <= UINT32_C( 393216)) ? UINT32_C( 393216) : ((value <= UINT32_C( 458752)) ? UINT32_C( 458752) :
             ((value <= UINT32_C( 524288)) ? UINT32_C( 524288) : ((value <=  UINT32_C( 655360)) ?  UINT32_C( 655360) : ((value <= UINT32_C( 786432)) ? UINT32_C( 786432) : ((value <= UINT32_C( 917504)) ? UINT32_C( 917504) :
             ((value <= UINT32_C(1048576)) ? UINT32_C(1048576) : ((value <=  UINT32_C(1310720)) ?  UINT32_C(1310720) : ((value <= UINT32_C(1572864)) ? UINT32_C(1572864) : ((value <= UINT32_C(1835008)) ? UINT32_C(1835008) : UINT32_C(0x7FFFFFFF)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))));
   }

   static std::uint32_t a029750_as_runtime_value(const std::uint32_t value)
   {
      // Sloane's A029750 List of numbers of the form 2^k times 1, 3, 5 or 7.
      // CoefficientList[Series[-(x + 1)^2 (x^2 + 1)^2/(2 x^4 - 1), {x, 0, 78}], x]
      constexpr std::array<std::uint32_t, 65U> a029750_data =
      {{
         UINT32_C(        32), UINT32_C(     40), UINT32_C(     48), UINT32_C(     56),
         UINT32_C(        64), UINT32_C(     80), UINT32_C(     96), UINT32_C(    112),
         UINT32_C(       128), UINT32_C(    160), UINT32_C(    192), UINT32_C(    224),
         UINT32_C(       256), UINT32_C(    320), UINT32_C(    384), UINT32_C(    448),
         UINT32_C(       512), UINT32_C(    640), UINT32_C(    768), UINT32_C(    896),
         UINT32_C(      1024), UINT32_C(   1280), UINT32_C(   1536), UINT32_C(   1792),
         UINT32_C(      2048), UINT32_C(   2560), UINT32_C(   3072), UINT32_C(   3584),
         UINT32_C(      4096), UINT32_C(   5120), UINT32_C(   6144), UINT32_C(   7168),
         UINT32_C(      8192), UINT32_C(  10240), UINT32_C(  12288), UINT32_C(  14336),
         UINT32_C(     16384), UINT32_C(  20480), UINT32_C(  24576), UINT32_C(  28672),
         UINT32_C(     32768), UINT32_C(  40960), UINT32_C(  49152), UINT32_C(  57344),
         UINT32_C(     65536), UINT32_C(  81920), UINT32_C(  98304), UINT32_C( 114688),
         UINT32_C(    131072), UINT32_C( 163840), UINT32_C( 196608), UINT32_C( 229376),
         UINT32_C(    262144), UINT32_C( 327680), UINT32_C( 393216), UINT32_C( 458752),
         UINT32_C(    524288), UINT32_C( 655360), UINT32_C( 786432), UINT32_C( 917504),
         UINT32_C(   1048576), UINT32_C(1310720), UINT32_C(1572864), UINT32_C(1835008),
         UINT32_C(0x7FFFFFFF)
      }};

      const std::array<std::uint32_t, 65U>::const_iterator it =
         std::lower_bound(a029750_data.cbegin(), a029750_data.cend(), value);

      return ((it != a029750_data.cend()) ? *it : UINT32_C(0xFFFFFFFF));
   }
};

constexpr std::uint32_t pow10_maker(std::uint32_t n)
{
   // Make the constant power of 10^n.
   return ((n == UINT32_C(0)) ? UINT32_C(1) : pow10_maker(n - UINT32_C(1)) * UINT32_C(10));
}

}}}} // namespace boost::multiprecision::backends::detail

#endif // BOOST_MP_DETAIL_TABLES_HPP

/* tables.hpp
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
*/