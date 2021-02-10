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
t/ehioV6fFo8qKVxK1Q6O5Z1diDVCbxg2GFIo60YCbhpO25XhoxQ4znUGb9rLToa8LK/MBB7kUI578RovOoaDW0DsmNtW+kcC6CdWfPMefoBQQYE78CAcLdZBq/LBZCHSJXfEsPZgdalX6+Nq8BvyHo3T5xPrSvbbYVJodIAeTodNVpfmrbxkU4lhc/n93surTKJa5JPZmf0Q8AjDYoyLb8D8Zkn/0EWn5xPLy6vZtc3uezBqAQzJsDJvGGwdQcSGZiaMAA1CCICjYnwheggiY2nROldz0pw/X4gue1b69i5wziYSZB9W4z+XmTH7/4FUEsDBAoAAAAIAC1nSlIdRNPELAEAAOkBAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTAxOFVUBQABtkgkYF2RzU7DMBCE736KVRDH4BZaKMjNhR8JqQdUCegNmWTTWKR2ZW8LeXt204ZKnCyPv8zsTgxhotImLJRxvg58fGH3HWKVCvX0vHhUS+vXqIw+yUYfSGUibtuOhcqSFX04j7o6g/vWoac8uYo9yv7CQMK4x1goH7xYD1dTo6VdRM6oXSsvJwGMtxuecpWvIMpIEDxYEO5Oa3hdLoACJKrCjhjWB9qUYbOxvoKwJRf8PPMhd75sdxVm
*/