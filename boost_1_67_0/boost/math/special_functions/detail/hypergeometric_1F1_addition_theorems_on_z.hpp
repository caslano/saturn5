
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_HYPERGEOMETRIC_1F1_ADDITION_THEOREMS_ON_Z_HPP
#define BOOST_MATH_HYPERGEOMETRIC_1F1_ADDITION_THEOREMS_ON_Z_HPP

#include <boost/math/tools/series.hpp>

//
// This file implements the addition theorems for 1F1 on z, specifically
// each function returns 1F1[a, b, z + k] for some integer k - there's
// no particular reason why k needs to be an integer, but no reason why
// it shouldn't be either.
//
// The functions are named hypergeometric_1f1_recurrence_on_z_[plus|minus|zero]_[plus|minus|zero]
// where a "plus" indicates forward recurrence, minus backwards recurrence, and zero no recurrence.
// So for example hypergeometric_1f1_recurrence_on_z_zero_plus uses forward recurrence on b and
// hypergeometric_1f1_recurrence_on_z_minus_minus uses backwards recurrence on both a and b.
//
// See https://dlmf.nist.gov/13.13
//

  namespace boost { namespace math { namespace detail {

     //
     // This works moderately well for a < 0, but has some very strange behaviour with
     // strings of values of the same sign followed by a sign switch then another
     // series all the same sign and so on.... doesn't converge smoothly either
     // but rises and falls in wave-like behaviour.... very slow to converge...
     //
     template <class T, class Policy>
     struct hypergeometric_1f1_recurrence_on_z_minus_zero_series
     {
        typedef T result_type;

        hypergeometric_1f1_recurrence_on_z_minus_zero_series(const T& a, const T& b, const T& z, int k_, const Policy& pol)
           : term(1), b_minus_a_plus_n(b - a), a_(a), b_(b), z_(z), n(0), k(k_)
        {
           BOOST_MATH_STD_USING
           int scale1(0), scale2(0);
           M = boost::math::detail::hypergeometric_1F1_imp(a, b, z, pol, scale1);
           M_next = boost::math::detail::hypergeometric_1F1_imp(T(a - 1), b, z, pol, scale2);
           if (scale1 != scale2)
              M_next *= exp(scale2 - scale1);
           if (M > 1e10f)
           {
              // rescale:
              int rescale = itrunc(log(fabs(M)));
              M *= exp(T(-rescale));
              M_next *= exp(T(-rescale));
              scale1 += rescale;
           }
           scaling = scale1;
        }
        T operator()()
        {
           T result = term * M;
           term *= b_minus_a_plus_n * k / ((z_ + k) * ++n);
           b_minus_a_plus_n += 1;
           T M2 = -((2 * (a_ - n) - b_ + z_) * M_next - (a_ - n) * M) / (b_ - (a_ - n));
           M = M_next;
           M_next = M2;

           return result;
        }
        int scale()const { return scaling; }
     private:
        T term, b_minus_a_plus_n, M, M_next, a_, b_, z_;
        int n, k, scaling;
     };

     template <class T, class Policy>
     T hypergeometric_1f1_recurrence_on_z_minus_zero(const T& a, const T& b, const T& z, int k, const Policy& pol, int& log_scaling)
     {
        BOOST_MATH_STD_USING
           BOOST_ASSERT((z + k) / z > 0.5f);
        hypergeometric_1f1_recurrence_on_z_minus_zero_series<T, Policy> s(a, b, z, k, pol);
        boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
        log_scaling += s.scale();
        boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1f1_recurrence_on_z_plus_plus<%1%>(%1%,%1%,%1%)", max_iter, pol);
        return result * exp(T(k)) * pow(z / (z + k), b - a);
     }

#if 0

     //
     // These are commented out as they are currently unused, but may find use in the future:
     //

     template <class T, class Policy>
     struct hypergeometric_1f1_recurrence_on_z_plus_plus_series
     {
        typedef T result_type;

        hypergeometric_1f1_recurrence_on_z_plus_plus_series(const T& a, const T& b, const T& z, int k_, const Policy& pol)
           : term(1), a_plus_n(a), b_plus_n(b), z_(z), n(0), k(k_)
        {
           M = boost::math::detail::hypergeometric_1F1_imp(a, b, z, pol);
           M_next = boost::math::detail::hypergeometric_1F1_imp(a + 1, b + 1, z, pol);
        }
        T operator()()
        {
           T result = term * M;
           term *= a_plus_n * k / (b_plus_n * ++n);
           a_plus_n += 1;
           b_plus_n += 1;
           // The a_plus_n == 0 case below isn't actually correct, but doesn't matter as that term will be zero
           // anyway, we just need to not divide by zero and end up with a NaN in the result.
           T M2 = (a_plus_n == -1) ? 1 : (a_plus_n == 0) ? 0 : (M_next * b_plus_n * (1 - b_plus_n + z_) + b_plus_n * (b_plus_n - 1) * M) / (a_plus_n * z_);
           M = M_next;
           M_next = M2;
           return result;
        }
        T term, a_plus_n, b_plus_n, M, M_next, z_;
        int n, k;
     };

     template <class T, class Policy>
     T hypergeometric_1f1_recurrence_on_z_plus_plus(const T& a, const T& b, const T& z, int k, const Policy& pol)
     {
        hypergeometric_1f1_recurrence_on_z_plus_plus_series<T, Policy> s(a, b, z, k, pol);
        boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
        boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1f1_recurrence_on_z_plus_plus<%1%>(%1%,%1%,%1%)", max_iter, pol);
        return result;
     }

     template <class T, class Policy>
     struct hypergeometric_1f1_recurrence_on_z_zero_minus_series
     {
        typedef T result_type;

        hypergeometric_1f1_recurrence_on_z_zero_minus_series(const T& a, const T& b, const T& z, int k_, const Policy& pol)
           : term(1), b_pochhammer(1 - b), x_k_power(-k_ / z), b_minus_n(b), a_(a), z_(z), b_(b), n(0), k(k_)
        {
           M = boost::math::detail::hypergeometric_1F1_imp(a, b, z, pol);
           M_next = boost::math::detail::hypergeometric_1F1_imp(a, b - 1, z, pol);
        }
        T operator()()
        {
           BOOST_MATH_STD_USING
           T result = term * M;
           term *= b_pochhammer * x_k_power / ++n;
           b_pochhammer += 1;
           b_minus_n -= 1;
           T M2 = (M_next * b_minus_n * (1 - b_minus_n - z_) + z_ * (b_minus_n - a_) * M) / (-b_minus_n * (b_minus_n - 1));
           M = M_next;
           M_next = M2;
           return result;
        }
        T term, b_pochhammer, x_k_power, M, M_next, b_minus_n, a_, z_, b_;
        int n, k;
     };

     template <class T, class Policy>
     T hypergeometric_1f1_recurrence_on_z_zero_minus(const T& a, const T& b, const T& z, int k, const Policy& pol)
     {
        BOOST_MATH_STD_USING
           BOOST_ASSERT(abs(k) < fabs(z));
        hypergeometric_1f1_recurrence_on_z_zero_minus_series<T, Policy> s(a, b, z, k, pol);
        boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
        boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1f1_recurrence_on_z_plus_plus<%1%>(%1%,%1%,%1%)", max_iter, pol);
        return result * pow((z + k) / z, 1 - b);
     }

     template <class T, class Policy>
     struct hypergeometric_1f1_recurrence_on_z_plus_zero_series
     {
        typedef T result_type;

        hypergeometric_1f1_recurrence_on_z_plus_zero_series(const T& a, const T& b, const T& z, int k_, const Policy& pol)
           : term(1), a_pochhammer(a), z_plus_k(z + k_), b_(b), a_(a), z_(z), n(0), k(k_)
        {
           M = boost::math::detail::hypergeometric_1F1_imp(a, b, z, pol);
           M_next = boost::math::detail::hypergeometric_1F1_imp(a + 1, b, z, pol);
        }
        T operator()()
        {
           T result = term * M;
           term *= a_pochhammer * k / (++n * z_plus_k);
           a_pochhammer += 1;
           T M2 = (a_pochhammer == -1) ? 1 : (a_pochhammer == 0) ? 0 : (M_next * (2 * a_pochhammer - b_ + z_) + (b_ - a_pochhammer) * M) / a_pochhammer;
           M = M_next;
           M_next = M2;

           return result;
        }
        T term, a_pochhammer, z_plus_k, M, M_next, b_minus_n, a_, b_, z_;
        int n, k;
     };

     template <class T, class Policy>
     T hypergeometric_1f1_recurrence_on_z_plus_zero(const T& a, const T& b, const T& z, int k, const Policy& pol)
     {
        BOOST_MATH_STD_USING
           BOOST_ASSERT(k / z > -0.5f);
        //BOOST_ASSERT(floor(a) != a || a > 0);
        hypergeometric_1f1_recurrence_on_z_plus_zero_series<T, Policy> s(a, b, z, k, pol);
        boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
        boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1f1_recurrence_on_z_plus_plus<%1%>(%1%,%1%,%1%)", max_iter, pol);
        return result * pow(z / (z + k), a);
     }

     template <class T, class Policy>
     struct hypergeometric_1f1_recurrence_on_z_zero_plus_series
     {
        typedef T result_type;

        hypergeometric_1f1_recurrence_on_z_zero_plus_series(const T& a, const T& b, const T& z, int k_, const Policy& pol)
           : term(1), b_minus_a_plus_n(b - a), b_plus_n(b), a_(a), z_(z), n(0), k(k_)
        {
           M = boost::math::detail::hypergeometric_1F1_imp(a, b, z, pol);
           M_next = boost::math::detail::hypergeometric_1F1_imp(a, b + 1, z, pol);
        }
        T operator()()
        {
           T result = term * M;
           term *= b_minus_a_plus_n * -k / (b_plus_n * ++n);
           b_minus_a_plus_n += 1;
           b_plus_n += 1;
           T M2 = (b_plus_n * (b_plus_n - 1) * M + b_plus_n * (1 - b_plus_n - z_) * M_next) / (-z_ * b_minus_a_plus_n);
           M = M_next;
           M_next = M2;

           return result;
        }
        T term, b_minus_a_plus_n, M, M_next, b_minus_n, a_, b_plus_n, z_;
        int n, k;
     };

     template <class T, class Policy>
     T hypergeometric_1f1_recurrence_on_z_zero_plus(const T& a, const T& b, const T& z, int k, const Policy& pol)
     {
        BOOST_MATH_STD_USING
           hypergeometric_1f1_recurrence_on_z_zero_plus_series<T, Policy> s(a, b, z, k, pol);
        boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
        boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1f1_recurrence_on_z_plus_plus<%1%>(%1%,%1%,%1%)", max_iter, pol);
        return result * exp(T(k));
     }
     //
     // I'm unable to find any situation where this series isn't divergent and therefore 
     // is probably quite useless:
     //
     template <class T, class Policy>
     struct hypergeometric_1f1_recurrence_on_z_minus_minus_series
     {
        typedef T result_type;

        hypergeometric_1f1_recurrence_on_z_minus_minus_series(const T& a, const T& b, const T& z, int k_, const Policy& pol)
           : term(1), one_minus_b_plus_n(1 - b), a_(a), b_(b), z_(z), n(0), k(k_)
        {
           M = boost::math::detail::hypergeometric_1F1_imp(a, b, z, pol);
           M_next = boost::math::detail::hypergeometric_1F1_imp(a - 1, b - 1, z, pol);
        }
        T operator()()
        {
           T result = term * M;
           term *= one_minus_b_plus_n * k / (z_ * ++n);
           one_minus_b_plus_n += 1;
           T M2 = -((b_ - n) * (1 - b_ + n + z_) * M_next - (a_ - n) * z_ * M) / ((b_ - n) * (b_ - n - 1));
           M = M_next;
           M_next = M2;

           return result;
        }
        T term, one_minus_b_plus_n, M, M_next, a_, b_, z_;
        int n, k;
     };

     template <class T, class Policy>
     T hypergeometric_1f1_recurrence_on_z_minus_minus(const T& a, const T& b, const T& z, int k, const Policy& pol)
     {
        BOOST_MATH_STD_USING
           hypergeometric_1f1_recurrence_on_z_minus_minus_series<T, Policy> s(a, b, z, k, pol);
        boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
        boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1f1_recurrence_on_z_plus_plus<%1%>(%1%,%1%,%1%)", max_iter, pol);
        return result * exp(T(k)) * pow((z + k) / z, 1 - b);
     }
#endif

  } } } // namespaces

#endif // BOOST_MATH_HYPERGEOMETRIC_1F1_ADDITION_THEOREMS_ON_Z_HPP

/* hypergeometric_1F1_addition_theorems_on_z.hpp
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
*/