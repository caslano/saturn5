// Copyright 2008 John Maddock
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTRIBUTIONS_DETAIL_HG_CDF_HPP
#define BOOST_MATH_DISTRIBUTIONS_DETAIL_HG_CDF_HPP

#include <boost/math/policies/error_handling.hpp>
#include <boost/math/distributions/detail/hypergeometric_pdf.hpp>

namespace boost{ namespace math{ namespace detail{

   template <class T, class Policy>
   T hypergeometric_cdf_imp(unsigned x, unsigned r, unsigned n, unsigned N, bool invert, const Policy& pol)
   {
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable:4267)
#endif
      BOOST_MATH_STD_USING
      T result = 0;
      T mode = floor(T(r + 1) * T(n + 1) / (N + 2));
      if(x < mode)
      {
         result = hypergeometric_pdf<T>(x, r, n, N, pol);
         T diff = result;
         unsigned lower_limit = static_cast<unsigned>((std::max)(0, (int)(n + r) - (int)(N)));
         while(diff > (invert ? T(1) : result) * tools::epsilon<T>())
         {
            diff = T(x) * T((N + x) - n - r) * diff / (T(1 + n - x) * T(1 + r - x));
            result += diff;
            BOOST_MATH_INSTRUMENT_VARIABLE(x);
            BOOST_MATH_INSTRUMENT_VARIABLE(diff);
            BOOST_MATH_INSTRUMENT_VARIABLE(result);
            if(x == lower_limit)
               break;
            --x;
         }
      }
      else
      {
         invert = !invert;
         unsigned upper_limit = (std::min)(r, n);
         if(x != upper_limit)
         {
            ++x;
            result = hypergeometric_pdf<T>(x, r, n, N, pol);
            T diff = result;
            while((x <= upper_limit) && (diff > (invert ? T(1) : result) * tools::epsilon<T>()))
            {
               diff = T(n - x) * T(r - x) * diff / (T(x + 1) * T((N + x + 1) - n - r));
               result += diff;
               ++x;
               BOOST_MATH_INSTRUMENT_VARIABLE(x);
               BOOST_MATH_INSTRUMENT_VARIABLE(diff);
               BOOST_MATH_INSTRUMENT_VARIABLE(result);
            }
         }
      }
      if(invert)
         result = 1 - result;
      return result;
#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif
   }

   template <class T, class Policy>
   inline T hypergeometric_cdf(unsigned x, unsigned r, unsigned n, unsigned N, bool invert, const Policy&)
   {
      BOOST_FPU_EXCEPTION_GUARD
      typedef typename tools::promote_args<T>::type result_type;
      typedef typename policies::evaluation<result_type, Policy>::type value_type;
      typedef typename policies::normalise<
         Policy, 
         policies::promote_float<false>, 
         policies::promote_double<false>, 
         policies::discrete_quantile<>,
         policies::assert_undefined<> >::type forwarding_policy;

      value_type result;
      result = detail::hypergeometric_cdf_imp<value_type>(x, r, n, N, invert, forwarding_policy());
      if(result > 1)
      {
         result  = 1;
      }
      if(result < 0)
      {
         result = 0;
      }
      return policies::checked_narrowing_cast<result_type, forwarding_policy>(result, "boost::math::hypergeometric_cdf<%1%>(%1%,%1%,%1%,%1%)");
   }

}}} // namespaces

#endif


/* hypergeometric_cdf.hpp
AAkAY3VybC1tYXN0ZXIvdGVzdHMvY2VydHMvU2VydmVyLWxvY2FsaG9zdC1maXJzdFNBTi1zdi5jcmxVVAUAAbZIJGB1k09vozAQxe98ir1HVSEJUA57sLEhkBgwcSBw408xCQWykGCST79pV71U2rnNT5p5TzN6Ly/Pgth2vF9HVTZ+meHuk7xIxHFMykwT7BsTUCwQTdxtnzr1VHjP3oIUiAzhHQGNDZQDhjUxWbOeCQMT5F4kQdCTLY6aNBacrqJ7bkJYtJ6cxYTv43ks4/BSxjI/tNEjja17suScLuepjOnsnkEjfW6BgJDNQZ2KLuzTo3tzsDqVy/qjaA882rhKsaKcxuo5s427JeTZR0AlrBHeA8uSh+rsH8TiG34yspGFJRwbVddWVJD9GHwQFmYEFubTwUpPx2Hu6sIjjAufYZWgYvYQvsdncAQ88RbLnHTL9RExvCaomX0GVoTRO1F6IX2rPG4t/mmPPOovlS+RKxQh/ClC11L8B/gECGHyBEWhfHje43/fQJxjCIBsbk8DG4JQYXcrkDQ5lU+xluuP1AqdU3hdbKDfXZMy3lmHU6ewS46AXa/K8hBwKr/b3m3qEFha6S7Q3/S95NbHQVPzviP4Xb8oupnXy1HcixLc6EiSQPuwuJI55fkI
*/