//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_STATISTICS_Z_TEST_HPP
#define BOOST_MATH_STATISTICS_Z_TEST_HPP

#include <boost/math/distributions/normal.hpp>
#include <boost/math/statistics/univariate_statistics.hpp>
#include <iterator>
#include <type_traits>
#include <utility>
#include <cmath>

namespace boost { namespace math { namespace statistics { namespace detail {

template<typename ReturnType, typename T>
ReturnType one_sample_z_test_impl(T sample_mean, T sample_variance, T sample_size, T assumed_mean)
{
    using Real = typename std::tuple_element<0, ReturnType>::type;
    using std::sqrt;
    using no_promote_policy = boost::math::policies::policy<boost::math::policies::promote_float<false>, boost::math::policies::promote_double<false>>;

    Real test_statistic = (sample_mean - assumed_mean) / (sample_variance / sqrt(sample_size));
    auto z = boost::math::normal_distribution<Real, no_promote_policy>(sample_size - 1);
    Real pvalue;
    if(test_statistic > 0)
    {
        pvalue = 2*boost::math::cdf<Real>(z, -test_statistic);
    }
    else
    {
        pvalue = 2*boost::math::cdf<Real>(z, test_statistic);
    }

    return std::make_pair(test_statistic, pvalue);
}

template<typename ReturnType, typename ForwardIterator>
ReturnType one_sample_z_test_impl(ForwardIterator begin, ForwardIterator end, typename std::iterator_traits<ForwardIterator>::value_type assumed_mean) 
{
    using Real = typename std::tuple_element<0, ReturnType>::type;
    std::pair<Real, Real> temp = mean_and_sample_variance(begin, end);
    Real mu = std::get<0>(temp);
    Real s_sq = std::get<1>(temp);
    return one_sample_z_test_impl<ReturnType>(mu, s_sq, Real(std::distance(begin, end)), Real(assumed_mean));
}

template<typename ReturnType, typename T>
ReturnType two_sample_z_test_impl(T mean_1, T variance_1, T size_1, T mean_2, T variance_2, T size_2)
{
    using Real = typename std::tuple_element<0, ReturnType>::type;
    using std::sqrt;
    using no_promote_policy = boost::math::policies::policy<boost::math::policies::promote_float<false>, boost::math::policies::promote_double<false>>;

    Real test_statistic = (mean_1 - mean_2) / sqrt(variance_1/size_1 + variance_2/size_2);
    auto z = boost::math::normal_distribution<Real, no_promote_policy>(size_1 + size_2 - 1);
    Real pvalue;
    if(test_statistic > 0)
    {
        pvalue = 2*boost::math::cdf<Real>(z, -test_statistic);
    }
    else
    {
        pvalue = 2*boost::math::cdf<Real>(z, test_statistic);
    }

    return std::make_pair(test_statistic, pvalue);
}

template<typename ReturnType, typename ForwardIterator>
ReturnType two_sample_z_test_impl(ForwardIterator begin_1, ForwardIterator end_1, ForwardIterator begin_2, ForwardIterator end_2)
{
    using Real = typename std::tuple_element<0, ReturnType>::type;
    using std::sqrt;
    auto n1 = std::distance(begin_1, end_1);
    auto n2 = std::distance(begin_2, end_2);

    ReturnType temp_1 = mean_and_sample_variance(begin_1, end_1);
    Real mean_1 = std::get<0>(temp_1);
    Real variance_1 = std::get<1>(temp_1);

    ReturnType temp_2 = mean_and_sample_variance(begin_2, end_2);
    Real mean_2 = std::get<0>(temp_2);
    Real variance_2 = std::get<1>(temp_2);

    return two_sample_z_test_impl<ReturnType>(mean_1, variance_1, Real(n1), mean_2, variance_2, Real(n2));
}

} // detail

template<typename Real, typename std::enable_if<std::is_integral<Real>::value, bool>::type = true>
inline auto one_sample_z_test(Real sample_mean, Real sample_variance, Real sample_size, Real assumed_mean) -> std::pair<double, double>
{
    return detail::one_sample_z_test_impl<std::pair<double, double>>(sample_mean, sample_variance, sample_size, assumed_mean);
}

template<typename Real, typename std::enable_if<!std::is_integral<Real>::value, bool>::type = true>
inline auto one_sample_z_test(Real sample_mean, Real sample_variance, Real sample_size, Real assumed_mean) -> std::pair<Real, Real>
{
    return detail::one_sample_z_test_impl<std::pair<Real, Real>>(sample_mean, sample_variance, sample_size, assumed_mean);
}

template<typename ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         typename std::enable_if<std::is_integral<Real>::value, bool>::type = true>
inline auto one_sample_z_test(ForwardIterator begin, ForwardIterator end, Real assumed_mean) -> std::pair<double, double>
{
    return detail::one_sample_z_test_impl<std::pair<double, double>>(begin, end, assumed_mean);
}

template<typename ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         typename std::enable_if<!std::is_integral<Real>::value, bool>::type = true>
inline auto one_sample_z_test(ForwardIterator begin, ForwardIterator end, Real assumed_mean) -> std::pair<Real, Real>
{
    return detail::one_sample_z_test_impl<std::pair<Real, Real>>(begin, end, assumed_mean);
}

template<typename Container, typename Real = typename Container::value_type,
         typename std::enable_if<std::is_integral<Real>::value, bool>::type = true>
inline auto one_sample_z_test(Container const & v, Real assumed_mean) -> std::pair<double, double>
{
    return detail::one_sample_z_test_impl<std::pair<double, double>>(std::begin(v), std::end(v), assumed_mean);
}

template<typename Container, typename Real = typename Container::value_type,
         typename std::enable_if<!std::is_integral<Real>::value, bool>::type = true>
inline auto one_sample_z_test(Container const & v, Real assumed_mean) -> std::pair<Real, Real>
{
    return detail::one_sample_z_test_impl<std::pair<Real, Real>>(std::begin(v), std::end(v), assumed_mean);
}

template<typename ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         typename std::enable_if<std::is_integral<Real>::value, bool>::type = true>
inline auto two_sample_z_test(ForwardIterator begin_1, ForwardIterator end_1, ForwardIterator begin_2, ForwardIterator end_2) -> std::pair<double, double>
{
    return detail::two_sample_z_test_impl<std::pair<double, double>>(begin_1, end_1, begin_2, end_2);
}

template<typename ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         typename std::enable_if<!std::is_integral<Real>::value, bool>::type = true>
inline auto two_sample_z_test(ForwardIterator begin_1, ForwardIterator end_1, ForwardIterator begin_2, ForwardIterator end_2) -> std::pair<Real, Real>
{
    return detail::two_sample_z_test_impl<std::pair<Real, Real>>(begin_1, end_1, begin_2, end_2);
}

template<typename Container, typename Real = typename Container::value_type, typename std::enable_if<std::is_integral<Real>::value, bool>::type = true>
inline auto two_sample_z_test(Container const & u, Container const & v) -> std::pair<double, double>
{
    return detail::two_sample_z_test_impl<std::pair<double, double>>(std::begin(u), std::end(u), std::begin(v), std::end(v));
}

template<typename Container, typename Real = typename Container::value_type, typename std::enable_if<!std::is_integral<Real>::value, bool>::type = true>
inline auto two_sample_z_test(Container const & u, Container const & v) -> std::pair<Real, Real>
{
    return detail::two_sample_z_test_impl<std::pair<Real, Real>>(std::begin(u), std::end(u), std::begin(v), std::end(v));
}

}}} // boost::math::statistics

#endif // BOOST_MATH_STATISTICS_Z_TEST_HPP

/* z_test.hpp
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
*/