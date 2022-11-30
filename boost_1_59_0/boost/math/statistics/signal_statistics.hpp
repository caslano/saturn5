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
#include <boost/math/statistics/univariate_statistics.hpp>


namespace boost::math::statistics {

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
    return boost::math::statistics::hoyer_sparsity(v.cbegin(), v.cend());
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