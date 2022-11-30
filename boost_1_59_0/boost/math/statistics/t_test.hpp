//  (C) Copyright Nick Thompson 2019.
//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_STATISTICS_T_TEST_HPP
#define BOOST_MATH_STATISTICS_T_TEST_HPP

#include <cmath>
#include <cstddef>
#include <iterator>
#include <utility>
#include <type_traits>
#include <vector>
#include <stdexcept>
#include <boost/math/distributions/students_t.hpp>
#include <boost/math/statistics/univariate_statistics.hpp>

namespace boost { namespace math { namespace statistics { namespace detail {

template<typename ReturnType, typename T>
ReturnType one_sample_t_test_impl(T sample_mean, T sample_variance, T num_samples, T assumed_mean) 
{
    using Real = typename std::tuple_element<0, ReturnType>::type;
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

template<typename ReturnType, typename ForwardIterator>
ReturnType one_sample_t_test_impl(ForwardIterator begin, ForwardIterator end, typename std::iterator_traits<ForwardIterator>::value_type assumed_mean) 
{
    using Real = typename std::tuple_element<0, ReturnType>::type;
    std::pair<Real, Real> temp = mean_and_sample_variance(begin, end);
    Real mu = std::get<0>(temp);
    Real s_sq = std::get<1>(temp);
    return one_sample_t_test_impl<ReturnType>(mu, s_sq, Real(std::distance(begin, end)), Real(assumed_mean));
}

// https://en.wikipedia.org/wiki/Student%27s_t-test#Equal_or_unequal_sample_sizes,_unequal_variances_(sX1_%3E_2sX2_or_sX2_%3E_2sX1)
template<typename ReturnType, typename T>
ReturnType welchs_t_test_impl(T mean_1, T variance_1, T size_1, T mean_2, T variance_2, T size_2)
{
    using Real = typename std::tuple_element<0, ReturnType>::type;
    using no_promote_policy = boost::math::policies::policy<boost::math::policies::promote_float<false>, boost::math::policies::promote_double<false>>;
    using std::sqrt;

    Real dof_num = (variance_1/size_1 + variance_2/size_2) * (variance_1/size_1 + variance_2/size_2);
    Real dof_denom = ((variance_1/size_1) * (variance_1/size_1))/(size_1 - 1) +
                     ((variance_2/size_2) * (variance_2/size_2))/(size_2 - 1);
    Real dof = dof_num / dof_denom;

    Real s_estimator = sqrt((variance_1/size_1) + (variance_2/size_2));

    Real test_statistic = (static_cast<Real>(mean_1) - static_cast<Real>(mean_2))/s_estimator;
    auto student = boost::math::students_t_distribution<Real, no_promote_policy>(dof);
    Real pvalue;
    if (test_statistic > 0) 
    {
        pvalue = 2*boost::math::cdf<Real>(student, -test_statistic);;
    }
    else 
    {
        pvalue = 2*boost::math::cdf<Real>(student, test_statistic);
    }

    return std::make_pair(test_statistic, pvalue);
}

// https://en.wikipedia.org/wiki/Student%27s_t-test#Equal_or_unequal_sample_sizes,_similar_variances_(1/2_%3C_sX1/sX2_%3C_2)
template<typename ReturnType, typename T>
ReturnType two_sample_t_test_impl(T mean_1, T variance_1, T size_1, T mean_2, T variance_2, T size_2)
{
    using Real = typename std::tuple_element<0, ReturnType>::type;
    using no_promote_policy = boost::math::policies::policy<boost::math::policies::promote_float<false>, boost::math::policies::promote_double<false>>;
    using std::sqrt;

    Real dof = size_1 + size_2 - 2;
    Real pooled_std_dev = sqrt(((size_1-1)*variance_1 + (size_2-1)*variance_2) / dof);
    Real test_statistic = (mean_1-mean_2) / (pooled_std_dev*sqrt(1.0/static_cast<Real>(size_1) + 1.0/static_cast<Real>(size_2)));

    auto student = boost::math::students_t_distribution<Real, no_promote_policy>(dof);
    Real pvalue;
    if (test_statistic > 0) 
    {
        pvalue = 2*boost::math::cdf<Real>(student, -test_statistic);;
    }
    else 
    {
        pvalue = 2*boost::math::cdf<Real>(student, test_statistic);
    }

    return std::make_pair(test_statistic, pvalue);
}

template<typename ReturnType, typename ForwardIterator>
ReturnType two_sample_t_test_impl(ForwardIterator begin_1, ForwardIterator end_1, ForwardIterator begin_2, ForwardIterator end_2)
{
    using Real = typename std::tuple_element<0, ReturnType>::type;
    using std::sqrt;
    auto n1 = std::distance(begin_1, end_1);
    auto n2 = std::distance(begin_2, end_2);

    ReturnType temp_1 = mean_and_sample_variance(begin_1, end_1);
    Real mean_1 = std::get<0>(temp_1);
    Real variance_1 = std::get<1>(temp_1);
    Real std_dev_1 = sqrt(variance_1);

    ReturnType temp_2 = mean_and_sample_variance(begin_2, end_2);
    Real mean_2 = std::get<0>(temp_2);
    Real variance_2 = std::get<1>(temp_2);
    Real std_dev_2 = sqrt(variance_2);
    
    if(std_dev_1 > 2 * std_dev_2 || std_dev_2 > 2 * std_dev_1)
    {
        return welchs_t_test_impl<ReturnType>(mean_1, variance_1, Real(n1), mean_2, variance_2, Real(n2));
    }
    else
    {
        return two_sample_t_test_impl<ReturnType>(mean_1, variance_1, Real(n1), mean_2, variance_2, Real(n2));
    }
}

// https://en.wikipedia.org/wiki/Student%27s_t-test#Dependent_t-test_for_paired_samples
template<typename ReturnType, typename ForwardIterator>
ReturnType paired_samples_t_test_impl(ForwardIterator begin_1, ForwardIterator end_1, ForwardIterator begin_2, ForwardIterator end_2)
{
    using Real = typename std::tuple_element<0, ReturnType>::type;
    using no_promote_policy = boost::math::policies::policy<boost::math::policies::promote_float<false>, boost::math::policies::promote_double<false>>;
    using std::sqrt;
    
    std::vector<Real> delta;
    ForwardIterator it_1 = begin_1;
    ForwardIterator it_2 = begin_2;
    std::size_t n = 0;
    while(it_1 != end_1 && it_2 != end_2)
    {
        delta.emplace_back(static_cast<Real>(*it_1++) - static_cast<Real>(*it_2++));
        ++n;
    }

    if(it_1 != end_1 || it_2 != end_2)
    {
        throw std::domain_error("Both sets must have the same number of values.");
    }

    std::pair<Real, Real> temp = mean_and_sample_variance(delta.begin(), delta.end());
    Real delta_mean = std::get<0>(temp);
    Real delta_std_dev = sqrt(std::get<1>(temp));

    Real test_statistic = delta_mean/(delta_std_dev/sqrt(n));

    auto student = boost::math::students_t_distribution<Real, no_promote_policy>(n - 1);
    Real pvalue;
    if (test_statistic > 0) 
    {
        pvalue = 2*boost::math::cdf<Real>(student, -test_statistic);;
    }
    else 
    {
        pvalue = 2*boost::math::cdf<Real>(student, test_statistic);
    }

    return std::make_pair(test_statistic, pvalue);
}
} // namespace detail

template<typename Real, typename std::enable_if<std::is_integral<Real>::value, bool>::type = true>
inline auto one_sample_t_test(Real sample_mean, Real sample_variance, Real num_samples, Real assumed_mean) -> std::pair<double, double>
{
    return detail::one_sample_t_test_impl<std::pair<double, double>>(sample_mean, sample_variance, num_samples, assumed_mean);
}

template<typename Real, typename std::enable_if<!std::is_integral<Real>::value, bool>::type = true>
inline auto one_sample_t_test(Real sample_mean, Real sample_variance, Real num_samples, Real assumed_mean) -> std::pair<Real, Real>
{
    return detail::one_sample_t_test_impl<std::pair<Real, Real>>(sample_mean, sample_variance, num_samples, assumed_mean);
}

template<typename ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         typename std::enable_if<std::is_integral<Real>::value, bool>::type = true>
inline auto one_sample_t_test(ForwardIterator begin, ForwardIterator end, Real assumed_mean) -> std::pair<double, double>
{
    return detail::one_sample_t_test_impl<std::pair<double, double>>(begin, end, assumed_mean);
}

template<typename ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         typename std::enable_if<!std::is_integral<Real>::value, bool>::type = true>
inline auto one_sample_t_test(ForwardIterator begin, ForwardIterator end, Real assumed_mean) -> std::pair<Real, Real>
{
    return detail::one_sample_t_test_impl<std::pair<Real, Real>>(begin, end, assumed_mean);
}

template<typename Container, typename Real = typename Container::value_type,
         typename std::enable_if<std::is_integral<Real>::value, bool>::type = true>
inline auto one_sample_t_test(Container const & v, Real assumed_mean) -> std::pair<double, double>
{
    return detail::one_sample_t_test_impl<std::pair<double, double>>(std::begin(v), std::end(v), assumed_mean);
}

template<typename Container, typename Real = typename Container::value_type,
         typename std::enable_if<!std::is_integral<Real>::value, bool>::type = true>
inline auto one_sample_t_test(Container const & v, Real assumed_mean) -> std::pair<Real, Real>
{
    return detail::one_sample_t_test_impl<std::pair<Real, Real>>(std::begin(v), std::end(v), assumed_mean);
}

template<typename ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         typename std::enable_if<std::is_integral<Real>::value, bool>::type = true>
inline auto two_sample_t_test(ForwardIterator begin_1, ForwardIterator end_1, ForwardIterator begin_2, ForwardIterator end_2) -> std::pair<double, double>
{
    return detail::two_sample_t_test_impl<std::pair<double, double>>(begin_1, end_1, begin_2, end_2);
}

template<typename ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         typename std::enable_if<!std::is_integral<Real>::value, bool>::type = true>
inline auto two_sample_t_test(ForwardIterator begin_1, ForwardIterator end_1, ForwardIterator begin_2, ForwardIterator end_2) -> std::pair<Real, Real>
{
    return detail::two_sample_t_test_impl<std::pair<Real, Real>>(begin_1, end_1, begin_2, end_2);
}

template<typename Container, typename Real = typename Container::value_type, typename std::enable_if<std::is_integral<Real>::value, bool>::type = true>
inline auto two_sample_t_test(Container const & u, Container const & v) -> std::pair<double, double>
{
    return detail::two_sample_t_test_impl<std::pair<double, double>>(std::begin(u), std::end(u), std::begin(v), std::end(v));
}

template<typename Container, typename Real = typename Container::value_type, typename std::enable_if<!std::is_integral<Real>::value, bool>::type = true>
inline auto two_sample_t_test(Container const & u, Container const & v) -> std::pair<Real, Real>
{
    return detail::two_sample_t_test_impl<std::pair<Real, Real>>(std::begin(u), std::end(u), std::begin(v), std::end(v));
}

template<typename ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         typename std::enable_if<std::is_integral<Real>::value, bool>::type = true>
inline auto paired_samples_t_test(ForwardIterator begin_1, ForwardIterator end_1, ForwardIterator begin_2, ForwardIterator end_2) -> std::pair<double, double>
{
    return detail::paired_samples_t_test_impl<std::pair<double, double>>(begin_1, end_1, begin_2, end_2);
}

template<typename ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         typename std::enable_if<!std::is_integral<Real>::value, bool>::type = true>
inline auto paired_samples_t_test(ForwardIterator begin_1, ForwardIterator end_1, ForwardIterator begin_2, ForwardIterator end_2) -> std::pair<Real, Real>
{
    return detail::paired_samples_t_test_impl<std::pair<Real, Real>>(begin_1, end_1, begin_2, end_2);
}

template<typename Container, typename Real = typename Container::value_type, typename std::enable_if<std::is_integral<Real>::value, bool>::type = true>
inline auto paired_samples_t_test(Container const & u, Container const & v) -> std::pair<double, double>
{
    return detail::paired_samples_t_test_impl<std::pair<double, double>>(std::begin(u), std::end(u), std::begin(v), std::end(v));
}

template<typename Container, typename Real = typename Container::value_type, typename std::enable_if<!std::is_integral<Real>::value, bool>::type = true>
inline auto paired_samples_t_test(Container const & u, Container const & v) -> std::pair<Real, Real>
{
    return detail::paired_samples_t_test_impl<std::pair<Real, Real>>(std::begin(u), std::end(u), std::begin(v), std::end(v));
}

}}} // namespace boost::math::statistics
#endif

/* t_test.hpp
nUSFDGaMOaN8Cuq8IXvthDh3BTRVuOj0wbToYU11cIGDAp81v8vaFd2ViWiKa/iMnRskh2zdXCGcJh2Xkyi8uoZre+VRyD4aW0X87KSWh7lNkQEu7tb3SauGdJKZIBKmOFmE61vJzBNVBBQ5xTXzlQjZ96ifBgspVKjvLIZcxoJN/wNhuo2vN1kE+2k4IQzWQgpICpuw7VSG7ODvGQCFSGrHhwPKgLD7oWqo/x2EDpYqXQET2urzMgkFEF0p5zJN1XcSq5GV2tmkLEV0pPef7FGhozYFsmx9QvilvYyXbfhZ65D4e1tQ9Rwar+Tm5J9tnVZDLK9kjgIv1rlFQUKTa5IVIhnn8rvq2Q/IrgWUrPVBkky5qZF5jMrMzKije28EhHqyfQWmtpe7tSpbpNMXMeCAv5imOLUBhgIKhPvuRbY5Sbi5OlmgCxTqQjyGmaiCtFPn4GzjJffyspvo0KNDStarot1JY4v9Dj0s0WpsOdJAXX+uxeDqS0ZvUvTL9xmq+02jIMETAdhOjZKafhxGKbymTr0+FgEHZHZuC2HMvpz8gqIhmUJwJvPSUFaX3wuPBLUuflXHQ1PGBv3amPy/qv+NLs4UktI3m1rkmmqFDpzV1mIrXfarl0RewB6NJqw+0ejMtnXP707UhVefwV3Hj37ypm8zeB4xPrnPlH+aD2luGgYGwWmSMIbyq9vomoypPa8e2oFPhSqY18R+DZdyNsexxzQNYT8oNwJAe9XyhNXcq3ihqUc6W15INavDCCSBRCY55ouv4LTbRiHh0GNNvJL8/31jpnPJEX+X/nuX34IsUHqjY0Pl7BtGFp1iCxmWQM6VgI8agS5Ft0IWBEsW86xdR0qMcLEpWZwMIT6mZrIeae1LDzrvL0sZQpCLgtvbUkgi3xvNqNcd9m2C7uFV9tseH+U38ob9e5XXbeomkdJqPv+G/J6YH2Ea6el/WUZx5Gevk0Jq1Y3joE5GqQZi58jtQX+vHevcP+tJexipaiLAnSCf44vqFkdKIA62L6vYOozlQpqigaFnNJRoGtFsqyJRXXB3YNhLqKrzq9XSfQQyRkOLVFSU9EsYGWIxfPQjvOIueHOA1uzJEBqj47D+FqD2bNwncrtV0xh840NMEyzoCuugfy/vGi07WlRgV/yvAUYFSU3XnMd+bugs3w76t0UuxxnEzn/eRHLf73WdX1MG9e5mc8HdWfJ7+ozCGRLJVwgPNdhp8uIV4EgFm7GI9ZbaAzlyD33pPtNxYwtUnzEC27Nd6x6r4nRd9fXQx2qZKzVDlPoXo5ppft1sWuvqwnJoiPIlE+Lv2Hv8BXMS4kogiDDxm7SEyfjGSTjhIwm6ZonChbP+s2aZ4El7otBlVIVvHVkhl00L0qg0QFVqT3vXf4xB1pKxaom4OLgph0Sp7jH81PmY/Tic+HL0005P0MVvA4Mp9YlQs2hafswZrU3Z0LhyOXaji/t+ZJqtJEJ3O6f2u5Mdr+9oLMxXveI3tIeQ9tiJ+VZYq+mJMj32+ib2/kCJsbFBnoKf86YjX2/pVHeqOMcHjopA2cMLIYoCKMsSGz1Rr8LQiqdcES6LGAt86DjVIVG1SlHiiYChHe/a0TDmarkwHhIbnbERmdUkVBHPhVp/cl/yRd9Ejs4dhYUrwexY3mWd5DP3rVk/qLVJCstaTPm2QSkEpkPd5oaK9xPagwyP2ZCe/KzOUzpbukJBWprne9MXQwXaApN566yatju/xTDFV+zfIbcq7lBuLnvbupNE16T8FECQIgOdE6e1e/WYtnc6YQVwN6bavKIqf5nS4YnDaB7pUlahEyb8Dx6J6U98ZPJALZPfgALvlPfSn3GBpctHxGJXhuNCfCHOG/0nn48vpiWRG+AqukB1brFJCmbsFT0oE/svTR5hhk1HVcRVdAKRnupbbnKZYLEMeXphzpp5i6vx7tdM/Ben+0Cp6EwSfqGlEOaFlcdY7DiUTPF1PtfJcuMaEQ64lVDLJkumc2zILS1z5Oq3Rf8vQudaGzLUXsCjgecUdpvaDTNGiDADZEC1JzoYA7oW2UDEXxtukJwQKUJsa7UGv2VnXbdmNHfSmHNnf3UOXLJXPlJVYVZZAEXUK1doDNgeyPIyOKldHrTLJkhI1x4m0b+jVRwjS9jcwtornV/gnWz2jiPlWrGxSlT8NRiieNRpNKLPmZDfOU4ayYlPmKsSn6tzba+AM4bwdhk3/bVmt0Iwcqb5/T0QFBWfZazZ6kD0x12mHmBke/ulS9RPp4vrRKlGbsGpvn83jE0sSW3cmjNwZt4kZiTN8UqqrE/JqiH3If19BlCCQa9BHUOJE1+41NDfM+xOUaPI0NipfvB+y7nTJC6nLO4h0S1cCaLQdnHNp7WqveVeeU1bvbsOkyYP0oy6u1HJsYwGiy5OpYUZLZapkIEBngRsXjjwCSg4ul4g5SLbueyKZi0Hbve535mDZxqp1hoywOiklmwDtbrT082Nk8WwUaKPpRzu4p+C2r4RMDkm6FJVJzJyhviG+rO6jGIKuhMLF4LsdfMoioHsH7JT3ICjXxEq3sgG0cWnX+CQsT7XEeWGfVQnqXxZd45SDYMb+5KvP2NSgbAYQq/hQH0vsJa8jurNpU+QFFcWbU7BS+kI7lv5c9J5oTXaYG/NHhvR4i8RL28oCTOjMZb29kpRF8m1F5l7xJSa3yJXr/OJhNVOrflPuBQt8Hn1hemHwmQZKTPkrKjkK02ykZlGc/bOGiYm+Susm2Ht9KA5gNqMoFHDy5MS4CPp2JkQ1XIsBobSC7IvnzjP3xvNNA8TiHqLMhRC+SX6MPgOGRo3vS7o9Vp9m1kOSArE2tWCMILMBqAHvQyPGOlawBula+WwvlIfiB8ZGtfjUhFKLMfKK81+YXBOQCC/maRQ5ga4oPN48aD0ol+wL/rvcCe+uoRZ70i2hfcGQ/pKKNtdOSw0sXYgO2Yb59lmSni2cm9zoaJr6Y8kVKGBmVhHqSUZtvzIQ8OLge+SO57oMq+PZCJXrBMza0O9FtqxnyeoTy4rp4GqBzK7z0v+dAaOSqaFRTquY81+/Dfhi1/oeaNIP0TK07kxLqBR3KoK/OkRhbpDEiF6wATsglUg0xyFRdBl5UfUGNvJc8Edf0ZvgGgc9MUsZDQNGQsdnZMfIDA/qhszRbQ8u69UylXuI1K6H1aoDxuItPQkkJhXFvI6uQx+RsfEzbqjbF3Ez4ajfHjxwRxDDAoUhMDVaGYbXsi69D8F5bbGzWLOlaVtFw0LWaAQYRB9fb25HWZCo/BUBAZddgnQTwOfVzJI8ketrjcCD+yJto+7uKqmw3myAs8OTtOXFsPCHn4JURyy0BgqUh9lVfkSlWJbpe39PSb0tbr5+KwRS/9D1zMJOsZpxgJ3SfnLZnqGCdJC/LrWd+zuiD/PX78ak6DEn4r2Lm/w9onAwItyeNPYT6fr2rVEoFGlUZSThoF3K8jf8YDnRpgsYGUeG4vJCX2pNURnsrq4+kdUfKrrGA8PoGgbNr7cmimUvcaZ5u1SXIDBxqn/awxL+89yMG/5j1XoEY0G9Aa4yJchL3y2/M7pJrP9RW0qE1b6QvlsvKbrErw8Em22O6Nf6ArAW82j9VSs8MPIua5ewHmZjmFY81bWOp9wCPwNJZdwjDA5tXdzb1Flp9xz4tMLlgwknkc1ysiITYSXxN5gqmhWP5pokvkHSCmYWG4cjwUQJVcSEyCjqW86Hu7WJCP5zPVSWwgqe1ORCkpQza9+5y5FZvTWcMwJUWvZYwTtZj/mcGz8/eir7OZ2agkpEsiaYAgDJota2sYDeSgh24heL2ySK2U7TLJTTSXQijTJgmvo7RdCDpdvjUafA6GHQShHAhHVt5E7GUY7utI3pvlVU1Iosrvhqu/K8K285KdCubQPtxl/n0QlQZxu02EkeTw3o/tLn/xASXiod9NAnc0HT4sDsC2YroyJi8h3yvcaUPVOALIoIdf6HU41wCVwQ+oKepS/i7UxA7Cbg08ky6EqC3UOoq/KXBNI69DLnE/e75cJAV8s3VM5bzvg4NBt4ZFE5R+LGhkAoJ6vxL1kiO/jlpgE13skas1eEXe4sAxcYbFhsYgYjxaJh/6S6BuSp6C3KT55OtpM/a8JqBBFZ6I5NqjNWp1fctD02WWFYpwfH9RxsQ60PvgZpJQfKWYObV9gC7ET7/hSY7mXRs2X9zpE4J3YyC9V1229096hDV65NOxpN8nWN61KGkYaKJAOg/KAq2KCpgQNcVP296xONyCUWTpfuynUN9QeyLzVEaLDX8PcGJQnfXSqg40NNhLLda4FUay2opAkUzESahLHvttHsp0RaEbBlLnLuT/coWexX/KXs9OEJVR/e425cmhQ4eNR3ppBcJfuMWwublRw4jPfttEvKiI/5rW6730LGRsPYlYi9awnpDgkm/QwA0ijJcYBI+rBb9AwplHKyaLjsx/SxZYOZhfVEy43mZeEXYVJGS48BwmL5BU6iYkPVtmmgdiMsW2is61jqN4Vl6OV8LCde3+pQdlso6hd9QSsoOs9D8p8TvhBq2P24k1a43k/xm2hkJYwVeZQQ2RgLjIxzXzcN9iO84H2XXKoRHB5DYo9uGvbTkkEIdGQqjkjREfO0Zqr4hvsii5yGs5LbLPeK6lAyPk28Ntet2QMLYaaLtmLQjOsiOi2EBuQvmq6pUTYa0LV1RVIeMbFx1Ho5Q2PJFjg6wF2mjWY1YjSM6xbhgsvLe0DraAvTw15BvPd5T3uTCTIJrVXAwHxJIkbpZm0tJzX+5GtwIi1tyT+w3RmPuH0GKHw8fOCQKXQWYL2ObyZ0mifFaFMcxk7haqb9j4X9TDZYpn3LDBVmu4c1k3YKmf/s2zFYv1zL/6kUX6vF04fN9geK7aHZGqDOPm+4eBhyCVfpj4lFe8JHWUItZE3AVNWeBs7at37miHvL0uwMPOtQjZ0WNCJ9OJyh03V7GY+LCh2M8B6Orq4jg473cCj5EDlljOIzNr6wwoNaT3B3BgcbzAjjcSkNZCTiQ3DOTWazBmSlSXGzpM4zbIVddEdhtmWO3gZhGAeKjFl3XQdgvEMkcmQ2/KsuevJqawGZNRaIRrv5uI0a42PWS5E+3bWtfrLLWXjrSkN59T9JPGY7tpMl9U306NpM41V6bTbzv5Pt/1qeqMlk3/H6HLT0qhZaloFSM/T89HP59grRq/o7UYzbI3xzgUfRG3WtOfhyO2L1UTcYSCvoNggkU4eYj17lBrl6KqMke6J3axl+aqh5xtZYQVaLVSOMZq1b+dWwSDEdJFID3OqxY5jSVTE9thLxM5EN8uXbaG9202IEJyF1OdeD3rmpRSNolqtuy/PSWtq07QdTTqm1w4Sv705xatiZS+SxZ6xErg3BxvU8yix4hA/aZgvjWAX2zbr3ytFolEbMwPMQ2KZGgtk2LWR86SKwVwFuCHKHyxiKzBIxC3c5vy3kK1e5OUu5JdXpdgm8Ghhh+nQruLadczQ2pR79EZmU3chbEJ2PUGZD7NG8AUrlVW1rMJ6sbfqhHloFLdINbMtV2pudUN3M0US6MS5dqGdLPKAlyhlh4ZdOeSfon33oDDDkmP9zankycZnaQ67f8EFssy2aKzSNESTbdvp/Z+NOeHDzlWBUFNr8vwcCuuGYZjmM5yak2XaHfdCMBkpEIoYW4KhEiaffCM1W14fig/37itqHNR+KIZtx+kHqiOra6m2P0LHAi64MYG8xwz6X9sOWD3AOpFJT3V3nKvvuY5R4MYEFaUFkyk0CLhv6F1BZo7w+VQ39gkb0hjG/A9BOQ6U93HQVjJSCLL9XxmLEUbQSphM+KobjESTefOKfsi8Fi3S9HQF8+JbXXdieNIq3R66WoQEJblXz+o+njLtXYVFf1Vr0dfghnkfHxfjqEPnbifE+dSEBC2FHrh3z6patQ/xKaXFS2yFUHP6aJysJGJUES0L+3zC/ubFKZLPwzSYEE1H4Q+D6GfExQ6ZFNV0K6ko1mBzQctaB+uWBCzCBpn35eF+p5DwG50yAcuMJByNo6TejqfdMIwB5gbyoVLefM9tSN0t6gonWqFlEQEremPe9jl8wjuehnsh8+SS5Qxu5icVl2aSMQjCOR3g6NwX4rRrEd37X0PVJeiymJowV7ZWQ0IjWnouo56IbGachnt0RAKuoSKrphei78tzfmvYTVXUWqx88jp7yAqJw/9FshwZddOLQBuinj3h+X+0Udv16yeg3Ra/12Gdm5okdsb5/EAmB3I+tl7NTAPvhgV+8quu6QoG3xY22S7WnReZlCXVQze6aasJ4nfr/JDs9gsgG6MNO6VYdVviCTOmETPpKm37lYZy0xB1tXCVYVwyyxA++QrzpdnTcrtrdsD2sAxEQgc6Gh3tpifiuRouLD1TbuNpqiBkIwDmet3C6HerPY/BLmL5tpGct5LvpI6nqLmoua4SCVZh7gr2QFgEe0qGG+0UlWsb6haKs2miJrp1+o68dyi7WS2fkTr58ROdJaOSrXeb8FzcKxpL+VhY71xQdZlvBVpxn4VXmy4vGli1O3G65VWfhwOeaEKI58W3jBT1BYZtWgEP5neJETXS+RjNIvlWUHzxvTVwb2DJ8EnFlGiErm7FqLyc68eo8AgTnB4MlRAiMC3N/PO+i4dWVTtUQQk0NXvME+xOdNTRX9DoI4hLkVhiT1ZufEgONM2rb9eIJza0IWIJDOF8Bnt6AEHCL07IOZs2F9LPBDHX9tPDbcxHuVqxDnvZK4fnRAg5bZIcwaXWz9+cdVCZWShwT3eyW+Hg2sGCt5IbdhDsobeInxkctxz2ejxCoLb2xzzSoEB3WUuoMGsGqtI0zOiqDTrEpmXXuPk3KXNbqF+qvKmTsqCkKANce84+LxDgzUpyrdP+62u2MwtfHhscNyd0MbFZWaHESBnCN/buQfkaVOiiqrhjm5IO9fLODqyuF/kddpNSF+2KDrrPBJcyREjIkQ+QqE9F2Gjn7dQ4viJLvlTAzcVucsQuZWgy+lPi1h78+92EggTKQF/Y+c4B0/SBlNqFzIN8nHdt9MnXz2d8sXO0tKb2lRqY8hfGvg07AUdhI2cC8t27Ib1r8jadFknsklpV5qCmkr1PWL2izqOo+hlAuFn1uN0ovxi4isbT14hTi75/Y+ssP/KHFS1Zahu0EnnbRFdsXJLucaBEKkR3EtHo/cp5bowR+i0X0n1DVXm4xnTZtWEbS9F/4RcelrIzom1wajYWSCpQBbjqiO7Ghuh2A++HO6qYieKgbbWn/IV3/l/duXO0Gr5ILB5u+UlKEhbeQnBrwuXPZKOgZFHnNqUeT8WRW43We+9H0sAuXi1ShTQGQSmz5mZkwrxyv0w8M1DY6oGqZL6Y7NGLbKTvwNROpBdfZ/mxDMb2xXsjRGf9iuhBMEfm5XsQ+zVkawQJfuJmmDwMF0YUKl/8inf2LG2NyNnSndSusu7IvB0YKZuWML7MVvEvkUKwnFDdABKR6JIHzCwJsqtMvyysRKSe/kHiw5OugUxcnv358wbtwTSxaVTF7KKet180TbgrGmCX5J/tiiDE1VJsKpHn4ZF8mQckbJQcEK7356PAaQMcBDVpIQnmIulXqLJv9mO7/UHYM4mS8XFPY51hSw/JP8Iq2N9DTPPw3BSE
*/