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
Q3P/pXuYc6OX1NBLFDlUfDyo4RrL4/to7fv+e+h9NoTZKHZLp11W4MGogjfPFzTjkMk1xChb7Luu59duuxw6w4kcrVDZ/q7JSVjmeGGUOZEiB3Ogz7LQe3mj8yaWsm7fqddTVmaV7/lGfU8tghyRJajn+tQdjx0bOTX6wjnehkyZJ3fqcT7czEmDNKtYDI9xvIcZmyFgqZv9VG+nsT91yqAsCo8F3C4EitAPYGZKGGvSfr3GHzDPCes8hnklqQcxy/Z9r8ZbsaoO/bp2PFbC/C7wc7AVH/UhS6dGJ/JxWJv7t7ldXc6XNTkF89I6CoKkZEFg9FnoZ7jLf2Fn6nnmfH3TkBOUTu65SQSFuiU5e3bp+588cyrYQ6UgR+tefS9T2M2gURe4TGU+8TU5KYNBXGV8vk2wr6qZ0idMkEJ97aImx2FJHMFROU1YQttAEtN/R9JmFaVsV1RZfs6SII7quoKGV2VMrEwtdoUy4DRUFESJW50TczeNyV/s0veZRZQkfpgHuGeh7Tf0X3tJIjk77qnXdVFXZZLVBcy5z1tceuHif6gjpvpkeIKpc4DaKBgNQdpXXh3W44aWVZSmUK9cwxgkn583/FP/UMWXrAqCOovqnI2fOlYkBfRRYYNlxClTeSoGLG5RZzWrsFrG+YEcm+dEMz+pPDWDtacq0iph3NGd2GosLy3OIJPqm33XRi1/npOmTpX6yMdbr9MEd2YNzyGVJ2deCBOOV/lsgo9SMjIVdVwiz9GN+pnJy1I/SbNbfuPguufvfACsNTn5hkYFG0F7F9DuFLQe3AnABmRqpR/TEmjvAdqNS30amoGS/1ywz39ivw9MnD4Dz51TM5oNer3RoJM+JfmiNTBoxEl+KTe10A178nyzhRF3+HMzipwtOoYMLwlzbquOISNKwvzdxmBVKr5ttukYGecA6fEOnW7qkB2UfpQlTlFuIF2R4V2cDg8vSJBv0PeC7+32WBIzssfCyIdq+QZ9b8RQVtGTrKKXstfCYHwVfIe16do7w/x9LHpr3PiZfRYOX0kJU9/XwmCRqM6esJ9jeisY3l6+Rw7dj3/HPm68zb4faTwk9rEl3quI9sMDOm1q8UWStuMg0fpzne6T50mibS3fBDR+1ukY2Ns4F3pCh4LiwNgYt3NhSfNncWm9jgEPAVyPBpZRJf7tBh2zOjfTVdM5N6zS1WBw1K9/r2OalRu9L1FaVzYSjnw/UFpsk0pfaC33dQtjl3t5s8Rwy8hWOde2mBhbzqFtEmP4tKAy7dlOGPKvRDKGd0i67c+BdO4RY/tfIr+eEtPqN2Nsp6RLvxiyjXdxmumWZYj8Ggzr600SOH6VZrccy4CvKVzHeF6sKdCzuXOSSdCIwnjSvWFIS6Upff4Gv6Tn+ce4tNylAMTl1e0u1rVjTH86lze04/ANWOLYxnac6QPq75tMnDps6c3/xuY1cLy8qq35Vg2LCnJ9/3BcWU/zF7VdxeKTMtYO2XeoGErX9A/z+ttUnBoTk2Tl97AwNKhVfeudKs6aH8in5C4TJzJPuvjwa9GpWUlnereNo2ZV8nWvVpzlb6HeY+L0euuqvt7WwHapfmHds3BYvZTuS+9jYmx/PmSnYGLb/bNdN3A0R1C6r7yvhum2lJd8GO+X2N4SxTcmnYgDQEcfNJLMVxhlXvGNeSX2/SQP6/pW55WDytrJKP+YL8UefT3Q7djJfN8hbW3Pqra2cF5ZnBYm4TubPA8Zea5ivw6i8FazLM8MI/qZpki9OA+jgpVg0iqySUE8T6nldIYkdXJpsTM/t9ghHY3NQP8v/HbNbiGc7beL2umjG3QdjSKoyigKklst9N6hzfd8APT/JtLimcmyKgM=
*/