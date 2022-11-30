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
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
*/