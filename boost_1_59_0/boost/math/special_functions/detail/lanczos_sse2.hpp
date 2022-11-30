//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_FUNCTIONS_LANCZOS_SSE2
#define BOOST_MATH_SPECIAL_FUNCTIONS_LANCZOS_SSE2

#ifdef _MSC_VER
#pragma once
#endif

#include <emmintrin.h>

#if defined(__GNUC__) || defined(__PGI) || defined(__SUNPRO_CC)
#define ALIGN16 __attribute__((__aligned__(16)))
#else
#define ALIGN16 __declspec(align(16))
#endif

namespace boost{ namespace math{ namespace lanczos{

template <>
inline double lanczos13m53::lanczos_sum<double>(const double& x)
{
   static const ALIGN16 double coeff[26] = {
      static_cast<double>(2.506628274631000270164908177133837338626L),
      static_cast<double>(1u),
      static_cast<double>(210.8242777515793458725097339207133627117L),
      static_cast<double>(66u),
      static_cast<double>(8071.672002365816210638002902272250613822L),
      static_cast<double>(1925u),
      static_cast<double>(186056.2653952234950402949897160456992822L),
      static_cast<double>(32670u),
      static_cast<double>(2876370.628935372441225409051620849613599L),
      static_cast<double>(357423u),
      static_cast<double>(31426415.58540019438061423162831820536287L),
      static_cast<double>(2637558u),
      static_cast<double>(248874557.8620541565114603864132294232163L),
      static_cast<double>(13339535u),
      static_cast<double>(1439720407.311721673663223072794912393972L),
      static_cast<double>(45995730u),
      static_cast<double>(6039542586.35202800506429164430729792107L),
      static_cast<double>(105258076u),
      static_cast<double>(17921034426.03720969991975575445893111267L),
      static_cast<double>(150917976u),
      static_cast<double>(35711959237.35566804944018545154716670596L),
      static_cast<double>(120543840u),
      static_cast<double>(42919803642.64909876895789904700198885093L),
      static_cast<double>(39916800u),
      static_cast<double>(23531376880.41075968857200767445163675473L),
      static_cast<double>(0u)
   };

   static const double lim = 4.31965e+25; // By experiment, the largest x for which the SSE2 code does not go bad.

   if (x > lim)
   {
      double z = 1 / x;
      return ((((((((((((coeff[24] * z + coeff[22]) * z + coeff[20]) * z + coeff[18]) * z + coeff[16]) * z + coeff[14]) * z + coeff[12]) * z + coeff[10]) * z + coeff[8]) * z + coeff[6]) * z + coeff[4]) * z + coeff[2]) * z + coeff[0]) / ((((((((((((coeff[25] * z + coeff[23]) * z + coeff[21]) * z + coeff[19]) * z + coeff[17]) * z + coeff[15]) * z + coeff[13]) * z + coeff[11]) * z + coeff[9]) * z + coeff[7]) * z + coeff[5]) * z + coeff[3]) * z + coeff[1]);
   }

   __m128d vx = _mm_load1_pd(&x);
   __m128d sum_even = _mm_load_pd(coeff);
   __m128d sum_odd = _mm_load_pd(coeff+2);
   __m128d nc_odd, nc_even;
   __m128d vx2 = _mm_mul_pd(vx, vx);

   sum_even = _mm_mul_pd(sum_even, vx2);
   nc_even = _mm_load_pd(coeff + 4);
   sum_odd = _mm_mul_pd(sum_odd, vx2);
   nc_odd = _mm_load_pd(coeff + 6);
   sum_even = _mm_add_pd(sum_even, nc_even);
   sum_odd = _mm_add_pd(sum_odd, nc_odd);

   sum_even = _mm_mul_pd(sum_even, vx2);
   nc_even = _mm_load_pd(coeff + 8);
   sum_odd = _mm_mul_pd(sum_odd, vx2);
   nc_odd = _mm_load_pd(coeff + 10);
   sum_even = _mm_add_pd(sum_even, nc_even);
   sum_odd = _mm_add_pd(sum_odd, nc_odd);

   sum_even = _mm_mul_pd(sum_even, vx2);
   nc_even = _mm_load_pd(coeff + 12);
   sum_odd = _mm_mul_pd(sum_odd, vx2);
   nc_odd = _mm_load_pd(coeff + 14);
   sum_even = _mm_add_pd(sum_even, nc_even);
   sum_odd = _mm_add_pd(sum_odd, nc_odd);

   sum_even = _mm_mul_pd(sum_even, vx2);
   nc_even = _mm_load_pd(coeff + 16);
   sum_odd = _mm_mul_pd(sum_odd, vx2);
   nc_odd = _mm_load_pd(coeff + 18);
   sum_even = _mm_add_pd(sum_even, nc_even);
   sum_odd = _mm_add_pd(sum_odd, nc_odd);

   sum_even = _mm_mul_pd(sum_even, vx2);
   nc_even = _mm_load_pd(coeff + 20);
   sum_odd = _mm_mul_pd(sum_odd, vx2);
   nc_odd = _mm_load_pd(coeff + 22);
   sum_even = _mm_add_pd(sum_even, nc_even);
   sum_odd = _mm_add_pd(sum_odd, nc_odd);

   sum_even = _mm_mul_pd(sum_even, vx2);
   nc_even = _mm_load_pd(coeff + 24);
   sum_odd = _mm_mul_pd(sum_odd, vx);
   sum_even = _mm_add_pd(sum_even, nc_even);
   sum_even = _mm_add_pd(sum_even, sum_odd);


   double ALIGN16 t[2];
   _mm_store_pd(t, sum_even);
   
   return t[0] / t[1];
}

template <>
inline double lanczos13m53::lanczos_sum_expG_scaled<double>(const double& x)
{
   static const ALIGN16 double coeff[26] = {
         static_cast<double>(0.006061842346248906525783753964555936883222L),
         static_cast<double>(1u),
         static_cast<double>(0.5098416655656676188125178644804694509993L),
         static_cast<double>(66u),
         static_cast<double>(19.51992788247617482847860966235652136208L),
         static_cast<double>(1925u),
         static_cast<double>(449.9445569063168119446858607650988409623L),
         static_cast<double>(32670u),
         static_cast<double>(6955.999602515376140356310115515198987526L),
         static_cast<double>(357423u),
         static_cast<double>(75999.29304014542649875303443598909137092L),
         static_cast<double>(2637558u),
         static_cast<double>(601859.6171681098786670226533699352302507L),
         static_cast<double>(13339535u),
         static_cast<double>(3481712.15498064590882071018964774556468L),
         static_cast<double>(45995730u),
         static_cast<double>(14605578.08768506808414169982791359218571L),
         static_cast<double>(105258076u),
         static_cast<double>(43338889.32467613834773723740590533316085L),
         static_cast<double>(150917976u),
         static_cast<double>(86363131.28813859145546927288977868422342L),
         static_cast<double>(120543840u),
         static_cast<double>(103794043.1163445451906271053616070238554L),
         static_cast<double>(39916800u),
         static_cast<double>(56906521.91347156388090791033559122686859L),
         static_cast<double>(0u)
   };

   static const double lim = 4.76886e+25; // By experiment, the largest x for which the SSE2 code does not go bad.

   if (x > lim)
   {
      double z = 1 / x;
      return ((((((((((((coeff[24] * z + coeff[22]) * z + coeff[20]) * z + coeff[18]) * z + coeff[16]) * z + coeff[14]) * z + coeff[12]) * z + coeff[10]) * z + coeff[8]) * z + coeff[6]) * z + coeff[4]) * z + coeff[2]) * z + coeff[0]) / ((((((((((((coeff[25] * z + coeff[23]) * z + coeff[21]) * z + coeff[19]) * z + coeff[17]) * z + coeff[15]) * z + coeff[13]) * z + coeff[11]) * z + coeff[9]) * z + coeff[7]) * z + coeff[5]) * z + coeff[3]) * z + coeff[1]);
   }

   __m128d vx = _mm_load1_pd(&x);
   __m128d sum_even = _mm_load_pd(coeff);
   __m128d sum_odd = _mm_load_pd(coeff+2);
   __m128d nc_odd, nc_even;
   __m128d vx2 = _mm_mul_pd(vx, vx);

   sum_even = _mm_mul_pd(sum_even, vx2);
   nc_even = _mm_load_pd(coeff + 4);
   sum_odd = _mm_mul_pd(sum_odd, vx2);
   nc_odd = _mm_load_pd(coeff + 6);
   sum_even = _mm_add_pd(sum_even, nc_even);
   sum_odd = _mm_add_pd(sum_odd, nc_odd);

   sum_even = _mm_mul_pd(sum_even, vx2);
   nc_even = _mm_load_pd(coeff + 8);
   sum_odd = _mm_mul_pd(sum_odd, vx2);
   nc_odd = _mm_load_pd(coeff + 10);
   sum_even = _mm_add_pd(sum_even, nc_even);
   sum_odd = _mm_add_pd(sum_odd, nc_odd);

   sum_even = _mm_mul_pd(sum_even, vx2);
   nc_even = _mm_load_pd(coeff + 12);
   sum_odd = _mm_mul_pd(sum_odd, vx2);
   nc_odd = _mm_load_pd(coeff + 14);
   sum_even = _mm_add_pd(sum_even, nc_even);
   sum_odd = _mm_add_pd(sum_odd, nc_odd);

   sum_even = _mm_mul_pd(sum_even, vx2);
   nc_even = _mm_load_pd(coeff + 16);
   sum_odd = _mm_mul_pd(sum_odd, vx2);
   nc_odd = _mm_load_pd(coeff + 18);
   sum_even = _mm_add_pd(sum_even, nc_even);
   sum_odd = _mm_add_pd(sum_odd, nc_odd);

   sum_even = _mm_mul_pd(sum_even, vx2);
   nc_even = _mm_load_pd(coeff + 20);
   sum_odd = _mm_mul_pd(sum_odd, vx2);
   nc_odd = _mm_load_pd(coeff + 22);
   sum_even = _mm_add_pd(sum_even, nc_even);
   sum_odd = _mm_add_pd(sum_odd, nc_odd);

   sum_even = _mm_mul_pd(sum_even, vx2);
   nc_even = _mm_load_pd(coeff + 24);
   sum_odd = _mm_mul_pd(sum_odd, vx);
   sum_even = _mm_add_pd(sum_even, nc_even);
   sum_even = _mm_add_pd(sum_even, sum_odd);


   double ALIGN16 t[2];
   _mm_store_pd(t, sum_even);
   
   return t[0] / t[1];
}

#ifdef _MSC_VER

static_assert(sizeof(double) == sizeof(long double), "sizeof(long double) != sizeof(double) is not supported");

template <>
inline long double lanczos13m53::lanczos_sum<long double>(const long double& x)
{
   return lanczos_sum<double>(static_cast<double>(x));
}
template <>
inline long double lanczos13m53::lanczos_sum_expG_scaled<long double>(const long double& x)
{
   return lanczos_sum_expG_scaled<double>(static_cast<double>(x));
}
#endif

} // namespace lanczos
} // namespace math
} // namespace boost

#undef ALIGN16

#endif // BOOST_MATH_SPECIAL_FUNCTIONS_LANCZOS






/* lanczos_sse2.hpp
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
*/