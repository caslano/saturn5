//  (C) Copyright Nick Thompson 2019.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_STATISTICS_LJUNG_BOX_HPP
#define BOOST_MATH_STATISTICS_LJUNG_BOX_HPP

#include <cmath>
#include <iterator>
#include <utility>
#include <boost/math/distributions/chi_squared.hpp>
#include <boost/math/statistics/univariate_statistics.hpp>

namespace boost::math::statistics {

template<class RandomAccessIterator>
auto ljung_box(RandomAccessIterator begin, RandomAccessIterator end, int64_t lags = -1, int64_t fit_dof = 0) {
    using Real = typename std::iterator_traits<RandomAccessIterator>::value_type;
    int64_t n = std::distance(begin, end);
    if (lags >= n) {
      throw std::domain_error("Number of lags must be < number of elements in array.");
    }

    if (lags == -1) {
      // This is the same default as Mathematica; it seems sensible enough . . .
      lags = static_cast<int64_t>(std::ceil(std::log(Real(n))));
    }

    if (lags <= 0) {
      throw std::domain_error("Must have at least one lag.");
    }

    auto mu = boost::math::statistics::mean(begin, end);

    std::vector<Real> r(lags + 1, Real(0));
    for (size_t i = 0; i < r.size(); ++i) {
      for (auto it = begin + i; it != end; ++it) {
        Real ak = *(it) - mu;
        Real akml = *(it-i) - mu;
        r[i] += ak*akml;
      }
    }

    Real Q = 0;

    for (size_t k = 1; k < r.size(); ++k) {
      Q += r[k]*r[k]/(r[0]*r[0]*(n-k));
    }
    Q *= n*(n+2);

    typedef boost::math::policies::policy<
          boost::math::policies::promote_float<false>,
          boost::math::policies::promote_double<false> >
          no_promote_policy;

    auto chi = boost::math::chi_squared_distribution<Real, no_promote_policy>(Real(lags - fit_dof));

    Real pvalue = 1 - boost::math::cdf(chi, Q);
    return std::make_pair(Q, pvalue);
}


template<class RandomAccessContainer>
auto ljung_box(RandomAccessContainer const & v, int64_t lags = -1, int64_t fit_dof = 0) {
    return ljung_box(v.begin(), v.end(), lags, fit_dof);
}

}
#endif

/* ljung_box.hpp
6ZHYO2UXmjPMF8vJf77+0b1MeoGH0FO6Yvk+rFiJsxff+CsKQLQvAfdTXGZ3f0Nb/XSVmOKv3z3eXl9o7wRd9gr5pWsXSq7qDYNi283A5joDpLYji1NnrjtOgGozl1n7Z1sseEnkfIjlaups4GbBAeVv0cK9OBTYFYfDnMsr3xRthnD7xluIquEDSgn/gReKm+2sqwfB7BJA9vli0p/FsR8hzRjWd8lyHNWbLMRXd4W1ArXQi9Q8WgNZ4S4jK0aWB3EWdy1l+iMBNA+sDifhs3v0Kdg3fzd6V2xeflzcj3b76El0lhUlVVVWhrXYsg1zWRHQ6L1Rilds14ER4aup6bws8iztDWXhWNUjwqiB+xsFO99p+H06QHQbZ0zJir8+eutzDj2TfeJv8iNmW+OvLFFqepdJCrLqbyjfM2Vmzd8wD9etelmtdBNbPIin4cLcSBPR2siwI4cZ7WMrB0Jw0U+QTmwTXgqmpulrRC68vHkelIouPTUJ8+PkIFNRfiwp1cOE81hhHi7LMX/d70XT98kOQHre3qwQY6kiam/BjHlKWjVNLRVoE9zNgQ==
*/