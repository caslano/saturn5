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

#ifdef __cpp_deduction_guides
template <class RealType>
inverse_gamma_distribution(RealType)->inverse_gamma_distribution<typename boost::math::tools::promote_args<RealType>::type>;
template <class RealType>
inverse_gamma_distribution(RealType,RealType)->inverse_gamma_distribution<typename boost::math::tools::promote_args<RealType>::type>;
#endif

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