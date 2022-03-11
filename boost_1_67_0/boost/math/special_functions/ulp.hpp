//  (C) Copyright John Maddock 2015.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_ULP_HPP
#define BOOST_MATH_SPECIAL_ULP_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/special_functions/next.hpp>

namespace boost{ namespace math{ namespace detail{

template <class T, class Policy>
T ulp_imp(const T& val, const boost::true_type&, const Policy& pol)
{
   BOOST_MATH_STD_USING
   int expon;
   static const char* function = "ulp<%1%>(%1%)";

   int fpclass = (boost::math::fpclassify)(val);

   if(fpclass == (int)FP_NAN)
   {
      return policies::raise_domain_error<T>(
         function,
         "Argument must be finite, but got %1%", val, pol);
   }
   else if((fpclass == (int)FP_INFINITE) || (fabs(val) >= tools::max_value<T>()))
   {
      return (val < 0 ? -1 : 1) * policies::raise_overflow_error<T>(function, 0, pol);
   }
   else if(fpclass == FP_ZERO)
      return detail::get_smallest_value<T>();
   //
   // This code is almost the same as that for float_next, except for negative integers,
   // where we preserve the relation ulp(x) == ulp(-x) as does Java:
   //
   frexp(fabs(val), &expon);
   T diff = ldexp(T(1), expon - tools::digits<T>());
   if(diff == 0)
      diff = detail::get_smallest_value<T>();
   return diff;
}
// non-binary version:
template <class T, class Policy>
T ulp_imp(const T& val, const boost::false_type&, const Policy& pol)
{
   BOOST_STATIC_ASSERT(std::numeric_limits<T>::is_specialized);
   BOOST_STATIC_ASSERT(std::numeric_limits<T>::radix != 2);
   BOOST_MATH_STD_USING
   int expon;
   static const char* function = "ulp<%1%>(%1%)";

   int fpclass = (boost::math::fpclassify)(val);

   if(fpclass == (int)FP_NAN)
   {
      return policies::raise_domain_error<T>(
         function,
         "Argument must be finite, but got %1%", val, pol);
   }
   else if((fpclass == (int)FP_INFINITE) || (fabs(val) >= tools::max_value<T>()))
   {
      return (val < 0 ? -1 : 1) * policies::raise_overflow_error<T>(function, 0, pol);
   }
   else if(fpclass == FP_ZERO)
      return detail::get_smallest_value<T>();
   //
   // This code is almost the same as that for float_next, except for negative integers,
   // where we preserve the relation ulp(x) == ulp(-x) as does Java:
   //
   expon = 1 + ilogb(fabs(val));
   T diff = scalbn(T(1), expon - std::numeric_limits<T>::digits);
   if(diff == 0)
      diff = detail::get_smallest_value<T>();
   return diff;
}

}

template <class T, class Policy>
inline typename tools::promote_args<T>::type ulp(const T& val, const Policy& pol)
{
   typedef typename tools::promote_args<T>::type result_type;
   return detail::ulp_imp(static_cast<result_type>(val), boost::integral_constant<bool, !std::numeric_limits<result_type>::is_specialized || (std::numeric_limits<result_type>::radix == 2)>(), pol);
}

template <class T>
inline typename tools::promote_args<T>::type ulp(const T& val)
{
   return ulp(val, policies::policy<>());
}


}} // namespaces

#endif // BOOST_MATH_SPECIAL_ULP_HPP


/* ulp.hpp
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
*/