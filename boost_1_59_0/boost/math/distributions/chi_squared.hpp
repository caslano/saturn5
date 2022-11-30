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

#ifdef __cpp_deduction_guides
template <class RealType>
chi_squared_distribution(RealType)->chi_squared_distribution<typename boost::math::tools::promote_args<RealType>::type>;
#endif

#ifdef _MSC_VER
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

#ifdef _MSC_VER
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
   std::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
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