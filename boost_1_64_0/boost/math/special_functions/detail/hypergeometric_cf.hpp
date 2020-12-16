
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
    boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
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
E0YnDgX5+3XluC2LxsrSxjkEBE62wyesfuT0sGxSdgMcW2P4PRs6+LvsC+hCWa5bSZv3jCNsJzSHcX9QHjU/qtnCa+NBf/iwVXH3OmP+JVw/IDn97XG7Hez2Z+lktNGbTl0YH7lNvXUJBVPtzZqj7s6gV4O7LQe9iwCY4wY6TiaFbnb3kHrH/12ye1EyPQoem25/lF2FttkejWfZu8iY5nsvraTZRixI/jbc5npy+oiMS93/XpJpA22IxPbAUe57X8jWDm0iK2/dnLmjtvYA4X3EJtx9NVDuxgE08JttCl8rWN6XPFm0+eF2ktWjNRtN4LJY9/BdDx/er76ue0/3ng62kfh7Nr4M2MzAVHbbS3eL46Ds1cKme/iW5Urr8N0P39LzXOfdeT8r2Lv6gVtqVmCLrVlxBSwRP1LxIxA/YvGjRT8i8aMtfqyJH2PxYyB+9MWPofjxMPED8g3x7woBDy+pn+Qvy+LHUfxcl3/fTf48KH5mxb7Ey/K+VctdTtwwqnuVWlyS5d7BAmBRtvXi9ehbj3Az+rXLWW7qaW0gEFMdSQIXzfGejmW7oJUtdONm068G5bpLHCPOZIt+n8r0mdLBYltNu0HU+aW5O5Zl8eGKLJQ8N/H8OK3WK24uhd5YiiHW4ZZPRr4DD1frUHWbgRf6YbNp1eH/kRPPqpEtLFiOk1iOrlYOz01rYRrWYs8qx/+Y/iq13XEWCM74cL6Ov0TxOj5OVpoiKEquab8p16YYOgjr2Aq8f92CKSUC66oNplog52mYJIUVVg58OZ/DmvVbC7l+LVSvMI9c+erfBsz1Hicw29MTUn/znJvpc1zbNBN/LQrIlmmPNjfbM55H231hSqH9m80vMAFkv/9QzPHeCvgZMzsB6l1Ya7IBHKDLCYXXPJCeMArk3Pcj+H37+HQm36FAm/y789ZNd+M6tbu9k+0Z4HFOOi/mFaNtpE2FdP9Sgs5qOLM/biNp35Y6f9B55MWwfsFvd7wMfVuCX+n7Hn+/q/r96/x9Wf1+28vS97up3x/N3w+o38/x94Pq91tejr7fXf2+y9/voX7/An8/pH5fvDx9v6faBjP6vkzYz/A3rQ1udAX6rrXBmL9rbfAJ/q61wfWuSN+1Nhjw94NqGc/S97vRt2tdKf92gL5t0beD9O2D9O3u9G3hyvm3e9C3Ln07RN/eS9/u6dwAv135KuLbzhDshEFvuzeETSN+52BLztm94Yn+sJfdKD3udMWLcvJIyyOEjAtNNX1YtukO/gpemaA9eW1JxxgSY018o4y2FprbL2g73gTo5ub6Dfi7tTF7a6DdWqZpn5HgxLO87yBx7MshYxfTWZZ0Kx4HrViuw2GJU/fROSWRToXz0d/y4XS4rupmNKbflPx8jsDMf8XKnxGCfpFF19c/DwK6KJyMBsE0O0qZoyRprKX6XuEW0zkzbLcR54cdk/k6zL6f6fViOqazW5yO1U+PmtO+Ku7mLBd8ToKFgtrqsaY8chqS/iRdZrDMnMfTma74B/V9npcABgPksr0E5EHnF4MtuWBHhuB7ozHuzLK+2S4rdBS32zvntJs5Bj8COC1oDdPHctkHljD9j8/pP3PP6NOAMwPnrLqzY0V+/yx8D46kbcDXcFjK9v8y14l9vFwhLnfRQSKs1zc5DXzDkflF3t8GuhbEiH3/A+ZjP7xS2WuoeWOWgu9XRXycp8T8phCDHY6YPxTXHfLnuv/FkG9TJv5h604LeHPGWWNJ1TtQYcAocQtGP7yV2tEKvpR5XOoaRXlwpQXm8oCxx5tejqsCRh1fXAr0UzBd1Z+kH68LdK5EVv8bEw/50JGJx+1NAaMHoGbfb0bfOchV5HMr+E6DGcs=
*/