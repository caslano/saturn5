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
T ulp_imp(const T& val, const std::true_type&, const Policy& pol)
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
T ulp_imp(const T& val, const std::false_type&, const Policy& pol)
{
   static_assert(std::numeric_limits<T>::is_specialized, "Type T must be specialized.");
   static_assert(std::numeric_limits<T>::radix != 2, "Type T must be specialized.");
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
   return detail::ulp_imp(static_cast<result_type>(val), std::integral_constant<bool, !std::numeric_limits<result_type>::is_specialized || (std::numeric_limits<result_type>::radix == 2)>(), pol);
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