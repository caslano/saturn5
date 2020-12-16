// boost\math\distributions\beta.hpp

// Copyright John Maddock 2006.
// Copyright Paul A. Bristow 2006.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// http://en.wikipedia.org/wiki/Beta_distribution
// http://www.itl.nist.gov/div898/handbook/eda/section3/eda366h.htm
// http://mathworld.wolfram.com/BetaDistribution.html

// The Beta Distribution is a continuous probability distribution.
// The beta distribution is used to model events which are constrained to take place
// within an interval defined by maxima and minima,
// so is used extensively in PERT and other project management systems
// to describe the time to completion.
// The cdf of the beta distribution is used as a convenient way
// of obtaining the sum over a set of binomial outcomes.
// The beta distribution is also used in Bayesian statistics.

#ifndef BOOST_MATH_DIST_BETA_HPP
#define BOOST_MATH_DIST_BETA_HPP

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/beta.hpp> // for beta.
#include <boost/math/distributions/complement.hpp> // complements.
#include <boost/math/distributions/detail/common_error_handling.hpp> // error checks
#include <boost/math/special_functions/fpclassify.hpp> // isnan.
#include <boost/math/tools/roots.hpp> // for root finding.

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning(disable: 4702) // unreachable code
// in domain_error_imp in error_handling
#endif

#include <utility>

namespace boost
{
  namespace math
  {
    namespace beta_detail
    {
      // Common error checking routines for beta distribution functions:
      template <class RealType, class Policy>
      inline bool check_alpha(const char* function, const RealType& alpha, RealType* result, const Policy& pol)
      {
        if(!(boost::math::isfinite)(alpha) || (alpha <= 0))
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "Alpha argument is %1%, but must be > 0 !", alpha, pol);
          return false;
        }
        return true;
      } // bool check_alpha

      template <class RealType, class Policy>
      inline bool check_beta(const char* function, const RealType& beta, RealType* result, const Policy& pol)
      {
        if(!(boost::math::isfinite)(beta) || (beta <= 0))
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "Beta argument is %1%, but must be > 0 !", beta, pol);
          return false;
        }
        return true;
      } // bool check_beta

      template <class RealType, class Policy>
      inline bool check_prob(const char* function, const RealType& p, RealType* result, const Policy& pol)
      {
        if((p < 0) || (p > 1) || !(boost::math::isfinite)(p))
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "Probability argument is %1%, but must be >= 0 and <= 1 !", p, pol);
          return false;
        }
        return true;
      } // bool check_prob

      template <class RealType, class Policy>
      inline bool check_x(const char* function, const RealType& x, RealType* result, const Policy& pol)
      {
        if(!(boost::math::isfinite)(x) || (x < 0) || (x > 1))
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "x argument is %1%, but must be >= 0 and <= 1 !", x, pol);
          return false;
        }
        return true;
      } // bool check_x

      template <class RealType, class Policy>
      inline bool check_dist(const char* function, const RealType& alpha, const RealType& beta, RealType* result, const Policy& pol)
      { // Check both alpha and beta.
        return check_alpha(function, alpha, result, pol)
          && check_beta(function, beta, result, pol);
      } // bool check_dist

      template <class RealType, class Policy>
      inline bool check_dist_and_x(const char* function, const RealType& alpha, const RealType& beta, RealType x, RealType* result, const Policy& pol)
      {
        return check_dist(function, alpha, beta, result, pol)
          && beta_detail::check_x(function, x, result, pol);
      } // bool check_dist_and_x

      template <class RealType, class Policy>
      inline bool check_dist_and_prob(const char* function, const RealType& alpha, const RealType& beta, RealType p, RealType* result, const Policy& pol)
      {
        return check_dist(function, alpha, beta, result, pol)
          && check_prob(function, p, result, pol);
      } // bool check_dist_and_prob

      template <class RealType, class Policy>
      inline bool check_mean(const char* function, const RealType& mean, RealType* result, const Policy& pol)
      {
        if(!(boost::math::isfinite)(mean) || (mean <= 0))
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "mean argument is %1%, but must be > 0 !", mean, pol);
          return false;
        }
        return true;
      } // bool check_mean
      template <class RealType, class Policy>
      inline bool check_variance(const char* function, const RealType& variance, RealType* result, const Policy& pol)
      {
        if(!(boost::math::isfinite)(variance) || (variance <= 0))
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "variance argument is %1%, but must be > 0 !", variance, pol);
          return false;
        }
        return true;
      } // bool check_variance
    } // namespace beta_detail

    // typedef beta_distribution<double> beta;
    // is deliberately NOT included to avoid a name clash with the beta function.
    // Use beta_distribution<> mybeta(...) to construct type double.

    template <class RealType = double, class Policy = policies::policy<> >
    class beta_distribution
    {
    public:
      typedef RealType value_type;
      typedef Policy policy_type;

      beta_distribution(RealType l_alpha = 1, RealType l_beta = 1) : m_alpha(l_alpha), m_beta(l_beta)
      {
        RealType result;
        beta_detail::check_dist(
           "boost::math::beta_distribution<%1%>::beta_distribution",
          m_alpha,
          m_beta,
          &result, Policy());
      } // beta_distribution constructor.
      // Accessor functions:
      RealType alpha() const
      {
        return m_alpha;
      }
      RealType beta() const
      { // .
        return m_beta;
      }

      // Estimation of the alpha & beta parameters.
      // http://en.wikipedia.org/wiki/Beta_distribution
      // gives formulae in section on parameter estimation.
      // Also NIST EDA page 3 & 4 give the same.
      // http://www.itl.nist.gov/div898/handbook/eda/section3/eda366h.htm
      // http://www.epi.ucdavis.edu/diagnostictests/betabuster.html

      static RealType find_alpha(
        RealType mean, // Expected value of mean.
        RealType variance) // Expected value of variance.
      {
        static const char* function = "boost::math::beta_distribution<%1%>::find_alpha";
        RealType result = 0; // of error checks.
        if(false ==
            (
              beta_detail::check_mean(function, mean, &result, Policy())
              && beta_detail::check_variance(function, variance, &result, Policy())
            )
          )
        {
          return result;
        }
        return mean * (( (mean * (1 - mean)) / variance)- 1);
      } // RealType find_alpha

      static RealType find_beta(
        RealType mean, // Expected value of mean.
        RealType variance) // Expected value of variance.
      {
        static const char* function = "boost::math::beta_distribution<%1%>::find_beta";
        RealType result = 0; // of error checks.
        if(false ==
            (
              beta_detail::check_mean(function, mean, &result, Policy())
              &&
              beta_detail::check_variance(function, variance, &result, Policy())
            )
          )
        {
          return result;
        }
        return (1 - mean) * (((mean * (1 - mean)) /variance)-1);
      } //  RealType find_beta

      // Estimate alpha & beta from either alpha or beta, and x and probability.
      // Uses for these parameter estimators are unclear.

      static RealType find_alpha(
        RealType beta, // from beta.
        RealType x, //  x.
        RealType probability) // cdf
      {
        static const char* function = "boost::math::beta_distribution<%1%>::find_alpha";
        RealType result = 0; // of error checks.
        if(false ==
            (
             beta_detail::check_prob(function, probability, &result, Policy())
             &&
             beta_detail::check_beta(function, beta, &result, Policy())
             &&
             beta_detail::check_x(function, x, &result, Policy())
            )
          )
        {
          return result;
        }
        return ibeta_inva(beta, x, probability, Policy());
      } // RealType find_alpha(beta, a, probability)

      static RealType find_beta(
        // ibeta_invb(T b, T x, T p); (alpha, x, cdf,)
        RealType alpha, // alpha.
        RealType x, // probability x.
        RealType probability) // probability cdf.
      {
        static const char* function = "boost::math::beta_distribution<%1%>::find_beta";
        RealType result = 0; // of error checks.
        if(false ==
            (
              beta_detail::check_prob(function, probability, &result, Policy())
              &&
              beta_detail::check_alpha(function, alpha, &result, Policy())
              &&
              beta_detail::check_x(function, x, &result, Policy())
            )
          )
        {
          return result;
        }
        return ibeta_invb(alpha, x, probability, Policy());
      } //  RealType find_beta(alpha, x, probability)

    private:
      RealType m_alpha; // Two parameters of the beta distribution.
      RealType m_beta;
    }; // template <class RealType, class Policy> class beta_distribution

    template <class RealType, class Policy>
    inline const std::pair<RealType, RealType> range(const beta_distribution<RealType, Policy>& /* dist */)
    { // Range of permissible values for random variable x.
      using boost::math::tools::max_value;
      return std::pair<RealType, RealType>(static_cast<RealType>(0), static_cast<RealType>(1));
    }

    template <class RealType, class Policy>
    inline const std::pair<RealType, RealType> support(const beta_distribution<RealType, Policy>&  /* dist */)
    { // Range of supported values for random variable x.
      // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
      return std::pair<RealType, RealType>(static_cast<RealType>(0), static_cast<RealType>(1));
    }

    template <class RealType, class Policy>
    inline RealType mean(const beta_distribution<RealType, Policy>& dist)
    { // Mean of beta distribution = np.
      return  dist.alpha() / (dist.alpha() + dist.beta());
    } // mean

    template <class RealType, class Policy>
    inline RealType variance(const beta_distribution<RealType, Policy>& dist)
    { // Variance of beta distribution = np(1-p).
      RealType a = dist.alpha();
      RealType b = dist.beta();
      return  (a * b) / ((a + b ) * (a + b) * (a + b + 1));
    } // variance

    template <class RealType, class Policy>
    inline RealType mode(const beta_distribution<RealType, Policy>& dist)
    {
      static const char* function = "boost::math::mode(beta_distribution<%1%> const&)";

      RealType result;
      if ((dist.alpha() <= 1))
      {
        result = policies::raise_domain_error<RealType>(
          function,
          "mode undefined for alpha = %1%, must be > 1!", dist.alpha(), Policy());
        return result;
      }

      if ((dist.beta() <= 1))
      {
        result = policies::raise_domain_error<RealType>(
          function,
          "mode undefined for beta = %1%, must be > 1!", dist.beta(), Policy());
        return result;
      }
      RealType a = dist.alpha();
      RealType b = dist.beta();
      return (a-1) / (a + b - 2);
    } // mode

    //template <class RealType, class Policy>
    //inline RealType median(const beta_distribution<RealType, Policy>& dist)
    //{ // Median of beta distribution is not defined.
    //  return tools::domain_error<RealType>(function, "Median is not implemented, result is %1%!", std::numeric_limits<RealType>::quiet_NaN());
    //} // median

    //But WILL be provided by the derived accessor as quantile(0.5).

    template <class RealType, class Policy>
    inline RealType skewness(const beta_distribution<RealType, Policy>& dist)
    {
      BOOST_MATH_STD_USING // ADL of std functions.
      RealType a = dist.alpha();
      RealType b = dist.beta();
      return (2 * (b-a) * sqrt(a + b + 1)) / ((a + b + 2) * sqrt(a * b));
    } // skewness

    template <class RealType, class Policy>
    inline RealType kurtosis_excess(const beta_distribution<RealType, Policy>& dist)
    {
      RealType a = dist.alpha();
      RealType b = dist.beta();
      RealType a_2 = a * a;
      RealType n = 6 * (a_2 * a - a_2 * (2 * b - 1) + b * b * (b + 1) - 2 * a * b * (b + 2));
      RealType d = a * b * (a + b + 2) * (a + b + 3);
      return  n / d;
    } // kurtosis_excess

    template <class RealType, class Policy>
    inline RealType kurtosis(const beta_distribution<RealType, Policy>& dist)
    {
      return 3 + kurtosis_excess(dist);
    } // kurtosis

    template <class RealType, class Policy>
    inline RealType pdf(const beta_distribution<RealType, Policy>& dist, const RealType& x)
    { // Probability Density/Mass Function.
      BOOST_FPU_EXCEPTION_GUARD

      static const char* function = "boost::math::pdf(beta_distribution<%1%> const&, %1%)";

      BOOST_MATH_STD_USING // for ADL of std functions

      RealType a = dist.alpha();
      RealType b = dist.beta();

      // Argument checks:
      RealType result = 0;
      if(false == beta_detail::check_dist_and_x(
        function,
        a, b, x,
        &result, Policy()))
      {
        return result;
      }
      using boost::math::beta;
      return ibeta_derivative(a, b, x, Policy());
    } // pdf

    template <class RealType, class Policy>
    inline RealType cdf(const beta_distribution<RealType, Policy>& dist, const RealType& x)
    { // Cumulative Distribution Function beta.
      BOOST_MATH_STD_USING // for ADL of std functions

      static const char* function = "boost::math::cdf(beta_distribution<%1%> const&, %1%)";

      RealType a = dist.alpha();
      RealType b = dist.beta();

      // Argument checks:
      RealType result = 0;
      if(false == beta_detail::check_dist_and_x(
        function,
        a, b, x,
        &result, Policy()))
      {
        return result;
      }
      // Special cases:
      if (x == 0)
      {
        return 0;
      }
      else if (x == 1)
      {
        return 1;
      }
      return ibeta(a, b, x, Policy());
    } // beta cdf

    template <class RealType, class Policy>
    inline RealType cdf(const complemented2_type<beta_distribution<RealType, Policy>, RealType>& c)
    { // Complemented Cumulative Distribution Function beta.

      BOOST_MATH_STD_USING // for ADL of std functions

      static const char* function = "boost::math::cdf(beta_distribution<%1%> const&, %1%)";

      RealType const& x = c.param;
      beta_distribution<RealType, Policy> const& dist = c.dist;
      RealType a = dist.alpha();
      RealType b = dist.beta();

      // Argument checks:
      RealType result = 0;
      if(false == beta_detail::check_dist_and_x(
        function,
        a, b, x,
        &result, Policy()))
      {
        return result;
      }
      if (x == 0)
      {
        return 1;
      }
      else if (x == 1)
      {
        return 0;
      }
      // Calculate cdf beta using the incomplete beta function.
      // Use of ibeta here prevents cancellation errors in calculating
      // 1 - x if x is very small, perhaps smaller than machine epsilon.
      return ibetac(a, b, x, Policy());
    } // beta cdf

    template <class RealType, class Policy>
    inline RealType quantile(const beta_distribution<RealType, Policy>& dist, const RealType& p)
    { // Quantile or Percent Point beta function or
      // Inverse Cumulative probability distribution function CDF.
      // Return x (0 <= x <= 1),
      // for a given probability p (0 <= p <= 1).
      // These functions take a probability as an argument
      // and return a value such that the probability that a random variable x
      // will be less than or equal to that value
      // is whatever probability you supplied as an argument.

      static const char* function = "boost::math::quantile(beta_distribution<%1%> const&, %1%)";

      RealType result = 0; // of argument checks:
      RealType a = dist.alpha();
      RealType b = dist.beta();
      if(false == beta_detail::check_dist_and_prob(
        function,
        a, b, p,
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
      return ibeta_inv(a, b, p, static_cast<RealType*>(0), Policy());
    } // quantile

    template <class RealType, class Policy>
    inline RealType quantile(const complemented2_type<beta_distribution<RealType, Policy>, RealType>& c)
    { // Complement Quantile or Percent Point beta function .
      // Return the number of expected x for a given
      // complement of the probability q.

      static const char* function = "boost::math::quantile(beta_distribution<%1%> const&, %1%)";

      //
      // Error checks:
      RealType q = c.param;
      const beta_distribution<RealType, Policy>& dist = c.dist;
      RealType result = 0;
      RealType a = dist.alpha();
      RealType b = dist.beta();
      if(false == beta_detail::check_dist_and_prob(
        function,
        a,
        b,
        q,
        &result, Policy()))
      {
        return result;
      }
      // Special cases:
      if(q == 1)
      {
        return 0;
      }
      if(q == 0)
      {
        return 1;
      }

      return ibetac_inv(a, b, q, static_cast<RealType*>(0), Policy());
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

#endif // BOOST_MATH_DIST_BETA_HPP



/* beta.hpp
Hc/F0gYutbWQQjcnpHWkLVboK1ivKN3w2+lS7xbu1j7fLTjetHaZsY0ha1wP2NieRFb/ziz043fb887ibq3q2++1SOz1VBCm7SPYkCFkJtMPVtTT9G5Zxnqq8R2sxHbt/2iidT/m3wbHtZfU4topg9e1cy6PzkRdZxdZp+F4eNX3mnNoFKWH1HWq3odFSW3PDu/dhZnFtFbT9clxbse61ubrE1nHGsvGdoCss6/InpdZOM3Yr9hlqQc2rsLWfx1S+4N1vT4TUXO9RnuvXajrQNWvYc3GcMNajBH6GVZl1+P0a8/COH1t12Ywj+vXftw98js36ef8kP/K4MVP3Pnotmtzbp857I6fftz9TI2vm8fvfekr/rfH4+M935DSb+4naB+CMk/TIxcvcnUNcu1sckki16ia/JL09wb9lMgFW/sNa1Wca1uTIle/t7JPjmtAmOjRYcpxF8GGYsPXFF4s+oRksfW7RMbRLxN9Ql84GPaDQ2F/XU55N4ShhnIOlvNdDuvBFFs5y+W4CYZydpTjOkk5z4NxMr7fBl4I42W+68UwSWz3usI00UOMV3JS757fVdiihvtYInLR1cilSp9rvz/1CANFromUv5lcd7RcR4zUd6zoLVrI/WsJN9nm367JCnNtJVSnt1B+HuOCGf8k/oLyn1jt3NxNor/w+LPc+sKZnae7/4X/7rm6odRnHAH9gfjZ9LZr7L7JPHcXH5xGW0fz3F32bTr1+bvJr/uew1tQzjmstE1aJ2D364k+ABno1AmUIu/RCxzZdGpze09uqn5+b8SLP+0c39rO70190b85vuU8g7HZ+B4l5BJWETYS9hOOE+Jz8DuaExjTD2yBLbAFtsAW2AJbYAts1W8hhPyfWv/fI71IxZUFwOn5AGiHfvpJPlI3IR3kShswanzq6PTUfqP6DUvzaPWVTv81m04/VPRRS4P4/ocFMDuZb/V9WtfTI71gSnY3ciiWoiKmxl37KJ3N1OkFuZzcNuf3KnXsyKDQoAjTWCx5O3W/RZl5xRVz1o8wX7xQ7R8c5BkXHaLi5xvHasnLrkORvHyO2yPv1NdkogqpOPdWzr1I7e+lzz2XuFlvKXnJ3OX2al3R4Wp/zzn9XGXkdbva3zGoIs3tOkza8oprIW0A+VdsN6u0EJeVFiV1NEyl9TfonEznLdTn3cM50tX+8fq8B0m7S6Wdo87bRM47Us5hpTWV845VafUN+ifTeQv0eXdwjuvU/kv0eUtJy1VpqUFyDrVNVWl1vM6br9IaqvMm2M6b4LhnPVWlFWYX29YZv1rt7xd03B2pZJpahZW12D1z2W9QMp2CPnI3ttnOo/RNR7cv93875f1ayb3htvIp6mLJWI2/cu7E9XL/Druj1LmWqtF5mpC0t6Pk4ZlTr8b3raYo+e9n3z3q+LZBUfpaiqbmZmNFL2VVY/rvWTIPURvLVVoUaR1UWhvqPkTb9Rftt9JiVd5byLu1krnPneOaoMr6OpU3kz+2wkIy2cGNv524Fd7kQW3RHPNY/l5JaMnft8ETVPofEpCNkWPoT94gvhOWRCgio+SVbqKvcV4MN1aNFfZR/h+aqXtXJ1KVlyLhnEHFb6uIE63UY/RRukjpU5xz9dWz7dBR6ufd6a9BnmvRUbZXssNVPE7HC1U8QeKyLru6h9xX4mTh0L91Fz1lMP1kW/gFF3AR+vuM92395dxu0lOm0wCmz51G6Tzt0i3t0uMb9OfquA9MvlXJ0zHfBBuDoqKKtrTB6l/U/j1uT181X8VbmXWb7HPomsnLRz/pOHdKZIV8IRN7PLYjS9X+YlO/qI9tUPkbYezH7OeYqnRyM7NINurKtawuf3Z+ela2sZ+yy04=
*/