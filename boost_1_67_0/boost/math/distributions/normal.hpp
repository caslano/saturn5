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

#ifdef BOOST_MSVC
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

#ifdef BOOST_MSVC
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