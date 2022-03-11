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
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
*/