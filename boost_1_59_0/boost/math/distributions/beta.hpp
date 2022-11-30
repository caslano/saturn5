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

    #ifdef __cpp_deduction_guides
    template <class RealType>
    beta_distribution(RealType)->beta_distribution<typename boost::math::tools::promote_args<RealType>::type>;
    template <class RealType>
    beta_distribution(RealType, RealType)->beta_distribution<typename boost::math::tools::promote_args<RealType>::type>;
    #endif

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

      // Corner case: check_x ensures x element of [0, 1], but PDF is 0 for x = 0 and x = 1. PDF EQN:
      // https://wikimedia.org/api/rest_v1/media/math/render/svg/125fdaa41844a8703d1a8610ac00fbf3edacc8e7
      if(x == 0 || x == 1)
      {
        return RealType(0);
      }
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