// boost/math/distributions/arcsine.hpp

// Copyright John Maddock 2014.
// Copyright Paul A. Bristow 2014.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// http://en.wikipedia.org/wiki/arcsine_distribution

// The arcsine Distribution is a continuous probability distribution.
// http://en.wikipedia.org/wiki/Arcsine_distribution
// http://www.wolframalpha.com/input/?i=ArcSinDistribution

// Standard arcsine distribution is a special case of beta distribution with both a & b = one half,
// and 0 <= x <= 1.

// It is generalized to include any bounded support a <= x <= b from 0 <= x <= 1
// by Wolfram and Wikipedia,
// but using location and scale parameters by
// Virtual Laboratories in Probability and Statistics http://www.math.uah.edu/stat/index.html
// http://www.math.uah.edu/stat/special/Arcsine.html
// The end-point version is simpler and more obvious, so we implement that.
// TODO Perhaps provide location and scale functions?


#ifndef BOOST_MATH_DIST_ARCSINE_HPP
#define BOOST_MATH_DIST_ARCSINE_HPP

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/distributions/complement.hpp> // complements.
#include <boost/math/distributions/detail/common_error_handling.hpp> // error checks.
#include <boost/math/constants/constants.hpp>

#include <boost/math/special_functions/fpclassify.hpp> // isnan.

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning(disable: 4702) // Unreachable code,
// in domain_error_imp in error_handling.
#endif

#include <utility>
#include <exception>  // For std::domain_error.

namespace boost
{
  namespace math
  {
    namespace arcsine_detail
    {
      // Common error checking routines for arcsine distribution functions:
      // Duplicating for x_min and x_max provides specific error messages.
      template <class RealType, class Policy>
      inline bool check_x_min(const char* function, const RealType& x, RealType* result, const Policy& pol)
      {
        if (!(boost::math::isfinite)(x))
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "x_min argument is %1%, but must be finite !", x, pol);
          return false;
        }
        return true;
      } // bool check_x_min

      template <class RealType, class Policy>
      inline bool check_x_max(const char* function, const RealType& x, RealType* result, const Policy& pol)
      {
        if (!(boost::math::isfinite)(x))
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "x_max argument is %1%, but must be finite !", x, pol);
          return false;
        }
        return true;
      } // bool check_x_max


      template <class RealType, class Policy>
      inline bool check_x_minmax(const char* function, const RealType& x_min, const RealType& x_max, RealType* result, const Policy& pol)
      { // Check x_min < x_max
        if (x_min >= x_max)
        {
          std::string msg = "x_max argument is %1%, but must be > x_min = " + lexical_cast<std::string>(x_min) + "!";
          *result = policies::raise_domain_error<RealType>(
            function,
            msg.c_str(), x_max, pol);
           // "x_max argument is %1%, but must be > x_min !", x_max, pol);
            //  "x_max argument is %1%, but must be > x_min %2!", x_max, x_min, pol); would be better. 
          // But would require replication of all helpers functions in /policies/error_handling.hpp for two values,
          // as well as two value versions of raise_error, raise_domain_error and do_format ...
          // so use slightly hacky lexical_cast to string instead.
          return false;
        }
        return true;
      } // bool check_x_minmax

      template <class RealType, class Policy>
      inline bool check_prob(const char* function, const RealType& p, RealType* result, const Policy& pol)
      {
        if ((p < 0) || (p > 1) || !(boost::math::isfinite)(p))
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "Probability argument is %1%, but must be >= 0 and <= 1 !", p, pol);
          return false;
        }
        return true;
      } // bool check_prob

      template <class RealType, class Policy>
      inline bool check_x(const char* function, const RealType& x_min, const RealType& x_max, const RealType& x, RealType* result, const Policy& pol)
      { // Check x finite and x_min < x < x_max.
        if (!(boost::math::isfinite)(x))
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "x argument is %1%, but must be finite !", x, pol);
          return false;
        }
        if ((x < x_min) || (x > x_max))
        {
          // std::cout << x_min << ' ' << x << x_max << std::endl;
          *result = policies::raise_domain_error<RealType>(
            function,
            "x argument is %1%, but must be x_min < x < x_max !", x, pol);
          // For example:
          // Error in function boost::math::pdf(arcsine_distribution<double> const&, double) : x argument is -1.01, but must be x_min < x < x_max !
          // TODO Perhaps show values of x_min and x_max?
          return false;
        }
        return true;
      } // bool check_x

      template <class RealType, class Policy>
      inline bool check_dist(const char* function, const RealType& x_min, const RealType& x_max, RealType* result, const Policy& pol)
      { // Check both x_min and x_max finite, and x_min  < x_max.
        return check_x_min(function, x_min, result, pol)
            && check_x_max(function, x_max, result, pol)
            && check_x_minmax(function, x_min, x_max, result, pol);
      } // bool check_dist

      template <class RealType, class Policy>
      inline bool check_dist_and_x(const char* function, const RealType& x_min, const RealType& x_max, RealType x, RealType* result, const Policy& pol)
      {
        return check_dist(function, x_min, x_max, result, pol)
          && arcsine_detail::check_x(function, x_min, x_max, x, result, pol);
      } // bool check_dist_and_x

      template <class RealType, class Policy>
      inline bool check_dist_and_prob(const char* function, const RealType& x_min, const RealType& x_max, RealType p, RealType* result, const Policy& pol)
      {
        return check_dist(function, x_min, x_max, result, pol)
          && check_prob(function, p, result, pol);
      } // bool check_dist_and_prob

    } // namespace arcsine_detail

    template <class RealType = double, class Policy = policies::policy<> >
    class arcsine_distribution
    {
    public:
      typedef RealType value_type;
      typedef Policy policy_type;

      arcsine_distribution(RealType x_min = 0, RealType x_max = 1) : m_x_min(x_min), m_x_max(x_max)
      { // Default beta (alpha = beta = 0.5) is standard arcsine with x_min = 0, x_max = 1.
        // Generalized to allow x_min and x_max to be specified.
        RealType result;
        arcsine_detail::check_dist(
          "boost::math::arcsine_distribution<%1%>::arcsine_distribution",
          m_x_min,
          m_x_max,
          &result, Policy());
      } // arcsine_distribution constructor.
      // Accessor functions:
      RealType x_min() const
      {
        return m_x_min;
      }
      RealType x_max() const
      {
        return m_x_max;
      }

    private:
      RealType m_x_min; // Two x min and x max parameters of the arcsine distribution.
      RealType m_x_max;
    }; // template <class RealType, class Policy> class arcsine_distribution

    // Convenient typedef to construct double version.
    typedef arcsine_distribution<double> arcsine;


    template <class RealType, class Policy>
    inline const std::pair<RealType, RealType> range(const arcsine_distribution<RealType, Policy>&  dist)
    { // Range of permissible values for random variable x.
      using boost::math::tools::max_value;
      return std::pair<RealType, RealType>(static_cast<RealType>(dist.x_min()), static_cast<RealType>(dist.x_max()));
    }

    template <class RealType, class Policy>
    inline const std::pair<RealType, RealType> support(const arcsine_distribution<RealType, Policy>&  dist)
    { // Range of supported values for random variable x.
      // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
      return std::pair<RealType, RealType>(static_cast<RealType>(dist.x_min()), static_cast<RealType>(dist.x_max()));
    }

    template <class RealType, class Policy>
    inline RealType mean(const arcsine_distribution<RealType, Policy>& dist)
    { // Mean of arcsine distribution .
      RealType result;
      RealType x_min = dist.x_min();
      RealType x_max = dist.x_max();

      if (false == arcsine_detail::check_dist(
        "boost::math::mean(arcsine_distribution<%1%> const&, %1% )",
        x_min,
        x_max,
        &result, Policy())
        )
      {
        return result;
      }
      return  (x_min + x_max) / 2;
    } // mean

    template <class RealType, class Policy>
    inline RealType variance(const arcsine_distribution<RealType, Policy>& dist)
    { // Variance of standard arcsine distribution = (1-0)/8 = 0.125.
      RealType result;
      RealType x_min = dist.x_min();
      RealType x_max = dist.x_max();
      if (false == arcsine_detail::check_dist(
        "boost::math::variance(arcsine_distribution<%1%> const&, %1% )",
        x_min,
        x_max,
        &result, Policy())
        )
      {
        return result;
      }
      return  (x_max - x_min) * (x_max - x_min) / 8;
    } // variance

    template <class RealType, class Policy>
    inline RealType mode(const arcsine_distribution<RealType, Policy>& /* dist */)
    { //There are always [*two] values for the mode, at ['x_min] and at ['x_max], default 0 and 1,
      // so instead we raise the exception domain_error.
      return policies::raise_domain_error<RealType>(
        "boost::math::mode(arcsine_distribution<%1%>&)",
        "The arcsine distribution has two modes at x_min and x_max: "
        "so the return value is %1%.",
        std::numeric_limits<RealType>::quiet_NaN(), Policy());
    } // mode

    template <class RealType, class Policy>
    inline RealType median(const arcsine_distribution<RealType, Policy>& dist)
    { // Median of arcsine distribution (a + b) / 2 == mean.
      RealType x_min = dist.x_min();
      RealType x_max = dist.x_max();
      RealType result;
      if (false == arcsine_detail::check_dist(
        "boost::math::median(arcsine_distribution<%1%> const&, %1% )",
        x_min,
        x_max,
        &result, Policy())
        )
      {
        return result;
      }
      return  (x_min + x_max) / 2;
    }

    template <class RealType, class Policy>
    inline RealType skewness(const arcsine_distribution<RealType, Policy>& dist)
    {
      RealType result;
      RealType x_min = dist.x_min();
      RealType x_max = dist.x_max();

      if (false == arcsine_detail::check_dist(
        "boost::math::skewness(arcsine_distribution<%1%> const&, %1% )",
        x_min,
        x_max,
        &result, Policy())
        )
      {
        return result;
      }
      return 0;
    } // skewness

    template <class RealType, class Policy>
    inline RealType kurtosis_excess(const arcsine_distribution<RealType, Policy>& dist)
    {
      RealType result;
      RealType x_min = dist.x_min();
      RealType x_max = dist.x_max();

      if (false == arcsine_detail::check_dist(
        "boost::math::kurtosis_excess(arcsine_distribution<%1%> const&, %1% )",
        x_min,
        x_max,
        &result, Policy())
        )
      {
        return result;
      }
      result = -3;
      return  result / 2;
    } // kurtosis_excess

    template <class RealType, class Policy>
    inline RealType kurtosis(const arcsine_distribution<RealType, Policy>& dist)
    {
      RealType result;
      RealType x_min = dist.x_min();
      RealType x_max = dist.x_max();

      if (false == arcsine_detail::check_dist(
        "boost::math::kurtosis(arcsine_distribution<%1%> const&, %1% )",
        x_min,
        x_max,
        &result, Policy())
        )
      {
        return result;
      }

      return 3 + kurtosis_excess(dist);
    } // kurtosis

    template <class RealType, class Policy>
    inline RealType pdf(const arcsine_distribution<RealType, Policy>& dist, const RealType& xx)
    { // Probability Density/Mass Function arcsine.
      BOOST_FPU_EXCEPTION_GUARD
      BOOST_MATH_STD_USING // For ADL of std functions.

      static const char* function = "boost::math::pdf(arcsine_distribution<%1%> const&, %1%)";

      RealType lo = dist.x_min();
      RealType hi = dist.x_max();
      RealType x = xx;

      // Argument checks:
      RealType result = 0; 
      if (false == arcsine_detail::check_dist_and_x(
        function,
        lo, hi, x,
        &result, Policy()))
      {
        return result;
      }
      using boost::math::constants::pi;
      result = static_cast<RealType>(1) / (pi<RealType>() * sqrt((x - lo) * (hi - x)));
      return result;
    } // pdf

    template <class RealType, class Policy>
    inline RealType cdf(const arcsine_distribution<RealType, Policy>& dist, const RealType& x)
    { // Cumulative Distribution Function arcsine.
      BOOST_MATH_STD_USING // For ADL of std functions.

      static const char* function = "boost::math::cdf(arcsine_distribution<%1%> const&, %1%)";

      RealType x_min = dist.x_min();
      RealType x_max = dist.x_max();

      // Argument checks:
      RealType result = 0;
      if (false == arcsine_detail::check_dist_and_x(
        function,
        x_min, x_max, x,
        &result, Policy()))
      {
        return result;
      }
      // Special cases:
      if (x == x_min)
      {
        return 0;
      }
      else if (x == x_max)
      {
        return 1;
      }
      using boost::math::constants::pi;
      result = static_cast<RealType>(2) * asin(sqrt((x - x_min) / (x_max - x_min))) / pi<RealType>();
      return result;
    } // arcsine cdf

    template <class RealType, class Policy>
    inline RealType cdf(const complemented2_type<arcsine_distribution<RealType, Policy>, RealType>& c)
    { // Complemented Cumulative Distribution Function arcsine.
      BOOST_MATH_STD_USING // For ADL of std functions.
      static const char* function = "boost::math::cdf(arcsine_distribution<%1%> const&, %1%)";

      RealType x = c.param;
      arcsine_distribution<RealType, Policy> const& dist = c.dist;
      RealType x_min = dist.x_min();
      RealType x_max = dist.x_max();

      // Argument checks:
      RealType result = 0;
      if (false == arcsine_detail::check_dist_and_x(
        function,
        x_min, x_max, x,
        &result, Policy()))
      {
        return result;
      }
      if (x == x_min)
      {
        return 0;
      }
      else if (x == x_max)
      {
        return 1;
      }
      using boost::math::constants::pi;
      // Naive version x = 1 - x;
      // result = static_cast<RealType>(2) * asin(sqrt((x - x_min) / (x_max - x_min))) / pi<RealType>();
      // is less accurate, so use acos instead of asin for complement.
      result = static_cast<RealType>(2) * acos(sqrt((x - x_min) / (x_max - x_min))) / pi<RealType>();
      return result;
    } // arcsine ccdf

    template <class RealType, class Policy>
    inline RealType quantile(const arcsine_distribution<RealType, Policy>& dist, const RealType& p)
    { 
      // Quantile or Percent Point arcsine function or
      // Inverse Cumulative probability distribution function CDF.
      // Return x (0 <= x <= 1),
      // for a given probability p (0 <= p <= 1).
      // These functions take a probability as an argument
      // and return a value such that the probability that a random variable x
      // will be less than or equal to that value
      // is whatever probability you supplied as an argument.
      BOOST_MATH_STD_USING // For ADL of std functions.

      using boost::math::constants::half_pi;

      static const char* function = "boost::math::quantile(arcsine_distribution<%1%> const&, %1%)";

      RealType result = 0; // of argument checks:
      RealType x_min = dist.x_min();
      RealType x_max = dist.x_max();
      if (false == arcsine_detail::check_dist_and_prob(
        function,
        x_min, x_max, p,
        &result, Policy()))
      {
        return result;
      }
      // Special cases:
      if (p == 0)
      {
        return 0;
      }
      if (p == 1)
      {
        return 1;
      }

      RealType sin2hpip = sin(half_pi<RealType>() * p);
      RealType sin2hpip2 = sin2hpip * sin2hpip;
      result = -x_min * sin2hpip2 + x_min + x_max * sin2hpip2;

      return result;
    } // quantile

    template <class RealType, class Policy>
    inline RealType quantile(const complemented2_type<arcsine_distribution<RealType, Policy>, RealType>& c)
    { 
      // Complement Quantile or Percent Point arcsine function.
      // Return the number of expected x for a given
      // complement of the probability q.
      BOOST_MATH_STD_USING // For ADL of std functions.

      using boost::math::constants::half_pi;
      static const char* function = "boost::math::quantile(arcsine_distribution<%1%> const&, %1%)";

      // Error checks:
      RealType q = c.param;
      const arcsine_distribution<RealType, Policy>& dist = c.dist;
      RealType result = 0;
      RealType x_min = dist.x_min();
      RealType x_max = dist.x_max();
      if (false == arcsine_detail::check_dist_and_prob(
        function,
        x_min,
        x_max,
        q,
        &result, Policy()))
      {
        return result;
      }
      // Special cases:
      if (q == 1)
      {
        return 0;
      }
      if (q == 0)
      {
        return 1;
      }
      // Naive RealType p = 1 - q; result = sin(half_pi<RealType>() * p); loses accuracy, so use a cos alternative instead.
      //result = cos(half_pi<RealType>() * q); // for arcsine(0,1)
      //result = result * result;
      // For generalized arcsine:
      RealType cos2hpip = cos(half_pi<RealType>() * q);
      RealType cos2hpip2 = cos2hpip * cos2hpip;
      result = -x_min * cos2hpip2 + x_min + x_max * cos2hpip2;

      return result;
    } // Quantile Complement

  } // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#if defined (BOOST_MSVC)
# pragma warning(pop)
#endif

#endif // BOOST_MATH_DIST_ARCSINE_HPP

/* arcsine.hpp
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
*/