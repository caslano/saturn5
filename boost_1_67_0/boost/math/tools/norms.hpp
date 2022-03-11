//  (C) Copyright Nick Thompson 2018.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_NORMS_HPP
#define BOOST_MATH_TOOLS_NORMS_HPP
#include <algorithm>
#include <iterator>
#include <boost/assert.hpp>
#include <boost/math/tools/complex.hpp>


namespace boost::math::tools {

// Mallat, "A Wavelet Tour of Signal Processing", equation 2.60:
template<class ForwardIterator>
auto total_variation(ForwardIterator first, ForwardIterator last)
{
    using T = typename std::iterator_traits<ForwardIterator>::value_type;
    using std::abs;
    BOOST_ASSERT_MSG(first != last && std::next(first) != last, "At least two samples are required to compute the total variation.");
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
    BOOST_ASSERT_MSG(first != last, "At least one value is required to compute the sup norm.");
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
        BOOST_ASSERT_MSG(p >= 0, "For p < 0, the lp norm is not a norm");
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
        BOOST_ASSERT_MSG(false, "Could not recognize type.");
    }

}

template<class Container>
auto l1_distance(Container const & v, Container const & w)
{
    using std::size;
    BOOST_ASSERT_MSG(size(v) == size(w),
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
    BOOST_ASSERT_MSG(size(v) == size(w),
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
    BOOST_ASSERT_MSG(size(v) == size(w),
                     "sup distance requires both containers to have the same number of elements");
    return sup_distance(v.cbegin(), v.cend(), w.begin());
}


}
#endif

/* norms.hpp
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
*/