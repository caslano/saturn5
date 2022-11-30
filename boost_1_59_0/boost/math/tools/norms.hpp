//  (C) Copyright Nick Thompson 2018.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_NORMS_HPP
#define BOOST_MATH_TOOLS_NORMS_HPP
#include <algorithm>
#include <iterator>
#include <complex>
#include <cmath>
#include <boost/math/tools/assert.hpp>
#include <boost/math/tools/complex.hpp>


namespace boost::math::tools {

// Mallat, "A Wavelet Tour of Signal Processing", equation 2.60:
template<class ForwardIterator>
auto total_variation(ForwardIterator first, ForwardIterator last)
{
    using T = typename std::iterator_traits<ForwardIterator>::value_type;
    using std::abs;
    BOOST_MATH_ASSERT_MSG(first != last && std::next(first) != last, "At least two samples are required to compute the total variation.");
    auto it = first;
    if constexpr (std::is_unsigned<T>::value)
    {
        T tmp = *it;
        double tv = 0;
        while (++it != last)
        {
            if (*it > tmp)
            {
                tv += *it - tmp;
            }
            else
            {
                tv += tmp - *it;
            }
            tmp = *it;
        }
        return tv;
    }
    else if constexpr (std::is_integral<T>::value)
    {
        double tv = 0;
        double tmp = *it;
        while(++it != last)
        {
            double tmp2 = *it;
            tv += abs(tmp2 - tmp);
            tmp = *it;
        }
        return tv;
    }
    else
    {
        T tmp = *it;
        T tv = 0;
        while (++it != last)
        {
            tv += abs(*it - tmp);
            tmp = *it;
        }
        return tv;
    }
}

template<class Container>
inline auto total_variation(Container const & v)
{
    return total_variation(v.cbegin(), v.cend());
}


template<class ForwardIterator>
auto sup_norm(ForwardIterator first, ForwardIterator last)
{
    BOOST_MATH_ASSERT_MSG(first != last, "At least one value is required to compute the sup norm.");
    using T = typename std::iterator_traits<ForwardIterator>::value_type;
    using std::abs;
    if constexpr (boost::math::tools::is_complex_type<T>::value)
    {
        auto it = std::max_element(first, last, [](T a, T b) { return abs(b) > abs(a); });
        return abs(*it);
    }
    else if constexpr (std::is_unsigned<T>::value)
    {
        return *std::max_element(first, last);
    }
    else
    {
        auto pair = std::minmax_element(first, last);
        if (abs(*pair.first) > abs(*pair.second))
        {
            return abs(*pair.first);
        }
        else
        {
            return abs(*pair.second);
        }
    }
}

template<class Container>
inline auto sup_norm(Container const & v)
{
    return sup_norm(v.cbegin(), v.cend());
}

template<class ForwardIterator>
auto l1_norm(ForwardIterator first, ForwardIterator last)
{
    using T = typename std::iterator_traits<ForwardIterator>::value_type;
    using std::abs;
    if constexpr (std::is_unsigned<T>::value)
    {
        double l1 = 0;
        for (auto it = first; it != last; ++it)
        {
            l1 += *it;
        }
        return l1;
    }
    else if constexpr (std::is_integral<T>::value)
    {
        double l1 = 0;
        for (auto it = first; it != last; ++it)
        {
            double tmp = *it;
            l1 += abs(tmp);
        }
        return l1;
    }
    else
    {
        decltype(abs(*first)) l1 = 0;
        for (auto it = first; it != last; ++it)
        {
            l1 += abs(*it);
        }
        return l1;
    }

}

template<class Container>
inline auto l1_norm(Container const & v)
{
    return l1_norm(v.cbegin(), v.cend());
}


template<class ForwardIterator>
auto l2_norm(ForwardIterator first, ForwardIterator last)
{
    using T = typename std::iterator_traits<ForwardIterator>::value_type;
    using std::abs;
    using std::norm;
    using std::sqrt;
    using std::is_floating_point;
    using std::isfinite;
    if constexpr (boost::math::tools::is_complex_type<T>::value)
    {
        typedef typename T::value_type Real;
        Real l2 = 0;
        for (auto it = first; it != last; ++it)
        {
            l2 += norm(*it);
        }
        Real result = sqrt(l2);
        if (!isfinite(result))
        {
            Real a = sup_norm(first, last);
            l2 = 0;
            for (auto it = first; it != last; ++it)
            {
                l2 += norm(*it/a);
            }
            return a*sqrt(l2);
        }
        return result;
    }
    else if constexpr (is_floating_point<T>::value ||
                       std::numeric_limits<T>::max_exponent)
    {
        T l2 = 0;
        for (auto it = first; it != last; ++it)
        {
            l2 += (*it)*(*it);
        }
        T result = sqrt(l2);
        // Higham, Accuracy and Stability of Numerical Algorithms,
        // Problem 27.5 presents a different algorithm to deal with overflow.
        // The algorithm used here takes 3 passes *if* there is overflow.
        // Higham's algorithm is 1 pass, but more requires operations than the no overflow case.
        // I'm operating under the assumption that overflow is rare since the dynamic range of floating point numbers is huge.
        if (!isfinite(result))
        {
            T a = sup_norm(first, last);
            l2 = 0;
            for (auto it = first; it != last; ++it)
            {
                T tmp = *it/a;
                l2 += tmp*tmp;
            }
            return a*sqrt(l2);
        }
        return result;
    }
    else
    {
        double l2 = 0;
        for (auto it = first; it != last; ++it)
        {
            double tmp = *it;
            l2 += tmp*tmp;
        }
        return sqrt(l2);
    }
}

template<class Container>
inline auto l2_norm(Container const & v)
{
    return l2_norm(v.cbegin(), v.cend());
}

template<class ForwardIterator>
size_t l0_pseudo_norm(ForwardIterator first, ForwardIterator last)
{
    using RealOrComplex = typename std::iterator_traits<ForwardIterator>::value_type;
    size_t count = 0;
    for (auto it = first; it != last; ++it)
    {
        if (*it != RealOrComplex(0))
        {
            ++count;
        }
    }
    return count;
}

template<class Container>
inline size_t l0_pseudo_norm(Container const & v)
{
    return l0_pseudo_norm(v.cbegin(), v.cend());
}

template<class ForwardIterator>
size_t hamming_distance(ForwardIterator first1, ForwardIterator last1, ForwardIterator first2)
{
    size_t count = 0;
    auto it1 = first1;
    auto it2 = first2;
    while (it1 != last1)
    {
        if (*it1++ != *it2++)
        {
            ++count;
        }
    }
    return count;
}

template<class Container>
inline size_t hamming_distance(Container const & v, Container const & w)
{
    return hamming_distance(v.cbegin(), v.cend(), w.cbegin());
}

template<class ForwardIterator>
auto lp_norm(ForwardIterator first, ForwardIterator last, unsigned p)
{
    using std::abs;
    using std::pow;
    using std::is_floating_point;
    using std::isfinite;
    using RealOrComplex = typename std::iterator_traits<ForwardIterator>::value_type;
    if constexpr (boost::math::tools::is_complex_type<RealOrComplex>::value)
    {
        using std::norm;
        using Real = typename RealOrComplex::value_type;
        Real lp = 0;
        for (auto it = first; it != last; ++it)
        {
            lp += pow(abs(*it), p);
        }

        auto result = pow(lp, Real(1)/Real(p));
        if (!isfinite(result))
        {
            auto a = boost::math::tools::sup_norm(first, last);
            Real lp = 0;
            for (auto it = first; it != last; ++it)
            {
                lp += pow(abs(*it)/a, p);
            }
            result = a*pow(lp, Real(1)/Real(p));
        }
        return result;
    }
    else if constexpr (is_floating_point<RealOrComplex>::value || std::numeric_limits<RealOrComplex>::max_exponent)
    {
        BOOST_MATH_ASSERT_MSG(p >= 0, "For p < 0, the lp norm is not a norm");
        RealOrComplex lp = 0;

        for (auto it = first; it != last; ++it)
        {
            lp += pow(abs(*it), p);
        }

        RealOrComplex result = pow(lp, RealOrComplex(1)/RealOrComplex(p));
        if (!isfinite(result))
        {
            RealOrComplex a = boost::math::tools::sup_norm(first, last);
            lp = 0;
            for (auto it = first; it != last; ++it)
            {
                lp += pow(abs(*it)/a, p);
            }
            result = a*pow(lp, RealOrComplex(1)/RealOrComplex(p));
        }
        return result;
    }
    else
    {
        double lp = 0;

        for (auto it = first; it != last; ++it)
        {
            double tmp = *it;
            lp += pow(abs(tmp), p);
        }
        double result = pow(lp, 1.0/double(p));
        if (!isfinite(result))
        {
            double a = boost::math::tools::sup_norm(first, last);
            lp = 0;
            for (auto it = first; it != last; ++it)
            {
                double tmp = *it;
                lp += pow(abs(tmp)/a, p);
            }
            result = a*pow(lp, double(1)/double(p));
        }
        return result;
    }
}

template<class Container>
inline auto lp_norm(Container const & v, unsigned p)
{
    return lp_norm(v.cbegin(), v.cend(), p);
}


template<class ForwardIterator>
auto lp_distance(ForwardIterator first1, ForwardIterator last1, ForwardIterator first2, unsigned p)
{
    using std::pow;
    using std::abs;
    using std::is_floating_point;
    using std::isfinite;
    using RealOrComplex = typename std::iterator_traits<ForwardIterator>::value_type;
    auto it1 = first1;
    auto it2 = first2;

    if constexpr (boost::math::tools::is_complex_type<RealOrComplex>::value)
    {
        using Real = typename RealOrComplex::value_type;
        using std::norm;
        Real dist = 0;
        while(it1 != last1)
        {
            auto tmp = *it1++ - *it2++;
            dist += pow(abs(tmp), p);
        }
        return pow(dist, Real(1)/Real(p));
    }
    else if constexpr (is_floating_point<RealOrComplex>::value || std::numeric_limits<RealOrComplex>::max_exponent)
    {
        RealOrComplex dist = 0;
        while(it1 != last1)
        {
            auto tmp = *it1++ - *it2++;
            dist += pow(abs(tmp), p);
        }
        return pow(dist, RealOrComplex(1)/RealOrComplex(p));
    }
    else
    {
        double dist = 0;
        while(it1 != last1)
        {
            double tmp1 = *it1++;
            double tmp2 = *it2++;
            // Naively you'd expect the integer subtraction to be faster,
            // but this can overflow or wraparound:
            //double tmp = *it1++ - *it2++;
            dist += pow(abs(tmp1 - tmp2), p);
        }
        return pow(dist, 1.0/double(p));
    }
}

template<class Container>
inline auto lp_distance(Container const & v, Container const & w, unsigned p)
{
    return lp_distance(v.cbegin(), v.cend(), w.cbegin(), p);
}


template<class ForwardIterator>
auto l1_distance(ForwardIterator first1, ForwardIterator last1, ForwardIterator first2)
{
    using std::abs;
    using std::is_floating_point;
    using std::isfinite;
    using T = typename std::iterator_traits<ForwardIterator>::value_type;
    auto it1 = first1;
    auto it2 = first2;
    if constexpr (boost::math::tools::is_complex_type<T>::value)
    {
        using Real = typename T::value_type;
        Real sum = 0;
        while (it1 != last1) {
            sum += abs(*it1++ - *it2++);
        }
        return sum;
    }
    else if constexpr (is_floating_point<T>::value || std::numeric_limits<T>::max_exponent)
    {
        T sum = 0;
        while (it1 != last1)
        {
            sum += abs(*it1++ - *it2++);
        }
        return sum;
    }
    else if constexpr (std::is_unsigned<T>::value)
    {
        double sum = 0;
        while(it1 != last1)
        {
            T x1 = *it1++;
            T x2 = *it2++;
            if (x1 > x2)
            {
                sum += (x1 - x2);
            }
            else
            {
                sum += (x2 - x1);
            }
        }
        return sum;
    }
    else if constexpr (std::is_integral<T>::value)
    {
        double sum = 0;
        while(it1 != last1)
        {
            double x1 = *it1++;
            double x2 = *it2++;
            sum += abs(x1-x2);
        }
        return sum;
    }
    else
    {
        BOOST_MATH_ASSERT_MSG(false, "Could not recognize type.");
    }

}

template<class Container>
auto l1_distance(Container const & v, Container const & w)
{
    using std::size;
    BOOST_MATH_ASSERT_MSG(size(v) == size(w),
                     "L1 distance requires both containers to have the same number of elements");
    return l1_distance(v.cbegin(), v.cend(), w.begin());
}

template<class ForwardIterator>
auto l2_distance(ForwardIterator first1, ForwardIterator last1, ForwardIterator first2)
{
    using std::abs;
    using std::norm;
    using std::sqrt;
    using std::is_floating_point;
    using std::isfinite;
    using T = typename std::iterator_traits<ForwardIterator>::value_type;
    auto it1 = first1;
    auto it2 = first2;
    if constexpr (boost::math::tools::is_complex_type<T>::value)
    {
        using Real = typename T::value_type;
        Real sum = 0;
        while (it1 != last1) {
            sum += norm(*it1++ - *it2++);
        }
        return sqrt(sum);
    }
    else if constexpr (is_floating_point<T>::value || std::numeric_limits<T>::max_exponent)
    {
        T sum = 0;
        while (it1 != last1)
        {
            T tmp = *it1++ - *it2++;
            sum += tmp*tmp;
        }
        return sqrt(sum);
    }
    else if constexpr (std::is_unsigned<T>::value)
    {
        double sum = 0;
        while(it1 != last1)
        {
            T x1 = *it1++;
            T x2 = *it2++;
            if (x1 > x2)
            {
                double tmp = x1-x2;
                sum += tmp*tmp;
            }
            else
            {
                double tmp = x2 - x1;
                sum += tmp*tmp;
            }
        }
        return sqrt(sum);
    }
    else
    {
        double sum = 0;
        while(it1 != last1)
        {
            double x1 = *it1++;
            double x2 = *it2++;
            double tmp = x1-x2;
            sum += tmp*tmp;
        }
        return sqrt(sum);
    }
}

template<class Container>
auto l2_distance(Container const & v, Container const & w)
{
    using std::size;
    BOOST_MATH_ASSERT_MSG(size(v) == size(w),
                     "L2 distance requires both containers to have the same number of elements");
    return l2_distance(v.cbegin(), v.cend(), w.begin());
}

template<class ForwardIterator>
auto sup_distance(ForwardIterator first1, ForwardIterator last1, ForwardIterator first2)
{
    using std::abs;
    using std::norm;
    using std::sqrt;
    using std::is_floating_point;
    using std::isfinite;
    using T = typename std::iterator_traits<ForwardIterator>::value_type;
    auto it1 = first1;
    auto it2 = first2;
    if constexpr (boost::math::tools::is_complex_type<T>::value)
    {
        using Real = typename T::value_type;
        Real sup_sq = 0;
        while (it1 != last1) {
            Real tmp = norm(*it1++ - *it2++);
            if (tmp > sup_sq) {
                sup_sq = tmp;
            }
        }
        return sqrt(sup_sq);
    }
    else if constexpr (is_floating_point<T>::value || std::numeric_limits<T>::max_exponent)
    {
        T sup = 0;
        while (it1 != last1)
        {
            T tmp = *it1++ - *it2++;
            if (sup < abs(tmp))
            {
                sup = abs(tmp);
            }
        }
        return sup;
    }
    else // integral values:
    {
        double sup = 0;
        while(it1 != last1)
        {
            T x1 = *it1++;
            T x2 = *it2++;
            double tmp;
            if (x1 > x2)
            {
                tmp = x1-x2;
            }
            else
            {
                tmp = x2 - x1;
            }
            if (sup < tmp) {
                sup = tmp;
            }
        }
        return sup;
    }
}

template<class Container>
auto sup_distance(Container const & v, Container const & w)
{
    using std::size;
    BOOST_MATH_ASSERT_MSG(size(v) == size(w),
                     "sup distance requires both containers to have the same number of elements");
    return sup_distance(v.cbegin(), v.cend(), w.begin());
}


}
#endif

/* norms.hpp
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
*/