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
#ifdef _MSC_VER
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
#ifdef _MSC_VER
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
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
*/