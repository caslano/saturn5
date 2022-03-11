
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HYPERGEOMETRIC_1F1_LARGE_ABZ_HPP_
#define BOOST_HYPERGEOMETRIC_1F1_LARGE_ABZ_HPP_

#include <boost/math/special_functions/detail/hypergeometric_1F1_bessel.hpp>
#include <boost/math/special_functions/detail/hypergeometric_series.hpp>
#include <boost/math/special_functions/gamma.hpp>


  namespace boost { namespace math { namespace detail {

     template <class T>
     inline bool is_negative_integer(const T& x)
     {
        using std::floor;
        return (x <= 0) && (floor(x) == x);
     }


     template <class T, class Policy>
     struct hypergeometric_1F1_igamma_series
     {
        enum{ cache_size = 64 };

        typedef T result_type;
        hypergeometric_1F1_igamma_series(const T& alpha, const T& delta, const T& x, const Policy& pol)
           : delta_poch(-delta), alpha_poch(alpha), x(x), k(0), cache_offset(0), pol(pol)
        {
           BOOST_MATH_STD_USING
           T log_term = log(x) * -alpha;
           log_scaling = itrunc(log_term - 3 - boost::math::tools::log_min_value<T>() / 50);
           term = exp(log_term - log_scaling);
           refill_cache();
        }
        T operator()()
        {
           if (k - cache_offset >= cache_size)
           {
              cache_offset += cache_size;
              refill_cache();
           }
           T result = term * gamma_cache[k - cache_offset];
           term *= delta_poch * alpha_poch / (++k * x);
           delta_poch += 1;
           alpha_poch += 1;
           return result;
        }
        void refill_cache()
        {
           typedef typename lanczos::lanczos<T, Policy>::type lanczos_type;

           gamma_cache[cache_size - 1] = boost::math::gamma_p(alpha_poch + ((int)cache_size - 1), x, pol);
           for (int i = cache_size - 1; i > 0; --i)
           {
              gamma_cache[i - 1] = gamma_cache[i] >= 1 ? T(1) : T(gamma_cache[i] + regularised_gamma_prefix(T(alpha_poch + (i - 1)), x, pol, lanczos_type()) / (alpha_poch + (i - 1)));
           }
        }
        T delta_poch, alpha_poch, x, term;
        T gamma_cache[cache_size];
        int k;
        int log_scaling;
        int cache_offset;
        Policy pol;
     };

     template <class T, class Policy>
     T hypergeometric_1F1_igamma(const T& a, const T& b, const T& x, const T& b_minus_a, const Policy& pol, int& log_scaling)
     {
        BOOST_MATH_STD_USING
        if (b_minus_a == 0)
        {
           // special case: M(a,a,z) == exp(z)
           int scale = itrunc(x, pol);
           log_scaling += scale;
           return exp(x - scale);
        }
        hypergeometric_1F1_igamma_series<T, Policy> s(b_minus_a, a - 1, x, pol);
        log_scaling += s.log_scaling;
        boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
        boost::math::policies::check_series_iterations<T>("boost::math::tgamma<%1%>(%1%,%1%)", max_iter, pol);
        T log_prefix = x + boost::math::lgamma(b, pol) - boost::math::lgamma(a, pol);
        int scale = itrunc(log_prefix);
        log_scaling += scale;
        return result * exp(log_prefix - scale);
     }

     template <class T, class Policy>
     T hypergeometric_1F1_shift_on_a(T h, const T& a_local, const T& b_local, const T& x, int a_shift, const Policy& pol, int& log_scaling)
     {
        BOOST_MATH_STD_USING
        T a = a_local + a_shift;
        if (a_shift == 0)
           return h;
        else if (a_shift > 0)
        {
           //
           // Forward recursion on a is stable as long as 2a-b+z > 0.
           // If 2a-b+z < 0 then backwards recursion is stable even though
           // the function may be strictly increasing with a.  Potentially
           // we may need to split the recurrence in 2 sections - one using 
           // forward recursion, and one backwards.
           //
           // We will get the next seed value from the ratio
           // on b as that's stable and quick to compute.
           //

           T crossover_a = (b_local - x) / 2;
           int crossover_shift = itrunc(crossover_a - a_local);

           if (crossover_shift > 1)
           {
              //
              // Forwards recursion will start off unstable, but may switch to the stable direction later.
              // Start in the middle and go in both directions:
              //
              if (crossover_shift > a_shift)
                 crossover_shift = a_shift;
              crossover_a = a_local + crossover_shift;
              boost::math::detail::hypergeometric_1F1_recurrence_b_coefficients<T> b_coef(crossover_a, b_local, x);
              boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
              T b_ratio = boost::math::tools::function_ratio_from_backwards_recurrence(b_coef, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
              boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1F1_large_abz<%1%>(%1%,%1%,%1%)", max_iter, pol);
              //
              // Convert to a ratio:
              //         (1+a-b)M(a, b, z) - aM(a+1, b, z) + (b-1)M(a, b-1, z) = 0
              //
              //  hence: M(a+1,b,z) = ((1+a-b) / a) M(a,b,z) + ((b-1) / a) M(a,b,z)/b_ratio
              //
              T first = 1;
              T second = ((1 + crossover_a - b_local) / crossover_a) + ((b_local - 1) / crossover_a) / b_ratio;
              //
              // Recurse down to a_local, compare values and re-normalise first and second:
              //
              boost::math::detail::hypergeometric_1F1_recurrence_a_coefficients<T> a_coef(crossover_a, b_local, x);
              int backwards_scale = 0;
              T comparitor = boost::math::tools::apply_recurrence_relation_backward(a_coef, crossover_shift, second, first, &backwards_scale);
              log_scaling -= backwards_scale;
              if ((h < 1) && (tools::max_value<T>() * h > comparitor))
              {
                 // Need to rescale!
                 int scale = itrunc(log(h), pol) + 1;
                 h *= exp(T(-scale));
                 log_scaling += scale;
              }
              comparitor /= h;
              first /= comparitor;
              second /= comparitor;
              //
              // Now we can recurse forwards for the rest of the range:
              //
              if (crossover_shift < a_shift)
              {
                 boost::math::detail::hypergeometric_1F1_recurrence_a_coefficients<T> a_coef_2(crossover_a + 1, b_local, x);
                 h = boost::math::tools::apply_recurrence_relation_forward(a_coef_2, a_shift - crossover_shift - 1, first, second, &log_scaling);
              }
              else
                 h = first;
           }
           else
           {
              //
              // Regular case where forwards iteration is stable right from the start:
              //
              boost::math::detail::hypergeometric_1F1_recurrence_b_coefficients<T> b_coef(a_local, b_local, x);
              boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
              T b_ratio = boost::math::tools::function_ratio_from_backwards_recurrence(b_coef, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
              boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1F1_large_abz<%1%>(%1%,%1%,%1%)", max_iter, pol);
              //
              // Convert to a ratio:
              //         (1+a-b)M(a, b, z) - aM(a+1, b, z) + (b-1)M(a, b-1, z) = 0
              //
              //  hence: M(a+1,b,z) = ((1+a-b) / a) M(a,b,z) + ((b-1) / a) M(a,b,z)/b_ratio
              //
              T second = ((1 + a_local - b_local) / a_local) * h + ((b_local - 1) / a_local) * h / b_ratio;
              boost::math::detail::hypergeometric_1F1_recurrence_a_coefficients<T> a_coef(a_local + 1, b_local, x);
              h = boost::math::tools::apply_recurrence_relation_forward(a_coef, --a_shift, h, second, &log_scaling);
           }
        }
        else
        {
           //
           // We've calculated h for a larger value of a than we want, and need to recurse down.
           // However, only forward iteration is stable, so calculate the ratio, compare values,
           // and normalise.  Note that we calculate the ratio on b and convert to a since the
           // direction is the minimal solution for N->+INF.
           //
           // IMPORTANT: this is only currently called for a > b and therefore forwards iteration
           // is the only stable direction as we will only iterate down until a ~ b, but we
           // will check this with an assert:
           //
           BOOST_ASSERT(2 * a - b_local + x > 0);
           boost::math::detail::hypergeometric_1F1_recurrence_b_coefficients<T> b_coef(a, b_local, x);
           boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
           T b_ratio = boost::math::tools::function_ratio_from_backwards_recurrence(b_coef, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
           boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1F1_large_abz<%1%>(%1%,%1%,%1%)", max_iter, pol);
           //
           // Convert to a ratio:
           //         (1+a-b)M(a, b, z) - aM(a+1, b, z) + (b-1)M(a, b-1, z) = 0
           //
           //  hence: M(a+1,b,z) = (1+a-b) / a M(a,b,z) + (b-1) / a M(a,b,z)/ (M(a,b,z)/M(a,b-1,z))
           //
           T first = 1;  // arbitrary value;
           T second = ((1 + a - b_local) / a) + ((b_local - 1) / a) * (1 / b_ratio);

           if (a_shift == -1)
              h = h / second;
           else
           {
              boost::math::detail::hypergeometric_1F1_recurrence_a_coefficients<T> a_coef(a + 1, b_local, x);
              T comparitor = boost::math::tools::apply_recurrence_relation_forward(a_coef, -(a_shift + 1), first, second);
              if (boost::math::tools::min_value<T>() * comparitor > h)
              {
                 // Ooops, need to rescale h:
                 int rescale = itrunc(log(fabs(h)));
                 T scale = exp(T(-rescale));
                 h *= scale;
                 log_scaling += rescale;
              }
              h = h / comparitor;
           }
        }
        return h;
     }

     template <class T, class Policy>
     T hypergeometric_1F1_shift_on_b(T h, const T& a, const T& b_local, const T& x, int b_shift, const Policy& pol, int& log_scaling)
     {
        BOOST_MATH_STD_USING

        T b = b_local + b_shift;
        if (b_shift == 0)
           return h;
        else if (b_shift > 0)
        {
           //
           // We get here for b_shift > 0 when b > z.  We can't use forward recursion on b - it's unstable,
           // so grab the ratio and work backwards to b - b_shift and normalise.
           //
           boost::math::detail::hypergeometric_1F1_recurrence_b_coefficients<T> b_coef(a, b, x);
           boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();

           T first = 1;  // arbitrary value;
           T second = 1 / boost::math::tools::function_ratio_from_backwards_recurrence(b_coef, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
           boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1F1_large_abz<%1%>(%1%,%1%,%1%)", max_iter, pol);
           if (b_shift == 1)
              h = h / second;
           else
           {
              //
              // Reset coefficients and recurse:
              //
              boost::math::detail::hypergeometric_1F1_recurrence_b_coefficients<T> b_coef_2(a, b - 1, x);
              int local_scale = 0;
              T comparitor = boost::math::tools::apply_recurrence_relation_backward(b_coef_2, --b_shift, first, second, &local_scale);
              log_scaling -= local_scale;
              if (boost::math::tools::min_value<T>() * comparitor > h)
              {
                 // Ooops, need to rescale h:
                 int rescale = itrunc(log(fabs(h)));
                 T scale = exp(T(-rescale));
                 h *= scale;
                 log_scaling += rescale;
              }
              h = h / comparitor;
           }
        }
        else
        {
           T second;
           if (a == b_local)
           {
               // recurrence is trivial for a == b and method of ratios fails as the c-term goes to zero:
              second = -b_local * (1 - b_local - x) * h / (b_local * (b_local - 1));
           }
           else
           {
              BOOST_ASSERT(!is_negative_integer(b - a));
              boost::math::detail::hypergeometric_1F1_recurrence_b_coefficients<T> b_coef(a, b_local, x);
              boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
              second = h / boost::math::tools::function_ratio_from_backwards_recurrence(b_coef, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
              boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1F1_large_abz<%1%>(%1%,%1%,%1%)", max_iter, pol);
           }
           if (b_shift == -1)
              h = second;
           else
           {
              boost::math::detail::hypergeometric_1F1_recurrence_b_coefficients<T> b_coef_2(a, b_local - 1, x);
              h = boost::math::tools::apply_recurrence_relation_backward(b_coef_2, -(++b_shift), h, second, &log_scaling);
           }
        }
        return h;
     }


     template <class T, class Policy>
     T hypergeometric_1F1_large_igamma(const T& a, const T& b, const T& x, const T& b_minus_a, const Policy& pol, int& log_scaling)
     {
        BOOST_MATH_STD_USING
        //
        // We need a < b < z in order to ensure there's at least a chance of convergence,
        // we can use recurrence relations to shift forwards on a+b or just a to achieve this,
        // for decent accuracy, try to keep 2b - 1 < a < 2b < z
        //
        int b_shift = b * 2 < x ? 0 : itrunc(b - x / 2);
        int a_shift = a > b - b_shift ? -itrunc(b - b_shift - a - 1) : -itrunc(b - b_shift - a);

        if (a_shift < 0)
        {
           // Might as well do all the shifting on b as scale a downwards:
           b_shift -= a_shift;
           a_shift = 0;
        }

        T a_local = a - a_shift;
        T b_local = b - b_shift;
        T b_minus_a_local = (a_shift == 0) && (b_shift == 0) ? b_minus_a : b_local - a_local;
        int local_scaling = 0;
        T h = hypergeometric_1F1_igamma(a_local, b_local, x, b_minus_a_local, pol, local_scaling);
        log_scaling += local_scaling;

        //
        // Apply shifts on a and b as required:
        //
        h = hypergeometric_1F1_shift_on_a(h, a_local, b_local, x, a_shift, pol, log_scaling);
        h = hypergeometric_1F1_shift_on_b(h, a, b_local, x, b_shift, pol, log_scaling);

        return h;
     }

     template <class T, class Policy>
     T hypergeometric_1F1_large_series(const T& a, const T& b, const T& z, const Policy& pol, int& log_scaling)
     {
        BOOST_MATH_STD_USING
        //
        // We make a small, and b > z:
        //
        int a_shift(0), b_shift(0);
        if (a * z > b)
        {
           a_shift = itrunc(a) - 5;
           b_shift = b < z ? itrunc(b - z - 1) : 0;
        }
        //
        // If a_shift is trivially small, there's really not much point in losing
        // accuracy to save a couple of iterations:
        //
        if (a_shift < 5)
           a_shift = 0;
        T a_local = a - a_shift;
        T b_local = b - b_shift;
        T h = boost::math::detail::hypergeometric_1F1_generic_series(a_local, b_local, z, pol, log_scaling, "hypergeometric_1F1_large_series<%1%>(a,b,z)");
        //
        // Apply shifts on a and b as required:
        //
        if (a_shift && (a_local == 0))
        {
           //
           // Shifting on a via method of ratios in hypergeometric_1F1_shift_on_a fails when
           // a_local == 0.  However, the value of h calculated was trivial (unity), so
           // calculate a second 1F1 for a == 1 and recurse as normal:
           //
           int scale = 0;
           T h2 = boost::math::detail::hypergeometric_1F1_generic_series(T(a_local + 1), b_local, z, pol, scale, "hypergeometric_1F1_large_series<%1%>(a,b,z)");
           if (scale != log_scaling)
           {
              h2 *= exp(T(scale - log_scaling));
           }
           boost::math::detail::hypergeometric_1F1_recurrence_a_coefficients<T> coef(a_local + 1, b_local, z);
           h = boost::math::tools::apply_recurrence_relation_forward(coef, a_shift - 1, h, h2, &log_scaling);
           h = hypergeometric_1F1_shift_on_b(h, a, b_local, z, b_shift, pol, log_scaling);
        }
        else
        {
           h = hypergeometric_1F1_shift_on_a(h, a_local, b_local, z, a_shift, pol, log_scaling);
           h = hypergeometric_1F1_shift_on_b(h, a, b_local, z, b_shift, pol, log_scaling);
        }
        return h;
     }

     template <class T, class Policy>
     T hypergeometric_1F1_large_13_3_6_series(const T& a, const T& b, const T& z, const Policy& pol, int& log_scaling)
     {
        BOOST_MATH_STD_USING
        //
        // A&S 13.3.6 is good only when a ~ b, but isn't too fussy on the size of z.
        // So shift b to match a (b shifting seems to be more stable via method of ratios).
        //
        int b_shift = itrunc(b - a);
        T b_local = b - b_shift;
        T h = boost::math::detail::hypergeometric_1F1_AS_13_3_6(a, b_local, z, T(b_local - a), pol, log_scaling);
        return hypergeometric_1F1_shift_on_b(h, a, b_local, z, b_shift, pol, log_scaling);
     }

     template <class T, class Policy>
     T hypergeometric_1F1_large_abz(const T& a, const T& b, const T& z, const Policy& pol, int& log_scaling)
     {
        BOOST_MATH_STD_USING
        //
        // This is the selection logic to pick the "best" method.
        // We have a,b,z >> 0 and need to compute the approximate cost of each method
        // and then select whichever wins out.
        //
        enum method
        {
           method_series = 0,
           method_shifted_series,
           method_gamma,
           method_bessel
        };
        //
        // Cost of direct series, is the approx number of terms required until we hit convergence:
        //
        T current_cost = (sqrt(16 * z * (3 * a + z) + 9 * b * b - 24 * b * z) - 3 * b + 4 * z) / 6;
        method current_method = method_series;
        //
        // Cost of shifted series, is the number of recurrences required to move to a zone where
        // the series is convergent right from the start.
        // Note that recurrence relations fail for very small b, and too many recurrences on a
        // will completely destroy all our digits.
        // Also note that the method fails when b-a is a negative integer unless b is already
        // larger than z and thus does not need shifting.
        //
        T cost = a + ((b < z) ? T(z - b) : T(0));
        if((b > 1) && (cost < current_cost) && ((b > z) || !is_negative_integer(b-a)))
        {
           current_method = method_shifted_series;
           current_cost = cost;
        }
        //
        // Cost for gamma function method is the number of recurrences required to move it
        // into a convergent zone, note that recurrence relations fail for very small b.
        // Also add on a fudge factor to account for the fact that this method is both
        // more expensive to compute (requires gamma functions), and less accurate than the
        // methods above:
        //
        T b_shift = fabs(b * 2 < z ? T(0) : T(b - z / 2));
        T a_shift = fabs(a > b - b_shift ? T(-(b - b_shift - a - 1)) : T(-(b - b_shift - a)));
        cost = 1000 + b_shift + a_shift;
        if((b > 1) && (cost <= current_cost))
        {
           current_method = method_gamma;
           current_cost = cost;
        }
        //
        // Cost for bessel approximation is the number of recurrences required to make a ~ b,
        // Note that recurrence relations fail for very small b.  We also have issue with large
        // z: either overflow/numeric instability or else the series goes divergent.  We seem to be
        // OK for z smaller than log_max_value<Quad> though, maybe we can stretch a little further
        // but that's not clear...
        // Also need to add on a fudge factor to the cost to account for the fact that we need
        // to calculate the Bessel functions, this is not quite as high as the gamma function 
        // method above as this is generally more accurate and so preferred if the methods are close:
        //
        cost = 50 + fabs(b - a);
        if((b > 1) && (cost <= current_cost) && (z < tools::log_max_value<T>()) && (z < 11356) && (b - a != 0.5f))
        {
           current_method = method_bessel;
           current_cost = cost;
        }

        switch (current_method)
        {
        case method_series:
           return detail::hypergeometric_1F1_generic_series(a, b, z, pol, log_scaling, "hypergeometric_1f1_large_abz<%1%>(a,b,z)");
        case method_shifted_series:
           return detail::hypergeometric_1F1_large_series(a, b, z, pol, log_scaling);
        case method_gamma:
           return detail::hypergeometric_1F1_large_igamma(a, b, z, T(b - a), pol, log_scaling);
        case method_bessel:
           return detail::hypergeometric_1F1_large_13_3_6_series(a, b, z, pol, log_scaling);
        }
        return 0; // We don't get here!
     }

  } } } // namespaces

#endif // BOOST_HYPERGEOMETRIC_1F1_LARGE_ABZ_HPP_

/* hypergeometric_1F1_large_abz.hpp
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
*/