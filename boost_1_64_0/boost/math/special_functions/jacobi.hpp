//  (C) Copyright Nick Thompson 2019.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_JACOBI_HPP
#define BOOST_MATH_SPECIAL_JACOBI_HPP

#include <limits>
#include <stdexcept>

namespace boost { namespace math {

template<typename Real>
Real jacobi(unsigned n, Real alpha, Real beta, Real x)
{
    static_assert(!std::is_integral<Real>::value, "Jacobi polynomials do not work with integer arguments.");

    if (n == 0) {
        return Real(1);
    }
    Real y0 = 1;
    Real y1 = (alpha+1) + (alpha+beta+2)*(x-1)/Real(2);

    Real yk = y1;
    Real k = 2;
    Real k_max = n*(1+std::numeric_limits<Real>::epsilon());
    while(k < k_max)
    {
        // Hoping for lots of common subexpression elimination by the compiler:
        Real denom = 2*k*(k+alpha+beta)*(2*k+alpha+beta-2);
        Real gamma1 = (2*k+alpha+beta-1)*( (2*k+alpha+beta)*(2*k+alpha+beta-2)*x + alpha*alpha -beta*beta);
        Real gamma0 = -2*(k+alpha-1)*(k+beta-1)*(2*k+alpha+beta);
        yk = (gamma1*y1 + gamma0*y0)/denom;
        y0 = y1;
        y1 = yk;
        k += 1;
    }
    return yk;
}

template<typename Real>
Real jacobi_derivative(unsigned n, Real alpha, Real beta, Real x, unsigned k)
{
    if (k > n) {
        return Real(0);
    }
    Real scale = 1;
    for(unsigned j = 1; j <= k; ++j) {
        scale *= (alpha + beta + n + j)/2;
    }

    return scale*jacobi<Real>(n-k, alpha + k, beta+k, x);
}

template<typename Real>
Real jacobi_prime(unsigned n, Real alpha, Real beta, Real x)
{
    return jacobi_derivative<Real>(n, alpha, beta, x, 1);
}

template<typename Real>
Real jacobi_double_prime(unsigned n, Real alpha, Real beta, Real x)
{
    return jacobi_derivative<Real>(n, alpha, beta, x, 2);
}

}}
#endif

/* jacobi.hpp
4OfV1vvLXA8PqVtEovtM4yH7n6e7/24cjsf3fmlnPy92s4afTBDnHpMfwvpGInhMtN92qvx4Lf+tpsP2i36fKp70oRceql68V5/qf+8b1Hv0C7GLmv/mL7Cf4PyZ/HTuw+zmMbhP/K1rFwMXiUfr1SdSE+yLSyc9Rv5oS1fsha9uwGP+xCP/Md79xIWJ+MMF1jcYI6+G5Wk6cHG0nvAF/foyf7cDbnwwxjqx4tl4+H8XPj1RH8cX6t43wiGD6aavqC8kxlvHShzMhqu+Ne69E/A+eGYI/W1AcP5suuPsdDysBH/aDhdfYD2Kzvz5M/z2M/n0ZHUP+nhT9PgOvBkWN41vYRp710/XEl0/Msob/vHck+gs5+qju896mufCtw/AxUPh+D7m81p2frI8d64+g+PM7zW+f3vI9feblyR9RacZd7h9wxD6vf7mus/pkXjM5vvxi1Xy0TS627XysfEoy6QLdbeu96F0sXzzS1cteFT/+/jY4LxbrG97uni3Ge6OhadK2fk28SvbedfBC/j+hmz1CvkucoLnfZidix/zL+J3o/GBPnS4tebPOM00TrXq7M3uu9k8dPvBPNbgez/BTTV4YBf86k66iv2wJiywDkej/gj7euWODo5ZN9INXqdDTBeH5eVu+gUK8JEcx/x9eN82uCmeXeg76TYCv7uGPffB0zroC+jD/8zD/DeMn376hZfq3xipX/5edmlcpspvjV3V4QbSC3bhW3TU0JHyon2Vsx+gr7TEBePGf9P6mOdJ4tB5cPbx8Gozu3vL/kXme9GpsXAhnGAd1+LPvc+MNsYTj+op7g+gt9gnfsIW8/YGXNUA11bog+0NtxZ6/nh2bP+OLDgtqYjOc4xjLftPTAjO/8L6PPrJy1v0Z1hfYPPRdIfu5nulcbiEPryafhSrDpEEP5fBO73lVXXmhf3Fv37sml8v3kuP+E6+WGBel8VZD0w8fwPO2gb3htn/D9bxvkSfqziVyv7TD8LTtson+0L6480nnbJFvCmz/1L1GHHtFnXQt+AsfZGV1+tDGQkPZKg3w6nbx+pDcP8Vp+DXn8B38EEifJUJX6WVmN8TgvNaLmbHs+Hqj/nvNLiHPWa633b73aYskMc/VdfeFhyze8PdR8XiX/DtAfHhFvrvxBh6Ahy9pw0dJE79F896Nbr/vHrVVfTkKeJYnxh6Nhz3fTQP0YPaxIlHMfyQXjoizv7b1u8o0Lf2HvwH9034k93hDZsWug/eVHs9/WByWB1ZnKCzzbcvUKbrrzoplu4l7n4PH1Wpm90E/4bplz3hyT/1ZX6sDgU/z42Du6L7tVTTrUbRB+SlzX5fZl5W2Wdx9cfqqr5jTk+iP42zXuzh7Ph4/UjHwmUJ7uc9VlylnnmOcd7E/8YmBOclwuHfmJ/3zfuR8KZxKt1vHRrrG9ZE6IaVeO7z+NOj6l1RXjUW78403/abmH2dvPMPPPonPUt8XXesff3uju4/A/f/yp678Gf5rQoua8RHU8xPrb6UBteb2ouOuR6++ZsOQ8cJvUA3sp5CemZrccT8z9Dntc48d8fP3L9lKf38dngkLE+2ZTe95L+F9LUcdtvffZ8X967Dk+LUgenEq+y7MmgbXFZhPF+k69xr3cPoPvYhOL5cPbiPOLwSPmRvNX3EqSZ5uzPdbCT7bG88e/Pzr83fg/TvA+b3ZPMS5Utr+ecU+O8W8a0f/vJeW9dNCI5XG7f//gv991/68/pB3uPv0ThqPqsT6P+eK/k59cnleBN/zWYPE55Qp6QHN9B5N3fEd+mSM6fyT/eZ+714XS2+fcQeyvnX/+jAO+inAyPq4HBjWPyFFxL/hLfUtwrzouuk6JsZpy+Ibr8=
*/