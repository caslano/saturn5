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

#ifdef __cpp_deduction_guides
template <class RealType>
inverse_gaussian_distribution(RealType)->inverse_gaussian_distribution<typename boost::math::tools::promote_args<RealType>::type>;
template <class RealType>
inverse_gaussian_distribution(RealType,RealType)->inverse_gaussian_distribution<typename boost::math::tools::promote_args<RealType>::type>;
#endif

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
  std::uintmax_t m = policies::get_max_root_iterations<Policy>(); // and max iterations.
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
  std::uintmax_t m = policies::get_max_root_iterations<Policy>();
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