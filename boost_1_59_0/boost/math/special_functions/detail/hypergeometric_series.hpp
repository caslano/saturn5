///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_DETAIL_HYPERGEOMETRIC_SERIES_HPP
#define BOOST_MATH_DETAIL_HYPERGEOMETRIC_SERIES_HPP

#include <cmath>
#include <cstdint>
#include <boost/math/tools/series.hpp>
#include <boost/math/special_functions/trunc.hpp>
#include <boost/math/policies/error_handling.hpp>

  namespace boost { namespace math { namespace detail {

  // primary template for term of Taylor series
  template <class T, unsigned p, unsigned q>
  struct hypergeometric_pFq_generic_series_term;

  // partial specialization for 0F1
  template <class T>
  struct hypergeometric_pFq_generic_series_term<T, 0u, 1u>
  {
    typedef T result_type;

    hypergeometric_pFq_generic_series_term(const T& b, const T& z)
       : n(0), term(1), b(b), z(z)
    {
    }

    T operator()()
    {
      BOOST_MATH_STD_USING
      const T r = term;
      term *= ((1 / ((b + n) * (n + 1))) * z);
      ++n;
      return r;
    }

  private:
    unsigned n;
    T term;
    const T b, z;
  };

  // partial specialization for 1F0
  template <class T>
  struct hypergeometric_pFq_generic_series_term<T, 1u, 0u>
  {
    typedef T result_type;

    hypergeometric_pFq_generic_series_term(const T& a, const T& z)
       : n(0), term(1), a(a), z(z)
    {
    }

    T operator()()
    {
      BOOST_MATH_STD_USING
      const T r = term;
      term *= (((a + n) / (n + 1)) * z);
      ++n;
      return r;
    }

  private:
    unsigned n;
    T term;
    const T a, z;
  };

  // partial specialization for 1F1
  template <class T>
  struct hypergeometric_pFq_generic_series_term<T, 1u, 1u>
  {
    typedef T result_type;

    hypergeometric_pFq_generic_series_term(const T& a, const T& b, const T& z)
       : n(0), term(1), a(a), b(b), z(z)
    {
    }

    T operator()()
    {
      BOOST_MATH_STD_USING
      const T r = term;
      term *= (((a + n) / ((b + n) * (n + 1))) * z);
      ++n;
      return r;
    }

  private:
    unsigned n;
    T term;
    const T a, b, z;
  };

  // partial specialization for 1F2
  template <class T>
  struct hypergeometric_pFq_generic_series_term<T, 1u, 2u>
  {
    typedef T result_type;

    hypergeometric_pFq_generic_series_term(const T& a, const T& b1, const T& b2, const T& z)
       : n(0), term(1), a(a), b1(b1), b2(b2), z(z)
    {
    }

    T operator()()
    {
      BOOST_MATH_STD_USING
      const T r = term;
      term *= (((a + n) / ((b1 + n) * (b2 + n) * (n + 1))) * z);
      ++n;
      return r;
    }

  private:
    unsigned n;
    T term;
    const T a, b1, b2, z;
  };

  // partial specialization for 2F0
  template <class T>
  struct hypergeometric_pFq_generic_series_term<T, 2u, 0u>
  {
    typedef T result_type;

    hypergeometric_pFq_generic_series_term(const T& a1, const T& a2, const T& z)
       : n(0), term(1), a1(a1), a2(a2), z(z)
    {
    }

    T operator()()
    {
      BOOST_MATH_STD_USING
      const T r = term;
      term *= (((a1 + n) * (a2 + n) / (n + 1)) * z);
      ++n;
      return r;
    }

  private:
    unsigned n;
    T term;
    const T a1, a2, z;
  };

  // partial specialization for 2F1
  template <class T>
  struct hypergeometric_pFq_generic_series_term<T, 2u, 1u>
  {
    typedef T result_type;

    hypergeometric_pFq_generic_series_term(const T& a1, const T& a2, const T& b, const T& z)
       : n(0), term(1), a1(a1), a2(a2), b(b), z(z)
    {
    }

    T operator()()
    {
      BOOST_MATH_STD_USING
      const T r = term;
      term *= (((a1 + n) * (a2 + n) / ((b + n) * (n + 1))) * z);
      ++n;
      return r;
    }

  private:
    unsigned n;
    T term;
    const T a1, a2, b, z;
  };

  // we don't need to define extra check and make a polinom from
  // series, when p(i) and q(i) are negative integers and p(i) >= q(i)
  // as described in functions.wolfram.alpha, because we always
  // stop summation when result (in this case numerator) is zero.
  template <class T, unsigned p, unsigned q, class Policy>
  inline T sum_pFq_series(detail::hypergeometric_pFq_generic_series_term<T, p, q>& term, const Policy& pol)
  {
    BOOST_MATH_STD_USING
    std::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();

    const T result = boost::math::tools::sum_series(term, boost::math::policies::get_epsilon<T, Policy>(), max_iter);

    policies::check_series_iterations<T>("boost::math::hypergeometric_pFq_generic_series<%1%>(%1%,%1%,%1%)", max_iter, pol);
    return result;
  }

  template <class T, class Policy>
  inline T hypergeometric_0F1_generic_series(const T& b, const T& z, const Policy& pol)
  {
    detail::hypergeometric_pFq_generic_series_term<T, 0u, 1u> s(b, z);
    return detail::sum_pFq_series(s, pol);
  }

  template <class T, class Policy>
  inline T hypergeometric_1F0_generic_series(const T& a, const T& z, const Policy& pol)
  {
    detail::hypergeometric_pFq_generic_series_term<T, 1u, 0u> s(a, z);
    return detail::sum_pFq_series(s, pol);
  }

  template <class T, class Policy>
  inline T log_pochhammer(T z, unsigned n, const Policy pol, int* s = 0)
  {
     BOOST_MATH_STD_USING
#if 0
     if (z < 0)
     {
        if (n < -z)
        {
           if(s)
            *s = (n & 1 ? -1 : 1);
           return log_pochhammer(T(-z + (1 - (int)n)), n, pol);
        }
        else
        {
           int cross = itrunc(ceil(-z));
           return log_pochhammer(T(-z + (1 - cross)), cross, pol, s) + log_pochhammer(T(cross + z), n - cross, pol);
        }
     }
     else
#endif
     {
        if (z + n < 0)
        {
           T r = log_pochhammer(T(-z - n + 1), n, pol, s);
           if (s)
              *s *= (n & 1 ? -1 : 1);
           return r;
        }
        int s1, s2;
        T r = boost::math::lgamma(T(z + n), &s1, pol) - boost::math::lgamma(z, &s2, pol);
        if(s)
           *s = s1 * s2;
        return r;
     }
  }

  template <class T, class Policy>
  inline T hypergeometric_1F1_generic_series(const T& a, const T& b, const T& z, const Policy& pol, long long& log_scaling, const char* function)
  {
     BOOST_MATH_STD_USING
     T sum(0), term(1), upper_limit(sqrt(boost::math::tools::max_value<T>())), diff;
     T lower_limit(1 / upper_limit);
     unsigned n = 0;
     long long log_scaling_factor = lltrunc(boost::math::tools::log_max_value<T>()) - 2;
     T scaling_factor = exp(T(log_scaling_factor));
     T term_m1 = 0;
     long long local_scaling = 0;
     //
     // When a is very small, then (a+n)/n => 1 faster than
     // z / (b+n) => 1, as a result the series starts off
     // converging, then at some unspecified time very gradually
     // starts to diverge, potentially resulting in some very large
     // values being missed.  As a result we need a check for small
     // a in the convergence criteria.  Note that this issue occurs
     // even when all the terms are positive.
     //
     bool small_a = fabs(a) < 0.25;

     unsigned summit_location = 0;
     bool have_minima = false;
     T sq = 4 * a * z + b * b - 2 * b * z + z * z;
     if (sq >= 0)
     {
        T t = (-sqrt(sq) - b + z) / 2;
        if (t > 1)  // Don't worry about a minima between 0 and 1.
           have_minima = true;
        t = (sqrt(sq) - b + z) / 2;
        if (t > 0)
           summit_location = itrunc(t);
     }

     if (summit_location > boost::math::policies::get_max_series_iterations<Policy>() / 4)
     {
        //
        // Skip forward to the location of the largest term in the series and
        // evaluate outwards from there:
        //
        int s1, s2;
        term = log_pochhammer(a, summit_location, pol, &s1) + summit_location * log(z) - log_pochhammer(b, summit_location, pol, &s2) - lgamma(T(summit_location + 1), pol);
        //std::cout << term << " " << log_pochhammer(boost::multiprecision::mpfr_float(a), summit_location, pol, &s1) + summit_location * log(boost::multiprecision::mpfr_float(z)) - log_pochhammer(boost::multiprecision::mpfr_float(b), summit_location, pol, &s2) - lgamma(boost::multiprecision::mpfr_float(summit_location + 1), pol) << std::endl;
        local_scaling = lltrunc(term);
        log_scaling += local_scaling;
        term = s1 * s2 * exp(term - local_scaling);
        //std::cout << term << " " << exp(log_pochhammer(boost::multiprecision::mpfr_float(a), summit_location, pol, &s1) + summit_location * log(boost::multiprecision::mpfr_float(z)) - log_pochhammer(boost::multiprecision::mpfr_float(b), summit_location, pol, &s2) - lgamma(boost::multiprecision::mpfr_float(summit_location + 1), pol) - local_scaling) << std::endl;
        n = summit_location;
     }
     else
        summit_location = 0;

     T saved_term = term;
     long long saved_scale = local_scaling;

     do
     {
        sum += term;
        //std::cout << n << " " << term * exp(boost::multiprecision::mpfr_float(local_scaling)) << " " << rising_factorial(boost::multiprecision::mpfr_float(a), n) * pow(boost::multiprecision::mpfr_float(z), n) / (rising_factorial(boost::multiprecision::mpfr_float(b), n) * factorial<boost::multiprecision::mpfr_float>(n)) << std::endl;
        if (fabs(sum) >= upper_limit)
        {
           sum /= scaling_factor;
           term /= scaling_factor;
           log_scaling += log_scaling_factor;
           local_scaling += log_scaling_factor;
        }
        if (fabs(sum) < lower_limit)
        {
           sum *= scaling_factor;
           term *= scaling_factor;
           log_scaling -= log_scaling_factor;
           local_scaling -= log_scaling_factor;
        }
        term_m1 = term;
        term *= (((a + n) / ((b + n) * (n + 1))) * z);
        if (n - summit_location > boost::math::policies::get_max_series_iterations<Policy>())
           return boost::math::policies::raise_evaluation_error(function, "Series did not converge, best value is %1%", sum, pol);
        ++n;
        diff = fabs(term / sum);
     } while ((diff > boost::math::policies::get_epsilon<T, Policy>()) || (fabs(term_m1) < fabs(term)) || (small_a && n < 10));

     //
     // See if we need to go backwards as well:
     //
     if (summit_location)
     {
        //
        // Backup state:
        //
        term = saved_term * exp(T(local_scaling - saved_scale));
        n = summit_location;
        term *= (b + (n - 1)) * n / ((a + (n - 1)) * z);
        --n;
        
        do
        {
           sum += term;
           //std::cout << n << " " << term * exp(boost::multiprecision::mpfr_float(local_scaling)) << " " << rising_factorial(boost::multiprecision::mpfr_float(a), n) * pow(boost::multiprecision::mpfr_float(z), n) / (rising_factorial(boost::multiprecision::mpfr_float(b), n) * factorial<boost::multiprecision::mpfr_float>(n)) << std::endl;
           if (n == 0)
              break;
           if (fabs(sum) >= upper_limit)
           {
              sum /= scaling_factor;
              term /= scaling_factor;
              log_scaling += log_scaling_factor;
              local_scaling += log_scaling_factor;
           }
           if (fabs(sum) < lower_limit)
           {
              sum *= scaling_factor;
              term *= scaling_factor;
              log_scaling -= log_scaling_factor;
              local_scaling -= log_scaling_factor;
           }
           term_m1 = term;
           term *= (b + (n - 1)) * n / ((a + (n - 1)) * z);
           if (summit_location - n > boost::math::policies::get_max_series_iterations<Policy>())
              return boost::math::policies::raise_evaluation_error(function, "Series did not converge, best value is %1%", sum, pol);
           --n;
           diff = fabs(term / sum);
        } while ((diff > boost::math::policies::get_epsilon<T, Policy>()) || (fabs(term_m1) < fabs(term)));
     }

     if (have_minima && n && summit_location)
     {
        //
        // There are a few terms starting at n == 0 which
        // haven't been accounted for yet...
        //
        unsigned backstop = n;
        n = 0;
        term = exp(T(-local_scaling));
        do
        {
           sum += term;
           //std::cout << n << " " << term << " " << sum << std::endl;
           if (fabs(sum) >= upper_limit)
           {
              sum /= scaling_factor;
              term /= scaling_factor;
              log_scaling += log_scaling_factor;
           }
           if (fabs(sum) < lower_limit)
           {
              sum *= scaling_factor;
              term *= scaling_factor;
              log_scaling -= log_scaling_factor;
           }
           //term_m1 = term;
           term *= (((a + n) / ((b + n) * (n + 1))) * z);
           if (n > boost::math::policies::get_max_series_iterations<Policy>())
              return boost::math::policies::raise_evaluation_error(function, "Series did not converge, best value is %1%", sum, pol);
           if (++n == backstop)
              break; // we've caught up with ourselves.
           diff = fabs(term / sum);
        } while ((diff > boost::math::policies::get_epsilon<T, Policy>())/* || (fabs(term_m1) < fabs(term))*/);
     }
     //std::cout << sum << std::endl;
     return sum;
  }

  template <class T, class Policy>
  inline T hypergeometric_1F2_generic_series(const T& a, const T& b1, const T& b2, const T& z, const Policy& pol)
  {
    detail::hypergeometric_pFq_generic_series_term<T, 1u, 2u> s(a, b1, b2, z);
    return detail::sum_pFq_series(s, pol);
  }

  template <class T, class Policy>
  inline T hypergeometric_2F0_generic_series(const T& a1, const T& a2, const T& z, const Policy& pol)
  {
    detail::hypergeometric_pFq_generic_series_term<T, 2u, 0u> s(a1, a2, z);
    return detail::sum_pFq_series(s, pol);
  }

  template <class T, class Policy>
  inline T hypergeometric_2F1_generic_series(const T& a1, const T& a2, const T& b, const T& z, const Policy& pol)
  {
    detail::hypergeometric_pFq_generic_series_term<T, 2u, 1u> s(a1, a2, b, z);
    return detail::sum_pFq_series(s, pol);
  }

  } } } // namespaces

#endif // BOOST_MATH_DETAIL_HYPERGEOMETRIC_SERIES_HPP

/* hypergeometric_series.hpp
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
*/