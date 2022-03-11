// boost\math\distributions\non_central_beta.hpp

// Copyright John Maddock 2008.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_NON_CENTRAL_BETA_HPP
#define BOOST_MATH_SPECIAL_NON_CENTRAL_BETA_HPP

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/special_functions/beta.hpp> // for incomplete gamma. gamma_q
#include <boost/math/distributions/complement.hpp> // complements
#include <boost/math/distributions/beta.hpp> // central distribution
#include <boost/math/distributions/detail/generic_mode.hpp>
#include <boost/math/distributions/detail/common_error_handling.hpp> // error checks
#include <boost/math/special_functions/fpclassify.hpp> // isnan.
#include <boost/math/tools/roots.hpp> // for root finding.
#include <boost/math/tools/series.hpp>

namespace boost
{
   namespace math
   {

      template <class RealType, class Policy>
      class non_central_beta_distribution;

      namespace detail{

         template <class T, class Policy>
         T non_central_beta_p(T a, T b, T lam, T x, T y, const Policy& pol, T init_val = 0)
         {
            BOOST_MATH_STD_USING
               using namespace boost::math;
            //
            // Variables come first:
            //
            boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
            T errtol = boost::math::policies::get_epsilon<T, Policy>();
            T l2 = lam / 2;
            //
            // k is the starting point for iteration, and is the
            // maximum of the poisson weighting term,
            // note that unlike other similar code, we do not set
            // k to zero, when l2 is small, as forward iteration
            // is unstable:
            //
            int k = itrunc(l2);
            if(k == 0)
               k = 1;
               // Starting Poisson weight:
            T pois = gamma_p_derivative(T(k+1), l2, pol);
            if(pois == 0)
               return init_val;
            // recurance term:
            T xterm;
            // Starting beta term:
            T beta = x < y
               ? detail::ibeta_imp(T(a + k), b, x, pol, false, true, &xterm)
               : detail::ibeta_imp(b, T(a + k), y, pol, true, true, &xterm);

            xterm *= y / (a + b + k - 1);
            T poisf(pois), betaf(beta), xtermf(xterm);
            T sum = init_val;

            if((beta == 0) && (xterm == 0))
               return init_val;

            //
            // Backwards recursion first, this is the stable
            // direction for recursion:
            //
            T last_term = 0;
            boost::uintmax_t count = k;
            for(int i = k; i >= 0; --i)
            {
               T term = beta * pois;
               sum += term;
               if(((fabs(term/sum) < errtol) && (last_term >= term)) || (term == 0))
               {
                  count = k - i;
                  break;
               }
               pois *= i / l2;
               beta += xterm;
               xterm *= (a + i - 1) / (x * (a + b + i - 2));
               last_term = term;
            }
            for(int i = k + 1; ; ++i)
            {
               poisf *= l2 / i;
               xtermf *= (x * (a + b + i - 2)) / (a + i - 1);
               betaf -= xtermf;

               T term = poisf * betaf;
               sum += term;
               if((fabs(term/sum) < errtol) || (term == 0))
               {
                  break;
               }
               if(static_cast<boost::uintmax_t>(count + i - k) > max_iter)
               {
                  return policies::raise_evaluation_error(
                     "cdf(non_central_beta_distribution<%1%>, %1%)",
                     "Series did not converge, closest value was %1%", sum, pol);
               }
            }
            return sum;
         }

         template <class T, class Policy>
         T non_central_beta_q(T a, T b, T lam, T x, T y, const Policy& pol, T init_val = 0)
         {
            BOOST_MATH_STD_USING
               using namespace boost::math;
            //
            // Variables come first:
            //
            boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
            T errtol = boost::math::policies::get_epsilon<T, Policy>();
            T l2 = lam / 2;
            //
            // k is the starting point for iteration, and is the
            // maximum of the poisson weighting term:
            //
            int k = itrunc(l2);
            T pois;
            if(k <= 30)
            {
               //
               // Might as well start at 0 since we'll likely have this number of terms anyway:
               //
               if(a + b > 1)
                  k = 0;
               else if(k == 0)
                  k = 1;
            }
            if(k == 0)
            {
               // Starting Poisson weight:
               pois = exp(-l2);
            }
            else
            {
               // Starting Poisson weight:
               pois = gamma_p_derivative(T(k+1), l2, pol);
            }
            if(pois == 0)
               return init_val;
            // recurance term:
            T xterm;
            // Starting beta term:
            T beta = x < y
               ? detail::ibeta_imp(T(a + k), b, x, pol, true, true, &xterm)
               : detail::ibeta_imp(b, T(a + k), y, pol, false, true, &xterm);

            xterm *= y / (a + b + k - 1);
            T poisf(pois), betaf(beta), xtermf(xterm);
            T sum = init_val;
            if((beta == 0) && (xterm == 0))
               return init_val;
            //
            // Forwards recursion first, this is the stable
            // direction for recursion, and the location
            // of the bulk of the sum:
            //
            T last_term = 0;
            boost::uintmax_t count = 0;
            for(int i = k + 1; ; ++i)
            {
               poisf *= l2 / i;
               xtermf *= (x * (a + b + i - 2)) / (a + i - 1);
               betaf += xtermf;

               T term = poisf * betaf;
               sum += term;
               if((fabs(term/sum) < errtol) && (last_term >= term))
               {
                  count = i - k;
                  break;
               }
               if(static_cast<boost::uintmax_t>(i - k) > max_iter)
               {
                  return policies::raise_evaluation_error(
                     "cdf(non_central_beta_distribution<%1%>, %1%)",
                     "Series did not converge, closest value was %1%", sum, pol);
               }
               last_term = term;
            }
            for(int i = k; i >= 0; --i)
            {
               T term = beta * pois;
               sum += term;
               if(fabs(term/sum) < errtol)
               {
                  break;
               }
               if(static_cast<boost::uintmax_t>(count + k - i) > max_iter)
               {
                  return policies::raise_evaluation_error(
                     "cdf(non_central_beta_distribution<%1%>, %1%)",
                     "Series did not converge, closest value was %1%", sum, pol);
               }
               pois *= i / l2;
               beta -= xterm;
               xterm *= (a + i - 1) / (x * (a + b + i - 2));
            }
            return sum;
         }

         template <class RealType, class Policy>
         inline RealType non_central_beta_cdf(RealType x, RealType y, RealType a, RealType b, RealType l, bool invert, const Policy&)
         {
            typedef typename policies::evaluation<RealType, Policy>::type value_type;
            typedef typename policies::normalise<
               Policy,
               policies::promote_float<false>,
               policies::promote_double<false>,
               policies::discrete_quantile<>,
               policies::assert_undefined<> >::type forwarding_policy;

            BOOST_MATH_STD_USING

            if(x == 0)
               return invert ? 1.0f : 0.0f;
            if(y == 0)
               return invert ? 0.0f : 1.0f;
            value_type result;
            value_type c = a + b + l / 2;
            value_type cross = 1 - (b / c) * (1 + l / (2 * c * c));
            if(l == 0)
               result = cdf(boost::math::beta_distribution<RealType, Policy>(a, b), x);
            else if(x > cross)
            {
               // Complement is the smaller of the two:
               result = detail::non_central_beta_q(
                  static_cast<value_type>(a),
                  static_cast<value_type>(b),
                  static_cast<value_type>(l),
                  static_cast<value_type>(x),
                  static_cast<value_type>(y),
                  forwarding_policy(),
                  static_cast<value_type>(invert ? 0 : -1));
               invert = !invert;
            }
            else
            {
               result = detail::non_central_beta_p(
                  static_cast<value_type>(a),
                  static_cast<value_type>(b),
                  static_cast<value_type>(l),
                  static_cast<value_type>(x),
                  static_cast<value_type>(y),
                  forwarding_policy(),
                  static_cast<value_type>(invert ? -1 : 0));
            }
            if(invert)
               result = -result;
            return policies::checked_narrowing_cast<RealType, forwarding_policy>(
               result,
               "boost::math::non_central_beta_cdf<%1%>(%1%, %1%, %1%)");
         }

         template <class T, class Policy>
         struct nc_beta_quantile_functor
         {
            nc_beta_quantile_functor(const non_central_beta_distribution<T,Policy>& d, T t, bool c)
               : dist(d), target(t), comp(c) {}

            T operator()(const T& x)
            {
               return comp ?
                  T(target - cdf(complement(dist, x)))
                  : T(cdf(dist, x) - target);
            }

         private:
            non_central_beta_distribution<T,Policy> dist;
            T target;
            bool comp;
         };

         //
         // This is more or less a copy of bracket_and_solve_root, but
         // modified to search only the interval [0,1] using similar
         // heuristics.
         //
         template <class F, class T, class Tol, class Policy>
         std::pair<T, T> bracket_and_solve_root_01(F f, const T& guess, T factor, bool rising, Tol tol, boost::uintmax_t& max_iter, const Policy& pol)
         {
            BOOST_MATH_STD_USING
               static const char* function = "boost::math::tools::bracket_and_solve_root_01<%1%>";
            //
            // Set up initial brackets:
            //
            T a = guess;
            T b = a;
            T fa = f(a);
            T fb = fa;
            //
            // Set up invocation count:
            //
            boost::uintmax_t count = max_iter - 1;

            if((fa < 0) == (guess < 0 ? !rising : rising))
            {
               //
               // Zero is to the right of b, so walk upwards
               // until we find it:
               //
               while((boost::math::sign)(fb) == (boost::math::sign)(fa))
               {
                  if(count == 0)
                  {
                     b = policies::raise_evaluation_error(function, "Unable to bracket root, last nearest value was %1%", b, pol);
                     return std::make_pair(a, b);
                  }
                  //
                  // Heuristic: every 20 iterations we double the growth factor in case the
                  // initial guess was *really* bad !
                  //
                  if((max_iter - count) % 20 == 0)
                     factor *= 2;
                  //
                  // Now go ahead and move are guess by "factor",
                  // we do this by reducing 1-guess by factor:
                  //
                  a = b;
                  fa = fb;
                  b = 1 - ((1 - b) / factor);
                  fb = f(b);
                  --count;
                  BOOST_MATH_INSTRUMENT_CODE("a = " << a << " b = " << b << " fa = " << fa << " fb = " << fb << " count = " << count);
               }
            }
            else
            {
               //
               // Zero is to the left of a, so walk downwards
               // until we find it:
               //
               while((boost::math::sign)(fb) == (boost::math::sign)(fa))
               {
                  if(fabs(a) < tools::min_value<T>())
                  {
                     // Escape route just in case the answer is zero!
                     max_iter -= count;
                     max_iter += 1;
                     return a > 0 ? std::make_pair(T(0), T(a)) : std::make_pair(T(a), T(0));
                  }
                  if(count == 0)
                  {
                     a = policies::raise_evaluation_error(function, "Unable to bracket root, last nearest value was %1%", a, pol);
                     return std::make_pair(a, b);
                  }
                  //
                  // Heuristic: every 20 iterations we double the growth factor in case the
                  // initial guess was *really* bad !
                  //
                  if((max_iter - count) % 20 == 0)
                     factor *= 2;
                  //
                  // Now go ahead and move are guess by "factor":
                  //
                  b = a;
                  fb = fa;
                  a /= factor;
                  fa = f(a);
                  --count;
                  BOOST_MATH_INSTRUMENT_CODE("a = " << a << " b = " << b << " fa = " << fa << " fb = " << fb << " count = " << count);
               }
            }
            max_iter -= count;
            max_iter += 1;
            std::pair<T, T> r = toms748_solve(
               f,
               (a < 0 ? b : a),
               (a < 0 ? a : b),
               (a < 0 ? fb : fa),
               (a < 0 ? fa : fb),
               tol,
               count,
               pol);
            max_iter += count;
            BOOST_MATH_INSTRUMENT_CODE("max_iter = " << max_iter << " count = " << count);
            return r;
         }

         template <class RealType, class Policy>
         RealType nc_beta_quantile(const non_central_beta_distribution<RealType, Policy>& dist, const RealType& p, bool comp)
         {
            static const char* function = "quantile(non_central_beta_distribution<%1%>, %1%)";
            typedef typename policies::evaluation<RealType, Policy>::type value_type;
            typedef typename policies::normalise<
               Policy,
               policies::promote_float<false>,
               policies::promote_double<false>,
               policies::discrete_quantile<>,
               policies::assert_undefined<> >::type forwarding_policy;

            value_type a = dist.alpha();
            value_type b = dist.beta();
            value_type l = dist.non_centrality();
            value_type r;
            if(!beta_detail::check_alpha(
               function,
               a, &r, Policy())
               ||
            !beta_detail::check_beta(
               function,
               b, &r, Policy())
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
            // Special cases first:
            //
            if(p == 0)
               return comp
               ? 1.0f
               : 0.0f;
            if(p == 1)
               return !comp
               ? 1.0f
               : 0.0f;

            value_type c = a + b + l / 2;
            value_type mean = 1 - (b / c) * (1 + l / (2 * c * c));
            /*
            //
            // Calculate a normal approximation to the quantile,
            // uses mean and variance approximations from:
            // Algorithm AS 310:
            // Computing the Non-Central Beta Distribution Function
            // R. Chattamvelli; R. Shanmugam
            // Applied Statistics, Vol. 46, No. 1. (1997), pp. 146-156.
            //
            // Unfortunately, when this is wrong it tends to be *very*
            // wrong, so it's disabled for now, even though it often
            // gets the initial guess quite close.  Probably we could
            // do much better by factoring in the skewness if only
            // we could calculate it....
            //
            value_type delta = l / 2;
            value_type delta2 = delta * delta;
            value_type delta3 = delta * delta2;
            value_type delta4 = delta2 * delta2;
            value_type G = c * (c + 1) + delta;
            value_type alpha = a + b;
            value_type alpha2 = alpha * alpha;
            value_type eta = (2 * alpha + 1) * (2 * alpha + 1) + 1;
            value_type H = 3 * alpha2 + 5 * alpha + 2;
            value_type F = alpha2 * (alpha + 1) + H * delta
               + (2 * alpha + 4) * delta2 + delta3;
            value_type P = (3 * alpha + 1) * (9 * alpha + 17)
               + 2 * alpha * (3 * alpha + 2) * (3 * alpha + 4) + 15;
            value_type Q = 54 * alpha2 + 162 * alpha + 130;
            value_type R = 6 * (6 * alpha + 11);
            value_type D = delta
               * (H * H + 2 * P * delta + Q * delta2 + R * delta3 + 9 * delta4);
            value_type variance = (b / G)
               * (1 + delta * (l * l + 3 * l + eta) / (G * G))
               - (b * b / F) * (1 + D / (F * F));
            value_type sd = sqrt(variance);

            value_type guess = comp
               ? quantile(complement(normal_distribution<RealType, Policy>(static_cast<RealType>(mean), static_cast<RealType>(sd)), p))
               : quantile(normal_distribution<RealType, Policy>(static_cast<RealType>(mean), static_cast<RealType>(sd)), p);

            if(guess >= 1)
               guess = mean;
            if(guess <= tools::min_value<value_type>())
               guess = mean;
            */
            value_type guess = mean;
            detail::nc_beta_quantile_functor<value_type, Policy>
               f(non_central_beta_distribution<value_type, Policy>(a, b, l), p, comp);
            tools::eps_tolerance<value_type> tol(policies::digits<RealType, Policy>());
            boost::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();

            std::pair<value_type, value_type> ir
               = bracket_and_solve_root_01(
                  f, guess, value_type(2.5), true, tol,
                  max_iter, Policy());
            value_type result = ir.first + (ir.second - ir.first) / 2;

            if(max_iter >= policies::get_max_root_iterations<Policy>())
            {
               return policies::raise_evaluation_error<RealType>(function, "Unable to locate solution in a reasonable time:"
                  " either there is no answer to quantile of the non central beta distribution"
                  " or the answer is infinite.  Current best guess is %1%",
                  policies::checked_narrowing_cast<RealType, forwarding_policy>(
                     result,
                     function), Policy());
            }
            return policies::checked_narrowing_cast<RealType, forwarding_policy>(
               result,
               function);
         }

         template <class T, class Policy>
         T non_central_beta_pdf(T a, T b, T lam, T x, T y, const Policy& pol)
         {
            BOOST_MATH_STD_USING
            //
            // Special cases:
            //
            if((x == 0) || (y == 0))
               return 0;
            //
            // Variables come first:
            //
            boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
            T errtol = boost::math::policies::get_epsilon<T, Policy>();
            T l2 = lam / 2;
            //
            // k is the starting point for iteration, and is the
            // maximum of the poisson weighting term:
            //
            int k = itrunc(l2);
            // Starting Poisson weight:
            T pois = gamma_p_derivative(T(k+1), l2, pol);
            // Starting beta term:
            T beta = x < y ?
               ibeta_derivative(a + k, b, x, pol)
               : ibeta_derivative(b, a + k, y, pol);
            T sum = 0;
            T poisf(pois);
            T betaf(beta);

            //
            // Stable backwards recursion first:
            //
            boost::uintmax_t count = k;
            for(int i = k; i >= 0; --i)
            {
               T term = beta * pois;
               sum += term;
               if((fabs(term/sum) < errtol) || (term == 0))
               {
                  count = k - i;
                  break;
               }
               pois *= i / l2;
               beta *= (a + i - 1) / (x * (a + i + b - 1));
            }
            for(int i = k + 1; ; ++i)
            {
               poisf *= l2 / i;
               betaf *= x * (a + b + i - 1) / (a + i - 1);

               T term = poisf * betaf;
               sum += term;
               if((fabs(term/sum) < errtol) || (term == 0))
               {
                  break;
               }
               if(static_cast<boost::uintmax_t>(count + i - k) > max_iter)
               {
                  return policies::raise_evaluation_error(
                     "pdf(non_central_beta_distribution<%1%>, %1%)",
                     "Series did not converge, closest value was %1%", sum, pol);
               }
            }
            return sum;
         }

         template <class RealType, class Policy>
         RealType nc_beta_pdf(const non_central_beta_distribution<RealType, Policy>& dist, const RealType& x)
         {
            BOOST_MATH_STD_USING
            static const char* function = "pdf(non_central_beta_distribution<%1%>, %1%)";
            typedef typename policies::evaluation<RealType, Policy>::type value_type;
            typedef typename policies::normalise<
               Policy,
               policies::promote_float<false>,
               policies::promote_double<false>,
               policies::discrete_quantile<>,
               policies::assert_undefined<> >::type forwarding_policy;

            value_type a = dist.alpha();
            value_type b = dist.beta();
            value_type l = dist.non_centrality();
            value_type r;
            if(!beta_detail::check_alpha(
               function,
               a, &r, Policy())
               ||
            !beta_detail::check_beta(
               function,
               b, &r, Policy())
               ||
            !detail::check_non_centrality(
               function,
               l,
               &r,
               Policy())
               ||
            !beta_detail::check_x(
               function,
               static_cast<value_type>(x),
               &r,
               Policy()))
                  return (RealType)r;

            if(l == 0)
               return pdf(boost::math::beta_distribution<RealType, Policy>(dist.alpha(), dist.beta()), x);
            return policies::checked_narrowing_cast<RealType, forwarding_policy>(
               non_central_beta_pdf(a, b, l, static_cast<value_type>(x), value_type(1 - static_cast<value_type>(x)), forwarding_policy()),
               "function");
         }

         template <class T>
         struct hypergeometric_2F2_sum
         {
            typedef T result_type;
            hypergeometric_2F2_sum(T a1_, T a2_, T b1_, T b2_, T z_) : a1(a1_), a2(a2_), b1(b1_), b2(b2_), z(z_), term(1), k(0) {}
            T operator()()
            {
               T result = term;
               term *= a1 * a2 / (b1 * b2);
               a1 += 1;
               a2 += 1;
               b1 += 1;
               b2 += 1;
               k += 1;
               term /= k;
               term *= z;
               return result;
            }
            T a1, a2, b1, b2, z, term, k;
         };

         template <class T, class Policy>
         T hypergeometric_2F2(T a1, T a2, T b1, T b2, T z, const Policy& pol)
         {
            typedef typename policies::evaluation<T, Policy>::type value_type;

            const char* function = "boost::math::detail::hypergeometric_2F2<%1%>(%1%,%1%,%1%,%1%,%1%)";

            hypergeometric_2F2_sum<value_type> s(a1, a2, b1, b2, z);
            boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))
            value_type zero = 0;
            value_type result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<value_type, Policy>(), max_iter, zero);
#else
            value_type result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<value_type, Policy>(), max_iter);
#endif
            policies::check_series_iterations<T>(function, max_iter, pol);
            return policies::checked_narrowing_cast<T, Policy>(result, function);
         }

      } // namespace detail

      template <class RealType = double, class Policy = policies::policy<> >
      class non_central_beta_distribution
      {
      public:
         typedef RealType value_type;
         typedef Policy policy_type;

         non_central_beta_distribution(RealType a_, RealType b_, RealType lambda) : a(a_), b(b_), ncp(lambda)
         {
            const char* function = "boost::math::non_central_beta_distribution<%1%>::non_central_beta_distribution(%1%,%1%)";
            RealType r;
            beta_detail::check_alpha(
               function,
               a, &r, Policy());
            beta_detail::check_beta(
               function,
               b, &r, Policy());
            detail::check_non_centrality(
               function,
               lambda,
               &r,
               Policy());
         } // non_central_beta_distribution constructor.

         RealType alpha() const
         { // Private data getter function.
            return a;
         }
         RealType beta() const
         { // Private data getter function.
            return b;
         }
         RealType non_centrality() const
         { // Private data getter function.
            return ncp;
         }
      private:
         // Data member, initialized by constructor.
         RealType a;   // alpha.
         RealType b;   // beta.
         RealType ncp; // non-centrality parameter
      }; // template <class RealType, class Policy> class non_central_beta_distribution

      typedef non_central_beta_distribution<double> non_central_beta; // Reserved name of type double.

      // Non-member functions to give properties of the distribution.

      template <class RealType, class Policy>
      inline const std::pair<RealType, RealType> range(const non_central_beta_distribution<RealType, Policy>& /* dist */)
      { // Range of permissible values for random variable k.
         using boost::math::tools::max_value;
         return std::pair<RealType, RealType>(static_cast<RealType>(0), static_cast<RealType>(1));
      }

      template <class RealType, class Policy>
      inline const std::pair<RealType, RealType> support(const non_central_beta_distribution<RealType, Policy>& /* dist */)
      { // Range of supported values for random variable k.
         // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
         using boost::math::tools::max_value;
         return std::pair<RealType, RealType>(static_cast<RealType>(0), static_cast<RealType>(1));
      }

      template <class RealType, class Policy>
      inline RealType mode(const non_central_beta_distribution<RealType, Policy>& dist)
      { // mode.
         static const char* function = "mode(non_central_beta_distribution<%1%> const&)";

         RealType a = dist.alpha();
         RealType b = dist.beta();
         RealType l = dist.non_centrality();
         RealType r;
         if(!beta_detail::check_alpha(
               function,
               a, &r, Policy())
               ||
            !beta_detail::check_beta(
               function,
               b, &r, Policy())
               ||
            !detail::check_non_centrality(
               function,
               l,
               &r,
               Policy()))
                  return (RealType)r;
         RealType c = a + b + l / 2;
         RealType mean = 1 - (b / c) * (1 + l / (2 * c * c));
         return detail::generic_find_mode_01(
            dist,
            mean,
            function);
      }

      //
      // We don't have the necessary information to implement
      // these at present.  These are just disabled for now,
      // prototypes retained so we can fill in the blanks
      // later:
      //
      template <class RealType, class Policy>
      inline RealType mean(const non_central_beta_distribution<RealType, Policy>& dist)
      {
         BOOST_MATH_STD_USING
         RealType a = dist.alpha();
         RealType b = dist.beta();
         RealType d = dist.non_centrality();
         RealType apb = a + b;
         return exp(-d / 2) * a * detail::hypergeometric_2F2<RealType, Policy>(1 + a, apb, a, 1 + apb, d / 2, Policy()) / apb;
      } // mean

      template <class RealType, class Policy>
      inline RealType variance(const non_central_beta_distribution<RealType, Policy>& dist)
      { 
         //
         // Relative error of this function may be arbitrarily large... absolute
         // error will be small however... that's the best we can do for now.
         //
         BOOST_MATH_STD_USING
         RealType a = dist.alpha();
         RealType b = dist.beta();
         RealType d = dist.non_centrality();
         RealType apb = a + b;
         RealType result = detail::hypergeometric_2F2(RealType(1 + a), apb, a, RealType(1 + apb), RealType(d / 2), Policy());
         result *= result * -exp(-d) * a * a / (apb * apb);
         result += exp(-d / 2) * a * (1 + a) * detail::hypergeometric_2F2(RealType(2 + a), apb, a, RealType(2 + apb), RealType(d / 2), Policy()) / (apb * (1 + apb));
         return result;
      }

      // RealType standard_deviation(const non_central_beta_distribution<RealType, Policy>& dist)
      // standard_deviation provided by derived accessors.
      template <class RealType, class Policy>
      inline RealType skewness(const non_central_beta_distribution<RealType, Policy>& /*dist*/)
      { // skewness = sqrt(l).
         const char* function = "boost::math::non_central_beta_distribution<%1%>::skewness()";
         typedef typename Policy::assert_undefined_type assert_type;
         BOOST_STATIC_ASSERT(assert_type::value == 0);

         return policies::raise_evaluation_error<RealType>(
            function,
            "This function is not yet implemented, the only sensible result is %1%.",
            std::numeric_limits<RealType>::quiet_NaN(), Policy()); // infinity?
      }

      template <class RealType, class Policy>
      inline RealType kurtosis_excess(const non_central_beta_distribution<RealType, Policy>& /*dist*/)
      {
         const char* function = "boost::math::non_central_beta_distribution<%1%>::kurtosis_excess()";
         typedef typename Policy::assert_undefined_type assert_type;
         BOOST_STATIC_ASSERT(assert_type::value == 0);

         return policies::raise_evaluation_error<RealType>(
            function,
            "This function is not yet implemented, the only sensible result is %1%.",
            std::numeric_limits<RealType>::quiet_NaN(), Policy()); // infinity?
      } // kurtosis_excess

      template <class RealType, class Policy>
      inline RealType kurtosis(const non_central_beta_distribution<RealType, Policy>& dist)
      {
         return kurtosis_excess(dist) + 3;
      }

      template <class RealType, class Policy>
      inline RealType pdf(const non_central_beta_distribution<RealType, Policy>& dist, const RealType& x)
      { // Probability Density/Mass Function.
         return detail::nc_beta_pdf(dist, x);
      } // pdf

      template <class RealType, class Policy>
      RealType cdf(const non_central_beta_distribution<RealType, Policy>& dist, const RealType& x)
      {
         const char* function = "boost::math::non_central_beta_distribution<%1%>::cdf(%1%)";
            RealType a = dist.alpha();
            RealType b = dist.beta();
            RealType l = dist.non_centrality();
            RealType r;
            if(!beta_detail::check_alpha(
               function,
               a, &r, Policy())
               ||
            !beta_detail::check_beta(
               function,
               b, &r, Policy())
               ||
            !detail::check_non_centrality(
               function,
               l,
               &r,
               Policy())
               ||
            !beta_detail::check_x(
               function,
               x,
               &r,
               Policy()))
                  return (RealType)r;

         if(l == 0)
            return cdf(beta_distribution<RealType, Policy>(a, b), x);

         return detail::non_central_beta_cdf(x, RealType(1 - x), a, b, l, false, Policy());
      } // cdf

      template <class RealType, class Policy>
      RealType cdf(const complemented2_type<non_central_beta_distribution<RealType, Policy>, RealType>& c)
      { // Complemented Cumulative Distribution Function
         const char* function = "boost::math::non_central_beta_distribution<%1%>::cdf(%1%)";
         non_central_beta_distribution<RealType, Policy> const& dist = c.dist;
            RealType a = dist.alpha();
            RealType b = dist.beta();
            RealType l = dist.non_centrality();
            RealType x = c.param;
            RealType r;
            if(!beta_detail::check_alpha(
               function,
               a, &r, Policy())
               ||
            !beta_detail::check_beta(
               function,
               b, &r, Policy())
               ||
            !detail::check_non_centrality(
               function,
               l,
               &r,
               Policy())
               ||
            !beta_detail::check_x(
               function,
               x,
               &r,
               Policy()))
                  return (RealType)r;

         if(l == 0)
            return cdf(complement(beta_distribution<RealType, Policy>(a, b), x));

         return detail::non_central_beta_cdf(x, RealType(1 - x), a, b, l, true, Policy());
      } // ccdf

      template <class RealType, class Policy>
      inline RealType quantile(const non_central_beta_distribution<RealType, Policy>& dist, const RealType& p)
      { // Quantile (or Percent Point) function.
         return detail::nc_beta_quantile(dist, p, false);
      } // quantile

      template <class RealType, class Policy>
      inline RealType quantile(const complemented2_type<non_central_beta_distribution<RealType, Policy>, RealType>& c)
      { // Quantile (or Percent Point) function.
         return detail::nc_beta_quantile(c.dist, c.param, true);
      } // quantile complement.

   } // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_MATH_SPECIAL_NON_CENTRAL_BETA_HPP


/* non_central_beta.hpp
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
*/