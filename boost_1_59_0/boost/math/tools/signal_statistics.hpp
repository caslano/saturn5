//  (C) Copyright Nick Thompson 2018.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_SIGNAL_STATISTICS_HPP
#define BOOST_MATH_TOOLS_SIGNAL_STATISTICS_HPP

#include <algorithm>
#include <iterator>
#include <boost/math/tools/assert.hpp>
#include <boost/math/tools/complex.hpp>
#include <boost/math/tools/roots.hpp>
#include <boost/math/tools/header_deprecated.hpp>
#include <boost/math/statistics/univariate_statistics.hpp>

BOOST_MATH_HEADER_DEPRECATED("<boost/math/statistics/signal_statistics.hpp>");

namespace boost::math::tools {

template<class ForwardIterator>
auto absolute_gini_coefficient(ForwardIterator first, ForwardIterator last)
{
    using std::abs;
    using RealOrComplex = typename std::iterator_traits<ForwardIterator>::value_type;
    BOOST_MATH_ASSERT_MSG(first != last && std::next(first) != last, "Computation of the Gini coefficient requires at least two samples.");

    std::sort(first, last,  [](RealOrComplex a, RealOrComplex b) { return abs(b) > abs(a); });


    decltype(abs(*first)) i = 1;
    decltype(abs(*first)) num = 0;
    decltype(abs(*first)) denom = 0;
    for (auto it = first; it != last; ++it)
    {
        decltype(abs(*first)) tmp = abs(*it);
        num += tmp*i;
        denom += tmp;
        ++i;
    }

    // If the l1 norm is zero, all elements are zero, so every element is the same.
    if (denom == 0)
    {
        decltype(abs(*first)) zero = 0;
        return zero;
    }
    return ((2*num)/denom - i)/(i-1);
}

template<class RandomAccessContainer>
inline auto absolute_gini_coefficient(RandomAccessContainer & v)
{
    return boost::math::tools::absolute_gini_coefficient(v.begin(), v.end());
}

template<class ForwardIterator>
auto sample_absolute_gini_coefficient(ForwardIterator first, ForwardIterator last)
{
    size_t n = std::distance(first, last);
    return n*boost::math::tools::absolute_gini_coefficient(first, last)/(n-1);
}

template<class RandomAccessContainer>
inline auto sample_absolute_gini_coefficient(RandomAccessContainer & v)
{
    return boost::math::tools::sample_absolute_gini_coefficient(v.begin(), v.end());
}


// The Hoyer sparsity measure is defined in:
// https://arxiv.org/pdf/0811.4706.pdf
template<class ForwardIterator>
auto hoyer_sparsity(const ForwardIterator first, const ForwardIterator last)
{
    using T = typename std::iterator_traits<ForwardIterator>::value_type;
    using std::abs;
    using std::sqrt;
    BOOST_MATH_ASSERT_MSG(first != last && std::next(first) != last, "Computation of the Hoyer sparsity requires at least two samples.");

    if constexpr (std::is_unsigned<T>::value)
    {
        T l1 = 0;
        T l2 = 0;
        size_t n = 0;
        for (auto it = first; it != last; ++it)
        {
            l1 += *it;
            l2 += (*it)*(*it);
            n += 1;
        }

        double rootn = sqrt(n);
        return (rootn - l1/sqrt(l2) )/ (rootn - 1);
    }
    else {
        decltype(abs(*first)) l1 = 0;
        decltype(abs(*first)) l2 = 0;
        // We wouldn't need to count the elements if it was a random access iterator,
        // but our only constraint is that it's a forward iterator.
        size_t n = 0;
        for (auto it = first; it != last; ++it)
        {
            decltype(abs(*first)) tmp = abs(*it);
            l1 += tmp;
            l2 += tmp*tmp;
            n += 1;
        }
        if constexpr (std::is_integral<T>::value)
        {
            double rootn = sqrt(n);
            return (rootn - l1/sqrt(l2) )/ (rootn - 1);
        }
        else
        {
            decltype(abs(*first)) rootn = sqrt(static_cast<decltype(abs(*first))>(n));
            return (rootn - l1/sqrt(l2) )/ (rootn - 1);
        }
    }
}

template<class Container>
inline auto hoyer_sparsity(Container const & v)
{
    return boost::math::tools::hoyer_sparsity(v.cbegin(), v.cend());
}


template<class Container>
auto oracle_snr(Container const & signal, Container const & noisy_signal)
{
    using Real = typename Container::value_type;
    BOOST_MATH_ASSERT_MSG(signal.size() == noisy_signal.size(),
                     "Signal and noisy_signal must be have the same number of elements.");
    if constexpr (std::is_integral<Real>::value)
    {
        double numerator = 0;
        double denominator = 0;
        for (size_t i = 0; i < signal.size(); ++i)
        {
            numerator += signal[i]*signal[i];
            denominator += (noisy_signal[i] - signal[i])*(noisy_signal[i] - signal[i]);
        }
        if (numerator == 0 && denominator == 0)
        {
            return std::numeric_limits<double>::quiet_NaN();
        }
        if (denominator == 0)
        {
            return std::numeric_limits<double>::infinity();
        }
        return numerator/denominator;
    }
    else if constexpr (boost::math::tools::is_complex_type<Real>::value)

    {
        using std::norm;
        typename Real::value_type numerator = 0;
        typename Real::value_type denominator = 0;
        for (size_t i = 0; i < signal.size(); ++i)
        {
            numerator += norm(signal[i]);
            denominator += norm(noisy_signal[i] - signal[i]);
        }
        if (numerator == 0 && denominator == 0)
        {
            return std::numeric_limits<typename Real::value_type>::quiet_NaN();
        }
        if (denominator == 0)
        {
            return std::numeric_limits<typename Real::value_type>::infinity();
        }

        return numerator/denominator;
    }
    else
    {
        Real numerator = 0;
        Real denominator = 0;
        for (size_t i = 0; i < signal.size(); ++i)
        {
            numerator += signal[i]*signal[i];
            denominator += (signal[i] - noisy_signal[i])*(signal[i] - noisy_signal[i]);
        }
        if (numerator == 0 && denominator == 0)
        {
            return std::numeric_limits<Real>::quiet_NaN();
        }
        if (denominator == 0)
        {
            return std::numeric_limits<Real>::infinity();
        }

        return numerator/denominator;
    }
}

template<class Container>
auto mean_invariant_oracle_snr(Container const & signal, Container const & noisy_signal)
{
    using Real = typename Container::value_type;
    BOOST_MATH_ASSERT_MSG(signal.size() == noisy_signal.size(), "Signal and noisy signal must be have the same number of elements.");

    Real mu = boost::math::tools::mean(signal);
    Real numerator = 0;
    Real denominator = 0;
    for (size_t i = 0; i < signal.size(); ++i)
    {
        Real tmp = signal[i] - mu;
        numerator += tmp*tmp;
        denominator += (signal[i] - noisy_signal[i])*(signal[i] - noisy_signal[i]);
    }
    if (numerator == 0 && denominator == 0)
    {
        return std::numeric_limits<Real>::quiet_NaN();
    }
    if (denominator == 0)
    {
        return std::numeric_limits<Real>::infinity();
    }

    return numerator/denominator;

}

template<class Container>
auto mean_invariant_oracle_snr_db(Container const & signal, Container const & noisy_signal)
{
    using std::log10;
    return 10*log10(boost::math::tools::mean_invariant_oracle_snr(signal, noisy_signal));
}


// Follows the definition of SNR given in Mallat, A Wavelet Tour of Signal Processing, equation 11.16.
template<class Container>
auto oracle_snr_db(Container const & signal, Container const & noisy_signal)
{
    using std::log10;
    return 10*log10(boost::math::tools::oracle_snr(signal, noisy_signal));
}

// A good reference on the M2M4 estimator:
// D. R. Pauluzzi and N. C. Beaulieu, "A comparison of SNR estimation techniques for the AWGN channel," IEEE Trans. Communications, Vol. 48, No. 10, pp. 1681-1691, 2000.
// A nice python implementation:
// https://github.com/gnuradio/gnuradio/blob/master/gr-digital/examples/snr_estimators.py
template<class ForwardIterator>
auto m2m4_snr_estimator(ForwardIterator first, ForwardIterator last, decltype(*first) estimated_signal_kurtosis=1, decltype(*first) estimated_noise_kurtosis=3)
{
    BOOST_MATH_ASSERT_MSG(estimated_signal_kurtosis > 0, "The estimated signal kurtosis must be positive");
    BOOST_MATH_ASSERT_MSG(estimated_noise_kurtosis > 0, "The estimated noise kurtosis must be positive.");
    using Real = typename std::iterator_traits<ForwardIterator>::value_type;
    using std::sqrt;
    if constexpr (std::is_floating_point<Real>::value || std::numeric_limits<Real>::max_exponent)
    {
        // If we first eliminate N, we obtain the quadratic equation:
        // (ka+kw-6)S^2 + 2M2(3-kw)S + kw*M2^2 - M4 = 0 =: a*S^2 + bs*N + cs = 0
        // If we first eliminate S, we obtain the quadratic equation:
        // (ka+kw-6)N^2 + 2M2(3-ka)N + ka*M2^2 - M4 = 0 =: a*N^2 + bn*N + cn = 0
        // I believe these equations are totally independent quadratics;
        // if one has a complex solution it is not necessarily the case that the other must also.
        // However, I can't prove that, so there is a chance that this does unnecessary work.
        // Future improvements: There are algorithms which can solve quadratics much more effectively than the naive implementation found here.
        // See: https://stackoverflow.com/questions/48979861/numerically-stable-method-for-solving-quadratic-equations/50065711#50065711
        auto [M1, M2, M3, M4] = boost::math::tools::first_four_moments(first, last);
        if (M4 == 0)
        {
            // The signal is constant. There is no noise:
            return std::numeric_limits<Real>::infinity();
        }
        // Change to notation in Pauluzzi, equation 41:
        auto kw = estimated_noise_kurtosis;
        auto ka = estimated_signal_kurtosis;
        // A common case, since it's the default:
        Real a = (ka+kw-6);
        Real bs = 2*M2*(3-kw);
        Real cs = kw*M2*M2 - M4;
        Real bn = 2*M2*(3-ka);
        Real cn = ka*M2*M2 - M4;
        auto [S0, S1] = boost::math::tools::quadratic_roots(a, bs, cs);
        if (S1 > 0)
        {
            auto N = M2 - S1;
            if (N > 0)
            {
                return S1/N;
            }
            if (S0 > 0)
            {
                N = M2 - S0;
                if (N > 0)
                {
                    return S0/N;
                }
            }
        }
        auto [N0, N1] = boost::math::tools::quadratic_roots(a, bn, cn);
        if (N1 > 0)
        {
            auto S = M2 - N1;
            if (S > 0)
            {
                return S/N1;
            }
            if (N0 > 0)
            {
                S = M2 - N0;
                if (S > 0)
                {
                    return S/N0;
                }
            }
        }
        // This happens distressingly often. It's a limitation of the method.
        return std::numeric_limits<Real>::quiet_NaN();
    }
    else
    {
        BOOST_MATH_ASSERT_MSG(false, "The M2M4 estimator has not been implemented for this type.");
        return std::numeric_limits<Real>::quiet_NaN();
    }
}

template<class Container>
inline auto m2m4_snr_estimator(Container const & noisy_signal,  typename Container::value_type estimated_signal_kurtosis=1, typename Container::value_type estimated_noise_kurtosis=3)
{
    return m2m4_snr_estimator(noisy_signal.cbegin(), noisy_signal.cend(), estimated_signal_kurtosis, estimated_noise_kurtosis);
}

template<class ForwardIterator>
inline auto m2m4_snr_estimator_db(ForwardIterator first, ForwardIterator last, decltype(*first) estimated_signal_kurtosis=1, decltype(*first) estimated_noise_kurtosis=3)
{
    using std::log10;
    return 10*log10(m2m4_snr_estimator(first, last, estimated_signal_kurtosis, estimated_noise_kurtosis));
}


template<class Container>
inline auto m2m4_snr_estimator_db(Container const & noisy_signal,  typename Container::value_type estimated_signal_kurtosis=1, typename Container::value_type estimated_noise_kurtosis=3)
{
    using std::log10;
    return 10*log10(m2m4_snr_estimator(noisy_signal, estimated_signal_kurtosis, estimated_noise_kurtosis));
}

}
#endif

/* signal_statistics.hpp
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
*/