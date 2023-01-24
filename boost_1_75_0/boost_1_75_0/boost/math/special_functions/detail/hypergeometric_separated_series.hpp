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
XNgcj55ZvIMkoPjuyYesn5xiNHJGUP+0I4bCpirFKLOQVcpUWDEApGKr/lIYPhaA5xLJeNud/JM6DnqJ7yFHVn2Tt4D/zP4piArvUAKlK8HhGcu/gNArkhPKlSOx+Kdecp/IEmR/WCriemYTi5bw0vDbS/0iCRNeu13gy/p+o5He489IaOy+SdOzaGD91hESNLP0G9QnE6JUvBnyMnCbwKlKMYZ/prAuPSDfkBWJLgvqsbvtFfDxPvmMzH5eayNu4ZRGIt4+PTxPGYWAD586DU/g04G0DCg1GLWM7cCVcyTlzmJfS59nH/QN7Jv99ZbkHEwQTexvJu37vvMQQZT1YINo4LrseoggmjPaFUorukiwSA1PoM9jSGdwft9mH+cO7VdBlzo5HZwHlmWd4nwu/V6UuLQWGmnfP3wofNhdsH2ofmNzf64DBYLrhWtptAAjLf0WHDTL0h2UgATa/JyZ0HEfP1GiOQ2mCHHTs3HZbWzgi9ToLBCvjLybNO9kpYixdyct7yhjjriw1V32j+JC5Vz9swqvEXz7P2ULNO8axGdZnUTPBheoxVea24nGz46ypOC8NyWAvS45dbXASNYU+8O9kWFzRn6ylIc/IFaAvzTH/I9+vhRXtrN6LUpx/Aii9+Km6TRCl17nm0BKmZjICzocRvZSkaODhDMrw6bHcE8my7XwJK/PKqP5ZmoqcTZuY1KeZmhGNOi6HSL6
*/