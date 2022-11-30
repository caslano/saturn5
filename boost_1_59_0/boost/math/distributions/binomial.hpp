// boost\math\distributions\binomial.hpp

// Copyright John Maddock 2006.
// Copyright Paul A. Bristow 2007.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// http://en.wikipedia.org/wiki/binomial_distribution

// Binomial distribution is the discrete probability distribution of
// the number (k) of successes, in a sequence of
// n independent (yes or no, success or failure) Bernoulli trials.

// It expresses the probability of a number of events occurring in a fixed time
// if these events occur with a known average rate (probability of success),
// and are independent of the time since the last event.

// The number of cars that pass through a certain point on a road during a given period of time.
// The number of spelling mistakes a secretary makes while typing a single page.
// The number of phone calls at a call center per minute.
// The number of times a web server is accessed per minute.
// The number of light bulbs that burn out in a certain amount of time.
// The number of roadkill found per unit length of road

// http://en.wikipedia.org/wiki/binomial_distribution

// Given a sample of N measured values k[i],
// we wish to estimate the value of the parameter x (mean)
// of the binomial population from which the sample was drawn.
// To calculate the maximum likelihood value = 1/N sum i = 1 to N of k[i]

// Also may want a function for EXACTLY k.

// And probability that there are EXACTLY k occurrences is
// exp(-x) * pow(x, k) / factorial(k)
// where x is expected occurrences (mean) during the given interval.
// For example, if events occur, on average, every 4 min,
// and we are interested in number of events occurring in 10 min,
// then x = 10/4 = 2.5

// http://www.itl.nist.gov/div898/handbook/eda/section3/eda366i.htm

// The binomial distribution is used when there are
// exactly two mutually exclusive outcomes of a trial.
// These outcomes are appropriately labeled "success" and "failure".
// The binomial distribution is used to obtain
// the probability of observing x successes in N trials,
// with the probability of success on a single trial denoted by p.
// The binomial distribution assumes that p is fixed for all trials.

// P(x, p, n) = n!/(x! * (n-x)!) * p^x * (1-p)^(n-x)

// http://mathworld.wolfram.com/BinomialCoefficient.html

// The binomial coefficient (n; k) is the number of ways of picking
// k unordered outcomes from n possibilities,
// also known as a combination or combinatorial number.
// The symbols _nC_k and (n; k) are used to denote a binomial coefficient,
// and are sometimes read as "n choose k."
// (n; k) therefore gives the number of k-subsets  possible out of a set of n distinct items.

// For example:
//  The 2-subsets of {1,2,3,4} are the six pairs {1,2}, {1,3}, {1,4}, {2,3}, {2,4}, and {3,4}, so (4; 2)==6.

// http://functions.wolfram.com/GammaBetaErf/Binomial/ for evaluation.

// But note that the binomial distribution
// (like others including the poisson, negative binomial & Bernoulli)
// is strictly defined as a discrete function: only integral values of k are envisaged.
// However because of the method of calculation using a continuous gamma function,
// it is convenient to treat it as if a continuous function,
// and permit non-integral values of k.
// To enforce the strict mathematical model, users should use floor or ceil functions
// on k outside this function to ensure that k is integral.

#ifndef BOOST_MATH_SPECIAL_BINOMIAL_HPP
#define BOOST_MATH_SPECIAL_BINOMIAL_HPP

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/beta.hpp> // for incomplete beta.
#include <boost/math/distributions/complement.hpp> // complements
#include <boost/math/distributions/detail/common_error_handling.hpp> // error checks
#include <boost/math/distributions/detail/inv_discrete_quantile.hpp> // error checks
#include <boost/math/special_functions/fpclassify.hpp> // isnan.
#include <boost/math/tools/roots.hpp> // for root finding.

#include <utility>

namespace boost
{
  namespace math
  {

     template <class RealType, class Policy>
     class binomial_distribution;

     namespace binomial_detail{
        // common error checking routines for binomial distribution functions:
        template <class RealType, class Policy>
        inline bool check_N(const char* function, const RealType& N, RealType* result, const Policy& pol)
        {
           if((N < 0) || !(boost::math::isfinite)(N))
           {
               *result = policies::raise_domain_error<RealType>(
                  function,
                  "Number of Trials argument is %1%, but must be >= 0 !", N, pol);
               return false;
           }
           return true;
        }
        template <class RealType, class Policy>
        inline bool check_success_fraction(const char* function, const RealType& p, RealType* result, const Policy& pol)
        {
           if((p < 0) || (p > 1) || !(boost::math::isfinite)(p))
           {
               *result = policies::raise_domain_error<RealType>(
                  function,
                  "Success fraction argument is %1%, but must be >= 0 and <= 1 !", p, pol);
               return false;
           }
           return true;
        }
        template <class RealType, class Policy>
        inline bool check_dist(const char* function, const RealType& N, const RealType& p, RealType* result, const Policy& pol)
        {
           return check_success_fraction(
              function, p, result, pol)
              && check_N(
               function, N, result, pol);
        }
        template <class RealType, class Policy>
        inline bool check_dist_and_k(const char* function, const RealType& N, const RealType& p, RealType k, RealType* result, const Policy& pol)
        {
           if(check_dist(function, N, p, result, pol) == false)
              return false;
           if((k < 0) || !(boost::math::isfinite)(k))
           {
               *result = policies::raise_domain_error<RealType>(
                  function,
                  "Number of Successes argument is %1%, but must be >= 0 !", k, pol);
               return false;
           }
           if(k > N)
           {
               *result = policies::raise_domain_error<RealType>(
                  function,
                  "Number of Successes argument is %1%, but must be <= Number of Trials !", k, pol);
               return false;
           }
           return true;
        }
        template <class RealType, class Policy>
        inline bool check_dist_and_prob(const char* function, const RealType& N, RealType p, RealType prob, RealType* result, const Policy& pol)
        {
           if((check_dist(function, N, p, result, pol) && detail::check_probability(function, prob, result, pol)) == false)
              return false;
           return true;
        }

         template <class T, class Policy>
         T inverse_binomial_cornish_fisher(T n, T sf, T p, T q, const Policy& pol)
         {
            BOOST_MATH_STD_USING
            // mean:
            T m = n * sf;
            // standard deviation:
            T sigma = sqrt(n * sf * (1 - sf));
            // skewness
            T sk = (1 - 2 * sf) / sigma;
            // kurtosis:
            // T k = (1 - 6 * sf * (1 - sf) ) / (n * sf * (1 - sf));
            // Get the inverse of a std normal distribution:
            T x = boost::math::erfc_inv(p > q ? 2 * q : 2 * p, pol) * constants::root_two<T>();
            // Set the sign:
            if(p < 0.5)
               x = -x;
            T x2 = x * x;
            // w is correction term due to skewness
            T w = x + sk * (x2 - 1) / 6;
            /*
            // Add on correction due to kurtosis.
            // Disabled for now, seems to make things worse?
            //
            if(n >= 10)
               w += k * x * (x2 - 3) / 24 + sk * sk * x * (2 * x2 - 5) / -36;
               */
            w = m + sigma * w;
            if(w < tools::min_value<T>())
               return sqrt(tools::min_value<T>());
            if(w > n)
               return n;
            return w;
         }

      template <class RealType, class Policy>
      RealType quantile_imp(const binomial_distribution<RealType, Policy>& dist, const RealType& p, const RealType& q, bool comp)
      { // Quantile or Percent Point Binomial function.
        // Return the number of expected successes k,
        // for a given probability p.
        //
        // Error checks:
        BOOST_MATH_STD_USING  // ADL of std names
        RealType result = 0;
        RealType trials = dist.trials();
        RealType success_fraction = dist.success_fraction();
        if(false == binomial_detail::check_dist_and_prob(
           "boost::math::quantile(binomial_distribution<%1%> const&, %1%)",
           trials,
           success_fraction,
           p,
           &result, Policy()))
        {
           return result;
        }

        // Special cases:
        //
        if(p == 0)
        {  // There may actually be no answer to this question,
           // since the probability of zero successes may be non-zero,
           // but zero is the best we can do:
           return 0;
        }
        if(p == 1)
        {  // Probability of n or fewer successes is always one,
           // so n is the most sensible answer here:
           return trials;
        }
        if (p <= pow(1 - success_fraction, trials))
        { // p <= pdf(dist, 0) == cdf(dist, 0)
          return 0; // So the only reasonable result is zero.
        } // And root finder would fail otherwise.
        if(success_fraction == 1)
        {  // our formulae break down in this case:
           return p > 0.5f ? trials : 0;
        }

        // Solve for quantile numerically:
        //
        RealType guess = binomial_detail::inverse_binomial_cornish_fisher(trials, success_fraction, p, q, Policy());
        RealType factor = 8;
        if(trials > 100)
           factor = 1.01f; // guess is pretty accurate
        else if((trials > 10) && (trials - 1 > guess) && (guess > 3))
           factor = 1.15f; // less accurate but OK.
        else if(trials < 10)
        {
           // pretty inaccurate guess in this area:
           if(guess > trials / 64)
           {
              guess = trials / 4;
              factor = 2;
           }
           else
              guess = trials / 1024;
        }
        else
           factor = 2; // trials largish, but in far tails.

        typedef typename Policy::discrete_quantile_type discrete_quantile_type;
        std::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
        return detail::inverse_discrete_quantile(
            dist,
            comp ? q : p,
            comp,
            guess,
            factor,
            RealType(1),
            discrete_quantile_type(),
            max_iter);
      } // quantile

     }

    template <class RealType = double, class Policy = policies::policy<> >
    class binomial_distribution
    {
    public:
      typedef RealType value_type;
      typedef Policy policy_type;

      binomial_distribution(RealType n = 1, RealType p = 0.5) : m_n(n), m_p(p)
      { // Default n = 1 is the Bernoulli distribution
        // with equal probability of 'heads' or 'tails.
         RealType r;
         binomial_detail::check_dist(
            "boost::math::binomial_distribution<%1%>::binomial_distribution",
            m_n,
            m_p,
            &r, Policy());
      } // binomial_distribution constructor.

      RealType success_fraction() const
      { // Probability.
        return m_p;
      }
      RealType trials() const
      { // Total number of trials.
        return m_n;
      }

      enum interval_type{
         clopper_pearson_exact_interval,
         jeffreys_prior_interval
      };

      //
      // Estimation of the success fraction parameter.
      // The best estimate is actually simply successes/trials,
      // these functions are used
      // to obtain confidence intervals for the success fraction.
      //
      static RealType find_lower_bound_on_p(
         RealType trials,
         RealType successes,
         RealType probability,
         interval_type t = clopper_pearson_exact_interval)
      {
        static const char* function = "boost::math::binomial_distribution<%1%>::find_lower_bound_on_p";
        // Error checks:
        RealType result = 0;
        if(false == binomial_detail::check_dist_and_k(
           function, trials, RealType(0), successes, &result, Policy())
            &&
           binomial_detail::check_dist_and_prob(
           function, trials, RealType(0), probability, &result, Policy()))
        { return result; }

        if(successes == 0)
           return 0;

        // NOTE!!! The Clopper Pearson formula uses "successes" not
        // "successes+1" as usual to get the lower bound,
        // see http://www.itl.nist.gov/div898/handbook/prc/section2/prc241.htm
        return (t == clopper_pearson_exact_interval) ? ibeta_inv(successes, trials - successes + 1, probability, static_cast<RealType*>(0), Policy())
           : ibeta_inv(successes + 0.5f, trials - successes + 0.5f, probability, static_cast<RealType*>(0), Policy());
      }
      static RealType find_upper_bound_on_p(
         RealType trials,
         RealType successes,
         RealType probability,
         interval_type t = clopper_pearson_exact_interval)
      {
        static const char* function = "boost::math::binomial_distribution<%1%>::find_upper_bound_on_p";
        // Error checks:
        RealType result = 0;
        if(false == binomial_detail::check_dist_and_k(
           function, trials, RealType(0), successes, &result, Policy())
            &&
           binomial_detail::check_dist_and_prob(
           function, trials, RealType(0), probability, &result, Policy()))
        { return result; }

        if(trials == successes)
           return 1;

        return (t == clopper_pearson_exact_interval) ? ibetac_inv(successes + 1, trials - successes, probability, static_cast<RealType*>(0), Policy())
           : ibetac_inv(successes + 0.5f, trials - successes + 0.5f, probability, static_cast<RealType*>(0), Policy());
      }
      // Estimate number of trials parameter:
      //
      // "How many trials do I need to be P% sure of seeing k events?"
      //    or
      // "How many trials can I have to be P% sure of seeing fewer than k events?"
      //
      static RealType find_minimum_number_of_trials(
         RealType k,     // number of events
         RealType p,     // success fraction
         RealType alpha) // risk level
      {
        static const char* function = "boost::math::binomial_distribution<%1%>::find_minimum_number_of_trials";
        // Error checks:
        RealType result = 0;
        if(false == binomial_detail::check_dist_and_k(
           function, k, p, k, &result, Policy())
            &&
           binomial_detail::check_dist_and_prob(
           function, k, p, alpha, &result, Policy()))
        { return result; }

        result = ibetac_invb(k + 1, p, alpha, Policy());  // returns n - k
        return result + k;
      }

      static RealType find_maximum_number_of_trials(
         RealType k,     // number of events
         RealType p,     // success fraction
         RealType alpha) // risk level
      {
        static const char* function = "boost::math::binomial_distribution<%1%>::find_maximum_number_of_trials";
        // Error checks:
        RealType result = 0;
        if(false == binomial_detail::check_dist_and_k(
           function, k, p, k, &result, Policy())
            &&
           binomial_detail::check_dist_and_prob(
           function, k, p, alpha, &result, Policy()))
        { return result; }

        result = ibeta_invb(k + 1, p, alpha, Policy());  // returns n - k
        return result + k;
      }

    private:
        RealType m_n; // Not sure if this shouldn't be an int?
        RealType m_p; // success_fraction
      }; // template <class RealType, class Policy> class binomial_distribution

      typedef binomial_distribution<> binomial;
      // typedef binomial_distribution<double> binomial;
      // IS now included since no longer a name clash with function binomial.
      //typedef binomial_distribution<double> binomial; // Reserved name of type double.

      #ifdef __cpp_deduction_guides
      template <class RealType>
      binomial_distribution(RealType)->binomial_distribution<typename boost::math::tools::promote_args<RealType>::type>;
      template <class RealType>
      binomial_distribution(RealType,RealType)->binomial_distribution<typename boost::math::tools::promote_args<RealType>::type>;
      #endif

      template <class RealType, class Policy>
      const std::pair<RealType, RealType> range(const binomial_distribution<RealType, Policy>& dist)
      { // Range of permissible values for random variable k.
        using boost::math::tools::max_value;
        return std::pair<RealType, RealType>(static_cast<RealType>(0), dist.trials());
      }

      template <class RealType, class Policy>
      const std::pair<RealType, RealType> support(const binomial_distribution<RealType, Policy>& dist)
      { // Range of supported values for random variable k.
        // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
        return std::pair<RealType, RealType>(static_cast<RealType>(0),  dist.trials());
      }

      template <class RealType, class Policy>
      inline RealType mean(const binomial_distribution<RealType, Policy>& dist)
      { // Mean of Binomial distribution = np.
        return  dist.trials() * dist.success_fraction();
      } // mean

      template <class RealType, class Policy>
      inline RealType variance(const binomial_distribution<RealType, Policy>& dist)
      { // Variance of Binomial distribution = np(1-p).
        return  dist.trials() * dist.success_fraction() * (1 - dist.success_fraction());
      } // variance

      template <class RealType, class Policy>
      RealType pdf(const binomial_distribution<RealType, Policy>& dist, const RealType& k)
      { // Probability Density/Mass Function.
        BOOST_FPU_EXCEPTION_GUARD

        BOOST_MATH_STD_USING // for ADL of std functions

        RealType n = dist.trials();

        // Error check:
        RealType result = 0; // initialization silences some compiler warnings
        if(false == binomial_detail::check_dist_and_k(
           "boost::math::pdf(binomial_distribution<%1%> const&, %1%)",
           n,
           dist.success_fraction(),
           k,
           &result, Policy()))
        {
           return result;
        }

        // Special cases of success_fraction, regardless of k successes and regardless of n trials.
        if (dist.success_fraction() == 0)
        {  // probability of zero successes is 1:
           return static_cast<RealType>(k == 0 ? 1 : 0);
        }
        if (dist.success_fraction() == 1)
        {  // probability of n successes is 1:
           return static_cast<RealType>(k == n ? 1 : 0);
        }
        // k argument may be integral, signed, or unsigned, or floating point.
        // If necessary, it has already been promoted from an integral type.
        if (n == 0)
        {
          return 1; // Probability = 1 = certainty.
        }
        if (k == 0)
        { // binomial coeffic (n 0) = 1,
          // n ^ 0 = 1
          return pow(1 - dist.success_fraction(), n);
        }
        if (k == n)
        { // binomial coeffic (n n) = 1,
          // n ^ 0 = 1
          return pow(dist.success_fraction(), k);  // * pow((1 - dist.success_fraction()), (n - k)) = 1
        }

        // Probability of getting exactly k successes
        // if C(n, k) is the binomial coefficient then:
        //
        // f(k; n,p) = C(n, k) * p^k * (1-p)^(n-k)
        //           = (n!/(k!(n-k)!)) * p^k * (1-p)^(n-k)
        //           = (tgamma(n+1) / (tgamma(k+1)*tgamma(n-k+1))) * p^k * (1-p)^(n-k)
        //           = p^k (1-p)^(n-k) / (beta(k+1, n-k+1) * (n+1))
        //           = ibeta_derivative(k+1, n-k+1, p) / (n+1)
        //
        using boost::math::ibeta_derivative; // a, b, x
        return ibeta_derivative(k+1, n-k+1, dist.success_fraction(), Policy()) / (n+1);

      } // pdf

      template <class RealType, class Policy>
      inline RealType cdf(const binomial_distribution<RealType, Policy>& dist, const RealType& k)
      { // Cumulative Distribution Function Binomial.
        // The random variate k is the number of successes in n trials.
        // k argument may be integral, signed, or unsigned, or floating point.
        // If necessary, it has already been promoted from an integral type.

        // Returns the sum of the terms 0 through k of the Binomial Probability Density/Mass:
        //
        //   i=k
        //   --  ( n )   i      n-i
        //   >   |   |  p  (1-p)
        //   --  ( i )
        //   i=0

        // The terms are not summed directly instead
        // the incomplete beta integral is employed,
        // according to the formula:
        // P = I[1-p]( n-k, k+1).
        //   = 1 - I[p](k + 1, n - k)

        BOOST_MATH_STD_USING // for ADL of std functions

        RealType n = dist.trials();
        RealType p = dist.success_fraction();

        // Error check:
        RealType result = 0;
        if(false == binomial_detail::check_dist_and_k(
           "boost::math::cdf(binomial_distribution<%1%> const&, %1%)",
           n,
           p,
           k,
           &result, Policy()))
        {
           return result;
        }
        if (k == n)
        {
          return 1;
        }

        // Special cases, regardless of k.
        if (p == 0)
        {  // This need explanation:
           // the pdf is zero for all cases except when k == 0.
           // For zero p the probability of zero successes is one.
           // Therefore the cdf is always 1:
           // the probability of k or *fewer* successes is always 1
           // if there are never any successes!
           return 1;
        }
        if (p == 1)
        { // This is correct but needs explanation:
          // when k = 1
          // all the cdf and pdf values are zero *except* when k == n,
          // and that case has been handled above already.
          return 0;
        }
        //
        // P = I[1-p](n - k, k + 1)
        //   = 1 - I[p](k + 1, n - k)
        // Use of ibetac here prevents cancellation errors in calculating
        // 1-p if p is very small, perhaps smaller than machine epsilon.
        //
        // Note that we do not use a finite sum here, since the incomplete
        // beta uses a finite sum internally for integer arguments, so
        // we'll just let it take care of the necessary logic.
        //
        return ibetac(k + 1, n - k, p, Policy());
      } // binomial cdf

      template <class RealType, class Policy>
      inline RealType cdf(const complemented2_type<binomial_distribution<RealType, Policy>, RealType>& c)
      { // Complemented Cumulative Distribution Function Binomial.
        // The random variate k is the number of successes in n trials.
        // k argument may be integral, signed, or unsigned, or floating point.
        // If necessary, it has already been promoted from an integral type.

        // Returns the sum of the terms k+1 through n of the Binomial Probability Density/Mass:
        //
        //   i=n
        //   --  ( n )   i      n-i
        //   >   |   |  p  (1-p)
        //   --  ( i )
        //   i=k+1

        // The terms are not summed directly instead
        // the incomplete beta integral is employed,
        // according to the formula:
        // Q = 1 -I[1-p]( n-k, k+1).
        //   = I[p](k + 1, n - k)

        BOOST_MATH_STD_USING // for ADL of std functions

        RealType const& k = c.param;
        binomial_distribution<RealType, Policy> const& dist = c.dist;
        RealType n = dist.trials();
        RealType p = dist.success_fraction();

        // Error checks:
        RealType result = 0;
        if(false == binomial_detail::check_dist_and_k(
           "boost::math::cdf(binomial_distribution<%1%> const&, %1%)",
           n,
           p,
           k,
           &result, Policy()))
        {
           return result;
        }

        if (k == n)
        { // Probability of greater than n successes is necessarily zero:
          return 0;
        }

        // Special cases, regardless of k.
        if (p == 0)
        {
           // This need explanation: the pdf is zero for all
           // cases except when k == 0.  For zero p the probability
           // of zero successes is one.  Therefore the cdf is always
           // 1: the probability of *more than* k successes is always 0
           // if there are never any successes!
           return 0;
        }
        if (p == 1)
        {
          // This needs explanation, when p = 1
          // we always have n successes, so the probability
          // of more than k successes is 1 as long as k < n.
          // The k == n case has already been handled above.
          return 1;
        }
        //
        // Calculate cdf binomial using the incomplete beta function.
        // Q = 1 -I[1-p](n - k, k + 1)
        //   = I[p](k + 1, n - k)
        // Use of ibeta here prevents cancellation errors in calculating
        // 1-p if p is very small, perhaps smaller than machine epsilon.
        //
        // Note that we do not use a finite sum here, since the incomplete
        // beta uses a finite sum internally for integer arguments, so
        // we'll just let it take care of the necessary logic.
        //
        return ibeta(k + 1, n - k, p, Policy());
      } // binomial cdf

      template <class RealType, class Policy>
      inline RealType quantile(const binomial_distribution<RealType, Policy>& dist, const RealType& p)
      {
         return binomial_detail::quantile_imp(dist, p, RealType(1-p), false);
      } // quantile

      template <class RealType, class Policy>
      RealType quantile(const complemented2_type<binomial_distribution<RealType, Policy>, RealType>& c)
      {
         return binomial_detail::quantile_imp(c.dist, RealType(1-c.param), c.param, true);
      } // quantile

      template <class RealType, class Policy>
      inline RealType mode(const binomial_distribution<RealType, Policy>& dist)
      {
         BOOST_MATH_STD_USING // ADL of std functions.
         RealType p = dist.success_fraction();
         RealType n = dist.trials();
         return floor(p * (n + 1));
      }

      template <class RealType, class Policy>
      inline RealType median(const binomial_distribution<RealType, Policy>& dist)
      { // Bounds for the median of the negative binomial distribution
        // VAN DE VEN R. ; WEBER N. C. ;
        // Univ. Sydney, school mathematics statistics, Sydney N.S.W. 2006, AUSTRALIE
        // Metrika  (Metrika)  ISSN 0026-1335   CODEN MTRKA8
        // 1993, vol. 40, no3-4, pp. 185-189 (4 ref.)

        // Bounds for median and 50 percentage point of binomial and negative binomial distribution
        // Metrika, ISSN   0026-1335 (Print) 1435-926X (Online)
        // Volume 41, Number 1 / December, 1994, DOI   10.1007/BF01895303
         BOOST_MATH_STD_USING // ADL of std functions.
         RealType p = dist.success_fraction();
         RealType n = dist.trials();
         // Wikipedia says one of floor(np) -1, floor (np), floor(np) +1
         return floor(p * n); // Chose the middle value.
      }

      template <class RealType, class Policy>
      inline RealType skewness(const binomial_distribution<RealType, Policy>& dist)
      {
         BOOST_MATH_STD_USING // ADL of std functions.
         RealType p = dist.success_fraction();
         RealType n = dist.trials();
         return (1 - 2 * p) / sqrt(n * p * (1 - p));
      }

      template <class RealType, class Policy>
      inline RealType kurtosis(const binomial_distribution<RealType, Policy>& dist)
      {
         RealType p = dist.success_fraction();
         RealType n = dist.trials();
         return 3 - 6 / n + 1 / (n * p * (1 - p));
      }

      template <class RealType, class Policy>
      inline RealType kurtosis_excess(const binomial_distribution<RealType, Policy>& dist)
      {
         RealType p = dist.success_fraction();
         RealType q = 1 - p;
         RealType n = dist.trials();
         return (1 - 6 * p * q) / (n * p * q);
      }

    } // namespace math
  } // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_MATH_SPECIAL_BINOMIAL_HPP



/* binomial.hpp
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
*/