///////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_MR_HPP
#define BOOST_MP_MR_HPP

#include <boost/random.hpp>
#include <boost/multiprecision/integer.hpp>

namespace boost {
namespace multiprecision {
namespace detail {

template <class I>
bool check_small_factors(const I& n)
{
   static const boost::uint32_t small_factors1[] = {
       3u, 5u, 7u, 11u, 13u, 17u, 19u, 23u};
   static const boost::uint32_t pp1 = 223092870u;

   boost::uint32_t m1 = integer_modulus(n, pp1);

   for (unsigned i = 0; i < sizeof(small_factors1) / sizeof(small_factors1[0]); ++i)
   {
      BOOST_ASSERT(pp1 % small_factors1[i] == 0);
      if (m1 % small_factors1[i] == 0)
         return false;
   }

   static const boost::uint32_t small_factors2[] = {
       29u, 31u, 37u, 41u, 43u, 47u};
   static const boost::uint32_t pp2 = 2756205443u;

   m1 = integer_modulus(n, pp2);

   for (unsigned i = 0; i < sizeof(small_factors2) / sizeof(small_factors2[0]); ++i)
   {
      BOOST_ASSERT(pp2 % small_factors2[i] == 0);
      if (m1 % small_factors2[i] == 0)
         return false;
   }

   static const boost::uint32_t small_factors3[] = {
       53u, 59u, 61u, 67u, 71u};
   static const boost::uint32_t pp3 = 907383479u;

   m1 = integer_modulus(n, pp3);

   for (unsigned i = 0; i < sizeof(small_factors3) / sizeof(small_factors3[0]); ++i)
   {
      BOOST_ASSERT(pp3 % small_factors3[i] == 0);
      if (m1 % small_factors3[i] == 0)
         return false;
   }

   static const boost::uint32_t small_factors4[] = {
       73u, 79u, 83u, 89u, 97u};
   static const boost::uint32_t pp4 = 4132280413u;

   m1 = integer_modulus(n, pp4);

   for (unsigned i = 0; i < sizeof(small_factors4) / sizeof(small_factors4[0]); ++i)
   {
      BOOST_ASSERT(pp4 % small_factors4[i] == 0);
      if (m1 % small_factors4[i] == 0)
         return false;
   }

   static const boost::uint32_t small_factors5[6][4] = {
       {101u, 103u, 107u, 109u},
       {113u, 127u, 131u, 137u},
       {139u, 149u, 151u, 157u},
       {163u, 167u, 173u, 179u},
       {181u, 191u, 193u, 197u},
       {199u, 211u, 223u, 227u}};
   static const boost::uint32_t pp5[6] =
       {
           121330189u,
           113u * 127u * 131u * 137u,
           139u * 149u * 151u * 157u,
           163u * 167u * 173u * 179u,
           181u * 191u * 193u * 197u,
           199u * 211u * 223u * 227u};

   for (unsigned k = 0; k < sizeof(pp5) / sizeof(*pp5); ++k)
   {
      m1 = integer_modulus(n, pp5[k]);

      for (unsigned i = 0; i < 4; ++i)
      {
         BOOST_ASSERT(pp5[k] % small_factors5[k][i] == 0);
         if (m1 % small_factors5[k][i] == 0)
            return false;
      }
   }
   return true;
}

inline bool is_small_prime(unsigned n)
{
   static const unsigned char p[] =
       {
           3u, 5u, 7u, 11u, 13u, 17u, 19u, 23u, 29u, 31u,
           37u, 41u, 43u, 47u, 53u, 59u, 61u, 67u, 71u, 73u,
           79u, 83u, 89u, 97u, 101u, 103u, 107u, 109u, 113u,
           127u, 131u, 137u, 139u, 149u, 151u, 157u, 163u,
           167u, 173u, 179u, 181u, 191u, 193u, 197u, 199u,
           211u, 223u, 227u};
   for (unsigned i = 0; i < sizeof(p) / sizeof(*p); ++i)
   {
      if (n == p[i])
         return true;
   }
   return false;
}

template <class I>
typename enable_if_c<is_convertible<I, unsigned>::value, unsigned>::type
cast_to_unsigned(const I& val)
{
   return static_cast<unsigned>(val);
}
template <class I>
typename disable_if_c<is_convertible<I, unsigned>::value, unsigned>::type
cast_to_unsigned(const I& val)
{
   return val.template convert_to<unsigned>();
}

} // namespace detail

template <class I, class Engine>
typename enable_if_c<number_category<I>::value == number_kind_integer, bool>::type
miller_rabin_test(const I& n, unsigned trials, Engine& gen)
{
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4127)
#endif
   typedef I number_type;

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
   unsigned k = lsb(q);
   q >>= k;

   // Declare our random number generator:
   boost::random::uniform_int_distribution<number_type> dist(2, n - 2);
   //
   // Execute the trials:
   //
   for (unsigned i = 0; i < trials; ++i)
   {
      x          = dist(gen);
      y          = powm(x, q, n);
      unsigned j = 0;
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
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
}

template <class I>
typename enable_if_c<number_category<I>::value == number_kind_integer, bool>::type
miller_rabin_test(const I& x, unsigned trials)
{
   static mt19937 gen;
   return miller_rabin_test(x, trials, gen);
}

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4, class Engine>
bool miller_rabin_test(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& n, unsigned trials, Engine& gen)
{
   typedef typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type number_type;
   return miller_rabin_test(number_type(n), trials, gen);
}

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
bool miller_rabin_test(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& n, unsigned trials)
{
   typedef typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type number_type;
   return miller_rabin_test(number_type(n), trials);
}

}} // namespace boost::multiprecision

#endif

/* miller_rabin.hpp
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
*/