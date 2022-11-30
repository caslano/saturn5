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

#ifdef __cpp_deduction_guides
template <class RealType>
gamma_distribution(RealType)->gamma_distribution<typename boost::math::tools::promote_args<RealType>::type>;
template <class RealType>
gamma_distribution(RealType,RealType)->gamma_distribution<typename boost::math::tools::promote_args<RealType>::type>;
#endif

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