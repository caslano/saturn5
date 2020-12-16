//  Copyright John Maddock 2006, 2007.
//  Copyright Paul A. Bristow 2006, 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_TRIANGULAR_HPP
#define BOOST_STATS_TRIANGULAR_HPP

// http://mathworld.wolfram.com/TriangularDistribution.html
// Note that the 'constructors' defined by Wolfram are difference from those here,
// for example
// N[variance[triangulardistribution{1, +2}, 1.5], 50] computes 
// 0.041666666666666666666666666666666666666666666666667
// TriangularDistribution{1, +2}, 1.5 is the analog of triangular_distribution(1, 1.5, 2)

// http://en.wikipedia.org/wiki/Triangular_distribution

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/expm1.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/math/distributions/complement.hpp>
#include <boost/math/constants/constants.hpp>

#include <utility>

namespace boost{ namespace math
{
  namespace detail
  {
    template <class RealType, class Policy>
    inline bool check_triangular_lower(
      const char* function,
      RealType lower,
      RealType* result, const Policy& pol)
    {
      if((boost::math::isfinite)(lower))
      { // Any finite value is OK.
        return true;
      }
      else
      { // Not finite: infinity or NaN.
        *result = policies::raise_domain_error<RealType>(
          function,
          "Lower parameter is %1%, but must be finite!", lower, pol);
        return false;
      }
    } // bool check_triangular_lower(

    template <class RealType, class Policy>
    inline bool check_triangular_mode(
      const char* function,
      RealType mode,
      RealType* result, const Policy& pol)
    {
      if((boost::math::isfinite)(mode))
      { // any finite value is OK.
        return true;
      }
      else
      { // Not finite: infinity or NaN.
        *result = policies::raise_domain_error<RealType>(
          function,
          "Mode parameter is %1%, but must be finite!", mode, pol);
        return false;
      }
    } // bool check_triangular_mode(

    template <class RealType, class Policy>
    inline bool check_triangular_upper(
      const char* function,
      RealType upper,
      RealType* result, const Policy& pol)
    {
      if((boost::math::isfinite)(upper))
      { // any finite value is OK.
        return true;
      }
      else
      { // Not finite: infinity or NaN.
        *result = policies::raise_domain_error<RealType>(
          function,
          "Upper parameter is %1%, but must be finite!", upper, pol);
        return false;
      }
    } // bool check_triangular_upper(

    template <class RealType, class Policy>
    inline bool check_triangular_x(
      const char* function,
      RealType const& x,
      RealType* result, const Policy& pol)
    {
      if((boost::math::isfinite)(x))
      { // Any finite value is OK
        return true;
      }
      else
      { // Not finite: infinity or NaN.
        *result = policies::raise_domain_error<RealType>(
          function,
          "x parameter is %1%, but must be finite!", x, pol);
        return false;
      }
    } // bool check_triangular_x

    template <class RealType, class Policy>
    inline bool check_triangular(
      const char* function,
      RealType lower,
      RealType mode,
      RealType upper,
      RealType* result, const Policy& pol)
    {
      if ((check_triangular_lower(function, lower, result, pol) == false)
        || (check_triangular_mode(function, mode, result, pol) == false)
        || (check_triangular_upper(function, upper, result, pol) == false))
      { // Some parameter not finite.
        return false;
      }
      else if (lower >= upper) // lower == upper NOT useful.
      { // lower >= upper.
        *result = policies::raise_domain_error<RealType>(
          function,
          "lower parameter is %1%, but must be less than upper!", lower, pol);
        return false;
      }
      else
      { // Check lower <= mode <= upper.
        if (mode < lower)
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "mode parameter is %1%, but must be >= than lower!", lower, pol);
          return false;
        }
        if (mode > upper)
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "mode parameter is %1%, but must be <= than upper!", upper, pol);
          return false;
        }
        return true; // All OK.
      }
    } // bool check_triangular
  } // namespace detail

  template <class RealType = double, class Policy = policies::policy<> >
  class triangular_distribution
  {
  public:
    typedef RealType value_type;
    typedef Policy policy_type;

    triangular_distribution(RealType l_lower = -1, RealType l_mode = 0, RealType l_upper = 1)
      : m_lower(l_lower), m_mode(l_mode), m_upper(l_upper) // Constructor.
    { // Evans says 'standard triangular' is lower 0, mode 1/2, upper 1,
      // has median sqrt(c/2) for c <=1/2 and 1 - sqrt(1-c)/2 for c >= 1/2
      // But this -1, 0, 1 is more useful in most applications to approximate normal distribution,
      // where the central value is the most likely and deviations either side equally likely.
      RealType result;
      detail::check_triangular("boost::math::triangular_distribution<%1%>::triangular_distribution",l_lower, l_mode, l_upper, &result, Policy());
    }
    // Accessor functions.
    RealType lower()const
    {
      return m_lower;
    }
    RealType mode()const
    {
      return m_mode;
    }
    RealType upper()const
    {
      return m_upper;
    }
  private:
    // Data members:
    RealType m_lower;  // distribution lower aka a
    RealType m_mode;  // distribution mode aka c
    RealType m_upper;  // distribution upper aka b
  }; // class triangular_distribution

  typedef triangular_distribution<double> triangular;

  template <class RealType, class Policy>
  inline const std::pair<RealType, RealType> range(const triangular_distribution<RealType, Policy>& /* dist */)
  { // Range of permissible values for random variable x.
    using boost::math::tools::max_value;
    return std::pair<RealType, RealType>(-max_value<RealType>(), max_value<RealType>());
  }

  template <class RealType, class Policy>
  inline const std::pair<RealType, RealType> support(const triangular_distribution<RealType, Policy>& dist)
  { // Range of supported values for random variable x.
    // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
    return std::pair<RealType, RealType>(dist.lower(), dist.upper());
  }

  template <class RealType, class Policy>
  RealType pdf(const triangular_distribution<RealType, Policy>& dist, const RealType& x)
  {
    static const char* function = "boost::math::pdf(const triangular_distribution<%1%>&, %1%)";
    RealType lower = dist.lower();
    RealType mode = dist.mode();
    RealType upper = dist.upper();
    RealType result = 0; // of checks.
    if(false == detail::check_triangular(function, lower, mode, upper, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_triangular_x(function, x, &result, Policy()))
    {
      return result;
    }
    if((x < lower) || (x > upper))
    {
      return 0;
    }
    if (x == lower)
    { // (mode - lower) == 0 which would lead to divide by zero!
      return (mode == lower) ? 2 / (upper - lower) : RealType(0);
    }
    else if (x == upper)
    {
      return (mode == upper) ? 2 / (upper - lower) : RealType(0);
    }
    else if (x <= mode)
    {
      return 2 * (x - lower) / ((upper - lower) * (mode - lower));
    }
    else
    {  // (x > mode)
      return 2 * (upper - x) / ((upper - lower) * (upper - mode));
    }
  } // RealType pdf(const triangular_distribution<RealType, Policy>& dist, const RealType& x)

  template <class RealType, class Policy>
  inline RealType cdf(const triangular_distribution<RealType, Policy>& dist, const RealType& x)
  {
    static const char* function = "boost::math::cdf(const triangular_distribution<%1%>&, %1%)";
    RealType lower = dist.lower();
    RealType mode = dist.mode();
    RealType upper = dist.upper();
    RealType result = 0; // of checks.
    if(false == detail::check_triangular(function, lower, mode, upper, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_triangular_x(function, x, &result, Policy()))
    {
      return result;
    }
    if((x <= lower))
    {
      return 0;
    }
    if (x >= upper)
    {
      return 1;
    }
    // else lower < x < upper
    if (x <= mode)
    {
      return ((x - lower) * (x - lower)) / ((upper - lower) * (mode - lower));
    }
    else
    {
      return 1 - (upper - x) *  (upper - x) / ((upper - lower) * (upper - mode));
    }
  } // RealType cdf(const triangular_distribution<RealType, Policy>& dist, const RealType& x)

  template <class RealType, class Policy>
  RealType quantile(const triangular_distribution<RealType, Policy>& dist, const RealType& p)
  {
    BOOST_MATH_STD_USING  // for ADL of std functions (sqrt).
    static const char* function = "boost::math::quantile(const triangular_distribution<%1%>&, %1%)";
    RealType lower = dist.lower();
    RealType mode = dist.mode();
    RealType upper = dist.upper();
    RealType result = 0; // of checks
    if(false == detail::check_triangular(function,lower, mode, upper, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_probability(function, p, &result, Policy()))
    {
      return result;
    }
    if(p == 0)
    {
      return lower;
    }
    if(p == 1)
    {
      return upper;
    }
    RealType p0 = (mode - lower) / (upper - lower);
    RealType q = 1 - p;
    if (p < p0)
    {
      result = sqrt((upper - lower) * (mode - lower) * p) + lower;
    }
    else if (p == p0)
    {
      result = mode;
    }
    else // p > p0
    {
      result = upper - sqrt((upper - lower) * (upper - mode) * q);
    }
    return result;

  } // RealType quantile(const triangular_distribution<RealType, Policy>& dist, const RealType& q)

  template <class RealType, class Policy>
  RealType cdf(const complemented2_type<triangular_distribution<RealType, Policy>, RealType>& c)
  {
    static const char* function = "boost::math::cdf(const triangular_distribution<%1%>&, %1%)";
    RealType lower = c.dist.lower();
    RealType mode = c.dist.mode();
    RealType upper = c.dist.upper();
    RealType x = c.param;
    RealType result = 0; // of checks.
    if(false == detail::check_triangular(function, lower, mode, upper, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_triangular_x(function, x, &result, Policy()))
    {
      return result;
    }
    if (x <= lower)
    {
      return 1;
    }
    if (x >= upper)
    {
      return 0;
    }
    if (x <= mode)
    {
      return 1 - ((x - lower) * (x - lower)) / ((upper - lower) * (mode - lower));
    }
    else
    {
      return (upper - x) *  (upper - x) / ((upper - lower) * (upper - mode));
    }
  } // RealType cdf(const complemented2_type<triangular_distribution<RealType, Policy>, RealType>& c)

  template <class RealType, class Policy>
  RealType quantile(const complemented2_type<triangular_distribution<RealType, Policy>, RealType>& c)
  {
    BOOST_MATH_STD_USING  // Aid ADL for sqrt.
    static const char* function = "boost::math::quantile(const triangular_distribution<%1%>&, %1%)";
    RealType l = c.dist.lower();
    RealType m = c.dist.mode();
    RealType u = c.dist.upper();
    RealType q = c.param; // probability 0 to 1.
    RealType result = 0; // of checks.
    if(false == detail::check_triangular(function, l, m, u, &result, Policy()))
    {
      return result;
    }
    if(false == detail::check_probability(function, q, &result, Policy()))
    {
      return result;
    }
    if(q == 0)
    {
      return u;
    }
    if(q == 1)
    {
      return l;
    }
    RealType lower = c.dist.lower();
    RealType mode = c.dist.mode();
    RealType upper = c.dist.upper();

    RealType p = 1 - q;
    RealType p0 = (mode - lower) / (upper - lower);
    if(p < p0)
    {
      RealType s = (upper - lower) * (mode - lower);
      s *= p;
      result = sqrt((upper - lower) * (mode - lower) * p) + lower;
    }
    else if (p == p0)
    {
      result = mode;
    }
    else // p > p0
    {
      result = upper - sqrt((upper - lower) * (upper - mode) * q);
    }
    return result;
  } // RealType quantile(const complemented2_type<triangular_distribution<RealType, Policy>, RealType>& c)

  template <class RealType, class Policy>
  inline RealType mean(const triangular_distribution<RealType, Policy>& dist)
  {
    static const char* function = "boost::math::mean(const triangular_distribution<%1%>&)";
    RealType lower = dist.lower();
    RealType mode = dist.mode();
    RealType upper = dist.upper();
    RealType result = 0;  // of checks.
    if(false == detail::check_triangular(function, lower, mode, upper, &result, Policy()))
    {
      return result;
    }
    return (lower + upper + mode) / 3;
  } // RealType mean(const triangular_distribution<RealType, Policy>& dist)


  template <class RealType, class Policy>
  inline RealType variance(const triangular_distribution<RealType, Policy>& dist)
  {
    static const char* function = "boost::math::mean(const triangular_distribution<%1%>&)";
    RealType lower = dist.lower();
    RealType mode = dist.mode();
    RealType upper = dist.upper();
    RealType result = 0; // of checks.
    if(false == detail::check_triangular(function, lower, mode, upper, &result, Policy()))
    {
      return result;
    }
    return (lower * lower + upper * upper + mode * mode - lower * upper - lower * mode - upper * mode) / 18;
  } // RealType variance(const triangular_distribution<RealType, Policy>& dist)

  template <class RealType, class Policy>
  inline RealType mode(const triangular_distribution<RealType, Policy>& dist)
  {
    static const char* function = "boost::math::mode(const triangular_distribution<%1%>&)";
    RealType mode = dist.mode();
    RealType result = 0; // of checks.
    if(false == detail::check_triangular_mode(function, mode, &result, Policy()))
    { // This should never happen!
      return result;
    }
    return mode;
  } // RealType mode

  template <class RealType, class Policy>
  inline RealType median(const triangular_distribution<RealType, Policy>& dist)
  {
    BOOST_MATH_STD_USING // ADL of std functions.
    static const char* function = "boost::math::median(const triangular_distribution<%1%>&)";
    RealType mode = dist.mode();
    RealType result = 0; // of checks.
    if(false == detail::check_triangular_mode(function, mode, &result, Policy()))
    { // This should never happen!
      return result;
    }
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    if (mode >= (upper + lower) / 2)
    {
      return lower + sqrt((upper - lower) * (mode - lower)) / constants::root_two<RealType>();
    }
    else
    {
      return upper - sqrt((upper - lower) * (upper - mode)) / constants::root_two<RealType>();
    }
  } // RealType mode

  template <class RealType, class Policy>
  inline RealType skewness(const triangular_distribution<RealType, Policy>& dist)
  {
    BOOST_MATH_STD_USING  // for ADL of std functions
    using namespace boost::math::constants; // for root_two
    static const char* function = "boost::math::skewness(const triangular_distribution<%1%>&)";

    RealType lower = dist.lower();
    RealType mode = dist.mode();
    RealType upper = dist.upper();
    RealType result = 0; // of checks.
    if(false == boost::math::detail::check_triangular(function,lower, mode, upper, &result, Policy()))
    {
      return result;
    }
    return root_two<RealType>() * (lower + upper - 2 * mode) * (2 * lower - upper - mode) * (lower - 2 * upper + mode) /
      (5 * pow((lower * lower + upper * upper + mode * mode 
        - lower * upper - lower * mode - upper * mode), RealType(3)/RealType(2)));
    // #11768: Skewness formula for triangular distribution is incorrect -  corrected 29 Oct 2015 for release 1.61.
  } // RealType skewness(const triangular_distribution<RealType, Policy>& dist)

  template <class RealType, class Policy>
  inline RealType kurtosis(const triangular_distribution<RealType, Policy>& dist)
  { // These checks may be belt and braces as should have been checked on construction?
    static const char* function = "boost::math::kurtosis(const triangular_distribution<%1%>&)";
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType mode = dist.mode();
    RealType result = 0;  // of checks.
    if(false == detail::check_triangular(function,lower, mode, upper, &result, Policy()))
    {
      return result;
    }
    return static_cast<RealType>(12)/5; //  12/5 = 2.4;
  } // RealType kurtosis_excess(const triangular_distribution<RealType, Policy>& dist)

  template <class RealType, class Policy>
  inline RealType kurtosis_excess(const triangular_distribution<RealType, Policy>& dist)
  { // These checks may be belt and braces as should have been checked on construction?
    static const char* function = "boost::math::kurtosis_excess(const triangular_distribution<%1%>&)";
    RealType lower = dist.lower();
    RealType upper = dist.upper();
    RealType mode = dist.mode();
    RealType result = 0;  // of checks.
    if(false == detail::check_triangular(function,lower, mode, upper, &result, Policy()))
    {
      return result;
    }
    return static_cast<RealType>(-3)/5; // - 3/5 = -0.6
    // Assuming mathworld really means kurtosis excess?  Wikipedia now corrected to match this.
  }

  template <class RealType, class Policy>
  inline RealType entropy(const triangular_distribution<RealType, Policy>& dist)
  {
    using std::log;
    return constants::half<RealType>() + log((dist.upper() - dist.lower())/2);
  }

} // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_STATS_TRIANGULAR_HPP




/* triangular.hpp
C90bkwJjYBtYDxbB+jAVJsMOsDnsCFNgIUxTuVNhJ9gXdoaDYVc4AXaD58PucL6GK9VwS2EvuAr2hlfBfnAzPA0+A0+HezTcexrufTgYHoJD4CdwBGxCnkbD1nAsHALPgONgIZwOi+AMOB7mwgmwAJ4D74TnwgfgNPgunA4PafgvNPyXcCZ0KM9ZsA48H8bC4Pk4mAUHwVw4Bs6HK+ACeCXMh9eofBkshLfp8SaYDe/R4/tgAdymx1qvOh7JmH1cvV6s9bpc63UFjIWXQNED0/pcDVvCy2Bb+CRsB1fqntZVsJv6d4eXw/7wCpgOr4JD4dVwOFwLp8AfwukabgYsg3Pgj+Bc3UO7AK6DF8Lr4ffhDfBquB6WafgfwZt1jfcWeBu8Fd4Bb4MPwNvh43Cjrv1t0nZzJ3xT43kL3qXt6G5tP1vg7+C98Et4HwwW6v0wDm6FCfAB2AY+CDvAJ2FH+BDsAR+BfeB2bXePart7DE6FP4FZcAecBx+HpfCn8GKNLz0ge6ROuDfK/u1dz/pd5Wt3rNlVbb3O+31e/5pcC5iO0zU4+/qbZ+3tGPSvsx3GfyWsaF1tJM6/lrYWToJlum62FVfZelkxTtbIfN8D/tLzTeBawypfA9P1L1378q512de57GtcFa9pvWf/nrBZu/KvWe3EjdV1qv0jIGtTh2vWp2p+Nb9/y+9f9f6fVbwwOAHwT7//53h0/8dHhfJwFvegU2B/OAwFnkn9y/V8z50yYsoZE0bxWbn5XMfo5ZpvWS0U2Xbug05j6/s9cRndX967+KvY855mzpt3uCTzjliQmxu0W5qduZRD8555Z/8KbfabuIgDWY1DbZ+G40iA94hcvE23V+NQu//BSD06w3vR60w08wRBM+wZi/nD6MkXmLJIlPwWqr5s+JsBr8n5+3h+bavfheE6A4J+oW/89BKbesUmzsZwvYT5C89sTZDBj6PmEqY2z+UzpMxyqdO5uHm4sA5tHn9vgOvU9lUn02Ij9GRHUB6k9TTR220i+Y5OIE2qMxu2eWn0YY2+LHXJcbHaSNZ3W1+dcU7Ll3O+uuD9V8qTMlZ92kibrke1bTbESd3hngsW4sDj22bWvJysBZIP9qZI+8y2tUXCRtoFm596Yrum4fwTbzCdEXafX1aDZ8/imuC24S4M2tSzpRFTn/TInIxibzoXmzY5UMJE29JNfJX3Ic57+5Cn7RYXL3S07UbsxaASPH1q98Dyb95si5CTijTf/1kvcv2cutRKS1xQfivy5ddbbK63Hf/w94zma/tcoOU9xVLY9raoZW9ve742JHkVv21m/wP5VL+txo88qd92E1bSHdH+pugeiGwaSlM4G57NHymnHV+3Ys1Zy31hyB5rIYe2utTw5M20AS7tGZu6yflkwgwnrypPKrpgYclT5/j7v3GWbeJ4SM5FG338J+T4AY/sPCO72yN7DNnX5fgGx7YXYLyc07GL495yfIqxizr3dBlX9Xz4uKknLr5doveNgRJ2pPsGrSnVreuRWWquV6pp41xokEE7N1Hn7/rJuWHuc06+freIK8n10j1xTeBcaGxeJ/Iv63E4bcke2YXmuvv0uuH9EYfleIUT/s7fo6Tl+YSq7T/gOsftP1gobU7aiM4NahvXtkA7NPfotLqhCE/RiJNxS4J2vk8/vh0yvHrv0db2Rzj/WGK333165Fg5rbFzwrnPE90rvGPn5nqhgMu13C7CDQje/9Kt+Qp+4YZnGcf6DHKGhGkrTwXWcT/d+n1C872/hnJ+gTMJ6SycrTyIw5RbqwT8ZPwZIf1A6lHOJ0jYo7SZZtj07UHdDSWf+UGbvrU6xrkxcYGouJja3vuP9zuxXdUWp7c=
*/