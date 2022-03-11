//  (C) Copyright Nick Thompson 2018.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_STATISTICS_UNIVARIATE_STATISTICS_HPP
#define BOOST_MATH_STATISTICS_UNIVARIATE_STATISTICS_HPP

#include <algorithm>
#include <iterator>
#include <tuple>
#include <cmath>
#include <boost/assert.hpp>

namespace boost::math::statistics {

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

template<class ForwardIterator>
auto mean_and_sample_variance(ForwardIterator first, ForwardIterator last)
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
        return std::pair<double, double>{M, Q/(k-2)};
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
        return std::pair<Real, Real>{M, Q/(k-2)};
    }
}

template<class Container>
auto mean_and_sample_variance(Container const & v)
{
    return mean_and_sample_variance(v.begin(), v.end());
}

// Follows equation 1.5 of:
// https://prod.sandia.gov/techlib-noauth/access-control.cgi/2008/086212.pdf
template<class ForwardIterator>
auto skewness(ForwardIterator first, ForwardIterator last)
{
    using Real = typename std::iterator_traits<ForwardIterator>::value_type;
    using std::sqrt;
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
        center = boost::math::statistics::median(first, last);
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

template<class ForwardIterator>
auto interquartile_range(ForwardIterator first, ForwardIterator last)
{
    using Real = typename std::iterator_traits<ForwardIterator>::value_type;
    static_assert(!std::is_integral<Real>::value, "Integer values have not yet been implemented.");
    auto m = std::distance(first,last);
    BOOST_ASSERT_MSG(m >= 3, "At least 3 samples are required to compute the interquartile range.");
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
    } else {
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

template<class RandomAccessContainer>
inline auto interquartile_range(RandomAccessContainer & v)
{
    return interquartile_range(v.begin(), v.end());
}


}
#endif

/* univariate_statistics.hpp
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
*/