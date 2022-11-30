// Copyright John Maddock 2006, 2007.
// Copyright Paul A. Bristow 2007.

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_CAUCHY_HPP
#define BOOST_STATS_CAUCHY_HPP

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4127) // conditional expression is constant
#endif

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/distributions/complement.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <utility>
#include <cmath>

namespace boost{ namespace math
{

template <class RealType, class Policy>
class cauchy_distribution;

namespace detail
{

template <class RealType, class Policy>
RealType cdf_imp(const cauchy_distribution<RealType, Policy>& dist, const RealType& x, bool complement)
{
   //
   // This calculates the cdf of the Cauchy distribution and/or its complement.
   //
   // The usual formula for the Cauchy cdf is:
   //
   // cdf = 0.5 + atan(x)/pi
   //
   // But that suffers from cancellation error as x -> -INF.
   //
   // Recall that for x < 0:
   //
   // atan(x) = -pi/2 - atan(1/x)
   //
   // Substituting into the above we get:
   //
   // CDF = -atan(1/x)  ; x < 0
   //
   // So the procedure is to calculate the cdf for -fabs(x)
   // using the above formula, and then subtract from 1 when required
   // to get the result.
   //
   BOOST_MATH_STD_USING // for ADL of std functions
   static const char* function = "boost::math::cdf(cauchy<%1%>&, %1%)";
   RealType result = 0;
   RealType location = dist.location();
   RealType scale = dist.scale();
   if(false == detail::check_location(function, location, &result, Policy()))
   {
     return result;
   }
   if(false == detail::check_scale(function, scale, &result, Policy()))
   {
      return result;
   }
   if(std::numeric_limits<RealType>::has_infinity && x == std::numeric_limits<RealType>::infinity())
   { // cdf +infinity is unity.
     return static_cast<RealType>((complement) ? 0 : 1);
   }
   if(std::numeric_limits<RealType>::has_infinity && x == -std::numeric_limits<RealType>::infinity())
   { // cdf -infinity is zero.
     return static_cast<RealType>((complement) ? 1 : 0);
   }
   if(false == detail::check_x(function, x, &result, Policy()))
   { // Catches x == NaN
      return result;
   }
   RealType mx = -fabs((x - location) / scale); // scale is > 0
   if(mx > -tools::epsilon<RealType>() / 8)
   {  // special case first: x extremely close to location.
      return 0.5;
   }
   result = -atan(1 / mx) / constants::pi<RealType>();
   return (((x > location) != complement) ? 1 - result : result);
} // cdf

template <class RealType, class Policy>
RealType quantile_imp(
      const cauchy_distribution<RealType, Policy>& dist,
      const RealType& p,
      bool complement)
{
   // This routine implements the quantile for the Cauchy distribution,
   // the value p may be the probability, or its complement if complement=true.
   //
   // The procedure first performs argument reduction on p to avoid error
   // when calculating the tangent, then calculates the distance from the
   // mid-point of the distribution.  This is either added or subtracted
   // from the location parameter depending on whether `complement` is true.
   //
   static const char* function = "boost::math::quantile(cauchy<%1%>&, %1%)";
   BOOST_MATH_STD_USING // for ADL of std functions

   RealType result = 0;
   RealType location = dist.location();
   RealType scale = dist.scale();
   if(false == detail::check_location(function, location, &result, Policy()))
   {
     return result;
   }
   if(false == detail::check_scale(function, scale, &result, Policy()))
   {
      return result;
   }
   if(false == detail::check_probability(function, p, &result, Policy()))
   {
      return result;
   }
   // Special cases:
   if(p == 1)
   {
      return (complement ? -1 : 1) * policies::raise_overflow_error<RealType>(function, 0, Policy());
   }
   if(p == 0)
   {
      return (complement ? 1 : -1) * policies::raise_overflow_error<RealType>(function, 0, Policy());
   }

   RealType P = p - floor(p);   // argument reduction of p:
   if(P > 0.5)
   {
      P = P - 1;
   }
   if(P == 0.5)   // special case:
   {
      return location;
   }
   result = -scale / tan(constants::pi<RealType>() * P);
   return complement ? RealType(location - result) : RealType(location + result);
} // quantile

} // namespace detail

template <class RealType = double, class Policy = policies::policy<> >
class cauchy_distribution
{
public:
   typedef RealType value_type;
   typedef Policy policy_type;

   cauchy_distribution(RealType l_location = 0, RealType l_scale = 1)
      : m_a(l_location), m_hg(l_scale)
   {
    static const char* function = "boost::math::cauchy_distribution<%1%>::cauchy_distribution";
     RealType result;
     detail::check_location(function, l_location, &result, Policy());
     detail::check_scale(function, l_scale, &result, Policy());
   } // cauchy_distribution

   RealType location()const
   {
      return m_a;
   }
   RealType scale()const
   {
      return m_hg;
   }

private:
   RealType m_a;    // The location, this is the median of the distribution.
   RealType m_hg;   // The scale )or shape), this is the half width at half height.
};

typedef cauchy_distribution<double> cauchy;

#ifdef __cpp_deduction_guides
template <class RealType>
cauchy_distribution(RealType)->cauchy_distribution<typename boost::math::tools::promote_args<RealType>::type>;
template <class RealType>
cauchy_distribution(RealType,RealType)->cauchy_distribution<typename boost::math::tools::promote_args<RealType>::type>;
#endif

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const cauchy_distribution<RealType, Policy>&)
{ // Range of permissible values for random variable x.
  if (std::numeric_limits<RealType>::has_infinity)
  { 
     return std::pair<RealType, RealType>(-std::numeric_limits<RealType>::infinity(), std::numeric_limits<RealType>::infinity()); // - to + infinity.
  }
  else
  { // Can only use max_value.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(-max_value<RealType>(), max_value<RealType>()); // - to + max.
  }
}

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const cauchy_distribution<RealType, Policy>& )
{ // Range of supported values for random variable x.
   // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
  if (std::numeric_limits<RealType>::has_infinity)
  { 
     return std::pair<RealType, RealType>(-std::numeric_limits<RealType>::infinity(), std::numeric_limits<RealType>::infinity()); // - to + infinity.
  }
  else
  { // Can only use max_value.
     using boost::math::tools::max_value;
     return std::pair<RealType, RealType>(-tools::max_value<RealType>(), max_value<RealType>()); // - to + max.
  }
}

template <class RealType, class Policy>
inline RealType pdf(const cauchy_distribution<RealType, Policy>& dist, const RealType& x)
{  
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::pdf(cauchy<%1%>&, %1%)";
   RealType result = 0;
   RealType location = dist.location();
   RealType scale = dist.scale();
   if(false == detail::check_scale("boost::math::pdf(cauchy<%1%>&, %1%)", scale, &result, Policy()))
   {
      return result;
   }
   if(false == detail::check_location("boost::math::pdf(cauchy<%1%>&, %1%)", location, &result, Policy()))
   {
      return result;
   }
   if((boost::math::isinf)(x))
   {
     return 0; // pdf + and - infinity is zero.
   }
   // These produce MSVC 4127 warnings, so the above used instead.
   //if(std::numeric_limits<RealType>::has_infinity && abs(x) == std::numeric_limits<RealType>::infinity())
   //{ // pdf + and - infinity is zero.
   //  return 0;
   //}

   if(false == detail::check_x(function, x, &result, Policy()))
   { // Catches x = NaN
      return result;
   }

   RealType xs = (x - location) / scale;
   result = 1 / (constants::pi<RealType>() * scale * (1 + xs * xs));
   return result;
} // pdf

template <class RealType, class Policy>
inline RealType cdf(const cauchy_distribution<RealType, Policy>& dist, const RealType& x)
{
   return detail::cdf_imp(dist, x, false);
} // cdf

template <class RealType, class Policy>
inline RealType quantile(const cauchy_distribution<RealType, Policy>& dist, const RealType& p)
{
   return detail::quantile_imp(dist, p, false);
} // quantile

template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<cauchy_distribution<RealType, Policy>, RealType>& c)
{
   return detail::cdf_imp(c.dist, c.param, true);
} //  cdf complement

template <class RealType, class Policy>
inline RealType quantile(const complemented2_type<cauchy_distribution<RealType, Policy>, RealType>& c)
{
   return detail::quantile_imp(c.dist, c.param, true);
} // quantile complement

template <class RealType, class Policy>
inline RealType mean(const cauchy_distribution<RealType, Policy>&)
{  // There is no mean:
   typedef typename Policy::assert_undefined_type assert_type;
   static_assert(assert_type::value == 0, "assert type is undefined");

   return policies::raise_domain_error<RealType>(
      "boost::math::mean(cauchy<%1%>&)",
      "The Cauchy distribution does not have a mean: "
      "the only possible return value is %1%.",
      std::numeric_limits<RealType>::quiet_NaN(), Policy());
}

template <class RealType, class Policy>
inline RealType variance(const cauchy_distribution<RealType, Policy>& /*dist*/)
{
   // There is no variance:
   typedef typename Policy::assert_undefined_type assert_type;
   static_assert(assert_type::value == 0, "assert type is undefined");

   return policies::raise_domain_error<RealType>(
      "boost::math::variance(cauchy<%1%>&)",
      "The Cauchy distribution does not have a variance: "
      "the only possible return value is %1%.",
      std::numeric_limits<RealType>::quiet_NaN(), Policy());
}

template <class RealType, class Policy>
inline RealType mode(const cauchy_distribution<RealType, Policy>& dist)
{
   return dist.location();
}

template <class RealType, class Policy>
inline RealType median(const cauchy_distribution<RealType, Policy>& dist)
{
   return dist.location();
}
template <class RealType, class Policy>
inline RealType skewness(const cauchy_distribution<RealType, Policy>& /*dist*/)
{
   // There is no skewness:
   typedef typename Policy::assert_undefined_type assert_type;
   static_assert(assert_type::value == 0, "assert type is undefined");

   return policies::raise_domain_error<RealType>(
      "boost::math::skewness(cauchy<%1%>&)",
      "The Cauchy distribution does not have a skewness: "
      "the only possible return value is %1%.",
      std::numeric_limits<RealType>::quiet_NaN(), Policy()); // infinity?
}

template <class RealType, class Policy>
inline RealType kurtosis(const cauchy_distribution<RealType, Policy>& /*dist*/)
{
   // There is no kurtosis:
   typedef typename Policy::assert_undefined_type assert_type;
   static_assert(assert_type::value == 0, "assert type is undefined");

   return policies::raise_domain_error<RealType>(
      "boost::math::kurtosis(cauchy<%1%>&)",
      "The Cauchy distribution does not have a kurtosis: "
      "the only possible return value is %1%.",
      std::numeric_limits<RealType>::quiet_NaN(), Policy());
}

template <class RealType, class Policy>
inline RealType kurtosis_excess(const cauchy_distribution<RealType, Policy>& /*dist*/)
{
   // There is no kurtosis excess:
   typedef typename Policy::assert_undefined_type assert_type;
   static_assert(assert_type::value == 0, "assert type is undefined");

   return policies::raise_domain_error<RealType>(
      "boost::math::kurtosis_excess(cauchy<%1%>&)",
      "The Cauchy distribution does not have a kurtosis: "
      "the only possible return value is %1%.",
      std::numeric_limits<RealType>::quiet_NaN(), Policy());
}

template <class RealType, class Policy>
inline RealType entropy(const cauchy_distribution<RealType, Policy> & dist)
{
   using std::log;
   return log(2*constants::two_pi<RealType>()*dist.scale());
}

} // namespace math
} // namespace boost

#ifdef _MSC_VER
#pragma warning(pop)
#endif

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_STATS_CAUCHY_HPP

/* cauchy.hpp
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
*/