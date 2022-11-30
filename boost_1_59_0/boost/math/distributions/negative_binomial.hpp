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

    #ifdef __cpp_deduction_guides
    template <class RealType>
    negative_binomial_distribution(RealType,RealType)->negative_binomial_distribution<typename boost::math::tools::promote_args<RealType>::type>;
    #endif

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
      std::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
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
       std::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
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