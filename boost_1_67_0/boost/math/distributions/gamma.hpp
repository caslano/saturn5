//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_GAMMA_HPP
#define BOOST_STATS_GAMMA_HPP

// http://www.itl.nist.gov/div898/handbook/eda/section3/eda366b.htm
// http://mathworld.wolfram.com/GammaDistribution.html
// http://en.wikipedia.org/wiki/Gamma_distribution

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/special_functions/digamma.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/math/distributions/complement.hpp>

#include <utility>

namespace boost{ namespace math
{
namespace detail
{

template <class RealType, class Policy>
inline bool check_gamma_shape(
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
inline bool check_gamma_x(
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
inline bool check_gamma(
      const char* function,
      RealType scale,
      RealType shape,
      RealType* result, const Policy& pol)
{
   return check_scale(function, scale, result, pol) && check_gamma_shape(function, shape, result, pol);
}

} // namespace detail

template <class RealType = double, class Policy = policies::policy<> >
class gamma_distribution
{
public:
   typedef RealType value_type;
   typedef Policy policy_type;

   gamma_distribution(RealType l_shape, RealType l_scale = 1)
      : m_shape(l_shape), m_scale(l_scale)
   {
      RealType result;
      detail::check_gamma("boost::math::gamma_distribution<%1%>::gamma_distribution", l_scale, l_shape, &result, Policy());
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

// NO typedef because of clash with name of gamma function.

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const gamma_distribution<RealType, Policy>& /* dist */)
{ // Range of permissible values for random variable x.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(static_cast<RealType>(0), max_value<RealType>());
}

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const gamma_distribution<RealType, Policy>& /* dist */)
{ // Range of supported values for random variable x.
   // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
   using boost::math::tools::max_value;
   using boost::math::tools::min_value;
   return std::pair<RealType, RealType>(min_value<RealType>(),  max_value<RealType>());
}

template <class RealType, class Policy>
inline RealType pdf(const gamma_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::pdf(const gamma_distribution<%1%>&, %1%)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_gamma(function, scale, shape, &result, Policy()))
      return result;
   if(false == detail::check_gamma_x(function, x, &result, Policy()))
      return result;

   if(x == 0)
   {
      return 0;
   }
   result = gamma_p_derivative(shape, x / scale, Policy()) / scale;
   return result;
} // pdf

template <class RealType, class Policy>
inline RealType cdf(const gamma_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::cdf(const gamma_distribution<%1%>&, %1%)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_gamma(function, scale, shape, &result, Policy()))
      return result;
   if(false == detail::check_gamma_x(function, x, &result, Policy()))
      return result;

   result = boost::math::gamma_p(shape, x / scale, Policy());
   return result;
} // cdf

template <class RealType, class Policy>
inline RealType quantile(const gamma_distribution<RealType, Policy>& dist, const RealType& p)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::quantile(const gamma_distribution<%1%>&, %1%)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_gamma(function, scale, shape, &result, Policy()))
      return result;
   if(false == detail::check_probability(function, p, &result, Policy()))
      return result;

   if(p == 1)
      return policies::raise_overflow_error<RealType>(function, 0, Policy());

   result = gamma_p_inv(shape, p, Policy()) * scale;

   return result;
}

template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<gamma_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::quantile(const gamma_distribution<%1%>&, %1%)";

   RealType shape = c.dist.shape();
   RealType scale = c.dist.scale();

   RealType result = 0;
   if(false == detail::check_gamma(function, scale, shape, &result, Policy()))
      return result;
   if(false == detail::check_gamma_x(function, c.param, &result, Policy()))
      return result;

   result = gamma_q(shape, c.param / scale, Policy());

   return result;
}

template <class RealType, class Policy>
inline RealType quantile(const complemented2_type<gamma_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::quantile(const gamma_distribution<%1%>&, %1%)";

   RealType shape = c.dist.shape();
   RealType scale = c.dist.scale();
   RealType q = c.param;

   RealType result = 0;
   if(false == detail::check_gamma(function, scale, shape, &result, Policy()))
      return result;
   if(false == detail::check_probability(function, q, &result, Policy()))
      return result;

   if(q == 0)
      return policies::raise_overflow_error<RealType>(function, 0, Policy());

   result = gamma_q_inv(shape, q, Policy()) * scale;

   return result;
}

template <class RealType, class Policy>
inline RealType mean(const gamma_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::mean(const gamma_distribution<%1%>&)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_gamma(function, scale, shape, &result, Policy()))
      return result;

   result = shape * scale;
   return result;
}

template <class RealType, class Policy>
inline RealType variance(const gamma_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::variance(const gamma_distribution<%1%>&)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_gamma(function, scale, shape, &result, Policy()))
      return result;

   result = shape * scale * scale;
   return result;
}

template <class RealType, class Policy>
inline RealType mode(const gamma_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::mode(const gamma_distribution<%1%>&)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_gamma(function, scale, shape, &result, Policy()))
      return result;

   if(shape < 1)
      return policies::raise_domain_error<RealType>(
         function,
         "The mode of the gamma distribution is only defined for values of the shape parameter >= 1, but got %1%.",
         shape, Policy());

   result = (shape - 1) * scale;
   return result;
}

//template <class RealType, class Policy>
//inline RealType median(const gamma_distribution<RealType, Policy>& dist)
//{  // Rely on default definition in derived accessors.
//}

template <class RealType, class Policy>
inline RealType skewness(const gamma_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::skewness(const gamma_distribution<%1%>&)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_gamma(function, scale, shape, &result, Policy()))
      return result;

   result = 2 / sqrt(shape);
   return result;
}

template <class RealType, class Policy>
inline RealType kurtosis_excess(const gamma_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::kurtosis_excess(const gamma_distribution<%1%>&)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_gamma(function, scale, shape, &result, Policy()))
      return result;

   result = 6 / shape;
   return result;
}

template <class RealType, class Policy>
inline RealType kurtosis(const gamma_distribution<RealType, Policy>& dist)
{
   return kurtosis_excess(dist) + 3;
}

template <class RealType, class Policy>
inline RealType entropy(const gamma_distribution<RealType, Policy>& dist)
{
   RealType k = dist.shape();
   RealType theta = dist.scale();
   using std::log;
   return k + log(theta) + lgamma(k) + (1-k)*digamma(k);
}

} // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_STATS_GAMMA_HPP



/* gamma.hpp
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
*/