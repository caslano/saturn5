// Copyright John Maddock 2006, 2007.
// Copyright Paul A. Bristow 2006, 2007, 2012.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTRIBUTIONS_COMMON_ERROR_HANDLING_HPP
#define BOOST_MATH_DISTRIBUTIONS_COMMON_ERROR_HANDLING_HPP

#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
// using boost::math::isfinite;
// using boost::math::isnan;

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable: 4702) // unreachable code (return after domain_error throw).
#endif

namespace boost{ namespace math{ namespace detail
{

template <class RealType, class Policy>
inline bool check_probability(const char* function, RealType const& prob, RealType* result, const Policy& pol)
{
   if((prob < 0) || (prob > 1) || !(boost::math::isfinite)(prob))
   {
      *result = policies::raise_domain_error<RealType>(
         function,
         "Probability argument is %1%, but must be >= 0 and <= 1 !", prob, pol);
      return false;
   }
   return true;
}

template <class RealType, class Policy>
inline bool check_df(const char* function, RealType const& df, RealType* result, const Policy& pol)
{ //  df > 0 but NOT +infinity allowed.
   if((df <= 0) || !(boost::math::isfinite)(df))
   {
      *result = policies::raise_domain_error<RealType>(
         function,
         "Degrees of freedom argument is %1%, but must be > 0 !", df, pol);
      return false;
   }
   return true;
}

template <class RealType, class Policy>
inline bool check_df_gt0_to_inf(const char* function, RealType const& df, RealType* result, const Policy& pol)
{  // df > 0 or +infinity are allowed.
   if( (df <= 0) || (boost::math::isnan)(df) )
   { // is bad df <= 0 or NaN or -infinity.
      *result = policies::raise_domain_error<RealType>(
         function,
         "Degrees of freedom argument is %1%, but must be > 0 !", df, pol);
      return false;
   }
   return true;
} // check_df_gt0_to_inf


template <class RealType, class Policy>
inline bool check_scale(
      const char* function,
      RealType scale,
      RealType* result,
      const Policy& pol)
{
   if((scale <= 0) || !(boost::math::isfinite)(scale))
   { // Assume scale == 0 is NOT valid for any distribution.
      *result = policies::raise_domain_error<RealType>(
         function,
         "Scale parameter is %1%, but must be > 0 !", scale, pol);
      return false;
   }
   return true;
}

template <class RealType, class Policy>
inline bool check_location(
      const char* function,
      RealType location,
      RealType* result,
      const Policy& pol)
{
   if(!(boost::math::isfinite)(location))
   {
      *result = policies::raise_domain_error<RealType>(
         function,
         "Location parameter is %1%, but must be finite!", location, pol);
      return false;
   }
   return true;
}

template <class RealType, class Policy>
inline bool check_x(
      const char* function,
      RealType x,
      RealType* result,
      const Policy& pol)
{
   // Note that this test catches both infinity and NaN.
   // Some distributions permit x to be infinite, so these must be tested 1st and return,
   // leaving this test to catch any NaNs.
   // See Normal, Logistic, Laplace and Cauchy for example.
   if(!(boost::math::isfinite)(x))
   {
      *result = policies::raise_domain_error<RealType>(
         function,
         "Random variate x is %1%, but must be finite!", x, pol);
      return false;
   }
   return true;
} // bool check_x

template <class RealType, class Policy>
inline bool check_x_not_NaN(
  const char* function,
  RealType x,
  RealType* result,
  const Policy& pol)
{
  // Note that this test catches only NaN.
  // Some distributions permit x to be infinite, leaving this test to catch any NaNs.
  // See Normal, Logistic, Laplace and Cauchy for example.
  if ((boost::math::isnan)(x))
  {
    *result = policies::raise_domain_error<RealType>(
      function,
      "Random variate x is %1%, but must be finite or + or - infinity!", x, pol);
    return false;
  }
  return true;
} // bool check_x_not_NaN

template <class RealType, class Policy>
inline bool check_x_gt0(
      const char* function,
      RealType x,
      RealType* result,
      const Policy& pol)
{
   if(x <= 0)
   {
      *result = policies::raise_domain_error<RealType>(
         function,
         "Random variate x is %1%, but must be > 0!", x, pol);
      return false;
   }

   return true;
   // Note that this test catches both infinity and NaN.
   // Some special cases permit x to be infinite, so these must be tested 1st,
   // leaving this test to catch any NaNs.  See Normal and cauchy for example.
} // bool check_x_gt0

template <class RealType, class Policy>
inline bool check_positive_x(
      const char* function,
      RealType x,
      RealType* result,
      const Policy& pol)
{
   if(!(boost::math::isfinite)(x) || (x < 0))
   {
      *result = policies::raise_domain_error<RealType>(
         function,
         "Random variate x is %1%, but must be finite and >= 0!", x, pol);
      return false;
   }
   return true;
   // Note that this test catches both infinity and NaN.
   // Some special cases permit x to be infinite, so these must be tested 1st,
   // leaving this test to catch any NaNs.  see Normal and cauchy for example.
}

template <class RealType, class Policy>
inline bool check_non_centrality(
      const char* function,
      RealType ncp,
      RealType* result,
      const Policy& pol)
{
   if((ncp < 0) || !(boost::math::isfinite)(ncp))
   { // Assume scale == 0 is NOT valid for any distribution.
      *result = policies::raise_domain_error<RealType>(
         function,
         "Non centrality parameter is %1%, but must be > 0 !", ncp, pol);
      return false;
   }
   return true;
}

template <class RealType, class Policy>
inline bool check_finite(
      const char* function,
      RealType x,
      RealType* result,
      const Policy& pol)
{
   if(!(boost::math::isfinite)(x))
   { // Assume scale == 0 is NOT valid for any distribution.
      *result = policies::raise_domain_error<RealType>(
         function,
         "Parameter is %1%, but must be finite !", x, pol);
      return false;
   }
   return true;
}

} // namespace detail
} // namespace math
} // namespace boost

#ifdef _MSC_VER
#  pragma warning(pop)
#endif

#endif // BOOST_MATH_DISTRIBUTIONS_COMMON_ERROR_HANDLING_HPP

/* common_error_handling.hpp
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
*/