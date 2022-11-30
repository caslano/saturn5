
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
           long long scale1(0), scale2(0);
           M = boost::math::detail::hypergeometric_1F1_imp(a, b, z, pol, scale1);
           M_next = boost::math::detail::hypergeometric_1F1_imp(T(a - 1), b, z, pol, scale2);
           if (scale1 != scale2)
              M_next *= exp(T(scale2 - scale1));
           if (M > 1e10f)
           {
              // rescale:
              long long rescale = lltrunc(log(fabs(M)));
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
        long long scale()const { return scaling; }
     private:
        T term, b_minus_a_plus_n, M, M_next, a_, b_, z_;
        int n, k;
        long long scaling;
     };

     template <class T, class Policy>
     T hypergeometric_1f1_recurrence_on_z_minus_zero(const T& a, const T& b, const T& z, int k, const Policy& pol, long long& log_scaling)
     {
        BOOST_MATH_STD_USING
           BOOST_MATH_ASSERT((z + k) / z > 0.5f);
        hypergeometric_1f1_recurrence_on_z_minus_zero_series<T, Policy> s(a, b, z, k, pol);
        std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
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
        std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
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
           BOOST_MATH_ASSERT(abs(k) < fabs(z));
        hypergeometric_1f1_recurrence_on_z_zero_minus_series<T, Policy> s(a, b, z, k, pol);
        std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
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
           BOOST_MATH_ASSERT(k / z > -0.5f);
        //BOOST_MATH_ASSERT(floor(a) != a || a > 0);
        hypergeometric_1f1_recurrence_on_z_plus_zero_series<T, Policy> s(a, b, z, k, pol);
        std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
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
        std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
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
        std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
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