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
TBqL1FPZ00L/nnHa0IqV7evjOzPXhjFyaSMWyjhfkyxfuP2mUMVCPT5NH9TM+gUqow+y0TtSncALhg2GPLpKkICrdivXlWWbqH7d64LftQ497/GyOwgQO5NCefKpUH80NVpeB5SKtWvTzUEA4+1Ses7fIaT+gDxYSNit1jCfTYEJIle0ZmH1DjYlLZfWV0ArduQnmafc+bJdV5iJVYB83Fu0VNq2ocinKYOP57d7kRY6hTUcjAZn/MMgDe0NU6/yDlKZSfYfFO/h6Pzi8ur6Zjw43spA8iol1EchEb1icPUWUnZga8YA3CAkP2hshE9ED1lsiDNlNh2bEuwmLdSRdS8Z/Ufpw1//AlBLAwQKAAAACAAtZ0pSiYIx2QcFAAB2DgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEwMjFVVAUAAbZIJGDtV21v2kgQ/m4p/2HbKl/aGgNJLynnRFoDBVogvDipuC+VsQfbifG6u+sQ99ff7NoEmqR31VV3V53OQnh3mZmd12cGW4KQvifg3LDjdMXwdQPFhvFAnBt9153oL9LruuWifTEed9vVJuPsrthbkrE7HBEvl5FhmvrE9NJC721rJ9a2yptekDnwW+CmiAMwbA5ZUpwbhu2zNAVflvdb
*/