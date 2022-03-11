// boost\math\distributions\non_central_t.hpp

// Copyright John Maddock 2008.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_NON_CENTRAL_T_HPP
#define BOOST_MATH_SPECIAL_NON_CENTRAL_T_HPP

#include <boost/math/distributions/fwd.hpp>
#include <boost/math/distributions/non_central_beta.hpp> // for nc beta
#include <boost/math/distributions/normal.hpp> // for normal CDF and quantile
#include <boost/math/distributions/students_t.hpp>
#include <boost/math/distributions/detail/generic_quantile.hpp> // quantile

namespace boost
{
   namespace math
   {

      template <class RealType, class Policy>
      class non_central_t_distribution;

      namespace detail{

         template <class T, class Policy>
         T non_central_t2_p(T v, T delta, T x, T y, const Policy& pol, T init_val)
         {
            BOOST_MATH_STD_USING
            //
            // Variables come first:
            //
            boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
            T errtol = policies::get_epsilon<T, Policy>();
            T d2 = delta * delta / 2;
            //
            // k is the starting point for iteration, and is the
            // maximum of the poisson weighting term, we don't
            // ever allow k == 0 as this can lead to catastrophic
            // cancellation errors later (test case is v = 1621286869049072.3
            // delta = 0.16212868690490723, x = 0.86987415482475994).
            //
            int k = itrunc(d2);
            T pois;
            if(k == 0) k = 1;
            // Starting Poisson weight:
            pois = gamma_p_derivative(T(k+1), d2, pol) 
               * tgamma_delta_ratio(T(k + 1), T(0.5f))
               * delta / constants::root_two<T>();
            if(pois == 0)
               return init_val;
            T xterm, beta;
            // Recurrence & starting beta terms:
            beta = x < y
               ? detail::ibeta_imp(T(k + 1), T(v / 2), x, pol, false, true, &xterm)
               : detail::ibeta_imp(T(v / 2), T(k + 1), y, pol, true, true, &xterm);
            xterm *= y / (v / 2 + k);
            T poisf(pois), betaf(beta), xtermf(xterm);
            T sum = init_val;
            if((xterm == 0) && (beta == 0))
               return init_val;

            //
            // Backwards recursion first, this is the stable
            // direction for recursion:
            //
            boost::uintmax_t count = 0;
            T last_term = 0;
            for(int i = k; i >= 0; --i)
            {
               T term = beta * pois;
               sum += term;
               // Don't terminate on first term in case we "fixed" k above:
               if((fabs(last_term) > fabs(term)) && fabs(term/sum) < errtol)
                  break;
               last_term = term;
               pois *= (i + 0.5f) / d2;
               beta += xterm;
               xterm *= (i) / (x * (v / 2 + i - 1));
               ++count;
            }
            last_term = 0;
            for(int i = k + 1; ; ++i)
            {
               poisf *= d2 / (i + 0.5f);
               xtermf *= (x * (v / 2 + i - 1)) / (i);
               betaf -= xtermf;
               T term = poisf * betaf;
               sum += term;
               if((fabs(last_term) >= fabs(term)) && (fabs(term/sum) < errtol))
                  break;
               last_term = term;
               ++count;
               if(count > max_iter)
               {
                  return policies::raise_evaluation_error(
                     "cdf(non_central_t_distribution<%1%>, %1%)", 
                     "Series did not converge, closest value was %1%", sum, pol);
               }
            }
            return sum;
         }

         template <class T, class Policy>
         T non_central_t2_q(T v, T delta, T x, T y, const Policy& pol, T init_val)
         {
            BOOST_MATH_STD_USING
            //
            // Variables come first:
            //
            boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
            T errtol = boost::math::policies::get_epsilon<T, Policy>();
            T d2 = delta * delta / 2;
            //
            // k is the starting point for iteration, and is the
            // maximum of the poisson weighting term, we don't allow
            // k == 0 as this can cause catastrophic cancellation errors
            // (test case is v = 561908036470413.25, delta = 0.056190803647041321,
            // x = 1.6155232703966216):
            //
            int k = itrunc(d2);
            if(k == 0) k = 1;
            // Starting Poisson weight:
            T pois;
            if((k < (int)(max_factorial<T>::value)) && (d2 < tools::log_max_value<T>()) && (log(d2) * k < tools::log_max_value<T>()))
            {
               //
               // For small k we can optimise this calculation by using
               // a simpler reduced formula:
               //
               pois = exp(-d2);
               pois *= pow(d2, static_cast<T>(k));
               pois /= boost::math::tgamma(T(k + 1 + 0.5), pol);
               pois *= delta / constants::root_two<T>();
            }
            else
            {
               pois = gamma_p_derivative(T(k+1), d2, pol) 
                  * tgamma_delta_ratio(T(k + 1), T(0.5f))
                  * delta / constants::root_two<T>();
            }
            if(pois == 0)
               return init_val;
            // Recurance term:
            T xterm;
            T beta;
            // Starting beta term:
            if(k != 0)
            {
               beta = x < y 
                  ? detail::ibeta_imp(T(k + 1), T(v / 2), x, pol, true, true, &xterm) 
                  : detail::ibeta_imp(T(v / 2), T(k + 1), y, pol, false, true, &xterm);

               xterm *= y / (v / 2 + k);
            }
            else
            {
               beta = pow(y, v / 2);
               xterm = beta;
            }
            T poisf(pois), betaf(beta), xtermf(xterm);
            T sum = init_val;
            if((xterm == 0) && (beta == 0))
               return init_val;

            //
            // Fused forward and backwards recursion:
            //
            boost::uintmax_t count = 0;
            T last_term = 0;
            for(int i = k + 1, j = k; ; ++i, --j)
            {
               poisf *= d2 / (i + 0.5f);
               xtermf *= (x * (v / 2 + i - 1)) / (i);
               betaf += xtermf;
               T term = poisf * betaf;

               if(j >= 0)
               {
                  term += beta * pois;
                  pois *= (j + 0.5f) / d2;
                  beta -= xterm;
                  xterm *= (j) / (x * (v / 2 + j - 1));
               }

               sum += term;
               // Don't terminate on first term in case we "fixed" the value of k above:
               if((fabs(last_term) > fabs(term)) && fabs(term/sum) < errtol)
                  break;
               last_term = term;
               if(count > max_iter)
               {
                  return policies::raise_evaluation_error(
                     "cdf(non_central_t_distribution<%1%>, %1%)", 
                     "Series did not converge, closest value was %1%", sum, pol);
               }
               ++count;
            }
            return sum;
         }

         template <class T, class Policy>
         T non_central_t_cdf(T v, T delta, T t, bool invert, const Policy& pol)
         {
            BOOST_MATH_STD_USING
            if ((boost::math::isinf)(v))
            { // Infinite degrees of freedom, so use normal distribution located at delta.
               normal_distribution<T, Policy> n(delta, 1); 
               return cdf(n, t);
            }
            //
            // Otherwise, for t < 0 we have to use the reflection formula:
            if(t < 0)
            {
               t = -t;
               delta = -delta;
               invert = !invert;
            }
            if(fabs(delta / (4 * v)) < policies::get_epsilon<T, Policy>())
            {
               // Approximate with a Student's T centred on delta,
               // the crossover point is based on eq 2.6 from
               // "A Comparison of Approximations To Percentiles of the
               // Noncentral t-Distribution".  H. Sahai and M. M. Ojeda,
               // Revista Investigacion Operacional Vol 21, No 2, 2000.
               // Original sources referenced in the above are:
               // "Some Approximations to the Percentage Points of the Noncentral
               // t-Distribution". C. van Eeden. International Statistical Review, 29, 4-31.
               // "Continuous Univariate Distributions".  N.L. Johnson, S. Kotz and
               // N. Balkrishnan. 1995. John Wiley and Sons New York.
               T result = cdf(students_t_distribution<T, Policy>(v), t - delta);
               return invert ? 1 - result : result;
            }
            //
            // x and y are the corresponding random
            // variables for the noncentral beta distribution,
            // with y = 1 - x:
            //
            T x = t * t / (v + t * t);
            T y = v / (v + t * t);
            T d2 = delta * delta;
            T a = 0.5f;
            T b = v / 2;
            T c = a + b + d2 / 2;
            //
            // Crossover point for calculating p or q is the same
            // as for the noncentral beta:
            //
            T cross = 1 - (b / c) * (1 + d2 / (2 * c * c));
            T result;
            if(x < cross)
            {
               //
               // Calculate p:
               //
               if(x != 0)
               {
                  result = non_central_beta_p(a, b, d2, x, y, pol);
                  result = non_central_t2_p(v, delta, x, y, pol, result);
                  result /= 2;
               }
               else
                  result = 0;
               result += cdf(boost::math::normal_distribution<T, Policy>(), -delta);
            }
            else
            {
               //
               // Calculate q:
               //
               invert = !invert;
               if(x != 0)
               {
                  result = non_central_beta_q(a, b, d2, x, y, pol);
                  result = non_central_t2_q(v, delta, x, y, pol, result);
                  result /= 2;
               }
               else // x == 0
                  result = cdf(complement(boost::math::normal_distribution<T, Policy>(), -delta));
            }
            if(invert)
               result = 1 - result;
            return result;
         }

         template <class T, class Policy>
         T non_central_t_quantile(const char* function, T v, T delta, T p, T q, const Policy&)
         {
            BOOST_MATH_STD_USING
     //       static const char* function = "quantile(non_central_t_distribution<%1%>, %1%)";
     // now passed as function
            typedef typename policies::evaluation<T, Policy>::type value_type;
            typedef typename policies::normalise<
               Policy, 
               policies::promote_float<false>, 
               policies::promote_double<false>, 
               policies::discrete_quantile<>,
               policies::assert_undefined<> >::type forwarding_policy;

               T r;
               if(!detail::check_df_gt0_to_inf(
                  function,
                  v, &r, Policy())
                  ||
               !detail::check_finite(
                  function,
                  delta,
                  &r,
                  Policy())
                  ||
               !detail::check_probability(
                  function,
                  p,
                  &r,
                  Policy()))
                     return r;


            value_type guess = 0;
            if ( ((boost::math::isinf)(v)) || (v > 1 / boost::math::tools::epsilon<T>()) )
            { // Infinite or very large degrees of freedom, so use normal distribution located at delta.
               normal_distribution<T, Policy> n(delta, 1);
               if (p < q)
               {
                 return quantile(n, p);
               }
               else
               {
                 return quantile(complement(n, q));
               }
            }
            else if(v > 3)
            { // Use normal distribution to calculate guess.
               value_type mean = (v > 1 / policies::get_epsilon<T, Policy>()) ? delta : delta * sqrt(v / 2) * tgamma_delta_ratio((v - 1) * 0.5f, T(0.5f));
               value_type var = (v > 1 / policies::get_epsilon<T, Policy>()) ? value_type(1) : (((delta * delta + 1) * v) / (v - 2) - mean * mean);
               if(p < q)
                  guess = quantile(normal_distribution<value_type, forwarding_policy>(mean, var), p);
               else
                  guess = quantile(complement(normal_distribution<value_type, forwarding_policy>(mean, var), q));
            }
            //
            // We *must* get the sign of the initial guess correct, 
            // or our root-finder will fail, so double check it now:
            //
            value_type pzero = non_central_t_cdf(
               static_cast<value_type>(v), 
               static_cast<value_type>(delta), 
               static_cast<value_type>(0), 
               !(p < q), 
               forwarding_policy());
            int s;
            if(p < q)
               s = boost::math::sign(p - pzero);
            else
               s = boost::math::sign(pzero - q);
            if(s != boost::math::sign(guess))
            {
               guess = static_cast<T>(s);
            }

            value_type result = detail::generic_quantile(
               non_central_t_distribution<value_type, forwarding_policy>(v, delta), 
               (p < q ? p : q), 
               guess, 
               (p >= q), 
               function);
            return policies::checked_narrowing_cast<T, forwarding_policy>(
               result, 
               function);
         }

         template <class T, class Policy>
         T non_central_t2_pdf(T n, T delta, T x, T y, const Policy& pol, T init_val)
         {
            BOOST_MATH_STD_USING
            //
            // Variables come first:
            //
            boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
            T errtol = boost::math::policies::get_epsilon<T, Policy>();
            T d2 = delta * delta / 2;
            //
            // k is the starting point for iteration, and is the
            // maximum of the poisson weighting term:
            //
            int k = itrunc(d2);
            T pois, xterm;
            if(k == 0)
               k = 1;
            // Starting Poisson weight:
            pois = gamma_p_derivative(T(k+1), d2, pol) 
               * tgamma_delta_ratio(T(k + 1), T(0.5f))
               * delta / constants::root_two<T>();
            // Starting beta term:
            xterm = x < y
               ? ibeta_derivative(T(k + 1), n / 2, x, pol)
               : ibeta_derivative(n / 2, T(k + 1), y, pol);
            T poisf(pois), xtermf(xterm);
            T sum = init_val;
            if((pois == 0) || (xterm == 0))
               return init_val;

            //
            // Backwards recursion first, this is the stable
            // direction for recursion:
            //
            boost::uintmax_t count = 0;
            for(int i = k; i >= 0; --i)
            {
               T term = xterm * pois;
               sum += term;
               if(((fabs(term/sum) < errtol) && (i != k)) || (term == 0))
                  break;
               pois *= (i + 0.5f) / d2;
               xterm *= (i) / (x * (n / 2 + i));
               ++count;
               if(count > max_iter)
               {
                  return policies::raise_evaluation_error(
                     "pdf(non_central_t_distribution<%1%>, %1%)", 
                     "Series did not converge, closest value was %1%", sum, pol);
               }
            }
            for(int i = k + 1; ; ++i)
            {
               poisf *= d2 / (i + 0.5f);
               xtermf *= (x * (n / 2 + i)) / (i);
               T term = poisf * xtermf;
               sum += term;
               if((fabs(term/sum) < errtol) || (term == 0))
                  break;
               ++count;
               if(count > max_iter)
               {
                  return policies::raise_evaluation_error(
                     "pdf(non_central_t_distribution<%1%>, %1%)", 
                     "Series did not converge, closest value was %1%", sum, pol);
               }
            }
            return sum;
         }

         template <class T, class Policy>
         T non_central_t_pdf(T n, T delta, T t, const Policy& pol)
         {
            BOOST_MATH_STD_USING
            if ((boost::math::isinf)(n))
            { // Infinite degrees of freedom, so use normal distribution located at delta.
               normal_distribution<T, Policy> norm(delta, 1); 
               return pdf(norm, t);
            }
            //
            // Otherwise, for t < 0 we have to use the reflection formula:
            if(t < 0)
            {
               t = -t;
               delta = -delta;
            }
            if(t == 0)
            {
               //
               // Handle this as a special case, using the formula
               // from Weisstein, Eric W. 
               // "Noncentral Student's t-Distribution." 
               // From MathWorld--A Wolfram Web Resource. 
               // http://mathworld.wolfram.com/NoncentralStudentst-Distribution.html 
               // 
               // The formula is simplified thanks to the relation
               // 1F1(a,b,0) = 1.
               //
               return tgamma_delta_ratio(n / 2 + 0.5f, T(0.5f))
                  * sqrt(n / constants::pi<T>()) 
                  * exp(-delta * delta / 2) / 2;
            }
            if(fabs(delta / (4 * n)) < policies::get_epsilon<T, Policy>())
            {
               // Approximate with a Student's T centred on delta,
               // the crossover point is based on eq 2.6 from
               // "A Comparison of Approximations To Percentiles of the
               // Noncentral t-Distribution".  H. Sahai and M. M. Ojeda,
               // Revista Investigacion Operacional Vol 21, No 2, 2000.
               // Original sources referenced in the above are:
               // "Some Approximations to the Percentage Points of the Noncentral
               // t-Distribution". C. van Eeden. International Statistical Review, 29, 4-31.
               // "Continuous Univariate Distributions".  N.L. Johnson, S. Kotz and
               // N. Balkrishnan. 1995. John Wiley and Sons New York.
               return pdf(students_t_distribution<T, Policy>(n), t - delta);
            }
            //
            // x and y are the corresponding random
            // variables for the noncentral beta distribution,
            // with y = 1 - x:
            //
            T x = t * t / (n + t * t);
            T y = n / (n + t * t);
            T a = 0.5f;
            T b = n / 2;
            T d2 = delta * delta;
            //
            // Calculate pdf:
            //
            T dt = n * t / (n * n + 2 * n * t * t + t * t * t * t);
            T result = non_central_beta_pdf(a, b, d2, x, y, pol);
            T tol = tools::epsilon<T>() * result * 500;
            result = non_central_t2_pdf(n, delta, x, y, pol, result);
            if(result <= tol)
               result = 0;
            result *= dt;
            return result;
         }

         template <class T, class Policy>
         T mean(T v, T delta, const Policy& pol)
         {
            if ((boost::math::isinf)(v))
            {
               return delta;
            }
            BOOST_MATH_STD_USING
            if (v > 1 / boost::math::tools::epsilon<T>() )
            {
              //normal_distribution<T, Policy> n(delta, 1);
              //return boost::math::mean(n); 
              return delta;
            }
            else
            {
             return delta * sqrt(v / 2) * tgamma_delta_ratio((v - 1) * 0.5f, T(0.5f), pol);
            }
            // Other moments use mean so using normal distribution is propagated.
         }

         template <class T, class Policy>
         T variance(T v, T delta, const Policy& pol)
         {
            if ((boost::math::isinf)(v))
            {
               return 1;
            }
            if (delta == 0)
            {  // == Student's t
              return v / (v - 2);
            }
            T result = ((delta * delta + 1) * v) / (v - 2);
            T m = mean(v, delta, pol);
            result -= m * m;
            return result;
         }

         template <class T, class Policy>
         T skewness(T v, T delta, const Policy& pol)
         {
            BOOST_MATH_STD_USING
            if ((boost::math::isinf)(v))
            {
               return 0;
            }
            if(delta == 0)
            { // == Student's t
              return 0;
            }
            T mean = boost::math::detail::mean(v, delta, pol);
            T l2 = delta * delta;
            T var = ((l2 + 1) * v) / (v - 2) - mean * mean;
            T result = -2 * var;
            result += v * (l2 + 2 * v - 3) / ((v - 3) * (v - 2));
            result *= mean;
            result /= pow(var, T(1.5f));
            return result;
         }

         template <class T, class Policy>
         T kurtosis_excess(T v, T delta, const Policy& pol)
         {
            BOOST_MATH_STD_USING
            if ((boost::math::isinf)(v))
            {
               return 3;
            }
            if (delta == 0)
            { // == Student's t
              return 3;
            }
            T mean = boost::math::detail::mean(v, delta, pol);
            T l2 = delta * delta;
            T var = ((l2 + 1) * v) / (v - 2) - mean * mean;
            T result = -3 * var;
            result += v * (l2 * (v + 1) + 3 * (3 * v - 5)) / ((v - 3) * (v - 2));
            result *= -mean * mean;
            result += v * v * (l2 * l2 + 6 * l2 + 3) / ((v - 4) * (v - 2));
            result /= var * var;
            return result;
         }

#if 0
         // 
         // This code is disabled, since there can be multiple answers to the
         // question, and it's not clear how to find the "right" one.
         //
         template <class RealType, class Policy>
         struct t_degrees_of_freedom_finder
         {
            t_degrees_of_freedom_finder(
               RealType delta_, RealType x_, RealType p_, bool c)
               : delta(delta_), x(x_), p(p_), comp(c) {}

            RealType operator()(const RealType& v)
            {
               non_central_t_distribution<RealType, Policy> d(v, delta);
               return comp ?
                  p - cdf(complement(d, x))
                  : cdf(d, x) - p;
            }
         private:
            RealType delta;
            RealType x;
            RealType p;
            bool comp;
         };

         template <class RealType, class Policy>
         inline RealType find_t_degrees_of_freedom(
            RealType delta, RealType x, RealType p, RealType q, const Policy& pol)
         {
            const char* function = "non_central_t<%1%>::find_degrees_of_freedom";
            if((p == 0) || (q == 0))
            {
               //
               // Can't a thing if one of p and q is zero:
               //
               return policies::raise_evaluation_error<RealType>(function, 
                  "Can't find degrees of freedom when the probability is 0 or 1, only possible answer is %1%", 
                  RealType(std::numeric_limits<RealType>::quiet_NaN()), Policy());
            }
            t_degrees_of_freedom_finder<RealType, Policy> f(delta, x, p < q ? p : q, p < q ? false : true);
            tools::eps_tolerance<RealType> tol(policies::digits<RealType, Policy>());
            boost::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
            //
            // Pick an initial guess:
            //
            RealType guess = 200;
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
         struct t_non_centrality_finder
         {
            t_non_centrality_finder(
               RealType v_, RealType x_, RealType p_, bool c)
               : v(v_), x(x_), p(p_), comp(c) {}

            RealType operator()(const RealType& delta)
            {
               non_central_t_distribution<RealType, Policy> d(v, delta);
               return comp ?
                  p - cdf(complement(d, x))
                  : cdf(d, x) - p;
            }
         private:
            RealType v;
            RealType x;
            RealType p;
            bool comp;
         };

         template <class RealType, class Policy>
         inline RealType find_t_non_centrality(
            RealType v, RealType x, RealType p, RealType q, const Policy& pol)
         {
            const char* function = "non_central_t<%1%>::find_t_non_centrality";
            if((p == 0) || (q == 0))
            {
               //
               // Can't do a thing if one of p and q is zero:
               //
               return policies::raise_evaluation_error<RealType>(function, 
                  "Can't find non-centrality parameter when the probability is 0 or 1, only possible answer is %1%", 
                  RealType(std::numeric_limits<RealType>::quiet_NaN()), Policy());
            }
            t_non_centrality_finder<RealType, Policy> f(v, x, p < q ? p : q, p < q ? false : true);
            tools::eps_tolerance<RealType> tol(policies::digits<RealType, Policy>());
            boost::uintmax_t max_iter = policies::get_max_root_iterations<Policy>();
            //
            // Pick an initial guess that we know is the right side of
            // zero:
            //
            RealType guess;
            if(f(0) < 0)
               guess = 1;
            else
               guess = -1;
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
#endif
      } // namespace detail ======================================================================

      template <class RealType = double, class Policy = policies::policy<> >
      class non_central_t_distribution
      {
      public:
         typedef RealType value_type;
         typedef Policy policy_type;

         non_central_t_distribution(RealType v_, RealType lambda) : v(v_), ncp(lambda)
         { 
            const char* function = "boost::math::non_central_t_distribution<%1%>::non_central_t_distribution(%1%,%1%)";
            RealType r;
            detail::check_df_gt0_to_inf(
               function,
               v, &r, Policy());
            detail::check_finite(
               function,
               lambda,
               &r,
               Policy());
         } // non_central_t_distribution constructor.

         RealType degrees_of_freedom() const
         { // Private data getter function.
            return v;
         }
         RealType non_centrality() const
         { // Private data getter function.
            return ncp;
         }
#if 0
         // 
         // This code is disabled, since there can be multiple answers to the
         // question, and it's not clear how to find the "right" one.
         //
         static RealType find_degrees_of_freedom(RealType delta, RealType x, RealType p)
         {
            const char* function = "non_central_t<%1%>::find_degrees_of_freedom";
            typedef typename policies::evaluation<RealType, Policy>::type value_type;
            typedef typename policies::normalise<
               Policy, 
               policies::promote_float<false>, 
               policies::promote_double<false>, 
               policies::discrete_quantile<>,
               policies::assert_undefined<> >::type forwarding_policy;
            value_type result = detail::find_t_degrees_of_freedom(
               static_cast<value_type>(delta), 
               static_cast<value_type>(x), 
               static_cast<value_type>(p), 
               static_cast<value_type>(1-p), 
               forwarding_policy());
            return policies::checked_narrowing_cast<RealType, forwarding_policy>(
               result, 
               function);
         }
         template <class A, class B, class C>
         static RealType find_degrees_of_freedom(const complemented3_type<A,B,C>& c)
         {
            const char* function = "non_central_t<%1%>::find_degrees_of_freedom";
            typedef typename policies::evaluation<RealType, Policy>::type value_type;
            typedef typename policies::normalise<
               Policy, 
               policies::promote_float<false>, 
               policies::promote_double<false>, 
               policies::discrete_quantile<>,
               policies::assert_undefined<> >::type forwarding_policy;
            value_type result = detail::find_t_degrees_of_freedom(
               static_cast<value_type>(c.dist), 
               static_cast<value_type>(c.param1), 
               static_cast<value_type>(1-c.param2), 
               static_cast<value_type>(c.param2), 
               forwarding_policy());
            return policies::checked_narrowing_cast<RealType, forwarding_policy>(
               result, 
               function);
         }
         static RealType find_non_centrality(RealType v, RealType x, RealType p)
         {
            const char* function = "non_central_t<%1%>::find_t_non_centrality";
            typedef typename policies::evaluation<RealType, Policy>::type value_type;
            typedef typename policies::normalise<
               Policy, 
               policies::promote_float<false>, 
               policies::promote_double<false>, 
               policies::discrete_quantile<>,
               policies::assert_undefined<> >::type forwarding_policy;
            value_type result = detail::find_t_non_centrality(
               static_cast<value_type>(v), 
               static_cast<value_type>(x), 
               static_cast<value_type>(p), 
               static_cast<value_type>(1-p), 
               forwarding_policy());
            return policies::checked_narrowing_cast<RealType, forwarding_policy>(
               result, 
               function);
         }
         template <class A, class B, class C>
         static RealType find_non_centrality(const complemented3_type<A,B,C>& c)
         {
            const char* function = "non_central_t<%1%>::find_t_non_centrality";
            typedef typename policies::evaluation<RealType, Policy>::type value_type;
            typedef typename policies::normalise<
               Policy, 
               policies::promote_float<false>, 
               policies::promote_double<false>, 
               policies::discrete_quantile<>,
               policies::assert_undefined<> >::type forwarding_policy;
            value_type result = detail::find_t_non_centrality(
               static_cast<value_type>(c.dist), 
               static_cast<value_type>(c.param1), 
               static_cast<value_type>(1-c.param2), 
               static_cast<value_type>(c.param2), 
               forwarding_policy());
            return policies::checked_narrowing_cast<RealType, forwarding_policy>(
               result, 
               function);
         }
#endif
      private:
         // Data member, initialized by constructor.
         RealType v;   // degrees of freedom
         RealType ncp; // non-centrality parameter
      }; // template <class RealType, class Policy> class non_central_t_distribution

      typedef non_central_t_distribution<double> non_central_t; // Reserved name of type double.

      // Non-member functions to give properties of the distribution.

      template <class RealType, class Policy>
      inline const std::pair<RealType, RealType> range(const non_central_t_distribution<RealType, Policy>& /* dist */)
      { // Range of permissible values for random variable k.
         using boost::math::tools::max_value;
         return std::pair<RealType, RealType>(-max_value<RealType>(), max_value<RealType>());
      }

      template <class RealType, class Policy>
      inline const std::pair<RealType, RealType> support(const non_central_t_distribution<RealType, Policy>& /* dist */)
      { // Range of supported values for random variable k.
         // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
         using boost::math::tools::max_value;
         return std::pair<RealType, RealType>(-max_value<RealType>(), max_value<RealType>());
      }

      template <class RealType, class Policy>
      inline RealType mode(const non_central_t_distribution<RealType, Policy>& dist)
      { // mode.
         static const char* function = "mode(non_central_t_distribution<%1%> const&)";
         RealType v = dist.degrees_of_freedom();
         RealType l = dist.non_centrality();
         RealType r;
         if(!detail::check_df_gt0_to_inf(
            function,
            v, &r, Policy())
            ||
         !detail::check_finite(
            function,
            l,
            &r,
            Policy()))
               return (RealType)r;

         BOOST_MATH_STD_USING

         RealType m = v < 3 ? 0 : detail::mean(v, l, Policy());
         RealType var = v < 4 ? 1 : detail::variance(v, l, Policy());

         return detail::generic_find_mode(
            dist, 
            m,
            function,
            sqrt(var));
      }

      template <class RealType, class Policy>
      inline RealType mean(const non_central_t_distribution<RealType, Policy>& dist)
      { 
         BOOST_MATH_STD_USING
         const char* function = "mean(const non_central_t_distribution<%1%>&)";
         typedef typename policies::evaluation<RealType, Policy>::type value_type;
         typedef typename policies::normalise<
            Policy, 
            policies::promote_float<false>, 
            policies::promote_double<false>, 
            policies::discrete_quantile<>,
            policies::assert_undefined<> >::type forwarding_policy;
         RealType v = dist.degrees_of_freedom();
         RealType l = dist.non_centrality();
         RealType r;
         if(!detail::check_df_gt0_to_inf(
            function,
            v, &r, Policy())
            ||
         !detail::check_finite(
            function,
            l,
            &r,
            Policy()))
               return (RealType)r;
         if(v <= 1)
            return policies::raise_domain_error<RealType>(
               function, 
               "The non-central t distribution has no defined mean for degrees of freedom <= 1: got v=%1%.", v, Policy());
         // return l * sqrt(v / 2) * tgamma_delta_ratio((v - 1) * 0.5f, RealType(0.5f));
         return policies::checked_narrowing_cast<RealType, forwarding_policy>(
            detail::mean(static_cast<value_type>(v), static_cast<value_type>(l), forwarding_policy()), function);

      } // mean

      template <class RealType, class Policy>
      inline RealType variance(const non_central_t_distribution<RealType, Policy>& dist)
      { // variance.
         const char* function = "variance(const non_central_t_distribution<%1%>&)";
         typedef typename policies::evaluation<RealType, Policy>::type value_type;
         typedef typename policies::normalise<
            Policy, 
            policies::promote_float<false>, 
            policies::promote_double<false>, 
            policies::discrete_quantile<>,
            policies::assert_undefined<> >::type forwarding_policy;
         BOOST_MATH_STD_USING
         RealType v = dist.degrees_of_freedom();
         RealType l = dist.non_centrality();
         RealType r;
         if(!detail::check_df_gt0_to_inf(
            function,
            v, &r, Policy())
            ||
         !detail::check_finite(
            function,
            l,
            &r,
            Policy()))
               return (RealType)r;
         if(v <= 2)
            return policies::raise_domain_error<RealType>(
               function, 
               "The non-central t distribution has no defined variance for degrees of freedom <= 2: got v=%1%.", v, Policy());
         return policies::checked_narrowing_cast<RealType, forwarding_policy>(
            detail::variance(static_cast<value_type>(v), static_cast<value_type>(l), forwarding_policy()), function);
      }

      // RealType standard_deviation(const non_central_t_distribution<RealType, Policy>& dist)
      // standard_deviation provided by derived accessors.

      template <class RealType, class Policy>
      inline RealType skewness(const non_central_t_distribution<RealType, Policy>& dist)
      { // skewness = sqrt(l).
         const char* function = "skewness(const non_central_t_distribution<%1%>&)";
         typedef typename policies::evaluation<RealType, Policy>::type value_type;
         typedef typename policies::normalise<
            Policy, 
            policies::promote_float<false>, 
            policies::promote_double<false>, 
            policies::discrete_quantile<>,
            policies::assert_undefined<> >::type forwarding_policy;
         RealType v = dist.degrees_of_freedom();
         RealType l = dist.non_centrality();
         RealType r;
         if(!detail::check_df_gt0_to_inf(
            function,
            v, &r, Policy())
            ||
         !detail::check_finite(
            function,
            l,
            &r,
            Policy()))
               return (RealType)r;
         if(v <= 3)
            return policies::raise_domain_error<RealType>(
               function, 
               "The non-central t distribution has no defined skewness for degrees of freedom <= 3: got v=%1%.", v, Policy());;
         return policies::checked_narrowing_cast<RealType, forwarding_policy>(
            detail::skewness(static_cast<value_type>(v), static_cast<value_type>(l), forwarding_policy()), function);
      }

      template <class RealType, class Policy>
      inline RealType kurtosis_excess(const non_central_t_distribution<RealType, Policy>& dist)
      { 
         const char* function = "kurtosis_excess(const non_central_t_distribution<%1%>&)";
         typedef typename policies::evaluation<RealType, Policy>::type value_type;
         typedef typename policies::normalise<
            Policy, 
            policies::promote_float<false>, 
            policies::promote_double<false>, 
            policies::discrete_quantile<>,
            policies::assert_undefined<> >::type forwarding_policy;
         RealType v = dist.degrees_of_freedom();
         RealType l = dist.non_centrality();
         RealType r;
         if(!detail::check_df_gt0_to_inf(
            function,
            v, &r, Policy())
            ||
         !detail::check_finite(
            function,
            l,
            &r,
            Policy()))
               return (RealType)r;
         if(v <= 4)
            return policies::raise_domain_error<RealType>(
               function, 
               "The non-central t distribution has no defined kurtosis for degrees of freedom <= 4: got v=%1%.", v, Policy());;
         return policies::checked_narrowing_cast<RealType, forwarding_policy>(
            detail::kurtosis_excess(static_cast<value_type>(v), static_cast<value_type>(l), forwarding_policy()), function);
      } // kurtosis_excess

      template <class RealType, class Policy>
      inline RealType kurtosis(const non_central_t_distribution<RealType, Policy>& dist)
      {
         return kurtosis_excess(dist) + 3;
      }

      template <class RealType, class Policy>
      inline RealType pdf(const non_central_t_distribution<RealType, Policy>& dist, const RealType& t)
      { // Probability Density/Mass Function.
         const char* function = "pdf(non_central_t_distribution<%1%>, %1%)";
         typedef typename policies::evaluation<RealType, Policy>::type value_type;
         typedef typename policies::normalise<
            Policy, 
            policies::promote_float<false>, 
            policies::promote_double<false>, 
            policies::discrete_quantile<>,
            policies::assert_undefined<> >::type forwarding_policy;

         RealType v = dist.degrees_of_freedom();
         RealType l = dist.non_centrality();
         RealType r;
         if(!detail::check_df_gt0_to_inf(
            function,
            v, &r, Policy())
            ||
         !detail::check_finite(
            function,
            l,
            &r,
            Policy())
            ||
         !detail::check_x(
            function,
            t,
            &r,
            Policy()))
               return (RealType)r;
         return policies::checked_narrowing_cast<RealType, forwarding_policy>(
            detail::non_central_t_pdf(static_cast<value_type>(v), 
               static_cast<value_type>(l), 
               static_cast<value_type>(t), 
               Policy()),
            function);
      } // pdf

      template <class RealType, class Policy>
      RealType cdf(const non_central_t_distribution<RealType, Policy>& dist, const RealType& x)
      { 
         const char* function = "boost::math::cdf(non_central_t_distribution<%1%>&, %1%)";
//   was const char* function = "boost::math::non_central_t_distribution<%1%>::cdf(%1%)";
         typedef typename policies::evaluation<RealType, Policy>::type value_type;
         typedef typename policies::normalise<
            Policy, 
            policies::promote_float<false>, 
            policies::promote_double<false>, 
            policies::discrete_quantile<>,
            policies::assert_undefined<> >::type forwarding_policy;

         RealType v = dist.degrees_of_freedom();
         RealType l = dist.non_centrality();
         RealType r;
         if(!detail::check_df_gt0_to_inf(
            function,
            v, &r, Policy())
            ||
         !detail::check_finite(
            function,
            l,
            &r,
            Policy())
            ||
         !detail::check_x(
            function,
            x,
            &r,
            Policy()))
               return (RealType)r;
          if ((boost::math::isinf)(v))
          { // Infinite degrees of freedom, so use normal distribution located at delta.
             normal_distribution<RealType, Policy> n(l, 1); 
             cdf(n, x);
              //return cdf(normal_distribution<RealType, Policy>(l, 1), x);
          }

         if(l == 0)
         { // NO non-centrality, so use Student's t instead.
            return cdf(students_t_distribution<RealType, Policy>(v), x);
         }
         return policies::checked_narrowing_cast<RealType, forwarding_policy>(
            detail::non_central_t_cdf(
               static_cast<value_type>(v), 
               static_cast<value_type>(l), 
               static_cast<value_type>(x), 
               false, Policy()),
            function);
      } // cdf

      template <class RealType, class Policy>
      RealType cdf(const complemented2_type<non_central_t_distribution<RealType, Policy>, RealType>& c)
      { // Complemented Cumulative Distribution Function
  // was       const char* function = "boost::math::non_central_t_distribution<%1%>::cdf(%1%)";
         const char* function = "boost::math::cdf(const complement(non_central_t_distribution<%1%>&), %1%)";
         typedef typename policies::evaluation<RealType, Policy>::type value_type;
         typedef typename policies::normalise<
            Policy, 
            policies::promote_float<false>, 
            policies::promote_double<false>, 
            policies::discrete_quantile<>,
            policies::assert_undefined<> >::type forwarding_policy;

         non_central_t_distribution<RealType, Policy> const& dist = c.dist;
         RealType x = c.param;
         RealType v = dist.degrees_of_freedom();
         RealType l = dist.non_centrality(); // aka delta
         RealType r;
         if(!detail::check_df_gt0_to_inf(
            function,
            v, &r, Policy())
            ||
         !detail::check_finite(
            function,
            l,
            &r,
            Policy())
            ||
         !detail::check_x(
            function,
            x,
            &r,
            Policy()))
               return (RealType)r;

         if ((boost::math::isinf)(v))
         { // Infinite degrees of freedom, so use normal distribution located at delta.
             normal_distribution<RealType, Policy> n(l, 1); 
             return cdf(complement(n, x));
         }
         if(l == 0)
         { // zero non-centrality so use Student's t distribution.
            return cdf(complement(students_t_distribution<RealType, Policy>(v), x));
         }
         return policies::checked_narrowing_cast<RealType, forwarding_policy>(
            detail::non_central_t_cdf(
               static_cast<value_type>(v), 
               static_cast<value_type>(l), 
               static_cast<value_type>(x), 
               true, Policy()),
            function);
      } // ccdf

      template <class RealType, class Policy>
      inline RealType quantile(const non_central_t_distribution<RealType, Policy>& dist, const RealType& p)
      { // Quantile (or Percent Point) function.
         static const char* function = "quantile(const non_central_t_distribution<%1%>, %1%)";
         RealType v = dist.degrees_of_freedom();
         RealType l = dist.non_centrality();
         return detail::non_central_t_quantile(function, v, l, p, RealType(1-p), Policy());
      } // quantile

      template <class RealType, class Policy>
      inline RealType quantile(const complemented2_type<non_central_t_distribution<RealType, Policy>, RealType>& c)
      { // Quantile (or Percent Point) function.
         static const char* function = "quantile(const complement(non_central_t_distribution<%1%>, %1%))";
         non_central_t_distribution<RealType, Policy> const& dist = c.dist;
         RealType q = c.param;
         RealType v = dist.degrees_of_freedom();
         RealType l = dist.non_centrality();
         return detail::non_central_t_quantile(function, v, l, RealType(1-q), q, Policy());
      } // quantile complement.

   } // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_MATH_SPECIAL_NON_CENTRAL_T_HPP


/* non_central_t.hpp
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
*/