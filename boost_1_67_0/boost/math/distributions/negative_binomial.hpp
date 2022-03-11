// boost\math\special_functions\negative_binomial.hpp

// Copyright Paul A. Bristow 2007.
// Copyright John Maddock 2007.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// http://en.wikipedia.org/wiki/negative_binomial_distribution
// http://mathworld.wolfram.com/NegativeBinomialDistribution.html
// http://documents.wolfram.com/teachersedition/Teacher/Statistics/DiscreteDistributions.html

// The negative binomial distribution NegativeBinomialDistribution[n, p]
// is the distribution of the number (k) of failures that occur in a sequence of trials before
// r successes have occurred, where the probability of success in each trial is p.

// In a sequence of Bernoulli trials or events
// (independent, yes or no, succeed or fail) with success_fraction probability p,
// negative_binomial is the probability that k or fewer failures
// precede the r th trial's success.
// random variable k is the number of failures (NOT the probability).

// Negative_binomial distribution is a discrete probability distribution.
// But note that the negative binomial distribution
// (like others including the binomial, Poisson & Bernoulli)
// is strictly defined as a discrete function: only integral values of k are envisaged.
// However because of the method of calculation using a continuous gamma function,
// it is convenient to treat it as if a continuous function,
// and permit non-integral values of k.

// However, by default the policy is to use discrete_quantile_policy.

// To enforce the strict mathematical model, users should use conversion
// on k outside this function to ensure that k is integral.

// MATHCAD cumulative negative binomial pnbinom(k, n, p)

// Implementation note: much greater speed, and perhaps greater accuracy,
// might be achieved for extreme values by using a normal approximation.
// This is NOT been tested or implemented.

#ifndef BOOST_MATH_SPECIAL_NEGATIVE_BINOMIAL_HPP
#define BOOST_MATH_SPECIAL_NEGATIVE_BINOMIAL_HPP

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/beta.hpp> // for ibeta(a, b, x) == Ix(a, b).
#include <boost/math/distributions/complement.hpp> // complement.
#include <boost/math/distributions/detail/common_error_handling.hpp> // error checks domain_error & logic_error.
#include <boost/math/special_functions/fpclassify.hpp> // isnan.
#include <boost/math/tools/roots.hpp> // for root finding.
#include <boost/math/distributions/detail/inv_discrete_quantile.hpp>

#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/if.hpp>

#include <limits> // using std::numeric_limits;
#include <utility>

#if defined (BOOST_MSVC)
#  pragma warning(push)
// This believed not now necessary, so commented out.
//#  pragma warning(disable: 4702) // unreachable code.
// in domain_error_imp in error_handling.
#endif

namespace boost
{
  namespace math
  {
    namespace negative_binomial_detail
    {
      // Common error checking routines for negative binomial distribution functions:
      template <class RealType, class Policy>
      inline bool check_successes(const char* function, const RealType& r, RealType* result, const Policy& pol)
      {
        if( !(boost::math::isfinite)(r) || (r <= 0) )
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "Number of successes argument is %1%, but must be > 0 !", r, pol);
          return false;
        }
        return true;
      }
      template <class RealType, class Policy>
      inline bool check_success_fraction(const char* function, const RealType& p, RealType* result, const Policy& pol)
      {
        if( !(boost::math::isfinite)(p) || (p < 0) || (p > 1) )
        {
          *result = policies::raise_domain_error<RealType>(
            function,
            "Success fraction argument is %1%, but must be >= 0 and <= 1 !", p, pol);
          return false;
        }
        return true;
      }
      template <class RealType, class Policy>
      inline bool check_dist(const char* function, const RealType& r, const RealType& p, RealType* result, const Policy& pol)
      {
        return check_success_fraction(function, p, result, pol)
          && check_successes(function, r, result, pol);
      }
      template <class RealType, class Policy>
      inline bool check_dist_and_k(const char* function, const RealType& r, const RealType& p, RealType k, RealType* result, const Policy& pol)
      {
        if(check_dist(function, r, p, result, pol) == false)
        {
          return false;
        }
        if( !(boost::math::isfinite)(k) || (k < 0) )
        { // Check k failures.
          *result = policies::raise_domain_error<RealType>(
            function,
            "Number of failures argument is %1%, but must be >= 0 !", k, pol);
          return false;
        }
        return true;
      } // Check_dist_and_k

      template <class RealType, class Policy>
      inline bool check_dist_and_prob(const char* function, const RealType& r, RealType p, RealType prob, RealType* result, const Policy& pol)
      {
        if((check_dist(function, r, p, result, pol) && detail::check_probability(function, prob, result, pol)) == false)
        {
          return false;
        }
        return true;
      } // check_dist_and_prob
    } //  namespace negative_binomial_detail

    template <class RealType = double, class Policy = policies::policy<> >
    class negative_binomial_distribution
    {
    public:
      typedef RealType value_type;
      typedef Policy policy_type;

      negative_binomial_distribution(RealType r, RealType p) : m_r(r), m_p(p)
      { // Constructor.
        RealType result;
        negative_binomial_detail::check_dist(
          "negative_binomial_distribution<%1%>::negative_binomial_distribution",
          m_r, // Check successes r > 0.
          m_p, // Check success_fraction 0 <= p <= 1.
          &result, Policy());
      } // negative_binomial_distribution constructor.

      // Private data getter class member functions.
      RealType success_fraction() const
      { // Probability of success as fraction in range 0 to 1.
        return m_p;
      }
      RealType successes() const
      { // Total number of successes r.
        return m_r;
      }

      static RealType find_lower_bound_on_p(
        RealType trials,
        RealType successes,
        RealType alpha) // alpha 0.05 equivalent to 95% for one-sided test.
      {
        static const char* function = "boost::math::negative_binomial<%1%>::find_lower_bound_on_p";
        RealType result = 0;  // of error checks.
        RealType failures = trials - successes;
        if(false == detail::check_probability(function, alpha, &result, Policy())
          && negative_binomial_detail::check_dist_and_k(
          function, successes, RealType(0), failures, &result, Policy()))
        {
          return result;
        }
        // Use complement ibeta_inv function for lower bound.
        // This is adapted from the corresponding binomial formula
        // here: http://www.itl.nist.gov/div898/handbook/prc/section2/prc241.htm
        // This is a Clopper-Pearson interval, and may be overly conservative,
        // see also "A Simple Improved Inferential Method for Some
        // Discrete Distributions" Yong CAI and K. KRISHNAMOORTHY
        // http://www.ucs.louisiana.edu/~kxk4695/Discrete_new.pdf
        //
        return ibeta_inv(successes, failures + 1, alpha, static_cast<RealType*>(0), Policy());
      } // find_lower_bound_on_p

      static RealType find_upper_bound_on_p(
        RealType trials,
        RealType successes,
        RealType alpha) // alpha 0.05 equivalent to 95% for one-sided test.
      {
        static const char* function = "boost::math::negative_binomial<%1%>::find_upper_bound_on_p";
        RealType result = 0;  // of error checks.
        RealType failures = trials - successes;
        if(false == negative_binomial_detail::check_dist_and_k(
          function, successes, RealType(0), failures, &result, Policy())
          && detail::check_probability(function, alpha, &result, Policy()))
        {
          return result;
        }
        if(failures == 0)
           return 1;
        // Use complement ibetac_inv function for upper bound.
        // Note adjusted failures value: *not* failures+1 as usual.
        // This is adapted from the corresponding binomial formula
        // here: http://www.itl.nist.gov/div898/handbook/prc/section2/prc241.htm
        // This is a Clopper-Pearson interval, and may be overly conservative,
        // see also "A Simple Improved Inferential Method for Some
        // Discrete Distributions" Yong CAI and K. KRISHNAMOORTHY
        // http://www.ucs.louisiana.edu/~kxk4695/Discrete_new.pdf
        //
        return ibetac_inv(successes, failures, alpha, static_cast<RealType*>(0), Policy());
      } // find_upper_bound_on_p

      // Estimate number of trials :
      // "How many trials do I need to be P% sure of seeing k or fewer failures?"

      static RealType find_minimum_number_of_trials(
        RealType k,     // number of failures (k >= 0).
        RealType p,     // success fraction 0 <= p <= 1.
        RealType alpha) // risk level threshold 0 <= alpha <= 1.
      {
        static const char* function = "boost::math::negative_binomial<%1%>::find_minimum_number_of_trials";
        // Error checks:
        RealType result = 0;
        if(false == negative_binomial_detail::check_dist_and_k(
          function, RealType(1), p, k, &result, Policy())
          && detail::check_probability(function, alpha, &result, Policy()))
        { return result; }

        result = ibeta_inva(k + 1, p, alpha, Policy());  // returns n - k
        return result + k;
      } // RealType find_number_of_failures

      static RealType find_maximum_number_of_trials(
        RealType k,     // number of failures (k >= 0).
        RealType p,     // success fraction 0 <= p <= 1.
        RealType alpha) // risk level threshold 0 <= alpha <= 1.
      {
        static const char* function = "boost::math::negative_binomial<%1%>::find_maximum_number_of_trials";
        // Error checks:
        RealType result = 0;
        if(false == negative_binomial_detail::check_dist_and_k(
          function, RealType(1), p, k, &result, Policy())
          &&  detail::check_probability(function, alpha, &result, Policy()))
        { return result; }

        result = ibetac_inva(k + 1, p, alpha, Policy());  // returns n - k
        return result + k;
      } // RealType find_number_of_trials complemented

    private:
      RealType m_r; // successes.
      RealType m_p; // success_fraction
    }; // template <class RealType, class Policy> class negative_binomial_distribution

    typedef negative_binomial_distribution<double> negative_binomial; // Reserved name of type double.

    template <class RealType, class Policy>
    inline const std::pair<RealType, RealType> range(const negative_binomial_distribution<RealType, Policy>& /* dist */)
    { // Range of permissible values for random variable k.
       using boost::math::tools::max_value;
       return std::pair<RealType, RealType>(static_cast<RealType>(0), max_value<RealType>()); // max_integer?
    }

    template <class RealType, class Policy>
    inline const std::pair<RealType, RealType> support(const negative_binomial_distribution<RealType, Policy>& /* dist */)
    { // Range of supported values for random variable k.
       // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
       using boost::math::tools::max_value;
       return std::pair<RealType, RealType>(static_cast<RealType>(0),  max_value<RealType>()); // max_integer?
    }

    template <class RealType, class Policy>
    inline RealType mean(const negative_binomial_distribution<RealType, Policy>& dist)
    { // Mean of Negative Binomial distribution = r(1-p)/p.
      return dist.successes() * (1 - dist.success_fraction() ) / dist.success_fraction();
    } // mean

    //template <class RealType, class Policy>
    //inline RealType median(const negative_binomial_distribution<RealType, Policy>& dist)
    //{ // Median of negative_binomial_distribution is not defined.
    //  return policies::raise_domain_error<RealType>(BOOST_CURRENT_FUNCTION, "Median is not implemented, result is %1%!", std::numeric_limits<RealType>::quiet_NaN());
    //} // median
    // Now implemented via quantile(half) in derived accessors.

    template <class RealType, class Policy>
    inline RealType mode(const negative_binomial_distribution<RealType, Policy>& dist)
    { // Mode of Negative Binomial distribution = floor[(r-1) * (1 - p)/p]
      BOOST_MATH_STD_USING // ADL of std functions.
      return floor((dist.successes() -1) * (1 - dist.success_fraction()) / dist.success_fraction());
    } // mode

    template <class RealType, class Policy>
    inline RealType skewness(const negative_binomial_distribution<RealType, Policy>& dist)
    { // skewness of Negative Binomial distribution = 2-p / (sqrt(r(1-p))
      BOOST_MATH_STD_USING // ADL of std functions.
      RealType p = dist.success_fraction();
      RealType r = dist.successes();

      return (2 - p) /
        sqrt(r * (1 - p));
    } // skewness

    template <class RealType, class Policy>
    inline RealType kurtosis(const negative_binomial_distribution<RealType, Policy>& dist)
    { // kurtosis of Negative Binomial distribution
      // http://en.wikipedia.org/wiki/Negative_binomial is kurtosis_excess so add 3
      RealType p = dist.success_fraction();
      RealType r = dist.successes();
      return 3 + (6 / r) + ((p * p) / (r * (1 - p)));
    } // kurtosis

     template <class RealType, class Policy>
    inline RealType kurtosis_excess(const negative_binomial_distribution<RealType, Policy>& dist)
    { // kurtosis excess of Negative Binomial distribution
      // http://mathworld.wolfram.com/Kurtosis.html table of kurtosis_excess
      RealType p = dist.success_fraction();
      RealType r = dist.successes();
      return (6 - p * (6-p)) / (r * (1-p));
    } // kurtosis_excess

    template <class RealType, class Policy>
    inline RealType variance(const negative_binomial_distribution<RealType, Policy>& dist)
    { // Variance of Binomial distribution = r (1-p) / p^2.
      return  dist.successes() * (1 - dist.success_fraction())
        / (dist.success_fraction() * dist.success_fraction());
    } // variance

    // RealType standard_deviation(const negative_binomial_distribution<RealType, Policy>& dist)
    // standard_deviation provided by derived accessors.
    // RealType hazard(const negative_binomial_distribution<RealType, Policy>& dist)
    // hazard of Negative Binomial distribution provided by derived accessors.
    // RealType chf(const negative_binomial_distribution<RealType, Policy>& dist)
    // chf of Negative Binomial distribution provided by derived accessors.

    template <class RealType, class Policy>
    inline RealType pdf(const negative_binomial_distribution<RealType, Policy>& dist, const RealType& k)
    { // Probability Density/Mass Function.
      BOOST_FPU_EXCEPTION_GUARD

      static const char* function = "boost::math::pdf(const negative_binomial_distribution<%1%>&, %1%)";

      RealType r = dist.successes();
      RealType p = dist.success_fraction();
      RealType result = 0;
      if(false == negative_binomial_detail::check_dist_and_k(
        function,
        r,
        dist.success_fraction(),
        k,
        &result, Policy()))
      {
        return result;
      }

      result = (p/(r + k)) * ibeta_derivative(r, static_cast<RealType>(k+1), p, Policy());
      // Equivalent to:
      // return exp(lgamma(r + k) - lgamma(r) - lgamma(k+1)) * pow(p, r) * pow((1-p), k);
      return result;
    } // negative_binomial_pdf

    template <class RealType, class Policy>
    inline RealType cdf(const negative_binomial_distribution<RealType, Policy>& dist, const RealType& k)
    { // Cumulative Distribution Function of Negative Binomial.
      static const char* function = "boost::math::cdf(const negative_binomial_distribution<%1%>&, %1%)";
      using boost::math::ibeta; // Regularized incomplete beta function.
      // k argument may be integral, signed, or unsigned, or floating point.
      // If necessary, it has already been promoted from an integral type.
      RealType p = dist.success_fraction();
      RealType r = dist.successes();
      // Error check:
      RealType result = 0;
      if(false == negative_binomial_detail::check_dist_and_k(
        function,
        r,
        dist.success_fraction(),
        k,
        &result, Policy()))
      {
        return result;
      }

      RealType probability = ibeta(r, static_cast<RealType>(k+1), p, Policy());
      // Ip(r, k+1) = ibeta(r, k+1, p)
      return probability;
    } // cdf Cumulative Distribution Function Negative Binomial.

      template <class RealType, class Policy>
      inline RealType cdf(const complemented2_type<negative_binomial_distribution<RealType, Policy>, RealType>& c)
      { // Complemented Cumulative Distribution Function Negative Binomial.

      static const char* function = "boost::math::cdf(const negative_binomial_distribution<%1%>&, %1%)";
      using boost::math::ibetac; // Regularized incomplete beta function complement.
      // k argument may be integral, signed, or unsigned, or floating point.
      // If necessary, it has already been promoted from an integral type.
      RealType const& k = c.param;
      negative_binomial_distribution<RealType, Policy> const& dist = c.dist;
      RealType p = dist.success_fraction();
      RealType r = dist.successes();
      // Error check:
      RealType result = 0;
      if(false == negative_binomial_detail::check_dist_and_k(
        function,
        r,
        p,
        k,
        &result, Policy()))
      {
        return result;
      }
      // Calculate cdf negative binomial using the incomplete beta function.
      // Use of ibeta here prevents cancellation errors in calculating
      // 1-p if p is very small, perhaps smaller than machine epsilon.
      // Ip(k+1, r) = ibetac(r, k+1, p)
      // constrain_probability here?
     RealType probability = ibetac(r, static_cast<RealType>(k+1), p, Policy());
      // Numerical errors might cause probability to be slightly outside the range < 0 or > 1.
      // This might cause trouble downstream, so warn, possibly throw exception, but constrain to the limits.
      return probability;
    } // cdf Cumulative Distribution Function Negative Binomial.

    template <class RealType, class Policy>
    inline RealType quantile(const negative_binomial_distribution<RealType, Policy>& dist, const RealType& P)
    { // Quantile, percentile/100 or Percent Point Negative Binomial function.
      // Return the number of expected failures k for a given probability p.

      // Inverse cumulative Distribution Function or Quantile (percentile / 100) of negative_binomial Probability.
      // MAthCAD pnbinom return smallest k such that negative_binomial(k, n, p) >= probability.
      // k argument may be integral, signed, or unsigned, or floating point.
      // BUT Cephes/CodeCogs says: finds argument p (0 to 1) such that cdf(k, n, p) = y
      static const char* function = "boost::math::quantile(const negative_binomial_distribution<%1%>&, %1%)";
      BOOST_MATH_STD_USING // ADL of std functions.

      RealType p = dist.success_fraction();
      RealType r = dist.successes();
      // Check dist and P.
      RealType result = 0;
      if(false == negative_binomial_detail::check_dist_and_prob
        (function, r, p, P, &result, Policy()))
      {
        return result;
      }

      // Special cases.
      if (P == 1)
      {  // Would need +infinity failures for total confidence.
        result = policies::raise_overflow_error<RealType>(
            function,
            "Probability argument is 1, which implies infinite failures !", Policy());
        return result;
       // usually means return +std::numeric_limits<RealType>::infinity();
       // unless #define BOOST_MATH_THROW_ON_OVERFLOW_ERROR
      }
      if (P == 0)
      { // No failures are expected if P = 0.
        return 0; // Total trials will be just dist.successes.
      }
      if (P <= pow(dist.success_fraction(), dist.successes()))
      { // p <= pdf(dist, 0) == cdf(dist, 0)
        return 0;
      }
      if(p == 0)
      {  // Would need +infinity failures for total confidence.
         result = policies::raise_overflow_error<RealType>(
            function,
            "Success fraction is 0, which implies infinite failures !", Policy());
         return result;
         // usually means return +std::numeric_limits<RealType>::infinity();
         // unless #define BOOST_MATH_THROW_ON_OVERFLOW_ERROR
      }
      /*
      // Calculate quantile of negative_binomial using the inverse incomplete beta function.
      using boost::math::ibeta_invb;
      return ibeta_invb(r, p, P, Policy()) - 1; //
      */
      RealType guess = 0;
      RealType factor = 5;
      if(r * r * r * P * p > 0.005)
         guess = detail::inverse_negative_binomial_cornish_fisher(r, p, RealType(1-p), P, RealType(1-P), Policy());

      if(guess < 10)
      {
         //
         // Cornish-Fisher Negative binomial approximation not accurate in this area:
         //
         guess = (std::min)(RealType(r * 2), RealType(10));
      }
      else
         factor = (1-P < sqrt(tools::epsilon<RealType>())) ? 2 : (guess < 20 ? 1.2f : 1.1f);
      BOOST_MATH_INSTRUMENT_CODE("guess = " << guess);
      //
      // Max iterations permitted:
      //
      boost::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
      typedef typename Policy::discrete_quantile_type discrete_type;
      return detail::inverse_discrete_quantile(
         dist,
         P,
         false,
         guess,
         factor,
         RealType(1),
         discrete_type(),
         max_iter);
    } // RealType quantile(const negative_binomial_distribution dist, p)

    template <class RealType, class Policy>
    inline RealType quantile(const complemented2_type<negative_binomial_distribution<RealType, Policy>, RealType>& c)
    {  // Quantile or Percent Point Binomial function.
       // Return the number of expected failures k for a given
       // complement of the probability Q = 1 - P.
       static const char* function = "boost::math::quantile(const negative_binomial_distribution<%1%>&, %1%)";
       BOOST_MATH_STD_USING

       // Error checks:
       RealType Q = c.param;
       const negative_binomial_distribution<RealType, Policy>& dist = c.dist;
       RealType p = dist.success_fraction();
       RealType r = dist.successes();
       RealType result = 0;
       if(false == negative_binomial_detail::check_dist_and_prob(
          function,
          r,
          p,
          Q,
          &result, Policy()))
       {
          return result;
       }

       // Special cases:
       //
       if(Q == 1)
       {  // There may actually be no answer to this question,
          // since the probability of zero failures may be non-zero,
          return 0; // but zero is the best we can do:
       }
       if(Q == 0)
       {  // Probability 1 - Q  == 1 so infinite failures to achieve certainty.
          // Would need +infinity failures for total confidence.
          result = policies::raise_overflow_error<RealType>(
             function,
             "Probability argument complement is 0, which implies infinite failures !", Policy());
          return result;
          // usually means return +std::numeric_limits<RealType>::infinity();
          // unless #define BOOST_MATH_THROW_ON_OVERFLOW_ERROR
       }
       if (-Q <= boost::math::powm1(dist.success_fraction(), dist.successes(), Policy()))
       {  // q <= cdf(complement(dist, 0)) == pdf(dist, 0)
          return 0; //
       }
       if(p == 0)
       {  // Success fraction is 0 so infinite failures to achieve certainty.
          // Would need +infinity failures for total confidence.
          result = policies::raise_overflow_error<RealType>(
             function,
             "Success fraction is 0, which implies infinite failures !", Policy());
          return result;
          // usually means return +std::numeric_limits<RealType>::infinity();
          // unless #define BOOST_MATH_THROW_ON_OVERFLOW_ERROR
       }
       //return ibetac_invb(r, p, Q, Policy()) -1;
       RealType guess = 0;
       RealType factor = 5;
       if(r * r * r * (1-Q) * p > 0.005)
          guess = detail::inverse_negative_binomial_cornish_fisher(r, p, RealType(1-p), RealType(1-Q), Q, Policy());

       if(guess < 10)
       {
          //
          // Cornish-Fisher Negative binomial approximation not accurate in this area:
          //
          guess = (std::min)(RealType(r * 2), RealType(10));
       }
       else
          factor = (Q < sqrt(tools::epsilon<RealType>())) ? 2 : (guess < 20 ? 1.2f : 1.1f);
       BOOST_MATH_INSTRUMENT_CODE("guess = " << guess);
       //
       // Max iterations permitted:
       //
       boost::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
       typedef typename Policy::discrete_quantile_type discrete_type;
       return detail::inverse_discrete_quantile(
          dist,
          Q,
          true,
          guess,
          factor,
          RealType(1),
          discrete_type(),
          max_iter);
    } // quantile complement

 } // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#if defined (BOOST_MSVC)
# pragma warning(pop)
#endif

#endif // BOOST_MATH_SPECIAL_NEGATIVE_BINOMIAL_HPP

/* negative_binomial.hpp
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
*/