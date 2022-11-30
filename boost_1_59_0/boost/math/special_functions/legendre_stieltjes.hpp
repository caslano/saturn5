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
            std::uintmax_t number_of_iterations = 500;

            auto f = [&] (Real x) { Real Pn = this->operator()(x);
                                    Real Pn_prime = this->prime(x);
                                    return std::pair<Real, Real>(Pn, Pn_prime); };

            const Real x_nk = boost::math::tools::newton_raphson_iterate(f, x_nk_guess,
                                                  p.first, p.second,
                                                  tools::digits<Real>(),
                                                  number_of_iterations);

            BOOST_MATH_ASSERT(p.first < x_nk);
            BOOST_MATH_ASSERT(x_nk < p.second);
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
DujupiEtqvWU3yRjwhF2d00Kxt6yNwZCAAUs+tMX+k3sgDvviQ+T6hk4DyJvosBf7RUUBfvoE23VjrRmqt0OQIpdQhxt24Cq4aAj8X0vKtX9QRwHpQutPyypmVSz0UNkVoIsR0AxVS0SEEe23ybu2DF7MzcZDBmCo9B14oZ0rkvImPxOscW4OtNVVr3OOZTfzCenEj7LuA24SMPW4hM1MQ9z3R0ORhIjzL+gt8VUJgOajYZ7/KVwJxtNakrt3ZDqJlOONh4xEg7whCNzOcHElnqMOgf7fRtvsaY8IAP3j02wyUkGl0udbMgAEaWWEDNFlMK/82ofoeJT+wDeuM+a4blFS7pyJWLRNsng4feykc6/NKaJQaIzx9TyCeiUwjAiiHRVMrlXHuuU9jCnaKWYC9pNtSEyYPlZcokQi2dSHC4kPlYd35fIJ0l/ciw+gZInIk6qXRdl4nL7unWAU4xelChzJHUkwrCNEBnJD/3DwdlSWB1N/L7369guGzMRbEBnEqM4h3XSMiNA6sZKxycKXbI7qAqxMoHLrdionKdSq+aSGdF9gnT//PMVFEBygEBTcFWJEXSaIA90uW96aI8oUFPx2tFt6CK1tb1/YP6GBwIISwjcluUzCcaZB4NmEt9ljhcriGozEWOH+cCOPBAiWOBiY/Vp3pFz7+ujHQGl3RRvGJJvKk63fA8ejy3+UStqBiF4uhM8uOEDW7Hq7wxnaNKn8/c0lkQnkSNVpxI4qO3gBHB2ah5jxy0+t12uFdWrHlYNyTV6wSb06IklHn6ZuNEa8X6CZ4jtnfluIl4qW7kz0bhUAQtoB2mytgwZr0UbvQ30njeYZ0YXeKzDFMfcYMJ2Vk2dhldoQQx2o9yzaZlvLUhW9LR2CnQUfxktWKMAtUXCz8h4kOheFMo8LDFVGo8V/qshEujC0+nBtGqBC75SbuaOPYAqyZGl3B1Hj31IPXHgueanXUuu7XkAXE1HUBxCBxuKab3EPua6xCwWY2x8iM7Sp4jeS0130Cz/l7pHE9nH4c9eKnapvgLvZHRhDfGooKN3AbrO7Hrx9ETds1c1t9wtl7MnfUM5DVALxqvplCdrd6emXJqETQjm0VBqmqLtNeJfvhUOnJAlycIDF2GgPKO0+z+KPzk07/9c03mD0mxz6cf5PFQmLfMZpoFyV/inwSQlwqR9t2MPwuZJfS68hiBSl+8nFzkW8fG4evVswtXk2g8WCdAwyYrwxuvoM8unGgtYWAvX3F9XhaLOZS1k74ssXtR5hgfIumakudD1F4RWgbylQrLanlMWm72ihM+q/27cwuNUnxSkgKzbD7TRsLcBxX+yhaLRH2dAstnAdE8PLjzZS34+p67E7zSCD9mKWtk1W6tKVnTHVt9BIZC4AdjNGou5PBaw0VF+JKlhHmGY5sebLuKQrOPGDJOvVO7yFVJziYC7vVGsm1mPCJsStOq78Y605tf2vGD0LPjcqRA4EfMF6Y9711W9Y89IJF8qhyYQHrQ54JysdAxsnITKWg5S3n/EF8nHBuJVtqfYNhFxBWr4EzlKrLq+9uoCNjCge4Y6QEYidKcA93BqEY+AtqYE3UmlnIbqWvK9shfTHL2A+tgK2c854Kco4ok1cqs+7EBapP+wCiafMv9AGWsX9ADV5bKl3ey59Klqc5UuNE8AX7NK5wqrwmzX3t5np0c8PEw4JNq4r9ij3Z36kPpjXjJIds+DUrJRnYJ2TsVu5JtILwZyiZtnvVmPFxfxEG+PYEQsD6x2F/BEtFR1YIxuF0Ok7xOxdZHlFhvJuHfOhRXW9Jz3KQ81A8MvJQZhc4buzaLeOVkP/7EzyqFrlfyyLZYdfSBeu2ghpFDX8oxF6GhJOjVf44HloWLJxK42gV2sKFZ2tBPhl6Aaa5vr6858NaFwxT68SB4p6lS/42MV/NxoDjz+HPt78qewHn8hD+tKzNcQ3TAFYiIFcOezXMZnVqb3sK0nqogQPDYcr2kuqgB6hOJVp2sq0BFFwMnJInxxLmvp8ioeO8uDM6mMQxre6zvQNzDFO7naGik0ON8Q5fa7H8fOD7FXR+bU9CSH+06U/x/bKoB3rL8JWZbEN3L1a+oxsUkZ3cJNWJr4CHFTcdzB4lQF1dxwa2N/rPDiIzy9z8+c7deitkeuCQ7qmrggy5+0SIEfTZeYObDkIg79q7zQ1pCmBElBuClUdtdYr0WbHF1ho2qe0nkDjArzKAQq5nPNRZiUZc355Ay6kLar1JLaZUJtQ3mFhw6GYwQhDwnH5GmfXeIikzSbn+0CIlkeZiC/uowfBOR/dAJalT2hawd49thAZXPACAAlohWfRQj5azv8/wyipn2qXQnWANnAi2TD4hqepfx6eB+3ZEDLCk7Uix8szc8Hm+n+bFRqRe/Yt7t1Zl1Y5bKEVM8yhRIMIXjTypO3hxDEXg2KOiSu8zr6i92p/7RrtBjGGb2jx3d/SHjwYWn3633xv6WwsWol6Q7vMTU7wUSQpCQ4bjjWr3obACKQ3QoP7x6Y7BnD5eq7EIgZ9dVoBwRES3xgIIKu+4wuYwkQQivTJ2oq67QObSfBKmjShgd1mV684wZR3y20wWFiI3QkrqFlSds+OZPb3qCgTpcenmXeGImh0pbVQuzjaOAK/OsI7cPmRzdoEjG5138qtB//cJNExS8jQmFZU1A2a/LLBYozP8JpHyQqJrml9txVIp5cAD0DSYfl0nfphwX+6rras/Dy94GQQ+tEU7WjUYyGdQiZ+nID87G2nLUo+ekNqgs6RBrNuU2izC2elXOVjmfEJNI4mO9dZ2puw98/9c4kb7jFn3D84w7z6EP4RFel1XT8suGpbjI7fCDxqaK6hFDcGSwGL8HG6trI3d1hUbXIYgtoMUsxrHLXPlrt0q47hOfSMIzz4EcKf9wOnQFEYsGIOV3vXaa3/yyVvr5kvH08U/SGMfO3zFpoMOJxgXDTfLm52azOSedqyET89p6iDccN7x8eMN7Syo/tKOz+trb7qLe9rbVtIJGTz5J1xePO9tssFT7hbF5FxtaQN0RHy5pqbvE/hnwzNw2RghvsWf1r8tGytPDzt4L0CZSzpdfpxDsMc4sG3esOHiJmFgAoJg0wHEvcAS/R/eicf1XT+TfOjNiNfu/3o8GXn2J3KeFq+skIgVB+BItQQZoD/xRN1QW2iNpYAmsLTQ2zFOZDFlzdMITu8fuqw7O1bCXAXOqru+8Jd9NJqZa5qb9uz8ZX88ArBrhnfXfVlglIn0JmBHAjGzoeSZG4Vrb53mf4csHqkgXVgK+hXeQu1ctmRtOMi9LC4fCUjaf6HyRfY5Yln9dX8j67mGgV8A9wkdJcbi9ciV7cXeoVFoqDYJS1IvUgrj0ZfMdAI9cbFUPkT0a1vGa69OE5TYOizGRSRu52CWyAhZR2yvmb5aRF1VCkV1u0kcBHWrE2IRNQA1PiKkimLx0cvVYq8544nQbLf7dV+vPHVkqaquZbFqG7309JxjLkoLq+1mDWCemXjlZC+nMVY77l4Qc2ZkJInS74WZvrvA3fX697X1anogCruEhbKexSFM6Gf1RtP7ZPgBAfqV3rclO1Vs6xXQO4SAqg2auh86xrxEelrSgdpSRhzjAfNXudfE/GKRiNDSj/oibJ/FpT31+AfpwdCnzqG6O26Q5crcve8nqmYq9wclJNce2oYvx+Qj3Qhr6/Q7fh3hvY+Zf3o0SD8X/G6rjO3vtM/9YOIPCtrz+MRumtm9BeRMZkbEIX8Y5u/dxYs1ntajo42sV8PQc23z8Z5qsec0Rnp8tRcRX2AbZx9nlnDMyZ23eWKl6ZfAok7A8EqAes3S9KVuiiBRZHT/IH/HnySJDlsCCfaO5cWAAwvgRty73xO+zCktHiXUCCXV3fz5K8VdKfnMpHcJaEiJsGmt/Iqn6C4yNeFG/QSJSExfXAdSxjLs+luQqbipG6d7i3ex8efWXIz1hbVFTyLv1XlG2MGkq2aNdHf3AzNVyZ1Dhs2wf3fMek5Dq2z9/tbX5LTFfqsFq3ZVGqqw0IASKnOlf79pdjdc5pSMqafZpzYb9zvCsUYwj0PtABgQD32N3TMMUqatSV4vl3kpU156K+pA9iZQ9WAtgTiqrv7T8UmXPXEESkuylbVdnzbkkfIdff2l2P8ttewS54JQJelGM5Jv+lJq1ekd6Zilzzm1A8JvodnyBuZdBLMnNlA4MyZu6Qams9fzSwE5boSNnzHS+yU7HCnBm5YUt36PoRFVQ2UJ2TKR4ipYOCFl8MwzrPao803GjERy8hZLIaB7uKuKOVQiEHfFo7cfO/ZYfNviEtfnd5QsRFM5k6fXgF9EwTmhxLPxLkMwpUb29LT6+/6QDwQVXac7/Q4TSY5mfWd2DdjR+4Vs/gq/FOGzCuwaSDmzNzhLrKFOCGehtUZjUa5eVOFTgTZyLHUSjdFfCa6OS9x0aR5se4mrXbE3nq6AQJb6svvoc170A5axjCYcDulKLc3mCZge9GFVs17hlPDjgox5KT8qtX4zl/9KyYx1j4e19bP09NuQ9wUpBXZL8mSBRvEy0WpRVbE5V20LE0qBTWWwPHWS+IVrSj0Ld1BP84NVpyAU8/kaH+1MxPh9VqHxHa0/dsOFmZfEjK0QhMQkUNU4qeiNONPk7dbI24QUnjpM1LZv/Z58XFF3CcscFLnWHfhCpH/Wp28UhTvwBQlLy/JAzn0IHWKtwYzAINXqk4evsAsusE44wpIFDLyfCefkE37j74wm/hRawW5WmF/zyjcTQzbnlDRYkCfxao66nCc6n4KN6bZnyhu7PU1P17H5vbI2KyP55/59n37Smf531UGPYCWD+MO9dgeJb7726AW0na4ioRXX7Q46of9s8btXjPWePG6I2xQy6H5dj98jG9Y+mWp/QfIbU2U7NlddWncW35/bvheqSEHeb1SKuHgZvGFyRyb4n34/1nxQihseeAUxtEKLa1gn9rMCt3bITo6XI3hvjGa5GznltxAT1dPCCgAZAaPp4p+SsLZ0J1m7rk6exHbhOhP+8H3Gz7LRFZUjsIlLDIZq6tQY+3r5TuwD/tAD3WqnrlTmnuhflhrLp4i9rx8B8Pp3ZPLXt7HQQzjhoCmq4vJ/fEn+0Jq2Lll4eBF0rZzDVZZQQEqubecX5R2btQextTV3TfNCzxHVepP9ZqRfdiqsIXYOztPy86swlwP6wB7SfuSdSB03aAM/EMrMhysY7ZMOeBvHE86ceN+LAi72iSdeuYKX3vZ1g2ATA++DYI7LJoixjrANdOrczlxZPpnK/6zoXojNcyjlmM3Af43Hh/nf6Jd+xf7zQlJsiNiUZu5cOKR58tzpHX3Rdnhg++l8+MbPdueZF3cj/3SKBIW8h+y9zcXHng0lNFhsEnndvtDNMkG9gP4GgodM0dkgpyMOpEfA2OeD4xOba2fwuhVQ/DT80GidrKRTeWqRScTxoZBAWWynsExTRpp2zF2NYMkIUBWbKL3RUUZ78os6oxm8Arr/9tmt1WJW6FCpR7WKMdrhYgASu9ig712QcLVtXZQQZcx5P9WrC9tpPEPWYKffoCcEC+R3NYIPsE5/FI7xlAFdZ/b2LvD2NZvjs2kefGprI/Ju+jLvj5SGSPJBTbuvv6Y3pavs8yyydshJPOi/Ys+5jve1tLxwk8glRKonfifDke3tO3+RZIgyq4TpPaViVZi+TBkomUeJQk5/w6ukGyjb6NZMM/36Mb2bc3p6jKnBIBXbjZFD8Z11haxfkuBJIOmTJGyUut5vFdwPwgDpFp9cTkQ6PjveMalTNU20YT9kyyw3akJ9yTwnJu8tnnNhsv+b2/p2IfX2F5G5XkmVnx5eIQmTtVqAxBb4VbSrpr7h40GF5V5++bkaTceH8tfMXQAvvJN+OK9NhKYNCq6F5bV6yLci+ZbXsWy3oXezBs2Jmw2tUkpzY1g+omR+zSPddNGXXOYA/UgKKYhZZ3s5ihRgPGqvAXTyffWXJTDtwwfPzC+57WV/qJduvKD7nGrsPgKnix0aoQLHdS2xRwfk88LN7VmikbervbvaFRqvcaRsUFXqP2svzYPGrqdkf4rWr8k5zOxggjTy+Rzp0lZFWkN6o23IJVaHLDOGCtq4ngef2BB/t2lyxT73pi5AJg5MraU6VJMT5v1sNU/+tfgE++f0g+E5txMHdt2oykW/fn5aFPGYd6ORV0zv273TUquXGab4IdjZSW70liNOZv9pnYKQ3XtJk0ts8DiMQRwMPscE5r3427U3ZPaXeKLcjgZiIa1aIPdvk2SFjRt77fprf+CpnCxg64gq24yV8lVl0rd3Ve7I9cyQceA9QSvo0Rd2oPWbt+AvzJnuGHLEpVNLzxSoZXPX13VERlLSIu7NooUDSbc8gxm8aNAx7YijYYJhQnP4CX7BRTL0a2oeZhJyMObKRHv4cxZNtBtQjxEWGwMmOeZAdntyEqtX2indJgSS6WY+OozV/KoOZXLBoZQkHeepDxXpATIrhmCdT5275Nez8pfyhMutvSzFHcdSU4oIqaGRwDmfqQbRYiWjoV1vmzmsaMJYDQW4uVJtLuqCnrTgMZVomOza+BMmzXhDHoHm0QFyWPbVRJ6Rmn4fKMb/XPzmKRNlzHy3wYeZEhrHJFvcum950Q2wrQNXp+NBD+CKuV0+GLkrclWDD7gnE3yXF/e0/s97izuWXzbcDLI9mHxfH0oKyUVpCtdwqP0sY4mEIWnYwPQSAjpiyqiIIJOeQVBrad/jBCjuIfOaUQDdejTJW3e2cX2UTnNvZfHsaybmF8OZqVPKhn5UTxcDJdMt1xT7iV2D9+8G50vuomXwwMYBZ0X0ZJn2b69dpf3ntRJeTxHxkrzvAOFItddOLZn8vJ4inV1x6Xul90aBkFoRWqX5KQQ+z8HQdPCCNCOtjMWIZweuwIw0UsrsrTjUz+eyUmSDkfQwlinomk6hfrhZnD95mB/dePZ/Di9bqRBQLM8uIBL2zxj65iqPNh4Er6h9csnzI7+F0//i7SdcvJJ70L8zq92XGES/ctcAQ8UGM7CKaOyaXNnJzRBPeser+bMQd2Z1TIqSRKmVvNUpM07A/N+Q2VY96eqHAl8/imLTsL390ygpq0DkSWeQOCp2awgxhSIRba2rqSIBwUsUW48zUm8YaisPomtPwL1fdIhMmlxuAHMq718OJpYYsfmqtQ0N/Mddqj27gGCquOTwKdpKYc9pRQ+DFRxaioTVqPpINZnOSg0z+Ph7wzRsOHLi63zdILT/31+6bLM9am3dq1+aFHSjzUi9YWbttt6ZCNww+AVdCYjma7PkeDLnOvLug4OE6HkFmEGFImRyyEbZuWnKAB6dlEBqySj49nXJny2d9/uAHMunvYV0Sbd+KIKHvap6BWlolpESCLJ12bgi2wYq4xLV7TvSusFinKws1sf/amqOTg466Og8SsBXjEI8P6j93ybgdgL7pbv7+Zam7y33qJv7hfeWr7I4vDj9dCUwOeHHd2Igz5K69hbA0rmd/tUyDZqDvjCMMGQgPxikbSs2q2h99XBV/zow7uqUj2lDWInmiqMfeV/Lscp76y7z4pigJnp5Zt2U7iiH9osTB10jGKyelZCoYjwmFl+fW9/AdiJYKJE5A/xTucmsP8LIMFUbHLH312
*/