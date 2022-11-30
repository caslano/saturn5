
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
#include <boost/math/special_functions/trunc.hpp>

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
           log_scaling = lltrunc(log_term - 3 - boost::math::tools::log_min_value<T>() / 50);
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
        long long log_scaling;
        int cache_offset;
        Policy pol;
     };

     template <class T, class Policy>
     T hypergeometric_1F1_igamma(const T& a, const T& b, const T& x, const T& b_minus_a, const Policy& pol, long long& log_scaling)
     {
        BOOST_MATH_STD_USING
        if (b_minus_a == 0)
        {
           // special case: M(a,a,z) == exp(z)
           long long scale = lltrunc(x, pol);
           log_scaling += scale;
           return exp(x - scale);
        }
        hypergeometric_1F1_igamma_series<T, Policy> s(b_minus_a, a - 1, x, pol);
        log_scaling += s.log_scaling;
        std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
        boost::math::policies::check_series_iterations<T>("boost::math::tgamma<%1%>(%1%,%1%)", max_iter, pol);
        T log_prefix = x + boost::math::lgamma(b, pol) - boost::math::lgamma(a, pol);
        long long scale = lltrunc(log_prefix);
        log_scaling += scale;
        return result * exp(log_prefix - scale);
     }

     template <class T, class Policy>
     T hypergeometric_1F1_shift_on_a(T h, const T& a_local, const T& b_local, const T& x, int a_shift, const Policy& pol, long long& log_scaling)
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
              std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
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
              long long backwards_scale = 0;
              T comparitor = boost::math::tools::apply_recurrence_relation_backward(a_coef, crossover_shift, second, first, &backwards_scale);
              log_scaling -= backwards_scale;
              if ((h < 1) && (tools::max_value<T>() * h > comparitor))
              {
                 // Need to rescale!
                 long long scale = lltrunc(log(h), pol) + 1;
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
              std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
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
           BOOST_MATH_ASSERT(2 * a - b_local + x > 0);
           boost::math::detail::hypergeometric_1F1_recurrence_b_coefficients<T> b_coef(a, b_local, x);
           std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
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
                 long long rescale = lltrunc(log(fabs(h)));
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
     T hypergeometric_1F1_shift_on_b(T h, const T& a, const T& b_local, const T& x, int b_shift, const Policy& pol, long long& log_scaling)
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
           std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();

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
              long long local_scale = 0;
              T comparitor = boost::math::tools::apply_recurrence_relation_backward(b_coef_2, --b_shift, first, second, &local_scale);
              log_scaling -= local_scale;
              if (boost::math::tools::min_value<T>() * comparitor > h)
              {
                 // Ooops, need to rescale h:
                 long long rescale = lltrunc(log(fabs(h)));
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
              BOOST_MATH_ASSERT(!is_negative_integer(b - a));
              boost::math::detail::hypergeometric_1F1_recurrence_b_coefficients<T> b_coef(a, b_local, x);
              std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
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
     T hypergeometric_1F1_large_igamma(const T& a, const T& b, const T& x, const T& b_minus_a, const Policy& pol, long long& log_scaling)
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
        long long local_scaling = 0;
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
     T hypergeometric_1F1_large_series(const T& a, const T& b, const T& z, const Policy& pol, long long& log_scaling)
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
           long long scale = 0;
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
     T hypergeometric_1F1_large_13_3_6_series(const T& a, const T& b, const T& z, const Policy& pol, long long& log_scaling)
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
     T hypergeometric_1F1_large_abz(const T& a, const T& b, const T& z, const Policy& pol, long long& log_scaling)
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
scKcD4/gmiQm8KIzgQOgifW4ED3LZB/5D1luRe0mN8vj9BETt1XPUvqtg4sZ2QSxW2dbYCJfFivBK7k6J3Gy3zbQAljjROPNYIPsfomOkVHoZzQ+esR7NRF3oblxN4L9CFAnP19+mf0cenoVZNZQSStIElg5gBgpiJF8Vz9xzvDIJ0qoXtZfhL1BkttYJN2TVYEFLEeoYelPa6H0j1BMhGSquwUoXQaYuWwbAJRGYLEZwE91CKufP7R1fC6DmgkRZBNfS78DbT3NzWRLLYBrBy2XersmX/wx+GQxtIeT+evcUjkyZT5qakA0XQak9OjPR98SB754qpMiI+pRWQZXjxUSTlgv1tjsVApmy8RVufdxR5Zwe1E6GJzlhCBRhikrmB7s6ZOAp2MgdQ/uk6G0MR9un7ugMVXtErpBOTKjTiCI+l4p5kUzon54ExhAOyn5GHYU3A3wyQz70VSNGOjy+Ubpi+iABtMdxBOZp49XFzOKiBgpWF7xhq73Z5TbyZRJ6qfu17N6PiP/Eshrz83UsWxrt0E/RXcuzcvfrLsNd3FBhGJKdIRozKVSBZIQGRAZDLN6dmsWAdKL2hZrvxaAbe9f+A8O3qP2+j4axSMapk52EQTrrcjAQdfyVqTN7aEDuwAacHwfY/8MyPr+GTHyz/+Yu2nOVJQ8cPcd1CHZC9Qk8gtZSj6ZBKWbQg67PmB679SlY/k/Oh4Sh3p/Zhr69j+8fBAIExQD/4f93+rf+k9+iTj1cf3IRl/7x0/gEO+Q3s1NG5aKCokeLH55J0+1YZjEasVA33CJhhAgq0ALdmvOX1zC/UUGYVEknI44waNfuJD6ScgVL1rhNUpqUXln45LWF8F14E1tmIMWYDFPVN7+s3Mkr9hgLytgny0zxN6u7ARJXPBDgfCgd1rMDWB94GijJSN9vyVuWKMuSxDBJORfRTbIWpkiMC5gAWalZ+MtXu7l+uWFy2Mr8+DnpOWehU5j38gG1Q0So9JfrrYDPmM/Xnj/K5s65+HtY8oAB2DOjFzyGf5C+8MWKI8Zv7CuWOhLfjiv9bRFA07ZFX8LWD1Vrnn+MxcT2109V5+qr0/whP2q4nARFnAq7Eg9ja4ONA/0/gsid7bjIgsW6fHmO6inNp55eogkTbgPbD/W6MePgPsccMwXM8qL3dm+SkhmPkyTikMyX8QtAkofBbDixZUK/eie34xJYgM/MEIS7MPG/qIIAPh8jrK4QUcK1F4jNLOeBTM41C/jPccjiswFceGFWVYNXMLaVPQfBt0gsWMXBWAtElAmlz2qm9gao5UfRXgaaPGXjxlOpkE77DE9iA1ZZECJMpA6xz6a2FPsXi3B2yGeIiZBJLdYyo1m8RcdoxpxnPdxnGclUw8z4SUYuiQiFucwP97CyV8bIhB+lbd6EbZFLsNFqDpYS0gXpZHiiQx3sos0CR5iXPqGst3va2lxqsgU1IG72fi05oo52V5WfjVLv4OMHrsrsvebBu7+93ZTlx3b+dlOhZX31OHqKVHyEI0E/KguZXxUumhA2qmbC3bF9bSw4g/YqLfhdbAXdaboES1y/3PFxqHomeDpB/sm3a6Jd4QIEmNxuae1z5oL2ZkKC+1HLl37jQnglIHvx/ADcpOQjIX2Igyea30Fo9CAC5IHeaFgtBcOjjsIiF4fZmqLqgXP+GbMqNYOwyw0EHyHCY0/tIf99xuyrv8CSH+BkBSAF6P/Pt5WXXN9z7Ej0ND+4bcIGOd8gqF7+aD1iadwSNn4tqMEOL0AByz405/U6iNIMVDQ1nRYMzNg7JOG7K22fidpsaGsUVJtrwvvtwBs6viYaUTpGKyoskUaf3uIspXfBWyB7hRkUpzBdaSyN1B3VW0VofYOWVimqbDi/XhazQaVQC8QQbs6IQTgviW4m4TaIKYwZDXQS3Juob9Ql8THlXjJ4EP8fGQXK3yducC6MEIwXUHRozSA7bcRC3rBLm2viyix0oxl8uXpGspzJWamZQZidjtFBb++65SvgAJaJbdK10YhFJWykeZu+ALKQlHOjZelOnti33wJQcMrp7saccZ2DL6Gv0ReKYnhssFQkrdIXp/wxZGQpQ7ShceNfIeqCoYnt09mbR2iym5wudybNQoG0PVdEjOEfRg8d/9kzG1935t3ph9uWWqf7R7umikKw1ulPKOWL7ebI8dIvWZRl5BDdulMgsGgasFIsxWR3UCcAbYlE8Um+MozUktDUGAvtYTEEsc3VO+sF0M4jUM0Oys0ZM7jN0yVHo0IG57Y+5wvJFhW+larLARM298a4TTmuTZQVzAFxmtPBHdfz4xOdQ6N+n0/b8ejiqShATg1UYudA5/1sh1tprbyZZD5LdzcOsB2oENwGyjEJZfe8jBmIiRWKJE+N/KDDQBL9w4eSR2smXKczjhrIkQIwAwetehdcM7AxIXLCk/FaE334vJj9RapQdbtO5H+4bX47Gd2bbfcz5Ti/d3dmAzXU4woSBAF0LFt27Z2bNu2bdu2bbyxbdu2bWunkpPUb6dzK7lDRok3WsdEOxNeQ7J2Mt2MS05hQ3JGl8BRlmoR46uSlbVfe+luvlp5bWOle37i2Qi21ypWbWfy/0XvxeKfiJNzJhQl14WhtwFBfUGFT5lJN77hyLqguhxRN0EZRAoqI2KvJCZ7LeXI74Xgl7j+fHKDrUe+Tp9Qa4cLJbHkScLV08RM3QYeMKprUu5hF+t21Z4+I/5DKYHLmwMn4HfIf+R6Idh5c8cxlxmuQXtky2Zs0kJmvBrpSD2cL2oHw4VzsNXx3gU4CG9tQYHppr/Uoe7N4ZFo7B2e73r5zX9pl2Fe55t9SfkF59M/XdpF4IAhgabY/WR9tRf9FMt16AGpBdX8cn1j9g846pTe/fQKqe+3F7uwXCpRV3J5V+P/8R+Wdo5MWlJxM4U61vAWTDLIdEACw2mOdQDe0pDIqIkh9Ksf5/z29a5yLUicj3w/JQj5wQyAz9n7+lGy/vJrF/z6+nweEKI1ZOAhpHpW3+2y+Dw6Sc366raXjtT9yco2499RG3vGTkuWwUIBtn3wwuvKBOda+uJZvkzoxeH1ZrpwEZYAIplbFUWHWjEbqi3+7+LyVdtRHmAPrQuCoZ2huWYM4x7VK3NzevaE2ekhLULlDRX9WNSc+rxt9HY0jwr7B7AxqQUpgPR0oQv9Ayf8e5EV/0fAasYW1x18bvaA/9h/FdbPiGNTuInIWxwUFCSHN6VQZKuQ/WrMr49z2dzRMYKVowgGO9IAsOabXOnbEFsDW4mbdL+DfreG+Xk1OgLXVqlamsnX7O3sLXaJpC62oQm6cTie8ymYEpyic6Lnp6HimnFQvuTwMm/Pa3ztZqNYK42+ZxNeaduALM1u15NoJK2uAgz4cKJ8Ot9h8N+r+hXU9yRvI0P19onb0hVyhPu8k4TWxUoVWOo9LdEq9tsjCKDRc7YwT5jfY53clGbEUigskGfSmkgfxCmUQsap+/F/nK1RrFYxTmhrOm2dU5ulDDr4DW++g8y/jfJYHZkb0HkEOKe/J347g8IPjQ/rlrY2MQhGO0HbrEc3y7r/btd1cN21WiIY6ROndhbq3xsOPLE6S9YzPS0cyWLFstDaJXFgT+a4vszLdGMU5aSjVxxmQsl/0txW6xAVT/vCwv1B+8qFAlXpug/fJRFbruGCcGDwKFN5bLxl4OSrTBzvqa22oSbfNYJYniXQpTcLM39bQOLh6l354vPkfJvCjDzDCrSKDqse36Oj6Li9+Xy4F7l8wt6KRPm8T5blDHA1zuR313Tu5W3pE2t/a1hbbeqzTkPuHjuD4u8cWvGFJlDZV/9bDh+SKEEnv94u408AanocPADtxXp9NfS2djbBa8U59MbdotnxttsKcWsedZwyIBNZD/K9audltpncZex6X2sJi8wxMZd+wVYSvt0tGsTU6WHZFrpSvGFqb2ptPjg+xlyW0aKLqZjbXL31dFSbBEY0xDvlgnYRkwUtf2ZWhVr1xX+m/a8rZmWtx2WtOzczKn1wk9JQfmFKc0Inhd2v3W4XzyykN3p5MXq9EU9Ge58348rHO7OsZNB+M/k1fTvXGUKhJUhmjQ++wnViVmXFT3FK9Nm5tmUiChzID32VlkWL3qGJ/PJ1Ac+Nj32dBX88IXiu9koM3z2szezdCk7Bhr6MxAHlpO38qdd6llVN6oTeQuVauZGFS1XYnSczT/EIcDY3Rid26yVtLKL8xuPEtozUJK8j2EMndxT9BG9MXtY01ijteCcbftzWETC5f9tWQO7nxKWHvWB9vn0ZPkLWLPx+ZJ67+0OYvrfA6PzV8vU/m0jvJaSf3Rcpswn+C+d3DbveoYp0/6X19Yydf+yINoOZ04677b1x1D8iAiGsEcxiv5OCY9zWJl21Et0zQf91CWfXD1Xhs8cWRdfIvitfzYZ5bTjr1Ej3XlBiNZdnlEc9a6u5As6vCr9GfprNXuNoXpIF8DndlvI9etx/SMKPueETzFNYguTTPJvOz9Tn1/8KBq3wVaURDVfV/lo+qeHc+lYGxqR1w9a8kMMOD++uNUNUHcf3ohKb6TB0YntIx32W17l9gUNnQTkmn/4DJfahv5CjAsB/ymH9Qd82XVNG/gTenjHrhJPE29UNxh9YRDWhu2+BLQ3r39Cq/bX224UuPBqAzsUEgQLxd6PKP30lvk2ad9swZQJ451PkU1w0kkpDwW+rlaqT+o3N570mOzoBqyNwNhm4kK/sraIP8t7suXhU3nuwixSMHEFU8oCOb/MTWd++p7VOjTfo1E5z7nCwMKAzQpuljxZIikGjIjUg9mfYpOYXfaiTwL+9qEsEQO+EMMu/2jxQ7XgzmNOU2VSSoKy7CQ06+ELuPHkipJQpMtqNzDGM/k+V/pvCKGrBWC7zMNLXmbtguBsQ/knPwMX49GiqnsAnABYNINn8IS5vb5dXhGY2nvWfETeJLvrV+OGQyvzH48r72RP/C8NgwK1bD3H2bt1l6DEnbpsYeyGI4OgoQ23qhl9PD/SH3W8vYgCkKF8kIT4o39vjJ17rj7+PN+xFDb48E9XbfLUdN20H0wZCwPtzuKJQlqzlQ0E05ZnQg94oSU1uYG8iaULdtxvl7Q2ABD4ogNgXKfu812xmwMdodZPaGcUZrCMENzXZxmaAd4PD6VqQD6BT/tN/v/embi2uHFzLtGc+MqQxSHuLeoQS4I4ab/J3B/T4fUkT+ybGp2gt4P7Lr8tN8d6HMiK9vD/UyNNFrhT8qr6gjvpz19TKtgL4biNTGRRCxtIf3EV06OT5bm/aZCFyPLgAkvy1SXxf+Pd7325EO8BAtr/9Art8Wr5H7zgY0spd3uJ9bfIEQ+rC79r+HCAx4cFeCYPfWsMQiT/0qU57v1t4uQ7LzgM7mMnzRi4Y0i2V5zNGg9a+07R2bFZyjIM9tXP3YmjOxC9Kr8BW/zBTXd+TWdUlhw4C1lDBkuch0qJOuO8rF/XbMw5VsCn44uzU1GQv/p10Eu+Vlu6OOTzAgs95kqqMtysZkSr22DYzlUYPJ+I578xlMVSJWu12ZMJHq0Fum1Y7zVXCs0vZ3coCHomncVweNFj3gizAOBgHApNVFH2hJxi8k30NSSvtvqAZxDRwyyVXzCjr0BZDroS+CyFvADMVW/Sx7z2mtLnxE8yXP2eLIdCdnP9n6LjVVKVMRskIik2ifLR9D4Bc00cAkFz9H8rYYEJiCQuN3vxynel13oGSTlU27Qq6Jdg9sI1XfbzaLFhbzxtzDX7i0vGsUaDZ7p5kJzmLJGf85jPcZFQE+BLfhJD52/fuzN2r13sPR5MmRenltsOXnU8cQydIh6mWRqmgzpDex9rhQ7FoWCJo/wVhblE4M4PzegG2s2N0Z+UKpYcwjGDqvCQGTxUb/CR0P9+k8fCqbZCvTa0CquUSmd6aleHI3ebn8rterwLC6BxYs+r395eGcd58JEVodb6a2tIA+BsHtCzSmHIjfP8lO2fCmA0LGYsWa6iz2DB8+Kty/+rTE51l4jop3r6uv12jrs1n7PLsAB9PmeXyfQwII+GHke9AGddqb5Qlcl4hS+yao9P7ZqBaLyXRu8hyIafvOIS5TPG84aLYA+zoW9UgzyrLC3Vff+hHIR/zmdK/V3oNlbAOQG7rjEEMlWtz76CSWFXPEcvsRmyedGnyFHRbr1NLgX+xKTwjqjzXy1nGXCFT+QAKM4WvRSARJRrjBfpDzCVvhYvmmyp8sIhz2ByP+kElMUesxLyAkUwFbQEIIL0/71iUkVXBcrSTnSxVG3TmI4vOieUEMlDMBO5VV6D392YG6zD7e2GFruF+/eN7oJqCQVfklOWTOnlfYcvIZEZW99bBUYwYnyKsufdjeLfL4/c5UqFBssej3teDqydNjoeTMTMTL/yGPvDGSdcoA6bzrshqlXNO/Lm1o2qXJeoR+J/TI5z2HboQLxRnuSJPcJQ0mIlKk5jNr083skJ224gJdUU+ZwLV2yw5mseMkZaNtmrDslQrNrrg8fNSi2ZqQ3L/1Beurur1xKLr6mShI9+8xbHR+XIWsRMwnKVaznDnPjAnVPBTgwH6taHTrabydymNB9MVTRBnVYLcM8qFAdcdeMK3Ka0WX67ok31ZWfujsRGJNgaKraWn9kjpA3M1xc6FQMTBI0AV46o5y8F/T3y2FWFgHaLFV9k1zAtQnVsMQap9iEB34NMlfTJMfo9bVWUpQ/kpfei+v4Pc0cler7GEJfTEjzFmPV0rxkeDK4wRFq7V/7NDrLa+yDx62QetLkYkdlS3e7AD6BcSyNflczkc7vOecXXhqBo19xTVC90x/VpmYXqL/4nK1LwU4jpuPOS9APLNBu/xkySs6twQ06vZMR6/+3tUpAhGpIZpRaAwK4G7pzlWTrsi4+raGfBt/Ksr5rDCtX/Gj20ZsKQA029eGizG7KXH5csCOPqSR2U1zmpyTZOtPTiikemNYLYnjuW0hIkjzLJsE5NxtUtdmUkawREvM/W4r22ob2TIrcRNPPbz56Q14v7lRdtAIx1j+sTRzWE5atQx+rk48/QZVGamvw/Y9UGZRA2NpR/YhxN+Drf7PJBnpLggkOiGY5608iR6sIXyIQhsas9BWUlHdLvnCQfwlT4SlYr4KAtbMLAotIhqJgu7Sqd/q2Heu1fKqg8lCg8PCRPqiKYJjR2yIcSBZlhvdXnlPOvAUT7MPGT9VBcycntR38nVghYqwfhntfbJGqk4/po79sAmrI2VPI2ddhf74eL4uhpwKqZU1UrDRX/foqkshkcMLPThpJ6DF6jcprpNUr2hxj/S+Y7q+btDmvf4JeLRjVeHTkGtRG9RP/tm0ZuT6u8fKEPUyt838TLD5eoEoEpPd1CMBgMJ3Vn7u2tfoxbdXRu1kmBvIKEHGYD/kGNP4yNWOuZPPKak8WA3hnmyXEMZqx5zZl3c4uJgGmQRUy4k07LHZa7BNTbL4OVY8OQt5VrkLnoI/tPMCOp/ipS6c56sVVOThLDbUGfj92GZA5sbtzMPvq+RNtjKxVXe4/N6V/EkdKUTHP7cpPVWYa44y6MulJu6pSio1mWjF7TmsGmqKjpnLu3WbSyjBlG5vbDV8pZmsPXrfcKQhZPMiOn6UJDPnTFbaoSsDprPxir0/ciFMKm2/Ux5
*/