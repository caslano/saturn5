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

#ifdef __cpp_deduction_guides
template <class RealType>
inverse_chi_squared_distribution(RealType)->inverse_chi_squared_distribution<typename boost::math::tools::promote_args<RealType>::type>;
template <class RealType>
inverse_chi_squared_distribution(RealType,RealType)->inverse_chi_squared_distribution<typename boost::math::tools::promote_args<RealType>::type>;
#endif

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