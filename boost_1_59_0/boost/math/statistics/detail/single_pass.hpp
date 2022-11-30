//  (C) Copyright Nick Thompson 2018
//  (C) Copyright Matt Borland 2020
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_STATISTICS_UNIVARIATE_STATISTICS_DETAIL_SINGLE_PASS_HPP
#define BOOST_MATH_STATISTICS_UNIVARIATE_STATISTICS_DETAIL_SINGLE_PASS_HPP

#include <boost/math/tools/config.hpp>
#include <boost/math/tools/assert.hpp>
#include <tuple>
#include <iterator>
#include <type_traits>
#include <cmath>
#include <algorithm>
#include <valarray>
#include <stdexcept>
#include <functional>
#include <vector>

#ifdef BOOST_HAS_THREADS
#include <future>
#include <thread>
#endif

namespace boost { namespace math { namespace statistics { namespace detail {

template<typename ReturnType, typename ForwardIterator>
ReturnType mean_sequential_impl(ForwardIterator first, ForwardIterator last)
{
    const std::size_t elements {static_cast<std::size_t>(std::distance(first, last))};
    std::valarray<ReturnType> mu {0, 0, 0, 0};
    std::valarray<ReturnType> temp {0, 0, 0, 0};
    ReturnType i {1};
    const ForwardIterator end {std::next(first, elements - (elements % 4))};
    ForwardIterator it {first};

    while(it != end)
    {
        const ReturnType inv {ReturnType(1) / i};
        temp = {static_cast<ReturnType>(*it++), static_cast<ReturnType>(*it++), static_cast<ReturnType>(*it++), static_cast<ReturnType>(*it++)};
        temp -= mu;
        mu += (temp *= inv);
        i += 1;
    }

    const ReturnType num1 {ReturnType(elements - (elements % 4))/ReturnType(4)};
    const ReturnType num2 {num1 + ReturnType(elements % 4)};

    while(it != last)
    {
        mu[3] += (*it-mu[3])/i;
        i += 1;
        ++it;
    }

    return (num1 * std::valarray<ReturnType>(mu[std::slice(0,3,1)]).sum() + num2 * mu[3]) / ReturnType(elements);
}

// Higham, Accuracy and Stability, equation 1.6a and 1.6b:
// Calculates Mean, M2, and variance
template<typename ReturnType, typename ForwardIterator>
ReturnType variance_sequential_impl(ForwardIterator first, ForwardIterator last)
{
    using Real = typename std::tuple_element<0, ReturnType>::type;

    Real M = *first;
    Real Q = 0;
    Real k = 2;
    Real M2 = 0;
    std::size_t n = 1;

    for(auto it = std::next(first); it != last; ++it)
    {
        Real tmp = (*it - M) / k;
        Real delta_1 = *it - M;
        Q += k*(k-1)*tmp*tmp;
        M += tmp;
        k += 1;
        Real delta_2 = *it - M;
        M2 += delta_1 * delta_2;
        ++n;
    }

    return std::make_tuple(M, M2, Q/(k-1), Real(n));
}

// https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Higher-order_statistics
template<typename ReturnType, typename ForwardIterator>
ReturnType first_four_moments_sequential_impl(ForwardIterator first, ForwardIterator last)
{
    using Real = typename std::tuple_element<0, ReturnType>::type;
    using Size = typename std::tuple_element<4, ReturnType>::type;

    Real M1 = *first;
    Real M2 = 0;
    Real M3 = 0;
    Real M4 = 0;
    Size n = 2;
    for (auto it = std::next(first); it != last; ++it)
    {
        Real delta21 = *it - M1;
        Real tmp = delta21/n;
        M4 = M4 + tmp*(tmp*tmp*delta21*((n-1)*(n*n-3*n+3)) + 6*tmp*M2 - 4*M3);
        M3 = M3 + tmp*((n-1)*(n-2)*delta21*tmp - 3*M2);
        M2 = M2 + tmp*(n-1)*delta21;
        M1 = M1 + tmp;
        n += 1;
    }

    return std::make_tuple(M1, M2, M3, M4, n-1);
}

#ifdef BOOST_HAS_THREADS

// https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Higher-order_statistics
// EQN 3.1: https://www.osti.gov/servlets/purl/1426900
template<typename ReturnType, typename ForwardIterator>
ReturnType first_four_moments_parallel_impl(ForwardIterator first, ForwardIterator last)
{
    using Real = typename std::tuple_element<0, ReturnType>::type;

    const auto elements = std::distance(first, last);
    const unsigned max_concurrency = std::thread::hardware_concurrency() == 0 ? 2u : std::thread::hardware_concurrency();
    unsigned num_threads = 2u;
    
    // Threading is faster for: 10 + 5.13e-3 N/j <= 5.13e-3N => N >= 10^4j/5.13(j-1).
    const auto parallel_lower_bound = 10e4*max_concurrency/(5.13*(max_concurrency-1));
    const auto parallel_upper_bound = 10e4*2/5.13; // j = 2

    // https://lemire.me/blog/2020/01/30/cost-of-a-thread-in-c-under-linux/
    if(elements < parallel_lower_bound)
    {
        return detail::first_four_moments_sequential_impl<ReturnType>(first, last);
    }
    else if(elements >= parallel_upper_bound)
    {
        num_threads = max_concurrency;
    }
    else
    {
        for(unsigned i = 3; i < max_concurrency; ++i)
        {
            if(parallel_lower_bound < 10e4*i/(5.13*(i-1)))
            {
                num_threads = i;
                break;
            }
        }
    }

    std::vector<std::future<ReturnType>> future_manager;
    const auto elements_per_thread = std::ceil(static_cast<double>(elements) / num_threads);

    auto it = first;
    for(std::size_t i {}; i < num_threads - 1; ++i)
    {
        future_manager.emplace_back(std::async(std::launch::async | std::launch::deferred, [it, elements_per_thread]() -> ReturnType
        {
            return first_four_moments_sequential_impl<ReturnType>(it, std::next(it, elements_per_thread));
        }));
        it = std::next(it, elements_per_thread);
    }

    future_manager.emplace_back(std::async(std::launch::async | std::launch::deferred, [it, last]() -> ReturnType
    {
        return first_four_moments_sequential_impl<ReturnType>(it, last);
    }));

    auto temp = future_manager[0].get();
    Real M1_a = std::get<0>(temp);
    Real M2_a = std::get<1>(temp);
    Real M3_a = std::get<2>(temp);
    Real M4_a = std::get<3>(temp);
    Real range_a = std::get<4>(temp);

    for(std::size_t i = 1; i < future_manager.size(); ++i)
    {
        temp = future_manager[i].get();
        Real M1_b = std::get<0>(temp);
        Real M2_b = std::get<1>(temp);
        Real M3_b = std::get<2>(temp);
        Real M4_b = std::get<3>(temp);
        Real range_b = std::get<4>(temp);

        const Real n_ab = range_a + range_b;
        const Real delta = M1_b - M1_a;
        
        M1_a = (range_a * M1_a + range_b * M1_b) / n_ab;
        M2_a = M2_a + M2_b + delta * delta * (range_a * range_b / n_ab);
        M3_a = M3_a + M3_b + (delta * delta * delta) * range_a * range_b * (range_a - range_b) / (n_ab * n_ab)    
               + Real(3) * delta * (range_a * M2_b - range_b * M2_a) / n_ab;
        M4_a = M4_a + M4_b + (delta * delta * delta * delta) * range_a * range_b * (range_a * range_a - range_a * range_b + range_b * range_b) / (n_ab * n_ab * n_ab)
               + Real(6) * delta * delta * (range_a * range_a * M2_b + range_b * range_b * M2_a) / (n_ab * n_ab) 
               + Real(4) * delta * (range_a * M3_b - range_b * M3_a) / n_ab;
        range_a = n_ab;
    }

    return std::make_tuple(M1_a, M2_a, M3_a, M4_a, elements);
}

#endif // BOOST_HAS_THREADS

// Follows equation 1.5 of:
// https://prod.sandia.gov/techlib-noauth/access-control.cgi/2008/086212.pdf
template<typename ReturnType, typename ForwardIterator>
ReturnType skewness_sequential_impl(ForwardIterator first, ForwardIterator last)
{
    using std::sqrt;
    BOOST_MATH_ASSERT_MSG(first != last, "At least one sample is required to compute skewness.");
    
    ReturnType M1 = *first;
    ReturnType M2 = 0;
    ReturnType M3 = 0;
    ReturnType n = 2;
        
    for (auto it = std::next(first); it != last; ++it)    
    {
        ReturnType delta21 = *it - M1;
        ReturnType tmp = delta21/n;
        M3 += tmp*((n-1)*(n-2)*delta21*tmp - 3*M2);
        M2 += tmp*(n-1)*delta21;
        M1 += tmp;
        n += 1;
    }
   
    ReturnType var = M2/(n-1);
    
    if (var == 0)
    {
        // The limit is technically undefined, but the interpretation here is clear:
        // A constant dataset has no skewness.
        return ReturnType(0);
    }
    
    ReturnType skew = M3/(M2*sqrt(var));
    return skew;
}

template<typename ReturnType, typename ForwardIterator>
ReturnType gini_coefficient_sequential_impl(ForwardIterator first, ForwardIterator last)
{
    ReturnType i = 1;
    ReturnType num = 0;
    ReturnType denom = 0;

    for(auto it = first; it != last; ++it)
    {
        num += *it*i;
        denom += *it;
        ++i;
    }

    // If the l1 norm is zero, all elements are zero, so every element is the same.
    if(denom == 0)
    {
        return ReturnType(0);
    }
    else
    {
        return ((2*num)/denom - i)/(i-1);
    }
}

template<typename ReturnType, typename ForwardIterator>
ReturnType gini_range_fraction(ForwardIterator first, ForwardIterator last, std::size_t starting_index)
{
    using Real = typename std::tuple_element<0, ReturnType>::type;

    std::size_t i = starting_index + 1;
    Real num = 0;
    Real denom = 0;

    for(auto it = first; it != last; ++it)
    {
        num += *it*i;
        denom += *it;
        ++i;
    }

    return std::make_tuple(num, denom, i);
}

#ifdef BOOST_HAS_THREADS

template<typename ReturnType, typename ExecutionPolicy, typename ForwardIterator>
ReturnType gini_coefficient_parallel_impl(ExecutionPolicy&&, ForwardIterator first, ForwardIterator last)
{
    using range_tuple = std::tuple<ReturnType, ReturnType, std::size_t>;
    
    const auto elements = std::distance(first, last);
    const unsigned max_concurrency = std::thread::hardware_concurrency() == 0 ? 2u : std::thread::hardware_concurrency();
    unsigned num_threads = 2u;
    
    // Threading is faster for: 10 + 10.12e-3 N/j <= 10.12e-3N => N >= 10^4j/10.12(j-1).
    const auto parallel_lower_bound = 10e4*max_concurrency/(10.12*(max_concurrency-1));
    const auto parallel_upper_bound = 10e4*2/10.12; // j = 2

    // https://lemire.me/blog/2020/01/30/cost-of-a-thread-in-c-under-linux/
    if(elements < parallel_lower_bound)
    {
        return gini_coefficient_sequential_impl<ReturnType>(first, last);
    }
    else if(elements >= parallel_upper_bound)
    {
        num_threads = max_concurrency;
    }
    else
    {
        for(unsigned i = 3; i < max_concurrency; ++i)
        {
            if(parallel_lower_bound < 10e4*i/(10.12*(i-1)))
            {
                num_threads = i;
                break;
            }
        }
    }

    std::vector<std::future<range_tuple>> future_manager;
    const auto elements_per_thread = std::ceil(static_cast<double>(elements) / num_threads);

    auto it = first;
    for(std::size_t i {}; i < num_threads - 1; ++i)
    {
        future_manager.emplace_back(std::async(std::launch::async | std::launch::deferred, [it, elements_per_thread, i]() -> range_tuple
        {
            return gini_range_fraction<range_tuple>(it, std::next(it, elements_per_thread), i*elements_per_thread);
        }));
        it = std::next(it, elements_per_thread);
    }

    future_manager.emplace_back(std::async(std::launch::async | std::launch::deferred, [it, last, num_threads, elements_per_thread]() -> range_tuple
    {
        return gini_range_fraction<range_tuple>(it, last, (num_threads - 1)*elements_per_thread);
    }));

    ReturnType num = 0;
    ReturnType denom = 0;

    for(std::size_t i = 0; i < future_manager.size(); ++i)
    {
        auto temp = future_manager[i].get();
        num += std::get<0>(temp);
        denom += std::get<1>(temp);
    }

    // If the l1 norm is zero, all elements are zero, so every element is the same.
    if(denom == 0)
    {
        return ReturnType(0);
    }
    else
    {
        return ((2*num)/denom - elements)/(elements-1);
    }
}

#endif // BOOST_HAS_THREADS

template<typename ForwardIterator, typename OutputIterator>
OutputIterator mode_impl(ForwardIterator first, ForwardIterator last, OutputIterator output)
{
    using Z = typename std::iterator_traits<ForwardIterator>::value_type;
    using Size = typename std::iterator_traits<ForwardIterator>::difference_type;

    std::vector<Z> modes {};
    modes.reserve(16);
    Size max_counter {0};

    while(first != last)
    {
        Size current_count {0};
        ForwardIterator end_it {first};
        while(end_it != last && *end_it == *first)
        {
            ++current_count;
            ++end_it;
        }

        if(current_count > max_counter)
        {
            modes.resize(1);
            modes[0] = *first;
            max_counter = current_count;
        }

        else if(current_count == max_counter)
        {
            modes.emplace_back(*first);
        }

        first = end_it;
    }

    return std::move(modes.begin(), modes.end(), output);
}
}}}}

#endif // BOOST_MATH_STATISTICS_UNIVARIATE_STATISTICS_DETAIL_SINGLE_PASS_HPP

/* single_pass.hpp
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
*/