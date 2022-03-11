//  (C) Copyright Nick Thompson 2018.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_SIGNAL_STATISTICS_HPP
#define BOOST_MATH_TOOLS_SIGNAL_STATISTICS_HPP

#include <algorithm>
#include <iterator>
#include <boost/assert.hpp>
#include <boost/math/tools/complex.hpp>
#include <boost/math/tools/roots.hpp>
#include <boost/math/statistics/univariate_statistics.hpp>
#include <boost/config/header_deprecated.hpp>

BOOST_HEADER_DEPRECATED("<boost/math/statistics/signal_statistics.hpp>");

namespace boost::math::tools {

template<class ForwardIterator>
auto absolute_gini_coefficient(ForwardIterator first, ForwardIterator last)
{
    using std::abs;
    using RealOrComplex = typename std::iterator_traits<ForwardIterator>::value_type;
    BOOST_ASSERT_MSG(first != last && std::next(first) != last, "Computation of the Gini coefficient requires at least two samples.");

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
    BOOST_ASSERT_MSG(first != last && std::next(first) != last, "Computation of the Hoyer sparsity requires at least two samples.");

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
    BOOST_ASSERT_MSG(signal.size() == noisy_signal.size(),
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
    BOOST_ASSERT_MSG(signal.size() == noisy_signal.size(), "Signal and noisy signal must be have the same number of elements.");

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
    BOOST_ASSERT_MSG(estimated_signal_kurtosis > 0, "The estimated signal kurtosis must be positive");
    BOOST_ASSERT_MSG(estimated_noise_kurtosis > 0, "The estimated noise kurtosis must be positive.");
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
        BOOST_ASSERT_MSG(false, "The M2M4 estimator has not been implemented for this type.");
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