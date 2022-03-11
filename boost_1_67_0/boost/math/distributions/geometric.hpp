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