//  (C) Copyright Nick Thompson 2018.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_UNIVARIATE_STATISTICS_HPP
#define BOOST_MATH_TOOLS_UNIVARIATE_STATISTICS_HPP

#include <algorithm>
#include <iterator>
#include <tuple>
#include <boost/math/tools/assert.hpp>
#include <boost/math/tools/header_deprecated.hpp>

BOOST_MATH_HEADER_DEPRECATED("<boost/math/statistics/univariate_statistics.hpp>");

namespace boost::math::tools {

template<class ForwardIterator>
auto mean(ForwardIterator first, ForwardIterator last)
{
    using Real = typename std::iterator_traits<ForwardIterator>::value_type;
    BOOST_MATH_ASSERT_MSG(first != last, "At least one sample is required to compute the mean.");
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
    BOOST_MATH_ASSERT_MSG(first != last, "At least one sample is required to compute mean and variance.");
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
    BOOST_MATH_ASSERT_MSG(n > 1, "At least two samples are required to compute the sample variance.");
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
    BOOST_MATH_ASSERT_MSG(first != last, "At least one sample is required to compute skewness.");
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
    BOOST_MATH_ASSERT_MSG(first != last, "At least one sample is required to compute the first four moments.");
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


template<class RandomAccessContainer>
inline auto median(RandomAccessContainer & v)
{
    return median(v.begin(), v.end());
}

template<class RandomAccessIterator>
auto gini_coefficient(RandomAccessIterator first, RandomAccessIterator last)
{
    using Real = typename std::iterator_traits<RandomAccessIterator>::value_type;
    BOOST_MATH_ASSERT_MSG(first != last && std::next(first) != last, "Computation of the Gini coefficient requires at least two samples.");

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