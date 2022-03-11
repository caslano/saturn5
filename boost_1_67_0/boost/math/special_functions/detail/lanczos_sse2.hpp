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

BOOST_STATIC_ASSERT(sizeof(double) == sizeof(long double));

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