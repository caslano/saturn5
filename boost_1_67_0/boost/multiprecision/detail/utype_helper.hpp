///////////////////////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock.
//  Copyright Christopher Kormanyos 2013. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MP_UTYPE_HELPER_HPP
#define BOOST_MP_UTYPE_HELPER_HPP

#include <limits>
#include <boost/cstdint.hpp>

namespace boost {
namespace multiprecision {
namespace detail {
template <const unsigned>
struct utype_helper
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<0U>
{
   typedef boost::uint8_t exact;
};
template <>
struct utype_helper<1U>
{
   typedef boost::uint8_t exact;
};
template <>
struct utype_helper<2U>
{
   typedef boost::uint8_t exact;
};
template <>
struct utype_helper<3U>
{
   typedef boost::uint8_t exact;
};
template <>
struct utype_helper<4U>
{
   typedef boost::uint8_t exact;
};
template <>
struct utype_helper<5U>
{
   typedef boost::uint8_t exact;
};
template <>
struct utype_helper<6U>
{
   typedef boost::uint8_t exact;
};
template <>
struct utype_helper<7U>
{
   typedef boost::uint8_t exact;
};
template <>
struct utype_helper<8U>
{
   typedef boost::uint8_t exact;
};

template <>
struct utype_helper<9U>
{
   typedef boost::uint16_t exact;
};
template <>
struct utype_helper<10U>
{
   typedef boost::uint16_t exact;
};
template <>
struct utype_helper<11U>
{
   typedef boost::uint16_t exact;
};
template <>
struct utype_helper<12U>
{
   typedef boost::uint16_t exact;
};
template <>
struct utype_helper<13U>
{
   typedef boost::uint16_t exact;
};
template <>
struct utype_helper<14U>
{
   typedef boost::uint16_t exact;
};
template <>
struct utype_helper<15U>
{
   typedef boost::uint16_t exact;
};
template <>
struct utype_helper<16U>
{
   typedef boost::uint16_t exact;
};

template <>
struct utype_helper<17U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<18U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<19U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<20U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<21U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<22U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<23U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<24U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<25U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<26U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<27U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<28U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<29U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<30U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<31U>
{
   typedef boost::uint32_t exact;
};
template <>
struct utype_helper<32U>
{
   typedef boost::uint32_t exact;
};

template <>
struct utype_helper<33U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<34U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<35U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<36U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<37U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<38U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<39U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<40U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<41U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<42U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<43U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<44U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<45U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<46U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<47U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<48U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<49U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<50U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<51U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<52U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<53U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<54U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<55U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<56U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<57U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<58U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<59U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<60U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<61U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<62U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<63U>
{
   typedef boost::uint64_t exact;
};
template <>
struct utype_helper<64U>
{
   typedef boost::uint64_t exact;
};

template <class unsigned_type>
int utype_prior(unsigned_type ui)
{
   // TBD: Implement a templated binary search for this.
   int priority_bit;

   unsigned_type priority_mask = unsigned_type(unsigned_type(1U) << (std::numeric_limits<unsigned_type>::digits - 1));

   for (priority_bit = std::numeric_limits<unsigned_type>::digits - 1; priority_bit >= 0; --priority_bit)
   {
      if (unsigned_type(priority_mask & ui) != unsigned_type(0U))
      {
         break;
      }

      priority_mask >>= 1;
   }

   return priority_bit;
}

}}} // namespace boost::multiprecision::detail

#endif // BOOST_MP_UTYPE_HELPER_HPP

/* utype_helper.hpp
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
*/