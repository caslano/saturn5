///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_HYPERGEOMETRIC_SEPARATED_SERIES_HPP
#define BOOST_MATH_HYPERGEOMETRIC_SEPARATED_SERIES_HPP

  namespace boost { namespace math { namespace detail {

  template <class T, class Policy>
  inline T hypergeometric_1F1_separated_series(const T& a, const T& b, const T& z, const Policy& pol)
  {
    BOOST_MATH_STD_USING

    boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
    const T factor = policies::get_epsilon<T, Policy>();

    T denom = 1, numer = 1;
    T intermediate_result = 1, result = 1;
    T a_pochhammer = a, z_pow = z;
    unsigned N = 0;
    while (--max_iter)
    {
      ++N;
      const T mult = (((b + N) - 1) * N);
      denom *= mult; numer *= mult;
      numer += a_pochhammer * z_pow;

      result = numer / denom;

      if (fabs(factor * result) > fabs(result - intermediate_result))
        break;

      intermediate_result = result;

      a_pochhammer *= (a + N);
      z_pow *= z;
    }

    return result;
  }

  } } } // namespaces

#endif // BOOST_MATH_HYPERGEOMETRIC_SEPARATED_SERIES_HPP

/* hypergeometric_separated_series.hpp
YDT3lnDjlqYusiRfIYQnESj5ympvqwujNVd3fs9KlWLUhZpmI7nev1vqIlfSzLOlaUyypvnn1MNVXT1cl3WRb5Bqls8Oudb/KdtdQ3GBUg8drHlKtcS2V37y7PkK0GTH9bYXHqrd1rpIfzWe//LqqD7/FRLiIcOukZYMC2aQ7Tky+7AOUl7bt0Utyc7tJpFuMoDmu7WxKcmyHWvbzmpSL8p0ZuNU63S+mvsN2FLjLPHq8Esy
*/