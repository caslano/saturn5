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

    #ifdef __cpp_deduction_guides
    template <class RealType>
    poisson_distribution(RealType)->poisson_distribution<typename boost::math::tools::promote_args<RealType>::type>;
    #endif

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
      std::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
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
      std::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
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
4cfUj+4HRgriwXu9xbZjncpdmIgXT6BODA4VdZ/9jHJI/ENGEUkRbcvL0c5V6AfN4CRqhZsm09aIxFn00DnCQz2u0uSUNFZgZZ9yzBAHX8YDlolHiMVfeR0RoQjKXj/J0yQs4IZD7Lo3cDJCF0GtgbdeIhOxt90MSqCu6YgSenJNP9gmlaRWnE2XK5X3yhpHMIKCkwran9+PCN43avxjQahNLHck3NqdB+5bjeTp/4o8KPmpPgKI8beHHv0z7G48/Y9mCxyVVV5ICYnkljsBFs9n5IY/SIj/Wg66XTVw2Vrh4I52y1wsLtmRKbyspvF3InF6kjP/mKK0eQH1Cjs39TKescS+oK5AQYV4QLmgnDlyfgJh0iyNvDqPMoN0X33nZXaM7k/6ZBqKN/KBvNlg+p8nM6UCbTD8FcI8/z8jPvjwoNx2cBeIVD2y0aLJ8Y7O4UzjJ64sVPSz56gvaM6mxYd6eS5diVdHvbKA+5MVx4dgklmY5fBC4Y33dklcLj1x7EwkvonmwP7wKHWpzA3Dmm3hiaamdf5zIgBvEA/WDX+t3BNf+9xr63Oxnck7BRON2Tf0tDh5JSXQnmq0SNKMJxhdMyUO3D8NPQz7lwmH4wbDKFG2lI9zxOuug727CDEEgA2S/N80iydqp14ofOKRGI9xKQvru5YpJaLMu5RtS44HEByEvlTOlD6yLLXJhtHySJfbS/eiyJ6YRYZCDt55Jb96wBQykFSzOkuF8Cf6HYwEBnvWCfS2pHivzVX+LLIDKpDPrkHPr9M/O3FMdgvpKFf4JAex+IbfxPEzSO+DOBCbHlUg7NFBpmikLCBAaJLovx3cIb86pGZA7wbrM9kYTXk7ORGl1e2OXJtkfu81tunv2GzILlOzCAsnjpGmVM4tkjPHrkmO0egJkZv5V8l/e6H+Y7Lhir1TtPYioOIgdvfxPoR8q5fNDnlGO86Z+oseBc4Ii+IkIoRVBo/N+wef3YIgmRqvuphZbdNX6E5zahFFDLzHRXKBCBWL0g9tojn+4yQEl8PcH17kNGhChp5cL3/kRHlUfc7/Ybc0UsA70oYyz6I2IP81SlVddVEyTaOAK1uTzSsoP64SxTG/wVTcYLufNgBdFk2IlQzDm4JBjcarZQ5jTdK6SpleIYiZHQuF3hF+2o4c3/C4mAqrQCGCWnGHCwORpHsijSTXQ4hMgbnKULM8CVptxqjV8TZUo1VfUamjfXnqb+bmxhDyLpE4CZiVhqevcMGt86GJqOudF9ECnwVnfgRKGemfZsfrfUEuDBmxosz4u7iuKUnC9Cugl8MR+QHBweHWubIdpDqEvOJ1a8gpq3EpXeUhukP3P8SSy9qTZrkGjcNAM3ynEuxsajr24MuhFxeJ7emtDUr62Gk0BIRCfQw7WWgivRqMjrkPhPUnY1PJ5SsZZ66ppVJezof9DIfDxBOtUm7xZ8g69lcBEKJJwu/nqahrlDxOdPRhdHM8DZaLhdp02jd7DDK6dg4Edb3sci68zMvOIgexJ+yyYfL2qnN/aBcDZCS4ohVID2Ina8tKYSl0kuh4/zqceC+YGmhcTnBC1hP6nONb5YfNgD8DJ07md+S3lNBdci71OqsKmF+umk/Ay7hhDUj09MU9/iT0MHORVjMZY2BxPCVCtWBa4FbLwc17ebA4fpdwkCMgigucWejpbF3ZqjH0HyRflhUgtHbxTQ1S+I6N/mS9TKlrUHABTZ1psbKOsBv2UcdVpgAt/XXfboBCqVkjZ/gRl3xyWYmFY5v1hjDQWE6AZmdlCB5QS9BOcpza9wqUtsB8rFn7vNr7zkwdFv0D7N2SLS660ACveD0/XPZwrpQfTIKLYdq0ufgUtpejagYJylN2grGHy1uAtmDC7iIbHFeoISLlxrUS3N8Uu4Q3iTMLI0RMVaSxOgpqo0xtfS6E9ZMGi21+RKAwnNTppN9vXF14xbTdV8LBK7iQJgBRjXfBUeq0Wrg0o5a8oYVNWDvQl7N2xahmou9Z4kNQ1zxzyksrRW28ky9Yv8LeOiX159RSxfqFnOUdCYi9ygvlT9QTQkrm2+IaJJz0wrm0RY20h1wWkfjXDlKz+jlJcRKO/IXV4iCbe0TwC8fskrcL3jNreQxqO0j5YEMQztg05TPpKAvrcgbVADyaElsvgc9qoy1GVOY9ZhSHP9RykmnO26tQW9usExyatEnpdHM9cIQGN9+EVBrFAuGi1mmbnxYNdaJm4rOfeL82kyc6BuD4mu1MAY3tsDP/ad9slP0w98q99Ig2mfUNeXCjgR+8ha89AABwbr0A4eUuNMAqMB5Aknb+Oy/rpEqR/ZiCRzwQUh1tdGioaPZ1F1zUB+dK9ZPDNi6AWCvpjkS6iN/254Lkn+JLrUwNe2z2iUqNJKA/uh/PDsXUA/xFZoUaEVxNMygbvRhL0IRBpjFnbbW+E19/4sFd7TsDPHiZ2q2KNmk3Ad/IPVUWpA1+EPrrLSpKFKqMKQare82Um7hSOR8dBjmYcUtwdiaVv9MdOzsYjGueX0cz2UXiAdTMNyiRLdGQNfvt2Tka8GsRtyLl9JenysdR+2AZrLCdcV/LxTTPi5g4QFhbj9HHsrFjbcrcmJMp2da9mEKOKlCzjEkWfbN7YLolkGrDmGNpUNdRQWBKuHTBNarUeUqpn2b32xtYAzvAuLzclUjQ2uK+HdZS0jrmN4h2FjU5VuVQb0HPMo/Gm/56InfpEu9LopChsFqfRP+o8vi0QjepeOzYl7xKdjClcgdZlGOZgzRgpcgsfMuBJj0pNLSqwiqXW9g3Jvly+Vz9MPVNHKCssioZ94qQVYlmyD0Zo0ktg49mp7hqPZTGqE25l0PRMnuJ3oC9Ho9fukmN5YsfGAB8CzhLAvDhUnRowU3Cry4op4fUgqVrEvr++IjOGYRkjOiJYAgkj9DXu7rdctC7nNcbao7WS2qKo7V/gH9yC7/4SrSTjvhzH3T2LZhQDC8ckp+5hNzAWTaVu9IqQ1547Yuwijm2E6bQx+UHLD0vFDOLdSIXe5mqRZsGyjynwK/bdW2/oHSh+kWXT2wA56/U3CTPR5VCo4oH1aopZEtuLDj6VeC+OdwGnSb881LAu0KJiaZLhICZfJpd2e8HTTGpRgiLUaby0sd/oTcOMMnBiuU28leyYDC333ciBmbdyrr8KhQlL9Lq8awhpk/8qtHIBtNIl2RXTD9fz3GZM/zjtP8sY08mXmEI8eMMiPYGTvsZpiGvvpOF80Z5O0dBR2XlHfXVDAnK8NPReD+Dmh6jIGPpeh0y2CJWhc3ojzizgUfci9WBAv5uoHXBSNNZj/4xq3gxVGt2u2xajJ7eQMVjC8olsKxEu3/xJLh86jgzz6uUlx54fSg32aNEeFMVia3Zk/6tZ3Sm1Zot9KfDk6Xn51VUJCKEpxF+b7vwAfsyx0VEuQHdp1p/J3RXM1la/nB/3u4zW9weSWTMWdm7VWcy0y1ucDNEsn2OBWZpgfk4sl2ll3H3UcvbJC+ff/B9ZlDJ1R0cAtPGRCVw66SC/q06Xuvz8H61E67af5zva88EEAMAgBDvrsRP6B8swClYP2ihtxt2rBLR9tTOyvYFf9a9rYI3RBwepHvkmJEKa9nIFTrv5wVJm9JhnyANbF7kvF28GkIBs95aodWMndfYCCVaNF1UhslcXsXuc+spik+I307x+aLlNZYunxF7hTO/aTL5XcDo0XXSa3GcpbbPEjpHV78EfOEHK+nLrse/kgMoj/g/X44iwwVBE03trd9FxK4ieimYtfYxJavZady2kYWPZ80eerW4EYyMsFaDUPd/FTNTcXSVTACUIB6tadSmWKpAktBLpfTmNTgM9qfUYVYaOvsXAtptnuCecSkkWedHU3HVeyOKKQkV69Zfw/ktQPS2PVSCAUgQ4l4rwt8l3Lkc71dgKb7ZI88t3Vny/egrQPs97STwzXOio6NYV03aRd0w9UlWMkB97rKwPJlXNwwlhYJeYRa38LN9khEE+ptOYwJol8q8kSnYK7dW819kCiqukqtGegCR78L7RZuInTr4dxPtR8LretB6eVP+faRocO1cV0GKsZb87PPc56LkQL7YJXksxCpa5HBUxvBS/tHWOXda4DTEQ1OJmSMfIL2udO5uCU5dXzRrHmutpu5NTlGIT9HD46rjgMQ1qmVN7DP88wK0/iSD0cyUcN6PcD+4V8N38RBghqkkAbfG8iKFQ9mTbi144eXE8q1rr3NRfyUTZmUoGH3nrg4Bx3j42sqzRB3I0pTQfqPlMEIbE/zOLbdfXfGNvN4in4dwAfzW11gwBeaabBlXH68fhPw32anGWdpgSwYVFPwJ+Z+1lHi8wnEpDSaxeRoI8NuGG/UcZdGcrW9c0g+VQFqNUWMqamKVW7uRQ5r3CrJur8wKi63cpXEtQ2/1X+siULtkI/F9t5LdNmR+9rqde8x+AVctmzzx1gjkmO+p4/QWo2QrJm4gv5C1S2PdphalFenKurvoqLwVSrOkblu/XDNv6xZuehXWGTsCUaVCQaDpfOax/oubR/QuewtFyoVqFiciLv7HU4DcmYWD2av7f7uv33qNa+dNWdd+199Wks7rgpc2MPPPVi58zB/YvQFSXDO3Ww0mIpz5fO5Pe96fraaha3DqOw7vs6H4pZAqLMuCig/DoeSY7s3fw2g75eWx6gyh3B0xVxZaXk6M3g+vVhMcjudVQ0OB7lbzlUSZjpcwbCiAY37QZCe6cz+lncVzoxhp/Y0zACGH+Tbw9EGfGhzklpMQK/8kG59yKlIZzK1Sxs7I7dXytx4CW76pW7PZ/w2Vm8DNgqfJjmWrRk08K887wHfHgDwSDdpdollz78Q6QSqCXyYLLo3Y7PW9nCcThSmzd5PZfrdqQ7H0GOxxMI35vJed9kJUaXxOdOY4p9g8b+zrgSUwgoeYjDhPMOVlV8dsYNZD1VHqtvWKh98rPGQjFBcMjnbZcV4l90tHc/zdF/2HteLkeDEEzeALLX3ICPPFLoarFq7dH3b/TSIXSuZ5MX7zdwzij0w7z7tUE/oTHvySQ220CcXJGlmHhniNaLU6UhfJNXnEl5LdX9e5ptgxcFA3eLXaHhJXuTK+zxjyncpoCWaQrnJqCDUtFC2Gqm4Zq07j4LalDPNszi6pI/5paoPg/fpQzCypCuloFAvKD6GKSVzwh6cXC9BZT3uWL8/7q1FSgp8sdzBKqIncEMjoAQkzmUcFp6XoQBYKh7C8P093mn/eImQz62U2n1Vg+9WpeZXhTp5p+jOLrUP+2p5/t3nB5GEYw+Xd8X76Q94S8nfgDjjWyjV2dX7oDGn+pODARwetgCnYfQJksxGusMIsOmUd0Gje8RITGzwFKR0vqy4Qf/tgvZ4/uoId/SAusefFUkTKPXh2O8L5CK3OtqB8twNF1P27qUMEDFIGg4bY5nFnWlmYc7oSoBGF0l61i9SwNhLhYuGF8HL1XqxIdUzANbx83hQO1fpkaF75aXcDvEHslITetBMWV2ZyKwnDnMvpEMO330uIGE3kVn4XbubeUq85+87jtMqIdnxTSTujKBmanWKmyXpak8IrLF2tUld7bRIK+LZ4rXwvBAIsOJeDtdTZA+pGwQnBBOhcWV2/UnUSDuz464KTOThcPPFtcFbklP08K/NFzg7GolylrQHieYDaEMaayLOkNaa7zqFJO3Q90D8ZsQFBghYuRS4h3jv9hk81k5tadgMGiAZdhnnyAbek6lGd0I7QSPV9HD6bI28OcikUswZthmkDMXHqlWoeEHHtb3unCdGeubjgIVfwlwYRHOkWRsWMy4lL7ecLrmrtDWaKFtthyOE0F/9Z6JWs5Iw/Z/w7HaTUo+AwALsej/MJg1hllDymMc6OsPsriu+LhsSu8bngOXvkfAEMX1FRsxgMN+G8JubMGYW6fdVduqCbm0TLrmYrlJCTfKevB6NL4kH4ZoeJEFeEOm5l/sXtG0YePiVAiLJDG1A5RzHAV93xQT1YKMlLo1pj5ug6kfeRp+FaQWzVs0TimoyvUjoF3sETbwSB+IPyRhs5gD3mijc1Hk6l5YAlsU7DKrtceo1tDAH6AvpV2D5AczRIMmUVs7Tuita0sRflpNhImdF5E41ctjaKpY6F9N0Ufm0dXdrcgqYoxPwJRgjQ8GJTPzBzbACIn44xYJLiitCAskTJvSI2mpod2GJeaUynU43TB+rp7DIMQ0gS2lnL+zvuIDPtCEpYRBEcfL+hYi/Wb7Kpxqv/b70km/FNz5+iG+aLqvWpVhmvhky7yJ4+kWLECYFOEfiqP3SAhCpDfRuDnP4EIus3sIXhbLdsT6827G+qTKkqabcyhv6dNGB+I/xRyyAzeSloPC8ISviPY0aYgfabXnHglFVAIKl5tPIrP7f7FXqP6CNZEVO2ZvPa4yub+Dhv9XFlCNhGpkg6tmkZsPXzpYRSNAVlGcPGICN6bwM1wNE/JkaHraS8YQf1oqouAMAAALUf7yESa9a0GBuxl6dmxNQnShzFhd/DLpI/sr1NfwPuqoG6mulEbx+7LhiuRqIuMXPIjA/xRUCi2238ZxNvdu7izFA1Ov36l9SqIo/XumQZM90c3PD8LfGY45dCrwYukL6auOXP0joJe583GMkL6SB2okNDFjI+GQLkbHYu29nGete+ylYTFJMvyWaCIyhhOcH3MDe1RQFygvF2tccwx0O9cHjk6b/KUk8HaH3njypdU18xLTMIvGMK7Ugod1Fh3vmQj0ZTUiVHmlhftOp9BqlUzvVSxLq9B4RnZDLFXIETcpYFL5G/Xg/8KVwzt38YOMj6Q2d8+EpliOjZUnyL8mz+Zl9wRZx4fkrJoBJ4avSCLD7rKD+qoBqOqOVutIjQL147J08usYFmFO5L53/BuI63GeP/QKdx7NRqHHkHc7xvWhrflUEwrixIf4dTSbddxa7OoNRqDZEr79EMMjYEaXtd4jH36+AkKFAN2iTh3oRyPT+12Ty5sICO/pMrhGTu8jr4s4Su5O+8csGG9tOKMPUwyAYqBrV0UgFbod6tpjUyi2cSanmAKXvwWKNVhFylxK04tTF88ZkTRcZ2arOyzAUHar5o1IMCZFilC1yKoB8/zFkNUivZsoo9gBP9UtOhQjS735HQspMFC3chvm2uc8OkThCi7Kp9UkON2bIK1fk4vH/JJyle9FR5bjNfIIL6NSD+paUDDPvt+a8H23coo8Yz+f2uOCkdLgP0wqfJ0+/dK/pffypHDW3PCrL/vMLbDWnPrBEbFNO2F3EyqmAIRkGaVWzT0qwo9XnckOOTgsst7bU9dqUL+UnqtJNHrHSm/DY1JAa/51inrNkW1cH8zynCt+JKgbjKmOIeF120VkgG/a1Gxr/KFFfqBB7xHkM+0W3opzOweofECnq3PB9XYjAv1JoTBPu+7U+sKinmcgX6e+eNuz9Wqml7VZ+SxgECaQh0fDWpsfvVTt0D8Rr3DvMiwampgyNymHH/8LK34klLdWCEYK/uWSOvYs+kNSHDMHTq7CSVb+HodehwVX3EOumv7KKqeYbfZD29UvsJkf/knJrBO1vmAlrCMOjJdCIYWxiu2NoO3ZZOC/VJbQZHMGo0x8znfRrhwVXNUJimBcMGBPSDVPWsvDxoZgZaZ/ljnIcB7pI0z3l2
*/