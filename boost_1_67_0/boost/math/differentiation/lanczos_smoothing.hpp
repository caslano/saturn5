//  (C) Copyright Nick Thompson 2019.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DIFFERENTIATION_LANCZOS_SMOOTHING_HPP
#define BOOST_MATH_DIFFERENTIATION_LANCZOS_SMOOTHING_HPP
#include <cmath> // for std::abs
#include <limits> // to nan initialize
#include <vector>
#include <string>
#include <stdexcept>
#include <boost/assert.hpp>

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
        BOOST_ASSERT_MSG(abs(m_x) <= 1, "Three term recurrence is stable only for |x| <=1.");
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
        BOOST_ASSERT_MSG(k <= 2 * m_n, "r <= 2n is required.");
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
        BOOST_ASSERT_MSG(k <= 2 * m_n, "r <= 2n is required.");
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
    BOOST_ASSERT_MSG(p <= 2*n, "Approximation order must be <= 2*n");
    BOOST_ASSERT_MSG(p > 2, "Approximation order must be > 2");

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
        BOOST_ASSERT_MSG(spacing > 0,
                         "Spacing between samples must be > 0.");

        if constexpr (order == 1)
        {
            BOOST_ASSERT_MSG(approximation_order <= 2 * n,
                             "The approximation order must be <= 2n");
            BOOST_ASSERT_MSG(approximation_order >= 2,
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
            BOOST_ASSERT_MSG(false, "Derivatives of order 3 and higher are not implemented.");
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

        BOOST_ASSERT_MSG(std::size(v) >= m_boundary_filters[0].size(),
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
7OM7nXBY30jsN8l2mnkSaOGWx6lVdZHQv9/uY2dPVW2/9qQjilYZkrE2/0nMBFI9mn8hZYlDeSauiuGpqoZ0Kursxp8zPabjLlIFYB/EPzhX0plWp+PDJNaPyKIxQzlPL/nSGN6mSH5oGVQfKtaNjrZXlUvlGpCkr8Kzi6y6coeafLRTIFjlSB9/t970WlBL3xhDUQj98k1x+PHPJTaqsNPydWGbj/27GTjyDjkzD337EsPMajeXtWJGuN7AUeOhOANPMycxR43VFxRcE3B5DoistwURrniYhiJ5KCdzb+/GS/OchC/VkXQeb8/nS3BQoYvK6EA5EqO9emunL3vl5THixKXcbl55X9tUUn1iR6aN0CYT5rny/VZ7GQNCfuBtCNdw8IwaAjcUrKSUx7QZInNBXAq28IBB+A9uf5tTI20G+SfUqBq8qs4sJY003og7ijxnfIgh/shrKUidvXPnkkkxQWwcqEF7KGPTu8kIztv3XnHBGeenCbMlcEoVmn+I7OShSlHz89KyMHeg58m+uJY8wEAqbNjGxDoERQzov7wmC4/C/7bWRtlO+YZ40Y9RbwMD3wcScmnR/GBAJC2vIU6rtW/smEXpvUkTedSkaICDG+2UG+rsLSkBckFPPfh8YmR+VLy/S3zx0ELx5UpW+xD/eYKQfhGK+HHMn8IL0hOWBRZDmibF+8rjLM3dX5YLcwQCjIi4FHDquPVIWjo8DzwJJATHc4tnJtcl4AE+b8J4lrHcx7tY2H3y6D0krqwdkeyyHevI28VJ7WBbb+vmiNoSa5tV3IIDnDGJS+XQ349gHxNkehHCxTHudrq+3FjFNFhc+ft/8klHHSZC0qWQSXVM79QimI0vXNMY+KOlI1nPcNO0vhzzwrZvzMdg0z/g16POyg2q04wQEOuPAPMic0yGuLubjay1G9ru1nDpoDSNgx9nFvN0FfWrd3Vc4yFZ4TGGZUCyZmJgmW8kaw1KE4ovjgcwy3MB4qcOQGev1+neJ9SzRyJdZTExZluRGXDH+a51DzDInIsudQ+1Bwnxwqlrl/sngD3SeTW9ePvF6q5Ewhh8YNyZEkxjJdvJ5eTT/hv+iQrZr2LrPW6gCrpgZ58DewVotPfakPtEER9ij/uFR8MiExKHhoURvylBpBadEslk+VDhmEVitKDwDfSDqbBaUZCFpHu8Q6qZzfakh9q65Cm2ndbvhsiGM+zRz+vZvPySfuVS8WG8dKG6E4X7etG6BkDQr1w1LcpIDCyrSdUaMDAAVlWdBxLHOwdzYhFimkrsPFRU5z+4Hc7nyPGGP8/bvDqTodOefSDzCOoneeQkxXzXESwWpSIk+ZilUfdbkhTWILoQUuX6FwatoBeVJ18dk4LqYmR+WJ92U02x5LBxUqQ99TbBHClIllxaSpIXVoQDILjucacNqdsuLGQMfnKy8hNNRZhlTZPP4KQMheuHYkrVymocnqaEm88dAgqLL6bNf9ao6phu0xmzZ8M0ek2GzZ9VqFqVlgk1B8kjK7Tql2tUndcWgiY61DT2QC7ASfFPFyPG5fs4JVHc/RNuKt4wEe2b9j8PUJmtEyHIJqijmFhrJgADoHiNWH8RJFqhMXigRHhTuPby/OOziZ5GVTS3jXz+cU1zbZhzxG2bvN1F6ur8iW5wZ3+cIewlJ6u8iyFlrmizyjHlQhsdBcWyh5oUjhbdspXK6Dx9DZCT2TU+eD0SmvDOfxcAr1OblMQi2Qixq7pw9Q/Hs3ginvaPiCd41nW5O2kj1U3Snp7MIPh+kmDqv/AcjtiGF0INWRH38as6dG/SKqNdfAwqLoIATLBAjunSCqxoeX2bmIsOUjC7kUKzCA6S/pofSSrEKNW7BJCUiw9ERZE742C3SttMOTmGtzuxKosIlKmgHTz7C7lHD97uN/Xmu93Ix50mai9a8FINtK5TOFEoVm0CVodWa7qsvwC7IkihgoEKklQsACcTJnew7EC2W980GEiYhl63cpDvhDmJPmQDL4cR8+vy+U4PzIj/8aQtYqY3wN93exoTXgNCSFWGEMIfuQ52LfniUDH8DhwpWVuTxKxuov8z+bjYwADfftOBcc/R8mUO1SX6ELJzMvSH7SU/FeVH+ZhpKuUlnPJDQPhMXP4d/+oT8+sjvu/b9xd9AGM2zuEDa6ZwREYFK22fzmFhJIY5e8iKw8jpV+eXmarB3uYeRNXj9EmAdqUYPXk8mag8Dn+gH0cI6cUjbyTay1ZNDI79jSTNq2k8fdxo/I/UvgraPvlCByAYFwkjdMAvnhUOx1cCxCxGYgLpGgB28tc0XBDn5OLpCBrgP+3xHPnZrdOUrhgxMTjjetrqb8RFe6w3xTU7bSsHxKcLzYE5pvmPIFioD6E+c6yxKe7UCevAW5TDzXu3PlnBYOdYYma6IDozjmXaty4qlmoWJVzd7SmujabF86Av3y/yBW/POkuHSoGcHMpcyMMzBVQ48NBoFA+x/ZdjNioaRpv/ZIDGzp9p1dQR1X4lQlbYfQOLp8/G1yOZQOVTKBenvpya6ZwVI/GhStAhXpnLC5SY8U0D16uTPwRcCSHTsVCRzIGkE3iOlJy/S3KI20odQMvYhd/NhCTvsBsTmMyyj29+owPtKQMcFUFJX5rZIFaQd5SCXUQDBGBz8pHvvHO/8V2YJzWfc5SurAUppR2I65x5T/EZm5tNHgg1MIl7a51PRhVNy295ik6HdbqOFwvUweB5PUzTYjm8vOTLAuZaG9tdTBv6bchoQa6TvJr1uXms9rVzhuAuoa51xKVTHXrGK35DlW7/lc6d8uih5p3ni8I6DhJ1j+VMfE+Iy38WHzIJHzHu2+ftvmhabmwWJzN4k0x6+U4R7CGOjj/1dthyEzndw9uL69O0BuJHx8YSEhdvuFaIlZa9OtlnJyseULaWMIr+m3QoiI5CfdD5fIGCW6QZWcFaGlwHrEyWEQXPRwliR1YfSg7/tKAsyfxnRZjspet6/PLANh62Vce5J8fNjQP2tquZ3gq55sSnNjU5H3rCBZelk0+SjKQpoze0rYZHXgBTL99voE+p0XYbUpGt6nX4lKPnpMh8zMK+DNYmTMTZy7GzLJbp1SVSCcvtsjD3j22fz1c50JOdbY+V71v2v+gYTyC7lt2UL8ALwhNloVQ0cYb0W83tO9qA5XN/6AjEAFF5BGcfYwpOgzN9keTJoFqRw/CHGEhR4yUn5aNa/jwf2YgHAQ4CDoCcIYE+fWY5G2qO37XhAqaJMY8Vn8nmV7UMIw+8mC+8d/8wi0WbWLwtVnk2q84lakSVk0u0DI2a6gJ3C4lUuSqV87bnoV3GuIVp9mQmyqGxuXFLvgopF2Zu6FNqWyd+SDthQSwGXZFnmKxgg7LtxbaSt1ULvqLjDWx1qBmzHOTMLvV2gg8xuJ8mlMO9R6Qtxd7dy62o6aZB87mRUPhHJFpXd2IYum9KBJS2FHgbb2urCRmwEwF5IKbrLMf9fWdLlg0wcdowlDeNtQgU4GY0XwbuVXrv2SOU0aTefNZYxvMW4YJP0su9FonVXw7uKY3eBqrSi3mea3vtt2WTe66DQ9z+cZ9Ij6xrUSVzjhaL597WlOvs7Em7uqMebfYPxzXACwseMB+WucHOyLR7O6xLO1YhzyU4/DCHJIYDu0aoNZ80W+oiBgfMH/v07oBg28dCsTIp3tM8OqL4VjUIOUYY+nsEnHdKO9sL70IA5j0qItdmbeuCma+9ZwLbuUaqSt/ONQiRyNSBi+j4WLEY8ouj5TICETLQWGnSybtXoAru5v5wxLLhK/g36ydtMpc0z6gCovVmplPnEKxl9qpa2LnmChErcE3k4TCTrPI0OEm54rbt+ar82cqomx3JeRsWvzIXU8IU+QhXYVW3vu+u98+E/gNp/RQIxOSjEN8SjqUb1V6WN2aVRBhU9ZgZgqLD6Ur3Mq0egWFshyBfmIy9zTpPLj5AAW+uVXv+tlIsc3yawEF7sO0BUuW6ERIrtlOg89/6jHSi0UapZWIiqMjpg8HIOsdlebKMVVfiqPbJBBW/OEJFRkb9C+l8h6BIE6UFMuqggDGJULjwWMxewJp+JeoWttHUEgq/rJItfDih30em5ztDba6JcG7LpVSQ+RJgjVP3zmXJK2uGs0R3e0G2Bq29Ursi9i2n33lSxhiFHluPFyy+K34mWR0qEMPTz1yzYtHnJhKlHWr8hpPcMwLHdxFaNDY+nkbXHVoN3dmSyouqKhQ8vhjSNjIMS1aMj+iOXXUA1FTUXPTON3hsXh2GhhlacZZ8m9V2Cga2AEjTTd5a5WUf7fFPgCF6fCYLyX3PH5GDH6dkQxbJgPIM/XGDt47i+QzkkOEBpfmMcmRgUB1U5F6O5CeUowTgRdH6pKlvEhAi1l9PGK2O/WvE+TB8Ej4gL2MMuOhBHFCjh3nrAm7HrrjflJ3aR/xy6yr2q+6+QZH+y+Da+4CI0yWZW4cr1x29Wv5qLIwNIilje3ywTh6tbEmSx62x+yuTku/HKUuMxe/0BqMMWZXdAyFJh0RbHMO1x7NJ8a8h/9ukJH2s7hwUi9VoR9vEuLZk6f9SP4j1iMhivVIQMkz//RVLhOvh0fHmJci07+eIowXbczdBjqCIJkc5pyzAO6D9dCUqy7C37yGUI9BhVJClf5G2UhlHkoqGNFvqrOsNKUL2Qye0U/oWl8QnzW8U+0qbx64LNUGxYk02CkkuoMPt6UzyRYUUncvTPhM4g2Dygq4O99LntgTbp1TGrvv794Qg4ZAzQY42VGbtCVAKgYESff7SfR20p2bF1WQ5h5TcoXh8aIyR7ppgW2SAiVb53mQ+jurSD9AUKK9YDmK/odaw6re4ErdcrQ3hTz646S1DdXQyEmL02sQeVYKtTzm/53SW2ukmHCuHVIFTtTwlF2b9z1rLkKGonsQ6D/tPDiM59RM4xnUe3Vhb2e8k6C7tGCcjWVVQRh8bF4xW3JGROA6N+VAy5rN4+wD1eovumhUwNl8+2e4YlU0HJJYNvL7f1WLYdJDuw1keJ76eK2zaeT3as37r4Mr7sXp6gkFDixwIvJv7J++cRAJcOSdCNAKIaOEsw3OOHWhJP5bazHWM75ndOLUk5r7k+0TP8KNthh7HQYORdMwveazD23d7RSGdDhUfCYJloIC9RQjrTfPyL/vUtNES/0IfWg3O4iuMiz9cbLAd3ASkAH36eEGOuLF3Z0037uG8iqBl46IX0mYhO7S2aVWSQ7BqrSSN3JY424HZHL9pc5pbvnGDqY4vu3BAO4zcxAcmf/g6rN722EqifHIsJkI8ihLSAbO9gu2XhzQxXqGSaSuQVqqzh82TZH3L4dWb0p4dbuIMFQZsLaFJFHHPMGGeD4Ww7BZSKX7a6WoEWWQojNVsFoQykTa0sI8UF6iaK6E/bBZU6d0dtWL070B3gVZrpadKFhyYZ+149tVpJClUkrOG9XLwjNecM051cbPTX8AOnVuPbbgkuo7HabOzmMNYZXwNt9I3Y+kwsncAH7I7P4SRezPe0yQBQKThe/XsM5ML+gKFWzSnhsc9Zy9fJ4N9Dv0xnbNjPAsGnW6YwsbYfvMtKbSGvn7mJa8UQIUZnDBpJN+FL4qXt370L04dTiDYmfGmF+d7SlCbkcifhbz7hJ7dDcGzNj/f//8HKwPfoMgn4tMAix+gxUuQrHqtRcrNUaseo0Bz94qNG25t1Yrw5wPfWx4I3GvuJBOokS9EZZnd/NG0HZjZYbUSSrjLg/UaILjUTcW8YdhyoWAlmWLHz3pX8rMseV1FKHJMvaMDoCncQ5UXYnwCQY6w71bEZEBnlhehXD7sjvsQzW+ryQPDh5Y7m1NHi06CdduBUUTv2GjUHjBut7QJhMfbpBqVOr+f81bssqo4KmP6pzbsWpUB24XdqNqEkvteFYSm4fu+8JeK+ynnEz+FeOLsjdswoQIdTAKLUVwGcu7D4NEcikQSj2H5k3QUq4V9InmeQeVpSYhwb2BTjxvidzCwBx3TPa5UdDfa563hmW6JEwkIGwYjsi9pwWx0rPZg8N0vYwFn7qLw1bcn5MkD1btKISyQcB71M8kYEq20X0ofy7P20651sGr4Tz5wU+foFS7gwxeJ6vYuYkVJkdqXMP+tjAPYVNXmPeqaxTjqC+VEeRVtIuPeL9hLwQ+txHzPEEJmWq1FhuvPNN9/Rud9djfACTVTcd3mJgAbt+4U9mX/AxeA6H9Jsvl8VjD7OD78cHaO0Z6I4TqqbWb/ij2RUE75wM+/ZoLo67PjuXxZs2I/v6bNXOwX1WhqN1Bv/6UMzbCHVtvRFjA/vrZ9OUDU/9mHmEnuKbKoeqXCrajG8F3sT9XVZkRqauJrOb7v6cZPzy6WdPQcF+Y61HbK2T4bKn935ueeoTBV/yAaYeO3f5fqTQzR4/HrbcsTzOe5p2t0EzqV0wizCJDc0Zs1OQy1r4QjZK0V22sv79XTV2N7SvHzti4xk4mdsPUo9DH/0WeEvLSYyERShTAwNE7IifgK6hwR1f3dLP9aYeZRVnhuApUck6RVsqqeYlOh279obbpTw+9VaW2l9mR1ab+t2uuX/ylY94+9NsTMx5MFs+tHLO3ja+kKg6F4Sk70V4S/tDjRYs35KNVMjq47F+cwNlbYZkOVb/kdIZUPJX/xTMPnzIAS/MHn8g8f2QNtAXwRfuS4XaSFYfHAKWFrLQTfQ+xYiM4mYlS/ENclB4HorRzCujmQ+V/CVgcOG+hsqERG1KWXJP359nmGanJC/UxOBd10ldBZQXwc7AL8Fhjf/fWA097dtLxd9F2oiQq3hFLUP/4Z+A8dGxknLPmKdktjGqz3DrfdoIqXNLFn7shpXb9HAOu264C/6KmiQOABEohlQvFMZF41j2DanRcJsZBfx1Xc7vcLounZ+LXAdOoWdoT71jRgcwC/B7tgL0sxq3RrC6RsuRo4wig4qG3pLe/oF847xBtLyKv5CsLjWh9Wk8AjuyohRfWHVmiGuAbxyfpAyw2I/YxavE/FThVkVZyJ+ri37p6fxlgPAbiDDT4B+n/jHG4QRWmTDDjWQOKWfBvHzAc2dvB3nyvPSUmWA7Lxws8x9SRydZbrtH+tV9H2CBlBAu4uRWoSVvuHa9yjYwE0DtTBvGL/87A88cGjaIMEj335H6UYmKeadzi6WD/iZecWCOhWlZuhS/yMrAQz85USS9IElREMtzHVnUb3laV3sto3tCinSekkC1+XJvXqZ90E5jDs6n7aLv0V+/1QQjirurud6yGvuBjYLYFdWwlA/EY64jyOBimutTwNtFmVxWfMRlZa67A1THM1KbNefQSB+EtnXYhhPZmUza+7DiQjo7p5IXZVcSnGxy5fyzbdpuyWImEMnWAYXqFynYJPralJfszV1/FjatibjVVDBSs3lX42DI5SaB3aONb+PQgXfbxuKwz/Tp8B4rPkhpe1HnAwT5z8i7Vnwb8sYs1cyRTYfmU69y1UhckD0s3gAgbXswui300xxA6uOUTNuIcaEBd/3j4LxN5Xw00OmpvXDmUeedn1ouUY9f9zBlpSKEnQGGNfU1NJ0XKgOz96BKm/7k6NxPAmfP71KGgc3IM9amOO0fIbWoGDJ5av6mfTIAxJgrh8ZLUk2pRIdDqpeUY150RhnEq1xetqvoskr/wVXG/RU+7BpMR5u1U5nhfrVPbDrDW/kBrrAIG1Bg7XmFjwVRij4UgedWags5GFZ5jjMWJxN7otMAgDoh355vnWb79r7Tul2BTzefzDEsAW1k4DndNSWVUX4dqzJ5MQptnndqgeumM3mxxMeN7bKGMp1rAzb1niOQVmKW08CQgKFkOlxnZxvbAw9vb2mk+fu7TKevyaNyckaifThF7/RYzpQIQEaqoIUQPgFRaScNUYcCol6rBT44ot3JyY+XV0fFzQvMCWiekG9cPtNV0o4Ot7bq6wYtXfPnY/PIiQXBiVhi/aXdEfp//4AT727jRJbL2DDMbaLc8FTsJi+oowMAaFcdRFhMKSoHZ9AwjhVNZCjstwVa6x8Pysl5M6sQeFkr+TDJMSd3Oyw8+1hcq1EULe7YnmvOChmp6o09iI0nAE3mdV0XNv/Jpv/03Hn26QP9jd+PJ80UJRMEf9VGL8Pa0/u3zE93yhlmAisiZ0kkBwhaVdpn6WKI49fkrEhgl4ShpudUa7loLntARN6FUNo6Up4W63743QmsUfhgWyhG4LL0E7/ULbwr3EslcnrtyXDttOyXnOK3dCAyJ3HUdZarqzCjOygyxTsy+XyN4oxnG27GmmYJzw6x35wIVEwTsVo+0XAOXlc4GVZ7k6uf7/TT2k4kcuj3FLKrwQw+YskB74Oo17PgX4abKWYosqyCiCHAy/78HJ7Y2hcFL/wwhg9cl2DVEztlLJ+ycmoIxEc2NlUyuajBvdWS8fEl/VD4N0dzit7c13Wzkg7X4G8D537MBp8vLWMMbqCCduqqvww7VSVNKDI0ER4VuK9Suff4H7YQtHhuWk6GFIM+j8REy27oUKZh7RZ8ujo4QoZMc4xDeS70ad60Z6bfseQ7D62iV9sUzbeLRIqdgHfvRHpu6I15sNyVmH+2DLDle4SKIog+NqV88qzNdfdtKcuTfwaKQOKwgSTOoEuzvZ+Yw/y98wH0xdbdGvb4oVL+Dho8PGW3Y5bJ8+3xRn9UEmQSwlPO3xZIrVNkLyIYLA50CS4yR/LHabW/tu9B2i+jWYPOHtajOpukp1kdRCFUeRERkjhtV9vMgBUvt7j/02AQ3mlxMpbFOTfaG3LBUpSHVXJsnU3mXZTcln5Zin0eVnTItehIlvalm41TXBZygC3leCO2/mmOewIdbNxiALZVLMwQRfNSM1VeC3GUeU/kTQASce+SGQ2w15snm15Gtvs0KxJIO2uZDXmId4h8co93DyYOcKS2PR0tjr8Wp11N3wWZHcl819LcaWOYLHFisXHBAfo4KGcR4ZkhLb1w/82RibadtewMk2kNfMpb+8eHiic8TqGFxwb1tKG/1SB3rrXMgK9PNacE9O4NDqdZP8NuZeW5J16IqSRTbRoWKxKET0kDHfz34JAiNlzuoxCFI4k2gHAVhOqoxO944xzOAkKrLCBEyr0Ncwqn8PoJ8359JWc1KV0z1Yf+/Akg1nhU9xrl6lleuN0FABiepACBB80ufwve79N2qn9MPBtYaajC4t4P5vMdkOLYk=
*/