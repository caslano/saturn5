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


namespace boost::math::statistics {

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
    return boost::math::statistics::absolute_gini_coefficient(v.begin(), v.end());
}

template<class ForwardIterator>
auto sample_absolute_gini_coefficient(ForwardIterator first, ForwardIterator last)
{
    size_t n = std::distance(first, last);
    return n*boost::math::statistics::absolute_gini_coefficient(first, last)/(n-1);
}

template<class RandomAccessContainer>
inline auto sample_absolute_gini_coefficient(RandomAccessContainer & v)
{
    return boost::math::statistics::sample_absolute_gini_coefficient(v.begin(), v.end());
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
    return boost::math::statistics::hoyer_sparsity(v.cbegin(), v.cend());
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

    Real mu = boost::math::statistics::mean(signal);
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
    return 10*log10(boost::math::statistics::mean_invariant_oracle_snr(signal, noisy_signal));
}


// Follows the definition of SNR given in Mallat, A Wavelet Tour of Signal Processing, equation 11.16.
template<class Container>
auto oracle_snr_db(Container const & signal, Container const & noisy_signal)
{
    using std::log10;
    return 10*log10(boost::math::statistics::oracle_snr(signal, noisy_signal));
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
        auto [M1, M2, M3, M4] = boost::math::statistics::first_four_moments(first, last);
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