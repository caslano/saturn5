// boost\math\distributions\geometric.hpp

// Copyright John Maddock 2010.
// Copyright Paul A. Bristow 2010.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// geometric distribution is a discrete probability distribution.
// It expresses the probability distribution of the number (k) of
// events, occurrences, failures or arrivals before the first success.
// supported on the set {0, 1, 2, 3...}

// Note that the set includes zero (unlike some definitions that start at one).

// The random variate k is the number of events, occurrences or arrivals.
// k argument may be integral, signed, or unsigned, or floating point.
// If necessary, it has already been promoted from an integral type.

// Note that the geometric distribution
// (like others including the binomial, geometric & Bernoulli)
// is strictly defined as a discrete function:
// only integral values of k are envisaged.
// However because the method of calculation uses a continuous gamma function,
// it is convenient to treat it as if a continuous function,
// and permit non-integral values of k.
// To enforce the strict mathematical model, users should use floor or ceil functions
// on k outside this function to ensure that k is integral.

// See http://en.wikipedia.org/wiki/geometric_distribution
// http://documents.wolfram.com/v5/Add-onsLinks/StandardPackages/Statistics/DiscreteDistributions.html
// http://mathworld.wolfram.com/GeometricDistribution.html

#ifndef BOOST_MATH_SPECIAL_GEOMETRIC_HPP
#define BOOST_MATH_SPECIAL_GEOMETRIC_HPP

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
    namespace geometric_detail
    {
      // Common error checking routines for geometric distribution function:
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
      inline bool check_dist(const char* function, const RealType& p, RealType* result, const Policy& pol)
      {
        return check_success_fraction(function, p, result, pol);
      }

      template <class RealType, class Policy>
      inline bool check_dist_and_k(const char* function,  const RealType& p, RealType k, RealType* result, const Policy& pol)
      {
        if(check_dist(function, p, result, pol) == false)
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
      inline bool check_dist_and_prob(const char* function, RealType p, RealType prob, RealType* result, const Policy& pol)
      {
        if((check_dist(function, p, result, pol) && detail::check_probability(function, prob, result, pol)) == false)
        {
          return false;
        }
        return true;
      } // check_dist_and_prob
    } //  namespace geometric_detail

    template <class RealType = double, class Policy = policies::policy<> >
    class geometric_distribution
    {
    public:
      typedef RealType value_type;
      typedef Policy policy_type;

      geometric_distribution(RealType p) : m_p(p)
      { // Constructor stores success_fraction p.
        RealType result;
        geometric_detail::check_dist(
          "geometric_distribution<%1%>::geometric_distribution",
          m_p, // Check success_fraction 0 <= p <= 1.
          &result, Policy());
      } // geometric_distribution constructor.

      // Private data getter class member functions.
      RealType success_fraction() const
      { // Probability of success as fraction in range 0 to 1.
        return m_p;
      }
      RealType successes() const
      { // Total number of successes r = 1 (for compatibility with negative binomial?).
        return 1;
      }

      // Parameter estimation.
      // (These are copies of negative_binomial distribution with successes = 1).
      static RealType find_lower_bound_on_p(
        RealType trials,
        RealType alpha) // alpha 0.05 equivalent to 95% for one-sided test.
      {
        static const char* function = "boost::math::geometric<%1%>::find_lower_bound_on_p";
        RealType result = 0;  // of error checks.
        RealType successes = 1;
        RealType failures = trials - successes;
        if(false == detail::check_probability(function, alpha, &result, Policy())
          && geometric_detail::check_dist_and_k(
          function, RealType(0), failures, &result, Policy()))
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
        RealType alpha) // alpha 0.05 equivalent to 95% for one-sided test.
      {
        static const char* function = "boost::math::geometric<%1%>::find_upper_bound_on_p";
        RealType result = 0;  // of error checks.
        RealType successes = 1;
        RealType failures = trials - successes;
        if(false == geometric_detail::check_dist_and_k(
          function, RealType(0), failures, &result, Policy())
          && detail::check_probability(function, alpha, &result, Policy()))
        {
          return result;
        }
        if(failures == 0)
        {
           return 1;
        }// Use complement ibetac_inv function for upper bound.
        // Note adjusted failures value: *not* failures+1 as usual.
        // This is adapted from the corresponding binomial formula
        // here: http://www.itl.nist.gov/div898/handbook/prc/section2/prc241.htm
        // This is a Clopper-Pearson interval, and may be overly conservative,
        // see also "A Simple Improved Inferential Method for Some
        // Discrete Distributions" Yong CAI and K. Krishnamoorthy
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
        static const char* function = "boost::math::geometric<%1%>::find_minimum_number_of_trials";
        // Error checks:
        RealType result = 0;
        if(false == geometric_detail::check_dist_and_k(
          function, p, k, &result, Policy())
          && detail::check_probability(function, alpha, &result, Policy()))
        {
          return result;
        }
        result = ibeta_inva(k + 1, p, alpha, Policy());  // returns n - k
        return result + k;
      } // RealType find_number_of_failures

      static RealType find_maximum_number_of_trials(
        RealType k,     // number of failures (k >= 0).
        RealType p,     // success fraction 0 <= p <= 1.
        RealType alpha) // risk level threshold 0 <= alpha <= 1.
      {
        static const char* function = "boost::math::geometric<%1%>::find_maximum_number_of_trials";
        // Error checks:
        RealType result = 0;
        if(false == geometric_detail::check_dist_and_k(
          function, p, k, &result, Policy())
          &&  detail::check_probability(function, alpha, &result, Policy()))
        { 
          return result;
        }
        result = ibetac_inva(k + 1, p, alpha, Policy());  // returns n - k
        return result + k;
      } // RealType find_number_of_trials complemented

    private:
      //RealType m_r; // successes fixed at unity.
      RealType m_p; // success_fraction
    }; // template <class RealType, class Policy> class geometric_distribution

    typedef geometric_distribution<double> geometric; // Reserved name of type double.

    #ifdef __cpp_deduction_guides
    template <class RealType>
    geometric_distribution(RealType)->geometric_distribution<typename boost::math::tools::promote_args<RealType>::type>;
    #endif

    template <class RealType, class Policy>
    inline const std::pair<RealType, RealType> range(const geometric_distribution<RealType, Policy>& /* dist */)
    { // Range of permissible values for random variable k.
       using boost::math::tools::max_value;
       return std::pair<RealType, RealType>(static_cast<RealType>(0), max_value<RealType>()); // max_integer?
    }

    template <class RealType, class Policy>
    inline const std::pair<RealType, RealType> support(const geometric_distribution<RealType, Policy>& /* dist */)
    { // Range of supported values for random variable k.
       // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
       using boost::math::tools::max_value;
       return std::pair<RealType, RealType>(static_cast<RealType>(0),  max_value<RealType>()); // max_integer?
    }

    template <class RealType, class Policy>
    inline RealType mean(const geometric_distribution<RealType, Policy>& dist)
    { // Mean of geometric distribution = (1-p)/p.
      return (1 - dist.success_fraction() ) / dist.success_fraction();
    } // mean

    // median implemented via quantile(half) in derived accessors.

    template <class RealType, class Policy>
    inline RealType mode(const geometric_distribution<RealType, Policy>&)
    { // Mode of geometric distribution = zero.
      BOOST_MATH_STD_USING // ADL of std functions.
      return 0;
    } // mode
    
    template <class RealType, class Policy>
    inline RealType variance(const geometric_distribution<RealType, Policy>& dist)
    { // Variance of Binomial distribution = (1-p) / p^2.
      return  (1 - dist.success_fraction())
        / (dist.success_fraction() * dist.success_fraction());
    } // variance

    template <class RealType, class Policy>
    inline RealType skewness(const geometric_distribution<RealType, Policy>& dist)
    { // skewness of geometric distribution = 2-p / (sqrt(r(1-p))
      BOOST_MATH_STD_USING // ADL of std functions.
      RealType p = dist.success_fraction();
      return (2 - p) / sqrt(1 - p);
    } // skewness

    template <class RealType, class Policy>
    inline RealType kurtosis(const geometric_distribution<RealType, Policy>& dist)
    { // kurtosis of geometric distribution
      // http://en.wikipedia.org/wiki/geometric is kurtosis_excess so add 3
      RealType p = dist.success_fraction();
      return 3 + (p*p - 6*p + 6) / (1 - p);
    } // kurtosis

     template <class RealType, class Policy>
    inline RealType kurtosis_excess(const geometric_distribution<RealType, Policy>& dist)
    { // kurtosis excess of geometric distribution
      // http://mathworld.wolfram.com/Kurtosis.html table of kurtosis_excess
      RealType p = dist.success_fraction();
      return (p*p - 6*p + 6) / (1 - p);
    } // kurtosis_excess

    // RealType standard_deviation(const geometric_distribution<RealType, Policy>& dist)
    // standard_deviation provided by derived accessors.
    // RealType hazard(const geometric_distribution<RealType, Policy>& dist)
    // hazard of geometric distribution provided by derived accessors.
    // RealType chf(const geometric_distribution<RealType, Policy>& dist)
    // chf of geometric distribution provided by derived accessors.

    template <class RealType, class Policy>
    inline RealType pdf(const geometric_distribution<RealType, Policy>& dist, const RealType& k)
    { // Probability Density/Mass Function.
      BOOST_FPU_EXCEPTION_GUARD
      BOOST_MATH_STD_USING  // For ADL of math functions.
      static const char* function = "boost::math::pdf(const geometric_distribution<%1%>&, %1%)";

      RealType p = dist.success_fraction();
      RealType result = 0;
      if(false == geometric_detail::check_dist_and_k(
        function,
        p,
        k,
        &result, Policy()))
      {
        return result;
      }
      if (k == 0)
      {
        return p; // success_fraction
      }
      RealType q = 1 - p;  // Inaccurate for small p?
      // So try to avoid inaccuracy for large or small p.
      // but has little effect > last significant bit.
      //cout << "p *  pow(q, k) " << result << endl; // seems best whatever p
      //cout << "exp(p * k * log1p(-p)) " << p * exp(k * log1p(-p)) << endl;
      //if (p < 0.5)
      //{
      //  result = p *  pow(q, k);
      //}
      //else
      //{
      //  result = p * exp(k * log1p(-p));
      //}
      result = p * pow(q, k);
      return result;
    } // geometric_pdf

    template <class RealType, class Policy>
    inline RealType cdf(const geometric_distribution<RealType, Policy>& dist, const RealType& k)
    { // Cumulative Distribution Function of geometric.
      static const char* function = "boost::math::cdf(const geometric_distribution<%1%>&, %1%)";

      // k argument may be integral, signed, or unsigned, or floating point.
      // If necessary, it has already been promoted from an integral type.
      RealType p = dist.success_fraction();
      // Error check:
      RealType result = 0;
      if(false == geometric_detail::check_dist_and_k(
        function,
        p,
        k,
        &result, Policy()))
      {
        return result;
      }
      if(k == 0)
      {
        return p; // success_fraction
      }
      //RealType q = 1 - p;  // Bad for small p
      //RealType probability = 1 - std::pow(q, k+1);

      RealType z = boost::math::log1p(-p, Policy()) * (k + 1);
      RealType probability = -boost::math::expm1(z, Policy());

      return probability;
    } // cdf Cumulative Distribution Function geometric.

      template <class RealType, class Policy>
      inline RealType cdf(const complemented2_type<geometric_distribution<RealType, Policy>, RealType>& c)
      { // Complemented Cumulative Distribution Function geometric.
      BOOST_MATH_STD_USING
      static const char* function = "boost::math::cdf(const geometric_distribution<%1%>&, %1%)";
      // k argument may be integral, signed, or unsigned, or floating point.
      // If necessary, it has already been promoted from an integral type.
      RealType const& k = c.param;
      geometric_distribution<RealType, Policy> const& dist = c.dist;
      RealType p = dist.success_fraction();
      // Error check:
      RealType result = 0;
      if(false == geometric_detail::check_dist_and_k(
        function,
        p,
        k,
        &result, Policy()))
      {
        return result;
      }
      RealType z = boost::math::log1p(-p, Policy()) * (k+1);
      RealType probability = exp(z);
      return probability;
    } // cdf Complemented Cumulative Distribution Function geometric.

    template <class RealType, class Policy>
    inline RealType quantile(const geometric_distribution<RealType, Policy>& dist, const RealType& x)
    { // Quantile, percentile/100 or Percent Point geometric function.
      // Return the number of expected failures k for a given probability p.

      // Inverse cumulative Distribution Function or Quantile (percentile / 100) of geometric Probability.
      // k argument may be integral, signed, or unsigned, or floating point.

      static const char* function = "boost::math::quantile(const geometric_distribution<%1%>&, %1%)";
      BOOST_MATH_STD_USING // ADL of std functions.

      RealType success_fraction = dist.success_fraction();
      // Check dist and x.
      RealType result = 0;
      if(false == geometric_detail::check_dist_and_prob
        (function, success_fraction, x, &result, Policy()))
      {
        return result;
      }

      // Special cases.
      if (x == 1)
      {  // Would need +infinity failures for total confidence.
        result = policies::raise_overflow_error<RealType>(
            function,
            "Probability argument is 1, which implies infinite failures !", Policy());
        return result;
       // usually means return +std::numeric_limits<RealType>::infinity();
       // unless #define BOOST_MATH_THROW_ON_OVERFLOW_ERROR
      }
      if (x == 0)
      { // No failures are expected if P = 0.
        return 0; // Total trials will be just dist.successes.
      }
      // if (P <= pow(dist.success_fraction(), 1))
      if (x <= success_fraction)
      { // p <= pdf(dist, 0) == cdf(dist, 0)
        return 0;
      }
      if (x == 1)
      {
        return 0;
      }
   
      // log(1-x) /log(1-success_fraction) -1; but use log1p in case success_fraction is small
      result = boost::math::log1p(-x, Policy()) / boost::math::log1p(-success_fraction, Policy()) - 1;
      // Subtract a few epsilons here too?
      // to make sure it doesn't slip over, so ceil would be one too many.
      return result;
    } // RealType quantile(const geometric_distribution dist, p)

    template <class RealType, class Policy>
    inline RealType quantile(const complemented2_type<geometric_distribution<RealType, Policy>, RealType>& c)
    {  // Quantile or Percent Point Binomial function.
       // Return the number of expected failures k for a given
       // complement of the probability Q = 1 - P.
       static const char* function = "boost::math::quantile(const geometric_distribution<%1%>&, %1%)";
       BOOST_MATH_STD_USING
       // Error checks:
       RealType x = c.param;
       const geometric_distribution<RealType, Policy>& dist = c.dist;
       RealType success_fraction = dist.success_fraction();
       RealType result = 0;
       if(false == geometric_detail::check_dist_and_prob(
          function,
          success_fraction,
          x,
          &result, Policy()))
       {
          return result;
       }

       // Special cases:
       if(x == 1)
       {  // There may actually be no answer to this question,
          // since the probability of zero failures may be non-zero,
          return 0; // but zero is the best we can do:
       }
       if (-x <= boost::math::powm1(dist.success_fraction(), dist.successes(), Policy()))
       {  // q <= cdf(complement(dist, 0)) == pdf(dist, 0)
          return 0; //
       }
       if(x == 0)
       {  // Probability 1 - Q  == 1 so infinite failures to achieve certainty.
          // Would need +infinity failures for total confidence.
          result = policies::raise_overflow_error<RealType>(
             function,
             "Probability argument complement is 0, which implies infinite failures !", Policy());
          return result;
          // usually means return +std::numeric_limits<RealType>::infinity();
          // unless #define BOOST_MATH_THROW_ON_OVERFLOW_ERROR
       }
       // log(x) /log(1-success_fraction) -1; but use log1p in case success_fraction is small
       result = log(x) / boost::math::log1p(-success_fraction, Policy()) - 1;
      return result;

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

#endif // BOOST_MATH_SPECIAL_GEOMETRIC_HPP

/* geometric.hpp
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
*/