//  (C) Copyright Nick Thompson 2018.
//  (C) Copyright Matt Borland 2020.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_STATISTICS_UNIVARIATE_STATISTICS_HPP
#define BOOST_MATH_STATISTICS_UNIVARIATE_STATISTICS_HPP

#include <boost/math/statistics/detail/single_pass.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/tools/assert.hpp>
#include <algorithm>
#include <iterator>
#include <tuple>
#include <cmath>
#include <vector>
#include <type_traits>
#include <utility>
#include <numeric>
#include <list>

// Support compilers with P0024R2 implemented without linking TBB
// https://en.cppreference.com/w/cpp/compiler_support
#if !defined(BOOST_NO_CXX17_HDR_EXECUTION) && defined(BOOST_HAS_THREADS)
#include <execution>

namespace boost::math::statistics {

template<class ExecutionPolicy, class ForwardIterator>
inline auto mean(ExecutionPolicy&& exec, ForwardIterator first, ForwardIterator last)
{
    using Real = typename std::iterator_traits<ForwardIterator>::value_type;
    BOOST_MATH_ASSERT_MSG(first != last, "At least one sample is required to compute the mean.");
    
    if constexpr (std::is_integral_v<Real>)
    {
        if constexpr (std::is_same_v<std::remove_reference_t<decltype(exec)>, decltype(std::execution::seq)>)
        {
            return detail::mean_sequential_impl<double>(first, last);
        }
        else
        {
            return std::reduce(exec, first, last, 0.0) / std::distance(first, last);
        }
    }
    else
    {
        if constexpr (std::is_same_v<std::remove_reference_t<decltype(exec)>, decltype(std::execution::seq)>)
        {
            return detail::mean_sequential_impl<Real>(first, last);
        }
        else
        {
            return std::reduce(exec, first, last, Real(0.0)) / Real(std::distance(first, last));
        }
    }
}

template<class ExecutionPolicy, class Container>
inline auto mean(ExecutionPolicy&& exec, Container const & v)
{
    return mean(exec, std::cbegin(v), std::cend(v));
}

template<class ForwardIterator>
inline auto mean(ForwardIterator first, ForwardIterator last)
{
    return mean(std::execution::seq, first, last);
}

template<class Container>
inline auto mean(Container const & v)
{
    return mean(std::execution::seq, std::cbegin(v), std::cend(v));
}

template<class ExecutionPolicy, class ForwardIterator>
inline auto variance(ExecutionPolicy&& exec, ForwardIterator first, ForwardIterator last)
{
    using Real = typename std::iterator_traits<ForwardIterator>::value_type;
    
    if constexpr (std::is_integral_v<Real>)
    {
        if constexpr (std::is_same_v<std::remove_reference_t<decltype(exec)>, decltype(std::execution::seq)>)
        {
           return std::get<2>(detail::variance_sequential_impl<std::tuple<double, double, double, double>>(first, last));
        }
        else
        {
            const auto results = detail::first_four_moments_parallel_impl<std::tuple<double, double, double, double, double>>(first, last);
            return std::get<1>(results) / std::get<4>(results);
        }
    }
    else
    {
        if constexpr (std::is_same_v<std::remove_reference_t<decltype(exec)>, decltype(std::execution::seq)>)
        {
            return std::get<2>(detail::variance_sequential_impl<std::tuple<Real, Real, Real, Real>>(first, last));
        }
        else
        {
            const auto results = detail::first_four_moments_parallel_impl<std::tuple<Real, Real, Real, Real, Real>>(first, last);
            return std::get<1>(results) / std::get<4>(results);
        }
    }
}

template<class ExecutionPolicy, class Container>
inline auto variance(ExecutionPolicy&& exec, Container const & v)
{
    return variance(exec, std::cbegin(v), std::cend(v));
}

template<class ForwardIterator>
inline auto variance(ForwardIterator first, ForwardIterator last)
{
    return variance(std::execution::seq, first, last);
}

template<class Container>
inline auto variance(Container const & v)
{
    return variance(std::execution::seq, std::cbegin(v), std::cend(v));
}

template<class ExecutionPolicy, class ForwardIterator>
inline auto sample_variance(ExecutionPolicy&& exec, ForwardIterator first, ForwardIterator last)
{
    const auto n = std::distance(first, last);
    BOOST_MATH_ASSERT_MSG(n > 1, "At least two samples are required to compute the sample variance.");
    return n*variance(exec, first, last)/(n-1);
}

template<class ExecutionPolicy, class Container>
inline auto sample_variance(ExecutionPolicy&& exec, Container const & v)
{
    return sample_variance(exec, std::cbegin(v), std::cend(v));
}

template<class ForwardIterator>
inline auto sample_variance(ForwardIterator first, ForwardIterator last)
{
    return sample_variance(std::execution::seq, first, last);
}

template<class Container>
inline auto sample_variance(Container const & v)
{
    return sample_variance(std::execution::seq, std::cbegin(v), std::cend(v));
}

template<class ExecutionPolicy, class ForwardIterator>
inline auto mean_and_sample_variance(ExecutionPolicy&& exec, ForwardIterator first, ForwardIterator last)
{
    using Real = typename std::iterator_traits<ForwardIterator>::value_type;

    if constexpr (std::is_integral_v<Real>)
    {
        if constexpr (std::is_same_v<std::remove_reference_t<decltype(exec)>, decltype(std::execution::seq)>)
        {
            const auto results = detail::variance_sequential_impl<std::tuple<double, double, double, double>>(first, last);
            return std::make_pair(std::get<0>(results), std::get<2>(results)*std::get<3>(results)/(std::get<3>(results)-1.0));
        }
        else
        {
            const auto results = detail::first_four_moments_parallel_impl<std::tuple<double, double, double, double, double>>(first, last);
            return std::make_pair(std::get<0>(results), std::get<1>(results) / (std::get<4>(results)-1.0));
        }
    }
    else
    {
        if constexpr (std::is_same_v<std::remove_reference_t<decltype(exec)>, decltype(std::execution::seq)>)
        {
            const auto results = detail::variance_sequential_impl<std::tuple<Real, Real, Real, Real>>(first, last);
            return std::make_pair(std::get<0>(results), std::get<2>(results)*std::get<3>(results)/(std::get<3>(results)-Real(1)));
        }
        else
        {
            const auto results = detail::first_four_moments_parallel_impl<std::tuple<Real, Real, Real, Real, Real>>(first, last);
            return std::make_pair(std::get<0>(results), std::get<1>(results) / (std::get<4>(results)-Real(1)));
        }
    }
}

template<class ExecutionPolicy, class Container>
inline auto mean_and_sample_variance(ExecutionPolicy&& exec, Container const & v)
{
    return mean_and_sample_variance(exec, std::cbegin(v), std::cend(v));
}

template<class ForwardIterator>
inline auto mean_and_sample_variance(ForwardIterator first, ForwardIterator last)
{
    return mean_and_sample_variance(std::execution::seq, first, last);
}

template<class Container>
inline auto mean_and_sample_variance(Container const & v)
{
    return mean_and_sample_variance(std::execution::seq, std::cbegin(v), std::cend(v));
}

template<class ExecutionPolicy, class ForwardIterator>
inline auto first_four_moments(ExecutionPolicy&& exec, ForwardIterator first, ForwardIterator last)
{
    using Real = typename std::iterator_traits<ForwardIterator>::value_type;

    if constexpr (std::is_integral_v<Real>)
    {
        if constexpr (std::is_same_v<std::remove_reference_t<decltype(exec)>, decltype(std::execution::seq)>)
        {
            const auto results = detail::first_four_moments_sequential_impl<std::tuple<double, double, double, double, double>>(first, last); 
            return std::make_tuple(std::get<0>(results), std::get<1>(results) / std::get<4>(results), std::get<2>(results) / std::get<4>(results), 
                                std::get<3>(results) / std::get<4>(results));
        }
        else
        {
            const auto results = detail::first_four_moments_parallel_impl<std::tuple<double, double, double, double, double>>(first, last);
            return std::make_tuple(std::get<0>(results), std::get<1>(results) / std::get<4>(results), std::get<2>(results) / std::get<4>(results), 
                                   std::get<3>(results) / std::get<4>(results));
        }
    }
    else
    {
        if constexpr (std::is_same_v<std::remove_reference_t<decltype(exec)>, decltype(std::execution::seq)>)
        {
            const auto results = detail::first_four_moments_sequential_impl<std::tuple<Real, Real, Real, Real, Real>>(first, last);
            return std::make_tuple(std::get<0>(results), std::get<1>(results) / std::get<4>(results), std::get<2>(results) / std::get<4>(results), 
                                   std::get<3>(results) / std::get<4>(results));
        }
        else
        {
            const auto results = detail::first_four_moments_parallel_impl<std::tuple<Real, Real, Real, Real, Real>>(first, last);
            return std::make_tuple(std::get<0>(results), std::get<1>(results) / std::get<4>(results), std::get<2>(results) / std::get<4>(results), 
                                   std::get<3>(results) / std::get<4>(results));
        }
    }
}

template<class ExecutionPolicy, class Container>
inline auto first_four_moments(ExecutionPolicy&& exec, Container const & v)
{
    return first_four_moments(exec, std::cbegin(v), std::cend(v));
}

template<class ForwardIterator>
inline auto first_four_moments(ForwardIterator first, ForwardIterator last)
{
    return first_four_moments(std::execution::seq, first, last);
}

template<class Container>
inline auto first_four_moments(Container const & v)
{
    return first_four_moments(std::execution::seq, std::cbegin(v), std::cend(v));
}

// https://prod.sandia.gov/techlib-noauth/access-control.cgi/2008/086212.pdf
template<class ExecutionPolicy, class ForwardIterator>
inline auto skewness(ExecutionPolicy&& exec, ForwardIterator first, ForwardIterator last)
{
    using Real = typename std::iterator_traits<ForwardIterator>::value_type;
    using std::sqrt;

    if constexpr (std::is_same_v<std::remove_reference_t<decltype(exec)>, decltype(std::execution::seq)>)
    {
        if constexpr (std::is_integral_v<Real>)
        {
            return detail::skewness_sequential_impl<double>(first, last);
        }
        else
        {
            return detail::skewness_sequential_impl<Real>(first, last);
        }
    }
    else 
    {
        const auto [M1, M2, M3, M4] = first_four_moments(exec, first, last);
        const auto n = std::distance(first, last);
        const auto var = M2/(n-1);

        if (M2 == 0)
        {
            // The limit is technically undefined, but the interpretation here is clear:
            // A constant dataset has no skewness.
            if constexpr (std::is_integral_v<Real>)
            {
                return double(0);
            }
            else
            {
                return Real(0);
            }
        }
        else
        {
            return M3/(M2*sqrt(var)) / Real(2);
        }
    }
}

template<class ExecutionPolicy, class Container>
inline auto skewness(ExecutionPolicy&& exec, Container & v)
{
    return skewness(exec, std::cbegin(v), std::cend(v));
}

template<class ForwardIterator>
inline auto skewness(ForwardIterator first, ForwardIterator last)
{
    return skewness(std::execution::seq, first, last);
}

template<class Container>
inline auto skewness(Container const & v)
{
    return skewness(std::execution::seq, std::cbegin(v), std::cend(v));
}

// Follows equation 1.6 of:
// https://prod.sandia.gov/techlib-noauth/access-control.cgi/2008/086212.pdf
template<class ExecutionPolicy, class ForwardIterator>
inline auto kurtosis(ExecutionPolicy&& exec, ForwardIterator first, ForwardIterator last)
{
    const auto [M1, M2, M3, M4] = first_four_moments(exec, first, last);
    if (M2 == 0)
    {
        return M2;
    }
    return M4/(M2*M2);
}

template<class ExecutionPolicy, class Container>
inline auto kurtosis(ExecutionPolicy&& exec, Container const & v)
{
    return kurtosis(exec, std::cbegin(v), std::cend(v));
}

template<class ForwardIterator>
inline auto kurtosis(ForwardIterator first, ForwardIterator last)
{
    return kurtosis(std::execution::seq, first, last);
}

template<class Container>
inline auto kurtosis(Container const & v)
{
    return kurtosis(std::execution::seq, std::cbegin(v), std::cend(v));
}

template<class ExecutionPolicy, class ForwardIterator>
inline auto excess_kurtosis(ExecutionPolicy&& exec, ForwardIterator first, ForwardIterator last)
{
    return kurtosis(exec, first, last) - 3;
}

template<class ExecutionPolicy, class Container>
inline auto excess_kurtosis(ExecutionPolicy&& exec, Container const & v)
{
    return excess_kurtosis(exec, std::cbegin(v), std::cend(v));
}

template<class ForwardIterator>
inline auto excess_kurtosis(ForwardIterator first, ForwardIterator last)
{
    return excess_kurtosis(std::execution::seq, first, last);
}

template<class Container>
inline auto excess_kurtosis(Container const & v)
{
    return excess_kurtosis(std::execution::seq, std::cbegin(v), std::cend(v));
}


template<class ExecutionPolicy, class RandomAccessIterator>
auto median(ExecutionPolicy&& exec, RandomAccessIterator first, RandomAccessIterator last)
{
    const auto num_elems = std::distance(first, last);
    BOOST_MATH_ASSERT_MSG(num_elems > 0, "The median of a zero length vector is undefined.");
    if (num_elems & 1)
    {
        auto middle = first + (num_elems - 1)/2;
        std::nth_element(exec, first, middle, last);
        return *middle;
    }
    else
    {
        auto middle = first + num_elems/2 - 1;
        std::nth_element(exec, first, middle, last);
        std::nth_element(exec, middle, middle+1, last);
        return (*middle + *(middle+1))/2;
    }
}


template<class ExecutionPolicy, class RandomAccessContainer>
inline auto median(ExecutionPolicy&& exec, RandomAccessContainer & v)
{
    return median(exec, std::begin(v), std::end(v));
}

template<class RandomAccessIterator>
inline auto median(RandomAccessIterator first, RandomAccessIterator last)
{
    return median(std::execution::seq, first, last);
}

template<class RandomAccessContainer>
inline auto median(RandomAccessContainer & v)
{
    return median(std::execution::seq, std::begin(v), std::end(v));
}

#if 0
//
// Parallel gini calculation is curently broken, see:
// https://github.com/boostorg/math/issues/585
// We will fix this at a later date, for now just use a serial implementation:
//
template<class ExecutionPolicy, class RandomAccessIterator>
inline auto gini_coefficient(ExecutionPolicy&& exec, RandomAccessIterator first, RandomAccessIterator last)
{
    using Real = typename std::iterator_traits<RandomAccessIterator>::value_type;

    if(!std::is_sorted(exec, first, last))
    {
        std::sort(exec, first, last);
    }

    if constexpr (std::is_same_v<std::remove_reference_t<decltype(exec)>, decltype(std::execution::seq)>)
    {
        if constexpr (std::is_integral_v<Real>)
        {
            return detail::gini_coefficient_sequential_impl<double>(first, last);
        }
        else
        {
            return detail::gini_coefficient_sequential_impl<Real>(first, last);
        }   
    }
    
    else if constexpr (std::is_integral_v<Real>)
    {
        return detail::gini_coefficient_parallel_impl<double>(exec, first, last);
    }

    else
    {
        return detail::gini_coefficient_parallel_impl<Real>(exec, first, last);
    }
}
#else
template<class ExecutionPolicy, class RandomAccessIterator>
inline auto gini_coefficient(ExecutionPolicy&& exec, RandomAccessIterator first, RandomAccessIterator last)
{
   using Real = typename std::iterator_traits<RandomAccessIterator>::value_type;

   if (!std::is_sorted(exec, first, last))
   {
      std::sort(exec, first, last);
   }

   if constexpr (std::is_integral_v<Real>)
   {
      return detail::gini_coefficient_sequential_impl<double>(first, last);
   }
   else
   {
      return detail::gini_coefficient_sequential_impl<Real>(first, last);
   }
}
#endif

template<class ExecutionPolicy, class RandomAccessContainer>
inline auto gini_coefficient(ExecutionPolicy&& exec, RandomAccessContainer & v)
{
    return gini_coefficient(exec, std::begin(v), std::end(v));
}

template<class RandomAccessIterator>
inline auto gini_coefficient(RandomAccessIterator first, RandomAccessIterator last)
{
    return gini_coefficient(std::execution::seq, first, last);
}

template<class RandomAccessContainer>
inline auto gini_coefficient(RandomAccessContainer & v)
{
    return gini_coefficient(std::execution::seq, std::begin(v), std::end(v));
}

template<class ExecutionPolicy, class RandomAccessIterator>
inline auto sample_gini_coefficient(ExecutionPolicy&& exec, RandomAccessIterator first, RandomAccessIterator last)
{
    const auto n = std::distance(first, last);
    return n*gini_coefficient(exec, first, last)/(n-1);
}

template<class ExecutionPolicy, class RandomAccessContainer>
inline auto sample_gini_coefficient(ExecutionPolicy&& exec, RandomAccessContainer & v)
{
    return sample_gini_coefficient(exec, std::begin(v), std::end(v));
}

template<class RandomAccessIterator>
inline auto sample_gini_coefficient(RandomAccessIterator first, RandomAccessIterator last)
{
    return sample_gini_coefficient(std::execution::seq, first, last);
}

template<class RandomAccessContainer>
inline auto sample_gini_coefficient(RandomAccessContainer & v)
{
    return sample_gini_coefficient(std::execution::seq, std::begin(v), std::end(v));
}

template<class ExecutionPolicy, class RandomAccessIterator>
auto median_absolute_deviation(ExecutionPolicy&& exec, RandomAccessIterator first, RandomAccessIterator last, 
    typename std::iterator_traits<RandomAccessIterator>::value_type center=std::numeric_limits<typename std::iterator_traits<RandomAccessIterator>::value_type>::quiet_NaN())
{
    using std::abs;
    using Real = typename std::iterator_traits<RandomAccessIterator>::value_type;
    using std::isnan;
    if (isnan(center))
    {
        center = boost::math::statistics::median(exec, first, last);
    }
    const auto num_elems = std::distance(first, last);
    BOOST_MATH_ASSERT_MSG(num_elems > 0, "The median of a zero-length vector is undefined.");
    auto comparator = [&center](Real a, Real b) { return abs(a-center) < abs(b-center);};
    if (num_elems & 1)
    {
        auto middle = first + (num_elems - 1)/2;
        std::nth_element(exec, first, middle, last, comparator);
        return abs(*middle);
    }
    else
    {
        auto middle = first + num_elems/2 - 1;
        std::nth_element(exec, first, middle, last, comparator);
        std::nth_element(exec, middle, middle+1, last, comparator);
        return (abs(*middle) + abs(*(middle+1)))/abs(static_cast<Real>(2));
    }
}

template<class ExecutionPolicy, class RandomAccessContainer>
inline auto median_absolute_deviation(ExecutionPolicy&& exec, RandomAccessContainer & v, 
    typename RandomAccessContainer::value_type center=std::numeric_limits<typename RandomAccessContainer::value_type>::quiet_NaN())
{
    return median_absolute_deviation(exec, std::begin(v), std::end(v), center);
}

template<class RandomAccessIterator>
inline auto median_absolute_deviation(RandomAccessIterator first, RandomAccessIterator last, 
    typename RandomAccessIterator::value_type center=std::numeric_limits<typename RandomAccessIterator::value_type>::quiet_NaN())
{
    return median_absolute_deviation(std::execution::seq, first, last, center);
}

template<class RandomAccessContainer>
inline auto median_absolute_deviation(RandomAccessContainer & v, 
    typename RandomAccessContainer::value_type center=std::numeric_limits<typename RandomAccessContainer::value_type>::quiet_NaN())
{
    return median_absolute_deviation(std::execution::seq, std::begin(v), std::end(v), center);
}

template<class ExecutionPolicy, class ForwardIterator>
auto interquartile_range(ExecutionPolicy&& exec, ForwardIterator first, ForwardIterator last)
{
    using Real = typename std::iterator_traits<ForwardIterator>::value_type;
    static_assert(!std::is_integral_v<Real>, "Integer values have not yet been implemented.");
    auto m = std::distance(first,last);
    BOOST_MATH_ASSERT_MSG(m >= 3, "At least 3 samples are required to compute the interquartile range.");
    auto k = m/4;
    auto j = m - (4*k);
    // m = 4k+j.
    // If j = 0 or j = 1, then there are an even number of samples below the median, and an even number above the median.
    //    Then we must average adjacent elements to get the quartiles.
    // If j = 2 or j = 3, there are an odd number of samples above and below the median, these elements may be directly extracted to get the quartiles.

    if (j==2 || j==3)
    {
        auto q1 = first + k;
        auto q3 = first + 3*k + j - 1;
        std::nth_element(exec, first, q1, last);
        Real Q1 = *q1;
        std::nth_element(exec, q1, q3, last);
        Real Q3 = *q3;
        return Q3 - Q1;
    } else {
        // j == 0 or j==1:
        auto q1 = first + k - 1;
        auto q3 = first + 3*k - 1 + j;
        std::nth_element(exec, first, q1, last);
        Real a = *q1;
        std::nth_element(exec, q1, q1 + 1, last);
        Real b = *(q1 + 1);
        Real Q1 = (a+b)/2;
        std::nth_element(exec, q1, q3, last);
        a = *q3;
        std::nth_element(exec, q3, q3 + 1, last);
        b = *(q3 + 1);
        Real Q3 = (a+b)/2;
        return Q3 - Q1;
    }
}

template<class ExecutionPolicy, class RandomAccessContainer>
inline auto interquartile_range(ExecutionPolicy&& exec, RandomAccessContainer & v)
{
    return interquartile_range(exec, std::begin(v), std::end(v));
}

template<class RandomAccessIterator>
inline auto interquartile_range(RandomAccessIterator first, RandomAccessIterator last)
{
    return interquartile_range(std::execution::seq, first, last);
}

template<class RandomAccessContainer>
inline auto interquartile_range(RandomAccessContainer & v)
{
    return interquartile_range(std::execution::seq, std::begin(v), std::end(v));
}

template<class ExecutionPolicy, class ForwardIterator, class OutputIterator>
inline OutputIterator mode(ExecutionPolicy&& exec, ForwardIterator first, ForwardIterator last, OutputIterator output)
{   
    if(!std::is_sorted(exec, first, last))
    {
        if constexpr (std::is_same_v<typename std::iterator_traits<ForwardIterator>::iterator_category(), std::random_access_iterator_tag>)
        {
            std::sort(exec, first, last);
        }
        else
        {
            BOOST_MATH_ASSERT("Data must be sorted for sequential mode calculation");
        }
    }

    return detail::mode_impl(first, last, output);
}

template<class ExecutionPolicy, class Container, class OutputIterator>
inline OutputIterator mode(ExecutionPolicy&& exec, Container & v, OutputIterator output)
{
    return mode(exec, std::begin(v), std::end(v), output);
}

template<class ForwardIterator, class OutputIterator>
inline OutputIterator mode(ForwardIterator first, ForwardIterator last, OutputIterator output)
{
    return mode(std::execution::seq, first, last, output);
}

// Requires enable_if_t to not clash with impl that returns std::list
// Very ugly. std::is_execution_policy_v returns false for the std::execution objects and decltype of the objects (e.g. std::execution::seq)
template<class Container, class OutputIterator, std::enable_if_t<!std::is_convertible_v<std::execution::sequenced_policy, Container> &&
                                                                 !std::is_convertible_v<std::execution::parallel_unsequenced_policy, Container> &&
                                                                 !std::is_convertible_v<std::execution::parallel_policy, Container>
                                                                 #if __cpp_lib_execution > 201900
                                                                 && !std::is_convertible_v<std::execution::unsequenced_policy, Container>
                                                                 #endif
                                                                 , bool> = true>
inline OutputIterator mode(Container & v, OutputIterator output)
{
    return mode(std::execution::seq, std::begin(v), std::end(v), output);
}

// std::list is the return type for the proposed STL stats library

template<class ExecutionPolicy, class ForwardIterator, class Real = typename std::iterator_traits<ForwardIterator>::value_type>
inline auto mode(ExecutionPolicy&& exec, ForwardIterator first, ForwardIterator last)
{
    std::list<Real> modes;
    mode(exec, first, last, std::inserter(modes, modes.begin()));
    return modes;
}

template<class ExecutionPolicy, class Container>
inline auto mode(ExecutionPolicy&& exec, Container & v)
{
    return mode(exec, std::begin(v), std::end(v));
}

template<class ForwardIterator>
inline auto mode(ForwardIterator first, ForwardIterator last)
{
    return mode(std::execution::seq, first, last);
}

template<class Container>
inline auto mode(Container & v)
{
    return mode(std::execution::seq, std::begin(v), std::end(v));
}

} // Namespace boost::math::statistics

#else // Backwards compatible bindings for C++11

namespace boost { namespace math { namespace statistics {

template<bool B, class T = void>
using enable_if_t = typename std::enable_if<B, T>::type;

template<class ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         enable_if_t<std::is_integral<Real>::value, bool> = true>
inline double mean(const ForwardIterator first, const ForwardIterator last)
{
    BOOST_MATH_ASSERT_MSG(first != last, "At least one sample is required to compute the mean.");
    return detail::mean_sequential_impl<double>(first, last);
}

template<class Container, typename Real = typename Container::value_type, 
         enable_if_t<std::is_integral<Real>::value, bool> = true>
inline double mean(const Container& c)
{
    return mean(std::begin(c), std::end(c));
}

template<class ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         enable_if_t<!std::is_integral<Real>::value, bool> = true>
inline Real mean(const ForwardIterator first, const ForwardIterator last)
{
    BOOST_MATH_ASSERT_MSG(first != last, "At least one sample is required to compute the mean.");
    return detail::mean_sequential_impl<Real>(first, last);
}

template<class Container, typename Real = typename Container::value_type, 
         enable_if_t<!std::is_integral<Real>::value, bool> = true>
inline Real mean(const Container& c)
{
    return mean(std::begin(c), std::end(c));
}

template<class ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         enable_if_t<std::is_integral<Real>::value, bool> = true>
inline double variance(const ForwardIterator first, const ForwardIterator last)
{
    return std::get<2>(detail::variance_sequential_impl<std::tuple<double, double, double, double>>(first, last));
}

template<class Container, typename Real = typename Container::value_type, 
         enable_if_t<std::is_integral<Real>::value, bool> = true>
inline double variance(const Container& c)
{
    return variance(std::begin(c), std::end(c));
}

template<class ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         enable_if_t<!std::is_integral<Real>::value, bool> = true>
inline Real variance(const ForwardIterator first, const ForwardIterator last)
{
    return std::get<2>(detail::variance_sequential_impl<std::tuple<Real, Real, Real, Real>>(first, last));

}

template<class Container, typename Real = typename Container::value_type, 
         enable_if_t<!std::is_integral<Real>::value, bool> = true>
inline Real variance(const Container& c)
{
    return variance(std::begin(c), std::end(c));
}

template<class ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         enable_if_t<std::is_integral<Real>::value, bool> = true>
inline double sample_variance(const ForwardIterator first, const ForwardIterator last)
{
    const auto n = std::distance(first, last);
    BOOST_MATH_ASSERT_MSG(n > 1, "At least two samples are required to compute the sample variance.");
    return n*variance(first, last)/(n-1);
}

template<class Container, typename Real = typename Container::value_type, 
         enable_if_t<std::is_integral<Real>::value, bool> = true>
inline double sample_variance(const Container& c)
{
    return sample_variance(std::begin(c), std::end(c));
}

template<class ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         enable_if_t<!std::is_integral<Real>::value, bool> = true>
inline Real sample_variance(const ForwardIterator first, const ForwardIterator last)
{
    const auto n = std::distance(first, last);
    BOOST_MATH_ASSERT_MSG(n > 1, "At least two samples are required to compute the sample variance.");
    return n*variance(first, last)/(n-1);
}

template<class Container, typename Real = typename Container::value_type, 
         enable_if_t<!std::is_integral<Real>::value, bool> = true>
inline Real sample_variance(const Container& c)
{
    return sample_variance(std::begin(c), std::end(c));
}

template<class ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         enable_if_t<std::is_integral<Real>::value, bool> = true>
inline std::pair<double, double> mean_and_sample_variance(const ForwardIterator first, const ForwardIterator last)
{
    const auto results = detail::variance_sequential_impl<std::tuple<double, double, double, double>>(first, last);
    return std::make_pair(std::get<0>(results), std::get<3>(results)*std::get<2>(results)/(std::get<3>(results)-1.0));
}

template<class Container, typename Real = typename Container::value_type, 
         enable_if_t<std::is_integral<Real>::value, bool> = true>
inline std::pair<double, double> mean_and_sample_variance(const Container& c)
{
    return mean_and_sample_variance(std::begin(c), std::end(c));
}

template<class ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         enable_if_t<!std::is_integral<Real>::value, bool> = true>
inline std::pair<Real, Real> mean_and_sample_variance(const ForwardIterator first, const ForwardIterator last)
{
    const auto results = detail::variance_sequential_impl<std::tuple<Real, Real, Real, Real>>(first, last);
    return std::make_pair(std::get<0>(results), std::get<3>(results)*std::get<2>(results)/(std::get<3>(results)-Real(1)));
}

template<class Container, typename Real = typename Container::value_type, 
         enable_if_t<!std::is_integral<Real>::value, bool> = true>
inline std::pair<Real, Real> mean_and_sample_variance(const Container& c)
{
    return mean_and_sample_variance(std::begin(c), std::end(c));
}

template<class ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         enable_if_t<std::is_integral<Real>::value, bool> = true>
inline std::tuple<double, double, double, double> first_four_moments(const ForwardIterator first, const ForwardIterator last)
{
    const auto results = detail::first_four_moments_sequential_impl<std::tuple<double, double, double, double, double>>(first, last); 
    return std::make_tuple(std::get<0>(results), std::get<1>(results) / std::get<4>(results), std::get<2>(results) / std::get<4>(results), 
                           std::get<3>(results) / std::get<4>(results));
}

template<class Container, typename Real = typename Container::value_type, 
         enable_if_t<std::is_integral<Real>::value, bool> = true>
inline std::tuple<double, double, double, double> first_four_moments(const Container& c)
{
    return first_four_moments(std::begin(c), std::end(c));
}

template<class ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         enable_if_t<!std::is_integral<Real>::value, bool> = true>
inline std::tuple<Real, Real, Real, Real> first_four_moments(const ForwardIterator first, const ForwardIterator last)
{
    const auto results = detail::first_four_moments_sequential_impl<std::tuple<Real, Real, Real, Real, Real>>(first, last);
    return std::make_tuple(std::get<0>(results), std::get<1>(results) / std::get<4>(results), std::get<2>(results) / std::get<4>(results), 
                           std::get<3>(results) / std::get<4>(results));
}

template<class Container, typename Real = typename Container::value_type, 
         enable_if_t<!std::is_integral<Real>::value, bool> = true>
inline std::tuple<Real, Real, Real, Real> first_four_moments(const Container& c)
{
    return first_four_moments(std::begin(c), std::end(c));
}

template<class ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         enable_if_t<std::is_integral<Real>::value, bool> = true>
inline double skewness(const ForwardIterator first, const ForwardIterator last)
{
    return detail::skewness_sequential_impl<double>(first, last);
}

template<class Container, typename Real = typename Container::value_type, 
         enable_if_t<std::is_integral<Real>::value, bool> = true>
inline double skewness(const Container& c)
{
    return skewness(std::begin(c), std::end(c));
}

template<class ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         enable_if_t<!std::is_integral<Real>::value, bool> = true>
inline Real skewness(const ForwardIterator first, const ForwardIterator last)
{
    return detail::skewness_sequential_impl<Real>(first, last);
}

template<class Container, typename Real = typename Container::value_type, 
         enable_if_t<!std::is_integral<Real>::value, bool> = true>
inline Real skewness(const Container& c)
{
    return skewness(std::begin(c), std::end(c));
}

template<class ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         enable_if_t<std::is_integral<Real>::value, bool> = true>
inline double kurtosis(const ForwardIterator first, const ForwardIterator last)
{
    std::tuple<double, double, double, double> M = first_four_moments(first, last);

    if(std::get<1>(M) == 0)
    {
        return std::get<1>(M);
    }
    else
    {
        return std::get<3>(M)/(std::get<1>(M)*std::get<1>(M));
    }
}

template<class Container, typename Real = typename Container::value_type, 
         enable_if_t<std::is_integral<Real>::value, bool> = true>
inline double kurtosis(const Container& c)
{
    return kurtosis(std::begin(c), std::end(c));
}

template<class ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         enable_if_t<!std::is_integral<Real>::value, bool> = true>
inline Real kurtosis(const ForwardIterator first, const ForwardIterator last)
{
    std::tuple<Real, Real, Real, Real> M = first_four_moments(first, last);
    
    if(std::get<1>(M) == 0)
    {
        return std::get<1>(M);
    }
    else
    {
        return std::get<3>(M)/(std::get<1>(M)*std::get<1>(M));
    }
}

template<class Container, typename Real = typename Container::value_type, 
         enable_if_t<!std::is_integral<Real>::value, bool> = true>
inline Real kurtosis(const Container& c)
{
    return kurtosis(std::begin(c), std::end(c));
}

template<class ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         enable_if_t<std::is_integral<Real>::value, bool> = true>
inline double excess_kurtosis(const ForwardIterator first, const ForwardIterator last)
{
    return kurtosis(first, last) - 3;
}

template<class Container, typename Real = typename Container::value_type, 
         enable_if_t<std::is_integral<Real>::value, bool> = true>
inline double excess_kurtosis(const Container& c)
{
    return excess_kurtosis(std::begin(c), std::end(c));
}

template<class ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type, 
         enable_if_t<!std::is_integral<Real>::value, bool> = true>
inline Real excess_kurtosis(const ForwardIterator first, const ForwardIterator last)
{
    return kurtosis(first, last) - 3;
}

template<class Container, typename Real = typename Container::value_type, 
         enable_if_t<!std::is_integral<Real>::value, bool> = true>
inline Real excess_kurtosis(const Container& c)
{
    return excess_kurtosis(std::begin(c), std::end(c));
}

template<class RandomAccessIterator, typename Real = typename std::iterator_traits<RandomAccessIterator>::value_type>
Real median(RandomAccessIterator first, RandomAccessIterator last)
{
    const auto num_elems = std::distance(first, last);
    BOOST_MATH_ASSERT_MSG(num_elems > 0, "The median of a zero length vector is undefined.");
    if (num_elems & 1)
    {
        auto middle = first + (num_elems - 1)/2;
        std::nth_element(first, middle, last);
        return *middle;
    }
    else
    {
        auto middle = first + num_elems/2 - 1;
        std::nth_element(first, middle, last);
        std::nth_element(middle, middle+1, last);
        return (*middle + *(middle+1))/2;
    }
}

template<class RandomAccessContainer, typename Real = typename RandomAccessContainer::value_type>
inline Real median(RandomAccessContainer& c)
{
    return median(std::begin(c), std::end(c));
}

template<class RandomAccessIterator, typename Real = typename std::iterator_traits<RandomAccessIterator>::value_type, 
         enable_if_t<std::is_integral<Real>::value, bool> = true>
inline double gini_coefficient(RandomAccessIterator first, RandomAccessIterator last)
{
    if(!std::is_sorted(first, last))
    {
        std::sort(first, last);
    }

    return detail::gini_coefficient_sequential_impl<double>(first, last);
}

template<class RandomAccessContainer, typename Real = typename RandomAccessContainer::value_type, 
         enable_if_t<std::is_integral<Real>::value, bool> = true>
inline double gini_coefficient(RandomAccessContainer& c)
{
    return gini_coefficient(std::begin(c), std::end(c));
}

template<class RandomAccessIterator, typename Real = typename std::iterator_traits<RandomAccessIterator>::value_type, 
         enable_if_t<!std::is_integral<Real>::value, bool> = true>
inline Real gini_coefficient(RandomAccessIterator first, RandomAccessIterator last)
{
    if(!std::is_sorted(first, last))
    {
        std::sort(first, last);
    }

    return detail::gini_coefficient_sequential_impl<Real>(first, last);
}

template<class RandomAccessContainer, typename Real = typename RandomAccessContainer::value_type, 
         enable_if_t<!std::is_integral<Real>::value, bool> = true>
inline Real gini_coefficient(RandomAccessContainer& c)
{
    return gini_coefficient(std::begin(c), std::end(c));
}

template<class RandomAccessIterator, typename Real = typename std::iterator_traits<RandomAccessIterator>::value_type, 
         enable_if_t<std::is_integral<Real>::value, bool> = true>
inline double sample_gini_coefficient(RandomAccessIterator first, RandomAccessIterator last)
{
    const auto n = std::distance(first, last);
    return n*gini_coefficient(first, last)/(n-1);
}

template<class RandomAccessContainer, typename Real = typename RandomAccessContainer::value_type, 
         enable_if_t<std::is_integral<Real>::value, bool> = true>
inline double sample_gini_coefficient(RandomAccessContainer& c)
{
    return sample_gini_coefficient(std::begin(c), std::end(c));
}

template<class RandomAccessIterator, typename Real = typename std::iterator_traits<RandomAccessIterator>::value_type, 
         enable_if_t<!std::is_integral<Real>::value, bool> = true>
inline Real sample_gini_coefficient(RandomAccessIterator first, RandomAccessIterator last)
{
    const auto n = std::distance(first, last);
    return n*gini_coefficient(first, last)/(n-1);
}

template<class RandomAccessContainer, typename Real = typename RandomAccessContainer::value_type, 
         enable_if_t<!std::is_integral<Real>::value, bool> = true>
inline Real sample_gini_coefficient(RandomAccessContainer& c)
{
    return sample_gini_coefficient(std::begin(c), std::end(c));
}

template<class RandomAccessIterator, typename Real = typename std::iterator_traits<RandomAccessIterator>::value_type>
Real median_absolute_deviation(RandomAccessIterator first, RandomAccessIterator last,
    typename std::iterator_traits<RandomAccessIterator>::value_type center=std::numeric_limits<typename std::iterator_traits<RandomAccessIterator>::value_type>::quiet_NaN())
{
    using std::abs;
    using std::isnan;
    if (isnan(center))
    {
        center = boost::math::statistics::median(first, last);
    }
    const auto num_elems = std::distance(first, last);
    BOOST_MATH_ASSERT_MSG(num_elems > 0, "The median of a zero-length vector is undefined.");
    auto comparator = [&center](Real a, Real b) { return abs(a-center) < abs(b-center);};
    if (num_elems & 1)
    {
        auto middle = first + (num_elems - 1)/2;
        std::nth_element(first, middle, last, comparator);
        return abs(*middle);
    }
    else
    {
        auto middle = first + num_elems/2 - 1;
        std::nth_element(first, middle, last, comparator);
        std::nth_element(middle, middle+1, last, comparator);
        return (abs(*middle) + abs(*(middle+1)))/abs(static_cast<Real>(2));
    }
}

template<class RandomAccessContainer, typename Real = typename RandomAccessContainer::value_type>
inline Real median_absolute_deviation(RandomAccessContainer& c,
    typename RandomAccessContainer::value_type center=std::numeric_limits<typename RandomAccessContainer::value_type>::quiet_NaN())
{
    return median_absolute_deviation(std::begin(c), std::end(c), center);
}

template<class ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type>
Real interquartile_range(ForwardIterator first, ForwardIterator last)
{
    static_assert(!std::is_integral<Real>::value, "Integer values have not yet been implemented.");
    auto m = std::distance(first,last);
    BOOST_MATH_ASSERT_MSG(m >= 3, "At least 3 samples are required to compute the interquartile range.");
    auto k = m/4;
    auto j = m - (4*k);
    // m = 4k+j.
    // If j = 0 or j = 1, then there are an even number of samples below the median, and an even number above the median.
    //    Then we must average adjacent elements to get the quartiles.
    // If j = 2 or j = 3, there are an odd number of samples above and below the median, these elements may be directly extracted to get the quartiles.

    if (j==2 || j==3)
    {
        auto q1 = first + k;
        auto q3 = first + 3*k + j - 1;
        std::nth_element(first, q1, last);
        Real Q1 = *q1;
        std::nth_element(q1, q3, last);
        Real Q3 = *q3;
        return Q3 - Q1;
    } 
    else 
    {
        // j == 0 or j==1:
        auto q1 = first + k - 1;
        auto q3 = first + 3*k - 1 + j;
        std::nth_element(first, q1, last);
        Real a = *q1;
        std::nth_element(q1, q1 + 1, last);
        Real b = *(q1 + 1);
        Real Q1 = (a+b)/2;
        std::nth_element(q1, q3, last);
        a = *q3;
        std::nth_element(q3, q3 + 1, last);
        b = *(q3 + 1);
        Real Q3 = (a+b)/2;
        return Q3 - Q1;
    }
}

template<class Container, typename Real = typename Container::value_type>
Real interquartile_range(Container& c)
{
    return interquartile_range(std::begin(c), std::end(c));
}

template<class ForwardIterator, class OutputIterator, 
    enable_if_t<std::is_same<typename std::iterator_traits<ForwardIterator>::iterator_category(), std::random_access_iterator_tag>::value, bool> = true>
inline OutputIterator mode(ForwardIterator first, ForwardIterator last, OutputIterator output)
{   
    if(!std::is_sorted(first, last))
    {
        std::sort(first, last);
    }

    return detail::mode_impl(first, last, output);
}

template<class ForwardIterator, class OutputIterator, 
    enable_if_t<!std::is_same<typename std::iterator_traits<ForwardIterator>::iterator_category(), std::random_access_iterator_tag>::value, bool> = true>
inline OutputIterator mode(ForwardIterator first, ForwardIterator last, OutputIterator output)
{   
    if(!std::is_sorted(first, last))
    {
        BOOST_MATH_ASSERT("Data must be sorted for mode calculation");
    }

    return detail::mode_impl(first, last, output);
}

template<class Container, class OutputIterator>
inline OutputIterator mode(Container& c, OutputIterator output)
{
    return mode(std::begin(c), std::end(c), output);
}

template<class ForwardIterator, typename Real = typename std::iterator_traits<ForwardIterator>::value_type>
inline std::list<Real> mode(ForwardIterator first, ForwardIterator last)
{
    std::list<Real> modes;
    mode(first, last, std::inserter(modes, modes.begin()));
    return modes;
}

template<class Container, typename Real = typename Container::value_type>
inline std::list<Real> mode(Container& c)
{
    return mode(std::begin(c), std::end(c));
}
}}}
#endif
#endif // BOOST_MATH_STATISTICS_UNIVARIATE_STATISTICS_HPP

/* univariate_statistics.hpp
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
*/