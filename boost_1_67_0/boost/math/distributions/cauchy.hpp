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
#include <boost/config/no_tr1/cmath.hpp>

#include <utility>

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
   BOOST_STATIC_ASSERT(assert_type::value == 0);

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
   BOOST_STATIC_ASSERT(assert_type::value == 0);

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
   BOOST_STATIC_ASSERT(assert_type::value == 0);

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
   BOOST_STATIC_ASSERT(assert_type::value == 0);

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
   BOOST_STATIC_ASSERT(assert_type::value == 0);

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