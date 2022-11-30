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
      inline bool check_dist(const char* function, const RealType& p, RealType* result, const Policy& /* pol */, const std::true_type&)
      {
        return check_success_fraction(function, p, result, Policy());
      }
      template <class RealType, class Policy>
      inline bool check_dist(const char* , const RealType& , RealType* , const Policy& /* pol */, const std::false_type&)
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

    #ifdef __cpp_deduction_guides
    template <class RealType>
    bernoulli_distribution(RealType)->bernoulli_distribution<typename boost::math::tools::promote_args<RealType>::type>;
    #endif

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