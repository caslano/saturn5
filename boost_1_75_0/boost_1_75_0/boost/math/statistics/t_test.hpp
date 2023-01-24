//  (C) Copyright Nick Thompson 2019.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_STATISTICS_T_TEST_HPP
#define BOOST_MATH_STATISTICS_T_TEST_HPP

#include <cmath>
#include <iterator>
#include <utility>
#include <boost/math/distributions/students_t.hpp>
#include <boost/math/statistics/univariate_statistics.hpp>

namespace boost::math::statistics {

template<typename Real>
std::pair<Real, Real> one_sample_t_test(Real sample_mean, Real sample_variance, Real num_samples, Real assumed_mean) {
    using std::sqrt;
    typedef boost::math::policies::policy<
          boost::math::policies::promote_float<false>,
          boost::math::policies::promote_double<false> >
          no_promote_policy;

    Real test_statistic = (sample_mean - assumed_mean)/sqrt(sample_variance/num_samples);
    auto student = boost::math::students_t_distribution<Real, no_promote_policy>(num_samples - 1);
    Real pvalue;
    if (test_statistic > 0) {
        pvalue = 2*boost::math::cdf<Real>(student, -test_statistic);;
    }
    else {
        pvalue = 2*boost::math::cdf<Real>(student, test_statistic);
    }
    return std::make_pair(test_statistic, pvalue);
}

template<class ForwardIterator>
auto one_sample_t_test(ForwardIterator begin, ForwardIterator end, typename std::iterator_traits<ForwardIterator>::value_type assumed_mean) {
    using Real = typename std::iterator_traits<ForwardIterator>::value_type;
    auto [mu, s_sq] = mean_and_sample_variance(begin, end);
    return one_sample_t_test(mu, s_sq, Real(std::distance(begin, end)), assumed_mean);
}

template<class Container>
auto one_sample_t_test(Container const & v, typename Container::value_type assumed_mean) {
    return one_sample_t_test(v.begin(), v.end(), assumed_mean);
}

}
#endif

/* t_test.hpp
5fG6Hujw3sSuF1Hd4mVRIR5p5MRQR+mypGbd9s40/qpB/j8xJqjqXbVZofGDZgN4McGV4KRL12MauEJ+Lr1cp4T7vFaU5L1mYGgk+dfO5Fd5f2qMGpQ2EwgcxiOMT1X01jEQpzpbN/Z4V7A9Rr72povDWFcWO+vpeWcNt6kKL/Yv7z8RR2BhNaUSa3o7Zk6Ya06yJFgpeZOQ1rQIPuJDndnssOObaKLthSnmvbhb2VWESg+s5Z223sRH01JSuHj2E2FIJdnPb268wd0qIRrGFtH4MyFnFRRHkMZxuEOCu0sCBAju7u7Osri7BncJ7r5ocHd3t8XdNbi7O5ecPVzd1VX1wzx09/w/nZnq+g20i24rGzk9pbev7QT4Gb8r89zmiW2LyXTl75woyt850VF67mRyTHGbZWs78+/OV3/2uPKrQXC1AxKg73UYLlvE5ct9Kd8iPygMNrVoVANWWNn9StDCQgO6sU5gYtshhFUIEK46/Fy0aczk4uDVBhgjvhh606zw/PZVU9hWjtBATxVAg+SISClct6ZWgfoCXcYS2ktEs16tc1W1sabFwrfx6DHsZyinkVs7FWslN22nktXh+enxxfm5tYUF08GBhN26AwylGSqUUCcb7qzy9aPEjaU/oEjYmAiuVLfkuF7WXpqWuZDSgjwkPHL1+ATlOCJPwTxm8MC/43MUjULy4jybU2Nj48LCQpqcacJwudwO
*/