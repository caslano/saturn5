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
DvGAZ7Dcjk32BF/H4sNtrhi3XSn/OQNxULkchvk9Y+Po3onDsD1PDyz79PkGc97GQKZkhyKdYPh73JCiQ3PhgtzPLm+UNKt3iXQa3CYbh1Ms7Y032xhx+BLZItzdg3GzEHRF7qdeumUgbnUFXJaKkir+P49sXRtP13vKvdhAHjG/y7xc2rYGTmSld1G9M7p9+0A8uRlV9pnXB+JXF9FRG/ma29GOPYb1J8+gt7XjZC9Rz6ADsDRDKGfQewzE0shTzyw7B+JpBCrt+NO18TQTKfl//a52HurLlJ+xe7ZjqVtB/ahvGIPwnZWVpRWlXnavhZPHJzqb38vGa56r1L69ZyB2mR/6elSN1KcG8eCqo2Iv3XswFocN9e297VhtZlTq+/pAPM2Q2D7o420AHpZnGg7qmbwdjzMm1ccgHM2s9NZ0XxsrvMKrtl33szGobyvLsnzAxjQHUnmxotqAHLTxwh2KqCXCfeYBA3BiSSXcew+14ez57e0PHITD6gbz6Knp58m6fPuDBuCpgWTfvfPBg7Ci4udAuJi41Hq4cridB8cmrREPacNZY1nm+9kPtfGqJYyah4sPa8fiSJa42SNtOHt+yB++Fs6eH8YeMQBP8wO9Tz7SxtJFjHKHefsAHPZJlCn1yywsXZLQXe6jbRxdkCAOz/w2zh6nzz46CGeP0/qYxMLxDVsdcyj1f4+rGEGjOXhU0qR6Bp7tOr2+uQ7Ftz9J2AUuBW7Ln6vqy90h6Q1V8uaPs2jQjIoPnydIOpaSd1yyR/r6kzj9/OrcvBws8mx7tuA0uajLt4Wjlfze7cxfEM8snRmi/1TQxaKq3AVSmtdPSzrmhs7DbzxDNJEf7WWO8nbg6YSDzFEMpGdp35sySfrIlE4Xgf0U+i/Oa3TskkQ/0pF0MSPiGkbpXzDoy9DuXeK/OKfQO/PgS/v8VLdDdfPu50o6XsVRmf15os0p9b1jSf3ezA4k843LRBfZVXjPdYkGOcWmIvobe0SHHQ809ioYap8nu/wXSDoa3END9Vag0kXWKW7VSxAnN2ZEe+nLiIbTBdXny5Gmb9Ak/doriA79EPNPsq++StJx2iDeK68RNGjlqedBvQmQ2tZnX9vQ4W9mWQIe1KT9OqRTH0VTPcLceIPAED+XhX1mb1M3b+QY0VvgwZby/tE3ye8olmgzb5O0lQ7MYSpt39slDWdAoh1+B6cJV/OYC6LdvMJpuInr905Jm323SuvCqbojafl7Ndrz1Lzc/T6k9eUBlWgjH0CazArRPv5BnQaMkvbnD3HanKzRmWUlJuFHBA3diNp2o+/9GKcrG0qsWjl3fdygd3nKlK8tn+B0fqPL4wHNn4e9C9llChrcPvjJ+MRkXSXlhObX5M67LLplo9f7JGLWsBs89CkTY9sN7vo0Yuw7Zorz2I6ReZL+/z/Tx0k9AiM/Zz9r0OVVLcnIP2dgjPyOfZ7og3QRftaGMeTcfU3FoFbYck/rW3d9QcOsLqvj6osKzSjDli8pNHmzT7zLRLfj9n1ZpUH9KPX7UZMm0iXe935Fo8PVNtEuf1WhGTGp3v81hWbU01u+DjT7pkzrH/E3WjGyf+xu2u6bHMdXSirTdfFNbqxwnae8XbnboK/MS9rbv000XMBJt+q7nNZ2zU06pk/Q7rlzFjqFV1XJLcc/eYRio/Z4sYci41pdxZSwF9fbWEPFlN6Hh20snqHnejx8saqDu7Edixt2esfeZOMUFVOK27O5BddtT3vXljasnfYTtrbhZNpk07MNcRg/mS+fmn/gHUTHIQwQ4mf3IDreVeh+yXbadGwoshPZZWNMHeA/727HUBUp/tLubWPNOD9f5hjbThuLSLgP723FWe8=
*/