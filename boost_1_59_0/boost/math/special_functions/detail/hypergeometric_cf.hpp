
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_DETAIL_HYPERGEOMETRIC_CF_HPP
#define BOOST_MATH_DETAIL_HYPERGEOMETRIC_CF_HPP

  namespace boost { namespace math { namespace detail {

  // primary template for term of continued fraction
  template <class T, unsigned p, unsigned q>
  struct hypergeometric_pFq_cf_term;

  // partial specialization for 0F1
  template <class T>
  struct hypergeometric_pFq_cf_term<T, 0u, 1u>
  {
    typedef std::pair<T,T> result_type;

    hypergeometric_pFq_cf_term(const T& b, const T& z):
      n(1), b(b), z(z),
      term(std::make_pair(T(0), T(1)))
    {
    }

    result_type operator()()
    {
      const result_type result = term;
      ++b; ++n;
      numer = -(z / (b * n));
      term = std::make_pair(numer, 1 - numer);
      return result;
    }

  private:
    unsigned n;
    T b;
    const T z;
    T numer;
    result_type term;
  };

  // partial specialization for 1F0
  template <class T>
  struct hypergeometric_pFq_cf_term<T, 1u, 0u>
  {
    typedef std::pair<T,T> result_type;

    hypergeometric_pFq_cf_term(const T& a, const T& z):
      n(1), a(a), z(z),
      term(std::make_pair(T(0), T(1)))
    {
    }

    result_type operator()()
    {
      const result_type result = term;
      ++a; ++n;
      numer = -((a * z) / n);
      term = std::make_pair(numer, 1 - numer);
      return result;
    }

  private:
    unsigned n;
    T a;
    const T z;
    T numer;
    result_type term;
  };

  // partial specialization for 1F1
  template <class T>
  struct hypergeometric_pFq_cf_term<T, 1u, 1u>
  {
    typedef std::pair<T,T> result_type;

    hypergeometric_pFq_cf_term(const T& a, const T& b, const T& z):
      n(1), a(a), b(b), z(z),
      term(std::make_pair(T(0), T(1)))
    {
    }

    result_type operator()()
    {
      const result_type result = term;
      ++a; ++b; ++n;
      numer = -((a * z) / (b * n));
      term = std::make_pair(numer, 1 - numer);
      return result;
    }

  private:
    unsigned n;
    T a, b;
    const T z;
    T numer;
    result_type term;
  };

  // partial specialization for 1f2
  template <class T>
  struct hypergeometric_pFq_cf_term<T, 1u, 2u>
  {
    typedef std::pair<T,T> result_type;

    hypergeometric_pFq_cf_term(const T& a, const T& b, const T& c, const T& z):
      n(1), a(a), b(b), c(c), z(z),
      term(std::make_pair(T(0), T(1)))
    {
    }

    result_type operator()()
    {
      const result_type result = term;
      ++a; ++b; ++c; ++n;
      numer = -((a * z) / ((b * c) * n));
      term = std::make_pair(numer, 1 - numer);
      return result;
    }

  private:
    unsigned n;
    T a, b, c;
    const T z;
    T numer;
    result_type term;
  };

  // partial specialization for 2f1
  template <class T>
  struct hypergeometric_pFq_cf_term<T, 2u, 1u>
  {
    typedef std::pair<T,T> result_type;

    hypergeometric_pFq_cf_term(const T& a, const T& b, const T& c, const T& z):
      n(1), a(a), b(b), c(c), z(z),
      term(std::make_pair(T(0), T(1)))
    {
    }

    result_type operator()()
    {
      const result_type result = term;
      ++a; ++b; ++c; ++n;
      numer = -(((a * b) * z) / (c * n));
      term = std::make_pair(numer, 1 - numer);
      return result;
    }

  private:
    unsigned n;
    T a, b, c;
    const T z;
    T numer;
    result_type term;
  };

  template <class T, unsigned p, unsigned q, class Policy>
  inline T compute_cf_pFq(detail::hypergeometric_pFq_cf_term<T, p, q>& term, const Policy& pol)
  {
    BOOST_MATH_STD_USING
    std::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
    const T result = tools::continued_fraction_b(
      term,
      boost::math::policies::get_epsilon<T, Policy>(),
      max_iter);
    boost::math::policies::check_series_iterations<T>(
      "boost::math::hypergeometric_pFq_cf<%1%>(%1%,%1%,%1%)",
      max_iter,
      pol);
    return result;
  }

  template <class T, class Policy>
  inline T hypergeometric_0F1_cf(const T& b, const T& z, const Policy& pol)
  {
    detail::hypergeometric_pFq_cf_term<T, 0u, 1u> f(b, z);
    T result = detail::compute_cf_pFq(f, pol);
    result = ((z / b) / result) + 1;
    return result;
  }

  template <class T, class Policy>
  inline T hypergeometric_1F0_cf(const T& a, const T& z, const Policy& pol)
  {
    detail::hypergeometric_pFq_cf_term<T, 1u, 0u> f(a, z);
    T result = detail::compute_cf_pFq(f, pol);
    result = ((a * z) / result) + 1;
    return result;
  }

  template <class T, class Policy>
  inline T hypergeometric_1F1_cf(const T& a, const T& b, const T& z, const Policy& pol)
  {
    detail::hypergeometric_pFq_cf_term<T, 1u, 1u> f(a, b, z);
    T result = detail::compute_cf_pFq(f, pol);
    result = (((a * z) / b) / result) + 1;
    return result;
  }

  template <class T, class Policy>
  inline T hypergeometric_1F2_cf(const T& a, const T& b, const T& c, const T& z, const Policy& pol)
  {
    detail::hypergeometric_pFq_cf_term<T, 1u, 2u> f(a, b, c, z);
    T result = detail::compute_cf_pFq(f, pol);
    result = (((a * z) / (b * c)) / result) + 1;
    return result;
  }

  template <class T, class Policy>
  inline T hypergeometric_2F1_cf(const T& a, const T& b, const T& c, const T& z, const Policy& pol)
  {
    detail::hypergeometric_pFq_cf_term<T, 2u, 1u> f(a, b, c, z);
    T result = detail::compute_cf_pFq(f, pol);
    result = ((((a * b) * z) / c) / result) + 1;
    return result;
  }

  } } } // namespaces

#endif // BOOST_MATH_DETAIL_HYPERGEOMETRIC_CF_HPP

/* hypergeometric_cf.hpp
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
*/