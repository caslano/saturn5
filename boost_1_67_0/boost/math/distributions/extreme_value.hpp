//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_EXTREME_VALUE_HPP
#define BOOST_STATS_EXTREME_VALUE_HPP

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/special_functions/expm1.hpp>
#include <boost/math/distributions/complement.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/config/no_tr1/cmath.hpp>

//
// This is the maximum extreme value distribution, see
// http://www.itl.nist.gov/div898/handbook/eda/section3/eda366g.htm
// and http://mathworld.wolfram.com/ExtremeValueDistribution.html
// Also known as a Fisher-Tippett distribution, a log-Weibull
// distribution or a Gumbel distribution.

#include <utility>

#ifdef BOOST_MSVC
# pragma warning(push)
# pragma warning(disable: 4702) // unreachable code (return after domain_error throw).
#endif

namespace boost{ namespace math{

namespace detail{
//
// Error check:
//
template <class RealType, class Policy>
inline bool verify_scale_b(const char* function, RealType b, RealType* presult, const Policy& pol)
{
   if((b <= 0) || !(boost::math::isfinite)(b))
   {
      *presult = policies::raise_domain_error<RealType>(
         function,
         "The scale parameter \"b\" must be finite and > 0, but was: %1%.", b, pol);
      return false;
   }
   return true;
}

} // namespace detail

template <class RealType = double, class Policy = policies::policy<> >
class extreme_value_distribution
{
public:
   typedef RealType value_type;
   typedef Policy policy_type;

   extreme_value_distribution(RealType a = 0, RealType b = 1)
      : m_a(a), m_b(b)
   {
      RealType err;
      detail::verify_scale_b("boost::math::extreme_value_distribution<%1%>::extreme_value_distribution", b, &err, Policy());
      detail::check_finite("boost::math::extreme_value_distribution<%1%>::extreme_value_distribution", a, &err, Policy());
   } // extreme_value_distribution

   RealType location()const { return m_a; }
   RealType scale()const { return m_b; }

private:
   RealType m_a, m_b;
};

typedef extreme_value_distribution<double> extreme_value;

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const extreme_value_distribution<RealType, Policy>& /*dist*/)
{ // Range of permissible values for random variable x.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(
      std::numeric_limits<RealType>::has_infinity ? -std::numeric_limits<RealType>::infinity() : -max_value<RealType>(), 
      std::numeric_limits<RealType>::has_infinity ? std::numeric_limits<RealType>::infinity() : max_value<RealType>());
}

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const extreme_value_distribution<RealType, Policy>& /*dist*/)
{ // Range of supported values for random variable x.
   // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(-max_value<RealType>(),  max_value<RealType>());
}

template <class RealType, class Policy>
inline RealType pdf(const extreme_value_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   static const char* function = "boost::math::pdf(const extreme_value_distribution<%1%>&, %1%)";

   RealType a = dist.location();
   RealType b = dist.scale();
   RealType result = 0;
   if(0 == detail::verify_scale_b(function, b, &result, Policy()))
      return result;
   if(0 == detail::check_finite(function, a, &result, Policy()))
      return result;
   if((boost::math::isinf)(x))
      return 0.0f;
   if(0 == detail::check_x(function, x, &result, Policy()))
      return result;
   RealType e = (a - x) / b;
   if(e < tools::log_max_value<RealType>())
      result = exp(e) * exp(-exp(e)) / b;
   // else.... result *must* be zero since exp(e) is infinite...
   return result;
} // pdf

template <class RealType, class Policy>
inline RealType cdf(const extreme_value_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   static const char* function = "boost::math::cdf(const extreme_value_distribution<%1%>&, %1%)";

   if((boost::math::isinf)(x))
      return x < 0 ? 0.0f : 1.0f;
   RealType a = dist.location();
   RealType b = dist.scale();
   RealType result = 0;
   if(0 == detail::verify_scale_b(function, b, &result, Policy()))
      return result;
   if(0 == detail::check_finite(function, a, &result, Policy()))
      return result;
   if(0 == detail::check_finite(function, a, &result, Policy()))
      return result;
   if(0 == detail::check_x("boost::math::cdf(const extreme_value_distribution<%1%>&, %1%)", x, &result, Policy()))
      return result;

   result = exp(-exp((a-x)/b));

   return result;
} // cdf

template <class RealType, class Policy>
RealType quantile(const extreme_value_distribution<RealType, Policy>& dist, const RealType& p)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   static const char* function = "boost::math::quantile(const extreme_value_distribution<%1%>&, %1%)";

   RealType a = dist.location();
   RealType b = dist.scale();
   RealType result = 0;
   if(0 == detail::verify_scale_b(function, b, &result, Policy()))
      return result;
   if(0 == detail::check_finite(function, a, &result, Policy()))
      return result;
   if(0 == detail::check_probability(function, p, &result, Policy()))
      return result;

   if(p == 0)
      return -policies::raise_overflow_error<RealType>(function, 0, Policy());
   if(p == 1)
      return policies::raise_overflow_error<RealType>(function, 0, Policy());

   result = a - log(-log(p)) * b;

   return result;
} // quantile

template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<extreme_value_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   static const char* function = "boost::math::cdf(const extreme_value_distribution<%1%>&, %1%)";

   if((boost::math::isinf)(c.param))
      return c.param < 0 ? 1.0f : 0.0f;
   RealType a = c.dist.location();
   RealType b = c.dist.scale();
   RealType result = 0;
   if(0 == detail::verify_scale_b(function, b, &result, Policy()))
      return result;
   if(0 == detail::check_finite(function, a, &result, Policy()))
      return result;
   if(0 == detail::check_x(function, c.param, &result, Policy()))
      return result;

   result = -boost::math::expm1(-exp((a-c.param)/b), Policy());

   return result;
}

template <class RealType, class Policy>
RealType quantile(const complemented2_type<extreme_value_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING // for ADL of std functions

   static const char* function = "boost::math::quantile(const extreme_value_distribution<%1%>&, %1%)";

   RealType a = c.dist.location();
   RealType b = c.dist.scale();
   RealType q = c.param;
   RealType result = 0;
   if(0 == detail::verify_scale_b(function, b, &result, Policy()))
      return result;
   if(0 == detail::check_finite(function, a, &result, Policy()))
      return result;
   if(0 == detail::check_probability(function, q, &result, Policy()))
      return result;

   if(q == 0)
      return policies::raise_overflow_error<RealType>(function, 0, Policy());
   if(q == 1)
      return -policies::raise_overflow_error<RealType>(function, 0, Policy());

   result = a - log(-boost::math::log1p(-q, Policy())) * b;

   return result;
}

template <class RealType, class Policy>
inline RealType mean(const extreme_value_distribution<RealType, Policy>& dist)
{
   RealType a = dist.location();
   RealType b = dist.scale();
   RealType result = 0;
   if(0 == detail::verify_scale_b("boost::math::mean(const extreme_value_distribution<%1%>&)", b, &result, Policy()))
      return result;
   if (0 == detail::check_finite("boost::math::mean(const extreme_value_distribution<%1%>&)", a, &result, Policy()))
      return result;
   return a + constants::euler<RealType>() * b;
}

template <class RealType, class Policy>
inline RealType standard_deviation(const extreme_value_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING // for ADL of std functions.

   RealType b = dist.scale();
   RealType result = 0;
   if(0 == detail::verify_scale_b("boost::math::standard_deviation(const extreme_value_distribution<%1%>&)", b, &result, Policy()))
      return result;
   if(0 == detail::check_finite("boost::math::standard_deviation(const extreme_value_distribution<%1%>&)", dist.location(), &result, Policy()))
      return result;
   return constants::pi<RealType>() * b / sqrt(static_cast<RealType>(6));
}

template <class RealType, class Policy>
inline RealType mode(const extreme_value_distribution<RealType, Policy>& dist)
{
   return dist.location();
}

template <class RealType, class Policy>
inline RealType median(const extreme_value_distribution<RealType, Policy>& dist)
{
  using constants::ln_ln_two;
   return dist.location() - dist.scale() * ln_ln_two<RealType>();
}

template <class RealType, class Policy>
inline RealType skewness(const extreme_value_distribution<RealType, Policy>& /*dist*/)
{
   //
   // This is 12 * sqrt(6) * zeta(3) / pi^3:
   // See http://mathworld.wolfram.com/ExtremeValueDistribution.html
   //
   return static_cast<RealType>(1.1395470994046486574927930193898461120875997958366L);
}

template <class RealType, class Policy>
inline RealType kurtosis(const extreme_value_distribution<RealType, Policy>& /*dist*/)
{
   // See http://mathworld.wolfram.com/ExtremeValueDistribution.html
   return RealType(27) / 5;
}

template <class RealType, class Policy>
inline RealType kurtosis_excess(const extreme_value_distribution<RealType, Policy>& /*dist*/)
{
   // See http://mathworld.wolfram.com/ExtremeValueDistribution.html
   return RealType(12) / 5;
}


} // namespace math
} // namespace boost

#ifdef BOOST_MSVC
# pragma warning(pop)
#endif

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_STATS_EXTREME_VALUE_HPP

/* extreme_value.hpp
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
*/