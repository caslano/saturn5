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

#ifdef BOOST_MSVC
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

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif

#endif // BOOST_MATH_DISTRIBUTIONS_COMMON_ERROR_HANDLING_HPP

/* common_error_handling.hpp
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
*/