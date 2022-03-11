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
        boost::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
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