//  (C) Copyright Nick Thompson 2018.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_UNIVARIATE_STATISTICS_HPP
#define BOOST_MATH_TOOLS_UNIVARIATE_STATISTICS_HPP

#include <algorithm>
#include <iterator>
#include <tuple>
#include <boost/assert.hpp>
#include <boost/config/header_deprecated.hpp>

BOOST_HEADER_DEPRECATED("<boost/math/statistics/univariate_statistics.hpp>");

namespace boost::math::tools {

template<class ForwardIterator>
auto mean(ForwardIterator first, ForwardIterator last)
{
    using Real = typename std::iterator_traits<ForwardIterator>::value_type;
    BOOST_ASSERT_MSG(first != last, "At least one sample is required to compute the mean.");
    if constexpr (std::is_integral<Real>::value)
    {
        double mu = 0;
        double i = 1;
        for(auto it = first; it != last; ++it) {
            mu = mu + (*it - mu)/i;
            i += 1;
        }
        return mu;
    }
    else if constexpr (std::is_same_v<typename std::iterator_traits<ForwardIterator>::iterator_category, std::random_access_iterator_tag>)
    {
        size_t elements = std::distance(first, last);
        Real mu0 = 0;
        Real mu1 = 0;
        Real mu2 = 0;
        Real mu3 = 0;
        Real i = 1;
        auto end = last - (elements % 4);
        for(auto it = first; it != end;  it += 4) {
            Real inv = Real(1)/i;
            Real tmp0 = (*it - mu0);
            Real tmp1 = (*(it+1) - mu1);
            Real tmp2 = (*(it+2) - mu2);
            Real tmp3 = (*(it+3) - mu3);
            // please generate a vectorized fma here
            mu0 += tmp0*inv;
            mu1 += tmp1*inv;
            mu2 += tmp2*inv;
            mu3 += tmp3*inv;
            i += 1;
        }
        Real num1 = Real(elements  - (elements %4))/Real(4);
        Real num2 = num1 + Real(elements % 4);

        for (auto it = end; it != last; ++it)
        {
            mu3 += (*it-mu3)/i;
            i += 1;
        }

        return (num1*(mu0+mu1+mu2) + num2*mu3)/Real(elements);
    }
    else
    {
        auto it = first;
        Real mu = *it;
        Real i = 2;
        while(++it != last)
        {
            mu += (*it - mu)/i;
            i += 1;
        }
        return mu;
    }
}

template<class Container>
inline auto mean(Container const & v)
{
    return mean(v.cbegin(), v.cend());
}

template<class ForwardIterator>
auto variance(ForwardIterator first, ForwardIterator last)
{
    using Real = typename std::iterator_traits<ForwardIterator>::value_type;
    BOOST_ASSERT_MSG(first != last, "At least one sample is required to compute mean and variance.");
    // Higham, Accuracy and Stability, equation 1.6a and 1.6b:
    if constexpr (std::is_integral<Real>::value)
    {
        double M = *first;
        double Q = 0;
        double k = 2;
        for (auto it = std::next(first); it != last; ++it)
        {
            double tmp = *it - M;
            Q = Q + ((k-1)*tmp*tmp)/k;
            M = M + tmp/k;
            k += 1;
        }
        return Q/(k-1);
    }
    else
    {
        Real M = *first;
        Real Q = 0;
        Real k = 2;
        for (auto it = std::next(first); it != last; ++it)
        {
            Real tmp = (*it - M)/k;
            Q += k*(k-1)*tmp*tmp;
            M += tmp;
            k += 1;
        }
        return Q/(k-1);
    }
}

template<class Container>
inline auto variance(Container const & v)
{
    return variance(v.cbegin(), v.cend());
}

template<class ForwardIterator>
auto sample_variance(ForwardIterator first, ForwardIterator last)
{
    size_t n = std::distance(first, last);
    BOOST_ASSERT_MSG(n > 1, "At least two samples are required to compute the sample variance.");
    return n*variance(first, last)/(n-1);
}

template<class Container>
inline auto sample_variance(Container const & v)
{
    return sample_variance(v.cbegin(), v.cend());
}


// Follows equation 1.5 of:
// https://prod.sandia.gov/techlib-noauth/access-control.cgi/2008/086212.pdf
template<class ForwardIterator>
auto skewness(ForwardIterator first, ForwardIterator last)
{
    using Real = typename std::iterator_traits<ForwardIterator>::value_type;
    BOOST_ASSERT_MSG(first != last, "At least one sample is required to compute skewness.");
    if constexpr (std::is_integral<Real>::value)
    {
        double M1 = *first;
        double M2 = 0;
        double M3 = 0;
        double n = 2;
        for (auto it = std::next(first); it != last; ++it)
        {
            double delta21 = *it - M1;
            double tmp = delta21/n;
            M3 = M3 + tmp*((n-1)*(n-2)*delta21*tmp - 3*M2);
            M2 = M2 + tmp*(n-1)*delta21;
            M1 = M1 + tmp;
            n += 1;
        }

        double var = M2/(n-1);
        if (var == 0)
        {
            // The limit is technically undefined, but the interpretation here is clear:
            // A constant dataset has no skewness.
            return double(0);
        }
        double skew = M3/(M2*sqrt(var));
        return skew;
    }
    else
    {
        Real M1 = *first;
        Real M2 = 0;
        Real M3 = 0;
        Real n = 2;
        for (auto it = std::next(first); it != last; ++it)
        {
            Real delta21 = *it - M1;
            Real tmp = delta21/n;
            M3 += tmp*((n-1)*(n-2)*delta21*tmp - 3*M2);
            M2 += tmp*(n-1)*delta21;
            M1 += tmp;
            n += 1;
        }

        Real var = M2/(n-1);
        if (var == 0)
        {
            // The limit is technically undefined, but the interpretation here is clear:
            // A constant dataset has no skewness.
            return Real(0);
        }
        Real skew = M3/(M2*sqrt(var));
        return skew;
    }
}

template<class Container>
inline auto skewness(Container const & v)
{
    return skewness(v.cbegin(), v.cend());
}

// Follows equation 1.5/1.6 of:
// https://prod.sandia.gov/techlib-noauth/access-control.cgi/2008/086212.pdf
template<class ForwardIterator>
auto first_four_moments(ForwardIterator first, ForwardIterator last)
{
    using Real = typename std::iterator_traits<ForwardIterator>::value_type;
    BOOST_ASSERT_MSG(first != last, "At least one sample is required to compute the first four moments.");
    if constexpr (std::is_integral<Real>::value)
    {
        double M1 = *first;
        double M2 = 0;
        double M3 = 0;
        double M4 = 0;
        double n = 2;
        for (auto it = std::next(first); it != last; ++it)
        {
            double delta21 = *it - M1;
            double tmp = delta21/n;
            M4 = M4 + tmp*(tmp*tmp*delta21*((n-1)*(n*n-3*n+3)) + 6*tmp*M2 - 4*M3);
            M3 = M3 + tmp*((n-1)*(n-2)*delta21*tmp - 3*M2);
            M2 = M2 + tmp*(n-1)*delta21;
            M1 = M1 + tmp;
            n += 1;
        }

        return std::make_tuple(M1, M2/(n-1), M3/(n-1), M4/(n-1));
    }
    else
    {
        Real M1 = *first;
        Real M2 = 0;
        Real M3 = 0;
        Real M4 = 0;
        Real n = 2;
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

        return std::make_tuple(M1, M2/(n-1), M3/(n-1), M4/(n-1));
    }
}

template<class Container>
inline auto first_four_moments(Container const & v)
{
    return first_four_moments(v.cbegin(), v.cend());
}


// Follows equation 1.6 of:
// https://prod.sandia.gov/techlib-noauth/access-control.cgi/2008/086212.pdf
template<class ForwardIterator>
auto kurtosis(ForwardIterator first, ForwardIterator last)
{
    auto [M1, M2, M3, M4] = first_four_moments(first, last);
    if (M2 == 0)
    {
        return M2;
    }
    return M4/(M2*M2);
}

template<class Container>
inline auto kurtosis(Container const & v)
{
    return kurtosis(v.cbegin(), v.cend());
}

template<class ForwardIterator>
auto excess_kurtosis(ForwardIterator first, ForwardIterator last)
{
    return kurtosis(first, last) - 3;
}

template<class Container>
inline auto excess_kurtosis(Container const & v)
{
    return excess_kurtosis(v.cbegin(), v.cend());
}


template<class RandomAccessIterator>
auto median(RandomAccessIterator first, RandomAccessIterator last)
{
    size_t num_elems = std::distance(first, last);
    BOOST_ASSERT_MSG(num_elems > 0, "The median of a zero length vector is undefined.");
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


template<class RandomAccessContainer>
inline auto median(RandomAccessContainer & v)
{
    return median(v.begin(), v.end());
}

template<class RandomAccessIterator>
auto gini_coefficient(RandomAccessIterator first, RandomAccessIterator last)
{
    using Real = typename std::iterator_traits<RandomAccessIterator>::value_type;
    BOOST_ASSERT_MSG(first != last && std::next(first) != last, "Computation of the Gini coefficient requires at least two samples.");

    std::sort(first, last);
    if constexpr (std::is_integral<Real>::value)
    {
        double i = 1;
        double num = 0;
        double denom = 0;
        for (auto it = first; it != last; ++it)
        {
            num += *it*i;
            denom += *it;
            ++i;
        }

        // If the l1 norm is zero, all elements are zero, so every element is the same.
        if (denom == 0)
        {
            return double(0);
        }

        return ((2*num)/denom - i)/(i-1);
    }
    else
    {
        Real i = 1;
        Real num = 0;
        Real denom = 0;
        for (auto it = first; it != last; ++it)
        {
            num += *it*i;
            denom += *it;
            ++i;
        }

        // If the l1 norm is zero, all elements are zero, so every element is the same.
        if (denom == 0)
        {
            return Real(0);
        }

        return ((2*num)/denom - i)/(i-1);
    }
}

template<class RandomAccessContainer>
inline auto gini_coefficient(RandomAccessContainer & v)
{
    return gini_coefficient(v.begin(), v.end());
}

template<class RandomAccessIterator>
inline auto sample_gini_coefficient(RandomAccessIterator first, RandomAccessIterator last)
{
    size_t n = std::distance(first, last);
    return n*gini_coefficient(first, last)/(n-1);
}

template<class RandomAccessContainer>
inline auto sample_gini_coefficient(RandomAccessContainer & v)
{
    return sample_gini_coefficient(v.begin(), v.end());
}

template<class RandomAccessIterator>
auto median_absolute_deviation(RandomAccessIterator first, RandomAccessIterator last, typename std::iterator_traits<RandomAccessIterator>::value_type center=std::numeric_limits<typename std::iterator_traits<RandomAccessIterator>::value_type>::quiet_NaN())
{
    using std::abs;
    using Real = typename std::iterator_traits<RandomAccessIterator>::value_type;
    using std::isnan;
    if (isnan(center))
    {
        center = boost::math::tools::median(first, last);
    }
    size_t num_elems = std::distance(first, last);
    BOOST_ASSERT_MSG(num_elems > 0, "The median of a zero-length vector is undefined.");
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

template<class RandomAccessContainer>
inline auto median_absolute_deviation(RandomAccessContainer & v, typename RandomAccessContainer::value_type center=std::numeric_limits<typename RandomAccessContainer::value_type>::quiet_NaN())
{
    return median_absolute_deviation(v.begin(), v.end(), center);
}

}
#endif

/* univariate_statistics.hpp
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
*/