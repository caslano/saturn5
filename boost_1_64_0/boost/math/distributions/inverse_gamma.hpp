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
Tbzx1khvlLXRm2A97q0a+u6QvJ+r/N/mzfJ2wc2Z733J+QaO5zQvn6Xs9Dt6ovLXnNCjrZGel8kT3B3xSbWiSGGOp4H3PGuDl7FZOl9pcUgZCebtX5WffE8n6+Vy87a6ToNazkndw+Pcw6C8kjGMeUiE5yqZe9ByLvMGv9GmKLel3iroQFNK0mr3awcSbPuXcb2Wkk31fcc17PoloT31FT2QzVT90oKOW6vUOzEotxS55sixp8kRf/UovY9JC9xaYlQ7UGQ3INtKtaWXt3R9x+nw9urwlrMolzE8LXuqRPan/vgqZV47tZOMcUhcsczdTm0STAsyrZHxrbC3F0qyjdrCqGZ1y1j32GHXx08+pnFgfNQE074rdSX8np0lvjErHvQ39vurzdf5quLbGrllhJWJXAuRY3Ok6oxRSfRVi0nxe+P4MSYmxu+NdzyL8pwRf1W+l9Eiq0b7a5RVXZ6/jco9xvhdvk6di7Lqhjx3j/PcxXvlGVPpcObljM7B+7gi1XUfdVozugTTuvwdf7Nq/oSCx0LS2h65HMJpi1wLkYtvR1rjnGktWEtio+PxY0rvA6peeRF7NfJujU7vW+vDp/eN9ab0biS953oCdcsgSa9u96nxzm2IY1uMELfAuyc5wnHP1Sl56szdXA8k0SZcqeJipQ8e2jnDEreLtFunLkG37iVunYJu7UvctN9frwu6ddR+t5a4Kb/Vcft2vVnnIX3t5nHWotsYui60vfn8ete6jHeZ+zt2nWup40VOniP8NpN35N2B9+yiOfmzJ+flzpmdb9B7yPus1j3IkoHBb7Eaym7UCxKusX9Uj+Fvo/yu1GHVV/ZG5r5WR1jfZBKWa4xyc+V3mLnv9e7y3+Eyj0DGNpP/Mo+gtwp3rmexdY/V0cN+bjKXIG+D0laqtHyK/yFKbppHvx8c/bsp2Bqq8w3dY6j1vI4x6vx4x3yGmbMX5uWr859wvr86nyPhl8x3qC7vqG7q/OUehx7BvoDWI3RX55d4hnoS3e8w3fe3SMmcR+tgu/WdlS7ufCMq99f54o7iTLyqc5d2pV+LQtROvZ8u1fXKZ1IHBWX83alnAu+bbe56qonIHEEmERlfwWvxvRkEmM6/WTHV/NFRIXWO1C20zVV8kqX9E4zfBmKXTFmPtS7gm2cR35bX4jup5FsgbzJZ5hwLsFv5u0fs+p6680eXsQNKPipsvjjTHXVuMN0Fp3W6nfpTqdM6IDNC5n5MxDjmd2g9XWqE9VtYnZ2hn9+PG88RbjxH4eobV7/PuPNKr+X3d8JI2xhcy6/3wGHyjSHlvIw1/MQf//RY5Qqsy6fG6xK2W39UZIhjcg/ehSFxpJ3IwohzKA263EZwbWdezDi/9HW+IE49Q6+zaK58r3xedl7g7+zXXvw8TF6Myiwdx7/hlhUSRzaBrcA9w6+uS3MTyt8DNmvj2e8BS1xK7QHLNd17wOp70r1H6fSm4DYlNL2L8nIiSyv+XHpjtlIMp8d3pfN4Be6fTqd7HJFcz5nG+heUTuNJ/OeGpFH1XUVU7nI3Rr6OZu7Gs19H8/PM8tfRDOoN4y4sncZP8V+g06hGFQ/o16tvvxGOvqT3y04r/p19w2XeTy2r+3QqUG7fN6SV68n9DE3r84a01qTMFprSqnrULfXs/VbFn1FOvOWzw62R6kpD/wjSkCJpIHziK+G79pje1bN0nP9KmreY4qzrl8ju0RZH/fLq+eXXL1t+QP3yvqF+4Zph95je0stcLnea0009E1mad1agXO78AfVMRcrlqt6l0/ox/otMaXXUNx+Vk9aiCtQ3RT+gvvmoAvXN0j6l0xrHM7g/NK1ZvUb0GiLVjYr/u+Wkdb8jrb8=
*/