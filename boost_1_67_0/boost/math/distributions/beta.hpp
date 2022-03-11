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
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
*/