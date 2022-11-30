//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_LOGNORMAL_HPP
#define BOOST_STATS_LOGNORMAL_HPP

// http://www.itl.nist.gov/div898/handbook/eda/section3/eda3669.htm
// http://mathworld.wolfram.com/LogNormalDistribution.html
// http://en.wikipedia.org/wiki/Lognormal_distribution

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/distributions/normal.hpp>
#include <boost/math/special_functions/expm1.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>

#include <utility>

namespace boost{ namespace math
{
namespace detail
{

  template <class RealType, class Policy>
  inline bool check_lognormal_x(
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

} // namespace detail


template <class RealType = double, class Policy = policies::policy<> >
class lognormal_distribution
{
public:
   typedef RealType value_type;
   typedef Policy policy_type;

   lognormal_distribution(RealType l_location = 0, RealType l_scale = 1)
      : m_location(l_location), m_scale(l_scale)
   {
      RealType result;
      detail::check_scale("boost::math::lognormal_distribution<%1%>::lognormal_distribution", l_scale, &result, Policy());
      detail::check_location("boost::math::lognormal_distribution<%1%>::lognormal_distribution", l_location, &result, Policy());
   }

   RealType location()const
   {
      return m_location;
   }

   RealType scale()const
   {
      return m_scale;
   }
private:
   //
   // Data members:
   //
   RealType m_location;  // distribution location.
   RealType m_scale;     // distribution scale.
};

typedef lognormal_distribution<double> lognormal;

#ifdef __cpp_deduction_guides
template <class RealType>
lognormal_distribution(RealType)->lognormal_distribution<typename boost::math::tools::promote_args<RealType>::type>;
template <class RealType>
lognormal_distribution(RealType,RealType)->lognormal_distribution<typename boost::math::tools::promote_args<RealType>::type>;
#endif

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const lognormal_distribution<RealType, Policy>& /*dist*/)
{ // Range of permissible values for random variable x is >0 to +infinity.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(static_cast<RealType>(0), max_value<RealType>());
}

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const lognormal_distribution<RealType, Policy>& /*dist*/)
{ // Range of supported values for random variable x.
   // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(static_cast<RealType>(0),  max_value<RealType>());
}

template <class RealType, class Policy>
RealType pdf(const lognormal_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   RealType mu = dist.location();
   RealType sigma = dist.scale();

   static const char* function = "boost::math::pdf(const lognormal_distribution<%1%>&, %1%)";

   RealType result = 0;
   if(0 == detail::check_scale(function, sigma, &result, Policy()))
      return result;
   if(0 == detail::check_location(function, mu, &result, Policy()))
      return result;
   if(0 == detail::check_lognormal_x(function, x, &result, Policy()))
      return result;

   if(x == 0)
      return 0;

   RealType exponent = log(x) - mu;
   exponent *= -exponent;
   exponent /= 2 * sigma * sigma;

   result = exp(exponent);
   result /= sigma * sqrt(2 * constants::pi<RealType>()) * x;

   return result;
}

template <class RealType, class Policy>
inline RealType cdf(const lognormal_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::cdf(const lognormal_distribution<%1%>&, %1%)";

   RealType result = 0;
   if(0 == detail::check_scale(function, dist.scale(), &result, Policy()))
      return result;
   if(0 == detail::check_location(function, dist.location(), &result, Policy()))
      return result;
   if(0 == detail::check_lognormal_x(function, x, &result, Policy()))
      return result;

   if(x == 0)
      return 0;

   normal_distribution<RealType, Policy> norm(dist.location(), dist.scale());
   return cdf(norm, log(x));
}

template <class RealType, class Policy>
inline RealType quantile(const lognormal_distribution<RealType, Policy>& dist, const RealType& p)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::quantile(const lognormal_distribution<%1%>&, %1%)";

   RealType result = 0;
   if(0 == detail::check_scale(function, dist.scale(), &result, Policy()))
      return result;
   if(0 == detail::check_location(function, dist.location(), &result, Policy()))
      return result;
   if(0 == detail::check_probability(function, p, &result, Policy()))
      return result;

   if(p == 0)
      return 0;
   if(p == 1)
      return policies::raise_overflow_error<RealType>(function, 0, Policy());

   normal_distribution<RealType, Policy> norm(dist.location(), dist.scale());
   return exp(quantile(norm, p));
}

template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<lognormal_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::cdf(const lognormal_distribution<%1%>&, %1%)";

   RealType result = 0;
   if(0 == detail::check_scale(function, c.dist.scale(), &result, Policy()))
      return result;
   if(0 == detail::check_location(function, c.dist.location(), &result, Policy()))
      return result;
   if(0 == detail::check_lognormal_x(function, c.param, &result, Policy()))
      return result;

   if(c.param == 0)
      return 1;

   normal_distribution<RealType, Policy> norm(c.dist.location(), c.dist.scale());
   return cdf(complement(norm, log(c.param)));
}

template <class RealType, class Policy>
inline RealType quantile(const complemented2_type<lognormal_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::quantile(const lognormal_distribution<%1%>&, %1%)";

   RealType result = 0;
   if(0 == detail::check_scale(function, c.dist.scale(), &result, Policy()))
      return result;
   if(0 == detail::check_location(function, c.dist.location(), &result, Policy()))
      return result;
   if(0 == detail::check_probability(function, c.param, &result, Policy()))
      return result;

   if(c.param == 1)
      return 0;
   if(c.param == 0)
      return policies::raise_overflow_error<RealType>(function, 0, Policy());

   normal_distribution<RealType, Policy> norm(c.dist.location(), c.dist.scale());
   return exp(quantile(complement(norm, c.param)));
}

template <class RealType, class Policy>
inline RealType mean(const lognormal_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   RealType mu = dist.location();
   RealType sigma = dist.scale();

   RealType result = 0;
   if(0 == detail::check_scale("boost::math::mean(const lognormal_distribution<%1%>&)", sigma, &result, Policy()))
      return result;
   if(0 == detail::check_location("boost::math::mean(const lognormal_distribution<%1%>&)", mu, &result, Policy()))
      return result;

   return exp(mu + sigma * sigma / 2);
}

template <class RealType, class Policy>
inline RealType variance(const lognormal_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   RealType mu = dist.location();
   RealType sigma = dist.scale();

   RealType result = 0;
   if(0 == detail::check_scale("boost::math::variance(const lognormal_distribution<%1%>&)", sigma, &result, Policy()))
      return result;
   if(0 == detail::check_location("boost::math::variance(const lognormal_distribution<%1%>&)", mu, &result, Policy()))
      return result;

   return boost::math::expm1(sigma * sigma, Policy()) * exp(2 * mu + sigma * sigma);
}

template <class RealType, class Policy>
inline RealType mode(const lognormal_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   RealType mu = dist.location();
   RealType sigma = dist.scale();

   RealType result = 0;
   if(0 == detail::check_scale("boost::math::mode(const lognormal_distribution<%1%>&)", sigma, &result, Policy()))
      return result;
   if(0 == detail::check_location("boost::math::mode(const lognormal_distribution<%1%>&)", mu, &result, Policy()))
      return result;

   return exp(mu - sigma * sigma);
}

template <class RealType, class Policy>
inline RealType median(const lognormal_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions
   RealType mu = dist.location();
   return exp(mu); // e^mu
}

template <class RealType, class Policy>
inline RealType skewness(const lognormal_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   //RealType mu = dist.location();
   RealType sigma = dist.scale();

   RealType ss = sigma * sigma;
   RealType ess = exp(ss);

   RealType result = 0;
   if(0 == detail::check_scale("boost::math::skewness(const lognormal_distribution<%1%>&)", sigma, &result, Policy()))
      return result;
   if(0 == detail::check_location("boost::math::skewness(const lognormal_distribution<%1%>&)", dist.location(), &result, Policy()))
      return result;

   return (ess + 2) * sqrt(boost::math::expm1(ss, Policy()));
}

template <class RealType, class Policy>
inline RealType kurtosis(const lognormal_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   //RealType mu = dist.location();
   RealType sigma = dist.scale();
   RealType ss = sigma * sigma;

   RealType result = 0;
   if(0 == detail::check_scale("boost::math::kurtosis(const lognormal_distribution<%1%>&)", sigma, &result, Policy()))
      return result;
   if(0 == detail::check_location("boost::math::kurtosis(const lognormal_distribution<%1%>&)", dist.location(), &result, Policy()))
      return result;

   return exp(4 * ss) + 2 * exp(3 * ss) + 3 * exp(2 * ss) - 3;
}

template <class RealType, class Policy>
inline RealType kurtosis_excess(const lognormal_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   // RealType mu = dist.location();
   RealType sigma = dist.scale();
   RealType ss = sigma * sigma;

   RealType result = 0;
   if(0 == detail::check_scale("boost::math::kurtosis_excess(const lognormal_distribution<%1%>&)", sigma, &result, Policy()))
      return result;
   if(0 == detail::check_location("boost::math::kurtosis_excess(const lognormal_distribution<%1%>&)", dist.location(), &result, Policy()))
      return result;

   return exp(4 * ss) + 2 * exp(3 * ss) + 3 * exp(2 * ss) - 6;
}

template <class RealType, class Policy>
inline RealType entropy(const lognormal_distribution<RealType, Policy>& dist)
{
   using std::log;
   RealType mu = dist.location();
   RealType sigma = dist.scale();
   return mu + log(constants::two_pi<RealType>()*constants::e<RealType>()*sigma*sigma)/2;
}

} // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_STATS_STUDENTS_T_HPP



/* lognormal.hpp
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
*/