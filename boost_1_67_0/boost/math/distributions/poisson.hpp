// boost\math\distributions\poisson.hpp

// Copyright John Maddock 2006.
// Copyright Paul A. Bristow 2007.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Poisson distribution is a discrete probability distribution.
// It expresses the probability of a number (k) of
// events, occurrences, failures or arrivals occurring in a fixed time,
// assuming these events occur with a known average or mean rate (lambda)
// and are independent of the time since the last event.
// The distribution was discovered by Simeon-Denis Poisson (1781-1840).

// Parameter lambda is the mean number of events in the given time interval.
// The random variate k is the number of events, occurrences or arrivals.
// k argument may be integral, signed, or unsigned, or floating point.
// If necessary, it has already been promoted from an integral type.

// Note that the Poisson distribution
// (like others including the binomial, negative binomial & Bernoulli)
// is strictly defined as a discrete function:
// only integral values of k are envisaged.
// However because the method of calculation uses a continuous gamma function,
// it is convenient to treat it as if a continuous function,
// and permit non-integral values of k.
// To enforce the strict mathematical model, users should use floor or ceil functions
// on k outside this function to ensure that k is integral.

// See http://en.wikipedia.org/wiki/Poisson_distribution
// http://documents.wolfram.com/v5/Add-onsLinks/StandardPackages/Statistics/DiscreteDistributions.html

#ifndef BOOST_MATH_SPECIAL_POISSON_HPP
#define BOOST_MATH_SPECIAL_POISSON_HPP

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/gamma.hpp> // for incomplete gamma. gamma_q
#include <boost/math/special_functions/trunc.hpp> // for incomplete gamma. gamma_q
#include <boost/math/distributions/complement.hpp> // complements
#include <boost/math/distributions/detail/common_error_handling.hpp> // error checks
#include <boost/math/special_functions/fpclassify.hpp> // isnan.
#include <boost/math/special_functions/factorials.hpp> // factorials.
#include <boost/math/tools/roots.hpp> // for root finding.
#include <boost/math/distributions/detail/inv_discrete_quantile.hpp>

#include <utility>

namespace boost
{
  namespace math
  {
    namespace poisson_detail
    {
      // Common error checking routines for Poisson distribution functions.
      // These are convoluted, & apparently redundant, to try to ensure that
      // checks are always performed, even if exceptions are not enabled.

      template <class RealType, class Policy>
      inline bool check_mean(const char* function, const RealType& mean, RealType* result, const Policy& pol)
      {
        if(!(boost::math::isfinite)(mean) || (mean < 0))
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "Mean argument is %1%, but must be >= 0 !", mean, pol);
          return false;
        }
        return true;
      } // bool check_mean

      template <class RealType, class Policy>
      inline bool check_mean_NZ(const char* function, const RealType& mean, RealType* result, const Policy& pol)
      { // mean == 0 is considered an error.
        if( !(boost::math::isfinite)(mean) || (mean <= 0))
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "Mean argument is %1%, but must be > 0 !", mean, pol);
          return false;
        }
        return true;
      } // bool check_mean_NZ

      template <class RealType, class Policy>
      inline bool check_dist(const char* function, const RealType& mean, RealType* result, const Policy& pol)
      { // Only one check, so this is redundant really but should be optimized away.
        return check_mean_NZ(function, mean, result, pol);
      } // bool check_dist

      template <class RealType, class Policy>
      inline bool check_k(const char* function, const RealType& k, RealType* result, const Policy& pol)
      {
        if((k < 0) || !(boost::math::isfinite)(k))
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "Number of events k argument is %1%, but must be >= 0 !", k, pol);
          return false;
        }
        return true;
      } // bool check_k

      template <class RealType, class Policy>
      inline bool check_dist_and_k(const char* function, RealType mean, RealType k, RealType* result, const Policy& pol)
      {
        if((check_dist(function, mean, result, pol) == false) ||
          (check_k(function, k, result, pol) == false))
        {
          return false;
        }
        return true;
      } // bool check_dist_and_k

      template <class RealType, class Policy>
      inline bool check_prob(const char* function, const RealType& p, RealType* result, const Policy& pol)
      { // Check 0 <= p <= 1
        if(!(boost::math::isfinite)(p) || (p < 0) || (p > 1))
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "Probability argument is %1%, but must be >= 0 and <= 1 !", p, pol);
          return false;
        }
        return true;
      } // bool check_prob

      template <class RealType, class Policy>
      inline bool check_dist_and_prob(const char* function, RealType mean,  RealType p, RealType* result, const Policy& pol)
      {
        if((check_dist(function, mean, result, pol) == false) ||
          (check_prob(function, p, result, pol) == false))
        {
          return false;
        }
        return true;
      } // bool check_dist_and_prob

    } // namespace poisson_detail

    template <class RealType = double, class Policy = policies::policy<> >
    class poisson_distribution
    {
    public:
      typedef RealType value_type;
      typedef Policy policy_type;

      poisson_distribution(RealType l_mean = 1) : m_l(l_mean) // mean (lambda).
      { // Expected mean number of events that occur during the given interval.
        RealType r;
        poisson_detail::check_dist(
           "boost::math::poisson_distribution<%1%>::poisson_distribution",
          m_l,
          &r, Policy());
      } // poisson_distribution constructor.

      RealType mean() const
      { // Private data getter function.
        return m_l;
      }
    private:
      // Data member, initialized by constructor.
      RealType m_l; // mean number of occurrences.
    }; // template <class RealType, class Policy> class poisson_distribution

    typedef poisson_distribution<double> poisson; // Reserved name of type double.

    // Non-member functions to give properties of the distribution.

    template <class RealType, class Policy>
    inline const std::pair<RealType, RealType> range(const poisson_distribution<RealType, Policy>& /* dist */)
    { // Range of permissible values for random variable k.
       using boost::math::tools::max_value;
       return std::pair<RealType, RealType>(static_cast<RealType>(0), max_value<RealType>()); // Max integer?
    }

    template <class RealType, class Policy>
    inline const std::pair<RealType, RealType> support(const poisson_distribution<RealType, Policy>& /* dist */)
    { // Range of supported values for random variable k.
       // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
       using boost::math::tools::max_value;
       return std::pair<RealType, RealType>(static_cast<RealType>(0),  max_value<RealType>());
    }

    template <class RealType, class Policy>
    inline RealType mean(const poisson_distribution<RealType, Policy>& dist)
    { // Mean of poisson distribution = lambda.
      return dist.mean();
    } // mean

    template <class RealType, class Policy>
    inline RealType mode(const poisson_distribution<RealType, Policy>& dist)
    { // mode.
      BOOST_MATH_STD_USING // ADL of std functions.
      return floor(dist.mean());
    }

    //template <class RealType, class Policy>
    //inline RealType median(const poisson_distribution<RealType, Policy>& dist)
    //{ // median = approximately lambda + 1/3 - 0.2/lambda
    //  RealType l = dist.mean();
    //  return dist.mean() + static_cast<RealType>(0.3333333333333333333333333333333333333333333333)
    //   - static_cast<RealType>(0.2) / l;
    //} // BUT this formula appears to be out-by-one compared to quantile(half)
    // Query posted on Wikipedia.
    // Now implemented via quantile(half) in derived accessors.

    template <class RealType, class Policy>
    inline RealType variance(const poisson_distribution<RealType, Policy>& dist)
    { // variance.
      return dist.mean();
    }

    // RealType standard_deviation(const poisson_distribution<RealType, Policy>& dist)
    // standard_deviation provided by derived accessors.

    template <class RealType, class Policy>
    inline RealType skewness(const poisson_distribution<RealType, Policy>& dist)
    { // skewness = sqrt(l).
      BOOST_MATH_STD_USING // ADL of std functions.
      return 1 / sqrt(dist.mean());
    }

    template <class RealType, class Policy>
    inline RealType kurtosis_excess(const poisson_distribution<RealType, Policy>& dist)
    { // skewness = sqrt(l).
      return 1 / dist.mean(); // kurtosis_excess 1/mean from Wiki & MathWorld eq 31.
      // http://mathworld.wolfram.com/Kurtosis.html explains that the kurtosis excess
      // is more convenient because the kurtosis excess of a normal distribution is zero
      // whereas the true kurtosis is 3.
    } // RealType kurtosis_excess

    template <class RealType, class Policy>
    inline RealType kurtosis(const poisson_distribution<RealType, Policy>& dist)
    { // kurtosis is 4th moment about the mean = u4 / sd ^ 4
      // http://en.wikipedia.org/wiki/Kurtosis
      // kurtosis can range from -2 (flat top) to +infinity (sharp peak & heavy tails).
      // http://www.itl.nist.gov/div898/handbook/eda/section3/eda35b.htm
      return 3 + 1 / dist.mean(); // NIST.
      // http://mathworld.wolfram.com/Kurtosis.html explains that the kurtosis excess
      // is more convenient because the kurtosis excess of a normal distribution is zero
      // whereas the true kurtosis is 3.
    } // RealType kurtosis

    template <class RealType, class Policy>
    RealType pdf(const poisson_distribution<RealType, Policy>& dist, const RealType& k)
    { // Probability Density/Mass Function.
      // Probability that there are EXACTLY k occurrences (or arrivals).
      BOOST_FPU_EXCEPTION_GUARD

      BOOST_MATH_STD_USING // for ADL of std functions.

      RealType mean = dist.mean();
      // Error check:
      RealType result = 0;
      if(false == poisson_detail::check_dist_and_k(
        "boost::math::pdf(const poisson_distribution<%1%>&, %1%)",
        mean,
        k,
        &result, Policy()))
      {
        return result;
      }

      // Special case of mean zero, regardless of the number of events k.
      if (mean == 0)
      { // Probability for any k is zero.
        return 0;
      }
      if (k == 0)
      { // mean ^ k = 1, and k! = 1, so can simplify.
        return exp(-mean);
      }
      return boost::math::gamma_p_derivative(k+1, mean, Policy());
    } // pdf

    template <class RealType, class Policy>
    RealType cdf(const poisson_distribution<RealType, Policy>& dist, const RealType& k)
    { // Cumulative Distribution Function Poisson.
      // The random variate k is the number of occurrences(or arrivals)
      // k argument may be integral, signed, or unsigned, or floating point.
      // If necessary, it has already been promoted from an integral type.
      // Returns the sum of the terms 0 through k of the Poisson Probability Density or Mass (pdf).

      // But note that the Poisson distribution
      // (like others including the binomial, negative binomial & Bernoulli)
      // is strictly defined as a discrete function: only integral values of k are envisaged.
      // However because of the method of calculation using a continuous gamma function,
      // it is convenient to treat it as if it is a continuous function
      // and permit non-integral values of k.
      // To enforce the strict mathematical model, users should use floor or ceil functions
      // outside this function to ensure that k is integral.

      // The terms are not summed directly (at least for larger k)
      // instead the incomplete gamma integral is employed,

      BOOST_MATH_STD_USING // for ADL of std function exp.

      RealType mean = dist.mean();
      // Error checks:
      RealType result = 0;
      if(false == poisson_detail::check_dist_and_k(
        "boost::math::cdf(const poisson_distribution<%1%>&, %1%)",
        mean,
        k,
        &result, Policy()))
      {
        return result;
      }
      // Special cases:
      if (mean == 0)
      { // Probability for any k is zero.
        return 0;
      }
      if (k == 0)
      { // return pdf(dist, static_cast<RealType>(0));
        // but mean (and k) have already been checked,
        // so this avoids unnecessary repeated checks.
       return exp(-mean);
      }
      // For small integral k could use a finite sum -
      // it's cheaper than the gamma function.
      // BUT this is now done efficiently by gamma_q function.
      // Calculate poisson cdf using the gamma_q function.
      return gamma_q(k+1, mean, Policy());
    } // binomial cdf

    template <class RealType, class Policy>
    RealType cdf(const complemented2_type<poisson_distribution<RealType, Policy>, RealType>& c)
    { // Complemented Cumulative Distribution Function Poisson
      // The random variate k is the number of events, occurrences or arrivals.
      // k argument may be integral, signed, or unsigned, or floating point.
      // If necessary, it has already been promoted from an integral type.
      // But note that the Poisson distribution
      // (like others including the binomial, negative binomial & Bernoulli)
      // is strictly defined as a discrete function: only integral values of k are envisaged.
      // However because of the method of calculation using a continuous gamma function,
      // it is convenient to treat it as is it is a continuous function
      // and permit non-integral values of k.
      // To enforce the strict mathematical model, users should use floor or ceil functions
      // outside this function to ensure that k is integral.

      // Returns the sum of the terms k+1 through inf of the Poisson Probability Density/Mass (pdf).
      // The terms are not summed directly (at least for larger k)
      // instead the incomplete gamma integral is employed,

      RealType const& k = c.param;
      poisson_distribution<RealType, Policy> const& dist = c.dist;

      RealType mean = dist.mean();

      // Error checks:
      RealType result = 0;
      if(false == poisson_detail::check_dist_and_k(
        "boost::math::cdf(const poisson_distribution<%1%>&, %1%)",
        mean,
        k,
        &result, Policy()))
      {
        return result;
      }
      // Special case of mean, regardless of the number of events k.
      if (mean == 0)
      { // Probability for any k is unity, complement of zero.
        return 1;
      }
      if (k == 0)
      { // Avoid repeated checks on k and mean in gamma_p.
         return -boost::math::expm1(-mean, Policy());
      }
      // Unlike un-complemented cdf (sum from 0 to k),
      // can't use finite sum from k+1 to infinity for small integral k,
      // anyway it is now done efficiently by gamma_p.
      return gamma_p(k + 1, mean, Policy()); // Calculate Poisson cdf using the gamma_p function.
      // CCDF = gamma_p(k+1, lambda)
    } // poisson ccdf

    template <class RealType, class Policy>
    inline RealType quantile(const poisson_distribution<RealType, Policy>& dist, const RealType& p)
    { // Quantile (or Percent Point) Poisson function.
      // Return the number of expected events k for a given probability p.
      static const char* function = "boost::math::quantile(const poisson_distribution<%1%>&, %1%)";
      RealType result = 0; // of Argument checks:
      if(false == poisson_detail::check_prob(
        function,
        p,
        &result, Policy()))
      {
        return result;
      }
      // Special case:
      if (dist.mean() == 0)
      { // if mean = 0 then p = 0, so k can be anything?
         if (false == poisson_detail::check_mean_NZ(
         function,
         dist.mean(),
         &result, Policy()))
        {
          return result;
        }
      }
      if(p == 0)
      {
         return 0; // Exact result regardless of discrete-quantile Policy
      }
      if(p == 1)
      {
         return policies::raise_overflow_error<RealType>(function, 0, Policy());
      }
      typedef typename Policy::discrete_quantile_type discrete_type;
      boost::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
      RealType guess, factor = 8;
      RealType z = dist.mean();
      if(z < 1)
         guess = z;
      else
         guess = boost::math::detail::inverse_poisson_cornish_fisher(z, p, RealType(1-p), Policy());
      if(z > 5)
      {
         if(z > 1000)
            factor = 1.01f;
         else if(z > 50)
            factor = 1.1f;
         else if(guess > 10)
            factor = 1.25f;
         else
            factor = 2;
         if(guess < 1.1)
            factor = 8;
      }

      return detail::inverse_discrete_quantile(
         dist,
         p,
         false,
         guess,
         factor,
         RealType(1),
         discrete_type(),
         max_iter);
   } // quantile

    template <class RealType, class Policy>
    inline RealType quantile(const complemented2_type<poisson_distribution<RealType, Policy>, RealType>& c)
    { // Quantile (or Percent Point) of Poisson function.
      // Return the number of expected events k for a given
      // complement of the probability q.
      //
      // Error checks:
      static const char* function = "boost::math::quantile(complement(const poisson_distribution<%1%>&, %1%))";
      RealType q = c.param;
      const poisson_distribution<RealType, Policy>& dist = c.dist;
      RealType result = 0;  // of argument checks.
      if(false == poisson_detail::check_prob(
        function,
        q,
        &result, Policy()))
      {
        return result;
      }
      // Special case:
      if (dist.mean() == 0)
      { // if mean = 0 then p = 0, so k can be anything?
         if (false == poisson_detail::check_mean_NZ(
         function,
         dist.mean(),
         &result, Policy()))
        {
          return result;
        }
      }
      if(q == 0)
      {
         return policies::raise_overflow_error<RealType>(function, 0, Policy());
      }
      if(q == 1)
      {
         return 0;  // Exact result regardless of discrete-quantile Policy
      }
      typedef typename Policy::discrete_quantile_type discrete_type;
      boost::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
      RealType guess, factor = 8;
      RealType z = dist.mean();
      if(z < 1)
         guess = z;
      else
         guess = boost::math::detail::inverse_poisson_cornish_fisher(z, RealType(1-q), q, Policy());
      if(z > 5)
      {
         if(z > 1000)
            factor = 1.01f;
         else if(z > 50)
            factor = 1.1f;
         else if(guess > 10)
            factor = 1.25f;
         else
            factor = 2;
         if(guess < 1.1)
            factor = 8;
      }

      return detail::inverse_discrete_quantile(
         dist,
         q,
         true,
         guess,
         factor,
         RealType(1),
         discrete_type(),
         max_iter);
   } // quantile complement.

  } // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>
#include <boost/math/distributions/detail/inv_discrete_quantile.hpp>

#endif // BOOST_MATH_SPECIAL_POISSON_HPP




/* poisson.hpp
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
*/