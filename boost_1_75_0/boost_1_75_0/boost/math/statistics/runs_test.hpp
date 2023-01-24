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
nA9vbxslMFLMm7K7Jwz+eij5slNvc+JMsZUDoKZ5EqBYAAumjWw7XvmQ7CbjJ8X7FWF01yFXP2068RtdYKr8KxCXP9wPpXUcru6F5Gy9eEMzRzYt/fRFd7poYlI5L8Vj3LP3mzms8Vgl7G3a2yhDJJ9ReSXk+nHlKdtNpWz+QWy9tpQ62YFyuuH85+od03IyPAkuDmp1ftOparpMGN/K3014iO2XxGY/g36R895kBnHRfY+aC2byWANN151Ma9x3YRX2DmDpM9nYzdBIeb/gMbA4XRhcCONOyJPqflFzh92CUgvniasqyuB+ZZg2sipouU6D9YNaL03gEMN6+zvfOx/1nP2P1d5C54Sw/GbBfLCGsITgGflFt19MtzMIzoXuaA6G3kMtsbLrct0WKRIXmk3Xr5/dgbqewLMQ2wVnWlKD8QC9Fipeb4WRwtLB1PbObhJerCxZntvglyQi4l7mRyhCTpOiOxyCVs9gc0ErgplcFfa++Gzk41z8uHcVFS/t1vnI5NubjayHoQDBI0HyGP3AQvn805FJdPF6aHmqTW8yvAFw/gjhhdMi1nFNhQMKflhjZX8QWZ4/fT12quNAnAzvPT5s2vCukbBuSAQGl/8UzHwqkP4lr+G7PCExM5/bxEfv0p7JNRrWObLujbBzkSV46Jl+/TAwbdqDybuc/DB9Tk0r1DNkn11Y1wuOQUnorNumNJGYRqGYahxV
*/