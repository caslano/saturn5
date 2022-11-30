//  (C) Copyright Nick Thompson 2018.
//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_STATISTICS_BIVARIATE_STATISTICS_HPP
#define BOOST_MATH_STATISTICS_BIVARIATE_STATISTICS_HPP

#include <iterator>
#include <tuple>
#include <type_traits>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <boost/math/tools/assert.hpp>
#include <boost/math/tools/config.hpp>

// Support compilers with P0024R2 implemented without linking TBB
// https://en.cppreference.com/w/cpp/compiler_support
#if !defined(BOOST_NO_CXX17_HDR_EXECUTION) && defined(BOOST_HAS_THREADS)
#include <execution>
#include <future>
#include <thread>
#define EXEC_COMPATIBLE
#endif

namespace boost{ namespace math{ namespace statistics { namespace detail {

// See Equation III.9 of "Numerically Stable, Single-Pass, Parallel Statistics Algorithms", Bennet et al.
template<typename ReturnType, typename ForwardIterator>
ReturnType means_and_covariance_seq_impl(ForwardIterator u_begin, ForwardIterator u_end, ForwardIterator v_begin, ForwardIterator v_end)
{
    using Real = typename std::tuple_element<0, ReturnType>::type;

    Real cov = 0;
    ForwardIterator u_it = u_begin;
    ForwardIterator v_it = v_begin;
    Real mu_u = *u_it++;
    Real mu_v = *v_it++;
    std::size_t i = 1;

    while(u_it != u_end && v_it != v_end)
    {
        Real u_temp = (*u_it++ - mu_u)/(i+1);
        Real v_temp = *v_it++ - mu_v;
        cov += i*u_temp*v_temp;
        mu_u = mu_u + u_temp;
        mu_v = mu_v + v_temp/(i+1);
        i = i + 1;
    }

    if(u_it != u_end || v_it != v_end)
    {
        throw std::domain_error("The size of each sample set must be the same to compute covariance");
    }

    return std::make_tuple(mu_u, mu_v, cov/i, Real(i));
}

#ifdef EXEC_COMPATIBLE

// Numerically stable parallel computation of (co-)variance
// https://dl.acm.org/doi/10.1145/3221269.3223036
template<typename ReturnType, typename ForwardIterator>
ReturnType means_and_covariance_parallel_impl(ForwardIterator u_begin, ForwardIterator u_end, ForwardIterator v_begin, ForwardIterator v_end)
{
    using Real = typename std::tuple_element<0, ReturnType>::type;

    const auto u_elements = std::distance(u_begin, u_end);
    const auto v_elements = std::distance(v_begin, v_end);

    if(u_elements != v_elements)
    {
        throw std::domain_error("The size of each sample set must be the same to compute covariance");
    }

    const unsigned max_concurrency = std::thread::hardware_concurrency() == 0 ? 2u : std::thread::hardware_concurrency();
    unsigned num_threads = 2u;
    
    // 5.16 comes from benchmarking. See boost/math/reporting/performance/bivariate_statistics_performance.cpp
    // Threading is faster for: 10 + 5.16e-3 N/j <= 5.16e-3N => N >= 10^4j/5.16(j-1).
    const auto parallel_lower_bound = 10e4*max_concurrency/(5.16*(max_concurrency-1));
    const auto parallel_upper_bound = 10e4*2/5.16; // j = 2

    // https://lemire.me/blog/2020/01/30/cost-of-a-thread-in-c-under-linux/
    if(u_elements < parallel_lower_bound)
    {
        return means_and_covariance_seq_impl<ReturnType>(u_begin, u_end, v_begin, v_end);
    }
    else if(u_elements >= parallel_upper_bound)
    {
        num_threads = max_concurrency;
    }
    else
    {
        for(unsigned i = 3; i < max_concurrency; ++i)
        {
            if(parallel_lower_bound < 10e4*i/(5.16*(i-1)))
            {
                num_threads = i;
                break;
            }
        }
    }

    std::vector<std::future<ReturnType>> future_manager;
    const auto elements_per_thread = std::ceil(static_cast<double>(u_elements)/num_threads);

    ForwardIterator u_it = u_begin;
    ForwardIterator v_it = v_begin;

    for(std::size_t i = 0; i < num_threads - 1; ++i)
    {
        future_manager.emplace_back(std::async(std::launch::async | std::launch::deferred, [u_it, v_it, elements_per_thread]() -> ReturnType
        {
            return means_and_covariance_seq_impl<ReturnType>(u_it, std::next(u_it, elements_per_thread), v_it, std::next(v_it, elements_per_thread));
        }));
        u_it = std::next(u_it, elements_per_thread);
        v_it = std::next(v_it, elements_per_thread);
    }

    future_manager.emplace_back(std::async(std::launch::async | std::launch::deferred, [u_it, u_end, v_it, v_end]() -> ReturnType
    {
        return means_and_covariance_seq_impl<ReturnType>(u_it, u_end, v_it, v_end);
    }));

    ReturnType temp = future_manager[0].get();
    Real mu_u_a = std::get<0>(temp);
    Real mu_v_a = std::get<1>(temp);
    Real cov_a = std::get<2>(temp);
    Real n_a = std::get<3>(temp);

    for(std::size_t i = 1; i < future_manager.size(); ++i)
    {
        temp = future_manager[i].get();
        Real mu_u_b = std::get<0>(temp);
        Real mu_v_b = std::get<1>(temp);
        Real cov_b = std::get<2>(temp);
        Real n_b = std::get<3>(temp);

        const Real n_ab = n_a + n_b;
        const Real delta_u = mu_u_b - mu_u_a;
        const Real delta_v = mu_v_b - mu_v_a;

        cov_a = cov_a + cov_b + (-delta_u)*(-delta_v)*((n_a*n_b)/n_ab);
        mu_u_a = mu_u_a + delta_u*(n_b/n_ab);
        mu_v_a = mu_v_a + delta_v*(n_b/n_ab);
        n_a = n_ab;
    }

    return std::make_tuple(mu_u_a, mu_v_a, cov_a, n_a);
}

#endif // EXEC_COMPATIBLE

template<typename ReturnType, typename ForwardIterator>
ReturnType correlation_coefficient_seq_impl(ForwardIterator u_begin, ForwardIterator u_end, ForwardIterator v_begin, ForwardIterator v_end)
{
    using Real = typename std::tuple_element<0, ReturnType>::type;
    using std::sqrt;

    Real cov = 0;
    ForwardIterator u_it = u_begin;
    ForwardIterator v_it = v_begin;
    Real mu_u = *u_it++;
    Real mu_v = *v_it++;
    Real Qu = 0;
    Real Qv = 0;
    std::size_t i = 1;

    while(u_it != u_end && v_it != v_end)
    {
        Real u_tmp = *u_it++ - mu_u;
        Real v_tmp = *v_it++ - mu_v;
        Qu = Qu + (i*u_tmp*u_tmp)/(i+1);
        Qv = Qv + (i*v_tmp*v_tmp)/(i+1);
        cov += i*u_tmp*v_tmp/(i+1);
        mu_u = mu_u + u_tmp/(i+1);
        mu_v = mu_v + v_tmp/(i+1);
        ++i;
    }


    // If one dataset is constant, then the correlation coefficient is undefined.
    // See https://stats.stackexchange.com/questions/23676/normalized-correlation-with-a-constant-vector
    // Thanks to zbjornson for pointing this out.
    if (Qu == 0 || Qv == 0)
    {
        return std::make_tuple(mu_u, Qu, mu_v, Qv, cov, std::numeric_limits<Real>::quiet_NaN(), Real(i));
    }

    // Make sure rho in [-1, 1], even in the presence of numerical noise.
    Real rho = cov/sqrt(Qu*Qv);
    if (rho > 1) {
        rho = 1;
    }
    if (rho < -1) {
        rho = -1;
    }

    return std::make_tuple(mu_u, Qu, mu_v, Qv, cov, rho, Real(i));
}

#ifdef EXEC_COMPATIBLE

// Numerically stable parallel computation of (co-)variance:
// https://dl.acm.org/doi/10.1145/3221269.3223036
//
// Parallel computation of variance:
// http://i.stanford.edu/pub/cstr/reports/cs/tr/79/773/CS-TR-79-773.pdf
template<typename ReturnType, typename ForwardIterator>
ReturnType correlation_coefficient_parallel_impl(ForwardIterator u_begin, ForwardIterator u_end, ForwardIterator v_begin, ForwardIterator v_end)
{
    using Real = typename std::tuple_element<0, ReturnType>::type;

    const auto u_elements = std::distance(u_begin, u_end);
    const auto v_elements = std::distance(v_begin, v_end);

    if(u_elements != v_elements)
    {
        throw std::domain_error("The size of each sample set must be the same to compute covariance");
    }

    const unsigned max_concurrency = std::thread::hardware_concurrency() == 0 ? 2u : std::thread::hardware_concurrency();
    unsigned num_threads = 2u;
    
    // 3.25 comes from benchmarking. See boost/math/reporting/performance/bivariate_statistics_performance.cpp
    // Threading is faster for: 10 + 3.25e-3 N/j <= 3.25e-3N => N >= 10^4j/3.25(j-1).
    const auto parallel_lower_bound = 10e4*max_concurrency/(3.25*(max_concurrency-1));
    const auto parallel_upper_bound = 10e4*2/3.25; // j = 2

    // https://lemire.me/blog/2020/01/30/cost-of-a-thread-in-c-under-linux/
    if(u_elements < parallel_lower_bound)
    {
        return correlation_coefficient_seq_impl<ReturnType>(u_begin, u_end, v_begin, v_end);
    }
    else if(u_elements >= parallel_upper_bound)
    {
        num_threads = max_concurrency;
    }
    else
    {
        for(unsigned i = 3; i < max_concurrency; ++i)
        {
            if(parallel_lower_bound < 10e4*i/(3.25*(i-1)))
            {
                num_threads = i;
                break;
            }
        }
    }

    std::vector<std::future<ReturnType>> future_manager;
    const auto elements_per_thread = std::ceil(static_cast<double>(u_elements)/num_threads);

    ForwardIterator u_it = u_begin;
    ForwardIterator v_it = v_begin;

    for(std::size_t i = 0; i < num_threads - 1; ++i)
    {
        future_manager.emplace_back(std::async(std::launch::async | std::launch::deferred, [u_it, v_it, elements_per_thread]() -> ReturnType
        {
            return correlation_coefficient_seq_impl<ReturnType>(u_it, std::next(u_it, elements_per_thread), v_it, std::next(v_it, elements_per_thread));
        }));
        u_it = std::next(u_it, elements_per_thread);
        v_it = std::next(v_it, elements_per_thread);
    }

    future_manager.emplace_back(std::async(std::launch::async | std::launch::deferred, [u_it, u_end, v_it, v_end]() -> ReturnType
    {
        return correlation_coefficient_seq_impl<ReturnType>(u_it, u_end, v_it, v_end);
    }));

    ReturnType temp = future_manager[0].get();
    Real mu_u_a = std::get<0>(temp);
    Real Qu_a = std::get<1>(temp);
    Real mu_v_a = std::get<2>(temp);
    Real Qv_a = std::get<3>(temp);
    Real cov_a = std::get<4>(temp);
    Real n_a = std::get<6>(temp);

    for(std::size_t i = 1; i < future_manager.size(); ++i)
    {
        temp = future_manager[i].get();
        Real mu_u_b = std::get<0>(temp);
        Real Qu_b = std::get<1>(temp);
        Real mu_v_b = std::get<2>(temp);
        Real Qv_b = std::get<3>(temp);
        Real cov_b = std::get<4>(temp);
        Real n_b = std::get<6>(temp);

        const Real n_ab = n_a + n_b;
        const Real delta_u = mu_u_b - mu_u_a;
        const Real delta_v = mu_v_b - mu_v_a;

        cov_a = cov_a + cov_b + (-delta_u)*(-delta_v)*((n_a*n_b)/n_ab);
        mu_u_a = mu_u_a + delta_u*(n_b/n_ab);
        mu_v_a = mu_v_a + delta_v*(n_b/n_ab);
        Qu_a = Qu_a + Qu_b + delta_u*delta_u*((n_a*n_b)/n_ab);
        Qv_b = Qv_a + Qv_b + delta_v*delta_v*((n_a*n_b)/n_ab);
        n_a = n_ab;
    }

    // If one dataset is constant, then the correlation coefficient is undefined.
    // See https://stats.stackexchange.com/questions/23676/normalized-correlation-with-a-constant-vector
    // Thanks to zbjornson for pointing this out.
    if (Qu_a == 0 || Qv_a == 0)
    {
        return std::make_tuple(mu_u_a, Qu_a, mu_v_a, Qv_a, cov_a, std::numeric_limits<Real>::quiet_NaN(), n_a);
    }

    // Make sure rho in [-1, 1], even in the presence of numerical noise.
    Real rho = cov_a/sqrt(Qu_a*Qv_a);
    if (rho > 1) {
        rho = 1;
    }
    if (rho < -1) {
        rho = -1;
    }

    return std::make_tuple(mu_u_a, Qu_a, mu_v_a, Qv_a, cov_a, rho, n_a);
}

#endif // EXEC_COMPATIBLE

} // namespace detail

#ifdef EXEC_COMPATIBLE

template<typename ExecutionPolicy, typename Container, typename Real = typename Container::value_type>
inline auto means_and_covariance(ExecutionPolicy&& exec, Container const & u, Container const & v)
{
    if constexpr (std::is_same_v<std::remove_reference_t<decltype(exec)>, decltype(std::execution::seq)>)
    {
        if constexpr (std::is_integral_v<Real>)
        {
            using ReturnType = std::tuple<double, double, double, double>;
            ReturnType temp = detail::means_and_covariance_seq_impl<ReturnType>(std::begin(u), std::end(u), std::begin(v), std::end(v));
            return std::make_tuple(std::get<0>(temp), std::get<1>(temp), std::get<2>(temp));
        }
        else
        {
            using ReturnType = std::tuple<Real, Real, Real, Real>;
            ReturnType temp = detail::means_and_covariance_seq_impl<ReturnType>(std::begin(u), std::end(u), std::begin(v), std::end(v));
            return std::make_tuple(std::get<0>(temp), std::get<1>(temp), std::get<2>(temp));
        }
    }
    else
    {
        if constexpr (std::is_integral_v<Real>)
        {
            using ReturnType = std::tuple<double, double, double, double>;
            ReturnType temp = detail::means_and_covariance_parallel_impl<ReturnType>(std::begin(u), std::end(u), std::begin(v), std::end(v));
            return std::make_tuple(std::get<0>(temp), std::get<1>(temp), std::get<2>(temp));
        }
        else
        {
            using ReturnType = std::tuple<Real, Real, Real, Real>;
            ReturnType temp = detail::means_and_covariance_parallel_impl<ReturnType>(std::begin(u), std::end(u), std::begin(v), std::end(v));
            return std::make_tuple(std::get<0>(temp), std::get<1>(temp), std::get<2>(temp));
        }
    }
}

template<typename Container>
inline auto means_and_covariance(Container const & u, Container const & v)
{
    return means_and_covariance(std::execution::seq, u, v);
}

template<typename ExecutionPolicy, typename Container>
inline auto covariance(ExecutionPolicy&& exec, Container const & u, Container const & v)
{
    return std::get<2>(means_and_covariance(exec, u, v));
}

template<typename Container>
inline auto covariance(Container const & u, Container const & v)
{
    return covariance(std::execution::seq, u, v);
}

template<typename ExecutionPolicy, typename Container, typename Real = typename Container::value_type>
inline auto correlation_coefficient(ExecutionPolicy&& exec, Container const & u, Container const & v)
{
    if constexpr (std::is_same_v<std::remove_reference_t<decltype(exec)>, decltype(std::execution::seq)>)
    {
        if constexpr (std::is_integral_v<Real>)
        {
            using ReturnType = std::tuple<double, double, double, double, double, double, double>;
            return std::get<5>(detail::correlation_coefficient_seq_impl<ReturnType>(std::begin(u), std::end(u), std::begin(v), std::end(v)));
        }
        else
        {
            using ReturnType = std::tuple<Real, Real, Real, Real, Real, Real, Real>;
            return std::get<5>(detail::correlation_coefficient_seq_impl<ReturnType>(std::begin(u), std::end(u), std::begin(v), std::end(v)));
        }
    }
    else
    {
        if constexpr (std::is_integral_v<Real>)
        {
            using ReturnType = std::tuple<double, double, double, double, double, double, double>;
            return std::get<5>(detail::correlation_coefficient_parallel_impl<ReturnType>(std::begin(u), std::end(u), std::begin(v), std::end(v)));
        }
        else
        {
            using ReturnType = std::tuple<Real, Real, Real, Real, Real, Real, Real>;
            return std::get<5>(detail::correlation_coefficient_parallel_impl<ReturnType>(std::begin(u), std::end(u), std::begin(v), std::end(v)));
        }
    }
}

template<typename Container, typename Real = typename Container::value_type>
inline auto correlation_coefficient(Container const & u, Container const & v)
{
    return correlation_coefficient(std::execution::seq, u, v);
}

#else // C++11 and single threaded bindings

template<typename Container, typename Real = typename Container::value_type, typename std::enable_if<std::is_integral<Real>::value, bool>::type = true>
inline auto means_and_covariance(Container const & u, Container const & v) -> std::tuple<double, double, double>
{
    using ReturnType = std::tuple<double, double, double, double>;
    ReturnType temp = detail::means_and_covariance_seq_impl<ReturnType>(std::begin(u), std::end(u), std::begin(v), std::end(v));
    return std::make_tuple(std::get<0>(temp), std::get<1>(temp), std::get<2>(temp));
}

template<typename Container, typename Real = typename Container::value_type, typename std::enable_if<!std::is_integral<Real>::value, bool>::type = true>
inline auto means_and_covariance(Container const & u, Container const & v) -> std::tuple<Real, Real, Real>
{
    using ReturnType = std::tuple<Real, Real, Real, Real>;
    ReturnType temp = detail::means_and_covariance_seq_impl<ReturnType>(std::begin(u), std::end(u), std::begin(v), std::end(v));
    return std::make_tuple(std::get<0>(temp), std::get<1>(temp), std::get<2>(temp));
}

template<typename Container, typename Real = typename Container::value_type, typename std::enable_if<std::is_integral<Real>::value, bool>::type = true>
inline double covariance(Container const & u, Container const & v)
{
    using ReturnType = std::tuple<double, double, double, double>;
    return std::get<2>(detail::means_and_covariance_seq_impl<ReturnType>(std::begin(u), std::end(u), std::begin(v), std::end(v)));
}

template<typename Container, typename Real = typename Container::value_type, typename std::enable_if<!std::is_integral<Real>::value, bool>::type = true>
inline Real covariance(Container const & u, Container const & v)
{
    using ReturnType = std::tuple<Real, Real, Real, Real>;
    return std::get<2>(detail::means_and_covariance_seq_impl<ReturnType>(std::begin(u), std::end(u), std::begin(v), std::end(v)));
}

template<typename Container, typename Real = typename Container::value_type, typename std::enable_if<std::is_integral<Real>::value, bool>::type = true>
inline double correlation_coefficient(Container const & u, Container const & v)
{
    using ReturnType = std::tuple<double, double, double, double, double, double, double>;
    return std::get<5>(detail::correlation_coefficient_seq_impl<ReturnType>(std::begin(u), std::end(u), std::begin(v), std::end(v)));
}

template<typename Container, typename Real = typename Container::value_type, typename std::enable_if<!std::is_integral<Real>::value, bool>::type = true>
inline Real correlation_coefficient(Container const & u, Container const & v)
{
    using ReturnType = std::tuple<Real, Real, Real, Real, Real, Real, Real>;
    return std::get<5>(detail::correlation_coefficient_seq_impl<ReturnType>(std::begin(u), std::end(u), std::begin(v), std::end(v)));
}

#endif

}}} // namespace boost::math::statistics

#endif

/* bivariate_statistics.hpp
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
*/