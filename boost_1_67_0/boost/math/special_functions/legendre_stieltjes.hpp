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
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
*/