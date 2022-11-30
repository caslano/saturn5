///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_MR_HPP
#define BOOST_MP_MR_HPP

#include <random>
#include <cstdint>
#include <type_traits>
#include <boost/multiprecision/detail/standalone_config.hpp>
#include <boost/multiprecision/integer.hpp>
#include <boost/multiprecision/detail/uniform_int_distribution.hpp>
#include <boost/multiprecision/detail/assert.hpp>

namespace boost {
namespace multiprecision {
namespace detail {

template <class I>
bool check_small_factors(const I& n)
{
   constexpr const std::uint32_t small_factors1[] = {
       3u, 5u, 7u, 11u, 13u, 17u, 19u, 23u};
   constexpr const std::uint32_t pp1 = 223092870u;

   std::uint32_t m1 = integer_modulus(n, pp1);

   for (std::size_t i = 0; i < sizeof(small_factors1) / sizeof(small_factors1[0]); ++i)
   {
      BOOST_MP_ASSERT(pp1 % small_factors1[i] == 0);
      if (m1 % small_factors1[i] == 0)
         return false;
   }

   constexpr const std::uint32_t small_factors2[] = {
       29u, 31u, 37u, 41u, 43u, 47u};
   constexpr const std::uint32_t pp2 = 2756205443u;

   m1 = integer_modulus(n, pp2);

   for (std::size_t i = 0; i < sizeof(small_factors2) / sizeof(small_factors2[0]); ++i)
   {
      BOOST_MP_ASSERT(pp2 % small_factors2[i] == 0);
      if (m1 % small_factors2[i] == 0)
         return false;
   }

   constexpr const std::uint32_t small_factors3[] = {
       53u, 59u, 61u, 67u, 71u};
   constexpr const std::uint32_t pp3 = 907383479u;

   m1 = integer_modulus(n, pp3);

   for (std::size_t i = 0; i < sizeof(small_factors3) / sizeof(small_factors3[0]); ++i)
   {
      BOOST_MP_ASSERT(pp3 % small_factors3[i] == 0);
      if (m1 % small_factors3[i] == 0)
         return false;
   }

   constexpr const std::uint32_t small_factors4[] = {
       73u, 79u, 83u, 89u, 97u};
   constexpr const std::uint32_t pp4 = 4132280413u;

   m1 = integer_modulus(n, pp4);

   for (std::size_t i = 0; i < sizeof(small_factors4) / sizeof(small_factors4[0]); ++i)
   {
      BOOST_MP_ASSERT(pp4 % small_factors4[i] == 0);
      if (m1 % small_factors4[i] == 0)
         return false;
   }

   constexpr const std::uint32_t small_factors5[6][4] = {
       {101u, 103u, 107u, 109u},
       {113u, 127u, 131u, 137u},
       {139u, 149u, 151u, 157u},
       {163u, 167u, 173u, 179u},
       {181u, 191u, 193u, 197u},
       {199u, 211u, 223u, 227u}};
   constexpr const std::uint32_t pp5[6] =
       {
           121330189u,
           113u * 127u * 131u * 137u,
           139u * 149u * 151u * 157u,
           163u * 167u * 173u * 179u,
           181u * 191u * 193u * 197u,
           199u * 211u * 223u * 227u};

   for (std::size_t k = 0; k < sizeof(pp5) / sizeof(*pp5); ++k)
   {
      m1 = integer_modulus(n, pp5[k]);

      for (std::size_t i = 0; i < 4; ++i)
      {
         BOOST_MP_ASSERT(pp5[k] % small_factors5[k][i] == 0);
         if (m1 % small_factors5[k][i] == 0)
            return false;
      }
   }
   return true;
}

inline bool is_small_prime(std::size_t n)
{
   constexpr const unsigned char p[] =
       {
           3u, 5u, 7u, 11u, 13u, 17u, 19u, 23u, 29u, 31u,
           37u, 41u, 43u, 47u, 53u, 59u, 61u, 67u, 71u, 73u,
           79u, 83u, 89u, 97u, 101u, 103u, 107u, 109u, 113u,
           127u, 131u, 137u, 139u, 149u, 151u, 157u, 163u,
           167u, 173u, 179u, 181u, 191u, 193u, 197u, 199u,
           211u, 223u, 227u};
   for (std::size_t i = 0; i < sizeof(p) / sizeof(*p); ++i)
   {
      if (n == p[i])
         return true;
   }
   return false;
}

template <class I>
typename std::enable_if<std::is_convertible<I, unsigned>::value, unsigned>::type
cast_to_unsigned(const I& val)
{
   return static_cast<unsigned>(val);
}
template <class I>
typename std::enable_if<!std::is_convertible<I, unsigned>::value, unsigned>::type
cast_to_unsigned(const I& val)
{
   return val.template convert_to<unsigned>();
}

} // namespace detail

template <class I, class Engine>
typename std::enable_if<number_category<I>::value == number_kind_integer, bool>::type
miller_rabin_test(const I& n, std::size_t trials, Engine& gen)
{
   using number_type = I;

   if (n == 2)
      return true; // Trivial special case.
   if (bit_test(n, 0) == 0)
      return false; // n is even
   if (n <= 227)
      return detail::is_small_prime(detail::cast_to_unsigned(n));

   if (!detail::check_small_factors(n))
      return false;

   number_type nm1 = n - 1;
   //
   // Begin with a single Fermat test - it excludes a lot of candidates:
   //
   number_type q(228), x, y; // We know n is greater than this, as we've excluded small factors
   x = powm(q, nm1, n);
   if (x != 1u)
      return false;

   q          = n - 1;
   std::size_t k = lsb(q);
   q >>= k;

   // Declare our random number generator:
   boost::multiprecision::uniform_int_distribution<number_type> dist(2, n - 2);

   //
   // Execute the trials:
   //
   for (std::size_t i = 0; i < trials; ++i)
   {
      x          = dist(gen);
      y          = powm(x, q, n);
      std::size_t j = 0;
      while (true)
      {
         if (y == nm1)
            break;
         if (y == 1)
         {
            if (j == 0)
               break;
            return false; // test failed
         }
         if (++j == k)
            return false; // failed
         y = powm(y, 2, n);
      }
   }
   return true; // Yeheh! probably prime.
}

template <class I>
typename std::enable_if<number_category<I>::value == number_kind_integer, bool>::type
miller_rabin_test(const I& x, std::size_t trials)
{
   static std::mt19937 gen;
   return miller_rabin_test(x, trials, gen);
}

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class Engine>
bool miller_rabin_test(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& n, std::size_t trials, Engine& gen)
{
   using number_type = typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type;
   return miller_rabin_test(number_type(n), trials, gen);
}

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
bool miller_rabin_test(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& n, std::size_t trials)
{
   using number_type = typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type;
   return miller_rabin_test(number_type(n), trials);
}

}} // namespace boost::multiprecision

#endif

/* miller_rabin.hpp
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
*/