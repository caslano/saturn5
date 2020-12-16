//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_POWM1
#define BOOST_MATH_POWM1

#ifdef _MSC_VER
#pragma once
#pragma warning(push)
#pragma warning(disable:4702) // Unreachable code (release mode only warning)
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/special_functions/expm1.hpp>
#include <boost/math/special_functions/trunc.hpp>
#include <boost/assert.hpp>

namespace boost{ namespace math{ namespace detail{

template <class T, class Policy>
inline T powm1_imp(const T x, const T y, const Policy& pol)
{
   BOOST_MATH_STD_USING
   static const char* function = "boost::math::powm1<%1%>(%1%, %1%)";

   if (x > 0)
   {
      if ((fabs(y * (x - 1)) < 0.5) || (fabs(y) < 0.2))
      {
         // We don't have any good/quick approximation for log(x) * y
         // so just try it and see:
         T l = y * log(x);
         if (l < 0.5)
            return boost::math::expm1(l);
         if (l > boost::math::tools::log_max_value<T>())
            return boost::math::policies::raise_overflow_error<T>(function, 0, pol);
         // fall through....
      }
   }
   else
   {
      // y had better be an integer:
      if (boost::math::trunc(y) != y)
         return boost::math::policies::raise_domain_error<T>(function, "For non-integral exponent, expected base > 0 but got %1%", x, pol);
      if (boost::math::trunc(y / 2) == y / 2)
         return powm1_imp(T(-x), y, pol);
   }
   return pow(x, y) - 1;
}

} // detail

template <class T1, class T2>
inline typename tools::promote_args<T1, T2>::type 
   powm1(const T1 a, const T2 z)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   return detail::powm1_imp(static_cast<result_type>(a), static_cast<result_type>(z), policies::policy<>());
}

template <class T1, class T2, class Policy>
inline typename tools::promote_args<T1, T2>::type 
   powm1(const T1 a, const T2 z, const Policy& pol)
{
   typedef typename tools::promote_args<T1, T2>::type result_type;
   return detail::powm1_imp(static_cast<result_type>(a), static_cast<result_type>(z), pol);
}

} // namespace math
} // namespace boost

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif // BOOST_MATH_POWM1






/* powm1.hpp
CJMhD8phF5yAiCieGVJgPhRAJTRB2MX0DzKgCFqgC8Z/geeFPKiCWmiDTghcwvNCAmRegiyoh1YIiw4JJEUjC1ZBC0waSb9GIgtKoRk6IeJS5EAKFMAaqIFW6ICwy+gbJMFcKIJGCI7ieWE8ZI1CLpTALmiD6NHM7WjkjUYeNEEfJF3Oc0IO5F+OPCiDaqiDdoi8ArmQDllQClWwC9qgE6LH0GeohCYIG8u8wNSxyB6L3LHIG4s8CF6JTBgFkyAdZkMW5EEhlEMzdELEVYwrpEAaFEAxVEIHdEMfhI1jPcAYyIC5kA+roAJaoAeCMbQPk2NoD0qgCmpjaA+ir2adQRpkwhqoh1bogLBrGLdrkH8NsqEaGqELIsczVpAOhVAOzdAGEbHIjkU2pMQiP5ZnieU5YpEfi/xY5EPctciGfCiDamiELghex7jBZEiHLMiDKqiFToiIQzbMj0N+HPKhCfogLp45iUd2PHKhBYLX028YD5NhNhRCFdRCG0RMoN+QAmkwH3InIB/WQBN0w5gE2oCpkANFCbQDddACoybSXyiHqonIhugvIhvmQy4Uwxqoh1aIuoHxgCJYBXXQBcFJyIPJkA5ZkAeFUAK7oA0CiawfSEukjUTaSKTfibQBGxLZD4m0k0j/E2nrS8wtFEEjtEMXjL+RtQqTYTaUQDk0Q0QSMpOQCcVQCU0wJpmxgKmQAfnJrENoSUYmRH4ZuTAZsqAQSqENIm5iXCAF5t+EbFgD9dB9E7JTGN8U5EE1tMCoVGSlIgtKoPx/TN19eHrvGADwEEIIIcxlGH7ev97fGX4YhrwPQxhCCCEMIYQwhCGEEEIIIYQQQghhCCGEEEJePrvkuvzxuc46nXM/93M/z2m17TmjRZcTArcUjxRZaowI3Uo84uSo0mZMZFu/2eWAEi1OOHNrNeVe5ClTY070NupInCo9lmzcVo4cUKBClwFTts6WIynylGkyYs6KG99OTdknxzFtlpx1e/E5IM0hJboMmLIgdgdtcXMSHFGjz4g50R3jxz45jqnSYMiYJde/ozlBgRItpoTvpEbskKJGhwlzVoTurC/EyVCkwZDIrrqTpsCAKeG7yJ8zJDiiTIc+EzbvKnfOJkORMcG7ictZHFCgRZcTFoTj4nMvjugwYsLm3eVKkgZLgvcQj+uzywEFKnQZELunfEmQJc8RHUL3UmvOJs4+Sar0GBK8t7nDWVyfPQ44pM6ABeH7aIcUWWr0mTAndF9tkKRIlSHBPbHZJc2AwP3EY4sdEuTpMGLCNe4vHklyHNOmx5AxwQfInV3SHFKiTpcpCwL76sTNSZClzJzNB5r3nE2SHEWOqTLjrAdpgzSHlKgzYEHswfrCGe5FiiP6jJiwmdAOSY6pMmbjIa4rdjkgzSEl6gw4IfBQ7XCGBEfUGLH5MPmTpM2M4IHYnMUuB5Soc8LNHy5XshxRo8mIFZuPEJN9Giw565HmCHuk6TIllhSPHRKkyFNjzuaj9J19MhRpMGTJxqPVgDQF6rQYMCX2GLFJkOWIGnNWbKbEpE2PMUvOeqx82WaXEhW6DJiyYOtxakGKLGUmrAg9Xt5kyNFgTCQtNtukKTBgSuwJ8iXPERM2n2g+k2PIjOCT9J3rk6ZAhS7hjJzIUqPPnBXXeLKxYZ8MRY6pMiT4FHlxSJ0ugafKizMkSNGkw5zNrPlDm+DT5MQuBxSoMGVB+OnGmx3yHFGjSZ8JKzafoc8kyVCkypAxS7YPzScOOKRAiRYDpmw9U1vcixQdJkSfJT45ilRp02NI8Nnqyy5pKnSZcvOcmNyLBDUmzLnGc9SXIm16LNl4rnzZo0CJFics2HqemCSoMSeUF4skRar0GDI=
*/