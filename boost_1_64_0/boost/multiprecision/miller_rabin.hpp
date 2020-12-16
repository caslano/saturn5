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
/t+uSaifH6U6CDfLvNyn4Q2OPf6Epbt42AiNCeCkoMFz2eOPN//3YZASvpPtvWXEeFf1Y6csCgZxp8Lp/hNljBWIBSJ+WFlsAlJNbtX/Jf5OlczRVuaTR4y4KUmRp7nfIfSUvGzWUmUJVCbG2hk14oT4TuFmpQMtpP+fkXHOmvMAFFJL8opW1zBqvGeFaRjm0PCmhf26EpuqQv3utuJbzr7eiH5vT1zuZ16csUZC0TsL5+vn9QQz0XkAk1aPR+du4PIgj5kowQuPHO3XZcvYcy3PpVdrZZ2oytApy7Lp1cmjdTUX2vodAv2O3JMMnXCcpRmv7H6TsTiOaWJaGYcMGdyBxccPC0vGE4X6EkLPYT+pefLYMTrOyoCnkZOjCPP/hVCYNZ6+YqBgv7dj7OlEXsYCmHZxkWfQg/9WZO1gDP8FMq0xtjVi6J8rnsY89+0x1pyMZGfhnGrb+poRGns2j8MkKcJ4qJzjlVQqZUI/lKyeWXv8MaZijHzUnE9hUQZB4jE5Vgi3g2oXbGJbr6tETsWioijzmGetnFOayktcD2m91Nh3W93lGI1FGxRe4sV5JOe5HFEwyZchgge0y1dV6rUyXj9G5zXnmVv5WSplYA9RIVTX/CFjfPo8ruDdjkvjGi1UGtonHCvadYXw5oyHaQQL+L/5ViIqiXwDwZpAHJd2XD5Rm6NTsLZkPEpDOUef3KDbMXxrzIiHCfA8TMuOMVwpraNZA7qufHRRXyN4kHpVznN9jcA+qDAWzjY6l2JfPDoFKcO2Y8ygruE1jzowIidkcRLwMkydunT4k/VnZTjO46f6vb7Yj5AiK3WsrdOsISsMEzdPs0LJEkGaqLwpNUadtk7r2+gYLXwvKLNIiTkp4nzeXp0uGrKqMC65m3u0TigQK2XaMr1rG7UlqsqKZ7GS4gjXyXbP7SP/iXa8f1Tnzxms51kOk0YJaJaRRfxEmh3T53XeE0XpxVWcNS3o64MUoMd1P9ekOdvPb27Nob/mA1DHhfS1hf768mIDQb3L3m0tHXmR9kqkoeEByh3fIWnEgEPxft6gAxHPw/6dkKZ8thc3xRUcMRMTNkbWUOUF3wmY/xD75WIHxvTdvfrPcRJLK+ce53n+X/tYt2NozwgdiyGPkjQtfRoH66SMnYQnv6NoXzFK3xOzmAe+k7brrjMA/fbpTQjYqXgdPPOM0thLmQsjOI/bbWR+8vHHJie1udiujYd0vqkQDgBenqYtWw3HOPjPerS2jh3xeAZQGKftgD6EMQ9H6d4Y+2FVZHlJ3m8aS6Pj822jVN2OYsxQIidjKa9Sz09i2R+yI8WsDnAzwa4BOW0bL9A25mmVBEHYtPFE00Yc35dr3ToawpjzCtpG6Nb8+M02Qsc5gONyHOjdeQnwfjWyvRPTmTP9Nd1Y605U/YOOddhPvCz13P92rKdtbEgiL2AiBl0YBqkx1tGFDQJMwrNDcwIHRbAQ9Zi2bpd1WW7C3NRLy6gs6d3kP1938PxA5GUsyTIf5nVsytv89zcdnNe/0eVVrCiq2PfyjByp7K1hxMN5/c9x8q4Xx1mSpaHk5/OiX5qY77g7YNn7CK/HSh6UIno6nEca9qK31cHutWP/sM4/BbuszwuPMxFcoK3nFtr56diKwd7uZ4EMMUrPa/StOQY+eg/kflhCTFsZ/fw4jgmydnnteXOR8Gcs5iJcZBjVMR+7heAO3sp4GZERsDjj8J3SgA29gx637kOXiAzOfO64XlAl1tmPDmyf9Ly2H3ycyAtZFRROkTuZ7FBhptrVr76+FmX4dmKvRW8ZJXRrrWFjQP8PuaguEwzJRYXtGPkHbUcMB3lPxIjn9YWkttU9DmULm4Z5UD0=
*/