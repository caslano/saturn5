// boost\math\distributions\bernoulli.hpp

// Copyright John Maddock 2006.
// Copyright Paul A. Bristow 2007.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// http://en.wikipedia.org/wiki/bernoulli_distribution
// http://mathworld.wolfram.com/BernoulliDistribution.html

// bernoulli distribution is the discrete probability distribution of
// the number (k) of successes, in a single Bernoulli trials.
// It is a version of the binomial distribution when n = 1.

// But note that the bernoulli distribution
// (like others including the poisson, binomial & negative binomial)
// is strictly defined as a discrete function: only integral values of k are envisaged.
// However because of the method of calculation using a continuous gamma function,
// it is convenient to treat it as if a continuous function,
// and permit non-integral values of k.
// To enforce the strict mathematical model, users should use floor or ceil functions
// on k outside this function to ensure that k is integral.

#ifndef BOOST_MATH_SPECIAL_BERNOULLI_HPP
#define BOOST_MATH_SPECIAL_BERNOULLI_HPP

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/distributions/complement.hpp> // complements
#include <boost/math/distributions/detail/common_error_handling.hpp> // error checks
#include <boost/math/special_functions/fpclassify.hpp> // isnan.

#include <utility>

namespace boost
{
  namespace math
  {
    namespace bernoulli_detail
    {
      // Common error checking routines for bernoulli distribution functions:
      template <class RealType, class Policy>
      inline bool check_success_fraction(const char* function, const RealType& p, RealType* result, const Policy& /* pol */)
      {
        if(!(boost::math::isfinite)(p) || (p < 0) || (p > 1))
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "Success fraction argument is %1%, but must be >= 0 and <= 1 !", p, Policy());
          return false;
        }
        return true;
      }
      template <class RealType, class Policy>
      inline bool check_dist(const char* function, const RealType& p, RealType* result, const Policy& /* pol */, const boost::true_type&)
      {
        return check_success_fraction(function, p, result, Policy());
      }
      template <class RealType, class Policy>
      inline bool check_dist(const char* , const RealType& , RealType* , const Policy& /* pol */, const boost::false_type&)
      {
         return true;
      }
      template <class RealType, class Policy>
      inline bool check_dist(const char* function, const RealType& p, RealType* result, const Policy& /* pol */)
      {
         return check_dist(function, p, result, Policy(), typename policies::constructor_error_check<Policy>::type());
      }

      template <class RealType, class Policy>
      inline bool check_dist_and_k(const char* function, const RealType& p, RealType k, RealType* result, const Policy& pol)
      {
        if(check_dist(function, p, result, Policy(), typename policies::method_error_check<Policy>::type()) == false)
        {
          return false;
        }
        if(!(boost::math::isfinite)(k) || !((k == 0) || (k == 1)))
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "Number of successes argument is %1%, but must be 0 or 1 !", k, pol);
          return false;
        }
       return true;
      }
      template <class RealType, class Policy>
      inline bool check_dist_and_prob(const char* function, RealType p, RealType prob, RealType* result, const Policy& /* pol */)
      {
        if((check_dist(function, p, result, Policy(), typename policies::method_error_check<Policy>::type()) && detail::check_probability(function, prob, result, Policy())) == false)
        {
          return false;
        }
        return true;
      }
    } // namespace bernoulli_detail


    template <class RealType = double, class Policy = policies::policy<> >
    class bernoulli_distribution
    {
    public:
      typedef RealType value_type;
      typedef Policy policy_type;

      bernoulli_distribution(RealType p = 0.5) : m_p(p)
      { // Default probability = half suits 'fair' coin tossing
        // where probability of heads == probability of tails.
        RealType result; // of checks.
        bernoulli_detail::check_dist(
           "boost::math::bernoulli_distribution<%1%>::bernoulli_distribution",
          m_p,
          &result, Policy());
      } // bernoulli_distribution constructor.

      RealType success_fraction() const
      { // Probability.
        return m_p;
      }

    private:
      RealType m_p; // success_fraction
    }; // template <class RealType> class bernoulli_distribution

    typedef bernoulli_distribution<double> bernoulli;

    template <class RealType, class Policy>
    inline const std::pair<RealType, RealType> range(const bernoulli_distribution<RealType, Policy>& /* dist */)
    { // Range of permissible values for random variable k = {0, 1}.
      using boost::math::tools::max_value;
      return std::pair<RealType, RealType>(static_cast<RealType>(0), static_cast<RealType>(1));
    }

    template <class RealType, class Policy>
    inline const std::pair<RealType, RealType> support(const bernoulli_distribution<RealType, Policy>& /* dist */)
    { // Range of supported values for random variable k = {0, 1}.
      // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
      return std::pair<RealType, RealType>(static_cast<RealType>(0), static_cast<RealType>(1));
    }

    template <class RealType, class Policy>
    inline RealType mean(const bernoulli_distribution<RealType, Policy>& dist)
    { // Mean of bernoulli distribution = p (n = 1).
      return dist.success_fraction();
    } // mean

    // Rely on dereived_accessors quantile(half)
    //template <class RealType>
    //inline RealType median(const bernoulli_distribution<RealType, Policy>& dist)
    //{ // Median of bernoulli distribution is not defined.
    //  return tools::domain_error<RealType>(BOOST_CURRENT_FUNCTION, "Median is not implemented, result is %1%!", std::numeric_limits<RealType>::quiet_NaN());
    //} // median

    template <class RealType, class Policy>
    inline RealType variance(const bernoulli_distribution<RealType, Policy>& dist)
    { // Variance of bernoulli distribution =p * q.
      return  dist.success_fraction() * (1 - dist.success_fraction());
    } // variance

    template <class RealType, class Policy>
    RealType pdf(const bernoulli_distribution<RealType, Policy>& dist, const RealType& k)
    { // Probability Density/Mass Function.
      BOOST_FPU_EXCEPTION_GUARD
      // Error check:
      RealType result = 0; // of checks.
      if(false == bernoulli_detail::check_dist_and_k(
        "boost::math::pdf(bernoulli_distribution<%1%>, %1%)",
        dist.success_fraction(), // 0 to 1
        k, // 0 or 1
        &result, Policy()))
      {
        return result;
      }
      // Assume k is integral.
      if (k == 0)
      {
        return 1 - dist.success_fraction(); // 1 - p
      }
      else  // k == 1
      {
        return dist.success_fraction(); // p
      }
    } // pdf

    template <class RealType, class Policy>
    inline RealType cdf(const bernoulli_distribution<RealType, Policy>& dist, const RealType& k)
    { // Cumulative Distribution Function Bernoulli.
      RealType p = dist.success_fraction();
      // Error check:
      RealType result = 0;
      if(false == bernoulli_detail::check_dist_and_k(
        "boost::math::cdf(bernoulli_distribution<%1%>, %1%)",
        p,
        k,
        &result, Policy()))
      {
        return result;
      }
      if (k == 0)
      {
        return 1 - p;
      }
      else
      { // k == 1
        return 1;
      }
    } // bernoulli cdf

    template <class RealType, class Policy>
    inline RealType cdf(const complemented2_type<bernoulli_distribution<RealType, Policy>, RealType>& c)
    { // Complemented Cumulative Distribution Function bernoulli.
      RealType const& k = c.param;
      bernoulli_distribution<RealType, Policy> const& dist = c.dist;
      RealType p = dist.success_fraction();
      // Error checks:
      RealType result = 0;
      if(false == bernoulli_detail::check_dist_and_k(
        "boost::math::cdf(bernoulli_distribution<%1%>, %1%)",
        p,
        k,
        &result, Policy()))
      {
        return result;
      }
      if (k == 0)
      {
        return p;
      }
      else
      { // k == 1
        return 0;
      }
    } // bernoulli cdf complement

    template <class RealType, class Policy>
    inline RealType quantile(const bernoulli_distribution<RealType, Policy>& dist, const RealType& p)
    { // Quantile or Percent Point Bernoulli function.
      // Return the number of expected successes k either 0 or 1.
      // for a given probability p.

      RealType result = 0; // of error checks:
      if(false == bernoulli_detail::check_dist_and_prob(
        "boost::math::quantile(bernoulli_distribution<%1%>, %1%)",
        dist.success_fraction(),
        p,
        &result, Policy()))
      {
        return result;
      }
      if (p <= (1 - dist.success_fraction()))
      { // p <= pdf(dist, 0) == cdf(dist, 0)
        return 0;
      }
      else
      {
        return 1;
      }
    } // quantile

    template <class RealType, class Policy>
    inline RealType quantile(const complemented2_type<bernoulli_distribution<RealType, Policy>, RealType>& c)
    { // Quantile or Percent Point bernoulli function.
      // Return the number of expected successes k for a given
      // complement of the probability q.
      //
      // Error checks:
      RealType q = c.param;
      const bernoulli_distribution<RealType, Policy>& dist = c.dist;
      RealType result = 0;
      if(false == bernoulli_detail::check_dist_and_prob(
        "boost::math::quantile(bernoulli_distribution<%1%>, %1%)",
        dist.success_fraction(),
        q,
        &result, Policy()))
      {
        return result;
      }

      if (q <= 1 - dist.success_fraction())
      { // // q <= cdf(complement(dist, 0)) == pdf(dist, 0)
        return 1;
      }
      else
      {
        return 0;
      }
    } // quantile complemented.

    template <class RealType, class Policy>
    inline RealType mode(const bernoulli_distribution<RealType, Policy>& dist)
    {
      return static_cast<RealType>((dist.success_fraction() <= 0.5) ? 0 : 1); // p = 0.5 can be 0 or 1
    }

    template <class RealType, class Policy>
    inline RealType skewness(const bernoulli_distribution<RealType, Policy>& dist)
    {
      BOOST_MATH_STD_USING; // Aid ADL for sqrt.
      RealType p = dist.success_fraction();
      return (1 - 2 * p) / sqrt(p * (1 - p));
    }

    template <class RealType, class Policy>
    inline RealType kurtosis_excess(const bernoulli_distribution<RealType, Policy>& dist)
    {
      RealType p = dist.success_fraction();
      // Note Wolfram says this is kurtosis in text, but gamma2 is the kurtosis excess,
      // and Wikipedia also says this is the kurtosis excess formula.
      // return (6 * p * p - 6 * p + 1) / (p * (1 - p));
      // But Wolfram kurtosis article gives this simpler formula for kurtosis excess:
      return 1 / (1 - p) + 1/p -6;
    }

    template <class RealType, class Policy>
    inline RealType kurtosis(const bernoulli_distribution<RealType, Policy>& dist)
    {
      RealType p = dist.success_fraction();
      return 1 / (1 - p) + 1/p -6 + 3;
      // Simpler than:
      // return (6 * p * p - 6 * p + 1) / (p * (1 - p)) + 3;
    }

  } // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_MATH_SPECIAL_BERNOULLI_HPP




/* bernoulli.hpp
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
*/