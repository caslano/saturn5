//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_WEIBULL_HPP
#define BOOST_STATS_WEIBULL_HPP

// http://www.itl.nist.gov/div898/handbook/eda/section3/eda3668.htm
// http://mathworld.wolfram.com/WeibullDistribution.html

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/special_functions/expm1.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/math/distributions/complement.hpp>

#include <utility>

namespace boost{ namespace math
{
namespace detail{

template <class RealType, class Policy>
inline bool check_weibull_shape(
      const char* function,
      RealType shape,
      RealType* result, const Policy& pol)
{
   if((shape <= 0) || !(boost::math::isfinite)(shape))
   {
      *result = policies::raise_domain_error<RealType>(
         function,
         "Shape parameter is %1%, but must be > 0 !", shape, pol);
      return false;
   }
   return true;
}

template <class RealType, class Policy>
inline bool check_weibull_x(
      const char* function,
      RealType const& x,
      RealType* result, const Policy& pol)
{
   if((x < 0) || !(boost::math::isfinite)(x))
   {
      *result = policies::raise_domain_error<RealType>(
         function,
         "Random variate is %1% but must be >= 0 !", x, pol);
      return false;
   }
   return true;
}

template <class RealType, class Policy>
inline bool check_weibull(
      const char* function,
      RealType scale,
      RealType shape,
      RealType* result, const Policy& pol)
{
   return check_scale(function, scale, result, pol) && check_weibull_shape(function, shape, result, pol);
}

} // namespace detail

template <class RealType = double, class Policy = policies::policy<> >
class weibull_distribution
{
public:
   typedef RealType value_type;
   typedef Policy policy_type;

   weibull_distribution(RealType l_shape, RealType l_scale = 1)
      : m_shape(l_shape), m_scale(l_scale)
   {
      RealType result;
      detail::check_weibull("boost::math::weibull_distribution<%1%>::weibull_distribution", l_scale, l_shape, &result, Policy());
   }

   RealType shape()const
   {
      return m_shape;
   }

   RealType scale()const
   {
      return m_scale;
   }
private:
   //
   // Data members:
   //
   RealType m_shape;     // distribution shape
   RealType m_scale;     // distribution scale
};

typedef weibull_distribution<double> weibull;

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const weibull_distribution<RealType, Policy>& /*dist*/)
{ // Range of permissible values for random variable x.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(static_cast<RealType>(0), max_value<RealType>());
}

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const weibull_distribution<RealType, Policy>& /*dist*/)
{ // Range of supported values for random variable x.
   // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
   using boost::math::tools::max_value;
   using boost::math::tools::min_value;
   return std::pair<RealType, RealType>(min_value<RealType>(),  max_value<RealType>());
   // A discontinuity at x == 0, so only support down to min_value.
}

template <class RealType, class Policy>
inline RealType pdf(const weibull_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::pdf(const weibull_distribution<%1%>, %1%)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
      return result;
   if(false == detail::check_weibull_x(function, x, &result, Policy()))
      return result;

   if(x == 0)
   {
      if(shape == 1)
      {
         return 1 / scale;
      }
      if(shape > 1)
      {
         return 0;
      }
      return policies::raise_overflow_error<RealType>(function, 0, Policy());
   }
   result = exp(-pow(x / scale, shape));
   result *= pow(x / scale, shape - 1) * shape / scale;

   return result;
}

template <class RealType, class Policy>
inline RealType cdf(const weibull_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::cdf(const weibull_distribution<%1%>, %1%)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
      return result;
   if(false == detail::check_weibull_x(function, x, &result, Policy()))
      return result;

   result = -boost::math::expm1(-pow(x / scale, shape), Policy());

   return result;
}

template <class RealType, class Policy>
inline RealType quantile(const weibull_distribution<RealType, Policy>& dist, const RealType& p)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::quantile(const weibull_distribution<%1%>, %1%)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
      return result;
   if(false == detail::check_probability(function, p, &result, Policy()))
      return result;

   if(p == 1)
      return policies::raise_overflow_error<RealType>(function, 0, Policy());

   result = scale * pow(-boost::math::log1p(-p, Policy()), 1 / shape);

   return result;
}

template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<weibull_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::cdf(const weibull_distribution<%1%>, %1%)";

   RealType shape = c.dist.shape();
   RealType scale = c.dist.scale();

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
      return result;
   if(false == detail::check_weibull_x(function, c.param, &result, Policy()))
      return result;

   result = exp(-pow(c.param / scale, shape));

   return result;
}

template <class RealType, class Policy>
inline RealType quantile(const complemented2_type<weibull_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::quantile(const weibull_distribution<%1%>, %1%)";

   RealType shape = c.dist.shape();
   RealType scale = c.dist.scale();
   RealType q = c.param;

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
      return result;
   if(false == detail::check_probability(function, q, &result, Policy()))
      return result;

   if(q == 0)
      return policies::raise_overflow_error<RealType>(function, 0, Policy());

   result = scale * pow(-log(q), 1 / shape);

   return result;
}

template <class RealType, class Policy>
inline RealType mean(const weibull_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::mean(const weibull_distribution<%1%>)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
      return result;

   result = scale * boost::math::tgamma(1 + 1 / shape, Policy());
   return result;
}

template <class RealType, class Policy>
inline RealType variance(const weibull_distribution<RealType, Policy>& dist)
{
   RealType shape = dist.shape();
   RealType scale = dist.scale();

   static const char* function = "boost::math::variance(const weibull_distribution<%1%>)";

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
   {
      return result;
   }
   result = boost::math::tgamma(1 + 1 / shape, Policy());
   result *= -result;
   result += boost::math::tgamma(1 + 2 / shape, Policy());
   result *= scale * scale;
   return result;
}

template <class RealType, class Policy>
inline RealType mode(const weibull_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std function pow.

   static const char* function = "boost::math::mode(const weibull_distribution<%1%>)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
   {
      return result;
   }
   if(shape <= 1)
      return 0;
   result = scale * pow((shape - 1) / shape, 1 / shape);
   return result;
}

template <class RealType, class Policy>
inline RealType median(const weibull_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std function pow.

   static const char* function = "boost::math::median(const weibull_distribution<%1%>)";

   RealType shape = dist.shape(); // Wikipedia k
   RealType scale = dist.scale(); // Wikipedia lambda

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
   {
      return result;
   }
   using boost::math::constants::ln_two;
   result = scale * pow(ln_two<RealType>(), 1 / shape);
   return result;
}

template <class RealType, class Policy>
inline RealType skewness(const weibull_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::skewness(const weibull_distribution<%1%>)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
   {
      return result;
   }
   RealType g1, g2, g3, d;

   g1 = boost::math::tgamma(1 + 1 / shape, Policy());
   g2 = boost::math::tgamma(1 + 2 / shape, Policy());
   g3 = boost::math::tgamma(1 + 3 / shape, Policy());
   d = pow(g2 - g1 * g1, RealType(1.5));

   result = (2 * g1 * g1 * g1 - 3 * g1 * g2 + g3) / d;
   return result;
}

template <class RealType, class Policy>
inline RealType kurtosis_excess(const weibull_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::kurtosis_excess(const weibull_distribution<%1%>)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_weibull(function, scale, shape, &result, Policy()))
      return result;

   RealType g1, g2, g3, g4, d, g1_2, g1_4;

   g1 = boost::math::tgamma(1 + 1 / shape, Policy());
   g2 = boost::math::tgamma(1 + 2 / shape, Policy());
   g3 = boost::math::tgamma(1 + 3 / shape, Policy());
   g4 = boost::math::tgamma(1 + 4 / shape, Policy());
   g1_2 = g1 * g1;
   g1_4 = g1_2 * g1_2;
   d = g2 - g1_2;
   d *= d;

   result = -6 * g1_4 + 12 * g1_2 * g2 - 3 * g2 * g2 - 4 * g1 * g3 + g4;
   result /= d;
   return result;
}

template <class RealType, class Policy>
inline RealType kurtosis(const weibull_distribution<RealType, Policy>& dist)
{
   return kurtosis_excess(dist) + 3;
}

template <class RealType, class Policy>
inline RealType entropy(const weibull_distribution<RealType, Policy>& dist)
{
   using std::log;
   RealType k = dist.shape();
   RealType lambda = dist.scale();
   return constants::euler<RealType>()*(1-1/k) + log(lambda/k) + 1;
}

} // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_STATS_WEIBULL_HPP



/* weibull.hpp
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
*/