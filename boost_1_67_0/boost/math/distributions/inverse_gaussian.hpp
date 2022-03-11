//  Copyright John Maddock 2010.
//  Copyright Paul A. Bristow 2010.

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_INVERSE_GAUSSIAN_HPP
#define BOOST_STATS_INVERSE_GAUSSIAN_HPP

#ifdef _MSC_VER
#pragma warning(disable: 4512) // assignment operator could not be generated
#endif

// http://en.wikipedia.org/wiki/Normal-inverse_Gaussian_distribution
// http://mathworld.wolfram.com/InverseGaussianDistribution.html

// The normal-inverse Gaussian distribution
// also called the Wald distribution (some sources limit this to when mean = 1).

// It is the continuous probability distribution
// that is defined as the normal variance-mean mixture where the mixing density is the 
// inverse Gaussian distribution. The tails of the distribution decrease more slowly
// than the normal distribution. It is therefore suitable to model phenomena
// where numerically large values are more probable than is the case for the normal distribution.

// The Inverse Gaussian distribution was first studied in relationship to Brownian motion.
// In 1956 M.C.K. Tweedie used the name 'Inverse Gaussian' because there is an inverse 
// relationship between the time to cover a unit distance and distance covered in unit time.

// Examples are returns from financial assets and turbulent wind speeds. 
// The normal-inverse Gaussian distributions form
// a subclass of the generalised hyperbolic distributions.

// See also

// http://en.wikipedia.org/wiki/Normal_distribution
// http://www.itl.nist.gov/div898/handbook/eda/section3/eda3661.htm
// Also:
// Weisstein, Eric W. "Normal Distribution."
// From MathWorld--A Wolfram Web Resource.
// http://mathworld.wolfram.com/NormalDistribution.html

// http://www.jstatsoft.org/v26/i04/paper General class of inverse Gaussian distributions.
// ig package - withdrawn but at http://cran.r-project.org/src/contrib/Archive/ig/

// http://www.stat.ucl.ac.be/ISdidactique/Rhelp/library/SuppDists/html/inverse_gaussian.html
// R package for dinverse_gaussian, ...

// http://www.statsci.org/s/inverse_gaussian.s  and http://www.statsci.org/s/inverse_gaussian.html

//#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/erf.hpp> // for erf/erfc.
#include <boost/math/distributions/complement.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions/gamma.hpp> // for gamma function
// using boost::math::gamma_p;

#include <boost/math/tools/tuple.hpp>
//using std::tr1::tuple;
//using std::tr1::make_tuple;
#include <boost/math/tools/roots.hpp>
//using boost::math::tools::newton_raphson_iterate;

#include <utility>

namespace boost{ namespace math{

template <class RealType = double, class Policy = policies::policy<> >
class inverse_gaussian_distribution
{
public:
   typedef RealType value_type;
   typedef Policy policy_type;

   inverse_gaussian_distribution(RealType l_mean = 1, RealType l_scale = 1)
      : m_mean(l_mean), m_scale(l_scale)
   { // Default is a 1,1 inverse_gaussian distribution.
     static const char* function = "boost::math::inverse_gaussian_distribution<%1%>::inverse_gaussian_distribution";

     RealType result;
     detail::check_scale(function, l_scale, &result, Policy());
     detail::check_location(function, l_mean, &result, Policy());
     detail::check_x_gt0(function, l_mean, &result, Policy());
   }

   RealType mean()const
   { // alias for location.
      return m_mean; // aka mu
   }

   // Synonyms, provided to allow generic use of find_location and find_scale.
   RealType location()const
   { // location, aka mu.
      return m_mean;
   }
   RealType scale()const
   { // scale, aka lambda.
      return m_scale;
   }

   RealType shape()const
   { // shape, aka phi = lambda/mu.
      return m_scale / m_mean;
   }

private:
   //
   // Data members:
   //
   RealType m_mean;  // distribution mean or location, aka mu.
   RealType m_scale;    // distribution standard deviation or scale, aka lambda.
}; // class normal_distribution

typedef inverse_gaussian_distribution<double> inverse_gaussian;

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> range(const inverse_gaussian_distribution<RealType, Policy>& /*dist*/)
{ // Range of permissible values for random variable x, zero to max.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(static_cast<RealType>(0.), max_value<RealType>()); // - to + max value.
}

template <class RealType, class Policy>
inline const std::pair<RealType, RealType> support(const inverse_gaussian_distribution<RealType, Policy>& /*dist*/)
{ // Range of supported values for random variable x, zero to max.
  // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
   using boost::math::tools::max_value;
   return std::pair<RealType, RealType>(static_cast<RealType>(0.),  max_value<RealType>()); // - to + max value.
}

template <class RealType, class Policy>
inline RealType pdf(const inverse_gaussian_distribution<RealType, Policy>& dist, const RealType& x)
{ // Probability Density Function
   BOOST_MATH_STD_USING  // for ADL of std functions

   RealType scale = dist.scale();
   RealType mean = dist.mean();
   RealType result = 0;
   static const char* function = "boost::math::pdf(const inverse_gaussian_distribution<%1%>&, %1%)";
   if(false == detail::check_scale(function, scale, &result, Policy()))
   {
      return result;
   }
   if(false == detail::check_location(function, mean, &result, Policy()))
   {
      return result;
   }
   if(false == detail::check_x_gt0(function, mean, &result, Policy()))
   {
      return result;
   }
   if(false == detail::check_positive_x(function, x, &result, Policy()))
   {
      return result;
   }

   if (x == 0)
   {
     return 0; // Convenient, even if not defined mathematically.
   }

   result =
     sqrt(scale / (constants::two_pi<RealType>() * x * x * x))
    * exp(-scale * (x - mean) * (x - mean) / (2 * x * mean * mean));
   return result;
} // pdf

template <class RealType, class Policy>
inline RealType cdf(const inverse_gaussian_distribution<RealType, Policy>& dist, const RealType& x)
{ // Cumulative Density Function.
   BOOST_MATH_STD_USING  // for ADL of std functions.

   RealType scale = dist.scale();
   RealType mean = dist.mean();
   static const char* function = "boost::math::cdf(const inverse_gaussian_distribution<%1%>&, %1%)";
   RealType result = 0;
   if(false == detail::check_scale(function, scale, &result, Policy()))
   {
      return result;
   }
   if(false == detail::check_location(function, mean, &result, Policy()))
   {
      return result;
   }
   if (false == detail::check_x_gt0(function, mean, &result, Policy()))
   {
      return result;
   }
   if(false == detail::check_positive_x(function, x, &result, Policy()))
   {
     return result;
   }
   if (x == 0)
   {
     return 0; // Convenient, even if not defined mathematically.
   }
   // Problem with this formula for large scale > 1000 or small x, 
   //result = 0.5 * (erf(sqrt(scale / x) * ((x / mean) - 1) / constants::root_two<RealType>(), Policy()) + 1)
   //  + exp(2 * scale / mean) / 2 
   //  * (1 - erf(sqrt(scale / x) * (x / mean + 1) / constants::root_two<RealType>(), Policy()));
   // so use normal distribution version:
   // Wikipedia CDF equation http://en.wikipedia.org/wiki/Inverse_Gaussian_distribution.

   normal_distribution<RealType> n01;

   RealType n0 = sqrt(scale / x);
   n0 *= ((x / mean) -1);
   RealType n1 = cdf(n01, n0);
   RealType expfactor = exp(2 * scale / mean);
   RealType n3 = - sqrt(scale / x);
   n3 *= (x / mean) + 1;
   RealType n4 = cdf(n01, n3);
   result = n1 + expfactor * n4;
   return result;
} // cdf

template <class RealType, class Policy>
struct inverse_gaussian_quantile_functor
{ 

  inverse_gaussian_quantile_functor(const boost::math::inverse_gaussian_distribution<RealType, Policy> dist, RealType const& p)
    : distribution(dist), prob(p)
  {
  }
  boost::math::tuple<RealType, RealType> operator()(RealType const& x)
  {
    RealType c = cdf(distribution, x);
    RealType fx = c - prob;  // Difference cdf - value - to minimize.
    RealType dx = pdf(distribution, x); // pdf is 1st derivative.
    // return both function evaluation difference f(x) and 1st derivative f'(x).
    return boost::math::make_tuple(fx, dx);
  }
  private:
  const boost::math::inverse_gaussian_distribution<RealType, Policy> distribution;
  RealType prob; 
};

template <class RealType, class Policy>
struct inverse_gaussian_quantile_complement_functor
{ 
    inverse_gaussian_quantile_complement_functor(const boost::math::inverse_gaussian_distribution<RealType, Policy> dist, RealType const& p)
    : distribution(dist), prob(p)
  {
  }
  boost::math::tuple<RealType, RealType> operator()(RealType const& x)
  {
    RealType c = cdf(complement(distribution, x));
    RealType fx = c - prob;  // Difference cdf - value - to minimize.
    RealType dx = -pdf(distribution, x); // pdf is 1st derivative.
    // return both function evaluation difference f(x) and 1st derivative f'(x).
    //return std::tr1::make_tuple(fx, dx); if available.
    return boost::math::make_tuple(fx, dx);
  }
  private:
  const boost::math::inverse_gaussian_distribution<RealType, Policy> distribution;
  RealType prob; 
};

namespace detail
{
  template <class RealType>
  inline RealType guess_ig(RealType p, RealType mu = 1, RealType lambda = 1)
  { // guess at random variate value x for inverse gaussian quantile.
      BOOST_MATH_STD_USING
      using boost::math::policies::policy;
      // Error type.
      using boost::math::policies::overflow_error;
      // Action.
      using boost::math::policies::ignore_error;

      typedef policy<
        overflow_error<ignore_error> // Ignore overflow (return infinity)
      > no_overthrow_policy;

    RealType x; // result is guess at random variate value x.
    RealType phi = lambda / mu;
    if (phi > 2.)
    { // Big phi, so starting to look like normal Gaussian distribution.
      //    x=(qnorm(p,0,1,true,false) - 0.5 * sqrt(mu/lambda)) / sqrt(lambda/mu);
      // Whitmore, G.A. and Yalovsky, M.
      // A normalising logarithmic transformation for inverse Gaussian random variables,
      // Technometrics 20-2, 207-208 (1978), but using expression from
      // V Seshadri, Inverse Gaussian distribution (1998) ISBN 0387 98618 9, page 6.
 
      normal_distribution<RealType, no_overthrow_policy> n01;
      x = mu * exp(quantile(n01, p) / sqrt(phi) - 1/(2 * phi));
     }
    else
    { // phi < 2 so much less symmetrical with long tail,
      // so use gamma distribution as an approximation.
      using boost::math::gamma_distribution;

      // Define the distribution, using gamma_nooverflow:
      typedef gamma_distribution<RealType, no_overthrow_policy> gamma_nooverflow;

      gamma_nooverflow g(static_cast<RealType>(0.5), static_cast<RealType>(1.));

      // gamma_nooverflow g(static_cast<RealType>(0.5), static_cast<RealType>(1.));
      // R qgamma(0.2, 0.5, 1)  0.0320923
      RealType qg = quantile(complement(g, p));
      //RealType qg1 = qgamma(1.- p, 0.5, 1.0, true, false);
      x = lambda / (qg * 2);
      // 
      if (x > mu/2) // x > mu /2?
      { // x too large for the gamma approximation to work well.
        //x = qgamma(p, 0.5, 1.0); // qgamma(0.270614, 0.5, 1) = 0.05983807
        RealType q = quantile(g, p);
       // x = mu * exp(q * static_cast<RealType>(0.1));  // Said to improve at high p
       // x = mu * x;  // Improves at high p?
        x = mu * exp(q / sqrt(phi) - 1/(2 * phi));
      }
    }
    return x;
  }  // guess_ig
} // namespace detail

template <class RealType, class Policy>
inline RealType quantile(const inverse_gaussian_distribution<RealType, Policy>& dist, const RealType& p)
{
   BOOST_MATH_STD_USING  // for ADL of std functions.
   // No closed form exists so guess and use Newton Raphson iteration.

   RealType mean = dist.mean();
   RealType scale = dist.scale();
   static const char* function = "boost::math::quantile(const inverse_gaussian_distribution<%1%>&, %1%)";

   RealType result = 0;
   if(false == detail::check_scale(function, scale, &result, Policy()))
      return result;
   if(false == detail::check_location(function, mean, &result, Policy()))
      return result;
   if (false == detail::check_x_gt0(function, mean, &result, Policy()))
      return result;
   if(false == detail::check_probability(function, p, &result, Policy()))
      return result;
   if (p == 0)
   {
     return 0; // Convenient, even if not defined mathematically?
   }
   if (p == 1)
   { // overflow 
      result = policies::raise_overflow_error<RealType>(function,
        "probability parameter is 1, but must be < 1!", Policy());
      return result; // std::numeric_limits<RealType>::infinity();
   }

  RealType guess = detail::guess_ig(p, dist.mean(), dist.scale());
  using boost::math::tools::max_value;

  RealType min = 0.; // Minimum possible value is bottom of range of distribution.
  RealType max = max_value<RealType>();// Maximum possible value is top of range. 
  // int digits = std::numeric_limits<RealType>::digits; // Maximum possible binary digits accuracy for type T.
  // digits used to control how accurate to try to make the result.
  // To allow user to control accuracy versus speed,
  int get_digits = policies::digits<RealType, Policy>();// get digits from policy, 
  boost::uintmax_t m = policies::get_max_root_iterations<Policy>(); // and max iterations.
  using boost::math::tools::newton_raphson_iterate;
  result =
    newton_raphson_iterate(inverse_gaussian_quantile_functor<RealType, Policy>(dist, p), guess, min, max, get_digits, m);
   return result;
} // quantile

template <class RealType, class Policy>
inline RealType cdf(const complemented2_type<inverse_gaussian_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING  // for ADL of std functions.

   RealType scale = c.dist.scale();
   RealType mean = c.dist.mean();
   RealType x = c.param;
   static const char* function = "boost::math::cdf(const complement(inverse_gaussian_distribution<%1%>&), %1%)";
   // infinite arguments not supported.
   //if((boost::math::isinf)(x))
   //{
   //  if(x < 0) return 1; // cdf complement -infinity is unity.
   //  return 0; // cdf complement +infinity is zero
   //}
   // These produce MSVC 4127 warnings, so the above used instead.
   //if(std::numeric_limits<RealType>::has_infinity && x == std::numeric_limits<RealType>::infinity())
   //{ // cdf complement +infinity is zero.
   //  return 0;
   //}
   //if(std::numeric_limits<RealType>::has_infinity && x == -std::numeric_limits<RealType>::infinity())
   //{ // cdf complement -infinity is unity.
   //  return 1;
   //}
   RealType result = 0;
   if(false == detail::check_scale(function, scale, &result, Policy()))
      return result;
   if(false == detail::check_location(function, mean, &result, Policy()))
      return result;
   if (false == detail::check_x_gt0(function, mean, &result, Policy()))
      return result;
   if(false == detail::check_positive_x(function, x, &result, Policy()))
      return result;

   normal_distribution<RealType> n01;
   RealType n0 = sqrt(scale / x);
   n0 *= ((x / mean) -1);
   RealType cdf_1 = cdf(complement(n01, n0));

   RealType expfactor = exp(2 * scale / mean);
   RealType n3 = - sqrt(scale / x);
   n3 *= (x / mean) + 1;

   //RealType n5 = +sqrt(scale/x) * ((x /mean) + 1); // note now positive sign.
   RealType n6 = cdf(complement(n01, +sqrt(scale/x) * ((x /mean) + 1)));
   // RealType n4 = cdf(n01, n3); // = 
   result = cdf_1 - expfactor * n6; 
   return result;
} // cdf complement

template <class RealType, class Policy>
inline RealType quantile(const complemented2_type<inverse_gaussian_distribution<RealType, Policy>, RealType>& c)
{
   BOOST_MATH_STD_USING  // for ADL of std functions

   RealType scale = c.dist.scale();
   RealType mean = c.dist.mean();
   static const char* function = "boost::math::quantile(const complement(inverse_gaussian_distribution<%1%>&), %1%)";
   RealType result = 0;
   if(false == detail::check_scale(function, scale, &result, Policy()))
      return result;
   if(false == detail::check_location(function, mean, &result, Policy()))
      return result;
   if (false == detail::check_x_gt0(function, mean, &result, Policy()))
      return result;
   RealType q = c.param;
   if(false == detail::check_probability(function, q, &result, Policy()))
      return result;

   RealType guess = detail::guess_ig(q, mean, scale);
   // Complement.
   using boost::math::tools::max_value;

  RealType min = 0.; // Minimum possible value is bottom of range of distribution.
  RealType max = max_value<RealType>();// Maximum possible value is top of range. 
  // int digits = std::numeric_limits<RealType>::digits; // Maximum possible binary digits accuracy for type T.
  // digits used to control how accurate to try to make the result.
  int get_digits = policies::digits<RealType, Policy>();
  boost::uintmax_t m = policies::get_max_root_iterations<Policy>();
  using boost::math::tools::newton_raphson_iterate;
  result =
    newton_raphson_iterate(inverse_gaussian_quantile_complement_functor<RealType, Policy>(c.dist, q), guess, min, max, get_digits, m);
   return result;
} // quantile

template <class RealType, class Policy>
inline RealType mean(const inverse_gaussian_distribution<RealType, Policy>& dist)
{ // aka mu
   return dist.mean();
}

template <class RealType, class Policy>
inline RealType scale(const inverse_gaussian_distribution<RealType, Policy>& dist)
{ // aka lambda
   return dist.scale();
}

template <class RealType, class Policy>
inline RealType shape(const inverse_gaussian_distribution<RealType, Policy>& dist)
{ // aka phi
   return dist.shape();
}

template <class RealType, class Policy>
inline RealType standard_deviation(const inverse_gaussian_distribution<RealType, Policy>& dist)
{
  BOOST_MATH_STD_USING
  RealType scale = dist.scale();
  RealType mean = dist.mean();
  RealType result = sqrt(mean * mean * mean / scale);
  return result;
}

template <class RealType, class Policy>
inline RealType mode(const inverse_gaussian_distribution<RealType, Policy>& dist)
{
  BOOST_MATH_STD_USING
  RealType scale = dist.scale();
  RealType  mean = dist.mean();
  RealType result = mean * (sqrt(1 + (9 * mean * mean)/(4 * scale * scale)) 
      - 3 * mean / (2 * scale));
  return result;
}

template <class RealType, class Policy>
inline RealType skewness(const inverse_gaussian_distribution<RealType, Policy>& dist)
{
  BOOST_MATH_STD_USING
  RealType scale = dist.scale();
  RealType  mean = dist.mean();
  RealType result = 3 * sqrt(mean/scale);
  return result;
}

template <class RealType, class Policy>
inline RealType kurtosis(const inverse_gaussian_distribution<RealType, Policy>& dist)
{
  RealType scale = dist.scale();
  RealType  mean = dist.mean();
  RealType result = 15 * mean / scale -3;
  return result;
}

template <class RealType, class Policy>
inline RealType kurtosis_excess(const inverse_gaussian_distribution<RealType, Policy>& dist)
{
  RealType scale = dist.scale();
  RealType  mean = dist.mean();
  RealType result = 15 * mean / scale;
  return result;
}

} // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_STATS_INVERSE_GAUSSIAN_HPP



/* inverse_gaussian.hpp
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
*/