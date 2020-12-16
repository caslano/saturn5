// Copyright Nick Thompson 2017.
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_LEGENDRE_STIELTJES_HPP
#define BOOST_MATH_SPECIAL_LEGENDRE_STIELTJES_HPP

/*
 * Constructs the Legendre-Stieltjes polynomial of degree m.
 * The Legendre-Stieltjes polynomials are used to create extensions for Gaussian quadratures,
 * commonly called "Gauss-Konrod" quadratures.
 *
 * References:
 * Patterson, TNL. "The optimum addition of points to quadrature formulae." Mathematics of Computation 22.104 (1968): 847-856.
 */

#include <iostream>
#include <vector>
#include <boost/math/tools/roots.hpp>
#include <boost/math/special_functions/legendre.hpp>

namespace boost{
namespace math{

template<class Real>
class legendre_stieltjes
{
public:
    legendre_stieltjes(size_t m)
    {
        if (m == 0)
        {
           throw std::domain_error("The Legendre-Stieltjes polynomial is defined for order m > 0.\n");
        }
        m_m = static_cast<int>(m);
        std::ptrdiff_t n = m - 1;
        std::ptrdiff_t q;
        std::ptrdiff_t r;
        bool odd = n & 1;
        if (odd)
        {
           q = 1;
           r = (n-1)/2 + 2;
        }
        else
        {
           q = 0;
           r = n/2 + 1;
        }
        m_a.resize(r + 1);
        // We'll keep the ones-based indexing at the cost of storing a superfluous element
        // so that we can follow Patterson's notation exactly.
        m_a[r] = static_cast<Real>(1);
        // Make sure using the zero index is a bug:
        m_a[0] = std::numeric_limits<Real>::quiet_NaN();

        for (std::ptrdiff_t k = 1; k < r; ++k)
        {
            Real ratio = 1;
            m_a[r - k] = 0;
            for (std::ptrdiff_t i = r + 1 - k; i <= r; ++i)
            {
                // See Patterson, equation 12
                std::ptrdiff_t num = (n - q + 2*(i + k - 1))*(n + q + 2*(k - i + 1))*(n-1-q+2*(i-k))*(2*(k+i-1) -1 -q -n);
                std::ptrdiff_t den = (n - q + 2*(i - k))*(2*(k + i - 1) - q - n)*(n + 1 + q + 2*(k - i))*(n - 1 - q + 2*(i + k));
                ratio *= static_cast<Real>(num)/static_cast<Real>(den);
                m_a[r - k] -= ratio*m_a[i];
            }
        }
    }


    Real norm_sq() const
    {
        Real t = 0;
        bool odd = m_m & 1;
        for (size_t i = 1; i < m_a.size(); ++i)
        {
            if(odd)
            {
                t += 2*m_a[i]*m_a[i]/static_cast<Real>(4*i-1);
            }
            else
            {
                t += 2*m_a[i]*m_a[i]/static_cast<Real>(4*i-3);
            }
        }
        return t;
    }


    Real operator()(Real x) const
    {
        // Trivial implementation:
        // Em += m_a[i]*legendre_p(2*i - 1, x);  m odd
        // Em += m_a[i]*legendre_p(2*i - 2, x);  m even
        size_t r = m_a.size() - 1;
        Real p0 = 1;
        Real p1 = x;

        Real Em;
        bool odd = m_m & 1;
        if (odd)
        {
            Em = m_a[1]*p1;
        }
        else
        {
            Em = m_a[1]*p0;
        }

        unsigned n = 1;
        for (size_t i = 2; i <= r; ++i)
        {
            std::swap(p0, p1);
            p1 = boost::math::legendre_next(n, x, p0, p1);
            ++n;
            if (!odd)
            {
               Em += m_a[i]*p1;
            }
            std::swap(p0, p1);
            p1 = boost::math::legendre_next(n, x, p0, p1);
            ++n;
            if(odd)
            {
                Em += m_a[i]*p1;
            }
        }
        return Em;
    }


    Real prime(Real x) const
    {
        Real Em_prime = 0;

        for (size_t i = 1; i < m_a.size(); ++i)
        {
            if(m_m & 1)
            {
                Em_prime += m_a[i]*detail::legendre_p_prime_imp(static_cast<unsigned>(2*i - 1), x, policies::policy<>());
            }
            else
            {
                Em_prime += m_a[i]*detail::legendre_p_prime_imp(static_cast<unsigned>(2*i - 2), x, policies::policy<>());
            }
        }
        return Em_prime;
    }

    std::vector<Real> zeros() const
    {
        using boost::math::constants::half;

        std::vector<Real> stieltjes_zeros;
        std::vector<Real> legendre_zeros = legendre_p_zeros<Real>(m_m - 1);
        int k;
        if (m_m & 1)
        {
            stieltjes_zeros.resize(legendre_zeros.size() + 1, std::numeric_limits<Real>::quiet_NaN());
            stieltjes_zeros[0] = 0;
            k = 1;
        }
        else
        {
            stieltjes_zeros.resize(legendre_zeros.size(), std::numeric_limits<Real>::quiet_NaN());
            k = 0;
        }

        while (k < (int)stieltjes_zeros.size())
        {
            Real lower_bound;
            Real upper_bound;
            if (m_m & 1)
            {
                lower_bound = legendre_zeros[k - 1];
                if (k == (int)legendre_zeros.size())
                {
                    upper_bound = 1;
                }
                else
                {
                    upper_bound = legendre_zeros[k];
                }
            }
            else
            {
                lower_bound = legendre_zeros[k];
                if (k == (int)legendre_zeros.size() - 1)
                {
                    upper_bound = 1;
                }
                else
                {
                    upper_bound = legendre_zeros[k+1];
                }
            }

            // The root bracketing is not very tight; to keep weird stuff from happening
            // in the Newton's method, let's tighten up the tolerance using a few bisections.
            boost::math::tools::eps_tolerance<Real> tol(6);
            auto g = [&](Real t) { return this->operator()(t); };
            auto p = boost::math::tools::bisect(g, lower_bound, upper_bound, tol);

            Real x_nk_guess = p.first + (p.second - p.first)*half<Real>();
            boost::uintmax_t number_of_iterations = 500;

            auto f = [&] (Real x) { Real Pn = this->operator()(x);
                                    Real Pn_prime = this->prime(x);
                                    return std::pair<Real, Real>(Pn, Pn_prime); };

            const Real x_nk = boost::math::tools::newton_raphson_iterate(f, x_nk_guess,
                                                  p.first, p.second,
                                                  2*std::numeric_limits<Real>::digits10,
                                                  number_of_iterations);

            BOOST_ASSERT(p.first < x_nk);
            BOOST_ASSERT(x_nk < p.second);
            stieltjes_zeros[k] = x_nk;
            ++k;
        }
        return stieltjes_zeros;
    }

private:
    // Coefficients of Legendre expansion
    std::vector<Real> m_a;
    int m_m;
};

}}
#endif

/* legendre_stieltjes.hpp
IsLzznsztlp34jyMPuM4DnG8rjHem+X9HvN9/2+d74Frn7xbaH8u9HwIUU/nqx+WaSe8b31gluP0TefbuHC4dt1w45PZL5qf8H2CeaeNN6ern43TTPnA9Vrjvu/xPNSPm2WcMPES95v6PlG7Zqz7a/Us7Tz1QOJy31czb71psnrgE99j9bmObtAe3WB9wG+1N/SDN690nBL0K77rejduu/E+46z5+hOF2i3Gj7d0mIcYa5zAuoNN+dp31dYH+pwztSuXT/BX/YVp633+N1y/z+vfD1h/UeGfR/jvrnb9xxsfGzxvzZfsO2w88auhfpfA+T49mLd3PWtPj64N835Fx9f41/YxnqcPaweGOn7Wd03XT1jyfIjj6fn6N8/jrdaVlesnV4f4733vd4P1jfolDVt8b7HTONQ1xiu05/d6D+uSHuNMxuUWGp88+NMQ14dx1DzP/wT1gPn4Lcb7YoxfzsrUnr3GOJ7x2E0TvFfGuFr2z/T73jP+d9y40T36sXdrJ/xB+yHLdbxEv/9j4563awc/7L1Jc7QHH1KP7dZP9ntbi6Y4njM87x8LMT4VYv5CPXm7frt6aJ7x4pGfaucYd9rofC10P8y4T739X/fxWu1E4xb9D7tfwjzvzLMlD1Nf5qnP/2GcPcF88uf0o2Kd12977sUblx4VtK7D+NZ016NyRyQYzzY+EtPkv/+t6/FB52uZ573nyz7Pl5PB85WjXeb5P+9zzlOycaQt5vNu8pz2vq7wy9V/5rkbtFPD9cN6jW/sWeg4G5dKVK+veN1zTH9vjvp6tPH7EOOuqcZdj7uftsdrNyw1bvWs+6XEfNdX3IeL/HnXzfHVtjdSO8K42tLzXCe/8XwpNV5nfGJmqO8bZKsvJhmvud59E2v+91LHX30x6wfqy3XaO9aLhbYZv7nd/flz9Zv+yvZkx7nDONtL5ke1b+I9h8KjtNdC/T6D972k6ncvVy8+P8v9b91ESJX+sPGiZOvVpgzmlf4b5v3ixmuMA401j7pcO3bRd41zGQed9qTr8ZDreo/6Ls48+Tr9LM/Tk296Lr+nHr/bOJHjM+OAdsavrdP7qXr4Qf2BOusvjmqfHDYu8nSo9ez6b/2ec6fcF1M9l6e5H3L9uSXO0xR//cj4QcwQv1/g+zcbjENs0y7UTs02/zjWcTju/XQHT5hX/Yv76hXtuQWe87Wh7gvfdx9p3P997Y1PHcdO60Resd7N+EV2qn7BRNfVl1w3FzuOv9Mvudxfvbd8n/ngbeqdkz8w3ux8Hp2jnn7OPLvn9f59w7TTrUdI0t7OcFxusp1T2jMD6hvjkb1/tF81nvs/CTH+Yv7jD9oNjtdx4/0HfB9nz0TX6e3a4Ve4Lt+wXmOF+k49sPHfjmOd590x7a6PQ72PyTj5BY5/qnmfj7STP2cefLTP82P1xS/DPQ+d31b3Zbjr8Drj+fNdD/Xh1j2r19T/S2Ndhw8Mzqv7vzjod2Wc11rH4xrr3HwfZZ9x6xj9yMOF7kvrD2L06+c4T6EvOC63BM1jWr+h3XdEv2ybfvpC/a1ts3yf7wa/n2zesb/Cex4qjZt+Ocz7bh33I8YDf6zcC5zv4+qZG7V/L9d/v9Z+9rkvretdMtr3V+923pK1f7boXxSo7/9snqfCuoGv6r9bLxl6v/5qhPa9/sEB+/Ou/uZe33OM13/Zrh2a+qznsHmk9YutT8t2Hez2PNhkHnKz67fAuqH77Gezf/8387Y7tbP9vvzuFz13/ma9xC3WqViHMcc4zUHHtf9l4y4xPo9xlCNfVf93Gy+6xviQebjlcebvRur/HfM8+I5yfS93/RfNf1yk3r1df+IK7UrzmOvP1187ZP378/o=
*/