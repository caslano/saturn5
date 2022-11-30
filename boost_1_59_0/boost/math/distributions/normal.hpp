//  Copyright John Maddock 2006, 2007.
//  Copyright Paul A. Bristow 2006, 2007.

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_NORMAL_HPP
#define BOOST_STATS_NORMAL_HPP

// http://en.wikipedia.org/wiki/Normal_distribution
// http://www.itl.nist.gov/div898/handbook/eda/section3/eda3661.htm
// Also:
// Weisstein, Eric W. "Normal Distribution."
// From MathWorld--A Wolfram Web Resource.
// http://mathworld.wolfram.com/NormalDistribution.html

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/erf.hpp> // for erf/erfc.
#include <boost/math/distributions/complement.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>

#include <utility>

namespace boost{ namespace math{

template <class RealType = double, class Policy = policies::policy<> >
class normal_distribution
{
public:
   typedef RealType value_type;
   typedef Policy policy_type;

   normal_distribution(RealType l_mean = 0, RealType sd = 1)
      : m_mean(l_mean), m_sd(sd)
   { // Default is a 'standard' normal distribution N01.
     static const char* function = "boost::math::normal_distribution<%1%>::normal_distribution";

     RealType result;
     detail::check_scale(function, sd, &result, Policy());
     detail::check_location(function, l_mean, &result, Policy());
   }

   RealType mean()const
   { // alias for location.
      return m_mean;
   }

   RealType standard_deviation()const
   { // alias for scale.
      return m_sd;
   }

   // Synonyms, provided to allow generic use of find_location and find_scale.
   RealType location()const
   { // location.
      return m_mean;
   }
   RealType scale()const
   { // scale.
      return m_sd;
   }

private:
   //
   // Data members:
   //
   RealType m_mean;  // distribution mean or location.
   RealType m_sd;    // distribution standard deviation or scale.
}; // class normal_distribution

typedef normal_distribution<double> normal;

//
// Deduction guides, note we don't check the 
// value of __cpp_deduction_guides, just assume
// they work as advertised, even if this is pre-final C++17.
//
#ifdef __cpp_deduction_guides

template <class RealType>
normal_distribution(RealType, RealType)->normal_distribution<typename boost::math::tools::promote_args<RealType>::type>;
template <class RealType>
normal_distribution(RealType)->normal_distribution<typename boost::math::tools::promote_args<RealType>::type>;

#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4127)
#endif

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const normal_distribution<RealType, Policy>& /*dist*/)
{ // Range of permissible values for random variable x.
  if (std::numeric_limits<RealType>::has_infinity)
  { 
     return std::pair<RealType, RealType>(-std::numeric_limits<RealType>::infinity(), std::numeric_limits<RealType>::infinity()); // - to + infinity.
  }
  else
  { // Can only use max_value.
    using boost::math::tools::max_value;
    return std::pair<RealType, RealType>(-max_value<RealType>(), max_value<RealType>()); // - to + max value.
  }
}

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const normal_distribution<RealType, Policy>& /*dist*/)
{ // This is range values for random variable x where cdf rises from 0 to 1, and outside it, the pdf is zero.
  if (std::numeric_limits<RealType>::has_infinity)
  { 
     return std::pair<RealType, RealType>(-std::numeric_limits<RealType>::infinity(), std::numeric_limits<RealType>::infinity()); // - to + infinity.
  }
  else
  { // Can only use max_value.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(-max_value<RealType>(),  max_value<RealType>()); // - to + max value.
  }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

template <class RealType, class Policy>
inline RealType pdf(const normal_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   RealType sd = dist.standard_deviation();
   RealType mean = dist.mean();

   static const char* function = "boost::math::pdf(const normal_distribution<%1%>&, %1%)";

   RealType result = 0;
   if(false == detail::check_scale(function, sd, &result, Policy()))
   {
      return result;
   }
   if(false == detail::check_location(function, mean, &result, Policy()))
   {
      return result;
   }
   if((boost::math::isinf)(x))
   {
     return 0; // pdf + and - infinity is zero.
   }
   // Below produces MSVC 4127 warnings, so the above used instead.
   //if(std::numeric_limits<RealType>::has_infinity && abs(x) == std::numeric_limits<RealType>::infinity())
   //{ // pdf + and - infinity is zero.
   //  return 0;
   //}
   if(false == detail::check_x(function, x, &result, Policy()))
   {
      return result;
   }

   RealType exponent = x - mean;
   exponent *= -exponent;
   exponent /= 2 * sd * sd;

   result = exp(exponent);
   result /= sd * sqrt(2 * constants::pi<RealType>());

   return result;
} // pdf

template <class RealType, class Policy>
inline RealType cdf(const normal_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   RealType sd = dist.standard_deviation();
   RealType mean = dist.mean();
   static const char* function = "boost::math::cdf(const normal_distribution<%1%>&, %1%)";
   RealType result = 0;
   if(false == detail::check_scale(function, sd, &result, Policy()))
   {
      return result;
   }
   if(false == detail::check_location(function, mean, &result, Policy()))
   {
      return result;
   }
   if((boost::math::isinf)(x))
   {
     if(x < 0) return 0; // -infinity
     return 1; // + infinity
   }
   // These produce MSVC 4127 warnings, so the above used instead.
   //if(std::numeric_limits<RealType>::has_infinity && x == std::numeric_limits<RealType>::infinity())
   //{ // cdf +infinity is unity.
   //  return 1;
   //}
   //if(std::numeric_limits<RealType>::has_infinity && x == -std::numeric_limits<RealType>::infinity())
   //{ // cdf -infinity is zero.
   //  return 0;
   //}
   if(false == detail::check_x(function, x, &result, Policy()))
   {
     return result;
   }
   RealType diff = (x - mean) / (sd * constants::root_two<RealType>());
   result = boost::math::erfc(-diff, Policy()) / 2;
   return result;
} // cdf

template <class RealType, class Policy>
inline RealType quantile(const normal_distribution<RealType, Policy>& dist, const RealType& p)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   RealType sd = dist.standard_deviation();
   RealType mean = dist.mean();
   static const char* function = "boost::math::quantile(const normal_distribution<%1%>&, %1%)";

   RealType result = 0;
   if(false == detail::check_scale(function, sd, &result, Policy()))
      return result;
   if(false == detail::check_location(function, mean, &result, Policy()))
      return result;
   if(false == detail::check_probability(function, p, &result, Policy()))
      return result;

   result= boost::math::erfc_inv(2 * p, Policy());
   result = -result;
   result *= sd * constants::root_two<RealType>();
   result += mean;
   return result;
} // quantile

template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<normal_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   RealType sd = c.dist.standard_deviation();
   RealType mean = c.dist.mean();
   RealType x = c.param;
   static const char* function = "boost::math::cdf(const complement(normal_distribution<%1%>&), %1%)";

   RealType result = 0;
   if(false == detail::check_scale(function, sd, &result, Policy()))
      return result;
   if(false == detail::check_location(function, mean, &result, Policy()))
      return result;
   if((boost::math::isinf)(x))
   {
     if(x < 0) return 1; // cdf complement -infinity is unity.
     return 0; // cdf complement +infinity is zero
   }
   // These produce MSVC 4127 warnings, so the above used instead.
   //if(std::numeric_limits<RealType>::has_infinity && x == std::numeric_limits<RealType>::infinity())
   //{ // cdf complement +infinity is zero.
   //  return 0;
   //}
   //if(std::numeric_limits<RealType>::has_infinity && x == -std::numeric_limits<RealType>::infinity())
   //{ // cdf complement -infinity is unity.
   //  return 1;
   //}
   if(false == detail::check_x(function, x, &result, Policy()))
      return result;

   RealType diff = (x - mean) / (sd * constants::root_two<RealType>());
   result = boost::math::erfc(diff, Policy()) / 2;
   return result;
} // cdf complement

template <class RealType, class Policy>
inline RealType quantile(const complemented2_type<normal_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   RealType sd = c.dist.standard_deviation();
   RealType mean = c.dist.mean();
   static const char* function = "boost::math::quantile(const complement(normal_distribution<%1%>&), %1%)";
   RealType result = 0;
   if(false == detail::check_scale(function, sd, &result, Policy()))
      return result;
   if(false == detail::check_location(function, mean, &result, Policy()))
      return result;
   RealType q = c.param;
   if(false == detail::check_probability(function, q, &result, Policy()))
      return result;
   result = boost::math::erfc_inv(2 * q, Policy());
   result *= sd * constants::root_two<RealType>();
   result += mean;
   return result;
} // quantile

template <class RealType, class Policy>
inline RealType mean(const normal_distribution<RealType, Policy>& dist)
{
   return dist.mean();
}

template <class RealType, class Policy>
inline RealType standard_deviation(const normal_distribution<RealType, Policy>& dist)
{
   return dist.standard_deviation();
}

template <class RealType, class Policy>
inline RealType mode(const normal_distribution<RealType, Policy>& dist)
{
   return dist.mean();
}

template <class RealType, class Policy>
inline RealType median(const normal_distribution<RealType, Policy>& dist)
{
   return dist.mean();
}

template <class RealType, class Policy>
inline RealType skewness(const normal_distribution<RealType, Policy>& /*dist*/)
{
   return 0;
}

template <class RealType, class Policy>
inline RealType kurtosis(const normal_distribution<RealType, Policy>& /*dist*/)
{
   return 3;
}

template <class RealType, class Policy>
inline RealType kurtosis_excess(const normal_distribution<RealType, Policy>& /*dist*/)
{
   return 0;
}

template <class RealType, class Policy>
inline RealType entropy(const normal_distribution<RealType, Policy> & dist)
{
   using std::log;
   RealType arg = constants::two_pi<RealType>()*constants::e<RealType>()*dist.standard_deviation()*dist.standard_deviation();
   return log(arg)/2;
}

} // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_STATS_NORMAL_HPP



/* normal.hpp
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
*/