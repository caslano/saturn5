///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_CPP_INT_CORE_HPP
#define BOOST_MP_CPP_INT_CORE_HPP

#include <boost/integer.hpp>
#include <boost/integer_traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/static_assert.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace multiprecision {

namespace detail {

//
// These traits calculate the largest type in the list
// [unsigned] boost::long_long_type, long, int, which has the specified number
// of bits.  Note that intN_t and boost::int_t<N> find the first
// member of the above list, not the last.  We want the last in the
// list to ensure that mixed arithmetic operations are as efficient
// as possible.
//
template <unsigned N>
struct largest_signed_type
{
   typedef typename mpl::if_c<
       1 + std::numeric_limits<boost::long_long_type>::digits == N,
       boost::long_long_type,
       typename mpl::if_c<
           1 + std::numeric_limits<long>::digits == N,
           long,
           typename mpl::if_c<
               1 + std::numeric_limits<int>::digits == N,
               int,
               typename boost::int_t<N>::exact>::type>::type>::type type;
};

template <unsigned N>
struct largest_unsigned_type
{
   typedef typename mpl::if_c<
       std::numeric_limits<boost::ulong_long_type>::digits == N,
       boost::ulong_long_type,
       typename mpl::if_c<
           std::numeric_limits<unsigned long>::digits == N,
           unsigned long,
           typename mpl::if_c<
               std::numeric_limits<unsigned int>::digits == N,
               unsigned int,
               typename boost::uint_t<N>::exact>::type>::type>::type type;
};

} // namespace detail

#if defined(BOOST_HAS_INT128)

typedef detail::largest_unsigned_type<64>::type limb_type;
typedef detail::largest_signed_type<64>::type   signed_limb_type;
typedef boost::uint128_type                     double_limb_type;
typedef boost::int128_type                      signed_double_limb_type;
static const limb_type                          max_block_10        = 1000000000000000000uLL;
static const limb_type                          digits_per_block_10 = 18;

inline BOOST_MP_CXX14_CONSTEXPR limb_type block_multiplier(unsigned count)
{
#ifdef BOOST_NO_CXX14_CONSTEXPR
   static
#else
   constexpr
#endif
   const limb_type values[digits_per_block_10] = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000, 100000000000000, 1000000000000000, 10000000000000000, 100000000000000000, 1000000000000000000};
   BOOST_ASSERT(count < digits_per_block_10);
   return values[count];
}

// Can't do formatted IO on an __int128
#define BOOST_MP_NO_DOUBLE_LIMB_TYPE_IO

// Need to specialise integer_traits for __int128 as it's not a normal native type:
} // namespace multiprecision

template <>
class integer_traits<multiprecision::double_limb_type>
    : public std::numeric_limits<multiprecision::double_limb_type>,
      public detail::integer_traits_base<multiprecision::double_limb_type, 0, ~static_cast<multiprecision::double_limb_type>(0)>
{};
template <>
class integer_traits<multiprecision::signed_double_limb_type>
    : public std::numeric_limits<multiprecision::signed_double_limb_type>,
      public detail::integer_traits_base<multiprecision::signed_double_limb_type, static_cast<multiprecision::signed_double_limb_type>((static_cast<multiprecision::double_limb_type>(1) << 127)), static_cast<multiprecision::signed_double_limb_type>(((~static_cast<multiprecision::double_limb_type>(0)) >> 1))>
{};

namespace multiprecision {

#else

typedef detail::largest_unsigned_type<32>::type limb_type;
typedef detail::largest_signed_type<32>::type   signed_limb_type;
typedef detail::largest_unsigned_type<64>::type double_limb_type;
typedef detail::largest_signed_type<64>::type   signed_double_limb_type;
static const limb_type                          max_block_10        = 1000000000;
static const limb_type                          digits_per_block_10 = 9;

inline limb_type block_multiplier(unsigned count)
{
#ifdef BOOST_NO_CXX14_CONSTEXPR
   static
#else
   constexpr
#endif
   const limb_type values[digits_per_block_10] = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
   BOOST_ASSERT(count < digits_per_block_10);
   return values[count];
}

#endif

static const unsigned bits_per_limb = sizeof(limb_type) * CHAR_BIT;

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

//
// Figure out whether to support user-defined-literals or not:
//
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && !defined(BOOST_NO_CXX11_USER_DEFINED_LITERALS) && !defined(BOOST_NO_CXX11_CONSTEXPR)
#define BOOST_MP_USER_DEFINED_LITERALS
#endif

#endif // BOOST_MP_CPP_INT_CORE_HPP

/* cpp_int_config.hpp
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
*/