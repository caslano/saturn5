///////////////////////////////////////////////////////////////
//  Copyright 2012 - 2021 John Maddock.
//  Copyright 2021 Matt Borland.
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_CPP_INT_CORE_HPP
#define BOOST_MP_CPP_INT_CORE_HPP

#include <cstdint>
#include <type_traits>
#include <limits>
#include <boost/multiprecision/detail/standalone_config.hpp>
#include <boost/multiprecision/detail/number_base.hpp>
#include <boost/multiprecision/detail/assert.hpp>

namespace boost {
namespace multiprecision {

namespace detail {

//
// These traits calculate the largest type in the list
// [unsigned] long long, long, int, which has the specified number
// of bits.  Note that int_t and uint_t find the first
// member of the above list, not the last.  We want the last in the
// list to ensure that mixed arithmetic operations are as efficient
// as possible.
//

template <std::size_t Bits>
struct int_t
{
   using exact = typename std::conditional<Bits <= sizeof(signed char) * CHAR_BIT, signed char,
                 typename std::conditional<Bits <= sizeof(short) * CHAR_BIT, short,
                 typename std::conditional<Bits <= sizeof(int) * CHAR_BIT, int,
                 typename std::conditional<Bits <= sizeof(long) * CHAR_BIT, long,
                 typename std::conditional<Bits <= sizeof(long long) * CHAR_BIT, long long, void
                 >::type>::type>::type>::type>::type;

   using least = typename std::conditional<Bits-1 <= std::numeric_limits<signed char>::digits, signed char,
                 typename std::conditional<Bits-1 <= std::numeric_limits<short>::digits, short,
                 typename std::conditional<Bits-1 <= std::numeric_limits<int>::digits, int,
                 typename std::conditional<Bits-1 <= std::numeric_limits<long>::digits, long,
                 typename std::conditional<Bits-1 <= std::numeric_limits<long long>::digits, long long, void
                 >::type>::type>::type>::type>::type;
   
   static_assert(!std::is_same<void, exact>::value && !std::is_same<void, least>::value, "Number of bits does not match any standard data type. \
      Please file an issue at https://github.com/boostorg/multiprecision/ referencing this error from cpp_int_config.hpp");
};

template <std::size_t Bits>
struct uint_t
{
   using exact = typename std::conditional<Bits <= sizeof(unsigned char) * CHAR_BIT, unsigned char,
                 typename std::conditional<Bits <= sizeof(unsigned short) * CHAR_BIT, unsigned short,
                 typename std::conditional<Bits <= sizeof(unsigned int) * CHAR_BIT, unsigned int,
                 typename std::conditional<Bits <= sizeof(unsigned long) * CHAR_BIT, unsigned long,
                 typename std::conditional<Bits <= sizeof(unsigned long long) * CHAR_BIT, unsigned long long, void
                 >::type>::type>::type>::type>::type;

   using least = typename std::conditional<Bits <= std::numeric_limits<unsigned char>::digits, unsigned char,
                 typename std::conditional<Bits <= std::numeric_limits<unsigned short>::digits, unsigned short,
                 typename std::conditional<Bits <= std::numeric_limits<unsigned int>::digits, unsigned int,
                 typename std::conditional<Bits <= std::numeric_limits<unsigned long>::digits, unsigned long,
                 typename std::conditional<Bits <= std::numeric_limits<unsigned long long>::digits, unsigned long long, void
                 >::type>::type>::type>::type>::type;

   static_assert(!std::is_same<void, exact>::value && !std::is_same<void, least>::value, "Number of bits does not match any standard data type. \
      Please file an issue at https://github.com/boostorg/multiprecision/ referencing this error from cpp_int_config.hpp");
};

template <std::size_t N>
struct largest_signed_type
{
   using type = typename std::conditional<
       1 + std::numeric_limits<long long>::digits == N,
       long long,
       typename std::conditional<
           1 + std::numeric_limits<long>::digits == N,
           long,
           typename std::conditional<
               1 + std::numeric_limits<int>::digits == N,
               int,
               typename int_t<N>::exact>::type>::type>::type;
};

template <std::size_t N>
struct largest_unsigned_type
{
   using type = typename std::conditional<
       std::numeric_limits<unsigned long long>::digits == N,
       unsigned long long,
       typename std::conditional<
           std::numeric_limits<unsigned long>::digits == N,
           unsigned long,
           typename std::conditional<
               std::numeric_limits<unsigned int>::digits == N,
               unsigned int,
               typename uint_t<N>::exact>::type>::type>::type;
};

} // namespace detail

#if defined(BOOST_HAS_INT128)

using limb_type = detail::largest_unsigned_type<64>::type;
using signed_limb_type = detail::largest_signed_type<64>::type;
using double_limb_type = boost::multiprecision::uint128_type;
using signed_double_limb_type = boost::multiprecision::int128_type;
constexpr const limb_type                       max_block_10        = 1000000000000000000uLL;
constexpr const limb_type                       digits_per_block_10 = 18;

inline BOOST_MP_CXX14_CONSTEXPR limb_type block_multiplier(std::size_t count)
{
   constexpr const limb_type values[digits_per_block_10] = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000, 100000000000000, 1000000000000000, 10000000000000000, 100000000000000000, 1000000000000000000};
   BOOST_MP_ASSERT(count < digits_per_block_10);
   return values[count];
}

// Can't do formatted IO on an __int128
#define BOOST_MP_NO_DOUBLE_LIMB_TYPE_IO

#else

using limb_type = detail::largest_unsigned_type<32>::type;
using signed_limb_type = detail::largest_signed_type<32>::type  ;
using double_limb_type = detail::largest_unsigned_type<64>::type;
using signed_double_limb_type = detail::largest_signed_type<64>::type  ;
constexpr const limb_type                       max_block_10        = 1000000000;
constexpr const limb_type                       digits_per_block_10 = 9;

inline limb_type block_multiplier(std::size_t count)
{
   constexpr const limb_type values[digits_per_block_10] = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
   BOOST_MP_ASSERT(count < digits_per_block_10);
   return values[count];
}

#endif

constexpr const std::size_t bits_per_limb = sizeof(limb_type) * CHAR_BIT;

template <class T>
inline BOOST_MP_CXX14_CONSTEXPR void minmax(const T& a, const T& b, T& aa, T& bb)
{
   if (a < b)
   {
      aa = a;
      bb = b;
   }
   else
   {
      aa = b;
      bb = a;
   }
}

enum cpp_integer_type
{
   signed_magnitude   = 1,
   unsigned_magnitude = 0,
   signed_packed      = 3,
   unsigned_packed    = 2
};

enum cpp_int_check_type
{
   checked   = 1,
   unchecked = 0
};

} // namespace multiprecision
} // namespace boost

#endif // BOOST_MP_CPP_INT_CORE_HPP

/* cpp_int_config.hpp
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
*/