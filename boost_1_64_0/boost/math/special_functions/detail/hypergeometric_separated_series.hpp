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
F8RrQOH8oR9Ycdbn8vKKO0Xx3mNRx29QPcAPwzFisky/AFpKd5Fm6fwKvmE+Tbg1gmJcfyfLQfcutdZKqytBoMeh/0Visj4IszOJatykrM8/Mwx2F0S6Ym9RStg3l7ymxOHdkXqbXB5ohWmosbx4hl8BVaDA8vsVgT/ze8LbFH4bLjIGjSfupYHvmGF2Xw78rjyyI+t4/Sxv9f4pKzb0ttfkdoAbk9bM8w/3BnoeyuigLJQyHr3pmU+W2weMdrk/5tfIeJWiMqNIOwW63Xf6+YCWlYYed/01IRe6IGUHZbC/jmn9pZ8neojSHigWmDbfWQCjDN8jgNhjibfu4edEsc227b5omTIwAkxWbDg8g+NRfN+5pjJeZHGyvnkEfBeo7KoOjAnO8rHfZTLOgzwJcLr82+P0aYBRZDJcbjlZ3K/RfurZi5cCjS7sxz5/lSVj+vmB12Z0fnuA6bIcr9fLAVG4Re0y7D0Cx+2bivvEivl+O+o/cekjiDLfBo31fxukYzzUIL+fBT79AuUM/269nK3lMMvnA5ZM6TL/sYyuJ2mcYfrENVH/ccQ93QlUk40gxDzL77NqeiIto72/ZLY3F0e239fmyZB5rsqUjyN47hq+42NDUEa870SUXUbFZmU4b41hTlw5+12uGWe34YOUwe8Bv13ADHsAaLWLYl+/CwZyX8nK/UKgGw/gyO+/0+vjL4cZ/o+anHV3xigff1LlI6uu7M8rXqtYh6lnOF+OelUIXT7HXwv4rAc9MK8fg8ypyiPXKzekvIhknRNYBEzBvGzd03UrwCmX4RryJa53g3JaMteOgqq4EhnP6F7LkD3jDNmdgY7zGZRZGDPyZhxxLU921gr7AMbkSpq06GziXQvrYNf1AOO0+ZZFHO8+kjIhDg9l9bzqtVSZyNr8F9S/ZPBkfXFN1BswouULTFj3e1/LHueqTN8D+fwoO0d4P8Bb86hxDqlk92+L62L2EQgTfvv3NaA+rRZeZ5v122UgLathUL7+bY5ltElD7i8ZEA+pib6SZYuuZc8hXPpCnbiyHGb1un9R3bm5ZF+uAqZAj3Me2O4PyHA8vxh3Av4M2oIFMvv2BigX+CuwfbIyrXN+Spfr9/b97Zr52d7VoAlVSpG3W9BP5nnmLcBYet7o70GGUYeANW+NuE/EMRYeQNjmlwK61pd4BnJaWD99LnpkURkZkp25zjA8XIx5wdHzP7IcZv35+GvNmVeMNniK3QaWPfUMu72tc2rPttKx5dMHjKGo5fdlOd+qozyTm5/Ad3psBvN5EfeHvJ+RTy6IXsna7GWWXtTt7HtCunAyBvJqXRTGDt318Apwpl42mylkDJ6UAaQ99VJAk7fW8Zpe1h3phy6DdOkHzkD4vqlza8T8hDA7QxvF92IcvazAHe8PM38yle/o5eB7to4Gl40sApXPv7xKG0CUi6RT+e54BaSbm55Kvj+5EmNmkwHl+4mr43feIyLaqWtoNDAMuU0efU2k2ZtC1Cbd687FiD0GyufX1yNcNwvk4L45e32msTOK+9W/qUqX5Sfe2SLTdrazQFK1XxduodFl4doiYF+Rja/fEjEYJoBp0J00P7kt0jmMgMr2xDuotP50S+Gr3RFpHJ5AeS7diWjQlTJLLd3unRV6RiLag+6m0cZApPqeubdO4+pyfbv3Y4zSXyRHTy0RXex60d09//LpuxKO4XDeVZ3OniLGfL3JGM0ZppRvaYUxMMykGxXqSDL3plWdPp0O2hsD2HrPikTpfOKBhBNREm254+twO97oIUSfmHIVtZmmeHKJ/oKuTe8NNyjt05tMR2c10Ra3iXYSFRWle2AkaFIc+nITvr3dmW1sUftd7+FEn0I=
*/