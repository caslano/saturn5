// boost\math\distributions\non_central_chi_squared.hpp

// Copyright John Maddock 2008.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_NON_CENTRAL_CHI_SQUARE_HPP
#define BOOST_MATH_SPECIAL_NON_CENTRAL_CHI_SQUARE_HPP

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/gamma.hpp> // for incomplete gamma. gamma_q
#include <boost/math/special_functions/bessel.hpp> // for cyl_bessel_i
#include <boost/math/special_functions/round.hpp> // for iround
#include <boost/math/distributions/complement.hpp> // complements
#include <boost/math/distributions/chi_squared.hpp> // central distribution
#include <boost/math/distributions/detail/common_error_handling.hpp> // error checks
#include <boost/math/special_functions/fpclassify.hpp> // isnan.
#include <boost/math/tools/roots.hpp> // for root finding.
#include <boost/math/distributions/detail/generic_mode.hpp>
#include <boost/math/distributions/detail/generic_quantile.hpp>

namespace boost
{
   namespace math
   {

      template <class RealType, class Policy>
      class non_central_chi_squared_distribution;

      namespace detail{

         template <class T, class Policy>
         T non_central_chi_square_q(T x, T f, T theta, const Policy& pol, T init_sum = 0)
         {
            //
            // Computes the complement of the Non-Central Chi-Square
            // Distribution CDF by summing a weighted sum of complements
            // of the central-distributions.  The weighting factor is
            // a Poisson Distribution.
            //
            // This is an application of the technique described in:
            //
            // Computing discrete mixtures of continuous
            // distributions: noncentral chisquare, noncentral t
            // and the distribution of the square of the sample
            // multiple correlation coefficient.
            // D. Benton, K. Krishnamoorthy.
            // Computational Statistics & Data Analysis 43 (2003) 249 - 267
            //
            BOOST_MATH_STD_USING

            // Special case:
            if(x == 0)
               return 1;

            //
            // Initialize the variables we'll be using:
            //
            T lambda = theta / 2;
            T del = f / 2;
            T y = x / 2;
            boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
            T errtol = boost::math::policies::get_epsilon<T, Policy>();
            T sum = init_sum;
            //
            // k is the starting location for iteration, we'll
            // move both forwards and backwards from this point.
            // k is chosen as the peek of the Poisson weights, which
            // will occur *before* the largest term.
            //
            int k = iround(lambda, pol);
            // Forwards and backwards Poisson weights:
            T poisf = boost::math::gamma_p_derivative(static_cast<T>(1 + k), lambda, pol);
            T poisb = poisf * k / lambda;
            // Initial forwards central chi squared term:
            T gamf = boost::math::gamma_q(del + k, y, pol);
            // Forwards and backwards recursion terms on the central chi squared:
            T xtermf = boost::math::gamma_p_derivative(del + 1 + k, y, pol);
            T xtermb = xtermf * (del + k) / y;
            // Initial backwards central chi squared term:
            T gamb = gamf - xtermb;

            //
            // Forwards iteration first, this is the
            // stable direction for the gamma function
            // recurrences:
            //
            int i;
            for(i = k; static_cast<boost::uintmax_t>(i-k) < max_iter; ++i)
            {
               T term = poisf * gamf;
               sum += term;
               poisf *= lambda / (i + 1);
               gamf += xtermf;
               xtermf *= y / (del + i + 1);
               if(((sum == 0) || (fabs(term / sum) < errtol)) && (term >= poisf * gamf))
                  break;
            }
            //Error check:
            if(static_cast<boost::uintmax_t>(i-k) >= max_iter)
               return policies::raise_evaluation_error(
                  "cdf(non_central_chi_squared_distribution<%1%>, %1%)",
                  "Series did not converge, closest value was %1%", sum, pol);
            //
            // Now backwards iteration: the gamma
            // function recurrences are unstable in this
            // direction, we rely on the terms diminishing in size
            // faster than we introduce cancellation errors.
            // For this reason it's very important that we start
            // *before* the largest term so that backwards iteration
            // is strictly converging.
            //
            for(i = k - 1; i >= 0; --i)
            {
               T term = poisb * gamb;
               sum += term;
               poisb *= i / lambda;
               xtermb *= (del + i) / y;
               gamb -= xtermb;
               if((sum == 0) || (fabs(term / sum) < errtol))
                  break;
            }

            return sum;
         }

         template <class T, class Policy>
         T non_central_chi_square_p_ding(T x, T f, T theta, const Policy& pol, T init_sum = 0)
         {
            //
            // This is an implementation of:
            //
            // Algorithm AS 275:
            // Computing the Non-Central #2 Distribution Function
            // Cherng G. Ding
            // Applied Statistics, Vol. 41, No. 2. (1992), pp. 478-482.
            //
            // This uses a stable forward iteration to sum the
            // CDF, unfortunately this can not be used for large
            // values of the non-centrality parameter because:
            // * The first term may underflow to zero.
            // * We may need an extra-ordinary number of terms
            //   before we reach the first *significant* term.
            //
            BOOST_MATH_STD_USING
            // Special case:
            if(x == 0)
               return 0;
            T tk = boost::math::gamma_p_derivative(f/2 + 1, x/2, pol);
            T lambda = theta / 2;
            T vk = exp(-lambda);
            T uk = vk;
            T sum = init_sum + tk * vk;
            if(sum == 0)
               return sum;

            boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
            T errtol = boost::math::policies::get_epsilon<T, Policy>();

            int i;
            T lterm(0), term(0);
            for(i = 1; static_cast<boost::uintmax_t>(i) < max_iter; ++i)
            {
               tk = tk * x / (f + 2 * i);
               uk = uk * lambda / i;
               vk = vk + uk;
               lterm = term;
               term = vk * tk;
               sum += term;
               if((fabs(term / sum) < errtol) && (term <= lterm))
                  break;
            }
            //Error check:
            if(static_cast<boost::uintmax_t>(i) >= max_iter)
               return policies::raise_evaluation_error(
                  "cdf(non_central_chi_squared_distribution<%1%>, %1%)",
                  "Series did not converge, closest value was %1%", sum, pol);
            return sum;
         }


         template <class T, class Policy>
         T non_central_chi_square_p(T y, T n, T lambda, const Policy& pol, T init_sum)
         {
            //
            // This is taken more or less directly from:
            //
            // Computing discrete mixtures of continuous
            // distributions: noncentral chisquare, noncentral t
            // and the distribution of the square of the sample
            // multiple correlation coefficient.
            // D. Benton, K. Krishnamoorthy.
            // Computational Statistics & Data Analysis 43 (2003) 249 - 267
            //
            // We're summing a Poisson weighting term multiplied by
            // a central chi squared distribution.
            //
            BOOST_MATH_STD_USING
            // Special case:
            if(y == 0)
               return 0;
            boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
            T errtol = boost::math::policies::get_epsilon<T, Policy>();
            T errorf(0), errorb(0);

            T x = y / 2;
            T del = lambda / 2;
            //
            // Starting location for the iteration, we'll iterate
            // both forwards and backwards from this point.  The
            // location chosen is the maximum of the Poisson weight
            // function, which ocurrs *after* the largest term in the
            // sum.
            //
            int k = iround(del, pol);
            T a = n / 2 + k;
            // Central chi squared term for forward iteration:
            T gamkf = boost::math::gamma_p(a, x, pol);

            if(lambda == 0)
               return gamkf;
            // Central chi squared term for backward iteration:
            T gamkb = gamkf;
            // Forwards Poisson weight:
            T poiskf = gamma_p_derivative(static_cast<T>(k+1), del, pol);
            // Backwards Poisson weight:
            T poiskb = poiskf;
            // Forwards gamma function recursion term:
            T xtermf = boost::math::gamma_p_derivative(a, x, pol);
            // Backwards gamma function recursion term:
            T xtermb = xtermf * x / a;
            T sum = init_sum + poiskf * gamkf;
            if(sum == 0)
               return sum;
            int i = 1;
            //
            // Backwards recursion first, this is the stable
            // direction for gamma function recurrences:
            //
            while(i <= k)
            {
               xtermb *= (a - i + 1) / x;
               gamkb += xtermb;
               poiskb = poiskb * (k - i + 1) / del;
               errorf = errorb;
               errorb = gamkb * poiskb;
               sum += errorb;
               if((fabs(errorb / sum) < errtol) && (errorb <= errorf))
                  break;
               ++i;
            }
            i = 1;
            //
            // Now forwards recursion, the gamma function
            // recurrence relation is unstable in this direction,
            // so we rely on the magnitude of successive terms
            // decreasing faster than we introduce cancellation error.
            // For this reason it's vital that k is chosen to be *after*
            // the largest term, so that successive forward iterations
            // are strictly (and rapidly) converging.
            //
            do
            {
               xtermf = xtermf * x / (a + i - 1);
               gamkf = gamkf - xtermf;
               poiskf = poiskf * del / (k + i);
               errorf = poiskf * gamkf;
               sum += errorf;
               ++i;
            }while((fabs(errorf / sum) > errtol) && (static_cast<boost::uintmax_t>(i) < max_iter));

            //Error check:
            if(static_cast<boost::uintmax_t>(i) >= max_iter)
               return policies::raise_evaluation_error(
                  "cdf(non_central_chi_squared_distribution<%1%>, %1%)",
                  "Series did not converge, closest value was %1%", sum, pol);

            return sum;
         }

         template <class T, class Policy>
         T non_central_chi_square_pdf(T x, T n, T lambda, const Policy& pol)
         {
            //
            // As above but for the PDF:
            //
            BOOST_MATH_STD_USING
            boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
            T errtol = boost::math::policies::get_epsilon<T, Policy>();
            T x2 = x / 2;
            T n2 = n / 2;
            T l2 = lambda / 2;
            T sum = 0;
            int k = itrunc(l2);
            T pois = gamma_p_derivative(static_cast<T>(k + 1), l2, pol) * gamma_p_derivative(static_cast<T>(n2 + k), x2);
            if(pois == 0)
               return 0;
            T poisb = pois;
            for(int i = k; ; ++i)
            {
               sum += pois;
               if(pois / sum < errtol)
                  break;
               if(static_cast<boost::uintmax_t>(i - k) >= max_iter)
                  return policies::raise_evaluation_error(
                     "pdf(non_central_chi_squared_distribution<%1%>, %1%)",
                     "Series did not converge, closest value was %1%", sum, pol);
               pois *= l2 * x2 / ((i + 1) * (n2 + i));
            }
            for(int i = k - 1; i >= 0; --i)
            {
               poisb *= (i + 1) * (n2 + i) / (l2 * x2);
               sum += poisb;
               if(poisb / sum < errtol)
                  break;
            }
            return sum / 2;
         }

         template <class RealType, class Policy>
         inline RealType non_central_chi_squared_cdf(RealType x, RealType k, RealType l, bool invert, const Policy&)
         {
            typedef typename policies::evaluation<RealType, Policy>::type value_type;
            typedef typename policies::normalise<
               Policy,
               policies::promote_float<false>,
               policies::promote_double<false>,
               policies::discrete_quantile<>,
               policies::assert_undefined<> >::type forwarding_policy;

            BOOST_MATH_STD_USING
            value_type result;
            if(l == 0)
              return invert == false ? cdf(boost::math::chi_squared_distribution<RealType, Policy>(k), x) : cdf(complement(boost::math::chi_squared_distribution<RealType, Policy>(k), x));
            else if(x > k + l)
            {
               // Complement is the smaller of the two:
               result = detail::non_central_chi_square_q(
                  static_cast<value_type>(x),
                  static_cast<value_type>(k),
                  static_cast<value_type>(l),
                  forwarding_policy(),
                  static_cast<value_type>(invert ? 0 : -1));
               invert = !invert;
            }
            else if(l < 200)
            {
               // For small values of the non-centrality parameter
               // we can use Ding's method:
               result = detail::non_central_chi_square_p_ding(
                  static_cast<value_type>(x),
                  static_cast<value_type>(k),
                  static_cast<value_type>(l),
                  forwarding_policy(),
                  static_cast<value_type>(invert ? -1 : 0));
            }
            else
            {
               // For largers values of the non-centrality
               // parameter Ding's method will consume an
               // extra-ordinary number of terms, and worse
               // may return zero when the result is in fact
               // finite, use Krishnamoorthy's method instead:
               result = detail::non_central_chi_square_p(
                  static_cast<value_type>(x),
                  static_cast<value_type>(k),
                  static_cast<value_type>(l),
                  forwarding_policy(),
                  static_cast<value_type>(invert ? -1 : 0));
            }
            if(invert)
               result = -result;
            return policies::checked_narrowing_cast<RealType, forwarding_policy>(
               result,
               "boost::math::non_central_chi_squared_cdf<%1%>(%1%, %1%, %1%)");
         }

         template <class T, class Policy>
         struct nccs_quantile_functor
         {
            nccs_quantile_functor(const non_central_chi_squared_distribution<T,Policy>& d, T t, bool c)
               : dist(d), target(t), comp(c) {}

            T operator()(const T& x)
            {
               return comp ?
                  target - cdf(complement(dist, x))
                  : cdf(dist, x) - target;
            }

         private:
            non_central_chi_squared_distribution<T,Policy> dist;
            T target;
            bool comp;
         };

         template <class RealType, class Policy>
         RealType nccs_quantile(const non_central_chi_squared_distribution<RealType, Policy>& dist, const RealType& p, bool comp)
         {
            BOOST_MATH_STD_USING
            static const char* function = "quantile(non_central_chi_squared_distribution<%1%>, %1%)";
            typedef typename policies::evaluation<RealType, Policy>::type value_type;
            typedef typename policies::normalise<
               Policy,
               policies::promote_float<false>,
               policies::promote_double<false>,
               policies::discrete_quantile<>,
               policies::assert_undefined<> >::type forwarding_policy;

            value_type k = dist.degrees_of_freedom();
            value_type l = dist.non_centrality();
            value_type r;
            if(!detail::check_df(
               function,
               k, &r, Policy())
               ||
            !detail::check_non_centrality(
               function,
               l,
               &r,
               Policy())
               ||
            !detail::check_probability(
               function,
               static_cast<value_type>(p),
               &r,
               Policy()))
                  return (RealType)r;
            //
            // Special cases get short-circuited first:
            //
            if(p == 0)
               return comp ? policies::raise_overflow_error<RealType>(function, 0, Policy()) : 0;
            if(p == 1)
               return comp ? 0 : policies::raise_overflow_error<RealType>(function, 0, Policy());
            //
            // This is Pearson's approximation to the quantile, see
            // Pearson, E. S. (1959) "Note on an approximation to the distribution of
            // noncentral chi squared", Biometrika 46: 364.
            // See also:
            // "A comparison of approximations to percentiles of the noncentral chi2-distribution",
            // Hardeo Sahai and Mario Miguel Ojeda, Revista de Matematica: Teoria y Aplicaciones 2003 10(1-2) : 57-76.
            // Note that the latter reference refers to an approximation of the CDF, when they really mean the quantile.
            //
            value_type b = -(l * l) / (k + 3 * l);
            value_type c = (k + 3 * l) / (k + 2 * l);
            value_type ff = (k + 2 * l) / (c * c);
            value_type guess;
            if(comp)
            {
               guess = b + c * quantile(complement(chi_squared_distribution<value_type, forwarding_policy>(ff), p));
            }
            else
            {
               guess = b + c * quantile(chi_squared_distribution<value_type, forwarding_policy>(ff), p);
            }
            //
            // Sometimes guess goes very small or negative, in that case we have
            // to do something else for the initial guess, this approximation
            // was provided in a private communication from Thomas Luu, PhD candidate,
            // University College London.  It's an asymptotic expansion for the
            // quantile which usually gets us within an order of magnitude of the
            // correct answer.
            // Fast and accurate parallel computation of quantile functions for random number generation,
            // Thomas LuuDoctorial Thesis 2016
            // http://discovery.ucl.ac.uk/1482128/
            //
            if(guess < 0.005)
            {
               value_type pp = comp ? 1 - p : p;
               //guess = pow(pow(value_type(2), (k / 2 - 1)) * exp(l / 2) * pp * k, 2 / k);
               guess = pow(pow(value_type(2), (k / 2 - 1)) * exp(l / 2) * pp * k * boost::math::tgamma(k / 2, forwarding_policy()), (2 / k));
               if(guess == 0)
                  guess = tools::min_value<value_type>();
            }
            value_type result = detail::generic_quantile(
               non_central_chi_squared_distribution<value_type, forwarding_policy>(k, l),
               p,
               guess,
               comp,
               function);

            return policies::checked_narrowing_cast<RealType, forwarding_policy>(
               result,
               function);
         }

         template <class RealType, class Policy>
         RealType nccs_pdf(const non_central_chi_squared_distribution<RealType, Policy>& dist, const RealType& x)
         {
            BOOST_MATH_STD_USING
            static const char* function = "pdf(non_central_chi_squared_distribution<%1%>, %1%)";
            typedef typename policies::evaluation<RealType, Policy>::type value_type;
            typedef typename policies::normalise<
               Policy,
               policies::promote_float<false>,
               policies::promote_double<false>,
               policies::discrete_quantile<>,
               policies::assert_undefined<> >::type forwarding_policy;

            value_type k = dist.degrees_of_freedom();
            value_type l = dist.non_centrality();
            value_type r;
            if(!detail::check_df(
               function,
               k, &r, Policy())
               ||
            !detail::check_non_centrality(
               function,
               l,
               &r,
               Policy())
               ||
            !detail::check_positive_x(
               function,
               (value_type)x,
               &r,
               Policy()))
                  return (RealType)r;

         if(l == 0)
            return pdf(boost::math::chi_squared_distribution<RealType, forwarding_policy>(dist.degrees_of_freedom()), x);

         // Special case:
         if(x == 0)
            return 0;
         if(l > 50)
         {
            r = non_central_chi_square_pdf(static_cast<value_type>(x), k, l, forwarding_policy());
         }
         else
         {
            r = log(x / l) * (k / 4 - 0.5f) - (x + l) / 2;
            if(fabs(r) >= tools::log_max_value<RealType>() / 4)
            {
               r = non_central_chi_square_pdf(static_cast<value_type>(x), k, l, forwarding_policy());
            }
            else
            {
               r = exp(r);
               r = 0.5f * r
                  * boost::math::cyl_bessel_i(k/2 - 1, sqrt(l * x), forwarding_policy());
            }
         }
         return policies::checked_narrowing_cast<RealType, forwarding_policy>(
               r,
               function);
         }

         template <class RealType, class Policy>
         struct degrees_of_freedom_finder
         {
            degrees_of_freedom_finder(
               RealType lam_, RealType x_, RealType p_, bool c)
               : lam(lam_), x(x_), p(p_), comp(c) {}

            RealType operator()(const RealType& v)
            {
               non_central_chi_squared_distribution<RealType, Policy> d(v, lam);
               return comp ?
                  RealType(p - cdf(complement(d, x)))
                  : RealType(cdf(d, x) - p);
            }
         private:
            RealType lam;
            RealType x;
            RealType p;
            bool comp;
         };

         template <class RealType, class Policy>
         inline RealType find_degrees_of_freedom(
            RealType lam, RealType x, RealType p, RealType q, const Policy& pol)
         {
            const char* function = "non_central_chi_squared<%1%>::find_degrees_of_freedom";
            if((p == 0) || (q == 0))
            {
               //
               // Can't a thing if one of p and q is zero:
               //
               return policies::raise_evaluation_error<RealType>(function,
                  "Can't find degrees of freedom when the probability is 0 or 1, only possible answer is %1%",
                  RealType(std::numeric_limits<RealType>::quiet_NaN()), Policy());
            }
            degrees_of_freedom_finder<RealType, Policy> f(lam, x, p < q ? p : q, p < q ? false : true);
            tools::eps_tolerance<RealType> tol(policies::digits<RealType, Policy>());
            boost::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
            //
            // Pick an initial guess that we know will give us a probability
            // right around 0.5.
            //
            RealType guess = x - lam;
            if(guess < 1)
               guess = 1;
            std::pair<RealType, RealType> ir = tools::bracket_and_solve_root(
               f, guess, RealType(2), false, tol, max_iter, pol);
            RealType result = ir.first + (ir.second - ir.first) / 2;
            if(max_iter >= policies::get_max_root_iterations<Policy>())
            {
               return policies::raise_evaluation_error<RealType>(function, "Unable to locate solution in a reasonable time:"
                  " or there is no answer to problem.  Current best guess is %1%", result, Policy());
            }
            return result;
         }

         template <class RealType, class Policy>
         struct non_centrality_finder
         {
            non_centrality_finder(
               RealType v_, RealType x_, RealType p_, bool c)
               : v(v_), x(x_), p(p_), comp(c) {}

            RealType operator()(const RealType& lam)
            {
               non_central_chi_squared_distribution<RealType, Policy> d(v, lam);
               return comp ?
                  RealType(p - cdf(complement(d, x)))
                  : RealType(cdf(d, x) - p);
            }
         private:
            RealType v;
            RealType x;
            RealType p;
            bool comp;
         };

         template <class RealType, class Policy>
         inline RealType find_non_centrality(
            RealType v, RealType x, RealType p, RealType q, const Policy& pol)
         {
            const char* function = "non_central_chi_squared<%1%>::find_non_centrality";
            if((p == 0) || (q == 0))
            {
               //
               // Can't do a thing if one of p and q is zero:
               //
               return policies::raise_evaluation_error<RealType>(function,
                  "Can't find non centrality parameter when the probability is 0 or 1, only possible answer is %1%",
                  RealType(std::numeric_limits<RealType>::quiet_NaN()), Policy());
            }
            non_centrality_finder<RealType, Policy> f(v, x, p < q ? p : q, p < q ? false : true);
            tools::eps_tolerance<RealType> tol(policies::digits<RealType, Policy>());
            boost::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
            //
            // Pick an initial guess that we know will give us a probability
            // right around 0.5.
            //
            RealType guess = x - v;
            if(guess < 1)
               guess = 1;
            std::pair<RealType, RealType> ir = tools::bracket_and_solve_root(
               f, guess, RealType(2), false, tol, max_iter, pol);
            RealType result = ir.first + (ir.second - ir.first) / 2;
            if(max_iter >= policies::get_max_root_iterations<Policy>())
            {
               return policies::raise_evaluation_error<RealType>(function, "Unable to locate solution in a reasonable time:"
                  " or there is no answer to problem.  Current best guess is %1%", result, Policy());
            }
            return result;
         }

      }

      template <class RealType = double, class Policy = policies::policy<> >
      class non_central_chi_squared_distribution
      {
      public:
         typedef RealType value_type;
         typedef Policy policy_type;

         non_central_chi_squared_distribution(RealType df_, RealType lambda) : df(df_), ncp(lambda)
         {
            const char* function = "boost::math::non_central_chi_squared_distribution<%1%>::non_central_chi_squared_distribution(%1%,%1%)";
            RealType r;
            detail::check_df(
               function,
               df, &r, Policy());
            detail::check_non_centrality(
               function,
               ncp,
               &r,
               Policy());
         } // non_central_chi_squared_distribution constructor.

         RealType degrees_of_freedom() const
         { // Private data getter function.
            return df;
         }
         RealType non_centrality() const
         { // Private data getter function.
            return ncp;
         }
         static RealType find_degrees_of_freedom(RealType lam, RealType x, RealType p)
         {
            const char* function = "non_central_chi_squared<%1%>::find_degrees_of_freedom";
            typedef typename policies::evaluation<RealType, Policy>::type eval_type;
            typedef typename policies::normalise<
               Policy,
               policies::promote_float<false>,
               policies::promote_double<false>,
               policies::discrete_quantile<>,
               policies::assert_undefined<> >::type forwarding_policy;
            eval_type result = detail::find_degrees_of_freedom(
               static_cast<eval_type>(lam),
               static_cast<eval_type>(x),
               static_cast<eval_type>(p),
               static_cast<eval_type>(1-p),
               forwarding_policy());
            return policies::checked_narrowing_cast<RealType, forwarding_policy>(
               result,
               function);
         }
         template <class A, class B, class C>
         static RealType find_degrees_of_freedom(const complemented3_type<A,B,C>& c)
         {
            const char* function = "non_central_chi_squared<%1%>::find_degrees_of_freedom";
            typedef typename policies::evaluation<RealType, Policy>::type eval_type;
            typedef typename policies::normalise<
               Policy,
               policies::promote_float<false>,
               policies::promote_double<false>,
               policies::discrete_quantile<>,
               policies::assert_undefined<> >::type forwarding_policy;
            eval_type result = detail::find_degrees_of_freedom(
               static_cast<eval_type>(c.dist),
               static_cast<eval_type>(c.param1),
               static_cast<eval_type>(1-c.param2),
               static_cast<eval_type>(c.param2),
               forwarding_policy());
            return policies::checked_narrowing_cast<RealType, forwarding_policy>(
               result,
               function);
         }
         static RealType find_non_centrality(RealType v, RealType x, RealType p)
         {
            const char* function = "non_central_chi_squared<%1%>::find_non_centrality";
            typedef typename policies::evaluation<RealType, Policy>::type eval_type;
            typedef typename policies::normalise<
               Policy,
               policies::promote_float<false>,
               policies::promote_double<false>,
               policies::discrete_quantile<>,
               policies::assert_undefined<> >::type forwarding_policy;
            eval_type result = detail::find_non_centrality(
               static_cast<eval_type>(v),
               static_cast<eval_type>(x),
               static_cast<eval_type>(p),
               static_cast<eval_type>(1-p),
               forwarding_policy());
            return policies::checked_narrowing_cast<RealType, forwarding_policy>(
               result,
               function);
         }
         template <class A, class B, class C>
         static RealType find_non_centrality(const complemented3_type<A,B,C>& c)
         {
            const char* function = "non_central_chi_squared<%1%>::find_non_centrality";
            typedef typename policies::evaluation<RealType, Policy>::type eval_type;
            typedef typename policies::normalise<
               Policy,
               policies::promote_float<false>,
               policies::promote_double<false>,
               policies::discrete_quantile<>,
               policies::assert_undefined<> >::type forwarding_policy;
            eval_type result = detail::find_non_centrality(
               static_cast<eval_type>(c.dist),
               static_cast<eval_type>(c.param1),
               static_cast<eval_type>(1-c.param2),
               static_cast<eval_type>(c.param2),
               forwarding_policy());
            return policies::checked_narrowing_cast<RealType, forwarding_policy>(
               result,
               function);
         }
      private:
         // Data member, initialized by constructor.
         RealType df; // degrees of freedom.
         RealType ncp; // non-centrality parameter
      }; // template <class RealType, class Policy> class non_central_chi_squared_distribution

      typedef non_central_chi_squared_distribution<double> non_central_chi_squared; // Reserved name of type double.

      // Non-member functions to give properties of the distribution.

      template <class RealType, class Policy>
      inline const std::pair<RealType, RealType> range(const non_central_chi_squared_distribution<RealType, Policy>& /* dist */)
      { // Range of permissible values for random variable k.
         using boost::math::tools::max_value;
         return std::pair<RealType, RealType>(static_cast<RealType>(0), max_value<RealType>()); // Max integer?
      }

      template <class RealType, class Policy>
      inline const std::pair<RealType, RealType> support(const non_central_chi_squared_distribution<RealType, Policy>& /* dist */)
      { // Range of supported values for random variable k.
         // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
         using boost::math::tools::max_value;
         return std::pair<RealType, RealType>(static_cast<RealType>(0),  max_value<RealType>());
      }

      template <class RealType, class Policy>
      inline RealType mean(const non_central_chi_squared_distribution<RealType, Policy>& dist)
      { // Mean of poisson distribution = lambda.
         const char* function = "boost::math::non_central_chi_squared_distribution<%1%>::mean()";
         RealType k = dist.degrees_of_freedom();
         RealType l = dist.non_centrality();
         RealType r;
         if(!detail::check_df(
            function,
            k, &r, Policy())
            ||
         !detail::check_non_centrality(
            function,
            l,
            &r,
            Policy()))
               return r;
         return k + l;
      } // mean

      template <class RealType, class Policy>
      inline RealType mode(const non_central_chi_squared_distribution<RealType, Policy>& dist)
      { // mode.
         static const char* function = "mode(non_central_chi_squared_distribution<%1%> const&)";

         RealType k = dist.degrees_of_freedom();
         RealType l = dist.non_centrality();
         RealType r;
         if(!detail::check_df(
            function,
            k, &r, Policy())
            ||
         !detail::check_non_centrality(
            function,
            l,
            &r,
            Policy()))
               return (RealType)r;
         return detail::generic_find_mode(dist, 1 + k, function);
      }

      template <class RealType, class Policy>
      inline RealType variance(const non_central_chi_squared_distribution<RealType, Policy>& dist)
      { // variance.
         const char* function = "boost::math::non_central_chi_squared_distribution<%1%>::variance()";
         RealType k = dist.degrees_of_freedom();
         RealType l = dist.non_centrality();
         RealType r;
         if(!detail::check_df(
            function,
            k, &r, Policy())
            ||
         !detail::check_non_centrality(
            function,
            l,
            &r,
            Policy()))
               return r;
         return 2 * (2 * l + k);
      }

      // RealType standard_deviation(const non_central_chi_squared_distribution<RealType, Policy>& dist)
      // standard_deviation provided by derived accessors.

      template <class RealType, class Policy>
      inline RealType skewness(const non_central_chi_squared_distribution<RealType, Policy>& dist)
      { // skewness = sqrt(l).
         const char* function = "boost::math::non_central_chi_squared_distribution<%1%>::skewness()";
         RealType k = dist.degrees_of_freedom();
         RealType l = dist.non_centrality();
         RealType r;
         if(!detail::check_df(
            function,
            k, &r, Policy())
            ||
         !detail::check_non_centrality(
            function,
            l,
            &r,
            Policy()))
               return r;
         BOOST_MATH_STD_USING
            return pow(2 / (k + 2 * l), RealType(3)/2) * (k + 3 * l);
      }

      template <class RealType, class Policy>
      inline RealType kurtosis_excess(const non_central_chi_squared_distribution<RealType, Policy>& dist)
      {
         const char* function = "boost::math::non_central_chi_squared_distribution<%1%>::kurtosis_excess()";
         RealType k = dist.degrees_of_freedom();
         RealType l = dist.non_centrality();
         RealType r;
         if(!detail::check_df(
            function,
            k, &r, Policy())
            ||
         !detail::check_non_centrality(
            function,
            l,
            &r,
            Policy()))
               return r;
         return 12 * (k + 4 * l) / ((k + 2 * l) * (k + 2 * l));
      } // kurtosis_excess

      template <class RealType, class Policy>
      inline RealType kurtosis(const non_central_chi_squared_distribution<RealType, Policy>& dist)
      {
         return kurtosis_excess(dist) + 3;
      }

      template <class RealType, class Policy>
      inline RealType pdf(const non_central_chi_squared_distribution<RealType, Policy>& dist, const RealType& x)
      { // Probability Density/Mass Function.
         return detail::nccs_pdf(dist, x);
      } // pdf

      template <class RealType, class Policy>
      RealType cdf(const non_central_chi_squared_distribution<RealType, Policy>& dist, const RealType& x)
      {
         const char* function = "boost::math::non_central_chi_squared_distribution<%1%>::cdf(%1%)";
         RealType k = dist.degrees_of_freedom();
         RealType l = dist.non_centrality();
         RealType r;
         if(!detail::check_df(
            function,
            k, &r, Policy())
            ||
         !detail::check_non_centrality(
            function,
            l,
            &r,
            Policy())
            ||
         !detail::check_positive_x(
            function,
            x,
            &r,
            Policy()))
               return r;

         return detail::non_central_chi_squared_cdf(x, k, l, false, Policy());
      } // cdf

      template <class RealType, class Policy>
      RealType cdf(const complemented2_type<non_central_chi_squared_distribution<RealType, Policy>, RealType>& c)
      { // Complemented Cumulative Distribution Function
         const char* function = "boost::math::non_central_chi_squared_distribution<%1%>::cdf(%1%)";
         non_central_chi_squared_distribution<RealType, Policy> const& dist = c.dist;
         RealType x = c.param;
         RealType k = dist.degrees_of_freedom();
         RealType l = dist.non_centrality();
         RealType r;
         if(!detail::check_df(
            function,
            k, &r, Policy())
            ||
         !detail::check_non_centrality(
            function,
            l,
            &r,
            Policy())
            ||
         !detail::check_positive_x(
            function,
            x,
            &r,
            Policy()))
               return r;

         return detail::non_central_chi_squared_cdf(x, k, l, true, Policy());
      } // ccdf

      template <class RealType, class Policy>
      inline RealType quantile(const non_central_chi_squared_distribution<RealType, Policy>& dist, const RealType& p)
      { // Quantile (or Percent Point) function.
         return detail::nccs_quantile(dist, p, false);
      } // quantile

      template <class RealType, class Policy>
      inline RealType quantile(const complemented2_type<non_central_chi_squared_distribution<RealType, Policy>, RealType>& c)
      { // Quantile (or Percent Point) function.
         return detail::nccs_quantile(c.dist, c.param, true);
      } // quantile complement.

   } // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_MATH_SPECIAL_NON_CENTRAL_CHI_SQUARE_HPP




/* non_central_chi_squared.hpp
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
*/