// Copyright John Maddock 2006, 2007.
// Copyright Paul A. Bristow 2008, 2010.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTRIBUTIONS_CHI_SQUARED_HPP
#define BOOST_MATH_DISTRIBUTIONS_CHI_SQUARED_HPP

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/gamma.hpp> // for incomplete beta.
#include <boost/math/distributions/complement.hpp> // complements
#include <boost/math/distributions/detail/common_error_handling.hpp> // error checks
#include <boost/math/special_functions/fpclassify.hpp>

#include <utility>

namespace boost{ namespace math{

template <class RealType = double, class Policy = policies::policy<> >
class chi_squared_distribution
{
public:
   typedef RealType value_type;
   typedef Policy policy_type;

   chi_squared_distribution(RealType i) : m_df(i)
   {
      RealType result;
      detail::check_df(
         "boost::math::chi_squared_distribution<%1%>::chi_squared_distribution", m_df, &result, Policy());
   } // chi_squared_distribution

   RealType degrees_of_freedom()const
   {
      return m_df;
   }

   // Parameter estimation:
   static RealType find_degrees_of_freedom(
      RealType difference_from_variance,
      RealType alpha,
      RealType beta,
      RealType variance,
      RealType hint = 100);

private:
   //
   // Data member:
   //
   RealType m_df; // degrees of freedom is a positive real number.
}; // class chi_squared_distribution

typedef chi_squared_distribution<double> chi_squared;

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4127)
#endif

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const chi_squared_distribution<RealType, Policy>& /*dist*/)
{ // Range of permissible values for random variable x.
  if (std::numeric_limits<RealType>::has_infinity)
  { 
    return std::pair<RealType, RealType>(static_cast<RealType>(0), std::numeric_limits<RealType>::infinity()); // 0 to + infinity.
  }
  else
  {
    using boost::math::tools::max_value;
    return std::pair<RealType, RealType>(static_cast<RealType>(0), max_value<RealType>()); // 0 to + max.
  }
}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const chi_squared_distribution<RealType, Policy>& /*dist*/)
{ // Range of supported values for random variable x.
   // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
   return std::pair<RealType, RealType>(static_cast<RealType>(0), tools::max_value<RealType>()); // 0 to + infinity.
}

template <class RealType, class Policy>
RealType pdf(const chi_squared_distribution<RealType, Policy>& dist, const RealType& chi_square)
{
   BOOST_MATH_STD_USING  // for ADL of std functions
   RealType degrees_of_freedom = dist.degrees_of_freedom();
   // Error check:
   RealType error_result;

   static const char* function = "boost::math::pdf(const chi_squared_distribution<%1%>&, %1%)";

   if(false == detail::check_df(
         function, degrees_of_freedom, &error_result, Policy()))
      return error_result;

   if((chi_square < 0) || !(boost::math::isfinite)(chi_square))
   {
      return policies::raise_domain_error<RealType>(
         function, "Chi Square parameter was %1%, but must be > 0 !", chi_square, Policy());
   }

   if(chi_square == 0)
   {
      // Handle special cases:
      if(degrees_of_freedom < 2)
      {
         return policies::raise_overflow_error<RealType>(
            function, 0, Policy());
      }
      else if(degrees_of_freedom == 2)
      {
         return 0.5f;
      }
      else
      {
         return 0;
      }
   }

   return gamma_p_derivative(degrees_of_freedom / 2, chi_square / 2, Policy()) / 2;
} // pdf

template <class RealType, class Policy>
inline RealType cdf(const chi_squared_distribution<RealType, Policy>& dist, const RealType& chi_square)
{
   RealType degrees_of_freedom = dist.degrees_of_freedom();
   // Error check:
   RealType error_result;
   static const char* function = "boost::math::cdf(const chi_squared_distribution<%1%>&, %1%)";

   if(false == detail::check_df(
         function, degrees_of_freedom, &error_result, Policy()))
      return error_result;

   if((chi_square < 0) || !(boost::math::isfinite)(chi_square))
   {
      return policies::raise_domain_error<RealType>(
         function, "Chi Square parameter was %1%, but must be > 0 !", chi_square, Policy());
   }

   return boost::math::gamma_p(degrees_of_freedom / 2, chi_square / 2, Policy());
} // cdf

template <class RealType, class Policy>
inline RealType quantile(const chi_squared_distribution<RealType, Policy>& dist, const RealType& p)
{
   RealType degrees_of_freedom = dist.degrees_of_freedom();
   static const char* function = "boost::math::quantile(const chi_squared_distribution<%1%>&, %1%)";
   // Error check:
   RealType error_result;
   if(false ==
     (
       detail::check_df(function, degrees_of_freedom, &error_result, Policy())
       && detail::check_probability(function, p, &error_result, Policy()))
     )
     return error_result;

   return 2 * boost::math::gamma_p_inv(degrees_of_freedom / 2, p, Policy());
} // quantile

template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<chi_squared_distribution<RealType, Policy>, RealType>& c)
{
   RealType const& degrees_of_freedom = c.dist.degrees_of_freedom();
   RealType const& chi_square = c.param;
   static const char* function = "boost::math::cdf(const chi_squared_distribution<%1%>&, %1%)";
   // Error check:
   RealType error_result;
   if(false == detail::check_df(
         function, degrees_of_freedom, &error_result, Policy()))
      return error_result;

   if((chi_square < 0) || !(boost::math::isfinite)(chi_square))
   {
      return policies::raise_domain_error<RealType>(
         function, "Chi Square parameter was %1%, but must be > 0 !", chi_square, Policy());
   }

   return boost::math::gamma_q(degrees_of_freedom / 2, chi_square / 2, Policy());
}

template <class RealType, class Policy>
inline RealType quantile(const complemented2_type<chi_squared_distribution<RealType, Policy>, RealType>& c)
{
   RealType const& degrees_of_freedom = c.dist.degrees_of_freedom();
   RealType const& q = c.param;
   static const char* function = "boost::math::quantile(const chi_squared_distribution<%1%>&, %1%)";
   // Error check:
   RealType error_result;
   if(false == (
     detail::check_df(function, degrees_of_freedom, &error_result, Policy())
     && detail::check_probability(function, q, &error_result, Policy()))
     )
    return error_result;

   return 2 * boost::math::gamma_q_inv(degrees_of_freedom / 2, q, Policy());
}

template <class RealType, class Policy>
inline RealType mean(const chi_squared_distribution<RealType, Policy>& dist)
{ // Mean of Chi-Squared distribution = v.
  return dist.degrees_of_freedom();
} // mean

template <class RealType, class Policy>
inline RealType variance(const chi_squared_distribution<RealType, Policy>& dist)
{ // Variance of Chi-Squared distribution = 2v.
  return 2 * dist.degrees_of_freedom();
} // variance

template <class RealType, class Policy>
inline RealType mode(const chi_squared_distribution<RealType, Policy>& dist)
{
   RealType df = dist.degrees_of_freedom();
   static const char* function = "boost::math::mode(const chi_squared_distribution<%1%>&)";
   // Most sources only define mode for df >= 2,
   // but for 0 <= df <= 2, the pdf maximum actually occurs at random variate = 0;
   // So one could extend the definition of mode thus:
   //if(df < 0)
   //{
   //   return policies::raise_domain_error<RealType>(
   //      function,
   //      "Chi-Squared distribution only has a mode for degrees of freedom >= 0, but got degrees of freedom = %1%.",
   //      df, Policy());
   //}
   //return (df <= 2) ? 0 : df - 2;

   if(df < 2)
      return policies::raise_domain_error<RealType>(
         function,
         "Chi-Squared distribution only has a mode for degrees of freedom >= 2, but got degrees of freedom = %1%.",
         df, Policy());
   return df - 2;
}

//template <class RealType, class Policy>
//inline RealType median(const chi_squared_distribution<RealType, Policy>& dist)
//{ // Median is given by Quantile[dist, 1/2]
//   RealType df = dist.degrees_of_freedom();
//   if(df <= 1)
//      return tools::domain_error<RealType>(
//         BOOST_CURRENT_FUNCTION,
//         "The Chi-Squared distribution only has a mode for degrees of freedom >= 2, but got degrees of freedom = %1%.",
//         df);
//   return df - RealType(2)/3;
//}
// Now implemented via quantile(half) in derived accessors.

template <class RealType, class Policy>
inline RealType skewness(const chi_squared_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING // For ADL
   RealType df = dist.degrees_of_freedom();
   return sqrt (8 / df);  // == 2 * sqrt(2 / df);
}

template <class RealType, class Policy>
inline RealType kurtosis(const chi_squared_distribution<RealType, Policy>& dist)
{
   RealType df = dist.degrees_of_freedom();
   return 3 + 12 / df;
}

template <class RealType, class Policy>
inline RealType kurtosis_excess(const chi_squared_distribution<RealType, Policy>& dist)
{
   RealType df = dist.degrees_of_freedom();
   return 12 / df;
}

//
// Parameter estimation comes last:
//
namespace detail
{

template <class RealType, class Policy>
struct df_estimator
{
   df_estimator(RealType a, RealType b, RealType variance, RealType delta)
      : alpha(a), beta(b), ratio(delta/variance)
   { // Constructor
   }

   RealType operator()(const RealType& df)
   {
      if(df <= tools::min_value<RealType>())
         return 1;
      chi_squared_distribution<RealType, Policy> cs(df);

      RealType result;
      if(ratio > 0)
      {
         RealType r = 1 + ratio;
         result = cdf(cs, quantile(complement(cs, alpha)) / r) - beta;
      }
      else
      { // ratio <= 0
         RealType r = 1 + ratio;
         result = cdf(complement(cs, quantile(cs, alpha) / r)) - beta;
      }
      return result;
   }
private:
   RealType alpha;
   RealType beta;
   RealType ratio; // Difference from variance / variance, so fractional.
};

} // namespace detail

template <class RealType, class Policy>
RealType chi_squared_distribution<RealType, Policy>::find_degrees_of_freedom(
   RealType difference_from_variance,
   RealType alpha,
   RealType beta,
   RealType variance,
   RealType hint)
{
   static const char* function = "boost::math::chi_squared_distribution<%1%>::find_degrees_of_freedom(%1%,%1%,%1%,%1%,%1%)";
   // Check for domain errors:
   RealType error_result;
   if(false ==
     detail::check_probability(function, alpha, &error_result, Policy())
     && detail::check_probability(function, beta, &error_result, Policy()))
   { // Either probability is outside 0 to 1.
      return error_result;
   }

   if(hint <= 0)
   { // No hint given, so guess df = 1.
      hint = 1;
   }

   detail::df_estimator<RealType, Policy> f(alpha, beta, variance, difference_from_variance);
   tools::eps_tolerance<RealType> tol(policies::digits<RealType, Policy>());
   boost::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
   std::pair<RealType, RealType> r =
     tools::bracket_and_solve_root(f, hint, RealType(2), false, tol, max_iter, Policy());
   RealType result = r.first + (r.second - r.first) / 2;
   if(max_iter >= policies::get_max_root_iterations<Policy>())
   {
      policies::raise_evaluation_error<RealType>(function, "Unable to locate solution in a reasonable time:"
         " either there is no answer to how many degrees of freedom are required"
         " or the answer is infinite.  Current best guess is %1%", result, Policy());
   }
   return result;
}

} // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_MATH_DISTRIBUTIONS_CHI_SQUARED_HPP

/* chi_squared.hpp
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
*/