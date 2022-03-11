// Copyright John Maddock 2010.
// Copyright Paul A. Bristow 2010.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTRIBUTIONS_INVERSE_CHI_SQUARED_HPP
#define BOOST_MATH_DISTRIBUTIONS_INVERSE_CHI_SQUARED_HPP

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/gamma.hpp> // for incomplete beta.
#include <boost/math/distributions/complement.hpp> // for complements.
#include <boost/math/distributions/detail/common_error_handling.hpp> // for error checks.
#include <boost/math/special_functions/fpclassify.hpp> // for isfinite

// See http://en.wikipedia.org/wiki/Scaled-inverse-chi-square_distribution
// for definitions of this scaled version.
// See http://en.wikipedia.org/wiki/Inverse-chi-square_distribution
// for unscaled version.

// http://reference.wolfram.com/mathematica/ref/InverseChiSquareDistribution.html
// Weisstein, Eric W. "Inverse Chi-Squared Distribution." From MathWorld--A Wolfram Web Resource.
// http://mathworld.wolfram.com/InverseChi-SquaredDistribution.html

#include <utility>

namespace boost{ namespace math{

namespace detail
{
  template <class RealType, class Policy>
  inline bool check_inverse_chi_squared( // Check both distribution parameters.
        const char* function,
        RealType degrees_of_freedom, // degrees_of_freedom (aka nu).
        RealType scale,  // scale (aka sigma^2)
        RealType* result,
        const Policy& pol)
  {
     return check_scale(function, scale, result, pol)
       && check_df(function, degrees_of_freedom,
       result, pol);
  } // bool check_inverse_chi_squared
} // namespace detail

template <class RealType = double, class Policy = policies::policy<> >
class inverse_chi_squared_distribution
{
public:
   typedef RealType value_type;
   typedef Policy policy_type;

   inverse_chi_squared_distribution(RealType df, RealType l_scale) : m_df(df), m_scale (l_scale)
   {
      RealType result;
      detail::check_df(
         "boost::math::inverse_chi_squared_distribution<%1%>::inverse_chi_squared_distribution",
         m_df, &result, Policy())
         && detail::check_scale(
"boost::math::inverse_chi_squared_distribution<%1%>::inverse_chi_squared_distribution",
         m_scale, &result,  Policy());
   } // inverse_chi_squared_distribution constructor 

   inverse_chi_squared_distribution(RealType df = 1) : m_df(df)
   {
      RealType result;
      m_scale = 1 / m_df ; // Default scale = 1 / degrees of freedom (Wikipedia definition 1).
      detail::check_df(
         "boost::math::inverse_chi_squared_distribution<%1%>::inverse_chi_squared_distribution",
         m_df, &result, Policy());
   } // inverse_chi_squared_distribution

   RealType degrees_of_freedom()const
   {
      return m_df; // aka nu
   }
   RealType scale()const
   {
      return m_scale;  // aka xi
   }

   // Parameter estimation:  NOT implemented yet.
   //static RealType find_degrees_of_freedom(
   //   RealType difference_from_variance,
   //   RealType alpha,
   //   RealType beta,
   //   RealType variance,
   //   RealType hint = 100);

private:
   // Data members:
   RealType m_df;  // degrees of freedom are treated as a real number.
   RealType m_scale;  // distribution scale.

}; // class chi_squared_distribution

typedef inverse_chi_squared_distribution<double> inverse_chi_squared;

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const inverse_chi_squared_distribution<RealType, Policy>& /*dist*/)
{  // Range of permissible values for random variable x.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(static_cast<RealType>(0), max_value<RealType>()); // 0 to + infinity.
}

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const inverse_chi_squared_distribution<RealType, Policy>& /*dist*/)
{  // Range of supported values for random variable x.
   // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
   return std::pair<RealType, RealType>(static_cast<RealType>(0), tools::max_value<RealType>()); // 0 to + infinity.
}

template <class RealType, class Policy>
RealType pdf(const inverse_chi_squared_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING  // for ADL of std functions.
   RealType df = dist.degrees_of_freedom();
   RealType scale = dist.scale();
   RealType error_result;

   static const char* function = "boost::math::pdf(const inverse_chi_squared_distribution<%1%>&, %1%)";

   if(false == detail::check_inverse_chi_squared
     (function, df, scale, &error_result, Policy())
     )
   { // Bad distribution.
      return error_result;
   }
   if((x < 0) || !(boost::math::isfinite)(x))
   { // Bad x.
      return policies::raise_domain_error<RealType>(
         function, "inverse Chi Square parameter was %1%, but must be >= 0 !", x, Policy());
   }

   if(x == 0)
   { // Treat as special case.
     return 0;
   }
   // Wikipedia scaled inverse chi sq (df, scale) related to inv gamma (df/2, df * scale /2) 
   // so use inverse gamma pdf with shape = df/2, scale df * scale /2 
   // RealType shape = df /2; // inv_gamma shape
   // RealType scale = df * scale/2; // inv_gamma scale
   // RealType result = gamma_p_derivative(shape, scale / x, Policy()) * scale / (x * x);
   RealType result = df * scale/2 / x;
   if(result < tools::min_value<RealType>())
      return 0; // Random variable is near enough infinite.
   result = gamma_p_derivative(df/2, result, Policy()) * df * scale/2;
   if(result != 0) // prevent 0 / 0,  gamma_p_derivative -> 0 faster than x^2
      result /= (x * x);
   return result;
} // pdf

template <class RealType, class Policy>
inline RealType cdf(const inverse_chi_squared_distribution<RealType, Policy>& dist, const RealType& x)
{
   static const char* function = "boost::math::cdf(const inverse_chi_squared_distribution<%1%>&, %1%)";
   RealType df = dist.degrees_of_freedom();
   RealType scale = dist.scale();
   RealType error_result;

   if(false ==
       detail::check_inverse_chi_squared(function, df, scale, &error_result, Policy())
     )
   { // Bad distribution.
      return error_result;
   }
   if((x < 0) || !(boost::math::isfinite)(x))
   { // Bad x.
      return policies::raise_domain_error<RealType>(
         function, "inverse Chi Square parameter was %1%, but must be >= 0 !", x, Policy());
   }
   if (x == 0)
   { // Treat zero as a special case.
     return 0;
   }
   // RealType shape = df /2; // inv_gamma shape,
   // RealType scale = df * scale/2; // inv_gamma scale,
   // result = boost::math::gamma_q(shape, scale / x, Policy()); // inverse_gamma code.
   return boost::math::gamma_q(df / 2, (df * (scale / 2)) / x, Policy());
} // cdf

template <class RealType, class Policy>
inline RealType quantile(const inverse_chi_squared_distribution<RealType, Policy>& dist, const RealType& p)
{
   using boost::math::gamma_q_inv;
   RealType df = dist.degrees_of_freedom();
   RealType scale = dist.scale();

   static const char* function = "boost::math::quantile(const inverse_chi_squared_distribution<%1%>&, %1%)";
   // Error check:
   RealType error_result;
   if(false == detail::check_df(
         function, df, &error_result, Policy())
         && detail::check_probability(
            function, p, &error_result, Policy()))
   {
      return error_result;
   }
   if(false == detail::check_probability(
            function, p, &error_result, Policy()))
   {
      return error_result;
   }
   // RealType shape = df /2; // inv_gamma shape,
   // RealType scale = df * scale/2; // inv_gamma scale,
   // result = scale / gamma_q_inv(shape, p, Policy());
      RealType result = gamma_q_inv(df /2, p, Policy());
      if(result == 0)
         return policies::raise_overflow_error<RealType, Policy>(function, "Random variable is infinite.", Policy());
      result = df * (scale / 2) / result;
      return result;
} // quantile

template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<inverse_chi_squared_distribution<RealType, Policy>, RealType>& c)
{
   using boost::math::gamma_q_inv;
   RealType const& df = c.dist.degrees_of_freedom();
   RealType const& scale = c.dist.scale();
   RealType const& x = c.param;
   static const char* function = "boost::math::cdf(const inverse_chi_squared_distribution<%1%>&, %1%)";
   // Error check:
   RealType error_result;
   if(false == detail::check_df(
         function, df, &error_result, Policy()))
   {
      return error_result;
   }
   if (x == 0)
   { // Treat zero as a special case.
     return 1;
   }
   if((x < 0) || !(boost::math::isfinite)(x))
   {
      return policies::raise_domain_error<RealType>(
         function, "inverse Chi Square parameter was %1%, but must be > 0 !", x, Policy());
   }
   // RealType shape = df /2; // inv_gamma shape,
   // RealType scale = df * scale/2; // inv_gamma scale,
   // result = gamma_p(shape, scale/c.param, Policy()); use inv_gamma.

   return gamma_p(df / 2, (df * scale/2) / x, Policy()); // OK
} // cdf(complemented

template <class RealType, class Policy>
inline RealType quantile(const complemented2_type<inverse_chi_squared_distribution<RealType, Policy>, RealType>& c)
{
   using boost::math::gamma_q_inv;

   RealType const& df = c.dist.degrees_of_freedom();
   RealType const& scale = c.dist.scale();
   RealType const& q = c.param;
   static const char* function = "boost::math::quantile(const inverse_chi_squared_distribution<%1%>&, %1%)";
   // Error check:
   RealType error_result;
   if(false == detail::check_df(function, df, &error_result, Policy()))
   {
      return error_result;
   }
   if(false == detail::check_probability(function, q, &error_result, Policy()))
   {
      return error_result;
   }
   // RealType shape = df /2; // inv_gamma shape,
   // RealType scale = df * scale/2; // inv_gamma scale,
   // result = scale / gamma_p_inv(shape, q, Policy());  // using inv_gamma.
   RealType result = gamma_p_inv(df/2, q, Policy());
   if(result == 0)
      return policies::raise_overflow_error<RealType, Policy>(function, "Random variable is infinite.", Policy());
   result = (df * scale / 2) / result;
   return result;
} // quantile(const complement

template <class RealType, class Policy>
inline RealType mean(const inverse_chi_squared_distribution<RealType, Policy>& dist)
{ // Mean of inverse Chi-Squared distribution.
   RealType df = dist.degrees_of_freedom();
   RealType scale = dist.scale();

   static const char* function = "boost::math::mean(const inverse_chi_squared_distribution<%1%>&)";
   if(df <= 2)
      return policies::raise_domain_error<RealType>(
         function,
         "inverse Chi-Squared distribution only has a mode for degrees of freedom > 2, but got degrees of freedom = %1%.",
         df, Policy());
  return (df * scale) / (df - 2);
} // mean

template <class RealType, class Policy>
inline RealType variance(const inverse_chi_squared_distribution<RealType, Policy>& dist)
{ // Variance of inverse Chi-Squared distribution.
   RealType df = dist.degrees_of_freedom();
   RealType scale = dist.scale();
   static const char* function = "boost::math::variance(const inverse_chi_squared_distribution<%1%>&)";
   if(df <= 4)
   {
      return policies::raise_domain_error<RealType>(
         function,
         "inverse Chi-Squared distribution only has a variance for degrees of freedom > 4, but got degrees of freedom = %1%.",
         df, Policy());
   }
   return 2 * df * df * scale * scale / ((df - 2)*(df - 2) * (df - 4));
} // variance

template <class RealType, class Policy>
inline RealType mode(const inverse_chi_squared_distribution<RealType, Policy>& dist)
{ // mode is not defined in Mathematica.
  // See Discussion section http://en.wikipedia.org/wiki/Talk:Scaled-inverse-chi-square_distribution
  // for origin of the formula used below.

   RealType df = dist.degrees_of_freedom();
   RealType scale = dist.scale();
   static const char* function = "boost::math::mode(const inverse_chi_squared_distribution<%1%>&)";
   if(df < 0)
      return policies::raise_domain_error<RealType>(
         function,
         "inverse Chi-Squared distribution only has a mode for degrees of freedom >= 0, but got degrees of freedom = %1%.",
         df, Policy());
   return (df * scale) / (df + 2);
}

//template <class RealType, class Policy>
//inline RealType median(const inverse_chi_squared_distribution<RealType, Policy>& dist)
//{ // Median is given by Quantile[dist, 1/2]
//   RealType df = dist.degrees_of_freedom();
//   if(df <= 1)
//      return tools::domain_error<RealType>(
//         BOOST_CURRENT_FUNCTION,
//         "The inverse_Chi-Squared distribution only has a median for degrees of freedom >= 0, but got degrees of freedom = %1%.",
//         df);
//   return df;
//}
// Now implemented via quantile(half) in derived accessors.

template <class RealType, class Policy>
inline RealType skewness(const inverse_chi_squared_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING // For ADL
   RealType df = dist.degrees_of_freedom();
   static const char* function = "boost::math::skewness(const inverse_chi_squared_distribution<%1%>&)";
   if(df <= 6)
      return policies::raise_domain_error<RealType>(
         function,
         "inverse Chi-Squared distribution only has a skewness for degrees of freedom > 6, but got degrees of freedom = %1%.",
         df, Policy());

   return 4 * sqrt (2 * (df - 4)) / (df - 6);  // Not a function of scale.
}

template <class RealType, class Policy>
inline RealType kurtosis(const inverse_chi_squared_distribution<RealType, Policy>& dist)
{
   RealType df = dist.degrees_of_freedom();
   static const char* function = "boost::math::kurtosis(const inverse_chi_squared_distribution<%1%>&)";
   if(df <= 8)
      return policies::raise_domain_error<RealType>(
         function,
         "inverse Chi-Squared distribution only has a kurtosis for degrees of freedom > 8, but got degrees of freedom = %1%.",
         df, Policy());

   return kurtosis_excess(dist) + 3;
}

template <class RealType, class Policy>
inline RealType kurtosis_excess(const inverse_chi_squared_distribution<RealType, Policy>& dist)
{
   RealType df = dist.degrees_of_freedom();
   static const char* function = "boost::math::kurtosis(const inverse_chi_squared_distribution<%1%>&)";
   if(df <= 8)
      return policies::raise_domain_error<RealType>(
         function,
         "inverse Chi-Squared distribution only has a kurtosis excess for degrees of freedom > 8, but got degrees of freedom = %1%.",
         df, Policy());

   return 12 * (5 * df - 22) / ((df - 6 )*(df - 8));  // Not a function of scale.
}

//
// Parameter estimation comes last:
//

} // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_MATH_DISTRIBUTIONS_INVERSE_CHI_SQUARED_HPP

/* inverse_chi_squared.hpp
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
*/