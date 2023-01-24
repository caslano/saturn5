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
l3NiEa8Rd4PH/f5les+pz2XvPXjN/Ewy9X+I4YizqfMvr7+n3PZJes1JV80tQU3PIK4j7lAdvOZQ7rLf7k7bOe1Aj0dvee5zxHrE3ZE3Di4v+fmzzzLvH1b43nd1S15H/Ef4675/YXLv7/Xhqi3B83v/Ub/sdsSExDnI1u++qTvomrBoZ78P0y6lvjQScSJxzrPOcMO3y75vTX9kS97ovMT5JsSOxL3DC2mnTs4smre4MXrPL59G/n0j4knC1+qazx49k3ftw4u2HnDlh3yjfBExJuEL8MvGnLPLfrgh5Vmn4okdny8rQdxJnPHs+bFKO2ZBysKn975YGeG8/0XEosRdvevvfH7sL3/MSbtX5X66x7qB/0R8Svh/nxm+5syX52q0u4If/HD8NRXXImYl/NvNFz+Zd2fdL5r9quMjP8gbNRNxLOG/b9foR77/3i7N86+v3H7d3tTliG0Jnem5Ryqibt/yVVZdwguThw1c8CjiXcJv6Poni2ovNLam7PxjetbVV/8WgRiYOMN5JOePR8Z4VIuOZITNKf9uRjHiYsJ3f+Dy3bdc2v1ndv2YLce+mnfnRcTKhE17YsTFx74bsVK9Y37OtI/LdhxE/Ezopt++3sv681UzFt388Je9ls9/917E1IRdt3ZLccnEnLzkey2//TjL2e9axNmE2eXwpvJwzbglWUeiZ9b++vPAPMTehI32tSMx9xQnmBY1
*/