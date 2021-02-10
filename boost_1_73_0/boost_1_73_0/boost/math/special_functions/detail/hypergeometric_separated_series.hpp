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
XEt5+f0uy9fp9WVond5tctlrX8mrOP4Yxp9qw+u8YFj8gW29HWgM7yC99WHoGMYxxoZQpR09M3d04SrjL4Q6TLWhQW+NN4VpEnGfrTakO9MNrdm7SKQ3WTZGeXzhN932Db8PU8PXx9tIjGEd4z6RWKXZQyTyp3RF60hk618rGneMpjSS+fXn/TqPwqrnUUqe5stzrMkfUEsDBAoAAAAIAC1nSlIPMzLN1gEAAP0CAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTAwNFVUBQABtkgkYGVSXW+jMBB8t8R/WKXKS1WfIeV6FwshVb1c07u2iRKu7w4sAZXYCDtp+fe3QD4eKiHYNbOzs7OOHFqXKosxi0qdG/q8Y/thmszGbJ4ky/4Fj7NkCOrGfLYsEhdQJIY6dsWuYI3NARtuywxZ1GBdtQTIlFMDmQi+BTDxfVj8Zb+UQwnJHm/An8KrOdCPwIcglOFUEuTxJWEDnYROJLd9InL1juxZ0cGLycq8xOzIEtzCn73u6IllIgP/xDJL1FbCaBL4k+88S3/w22l4NwmnP0fsPk2xdnyl9BathE1LndiD0Q6148+ot66QcNedaExdabSEtDIWz5ikrbHT9+lE4XYV+73XuuUFKlLVoqWHMZ4b
*/