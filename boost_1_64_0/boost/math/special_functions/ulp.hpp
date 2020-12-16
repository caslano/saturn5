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
5p0CPaKvUgd52gSvVgdbVOgTy7nGOmWGJF9jHVBiSOS1+kOWJhOSr9MWOVpMWcobG/LsMSX5emXZocmU1BvETZ49piTeKB9F+kQK5oZt6kxJv0k5dukTebP+kaHFlOW3eD0hR4N9orvmlTMU6BF+q/o4TYUewdvExilyNBmz+HbtsE2VAZGiOlmnSIc5qXcoT44mYxbfqTzbVBkQeZfyrFOkw5xUSXlyNBmz+G7l2abKgMh7lGedIh3mpN6rPDmaBGXPI1k6RN9nnNllQOL9xpQKfWIfMO5kaRGqaIczlAh/0HgzJf0h7VNhn8SHtc0uPaJVcZNljzkrH/E8UWPM0ke1T4kB8Y+JjzwdwjXxk6HJjOWPmzfK9Fj8hJjJ0iH2SWuaLVqE6saFk2TokfqUWKkzIPJpZdigRJfIZ/SddYr0CTdcY50KfSKfdY0t6gyIf06/CL3iQLArHRD6vDbYoEyHoKk/bFFiyLEvmGcSX9QvsrQIvmS8WKPEgHhLnay1/D2rtMY+8S97PWSHFlNWviJuygyIf1UetqkyJLqnPjYoMSL+NfVTIPJ140iWEclvmC9aBG1rgjwd5ix9U34K7DEh8S3XyDJm8dv6TJYGU5IdbVKgS/AdcbFBlQGL37U2yFEn+J722aLOnHTXOVWWvq88ZcYs/kAbFBgQ+aG+sEOXOUd6ytNixuaPrEMmrPzYeFJnzPJPnFNnwkrf2LLHlNWL1U2HOUd+KnZ6hH6mf2zTZEJqYJ1Tokf058qQo8WE5C88mxTpEPxSH9nn9NAaZZ/0r5xToU/Sz7YZmoxI/sacsMuA8L542aDKPku/lYcCXUK/02fWqTAg9ntrliwdQiP1kKHOiKU/iJkKA6J/tA7J0ya4RD/JUGPC0thcscuA5J/cp8qA6KXaoUyfxGViJUuTGSsT80ed4M/ys0GVGct/ERclRiz+1XogR5fIVBm2qDNk8W/aoU347+ogwz7xf+gH21QYEJ65xgYVeoT/qRzr7NJhxvK/zBm7tJmT/rcYKdBmytpcHjoE/zFWnCJHixGL/zUvbFNlRPR/njt2aDFnJfCeBS2mJK7gvR+2qTHgsPcWy/QJH/A+I+uU6BIKeW+EM+zSJ3zQey5s0WDK8oL3KijTJ35IHrapEg17D4Uu4StphzIDIme5xxY1RiTOFitZGkxIRLwvRZYWE5au7Bp5WsxYuor3lsjRZEryqt4HosyIdNQ5ZbrEryZe8vRJXF377DIkeQ3vIVGkSzzmPju0mJG6pvd/KDMifi1tUGZE/NrOKTMiHlcHu/QJXce4sEObKalzjAtNRixe1zhToktoUdxkaTAmdT3vPVFhQOz6YidDnQnJGxgjCvQIJ8wBWzQYk7yhPJQZEr+ReijSJ3Zj8VOgSyQpFnK0mZK+ifVEhR7Rm+ojW1TYZ/Fm5pAcbWYsLylHhSHxm4uPDFVGxG6hfXZoMSF1S+WoMCSaUjdNpizdyhyQp0P4XPGwSYV90re23inSJ5lWB3m6hG4jPjLsMSN5W3NPlTHx2xk7CgyJLBs7MnQI31677NBlztE7GBf2mHHkjs6psU9iRR7yNAjuJA42qDAidp52KTIidmfrhTwDwqv6Qp5TPkMzkKbu4hpF2rTuZG+P88VLli6hu3rfkQwVBoQP6wNnKNIjfDf5yNJkxsrdjS8VRizeQxmKjEgcMWeUmbB0T/cpMSR+L7FSoEf03togS5sZh4+qgzr7LN1HGUp0id/X2JGjwZwj93NOk9Ax98nSILi/c/K0iTxAG2RpEX6gvpOhxozUcfNFjTkrD3KfGjNSFxgHqsxYfrD71JiRPmG9sfQQa+TaXv/jvkZwil3azEl537d3S38=
*/