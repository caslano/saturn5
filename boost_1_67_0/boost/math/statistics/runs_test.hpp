/*
 * Copyright Nick Thompson, 2019
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_MATH_STATISTICS_RUNS_TEST_HPP
#define BOOST_MATH_STATISTICS_RUNS_TEST_HPP

#include <cmath>
#include <algorithm>
#include <utility>
#include <boost/math/statistics/univariate_statistics.hpp>
#include <boost/math/distributions/normal.hpp>

namespace boost::math::statistics {

template<class RandomAccessContainer>
auto runs_above_and_below_threshold(RandomAccessContainer const & v,
                          typename RandomAccessContainer::value_type threshold)
{
    using Real = typename RandomAccessContainer::value_type;
    using std::sqrt;
    using std::abs;
    if (v.size() <= 1)
    {
        throw std::domain_error("At least 2 samples are required to get number of runs.");
    }
    typedef boost::math::policies::policy<
          boost::math::policies::promote_float<false>,
          boost::math::policies::promote_double<false> >
          no_promote_policy;

    decltype(v.size()) nabove = 0;
    decltype(v.size()) nbelow = 0;

    decltype(v.size()) imin = 0;

    // Take care of the case that v[0] == threshold:
    while (imin < v.size() && v[imin] == threshold) {
        ++imin;
    }

    // Take care of the constant vector case:
    if (imin == v.size()) {
        return std::make_pair(std::numeric_limits<Real>::quiet_NaN(), Real(0));
    }

    bool run_up = (v[imin] > threshold);
    if (run_up) {
        ++nabove;
    } else {
        ++nbelow;
    }
    decltype(v.size()) runs = 1;
    for (decltype(v.size()) i = imin + 1; i < v.size(); ++i) {
      if (v[i] == threshold) {
        // skip values precisely equal to threshold (following R's randtests package)
        continue;
      }
      bool above = (v[i] > threshold);
      if (above) {
          ++nabove;
      } else {
          ++nbelow;
      }
      if (run_up == above) {
        continue;
      }
      else {
        run_up = above;
        runs++;
      }
    }

    // If you make n an int, the subtraction is gonna be bad in the variance:
    Real n = nabove + nbelow;

    Real expected_runs = Real(1) + Real(2*nabove*nbelow)/Real(n);
    Real variance = 2*nabove*nbelow*(2*nabove*nbelow-n)/Real(n*n*(n-1));

    // Bizarre, pathological limits:
    if (variance == 0)
    {
        if (runs == expected_runs)
        {
            Real statistic = 0;
            Real pvalue = 1;
            return std::make_pair(statistic, pvalue);
        }
        else
        {
            return std::make_pair(std::numeric_limits<Real>::quiet_NaN(), Real(0));
        }
    }

    Real sd = sqrt(variance);
    Real statistic = (runs - expected_runs)/sd;

    auto normal = boost::math::normal_distribution<Real, no_promote_policy>(0,1);
    Real pvalue = 2*boost::math::cdf(normal, -abs(statistic));
    return std::make_pair(statistic, pvalue);
}

template<class RandomAccessContainer>
auto runs_above_and_below_median(RandomAccessContainer const & v)
{
    using Real = typename RandomAccessContainer::value_type;
    using std::log;
    using std::sqrt;

    // We have to memcpy v because the median does a partial sort,
    // and that would be catastrophic for the runs test.
    auto w = v;
    Real median = boost::math::statistics::median(w);
    return runs_above_and_below_threshold(v, median);
}

}
#endif

/* runs_test.hpp
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
*/