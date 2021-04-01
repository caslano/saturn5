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
teFab9/XNXoCFcvcmnx3T3lRxqpxuItIUckZq+GOdSwG+g9xCM56Bq+kZlkVyzhQhE10D0w8tHbQZaBezELkoEkAEP2ScLavl6UReKn+y+7ju5ZGGt9FziRqFqO8fJcAKwvAl37FA4MMpMb4X4k1hxKfhM4XUInAXWxKWZjy5cQ1igLcIp/VXQdYeW6BoKr7YNNqnnNQ6gAkZxHrYuLtMbxJlHg3es6/hQLF+lDvEUmi6/xA/l4bL9nzTRYI4SMH4q3fMr4VUCIbnE/kGIzD6V+sRD7WvaYE42p3r+gTkid90Z0o2CstAN4gdi2/OUbISBQaqhk67q0xopGNjkVeLHox2nIzjIdXeC1k7vi2U0szc2zrvgJKoUDgZ3xl4XUZ/Nbu6XUc5sWfO/ZhAF3rZN4ktLibFTtQonN4Up1LuGkw0HttvxfTBMaOE6tN+rTP6XTkVjnzyEThJw2300BCs+oectyfpi7faQGXnS+myhQobpbS+/1+btZk+i1sSds3oTltBiKYMCtqSdnHCXeQpz+TWSjZ0oWfvr59hS4+Dz1ULgzJHhVGW4PVFw==
*/