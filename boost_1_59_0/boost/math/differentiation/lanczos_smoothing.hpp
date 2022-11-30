//  (C) Copyright Nick Thompson 2019.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DIFFERENTIATION_LANCZOS_SMOOTHING_HPP
#define BOOST_MATH_DIFFERENTIATION_LANCZOS_SMOOTHING_HPP
#include <cmath> // for std::abs
#include <cstddef>
#include <limits> // to nan initialize
#include <vector>
#include <string>
#include <stdexcept>
#include <type_traits>
#include <boost/math/tools/assert.hpp>

namespace boost::math::differentiation {

namespace detail {
template <typename Real>
class discrete_legendre {
  public:
    explicit discrete_legendre(std::size_t n, Real x) : m_n{n}, m_r{2}, m_x{x},
                                                        m_qrm2{1}, m_qrm1{x},
                                                        m_qrm2p{0}, m_qrm1p{1},
                                                        m_qrm2pp{0}, m_qrm1pp{0}
    {
        using std::abs;
        BOOST_MATH_ASSERT_MSG(abs(m_x) <= 1, "Three term recurrence is stable only for |x| <=1.");
        // The integer n indexes a family of discrete Legendre polynomials indexed by k <= 2*n
    }

    Real norm_sq(int r) const
    {
        Real prod = Real(2) / Real(2 * r + 1);
        for (int k = -r; k <= r; ++k) {
            prod *= Real(2 * m_n + 1 + k) / Real(2 * m_n);
        }
        return prod;
    }

    Real next()
    {
        Real N = 2 * m_n + 1;
        Real num = (m_r - 1) * (N * N - (m_r - 1) * (m_r - 1)) * m_qrm2;
        Real tmp = (2 * m_r - 1) * m_x * m_qrm1 - num / Real(4 * m_n * m_n);
        m_qrm2 = m_qrm1;
        m_qrm1 = tmp / m_r;
        ++m_r;
        return m_qrm1;
    }

    Real next_prime()
    {
        Real N = 2 * m_n + 1;
        Real s = (m_r - 1) * (N * N - (m_r - 1) * (m_r - 1)) / Real(4 * m_n * m_n);
        Real tmp1 = ((2 * m_r - 1) * m_x * m_qrm1 - s * m_qrm2) / m_r;
        Real tmp2 = ((2 * m_r - 1) * (m_qrm1 + m_x * m_qrm1p) - s * m_qrm2p) / m_r;
        m_qrm2 = m_qrm1;
        m_qrm1 = tmp1;
        m_qrm2p = m_qrm1p;
        m_qrm1p = tmp2;
        ++m_r;
        return m_qrm1p;
    }

    Real next_dbl_prime()
    {
        Real N = 2*m_n + 1;
        Real trm1 = 2*m_r - 1;
        Real s = (m_r - 1) * (N * N - (m_r - 1) * (m_r - 1)) / Real(4 * m_n * m_n);
        Real rqrpp = 2*trm1*m_qrm1p + trm1*m_x*m_qrm1pp - s*m_qrm2pp;
        Real tmp1 = ((2 * m_r - 1) * m_x * m_qrm1 - s * m_qrm2) / m_r;
        Real tmp2 = ((2 * m_r - 1) * (m_qrm1 + m_x * m_qrm1p) - s * m_qrm2p) / m_r;
        m_qrm2 = m_qrm1;
        m_qrm1 = tmp1;
        m_qrm2p = m_qrm1p;
        m_qrm1p = tmp2;
        m_qrm2pp = m_qrm1pp;
        m_qrm1pp = rqrpp/m_r;
        ++m_r;
        return m_qrm1pp;
    }

    Real operator()(Real x, std::size_t k)
    {
        BOOST_MATH_ASSERT_MSG(k <= 2 * m_n, "r <= 2n is required.");
        if (k == 0)
        {
            return 1;
        }
        if (k == 1)
        {
            return x;
        }
        Real qrm2 = 1;
        Real qrm1 = x;
        Real N = 2 * m_n + 1;
        for (std::size_t r = 2; r <= k; ++r) {
            Real num = (r - 1) * (N * N - (r - 1) * (r - 1)) * qrm2;
            Real tmp = (2 * r - 1) * x * qrm1 - num / Real(4 * m_n * m_n);
            qrm2 = qrm1;
            qrm1 = tmp / r;
        }
        return qrm1;
    }

    Real prime(Real x, std::size_t k) {
        BOOST_MATH_ASSERT_MSG(k <= 2 * m_n, "r <= 2n is required.");
        if (k == 0) {
            return 0;
        }
        if (k == 1) {
            return 1;
        }
        Real qrm2 = 1;
        Real qrm1 = x;
        Real qrm2p = 0;
        Real qrm1p = 1;
        Real N = 2 * m_n + 1;
        for (std::size_t r = 2; r <= k; ++r) {
            Real s =
                (r - 1) * (N * N - (r - 1) * (r - 1)) / Real(4 * m_n * m_n);
            Real tmp1 = ((2 * r - 1) * x * qrm1 - s * qrm2) / r;
            Real tmp2 = ((2 * r - 1) * (qrm1 + x * qrm1p) - s * qrm2p) / r;
            qrm2 = qrm1;
            qrm1 = tmp1;
            qrm2p = qrm1p;
            qrm1p = tmp2;
        }
        return qrm1p;
    }

  private:
    std::size_t m_n;
    std::size_t m_r;
    Real m_x;
    Real m_qrm2;
    Real m_qrm1;
    Real m_qrm2p;
    Real m_qrm1p;
    Real m_qrm2pp;
    Real m_qrm1pp;
};

template <class Real>
std::vector<Real> interior_velocity_filter(std::size_t n, std::size_t p) {
    auto dlp = discrete_legendre<Real>(n, 0);
    std::vector<Real> coeffs(p+1);
    coeffs[1] = 1/dlp.norm_sq(1);
    for (std::size_t l = 3; l < p + 1; l += 2)
    {
        dlp.next_prime();
        coeffs[l] = dlp.next_prime()/ dlp.norm_sq(l);
    }

    // We could make the filter length n, as f[0] = 0,
    // but that'd make the indexing awkward when applying the filter.
    std::vector<Real> f(n + 1);
    // This value should never be read, but this is the correct value *if it is read*.
    // Hmm, should it be a nan then? I'm not gonna agonize.
    f[0] = 0;
    for (std::size_t j = 1; j < f.size(); ++j)
    {
        Real arg = Real(j) / Real(n);
        dlp = discrete_legendre<Real>(n, arg);
        f[j] = coeffs[1]*arg;
        for (std::size_t l = 3; l <= p; l += 2)
        {
            dlp.next();
            f[j] += coeffs[l]*dlp.next();
        }
        f[j] /= (n * n);
    }
    return f;
}

template <class Real>
std::vector<Real> boundary_velocity_filter(std::size_t n, std::size_t p, int64_t s)
{
    std::vector<Real> coeffs(p+1, std::numeric_limits<Real>::quiet_NaN());
    Real sn = Real(s) / Real(n);
    auto dlp = discrete_legendre<Real>(n, sn);
    coeffs[0] = 0;
    coeffs[1] = 1/dlp.norm_sq(1);
    for (std::size_t l = 2; l < p + 1; ++l)
    {
        // Calculation of the norms is common to all filters,
        // so it seems like an obvious optimization target.
        // I tried this: The spent in computing the norms time is not negligible,
        // but still a small fraction of the total compute time.
        // Hence I'm not refactoring out these norm calculations.
        coeffs[l] = dlp.next_prime()/ dlp.norm_sq(l);
    }

    std::vector<Real> f(2*n + 1);
    for (std::size_t k = 0; k < f.size(); ++k)
    {
        Real j = Real(k) - Real(n);
        Real arg = j/Real(n);
        dlp = discrete_legendre<Real>(n, arg);
        f[k] = coeffs[1]*arg;
        for (std::size_t l = 2; l <= p; ++l)
        {
            f[k] += coeffs[l]*dlp.next();
        }
        f[k] /= (n * n);
    }
    return f;
}

template <class Real>
std::vector<Real> acceleration_filter(std::size_t n, std::size_t p, int64_t s)
{
    BOOST_MATH_ASSERT_MSG(p <= 2*n, "Approximation order must be <= 2*n");
    BOOST_MATH_ASSERT_MSG(p > 2, "Approximation order must be > 2");

    std::vector<Real> coeffs(p+1, std::numeric_limits<Real>::quiet_NaN());
    Real sn = Real(s) / Real(n);
    auto dlp = discrete_legendre<Real>(n, sn);
    coeffs[0] = 0;
    coeffs[1] = 0;
    for (std::size_t l = 2; l < p + 1; ++l)
    {
        coeffs[l] = dlp.next_dbl_prime()/ dlp.norm_sq(l);
    }

    std::vector<Real> f(2*n + 1, 0);
    for (std::size_t k = 0; k < f.size(); ++k)
    {
        Real j = Real(k) - Real(n);
        Real arg = j/Real(n);
        dlp = discrete_legendre<Real>(n, arg);
        for (std::size_t l = 2; l <= p; ++l)
        {
            f[k] += coeffs[l]*dlp.next();
        }
        f[k] /= (n * n * n);
    }
    return f;
}


} // namespace detail

template <typename Real, std::size_t order = 1>
class discrete_lanczos_derivative {
public:
    discrete_lanczos_derivative(Real const & spacing,
                                std::size_t n = 18,
                                std::size_t approximation_order = 3)
        : m_dt{spacing}
    {
        static_assert(!std::is_integral_v<Real>,
                      "Spacing must be a floating point type.");
        BOOST_MATH_ASSERT_MSG(spacing > 0,
                         "Spacing between samples must be > 0.");

        if constexpr (order == 1)
        {
            BOOST_MATH_ASSERT_MSG(approximation_order <= 2 * n,
                             "The approximation order must be <= 2n");
            BOOST_MATH_ASSERT_MSG(approximation_order >= 2,
                             "The approximation order must be >= 2");

            if constexpr (std::is_same_v<Real, float> || std::is_same_v<Real, double>)
            {
                auto interior = detail::interior_velocity_filter<long double>(n, approximation_order);
                m_f.resize(interior.size());
                for (std::size_t j = 0; j < interior.size(); ++j)
                {
                    m_f[j] = static_cast<Real>(interior[j])/m_dt;
                }
            }
            else
            {
                m_f = detail::interior_velocity_filter<Real>(n, approximation_order);
                for (auto & x : m_f)
                {
                    x /= m_dt;
                }
            }

            m_boundary_filters.resize(n);
            // This for loop is a natural candidate for parallelization.
            // But does it matter? Probably not.
            for (std::size_t i = 0; i < n; ++i)
            {
                if constexpr (std::is_same_v<Real, float> || std::is_same_v<Real, double>)
                {
                    int64_t s = static_cast<int64_t>(i) - static_cast<int64_t>(n);
                    auto bf = detail::boundary_velocity_filter<long double>(n, approximation_order, s);
                    m_boundary_filters[i].resize(bf.size());
                    for (std::size_t j = 0; j < bf.size(); ++j)
                    {
                        m_boundary_filters[i][j] = static_cast<Real>(bf[j])/m_dt;
                    }
                }
                else
                {
                    int64_t s = static_cast<int64_t>(i) - static_cast<int64_t>(n);
                    m_boundary_filters[i] = detail::boundary_velocity_filter<Real>(n, approximation_order, s);
                    for (auto & bf : m_boundary_filters[i])
                    {
                        bf /= m_dt;
                    }
                }
            }
        }
        else if constexpr (order == 2)
        {
            // High precision isn't warranted for small p; only for large p.
            // (The computation appears stable for large n.)
            // But given that the filters are reusable for many vectors,
            // it's better to do a high precision computation and then cast back,
            // since the resulting cost is a factor of 2, and the cost of the filters not working is hours of debugging.
            if constexpr (std::is_same_v<Real, double> || std::is_same_v<Real, float>)
            {
                auto f = detail::acceleration_filter<long double>(n, approximation_order, 0);
                m_f.resize(n+1);
                for (std::size_t i = 0; i < m_f.size(); ++i)
                {
                    m_f[i] = static_cast<Real>(f[i+n])/(m_dt*m_dt);
                }
                m_boundary_filters.resize(n);
                for (std::size_t i = 0; i < n; ++i)
                {
                    int64_t s = static_cast<int64_t>(i) - static_cast<int64_t>(n);
                    auto bf = detail::acceleration_filter<long double>(n, approximation_order, s);
                    m_boundary_filters[i].resize(bf.size());
                    for (std::size_t j = 0; j < bf.size(); ++j)
                    {
                        m_boundary_filters[i][j] = static_cast<Real>(bf[j])/(m_dt*m_dt);
                    }
                }
            }
            else
            {
                // Given that the purpose is denoising, for higher precision calculations,
                // the default precision should be fine.
                auto f = detail::acceleration_filter<Real>(n, approximation_order, 0);
                m_f.resize(n+1);
                for (std::size_t i = 0; i < m_f.size(); ++i)
                {
                    m_f[i] = f[i+n]/(m_dt*m_dt);
                }
                m_boundary_filters.resize(n);
                for (std::size_t i = 0; i < n; ++i)
                {
                    int64_t s = static_cast<int64_t>(i) - static_cast<int64_t>(n);
                    m_boundary_filters[i] = detail::acceleration_filter<Real>(n, approximation_order, s);
                    for (auto & bf : m_boundary_filters[i])
                    {
                        bf /= (m_dt*m_dt);
                    }
                }
            }
        }
        else
        {
            BOOST_MATH_ASSERT_MSG(false, "Derivatives of order 3 and higher are not implemented.");
        }
    }

    Real get_spacing() const
    {
        return m_dt;
    }

    template<class RandomAccessContainer>
    Real operator()(RandomAccessContainer const & v, std::size_t i) const
    {
        static_assert(std::is_same_v<typename RandomAccessContainer::value_type, Real>,
                      "The type of the values in the vector provided does not match the type in the filters.");

        BOOST_MATH_ASSERT_MSG(std::size(v) >= m_boundary_filters[0].size(),
            "Vector must be at least as long as the filter length");

        if constexpr (order==1)
        {
            if (i >= m_f.size() - 1 && i <= std::size(v) - m_f.size())
            {
                // The filter has length >= 1:
                Real dvdt = m_f[1] * (v[i + 1] - v[i - 1]);
                for (std::size_t j = 2; j < m_f.size(); ++j)
                {
                    dvdt += m_f[j] * (v[i + j] - v[i - j]);
                }
                return dvdt;
            }

            // m_f.size() = N+1
            if (i < m_f.size() - 1)
            {
                auto &bf = m_boundary_filters[i];
                Real dvdt = bf[0]*v[0];
                for (std::size_t j = 1; j < bf.size(); ++j)
                {
                    dvdt += bf[j] * v[j];
                }
                return dvdt;
            }

            if (i > std::size(v) - m_f.size() && i < std::size(v))
            {
                int k = std::size(v) - 1 - i;
                auto &bf = m_boundary_filters[k];
                Real dvdt = bf[0]*v[std::size(v)-1];
                for (std::size_t j = 1; j < bf.size(); ++j)
                {
                    dvdt += bf[j] * v[std::size(v) - 1 - j];
                }
                return -dvdt;
            }
        }
        else if constexpr (order==2)
        {
            if (i >= m_f.size() - 1 && i <= std::size(v) - m_f.size())
            {
                Real d2vdt2 = m_f[0]*v[i];
                for (std::size_t j = 1; j < m_f.size(); ++j)
                {
                    d2vdt2 += m_f[j] * (v[i + j] + v[i - j]);
                }
                return d2vdt2;
            }

            // m_f.size() = N+1
            if (i < m_f.size() - 1)
            {
                auto &bf = m_boundary_filters[i];
                Real d2vdt2 = bf[0]*v[0];
                for (std::size_t j = 1; j < bf.size(); ++j)
                {
                    d2vdt2 += bf[j] * v[j];
                }
                return d2vdt2;
            }

            if (i > std::size(v) - m_f.size() && i < std::size(v))
            {
                int k = std::size(v) - 1 - i;
                auto &bf = m_boundary_filters[k];
                Real d2vdt2 = bf[0] * v[std::size(v) - 1];
                for (std::size_t j = 1; j < bf.size(); ++j)
                {
                    d2vdt2 += bf[j] * v[std::size(v) - 1 - j];
                }
                return d2vdt2;
            }
        }

        // OOB access:
        std::string msg = "Out of bounds access in Lanczos derivative.";
        msg += "Input vector has length " + std::to_string(std::size(v)) + ", but user requested access at index " + std::to_string(i) + ".";
        throw std::out_of_range(msg);
        return std::numeric_limits<Real>::quiet_NaN();
    }

    template<class RandomAccessContainer>
    void operator()(RandomAccessContainer const & v, RandomAccessContainer & w) const
    {
        static_assert(std::is_same_v<typename RandomAccessContainer::value_type, Real>,
                      "The type of the values in the vector provided does not match the type in the filters.");
        if (&w[0] == &v[0])
        {
            throw std::logic_error("This transform cannot be performed in-place.");
        }

        if (std::size(v) < m_boundary_filters[0].size())
        {
            std::string msg = "The input vector must be at least as long as the filter length. ";
            msg += "The input vector has length = " + std::to_string(std::size(v)) + ", the filter has length " + std::to_string(m_boundary_filters[0].size());
            throw std::length_error(msg);
        }

        if (std::size(w) < std::size(v))
        {
            std::string msg = "The output vector (containing the derivative) must be at least as long as the input vector.";
            msg += "The output vector has length = " + std::to_string(std::size(w)) + ", the input vector has length " + std::to_string(std::size(v));
            throw std::length_error(msg);
        }

        if constexpr (order==1)
        {
            for (std::size_t i = 0; i < m_f.size() - 1; ++i)
            {
                auto &bf = m_boundary_filters[i];
                Real dvdt = bf[0] * v[0];
                for (std::size_t j = 1; j < bf.size(); ++j)
                {
                    dvdt += bf[j] * v[j];
                }
                w[i] = dvdt;
            }

            for(std::size_t i = m_f.size() - 1; i <= std::size(v) - m_f.size(); ++i)
            {
                Real dvdt = m_f[1] * (v[i + 1] - v[i - 1]);
                for (std::size_t j = 2; j < m_f.size(); ++j)
                {
                    dvdt += m_f[j] *(v[i + j] - v[i - j]);
                }
                w[i] = dvdt;
            }


            for(std::size_t i = std::size(v) - m_f.size() + 1; i < std::size(v); ++i)
            {
                int k = std::size(v) - 1 - i;
                auto &f = m_boundary_filters[k];
                Real dvdt = f[0] * v[std::size(v) - 1];;
                for (std::size_t j = 1; j < f.size(); ++j)
                {
                    dvdt += f[j] * v[std::size(v) - 1 - j];
                }
                w[i] = -dvdt;
            }
        }
        else if constexpr (order==2)
        {
            // m_f.size() = N+1
            for (std::size_t i = 0; i < m_f.size() - 1; ++i)
            {
                auto &bf = m_boundary_filters[i];
                Real d2vdt2 = 0;
                for (std::size_t j = 0; j < bf.size(); ++j)
                {
                    d2vdt2 += bf[j] * v[j];
                }
                w[i] = d2vdt2;
            }

            for (std::size_t i = m_f.size() - 1; i <= std::size(v) - m_f.size(); ++i)
            {
                Real d2vdt2 = m_f[0]*v[i];
                for (std::size_t j = 1; j < m_f.size(); ++j)
                {
                    d2vdt2 += m_f[j] * (v[i + j] + v[i - j]);
                }
                w[i] = d2vdt2;
            }

            for (std::size_t i = std::size(v) - m_f.size() + 1; i < std::size(v); ++i)
            {
                int k = std::size(v) - 1 - i;
                auto &bf = m_boundary_filters[k];
                Real d2vdt2 = bf[0] * v[std::size(v) - 1];
                for (std::size_t j = 1; j < bf.size(); ++j)
                {
                    d2vdt2 += bf[j] * v[std::size(v) - 1 - j];
                }
                w[i] = d2vdt2;
            }
        }
    }

    template<class RandomAccessContainer>
    RandomAccessContainer operator()(RandomAccessContainer const & v) const
    {
        RandomAccessContainer w(std::size(v));
        this->operator()(v, w);
        return w;
    }


    // Don't copy; too big.
    discrete_lanczos_derivative( const discrete_lanczos_derivative & ) = delete;
    discrete_lanczos_derivative& operator=(const discrete_lanczos_derivative&) = delete;

    // Allow moves:
    discrete_lanczos_derivative(discrete_lanczos_derivative&&) = default;
    discrete_lanczos_derivative& operator=(discrete_lanczos_derivative&&) = default;

private:
    std::vector<Real> m_f;
    std::vector<std::vector<Real>> m_boundary_filters;
    Real m_dt;
};

} // namespaces
#endif

/* lanczos_smoothing.hpp
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
*/