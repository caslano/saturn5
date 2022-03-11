// inverse_gamma.hpp

//  Copyright Paul A. Bristow 2010.
//  Copyright John Maddock 2010.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_INVERSE_GAMMA_HPP
#define BOOST_STATS_INVERSE_GAMMA_HPP

// Inverse Gamma Distribution is a two-parameter family
// of continuous probability distributions
// on the positive real line, which is the distribution of
// the reciprocal of a variable distributed according to the gamma distribution.

// http://en.wikipedia.org/wiki/Inverse-gamma_distribution
// http://rss.acs.unt.edu/Rdoc/library/pscl/html/igamma.html

// See also gamma distribution at gamma.hpp:
// http://www.itl.nist.gov/div898/handbook/eda/section3/eda366b.htm
// http://mathworld.wolfram.com/GammaDistribution.html
// http://en.wikipedia.org/wiki/Gamma_distribution

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/gamma.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/math/distributions/complement.hpp>

#include <utility>

namespace boost{ namespace math
{
namespace detail
{

template <class RealType, class Policy>
inline bool check_inverse_gamma_shape(
      const char* function, // inverse_gamma
      RealType shape, // shape aka alpha
      RealType* result, // to update, perhaps with NaN
      const Policy& pol)
{  // Sources say shape argument must be > 0
   // but seems logical to allow shape zero as special case,
   // returning pdf and cdf zero (but not < 0).
   // (Functions like mean, variance with other limits on shape are checked
   // in version including an operator & limit below).
   if((shape < 0) || !(boost::math::isfinite)(shape))
   {
      *result = policies::raise_domain_error<RealType>(
         function,
         "Shape parameter is %1%, but must be >= 0 !", shape, pol);
      return false;
   }
   return true;
} //bool check_inverse_gamma_shape

template <class RealType, class Policy>
inline bool check_inverse_gamma_x(
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
inline bool check_inverse_gamma(
      const char* function, // TODO swap these over, so shape is first.
      RealType scale,  // scale aka beta
      RealType shape, // shape aka alpha
      RealType* result, const Policy& pol)
{
   return check_scale(function, scale, result, pol)
     && check_inverse_gamma_shape(function, shape, result, pol);
} // bool check_inverse_gamma

} // namespace detail

template <class RealType = double, class Policy = policies::policy<> >
class inverse_gamma_distribution
{
public:
   typedef RealType value_type;
   typedef Policy policy_type;

   inverse_gamma_distribution(RealType l_shape = 1, RealType l_scale = 1)
      : m_shape(l_shape), m_scale(l_scale)
   {
      RealType result;
      detail::check_inverse_gamma(
        "boost::math::inverse_gamma_distribution<%1%>::inverse_gamma_distribution",
        l_scale, l_shape, &result, Policy());
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

typedef inverse_gamma_distribution<double> inverse_gamma;
// typedef - but potential clash with name of inverse gamma *function*.
// but there is a typedef for gamma
//   typedef boost::math::gamma_distribution<Type, Policy> gamma;

// Allow random variable x to be zero, treated as a special case (unlike some definitions).

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const inverse_gamma_distribution<RealType, Policy>& /* dist */)
{  // Range of permissible values for random variable x.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(static_cast<RealType>(0), max_value<RealType>());
}

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const inverse_gamma_distribution<RealType, Policy>& /* dist */)
{  // Range of supported values for random variable x.
   // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
   using boost::math::tools::max_value;
   using boost::math::tools::min_value;
   return std::pair<RealType, RealType>(static_cast<RealType>(0),  max_value<RealType>());
}

template <class RealType, class Policy>
inline RealType pdf(const inverse_gamma_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::pdf(const inverse_gamma_distribution<%1%>&, %1%)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_inverse_gamma(function, scale, shape, &result, Policy()))
   { // distribution parameters bad.
      return result;
   } 
   if(x == 0)
   { // Treat random variate zero as a special case.
      return 0;
   }
   else if(false == detail::check_inverse_gamma_x(function, x, &result, Policy()))
   { // x bad.
      return result;
   }
   result = scale / x;
   if(result < tools::min_value<RealType>())
      return 0;  // random variable is infinite or so close as to make no difference.
   result = gamma_p_derivative(shape, result, Policy()) * scale;
   if(0 != result)
   {
      if(x < 0)
      {
         // x * x may under or overflow, likewise our result,
         // so be extra careful about the arithmetic:
         RealType lim = tools::max_value<RealType>() * x;
         if(lim < result)
            return policies::raise_overflow_error<RealType, Policy>(function, "PDF is infinite.", Policy());
         result /= x;
         if(lim < result)
            return policies::raise_overflow_error<RealType, Policy>(function, "PDF is infinite.", Policy());
         result /= x;
      }
      result /= (x * x);
   }
   // better than naive
   // result = (pow(scale, shape) * pow(x, (-shape -1)) * exp(-scale/x) ) / tgamma(shape);
   return result;
} // pdf

template <class RealType, class Policy>
inline RealType cdf(const inverse_gamma_distribution<RealType, Policy>& dist, const RealType& x)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::cdf(const inverse_gamma_distribution<%1%>&, %1%)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_inverse_gamma(function, scale, shape, &result, Policy()))
   { // distribution parameters bad.
      return result;
   }
   if (x == 0)
   { // Treat zero as a special case.
     return 0;
   }
   else if(false == detail::check_inverse_gamma_x(function, x, &result, Policy()))
   { // x bad
      return result;
   }
   result = boost::math::gamma_q(shape, scale / x, Policy());
   // result = tgamma(shape, scale / x) / tgamma(shape); // naive using tgamma
   return result;
} // cdf

template <class RealType, class Policy>
inline RealType quantile(const inverse_gamma_distribution<RealType, Policy>& dist, const RealType& p)
{
   BOOST_MATH_STD_USING  // for ADL of std functions
   using boost::math::gamma_q_inv;

   static const char* function = "boost::math::quantile(const inverse_gamma_distribution<%1%>&, %1%)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_inverse_gamma(function, scale, shape, &result, Policy()))
      return result;
   if(false == detail::check_probability(function, p, &result, Policy()))
      return result;
   if(p == 1)
   {
      return policies::raise_overflow_error<RealType>(function, 0, Policy());
   }
   result = gamma_q_inv(shape, p, Policy());
   if((result < 1) && (result * tools::max_value<RealType>() < scale))
      return policies::raise_overflow_error<RealType, Policy>(function, "Value of random variable in inverse gamma distribution quantile is infinite.", Policy());
   result = scale / result;
   return result;
}

template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<inverse_gamma_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::quantile(const gamma_distribution<%1%>&, %1%)";

   RealType shape = c.dist.shape();
   RealType scale = c.dist.scale();

   RealType result = 0;
   if(false == detail::check_inverse_gamma(function, scale, shape, &result, Policy()))
      return result;
   if(false == detail::check_inverse_gamma_x(function, c.param, &result, Policy()))
      return result;

   if(c.param == 0)
      return 1; // Avoid division by zero

   //result = 1. - gamma_q(shape, c.param / scale, Policy());
   result = gamma_p(shape, scale/c.param, Policy());
   return result;
}

template <class RealType, class Policy>
inline RealType quantile(const complemented2_type<inverse_gamma_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::quantile(const inverse_gamma_distribution<%1%>&, %1%)";

   RealType shape = c.dist.shape();
   RealType scale = c.dist.scale();
   RealType q = c.param;

   RealType result = 0;
   if(false == detail::check_inverse_gamma(function, scale, shape, &result, Policy()))
      return result;
   if(false == detail::check_probability(function, q, &result, Policy()))
      return result;

   if(q == 0)
   {
      return policies::raise_overflow_error<RealType>(function, 0, Policy());
   }
   result = gamma_p_inv(shape, q, Policy());
   if((result < 1) && (result * tools::max_value<RealType>() < scale))
      return policies::raise_overflow_error<RealType, Policy>(function, "Value of random variable in inverse gamma distribution quantile is infinite.", Policy());
   result = scale / result;
   return result;
}

template <class RealType, class Policy>
inline RealType mean(const inverse_gamma_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::mean(const inverse_gamma_distribution<%1%>&)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;

   if(false == detail::check_scale(function, scale, &result, Policy()))
   {
     return result;
   }
   if((shape <= 1) || !(boost::math::isfinite)(shape))
   {
     result = policies::raise_domain_error<RealType>(
       function,
       "Shape parameter is %1%, but for a defined mean it must be > 1", shape, Policy());
     return result;
   }
  result = scale / (shape - 1);
  return result;
} // mean

template <class RealType, class Policy>
inline RealType variance(const inverse_gamma_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::variance(const inverse_gamma_distribution<%1%>&)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
      if(false == detail::check_scale(function, scale, &result, Policy()))
   {
     return result;
   }
   if((shape <= 2) || !(boost::math::isfinite)(shape))
   {
     result = policies::raise_domain_error<RealType>(
       function,
       "Shape parameter is %1%, but for a defined variance it must be > 2", shape, Policy());
     return result;
   }
   result = (scale * scale) / ((shape - 1) * (shape -1) * (shape -2));
   return result;
}

template <class RealType, class Policy>
inline RealType mode(const inverse_gamma_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::mode(const inverse_gamma_distribution<%1%>&)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_inverse_gamma(function, scale, shape, &result, Policy()))
   {
      return result;
   }
   // Only defined for shape >= 0, but is checked by check_inverse_gamma.
   result = scale / (shape + 1);
   return result;
}

//template <class RealType, class Policy>
//inline RealType median(const gamma_distribution<RealType, Policy>& dist)
//{  // Wikipedia does not define median,
     // so rely on default definition quantile(0.5) in derived accessors.
//  return result.
//}

template <class RealType, class Policy>
inline RealType skewness(const inverse_gamma_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::skewness(const inverse_gamma_distribution<%1%>&)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();
   RealType result = 0;

   if(false == detail::check_scale(function, scale, &result, Policy()))
   {
     return result;
   }
   if((shape <= 3) || !(boost::math::isfinite)(shape))
   {
     result = policies::raise_domain_error<RealType>(
       function,
       "Shape parameter is %1%, but for a defined skewness it must be > 3", shape, Policy());
     return result;
   }
   result = (4 * sqrt(shape - 2) ) / (shape - 3);
   return result;
}

template <class RealType, class Policy>
inline RealType kurtosis_excess(const inverse_gamma_distribution<RealType, Policy>& dist)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   static const char* function = "boost::math::kurtosis_excess(const inverse_gamma_distribution<%1%>&)";

   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;
   if(false == detail::check_scale(function, scale, &result, Policy()))
   {
     return result;
   }
   if((shape <= 4) || !(boost::math::isfinite)(shape))
   {
     result = policies::raise_domain_error<RealType>(
       function,
       "Shape parameter is %1%, but for a defined kurtosis excess it must be > 4", shape, Policy());
     return result;
   }
   result = (30 * shape - 66) / ((shape - 3) * (shape - 4));
   return result;
}

template <class RealType, class Policy>
inline RealType kurtosis(const inverse_gamma_distribution<RealType, Policy>& dist)
{
  static const char* function = "boost::math::kurtosis(const inverse_gamma_distribution<%1%>&)";
   RealType shape = dist.shape();
   RealType scale = dist.scale();

   RealType result = 0;

  if(false == detail::check_scale(function, scale, &result, Policy()))
   {
     return result;
   }
   if((shape <= 4) || !(boost::math::isfinite)(shape))
   {
     result = policies::raise_domain_error<RealType>(
       function,
       "Shape parameter is %1%, but for a defined kurtosis it must be > 4", shape, Policy());
     return result;
   }
  return kurtosis_excess(dist) + 3;
}

} // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_STATS_INVERSE_GAMMA_HPP

/* inverse_gamma.hpp
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
*/