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
ZWxcyxkG4GuIfWPXzEyJGWJmppgTMzMzrRljhpghZmZmZmZmZua117DrLahVq7ZqK1XnSEdnZjT/39F83yP+siOnUpwSElZsy1vo7Kc/Pu6fYF2++mqiw6SVsVdX59eWLoZEE+dI+Z6enejEInIBJCpMPMde+CXkmfNPhSPvK0J3/nUefxv41w80JxsK++eSH1VF/Y4G9j9V9NT+p5If+n/bspP17y07xS3NTGz+3rPzwoFoJbknDPOxEGtNnZgfkBCxP+pmvLYfV19I2/ypW2yIZajRjL9ZPHYwnoOVU9U8NAWHm4i+KaOYaMiJS5GMNg87fAGNbq59gwmWo4P2T4nuzaxFM5dsXgzSuMWUjqbVCBjIfvu1F55g+f3U7/dZ79uMNz5QpveMIGib4gb8xsLld7+1gQZOTwoJKgz10bf9BKhmQzfMCyFHnPHXZ8S92t/fGcCjB3/Y6/PcYDyei2LNevCSgMvHmAu2lHpGJ0IHkV8fMYtwUXJFNFfh79DM+6MZRDtmmsYxUsbTzrFyjdq+qH9jtaXQt5hSEW5d3zc5Ej5YYuW+uU2Ert15PwjnppiT7pvpJ5BrsYUUftkSX41yuozvk2XMN9KuyfXHu2Ncc1meP/m4joemhDZocKaEco18FVvjOSr3I9YjoBqlHXe5HIppjFj3CAL5El5HbMZU6/gvHZCJ+RxG9/T4U6fHdDreSsf7XtSKTvAB
*/