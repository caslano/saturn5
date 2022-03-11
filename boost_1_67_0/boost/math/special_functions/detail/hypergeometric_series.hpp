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
    boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))
    const T zero = 0;
    const T result = boost::math::tools::sum_series(term, boost::math::policies::get_epsilon<T, Policy>(), max_iter, zero);
#else
    const T result = boost::math::tools::sum_series(term, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
#endif
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
  inline T hypergeometric_1F1_generic_series(const T& a, const T& b, const T& z, const Policy& pol, int& log_scaling, const char* function)
  {
     BOOST_MATH_STD_USING
     T sum(0), term(1), upper_limit(sqrt(boost::math::tools::max_value<T>())), diff;
     T lower_limit(1 / upper_limit);
     unsigned n = 0;
     int log_scaling_factor = itrunc(boost::math::tools::log_max_value<T>()) - 2;
     T scaling_factor = exp(T(log_scaling_factor));
     T term_m1 = 0;
     int local_scaling = 0;
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
        local_scaling = itrunc(term);
        log_scaling += local_scaling;
        term = s1 * s2 * exp(term - local_scaling);
        //std::cout << term << " " << exp(log_pochhammer(boost::multiprecision::mpfr_float(a), summit_location, pol, &s1) + summit_location * log(boost::multiprecision::mpfr_float(z)) - log_pochhammer(boost::multiprecision::mpfr_float(b), summit_location, pol, &s2) - lgamma(boost::multiprecision::mpfr_float(summit_location + 1), pol) - local_scaling) << std::endl;
        n = summit_location;
     }
     else
        summit_location = 0;

     T saved_term = term;
     int saved_scale = local_scaling;

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