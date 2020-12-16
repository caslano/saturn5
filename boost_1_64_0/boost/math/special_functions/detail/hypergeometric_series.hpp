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
cNkG/CWvtnGUei1NAKPuPYo+wj48SzQr5IX6/5lTgRn0QNRno+NDKtstd+C7fiIfHGXct1+w6fKAlVq2955UMLLJue4PeoRKA1UEyQ8GDusxnQ5ZM21rV6WNd6ZbTIsuVmhZkYh24JGC9ggQQahruzPdUM4gXnnNOHPqV5teUKu7HeWmcj7SSfExi2v6fjgE2cAprDrwgS3Rlkc5xDVa485sSzR8bzLsYAQ6p+EbacDpziSIwe9lv/4MPTgcDeE8l+kT3lrT/QZwmAn+rQZFafSnmMwGlYXPDaxpsaexiHcI654rZuV2bxt80/pZytMqvgnHFCHoGM7PSTxKdZ5Fm84f63mEXiNJIfIG5oJuf8LhrW6OP6vj0wA85Q3oGmCAuDPxVoJxvlPFxy5EUQVxxWvk+CHoqk0sVDv3AZ1fM+KcvCYcCfIS94SMVQbpHW0LP8WMyzfMef+1psfup3AGJ/T8yC14LQHzJd5rHTHOeSZJpVyHOAD79YS8HYe5zN5R4wU3e7MBTV+ruuarCtieuS/aPaL76UtVL62UGqK8J4tfPNbbd13lTyFUza/ENa/mwqExIV7TnjxEpp/LmKk8h4JyuSwMQ3c46W22h6Mp1o3jifb0PPxmVA6CBAJgRhDleLGWB43hFxwxzhHXIfjchzOs4+w+0/Z4o5+pBL0+bzqi+1W9pFHxm4k7Wc4MMMiTynf7PEbhiHYOIYKrDOHknmSBXPRYj88YfVypNNMgDT3XftmB8snrdN7s40bUKNW9CHmtPs7z/NMR3YddgkOxSQpn6AtfgtDbY+EirT3gnHOcNOo1yToVJ0roKBafN1+8yDiH5qVVcb2jMBK7cvIfgfrTzk6wX/si87x/5JfL4EyVO6nCRoYchb426hhdpI/ZRs2HgxJpRePT24f6ZOsivU/g1oy6HzXrOu/OYDQ8YZV3Ty+vvDSgCUfPkBfsrOLyvsDIE+LU0moz8phvfp5v0njhiDtUtFmHGEp4SUN//V+XvU8Y/dL046o4muIWvPRhxTZqvA04Y9ysl8Moznjn6wnSi0be9UoMqs0PmJ9fS89jRkkvHtXltxE1U7gGoiZ47VfUdV2zpPIeSkqNepDWMs6NyYBkdzWv5320vGqgD+H8RqVckhz268dW3xw9auidWgVO8GKOqu1gtM/4qN4+cA1HUoHz5xZfm84nubn+earKe48anHpvhGlW4n53bOhFxJK8JtWoWQ6l7OCuR0lcMYKiQ3djvFHlE2FYCYRVlrLuQ4O1M5jpdfqgllcFYoKaoThRL5hkXaxu43np20Y/pB4c7PYSKW+4Q2Bzwz+k88z2jCulaq1aJ37eUcuZXbL/jukxIBE0ERzaK0veaRZcw7Xlu0AWDb5KVCs30qxpV6NWuxLIF3yRjWNODhwz7+cANrCzTt4N9AAso/obwlaBcG+a5bisqZ4n2HqR1wjBwMHNJVBed2WriMvaPabLAUQ9VqCNFTZ1dmQ52D2myUECcaX1qJG4vJcleHU5eKZeP4jt9fyG7zcMJmjSfmeKckByp+cXNOI0gaPRKivWjmX8g0bdorLoaV8rJBt+3Cbnjhk62QtCCL9GNqGTi22NXxzTx7xf98CgKamMuFukt4vzAOPsOTCFFbD1mS/rhPbxEZodHHv4AD1P0Gsw7SRBzivDyORSW+c7oPGVIM9yHS7mSF11B5C7kPhqOh/oNThDDLa0zgczvMH3IJUvBbYwgUsaEvd4pwuRmeIsb7bPimxkd4wfoJ97gxOwIRimgs+4c4T7b+8BxlgIY3FViu8eH4qjABvL8HfR2fcXaHx1CIpLvXJcSiXfbARlnA7hlJpYsp3oTdQkeFy8U00jgWtrGrA=
*/